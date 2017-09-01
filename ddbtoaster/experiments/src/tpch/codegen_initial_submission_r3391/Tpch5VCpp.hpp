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
  
  struct REGION_entry {
    long REGION_REGIONKEY; STRING_TYPE REGION_NAME; STRING_TYPE REGION_COMMENT; long __av; 
    explicit REGION_entry() { /*REGION_REGIONKEY = 0L; REGION_NAME = ""; REGION_COMMENT = ""; __av = 0L; */ }
    explicit REGION_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { REGION_REGIONKEY = c0; REGION_NAME = c1; REGION_COMMENT = c2; __av = c3; }
    REGION_entry(const REGION_entry& other) : REGION_REGIONKEY( other.REGION_REGIONKEY ), REGION_NAME( other.REGION_NAME ), REGION_COMMENT( other.REGION_COMMENT ), __av( other.__av ) {}
    FORCE_INLINE REGION_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { REGION_REGIONKEY = c0; REGION_NAME = c1; REGION_COMMENT = c2;  return *this; }
    FORCE_INLINE REGION_entry& modify01(const long c0, const STRING_TYPE& c1) { REGION_REGIONKEY = c0; REGION_NAME = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REGION_REGIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REGION_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REGION_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REGION_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const REGION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REGION_REGIONKEY);
      hash_combine(h, e.REGION_NAME);
      hash_combine(h, e.REGION_COMMENT);
      return h;
    }
    FORCE_INLINE static bool equals(const REGION_entry& x, const REGION_entry& y) {
      return x.REGION_REGIONKEY == y.REGION_REGIONKEY && x.REGION_NAME == y.REGION_NAME && x.REGION_COMMENT == y.REGION_COMMENT;
    }
  };
  
  struct REGION_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REGION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REGION_REGIONKEY);
      hash_combine(h, e.REGION_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REGION_entry& x, const REGION_entry& y) {
      return x.REGION_REGIONKEY == y.REGION_REGIONKEY && x.REGION_NAME == y.REGION_NAME;
    }
  };
  
  typedef MultiHashMap<REGION_entry,long,
    HashIndex<REGION_entry,long,REGION_mapkey012_idxfn,true>,
    HashIndex<REGION_entry,long,REGION_mapkey01_idxfn,false>
  > REGION_map;
  typedef HashIndex<REGION_entry,long,REGION_mapkey012_idxfn,true> HashIndex_REGION_map_012;
  typedef HashIndex<REGION_entry,long,REGION_mapkey01_idxfn,false> HashIndex_REGION_map_01;
  
  struct REVENUE_entry {
    STRING_TYPE N_NAME; DOUBLE_TYPE __av; 
    explicit REVENUE_entry() { /*N_NAME = ""; __av = 0.0; */ }
    explicit REVENUE_entry(const STRING_TYPE& c0, const DOUBLE_TYPE c1) { N_NAME = c0; __av = c1; }
    REVENUE_entry(const REVENUE_entry& other) : N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_entry& modify(const STRING_TYPE& c0) { N_NAME = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_entry& x, const REVENUE_entry& y) {
      return x.N_NAME == y.N_NAME;
    }
  };
  
  typedef MultiHashMap<REVENUE_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_entry,DOUBLE_TYPE,REVENUE_mapkey0_idxfn,true>
  > REVENUE_map;
  typedef HashIndex<REVENUE_entry,DOUBLE_TYPE,REVENUE_mapkey0_idxfn,true> HashIndex_REVENUE_map_0;
  
  struct REVENUE_mSUPPLIER2_entry {
    long REVENUE_mSUPPLIERSUPPLIER_NATIONKEY; long REVENUE_mSUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit REVENUE_mSUPPLIER2_entry() { /*REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = 0L; REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit REVENUE_mSUPPLIER2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = c0; REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = c1; __av = c2; }
    REVENUE_mSUPPLIER2_entry(const REVENUE_mSUPPLIER2_entry& other) : REVENUE_mSUPPLIERSUPPLIER_NATIONKEY( other.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY ), REVENUE_mSUPPLIERSUPPLIER_SUPPKEY( other.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mSUPPLIER2_entry& modify(const long c0, const long c1) { REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = c0; REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mSUPPLIER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY);
      hash_combine(h, e.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER2_entry& x, const REVENUE_mSUPPLIER2_entry& y) {
      return x.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY == y.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY && x.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY == y.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mSUPPLIER2_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mSUPPLIER2_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mapkey01_idxfn,true>
  > REVENUE_mSUPPLIER2_map;
  typedef HashIndex<REVENUE_mSUPPLIER2_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mapkey01_idxfn,true> HashIndex_REVENUE_mSUPPLIER2_map_01;
  
  struct REVENUE_mSUPPLIER2_mORDERS4_entry {
    long REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY; long REVENUE_mSUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit REVENUE_mSUPPLIER2_mORDERS4_entry() { /*REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY = 0L; REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit REVENUE_mSUPPLIER2_mORDERS4_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY = c0; REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = c1; __av = c2; }
    REVENUE_mSUPPLIER2_mORDERS4_entry(const REVENUE_mSUPPLIER2_mORDERS4_entry& other) : REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY( other.REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY ), REVENUE_mSUPPLIERSUPPLIER_SUPPKEY( other.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mSUPPLIER2_mORDERS4_entry& modify(const long c0, const long c1) { REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY = c0; REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mSUPPLIER2_mORDERS4_entry& modify0(const long c0) { REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUE_mSUPPLIER2_mORDERS4_entry& modify1(const long c1) { REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mSUPPLIER2_mORDERS4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER2_mORDERS4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY);
      hash_combine(h, e.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER2_mORDERS4_entry& x, const REVENUE_mSUPPLIER2_mORDERS4_entry& y) {
      return x.REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY == y.REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY && x.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY == y.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  struct REVENUE_mSUPPLIER2_mORDERS4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER2_mORDERS4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER2_mORDERS4_entry& x, const REVENUE_mSUPPLIER2_mORDERS4_entry& y) {
      return x.REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY == y.REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY;
    }
  };
  
  struct REVENUE_mSUPPLIER2_mORDERS4_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER2_mORDERS4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER2_mORDERS4_entry& x, const REVENUE_mSUPPLIER2_mORDERS4_entry& y) {
      return x.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY == y.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mSUPPLIER2_mORDERS4_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mSUPPLIER2_mORDERS4_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mORDERS4_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mSUPPLIER2_mORDERS4_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mORDERS4_mapkey0_idxfn,false>,
    HashIndex<REVENUE_mSUPPLIER2_mORDERS4_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mORDERS4_mapkey1_idxfn,false>
  > REVENUE_mSUPPLIER2_mORDERS4_map;
  typedef HashIndex<REVENUE_mSUPPLIER2_mORDERS4_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mORDERS4_mapkey01_idxfn,true> HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_01;
  typedef HashIndex<REVENUE_mSUPPLIER2_mORDERS4_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mORDERS4_mapkey0_idxfn,false> HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0;
  typedef HashIndex<REVENUE_mSUPPLIER2_mORDERS4_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mORDERS4_mapkey1_idxfn,false> HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_1;
  
  struct REVENUE_mSUPPLIER2_mCUSTOMER1_entry {
    long REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY; long REVENUE_mSUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit REVENUE_mSUPPLIER2_mCUSTOMER1_entry() { /*REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY = 0L; REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit REVENUE_mSUPPLIER2_mCUSTOMER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY = c0; REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = c1; __av = c2; }
    REVENUE_mSUPPLIER2_mCUSTOMER1_entry(const REVENUE_mSUPPLIER2_mCUSTOMER1_entry& other) : REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY( other.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY ), REVENUE_mSUPPLIERSUPPLIER_SUPPKEY( other.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mSUPPLIER2_mCUSTOMER1_entry& modify(const long c0, const long c1) { REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY = c0; REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mSUPPLIER2_mCUSTOMER1_entry& modify0(const long c0) { REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY = c0;  return *this; }
    FORCE_INLINE REVENUE_mSUPPLIER2_mCUSTOMER1_entry& modify1(const long c1) { REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER2_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER2_mCUSTOMER1_entry& x, const REVENUE_mSUPPLIER2_mCUSTOMER1_entry& y) {
      return x.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY && x.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY == y.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  struct REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER2_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER2_mCUSTOMER1_entry& x, const REVENUE_mSUPPLIER2_mCUSTOMER1_entry& y) {
      return x.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER2_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER2_mCUSTOMER1_entry& x, const REVENUE_mSUPPLIER2_mCUSTOMER1_entry& y) {
      return x.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY == y.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mSUPPLIER2_mCUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mSUPPLIER2_mCUSTOMER1_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mSUPPLIER2_mCUSTOMER1_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey0_idxfn,false>,
    HashIndex<REVENUE_mSUPPLIER2_mCUSTOMER1_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey1_idxfn,false>
  > REVENUE_mSUPPLIER2_mCUSTOMER1_map;
  typedef HashIndex<REVENUE_mSUPPLIER2_mCUSTOMER1_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey01_idxfn,true> HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_01;
  typedef HashIndex<REVENUE_mSUPPLIER2_mCUSTOMER1_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey0_idxfn,false> HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_0;
  typedef HashIndex<REVENUE_mSUPPLIER2_mCUSTOMER1_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey1_idxfn,false> HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_1;
  
  struct REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry {
    long REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY; long REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY; long __av; 
    explicit REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry() { /*REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = 0L; REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY = 0L; __av = 0L; */ }
    explicit REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry(const long c0, const long c1, const long c2) { REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = c0; REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY = c1; __av = c2; }
    REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry(const REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& other) : REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY( other.REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY ), REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY( other.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& modify(const long c0, const long c1) { REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = c0; REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& modify0(const long c0) { REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& modify1(const long c1) { REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& x, const REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& y) {
      return x.REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY && x.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& x, const REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& y) {
      return x.REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& x, const REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry& y) {
      return x.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry,long,
    HashIndex<REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry,long,REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry,long,REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey0_idxfn,false>,
    HashIndex<REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry,long,REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey1_idxfn,false>
  > REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map;
  typedef HashIndex<REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry,long,REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey01_idxfn,true> HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_01;
  typedef HashIndex<REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry,long,REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey0_idxfn,false> HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0;
  typedef HashIndex<REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry,long,REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey1_idxfn,false> HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_1;
  
  struct REVENUE_mLINEITEM1_T_2_entry {
    long C_NATIONKEY; long REVENUE_mLINEITEMLINEITEM_ORDERKEY; long __av; 
    explicit REVENUE_mLINEITEM1_T_2_entry() { /*C_NATIONKEY = 0L; REVENUE_mLINEITEMLINEITEM_ORDERKEY = 0L; __av = 0L; */ }
    explicit REVENUE_mLINEITEM1_T_2_entry(const long c0, const long c1, const long c2) { C_NATIONKEY = c0; REVENUE_mLINEITEMLINEITEM_ORDERKEY = c1; __av = c2; }
    REVENUE_mLINEITEM1_T_2_entry(const REVENUE_mLINEITEM1_T_2_entry& other) : C_NATIONKEY( other.C_NATIONKEY ), REVENUE_mLINEITEMLINEITEM_ORDERKEY( other.REVENUE_mLINEITEMLINEITEM_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mLINEITEM1_T_2_entry& modify(const long c0, const long c1) { C_NATIONKEY = c0; REVENUE_mLINEITEMLINEITEM_ORDERKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mLINEITEM1_T_2_entry& modify1(const long c1) { REVENUE_mLINEITEMLINEITEM_ORDERKEY = c1;  return *this; }
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
  struct REVENUE_mLINEITEM1_T_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM1_T_2_entry& x, const REVENUE_mLINEITEM1_T_2_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.REVENUE_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct REVENUE_mLINEITEM1_T_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM1_T_2_entry& x, const REVENUE_mLINEITEM1_T_2_entry& y) {
      return x.REVENUE_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mLINEITEM1_T_2_entry,long,
    HashIndex<REVENUE_mLINEITEM1_T_2_entry,long,REVENUE_mLINEITEM1_T_2_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mLINEITEM1_T_2_entry,long,REVENUE_mLINEITEM1_T_2_mapkey1_idxfn,false>
  > REVENUE_mLINEITEM1_T_2_map;
  typedef HashIndex<REVENUE_mLINEITEM1_T_2_entry,long,REVENUE_mLINEITEM1_T_2_mapkey01_idxfn,true> HashIndex_REVENUE_mLINEITEM1_T_2_map_01;
  typedef HashIndex<REVENUE_mLINEITEM1_T_2_entry,long,REVENUE_mLINEITEM1_T_2_mapkey1_idxfn,false> HashIndex_REVENUE_mLINEITEM1_T_2_map_1;
  
  struct REVENUE_mLINEITEM1_T_3_entry {
    long REVENUE_mLINEITEMLINEITEM_SUPPKEY; long C_NATIONKEY; long __av; 
    explicit REVENUE_mLINEITEM1_T_3_entry() { /*REVENUE_mLINEITEMLINEITEM_SUPPKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUE_mLINEITEM1_T_3_entry(const long c0, const long c1, const long c2) { REVENUE_mLINEITEMLINEITEM_SUPPKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUE_mLINEITEM1_T_3_entry(const REVENUE_mLINEITEM1_T_3_entry& other) : REVENUE_mLINEITEMLINEITEM_SUPPKEY( other.REVENUE_mLINEITEMLINEITEM_SUPPKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mLINEITEM1_T_3_entry& modify(const long c0, const long c1) { REVENUE_mLINEITEMLINEITEM_SUPPKEY = c0; C_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mLINEITEM1_T_3_entry& modify0(const long c0) { REVENUE_mLINEITEMLINEITEM_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mLINEITEMLINEITEM_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mLINEITEM1_T_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_SUPPKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM1_T_3_entry& x, const REVENUE_mLINEITEM1_T_3_entry& y) {
      return x.REVENUE_mLINEITEMLINEITEM_SUPPKEY == y.REVENUE_mLINEITEMLINEITEM_SUPPKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  struct REVENUE_mLINEITEM1_T_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM1_T_3_entry& x, const REVENUE_mLINEITEM1_T_3_entry& y) {
      return x.REVENUE_mLINEITEMLINEITEM_SUPPKEY == y.REVENUE_mLINEITEMLINEITEM_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mLINEITEM1_T_3_entry,long,
    HashIndex<REVENUE_mLINEITEM1_T_3_entry,long,REVENUE_mLINEITEM1_T_3_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mLINEITEM1_T_3_entry,long,REVENUE_mLINEITEM1_T_3_mapkey0_idxfn,false>
  > REVENUE_mLINEITEM1_T_3_map;
  typedef HashIndex<REVENUE_mLINEITEM1_T_3_entry,long,REVENUE_mLINEITEM1_T_3_mapkey01_idxfn,true> HashIndex_REVENUE_mLINEITEM1_T_3_map_01;
  typedef HashIndex<REVENUE_mLINEITEM1_T_3_entry,long,REVENUE_mLINEITEM1_T_3_mapkey0_idxfn,false> HashIndex_REVENUE_mLINEITEM1_T_3_map_0;
  
  struct REVENUE_mORDERS1_T_2_entry {
    long REVENUE_mORDERSORDERS_CUSTKEY; long C_NATIONKEY; long __av; 
    explicit REVENUE_mORDERS1_T_2_entry() { /*REVENUE_mORDERSORDERS_CUSTKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUE_mORDERS1_T_2_entry(const long c0, const long c1, const long c2) { REVENUE_mORDERSORDERS_CUSTKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUE_mORDERS1_T_2_entry(const REVENUE_mORDERS1_T_2_entry& other) : REVENUE_mORDERSORDERS_CUSTKEY( other.REVENUE_mORDERSORDERS_CUSTKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mORDERS1_T_2_entry& modify(const long c0, const long c1) { REVENUE_mORDERSORDERS_CUSTKEY = c0; C_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mORDERS1_T_2_entry& modify0(const long c0) { REVENUE_mORDERSORDERS_CUSTKEY = c0;  return *this; }
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
  struct REVENUE_mORDERS1_T_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mORDERS1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mORDERSORDERS_CUSTKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mORDERS1_T_2_entry& x, const REVENUE_mORDERS1_T_2_entry& y) {
      return x.REVENUE_mORDERSORDERS_CUSTKEY == y.REVENUE_mORDERSORDERS_CUSTKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  struct REVENUE_mORDERS1_T_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mORDERS1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mORDERS1_T_2_entry& x, const REVENUE_mORDERS1_T_2_entry& y) {
      return x.REVENUE_mORDERSORDERS_CUSTKEY == y.REVENUE_mORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mORDERS1_T_2_entry,long,
    HashIndex<REVENUE_mORDERS1_T_2_entry,long,REVENUE_mORDERS1_T_2_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mORDERS1_T_2_entry,long,REVENUE_mORDERS1_T_2_mapkey0_idxfn,false>
  > REVENUE_mORDERS1_T_2_map;
  typedef HashIndex<REVENUE_mORDERS1_T_2_entry,long,REVENUE_mORDERS1_T_2_mapkey01_idxfn,true> HashIndex_REVENUE_mORDERS1_T_2_map_01;
  typedef HashIndex<REVENUE_mORDERS1_T_2_entry,long,REVENUE_mORDERS1_T_2_mapkey0_idxfn,false> HashIndex_REVENUE_mORDERS1_T_2_map_0;
  
  struct REVENUE_mORDERS1_T_3_entry {
    long REVENUE_mORDERSORDERS_ORDERKEY; long C_NATIONKEY; DOUBLE_TYPE __av; 
    explicit REVENUE_mORDERS1_T_3_entry() { /*REVENUE_mORDERSORDERS_ORDERKEY = 0L; C_NATIONKEY = 0L; __av = 0.0; */ }
    explicit REVENUE_mORDERS1_T_3_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { REVENUE_mORDERSORDERS_ORDERKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUE_mORDERS1_T_3_entry(const REVENUE_mORDERS1_T_3_entry& other) : REVENUE_mORDERSORDERS_ORDERKEY( other.REVENUE_mORDERSORDERS_ORDERKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mORDERS1_T_3_entry& modify(const long c0, const long c1) { REVENUE_mORDERSORDERS_ORDERKEY = c0; C_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mORDERS1_T_3_entry& modify0(const long c0) { REVENUE_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mORDERS1_T_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mORDERS1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mORDERSORDERS_ORDERKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mORDERS1_T_3_entry& x, const REVENUE_mORDERS1_T_3_entry& y) {
      return x.REVENUE_mORDERSORDERS_ORDERKEY == y.REVENUE_mORDERSORDERS_ORDERKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  struct REVENUE_mORDERS1_T_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mORDERS1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mORDERS1_T_3_entry& x, const REVENUE_mORDERS1_T_3_entry& y) {
      return x.REVENUE_mORDERSORDERS_ORDERKEY == y.REVENUE_mORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mORDERS1_T_3_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mORDERS1_T_3_entry,DOUBLE_TYPE,REVENUE_mORDERS1_T_3_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mORDERS1_T_3_entry,DOUBLE_TYPE,REVENUE_mORDERS1_T_3_mapkey0_idxfn,false>
  > REVENUE_mORDERS1_T_3_map;
  typedef HashIndex<REVENUE_mORDERS1_T_3_entry,DOUBLE_TYPE,REVENUE_mORDERS1_T_3_mapkey01_idxfn,true> HashIndex_REVENUE_mORDERS1_T_3_map_01;
  typedef HashIndex<REVENUE_mORDERS1_T_3_entry,DOUBLE_TYPE,REVENUE_mORDERS1_T_3_mapkey0_idxfn,false> HashIndex_REVENUE_mORDERS1_T_3_map_0;
  
  struct REVENUE_mCUSTOMER1_entry {
    long REVENUE_mCUSTOMERCUSTOMER_NATIONKEY; STRING_TYPE N_NAME; long __av; 
    explicit REVENUE_mCUSTOMER1_entry() { /*REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = 0L; N_NAME = ""; __av = 0L; */ }
    explicit REVENUE_mCUSTOMER1_entry(const long c0, const STRING_TYPE& c1, const long c2) { REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c0; N_NAME = c1; __av = c2; }
    REVENUE_mCUSTOMER1_entry(const REVENUE_mCUSTOMER1_entry& other) : REVENUE_mCUSTOMERCUSTOMER_NATIONKEY( other.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mCUSTOMER1_entry& modify(const long c0, const STRING_TYPE& c1) { REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c0; N_NAME = c1;  return *this; }
    FORCE_INLINE REVENUE_mCUSTOMER1_entry& modify0(const long c0) { REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mCUSTOMER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_entry& x, const REVENUE_mCUSTOMER1_entry& y) {
      return x.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY == y.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  struct REVENUE_mCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_entry& x, const REVENUE_mCUSTOMER1_entry& y) {
      return x.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY == y.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mCUSTOMER1_entry,long,
    HashIndex<REVENUE_mCUSTOMER1_entry,long,REVENUE_mCUSTOMER1_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mCUSTOMER1_entry,long,REVENUE_mCUSTOMER1_mapkey0_idxfn,false>
  > REVENUE_mCUSTOMER1_map;
  typedef HashIndex<REVENUE_mCUSTOMER1_entry,long,REVENUE_mCUSTOMER1_mapkey01_idxfn,true> HashIndex_REVENUE_mCUSTOMER1_map_01;
  typedef HashIndex<REVENUE_mCUSTOMER1_entry,long,REVENUE_mCUSTOMER1_mapkey0_idxfn,false> HashIndex_REVENUE_mCUSTOMER1_map_0;
  
  struct REVENUE_mCUSTOMER2_entry {
    long REVENUE_mCUSTOMERCUSTOMER_CUSTKEY; long REVENUE_mCUSTOMERCUSTOMER_NATIONKEY; DOUBLE_TYPE __av; 
    explicit REVENUE_mCUSTOMER2_entry() { /*REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = 0L; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = 0L; __av = 0.0; */ }
    explicit REVENUE_mCUSTOMER2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c0; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c1; __av = c2; }
    REVENUE_mCUSTOMER2_entry(const REVENUE_mCUSTOMER2_entry& other) : REVENUE_mCUSTOMERCUSTOMER_CUSTKEY( other.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY ), REVENUE_mCUSTOMERCUSTOMER_NATIONKEY( other.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mCUSTOMER2_entry& modify(const long c0, const long c1) { REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c0; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mCUSTOMER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER2_entry& x, const REVENUE_mCUSTOMER2_entry& y) {
      return x.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY && x.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY == y.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mCUSTOMER2_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mCUSTOMER2_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER2_mapkey01_idxfn,true>
  > REVENUE_mCUSTOMER2_map;
  typedef HashIndex<REVENUE_mCUSTOMER2_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER2_mapkey01_idxfn,true> HashIndex_REVENUE_mCUSTOMER2_map_01;
  
  
  
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
    data_t(): tlq_t() {
      c2 = Udate(STRING_TYPE("1995-1-1"));
      c1 = Udate(STRING_TYPE("1994-1-1"));
      c3 = STRING_TYPE("ASIA");
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_NATION(const long nation_nationkey, const STRING_TYPE nation_name, const long nation_regionkey, const STRING_TYPE nation_comment) {
      NATION_entry e(nation_nationkey, nation_name, nation_regionkey, nation_comment, 1L);
      NATION.addOrDelOnZero(e,1L);
    }
    
    void on_insert_REGION(const long region_regionkey, const STRING_TYPE region_name, const STRING_TYPE region_comment) {
      REGION_entry e(region_regionkey, region_name, region_comment, 1L);
      REGION.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        {  // foreach
          const HashIndex_REVENUE_mCUSTOMER1_map_01* i1 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_01*>(REVENUE_mCUSTOMER1.index[0]);
          HashIndex_REVENUE_mCUSTOMER1_map_01::IdxNode* n1; 
          REVENUE_mCUSTOMER1_entry* e1;
        
          for (size_t i = 0; i < i1->size_; i++)
          {
            n1 = i1->buckets_ + i;
            while (n1 && (e1 = n1->obj))
            {
                long c_nationkey = e1->REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
                STRING_TYPE n_name = e1->N_NAME;
                long v1 = e1->__av;
                REVENUE.addOrDelOnZero(se1.modify(n_name),((v1 * (REVENUE_mLINEITEM1_T_2.getValueOrDefault(se2.modify(c_nationkey,lineitem_orderkey)) * REVENUE_mLINEITEM1_T_3.getValueOrDefault(se3.modify(lineitem_suppkey,c_nationkey)))) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n1 = n1->nxt;
            }
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM1_T_2_map_1* i2 = static_cast<HashIndex_REVENUE_mLINEITEM1_T_2_map_1*>(REVENUE_mLINEITEM1_T_2.index[1]);
          const HASH_RES_t h1 = REVENUE_mLINEITEM1_T_2_mapkey1_idxfn::hash(se5.modify1(lineitem_orderkey));
          HashIndex_REVENUE_mLINEITEM1_T_2_map_1::IdxNode* n2 = static_cast<HashIndex_REVENUE_mLINEITEM1_T_2_map_1::IdxNode*>(i2->slice(se5, h1));
          REVENUE_mLINEITEM1_T_2_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long revenue_msuppliersupplier_nationkey = e2->C_NATIONKEY;
              long v2 = e2->__av;
              REVENUE_mSUPPLIER2.addOrDelOnZero(se4.modify(revenue_msuppliersupplier_nationkey,lineitem_suppkey),(v2 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h1 == n2->hash &&  REVENUE_mLINEITEM1_T_2_mapkey1_idxfn::equals(se5, *e2)); 
          }
        }REVENUE_mSUPPLIER2_mORDERS4.addOrDelOnZero(se6.modify(lineitem_orderkey,lineitem_suppkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount))));
        { //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0* i3 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0*>(REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1.index[1]);
          const HASH_RES_t h2 = REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey0_idxfn::hash(se8.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0::IdxNode* n3 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0::IdxNode*>(i3->slice(se8, h2));
          REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              long revenue_msupplier2_mcustomercustomer_custkey = e3->REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY;
              long v3 = e3->__av;
              REVENUE_mSUPPLIER2_mCUSTOMER1.addOrDelOnZero(se7.modify(revenue_msupplier2_mcustomercustomer_custkey,lineitem_suppkey),(v3 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h2 == n3->hash &&  REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey0_idxfn::equals(se8, *e3)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM1_T_3_map_0* i4 = static_cast<HashIndex_REVENUE_mLINEITEM1_T_3_map_0*>(REVENUE_mLINEITEM1_T_3.index[1]);
          const HASH_RES_t h3 = REVENUE_mLINEITEM1_T_3_mapkey0_idxfn::hash(se10.modify0(lineitem_suppkey));
          HashIndex_REVENUE_mLINEITEM1_T_3_map_0::IdxNode* n4 = static_cast<HashIndex_REVENUE_mLINEITEM1_T_3_map_0::IdxNode*>(i4->slice(se10, h3));
          REVENUE_mLINEITEM1_T_3_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long c_nationkey = e4->C_NATIONKEY;
              long v4 = e4->__av;
              REVENUE_mORDERS1_T_3.addOrDelOnZero(se9.modify(lineitem_orderkey,c_nationkey),(v4 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h3 == n4->hash &&  REVENUE_mLINEITEM1_T_3_mapkey0_idxfn::equals(se10, *e4)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0* i5 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0*>(REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1.index[1]);
          const HASH_RES_t h5 = REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey0_idxfn::hash(se13.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0::IdxNode* n5 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0::IdxNode*>(i5->slice(se13, h5));
          REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long revenue_mcustomercustomer_custkey = e5->REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY;
              long v5 = e5->__av;
              { //slice 
                const HashIndex_REVENUE_mLINEITEM1_T_3_map_0* i6 = static_cast<HashIndex_REVENUE_mLINEITEM1_T_3_map_0*>(REVENUE_mLINEITEM1_T_3.index[1]);
                const HASH_RES_t h4 = REVENUE_mLINEITEM1_T_3_mapkey0_idxfn::hash(se12.modify0(lineitem_suppkey));
                HashIndex_REVENUE_mLINEITEM1_T_3_map_0::IdxNode* n6 = static_cast<HashIndex_REVENUE_mLINEITEM1_T_3_map_0::IdxNode*>(i6->slice(se12, h4));
                REVENUE_mLINEITEM1_T_3_entry* e6;
               
                if (n6 && (e6 = n6->obj)) {
                  do {                
                    long revenue_mcustomercustomer_nationkey = e6->C_NATIONKEY;
                    long v6 = e6->__av;
                    REVENUE_mCUSTOMER2.addOrDelOnZero(se11.modify(revenue_mcustomercustomer_custkey,revenue_mcustomercustomer_nationkey),(v5 * (v6 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
                    n6 = n6->nxt;
                  } while (n6 && (e6 = n6->obj) && h4 == n6->hash &&  REVENUE_mLINEITEM1_T_3_mapkey0_idxfn::equals(se12, *e6)); 
                }
              }
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey0_idxfn::equals(se13, *e5)); 
          }
        }
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        {  // foreach
          const HashIndex_REVENUE_mCUSTOMER1_map_01* i7 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_01*>(REVENUE_mCUSTOMER1.index[0]);
          HashIndex_REVENUE_mCUSTOMER1_map_01::IdxNode* n7; 
          REVENUE_mCUSTOMER1_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long c_nationkey = e7->REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
                STRING_TYPE n_name = e7->N_NAME;
                long v7 = e7->__av;
                REVENUE.addOrDelOnZero(se14.modify(n_name),((v7 * (REVENUE_mLINEITEM1_T_2.getValueOrDefault(se15.modify(c_nationkey,lineitem_orderkey)) * REVENUE_mLINEITEM1_T_3.getValueOrDefault(se16.modify(lineitem_suppkey,c_nationkey)))) * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n7 = n7->nxt;
            }
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM1_T_2_map_1* i8 = static_cast<HashIndex_REVENUE_mLINEITEM1_T_2_map_1*>(REVENUE_mLINEITEM1_T_2.index[1]);
          const HASH_RES_t h6 = REVENUE_mLINEITEM1_T_2_mapkey1_idxfn::hash(se18.modify1(lineitem_orderkey));
          HashIndex_REVENUE_mLINEITEM1_T_2_map_1::IdxNode* n8 = static_cast<HashIndex_REVENUE_mLINEITEM1_T_2_map_1::IdxNode*>(i8->slice(se18, h6));
          REVENUE_mLINEITEM1_T_2_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              long revenue_msuppliersupplier_nationkey = e8->C_NATIONKEY;
              long v8 = e8->__av;
              REVENUE_mSUPPLIER2.addOrDelOnZero(se17.modify(revenue_msuppliersupplier_nationkey,lineitem_suppkey),(v8 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h6 == n8->hash &&  REVENUE_mLINEITEM1_T_2_mapkey1_idxfn::equals(se18, *e8)); 
          }
        }REVENUE_mSUPPLIER2_mORDERS4.addOrDelOnZero(se19.modify(lineitem_orderkey,lineitem_suppkey),(-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
        { //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0* i9 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0*>(REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1.index[1]);
          const HASH_RES_t h7 = REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey0_idxfn::hash(se21.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0::IdxNode* n9 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0::IdxNode*>(i9->slice(se21, h7));
          REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              long revenue_msupplier2_mcustomercustomer_custkey = e9->REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY;
              long v9 = e9->__av;
              REVENUE_mSUPPLIER2_mCUSTOMER1.addOrDelOnZero(se20.modify(revenue_msupplier2_mcustomercustomer_custkey,lineitem_suppkey),(v9 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h7 == n9->hash &&  REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey0_idxfn::equals(se21, *e9)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM1_T_3_map_0* i10 = static_cast<HashIndex_REVENUE_mLINEITEM1_T_3_map_0*>(REVENUE_mLINEITEM1_T_3.index[1]);
          const HASH_RES_t h8 = REVENUE_mLINEITEM1_T_3_mapkey0_idxfn::hash(se23.modify0(lineitem_suppkey));
          HashIndex_REVENUE_mLINEITEM1_T_3_map_0::IdxNode* n10 = static_cast<HashIndex_REVENUE_mLINEITEM1_T_3_map_0::IdxNode*>(i10->slice(se23, h8));
          REVENUE_mLINEITEM1_T_3_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              long c_nationkey = e10->C_NATIONKEY;
              long v10 = e10->__av;
              REVENUE_mORDERS1_T_3.addOrDelOnZero(se22.modify(lineitem_orderkey,c_nationkey),(v10 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h8 == n10->hash &&  REVENUE_mLINEITEM1_T_3_mapkey0_idxfn::equals(se23, *e10)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0* i11 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0*>(REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1.index[1]);
          const HASH_RES_t h10 = REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey0_idxfn::hash(se26.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0::IdxNode* n11 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_0::IdxNode*>(i11->slice(se26, h10));
          REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              long revenue_mcustomercustomer_custkey = e11->REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY;
              long v11 = e11->__av;
              { //slice 
                const HashIndex_REVENUE_mLINEITEM1_T_3_map_0* i12 = static_cast<HashIndex_REVENUE_mLINEITEM1_T_3_map_0*>(REVENUE_mLINEITEM1_T_3.index[1]);
                const HASH_RES_t h9 = REVENUE_mLINEITEM1_T_3_mapkey0_idxfn::hash(se25.modify0(lineitem_suppkey));
                HashIndex_REVENUE_mLINEITEM1_T_3_map_0::IdxNode* n12 = static_cast<HashIndex_REVENUE_mLINEITEM1_T_3_map_0::IdxNode*>(i12->slice(se25, h9));
                REVENUE_mLINEITEM1_T_3_entry* e12;
               
                if (n12 && (e12 = n12->obj)) {
                  do {                
                    long revenue_mcustomercustomer_nationkey = e12->C_NATIONKEY;
                    long v12 = e12->__av;
                    REVENUE_mCUSTOMER2.addOrDelOnZero(se24.modify(revenue_mcustomercustomer_custkey,revenue_mcustomercustomer_nationkey),(v11 * (v12 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
                    n12 = n12->nxt;
                  } while (n12 && (e12 = n12->obj) && h9 == n12->hash &&  REVENUE_mLINEITEM1_T_3_mapkey0_idxfn::equals(se25, *e12)); 
                }
              }
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h10 == n11->hash &&  REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey0_idxfn::equals(se26, *e11)); 
          }
        }
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        {  // foreach
          const HashIndex_REVENUE_mCUSTOMER1_map_01* i13 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_01*>(REVENUE_mCUSTOMER1.index[0]);
          HashIndex_REVENUE_mCUSTOMER1_map_01::IdxNode* n13; 
          REVENUE_mCUSTOMER1_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long c_nationkey = e13->REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
                STRING_TYPE n_name = e13->N_NAME;
                long v13 = e13->__av;
                (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE.addOrDelOnZero(se27.modify(n_name),(v13 * (REVENUE_mORDERS1_T_2.getValueOrDefault(se28.modify(orders_custkey,c_nationkey)) * REVENUE_mORDERS1_T_3.getValueOrDefault(se29.modify(orders_orderkey,c_nationkey))))) : (void)0);
              n13 = n13->nxt;
            }
          }
        }{ //slice 
          const HashIndex_REVENUE_mORDERS1_T_2_map_0* i14 = static_cast<HashIndex_REVENUE_mORDERS1_T_2_map_0*>(REVENUE_mORDERS1_T_2.index[1]);
          const HASH_RES_t h12 = REVENUE_mORDERS1_T_2_mapkey0_idxfn::hash(se32.modify0(orders_custkey));
          HashIndex_REVENUE_mORDERS1_T_2_map_0::IdxNode* n14 = static_cast<HashIndex_REVENUE_mORDERS1_T_2_map_0::IdxNode*>(i14->slice(se32, h12));
          REVENUE_mORDERS1_T_2_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              long revenue_msuppliersupplier_nationkey = e14->C_NATIONKEY;
              long v14 = e14->__av;
              { //slice 
                const HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0* i15 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0*>(REVENUE_mSUPPLIER2_mORDERS4.index[1]);
                const HASH_RES_t h11 = REVENUE_mSUPPLIER2_mORDERS4_mapkey0_idxfn::hash(se31.modify0(orders_orderkey));
                HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0::IdxNode* n15 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0::IdxNode*>(i15->slice(se31, h11));
                REVENUE_mSUPPLIER2_mORDERS4_entry* e15;
               
                if (n15 && (e15 = n15->obj)) {
                  do {                
                    long revenue_msuppliersupplier_suppkey = e15->REVENUE_mSUPPLIERSUPPLIER_SUPPKEY;
                    DOUBLE_TYPE v15 = e15->__av;
                    (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE_mSUPPLIER2.addOrDelOnZero(se30.modify(revenue_msuppliersupplier_nationkey,revenue_msuppliersupplier_suppkey),(v14 * v15)) : (void)0);
                    n15 = n15->nxt;
                  } while (n15 && (e15 = n15->obj) && h11 == n15->hash &&  REVENUE_mSUPPLIER2_mORDERS4_mapkey0_idxfn::equals(se31, *e15)); 
                }
              }
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h12 == n14->hash &&  REVENUE_mORDERS1_T_2_mapkey0_idxfn::equals(se32, *e14)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0* i16 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0*>(REVENUE_mSUPPLIER2_mORDERS4.index[1]);
          const HASH_RES_t h13 = REVENUE_mSUPPLIER2_mORDERS4_mapkey0_idxfn::hash(se34.modify0(orders_orderkey));
          HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0::IdxNode* n16 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0::IdxNode*>(i16->slice(se34, h13));
          REVENUE_mSUPPLIER2_mORDERS4_entry* e16;
         
          if (n16 && (e16 = n16->obj)) {
            do {                
              long revenue_msuppliersupplier_suppkey = e16->REVENUE_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v16 = e16->__av;
              (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE_mSUPPLIER2_mCUSTOMER1.addOrDelOnZero(se33.modify(orders_custkey,revenue_msuppliersupplier_suppkey),v16) : (void)0);
              n16 = n16->nxt;
            } while (n16 && (e16 = n16->obj) && h13 == n16->hash &&  REVENUE_mSUPPLIER2_mORDERS4_mapkey0_idxfn::equals(se34, *e16)); 
          }
        }(/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1.addOrDelOnZero(se35.modify(orders_orderkey,orders_custkey),1L) : (void)0);
        { //slice 
          const HashIndex_REVENUE_mORDERS1_T_2_map_0* i17 = static_cast<HashIndex_REVENUE_mORDERS1_T_2_map_0*>(REVENUE_mORDERS1_T_2.index[1]);
          const HASH_RES_t h14 = REVENUE_mORDERS1_T_2_mapkey0_idxfn::hash(se37.modify0(orders_custkey));
          HashIndex_REVENUE_mORDERS1_T_2_map_0::IdxNode* n17 = static_cast<HashIndex_REVENUE_mORDERS1_T_2_map_0::IdxNode*>(i17->slice(se37, h14));
          REVENUE_mORDERS1_T_2_entry* e17;
         
          if (n17 && (e17 = n17->obj)) {
            do {                
              long c_nationkey = e17->C_NATIONKEY;
              long v17 = e17->__av;
              (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE_mLINEITEM1_T_2.addOrDelOnZero(se36.modify(c_nationkey,orders_orderkey),v17) : (void)0);
              n17 = n17->nxt;
            } while (n17 && (e17 = n17->obj) && h14 == n17->hash &&  REVENUE_mORDERS1_T_2_mapkey0_idxfn::equals(se37, *e17)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mORDERS1_T_3_map_0* i18 = static_cast<HashIndex_REVENUE_mORDERS1_T_3_map_0*>(REVENUE_mORDERS1_T_3.index[1]);
          const HASH_RES_t h15 = REVENUE_mORDERS1_T_3_mapkey0_idxfn::hash(se39.modify0(orders_orderkey));
          HashIndex_REVENUE_mORDERS1_T_3_map_0::IdxNode* n18 = static_cast<HashIndex_REVENUE_mORDERS1_T_3_map_0::IdxNode*>(i18->slice(se39, h15));
          REVENUE_mORDERS1_T_3_entry* e18;
         
          if (n18 && (e18 = n18->obj)) {
            do {                
              long revenue_mcustomercustomer_nationkey = e18->C_NATIONKEY;
              DOUBLE_TYPE v18 = e18->__av;
              (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE_mCUSTOMER2.addOrDelOnZero(se38.modify(orders_custkey,revenue_mcustomercustomer_nationkey),v18) : (void)0);
              n18 = n18->nxt;
            } while (n18 && (e18 = n18->obj) && h15 == n18->hash &&  REVENUE_mORDERS1_T_3_mapkey0_idxfn::equals(se39, *e18)); 
          }
        }
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        {  // foreach
          const HashIndex_REVENUE_mCUSTOMER1_map_01* i19 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_01*>(REVENUE_mCUSTOMER1.index[0]);
          HashIndex_REVENUE_mCUSTOMER1_map_01::IdxNode* n19; 
          REVENUE_mCUSTOMER1_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long c_nationkey = e19->REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
                STRING_TYPE n_name = e19->N_NAME;
                long v19 = e19->__av;
                (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE.addOrDelOnZero(se40.modify(n_name),((v19 * (REVENUE_mORDERS1_T_2.getValueOrDefault(se41.modify(orders_custkey,c_nationkey)) * REVENUE_mORDERS1_T_3.getValueOrDefault(se42.modify(orders_orderkey,c_nationkey)))) * -1L)) : (void)0);
              n19 = n19->nxt;
            }
          }
        }{ //slice 
          const HashIndex_REVENUE_mORDERS1_T_2_map_0* i20 = static_cast<HashIndex_REVENUE_mORDERS1_T_2_map_0*>(REVENUE_mORDERS1_T_2.index[1]);
          const HASH_RES_t h17 = REVENUE_mORDERS1_T_2_mapkey0_idxfn::hash(se45.modify0(orders_custkey));
          HashIndex_REVENUE_mORDERS1_T_2_map_0::IdxNode* n20 = static_cast<HashIndex_REVENUE_mORDERS1_T_2_map_0::IdxNode*>(i20->slice(se45, h17));
          REVENUE_mORDERS1_T_2_entry* e20;
         
          if (n20 && (e20 = n20->obj)) {
            do {                
              long revenue_msuppliersupplier_nationkey = e20->C_NATIONKEY;
              long v20 = e20->__av;
              { //slice 
                const HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0* i21 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0*>(REVENUE_mSUPPLIER2_mORDERS4.index[1]);
                const HASH_RES_t h16 = REVENUE_mSUPPLIER2_mORDERS4_mapkey0_idxfn::hash(se44.modify0(orders_orderkey));
                HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0::IdxNode* n21 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0::IdxNode*>(i21->slice(se44, h16));
                REVENUE_mSUPPLIER2_mORDERS4_entry* e21;
               
                if (n21 && (e21 = n21->obj)) {
                  do {                
                    long revenue_msuppliersupplier_suppkey = e21->REVENUE_mSUPPLIERSUPPLIER_SUPPKEY;
                    DOUBLE_TYPE v21 = e21->__av;
                    (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE_mSUPPLIER2.addOrDelOnZero(se43.modify(revenue_msuppliersupplier_nationkey,revenue_msuppliersupplier_suppkey),(v20 * (v21 * -1L))) : (void)0);
                    n21 = n21->nxt;
                  } while (n21 && (e21 = n21->obj) && h16 == n21->hash &&  REVENUE_mSUPPLIER2_mORDERS4_mapkey0_idxfn::equals(se44, *e21)); 
                }
              }
              n20 = n20->nxt;
            } while (n20 && (e20 = n20->obj) && h17 == n20->hash &&  REVENUE_mORDERS1_T_2_mapkey0_idxfn::equals(se45, *e20)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0* i22 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0*>(REVENUE_mSUPPLIER2_mORDERS4.index[1]);
          const HASH_RES_t h18 = REVENUE_mSUPPLIER2_mORDERS4_mapkey0_idxfn::hash(se47.modify0(orders_orderkey));
          HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0::IdxNode* n22 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_0::IdxNode*>(i22->slice(se47, h18));
          REVENUE_mSUPPLIER2_mORDERS4_entry* e22;
         
          if (n22 && (e22 = n22->obj)) {
            do {                
              long revenue_msuppliersupplier_suppkey = e22->REVENUE_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v22 = e22->__av;
              (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE_mSUPPLIER2_mCUSTOMER1.addOrDelOnZero(se46.modify(orders_custkey,revenue_msuppliersupplier_suppkey),(v22 * -1L)) : (void)0);
              n22 = n22->nxt;
            } while (n22 && (e22 = n22->obj) && h18 == n22->hash &&  REVENUE_mSUPPLIER2_mORDERS4_mapkey0_idxfn::equals(se47, *e22)); 
          }
        }(/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1.addOrDelOnZero(se48.modify(orders_orderkey,orders_custkey),-1L) : (void)0);
        { //slice 
          const HashIndex_REVENUE_mORDERS1_T_2_map_0* i23 = static_cast<HashIndex_REVENUE_mORDERS1_T_2_map_0*>(REVENUE_mORDERS1_T_2.index[1]);
          const HASH_RES_t h19 = REVENUE_mORDERS1_T_2_mapkey0_idxfn::hash(se50.modify0(orders_custkey));
          HashIndex_REVENUE_mORDERS1_T_2_map_0::IdxNode* n23 = static_cast<HashIndex_REVENUE_mORDERS1_T_2_map_0::IdxNode*>(i23->slice(se50, h19));
          REVENUE_mORDERS1_T_2_entry* e23;
         
          if (n23 && (e23 = n23->obj)) {
            do {                
              long c_nationkey = e23->C_NATIONKEY;
              long v23 = e23->__av;
              (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE_mLINEITEM1_T_2.addOrDelOnZero(se49.modify(c_nationkey,orders_orderkey),(v23 * -1L)) : (void)0);
              n23 = n23->nxt;
            } while (n23 && (e23 = n23->obj) && h19 == n23->hash &&  REVENUE_mORDERS1_T_2_mapkey0_idxfn::equals(se50, *e23)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mORDERS1_T_3_map_0* i24 = static_cast<HashIndex_REVENUE_mORDERS1_T_3_map_0*>(REVENUE_mORDERS1_T_3.index[1]);
          const HASH_RES_t h20 = REVENUE_mORDERS1_T_3_mapkey0_idxfn::hash(se52.modify0(orders_orderkey));
          HashIndex_REVENUE_mORDERS1_T_3_map_0::IdxNode* n24 = static_cast<HashIndex_REVENUE_mORDERS1_T_3_map_0::IdxNode*>(i24->slice(se52, h20));
          REVENUE_mORDERS1_T_3_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              long revenue_mcustomercustomer_nationkey = e24->C_NATIONKEY;
              DOUBLE_TYPE v24 = e24->__av;
              (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE_mCUSTOMER2.addOrDelOnZero(se51.modify(orders_custkey,revenue_mcustomercustomer_nationkey),(v24 * -1L)) : (void)0);
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h20 == n24->hash &&  REVENUE_mORDERS1_T_3_mapkey0_idxfn::equals(se52, *e24)); 
          }
        }
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_map_0* i25 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_0*>(REVENUE_mCUSTOMER1.index[1]);
          const HASH_RES_t h21 = REVENUE_mCUSTOMER1_mapkey0_idxfn::hash(se55.modify0(customer_nationkey));
          HashIndex_REVENUE_mCUSTOMER1_map_0::IdxNode* n25 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_0::IdxNode*>(i25->slice(se55, h21));
          REVENUE_mCUSTOMER1_entry* e25;
         
          if (n25 && (e25 = n25->obj)) {
            do {                
              STRING_TYPE n_name = e25->N_NAME;
              long v25 = e25->__av;
              REVENUE.addOrDelOnZero(se53.modify(n_name),(v25 * REVENUE_mCUSTOMER2.getValueOrDefault(se54.modify(customer_custkey,customer_nationkey))));
              n25 = n25->nxt;
            } while (n25 && (e25 = n25->obj) && h21 == n25->hash &&  REVENUE_mCUSTOMER1_mapkey0_idxfn::equals(se55, *e25)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_0* i26 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_0*>(REVENUE_mSUPPLIER2_mCUSTOMER1.index[1]);
          const HASH_RES_t h22 = REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey0_idxfn::hash(se57.modify0(customer_custkey));
          HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_0::IdxNode* n26 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_0::IdxNode*>(i26->slice(se57, h22));
          REVENUE_mSUPPLIER2_mCUSTOMER1_entry* e26;
         
          if (n26 && (e26 = n26->obj)) {
            do {                
              long revenue_msuppliersupplier_suppkey = e26->REVENUE_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v26 = e26->__av;
              REVENUE_mSUPPLIER2.addOrDelOnZero(se56.modify(customer_nationkey,revenue_msuppliersupplier_suppkey),v26);
              n26 = n26->nxt;
            } while (n26 && (e26 = n26->obj) && h22 == n26->hash &&  REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey0_idxfn::equals(se57, *e26)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_1* i27 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_1*>(REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1.index[2]);
          const HASH_RES_t h23 = REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey1_idxfn::hash(se59.modify1(customer_custkey));
          HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_1::IdxNode* n27 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_1::IdxNode*>(i27->slice(se59, h23));
          REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry* e27;
         
          if (n27 && (e27 = n27->obj)) {
            do {                
              long revenue_mlineitemlineitem_orderkey = e27->REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
              long v27 = e27->__av;
              REVENUE_mLINEITEM1_T_2.addOrDelOnZero(se58.modify(customer_nationkey,revenue_mlineitemlineitem_orderkey),v27);
              n27 = n27->nxt;
            } while (n27 && (e27 = n27->obj) && h23 == n27->hash &&  REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey1_idxfn::equals(se59, *e27)); 
          }
        }REVENUE_mORDERS1_T_2.addOrDelOnZero(se60.modify(customer_custkey,customer_nationkey),1L);
      }
    }
    void on_delete_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_map_0* i28 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_0*>(REVENUE_mCUSTOMER1.index[1]);
          const HASH_RES_t h24 = REVENUE_mCUSTOMER1_mapkey0_idxfn::hash(se63.modify0(customer_nationkey));
          HashIndex_REVENUE_mCUSTOMER1_map_0::IdxNode* n28 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_0::IdxNode*>(i28->slice(se63, h24));
          REVENUE_mCUSTOMER1_entry* e28;
         
          if (n28 && (e28 = n28->obj)) {
            do {                
              STRING_TYPE n_name = e28->N_NAME;
              long v28 = e28->__av;
              REVENUE.addOrDelOnZero(se61.modify(n_name),(v28 * (REVENUE_mCUSTOMER2.getValueOrDefault(se62.modify(customer_custkey,customer_nationkey)) * -1L)));
              n28 = n28->nxt;
            } while (n28 && (e28 = n28->obj) && h24 == n28->hash &&  REVENUE_mCUSTOMER1_mapkey0_idxfn::equals(se63, *e28)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_0* i29 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_0*>(REVENUE_mSUPPLIER2_mCUSTOMER1.index[1]);
          const HASH_RES_t h25 = REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey0_idxfn::hash(se65.modify0(customer_custkey));
          HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_0::IdxNode* n29 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_0::IdxNode*>(i29->slice(se65, h25));
          REVENUE_mSUPPLIER2_mCUSTOMER1_entry* e29;
         
          if (n29 && (e29 = n29->obj)) {
            do {                
              long revenue_msuppliersupplier_suppkey = e29->REVENUE_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v29 = e29->__av;
              REVENUE_mSUPPLIER2.addOrDelOnZero(se64.modify(customer_nationkey,revenue_msuppliersupplier_suppkey),(v29 * -1L));
              n29 = n29->nxt;
            } while (n29 && (e29 = n29->obj) && h25 == n29->hash &&  REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey0_idxfn::equals(se65, *e29)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_1* i30 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_1*>(REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1.index[2]);
          const HASH_RES_t h26 = REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey1_idxfn::hash(se67.modify1(customer_custkey));
          HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_1::IdxNode* n30 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map_1::IdxNode*>(i30->slice(se67, h26));
          REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry* e30;
         
          if (n30 && (e30 = n30->obj)) {
            do {                
              long revenue_mlineitemlineitem_orderkey = e30->REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
              long v30 = e30->__av;
              REVENUE_mLINEITEM1_T_2.addOrDelOnZero(se66.modify(customer_nationkey,revenue_mlineitemlineitem_orderkey),(v30 * -1L));
              n30 = n30->nxt;
            } while (n30 && (e30 = n30->obj) && h26 == n30->hash &&  REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_mapkey1_idxfn::equals(se67, *e30)); 
          }
        }REVENUE_mORDERS1_T_2.addOrDelOnZero(se68.modify(customer_custkey,customer_nationkey),-1L);
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_map_0* i31 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_0*>(REVENUE_mCUSTOMER1.index[1]);
          const HASH_RES_t h27 = REVENUE_mCUSTOMER1_mapkey0_idxfn::hash(se71.modify0(supplier_nationkey));
          HashIndex_REVENUE_mCUSTOMER1_map_0::IdxNode* n31 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_0::IdxNode*>(i31->slice(se71, h27));
          REVENUE_mCUSTOMER1_entry* e31;
         
          if (n31 && (e31 = n31->obj)) {
            do {                
              STRING_TYPE n_name = e31->N_NAME;
              long v31 = e31->__av;
              REVENUE.addOrDelOnZero(se69.modify(n_name),(v31 * REVENUE_mSUPPLIER2.getValueOrDefault(se70.modify(supplier_nationkey,supplier_suppkey))));
              n31 = n31->nxt;
            } while (n31 && (e31 = n31->obj) && h27 == n31->hash &&  REVENUE_mCUSTOMER1_mapkey0_idxfn::equals(se71, *e31)); 
          }
        }REVENUE_mLINEITEM1_T_3.addOrDelOnZero(se72.modify(supplier_suppkey,supplier_nationkey),1L);
        { //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_1* i32 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_1*>(REVENUE_mSUPPLIER2_mORDERS4.index[2]);
          const HASH_RES_t h28 = REVENUE_mSUPPLIER2_mORDERS4_mapkey1_idxfn::hash(se74.modify1(supplier_suppkey));
          HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_1::IdxNode* n32 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_1::IdxNode*>(i32->slice(se74, h28));
          REVENUE_mSUPPLIER2_mORDERS4_entry* e32;
         
          if (n32 && (e32 = n32->obj)) {
            do {                
              long revenue_mordersorders_orderkey = e32->REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v32 = e32->__av;
              REVENUE_mORDERS1_T_3.addOrDelOnZero(se73.modify(revenue_mordersorders_orderkey,supplier_nationkey),v32);
              n32 = n32->nxt;
            } while (n32 && (e32 = n32->obj) && h28 == n32->hash &&  REVENUE_mSUPPLIER2_mORDERS4_mapkey1_idxfn::equals(se74, *e32)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_1* i33 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_1*>(REVENUE_mSUPPLIER2_mCUSTOMER1.index[2]);
          const HASH_RES_t h29 = REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey1_idxfn::hash(se76.modify1(supplier_suppkey));
          HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_1::IdxNode* n33 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_1::IdxNode*>(i33->slice(se76, h29));
          REVENUE_mSUPPLIER2_mCUSTOMER1_entry* e33;
         
          if (n33 && (e33 = n33->obj)) {
            do {                
              long revenue_mcustomercustomer_custkey = e33->REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY;
              DOUBLE_TYPE v33 = e33->__av;
              REVENUE_mCUSTOMER2.addOrDelOnZero(se75.modify(revenue_mcustomercustomer_custkey,supplier_nationkey),v33);
              n33 = n33->nxt;
            } while (n33 && (e33 = n33->obj) && h29 == n33->hash &&  REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey1_idxfn::equals(se76, *e33)); 
          }
        }
      }
    }
    void on_delete_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_map_0* i34 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_0*>(REVENUE_mCUSTOMER1.index[1]);
          const HASH_RES_t h30 = REVENUE_mCUSTOMER1_mapkey0_idxfn::hash(se79.modify0(supplier_nationkey));
          HashIndex_REVENUE_mCUSTOMER1_map_0::IdxNode* n34 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_0::IdxNode*>(i34->slice(se79, h30));
          REVENUE_mCUSTOMER1_entry* e34;
         
          if (n34 && (e34 = n34->obj)) {
            do {                
              STRING_TYPE n_name = e34->N_NAME;
              long v34 = e34->__av;
              REVENUE.addOrDelOnZero(se77.modify(n_name),(v34 * (REVENUE_mSUPPLIER2.getValueOrDefault(se78.modify(supplier_nationkey,supplier_suppkey)) * -1L)));
              n34 = n34->nxt;
            } while (n34 && (e34 = n34->obj) && h30 == n34->hash &&  REVENUE_mCUSTOMER1_mapkey0_idxfn::equals(se79, *e34)); 
          }
        }REVENUE_mLINEITEM1_T_3.addOrDelOnZero(se80.modify(supplier_suppkey,supplier_nationkey),-1L);
        { //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_1* i35 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_1*>(REVENUE_mSUPPLIER2_mORDERS4.index[2]);
          const HASH_RES_t h31 = REVENUE_mSUPPLIER2_mORDERS4_mapkey1_idxfn::hash(se82.modify1(supplier_suppkey));
          HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_1::IdxNode* n35 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mORDERS4_map_1::IdxNode*>(i35->slice(se82, h31));
          REVENUE_mSUPPLIER2_mORDERS4_entry* e35;
         
          if (n35 && (e35 = n35->obj)) {
            do {                
              long revenue_mordersorders_orderkey = e35->REVENUE_mSUPPLIER2_mORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v35 = e35->__av;
              REVENUE_mORDERS1_T_3.addOrDelOnZero(se81.modify(revenue_mordersorders_orderkey,supplier_nationkey),(v35 * -1L));
              n35 = n35->nxt;
            } while (n35 && (e35 = n35->obj) && h31 == n35->hash &&  REVENUE_mSUPPLIER2_mORDERS4_mapkey1_idxfn::equals(se82, *e35)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_1* i36 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_1*>(REVENUE_mSUPPLIER2_mCUSTOMER1.index[2]);
          const HASH_RES_t h32 = REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey1_idxfn::hash(se84.modify1(supplier_suppkey));
          HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_1::IdxNode* n36 = static_cast<HashIndex_REVENUE_mSUPPLIER2_mCUSTOMER1_map_1::IdxNode*>(i36->slice(se84, h32));
          REVENUE_mSUPPLIER2_mCUSTOMER1_entry* e36;
         
          if (n36 && (e36 = n36->obj)) {
            do {                
              long revenue_mcustomercustomer_custkey = e36->REVENUE_mSUPPLIER2_mCUSTOMERCUSTOMER_CUSTKEY;
              DOUBLE_TYPE v36 = e36->__av;
              REVENUE_mCUSTOMER2.addOrDelOnZero(se83.modify(revenue_mcustomercustomer_custkey,supplier_nationkey),(v36 * -1L));
              n36 = n36->nxt;
            } while (n36 && (e36 = n36->obj) && h32 == n36->hash &&  REVENUE_mSUPPLIER2_mCUSTOMER1_mapkey1_idxfn::equals(se84, *e36)); 
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        REVENUE_mCUSTOMER1.clear();
        STRING_TYPE l1 = c3;
        {  // foreach
          const HashIndex_NATION_map_0123* i37 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n37; 
          NATION_entry* e37;
        
          for (size_t i = 0; i < i37->size_; i++)
          {
            n37 = i37->buckets_ + i;
            while (n37 && (e37 = n37->obj))
            {
                long revenue_mcustomercustomer_nationkey = e37->NATION_NATIONKEY;
                STRING_TYPE n_name = e37->NATION_NAME;
                long n_regionkey = e37->NATION_REGIONKEY;
                STRING_TYPE n_comment = e37->NATION_COMMENT;
                long v37 = e37->__av;
                { //slice 
                  const HashIndex_REGION_map_01* i38 = static_cast<HashIndex_REGION_map_01*>(REGION.index[1]);
                  const HASH_RES_t h33 = REGION_mapkey01_idxfn::hash(se86.modify01(n_regionkey, l1));
                  HashIndex_REGION_map_01::IdxNode* n38 = static_cast<HashIndex_REGION_map_01::IdxNode*>(i38->slice(se86, h33));
                  REGION_entry* e38;
                 
                  if (n38 && (e38 = n38->obj)) {
                    do {                
                      STRING_TYPE r_comment = e38->REGION_COMMENT;
                      long v38 = e38->__av;
                      REVENUE_mCUSTOMER1.addOrDelOnZero(se85.modify(revenue_mcustomercustomer_nationkey,n_name),(v37 * v38));
                      n38 = n38->nxt;
                    } while (n38 && (e38 = n38->obj) && h33 == n38->hash &&  REGION_mapkey01_idxfn::equals(se86, *e38)); 
                  }
                }
              n37 = n37->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    REVENUE_entry se1;
    REVENUE_mLINEITEM1_T_2_entry se2;
    REVENUE_mLINEITEM1_T_3_entry se3;
    REVENUE_mSUPPLIER2_entry se4;
    REVENUE_mLINEITEM1_T_2_entry se5;
    REVENUE_mSUPPLIER2_mORDERS4_entry se6;
    REVENUE_mSUPPLIER2_mCUSTOMER1_entry se7;
    REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry se8;
    REVENUE_mORDERS1_T_3_entry se9;
    REVENUE_mLINEITEM1_T_3_entry se10;
    REVENUE_mCUSTOMER2_entry se11;
    REVENUE_mLINEITEM1_T_3_entry se12;
    REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry se13;
    REVENUE_entry se14;
    REVENUE_mLINEITEM1_T_2_entry se15;
    REVENUE_mLINEITEM1_T_3_entry se16;
    REVENUE_mSUPPLIER2_entry se17;
    REVENUE_mLINEITEM1_T_2_entry se18;
    REVENUE_mSUPPLIER2_mORDERS4_entry se19;
    REVENUE_mSUPPLIER2_mCUSTOMER1_entry se20;
    REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry se21;
    REVENUE_mORDERS1_T_3_entry se22;
    REVENUE_mLINEITEM1_T_3_entry se23;
    REVENUE_mCUSTOMER2_entry se24;
    REVENUE_mLINEITEM1_T_3_entry se25;
    REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry se26;
    REVENUE_entry se27;
    REVENUE_mORDERS1_T_2_entry se28;
    REVENUE_mORDERS1_T_3_entry se29;
    REVENUE_mSUPPLIER2_entry se30;
    REVENUE_mSUPPLIER2_mORDERS4_entry se31;
    REVENUE_mORDERS1_T_2_entry se32;
    REVENUE_mSUPPLIER2_mCUSTOMER1_entry se33;
    REVENUE_mSUPPLIER2_mORDERS4_entry se34;
    REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry se35;
    REVENUE_mLINEITEM1_T_2_entry se36;
    REVENUE_mORDERS1_T_2_entry se37;
    REVENUE_mCUSTOMER2_entry se38;
    REVENUE_mORDERS1_T_3_entry se39;
    REVENUE_entry se40;
    REVENUE_mORDERS1_T_2_entry se41;
    REVENUE_mORDERS1_T_3_entry se42;
    REVENUE_mSUPPLIER2_entry se43;
    REVENUE_mSUPPLIER2_mORDERS4_entry se44;
    REVENUE_mORDERS1_T_2_entry se45;
    REVENUE_mSUPPLIER2_mCUSTOMER1_entry se46;
    REVENUE_mSUPPLIER2_mORDERS4_entry se47;
    REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry se48;
    REVENUE_mLINEITEM1_T_2_entry se49;
    REVENUE_mORDERS1_T_2_entry se50;
    REVENUE_mCUSTOMER2_entry se51;
    REVENUE_mORDERS1_T_3_entry se52;
    REVENUE_entry se53;
    REVENUE_mCUSTOMER2_entry se54;
    REVENUE_mCUSTOMER1_entry se55;
    REVENUE_mSUPPLIER2_entry se56;
    REVENUE_mSUPPLIER2_mCUSTOMER1_entry se57;
    REVENUE_mLINEITEM1_T_2_entry se58;
    REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry se59;
    REVENUE_mORDERS1_T_2_entry se60;
    REVENUE_entry se61;
    REVENUE_mCUSTOMER2_entry se62;
    REVENUE_mCUSTOMER1_entry se63;
    REVENUE_mSUPPLIER2_entry se64;
    REVENUE_mSUPPLIER2_mCUSTOMER1_entry se65;
    REVENUE_mLINEITEM1_T_2_entry se66;
    REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_entry se67;
    REVENUE_mORDERS1_T_2_entry se68;
    REVENUE_entry se69;
    REVENUE_mSUPPLIER2_entry se70;
    REVENUE_mCUSTOMER1_entry se71;
    REVENUE_mLINEITEM1_T_3_entry se72;
    REVENUE_mORDERS1_T_3_entry se73;
    REVENUE_mSUPPLIER2_mORDERS4_entry se74;
    REVENUE_mCUSTOMER2_entry se75;
    REVENUE_mSUPPLIER2_mCUSTOMER1_entry se76;
    REVENUE_entry se77;
    REVENUE_mSUPPLIER2_entry se78;
    REVENUE_mCUSTOMER1_entry se79;
    REVENUE_mLINEITEM1_T_3_entry se80;
    REVENUE_mORDERS1_T_3_entry se81;
    REVENUE_mSUPPLIER2_mORDERS4_entry se82;
    REVENUE_mCUSTOMER2_entry se83;
    REVENUE_mSUPPLIER2_mCUSTOMER1_entry se84;
    REVENUE_mCUSTOMER1_entry se85;
    REGION_entry se86;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REGION_map REGION;
    REVENUE_mSUPPLIER2_map REVENUE_mSUPPLIER2;
    REVENUE_mSUPPLIER2_mORDERS4_map REVENUE_mSUPPLIER2_mORDERS4;
    REVENUE_mSUPPLIER2_mCUSTOMER1_map REVENUE_mSUPPLIER2_mCUSTOMER1;
    REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1_map REVENUE_mSUPPLIER2_mCUSTOMER1_mLINEITEM1;
    REVENUE_mLINEITEM1_T_2_map REVENUE_mLINEITEM1_T_2;
    REVENUE_mLINEITEM1_T_3_map REVENUE_mLINEITEM1_T_3;
    REVENUE_mORDERS1_T_2_map REVENUE_mORDERS1_T_2;
    REVENUE_mORDERS1_T_3_map REVENUE_mORDERS1_T_3;
    REVENUE_mCUSTOMER1_map REVENUE_mCUSTOMER1;
    REVENUE_mCUSTOMER2_map REVENUE_mCUSTOMER2;
    
    /*const static*/ long c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
  
  };

}
