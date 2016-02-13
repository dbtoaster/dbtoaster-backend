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
    FORCE_INLINE NATION_entry& modify1(const STRING_TYPE& c1) { NATION_NAME = c1;  return *this; }
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
  
  struct NATION_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const NATION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NATION_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const NATION_entry& x, const NATION_entry& y) {
      return x.NATION_NAME == y.NATION_NAME;
    }
  };
  
  typedef MultiHashMap<NATION_entry,long,
    HashIndex<NATION_entry,long,NATION_mapkey0123_idxfn,true>,
    HashIndex<NATION_entry,long,NATION_mapkey1_idxfn,false>
  > NATION_map;
  typedef HashIndex<NATION_entry,long,NATION_mapkey0123_idxfn,true> HashIndex_NATION_map_0123;
  typedef HashIndex<NATION_entry,long,NATION_mapkey1_idxfn,false> HashIndex_NATION_map_1;
  
  struct QUERY11_entry {
    long P_PARTKEY; DOUBLE_TYPE __av; 
    explicit QUERY11_entry() { /*P_PARTKEY = 0L; __av = 0.0; */ }
    explicit QUERY11_entry(const long c0, const DOUBLE_TYPE c1) { P_PARTKEY = c0; __av = c1; }
    QUERY11_entry(const QUERY11_entry& other) : P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11_entry& modify(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11_entry& x, const QUERY11_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11_entry,DOUBLE_TYPE,
    HashIndex<QUERY11_entry,DOUBLE_TYPE,QUERY11_mapkey0_idxfn,true>
  > QUERY11_map;
  typedef HashIndex<QUERY11_entry,DOUBLE_TYPE,QUERY11_mapkey0_idxfn,true> HashIndex_QUERY11_map_0;
  
  struct QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry {
    long QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_NATIONKEY; long __av; 
    explicit QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry() { /*QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_NATIONKEY = 0L; __av = 0L; */ }
    explicit QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry(const long c0, const long c1) { QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_NATIONKEY = c0; __av = c1; }
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry(const QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry& other) : QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_NATIONKEY( other.QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry& modify(const long c0) { QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry& x, const QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry& y) {
      return x.QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_NATIONKEY == y.QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry,long,
    HashIndex<QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry,long,QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_mapkey0_idxfn,true>
  > QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_map;
  typedef HashIndex<QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry,long,QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_mapkey0_idxfn,true> HashIndex_QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_map_0;
  
  struct QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry {
    long QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry() { /*QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry(const long c0, const DOUBLE_TYPE c1) { QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY = c0; __av = c1; }
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry(const QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry& other) : QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY( other.QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry& modify(const long c0) { QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry& x, const QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry& y) {
      return x.QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY == y.QUERY11_mPARTSUPP1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry,DOUBLE_TYPE,
    HashIndex<QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry,DOUBLE_TYPE,QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_mapkey0_idxfn,true>
  > QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_map;
  typedef HashIndex<QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry,DOUBLE_TYPE,QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_mapkey0_idxfn,true> HashIndex_QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_map_0;
  
  struct QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry {
    long QUERY11_mPARTSUPP1_L1_1_mPARTSUPPPARTSUPP_SUPPKEY; long __av; 
    explicit QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry() { /*QUERY11_mPARTSUPP1_L1_1_mPARTSUPPPARTSUPP_SUPPKEY = 0L; __av = 0L; */ }
    explicit QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry(const long c0, const long c1) { QUERY11_mPARTSUPP1_L1_1_mPARTSUPPPARTSUPP_SUPPKEY = c0; __av = c1; }
    QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry(const QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry& other) : QUERY11_mPARTSUPP1_L1_1_mPARTSUPPPARTSUPP_SUPPKEY( other.QUERY11_mPARTSUPP1_L1_1_mPARTSUPPPARTSUPP_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry& modify(const long c0) { QUERY11_mPARTSUPP1_L1_1_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY11_mPARTSUPP1_L1_1_mPARTSUPPPARTSUPP_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11_mPARTSUPP1_L1_1_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry& x, const QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry& y) {
      return x.QUERY11_mPARTSUPP1_L1_1_mPARTSUPPPARTSUPP_SUPPKEY == y.QUERY11_mPARTSUPP1_L1_1_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry,long,
    HashIndex<QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry,long,QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_mapkey0_idxfn,true>
  > QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_map;
  typedef HashIndex<QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry,long,QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_mapkey0_idxfn,true> HashIndex_QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_map_0;
  
  struct QUERY11_mPARTSUPP1_E2_1_entry {
    long P_PARTKEY; long __av; 
    explicit QUERY11_mPARTSUPP1_E2_1_entry() { /*P_PARTKEY = 0L; __av = 0L; */ }
    explicit QUERY11_mPARTSUPP1_E2_1_entry(const long c0, const long c1) { P_PARTKEY = c0; __av = c1; }
    QUERY11_mPARTSUPP1_E2_1_entry(const QUERY11_mPARTSUPP1_E2_1_entry& other) : P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11_mPARTSUPP1_E2_1_entry& modify(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11_mPARTSUPP1_E2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11_mPARTSUPP1_E2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11_mPARTSUPP1_E2_1_entry& x, const QUERY11_mPARTSUPP1_E2_1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11_mPARTSUPP1_E2_1_entry,long,
    HashIndex<QUERY11_mPARTSUPP1_E2_1_entry,long,QUERY11_mPARTSUPP1_E2_1_mapkey0_idxfn,true>
  > QUERY11_mPARTSUPP1_E2_1_map;
  typedef HashIndex<QUERY11_mPARTSUPP1_E2_1_entry,long,QUERY11_mPARTSUPP1_E2_1_mapkey0_idxfn,true> HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0;
  
  struct QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry {
    long QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY; long P_PARTKEY; long __av; 
    explicit QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry() { /*QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; P_PARTKEY = 0L; __av = 0L; */ }
    explicit QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry(const long c0, const long c1, const long c2) { QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY = c0; P_PARTKEY = c1; __av = c2; }
    QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry(const QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry& other) : QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY( other.QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY ), P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry& modify(const long c0, const long c1) { QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY = c0; P_PARTKEY = c1;  return *this; }
    FORCE_INLINE QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry& modify0(const long c0) { QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry& x, const QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry& y) {
      return x.QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY == y.QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY && x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry& x, const QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry& y) {
      return x.QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY == y.QUERY11_mPARTSUPP1_E2_1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry,long,
    HashIndex<QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry,long,QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_mapkey01_idxfn,true>,
    HashIndex<QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry,long,QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_mapkey0_idxfn,false>
  > QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_map;
  typedef HashIndex<QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry,long,QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_mapkey01_idxfn,true> HashIndex_QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_map_01;
  typedef HashIndex<QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry,long,QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_mapkey0_idxfn,false> HashIndex_QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_map_0;
  
  struct QUERY11_mPARTSUPP1_L3_1_entry {
    long P_PARTKEY; DOUBLE_TYPE __av; 
    explicit QUERY11_mPARTSUPP1_L3_1_entry() { /*P_PARTKEY = 0L; __av = 0.0; */ }
    explicit QUERY11_mPARTSUPP1_L3_1_entry(const long c0, const DOUBLE_TYPE c1) { P_PARTKEY = c0; __av = c1; }
    QUERY11_mPARTSUPP1_L3_1_entry(const QUERY11_mPARTSUPP1_L3_1_entry& other) : P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11_mPARTSUPP1_L3_1_entry& modify(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11_mPARTSUPP1_L3_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11_mPARTSUPP1_L3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11_mPARTSUPP1_L3_1_entry& x, const QUERY11_mPARTSUPP1_L3_1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11_mPARTSUPP1_L3_1_entry,DOUBLE_TYPE,
    HashIndex<QUERY11_mPARTSUPP1_L3_1_entry,DOUBLE_TYPE,QUERY11_mPARTSUPP1_L3_1_mapkey0_idxfn,true>
  > QUERY11_mPARTSUPP1_L3_1_map;
  typedef HashIndex<QUERY11_mPARTSUPP1_L3_1_entry,DOUBLE_TYPE,QUERY11_mPARTSUPP1_L3_1_mapkey0_idxfn,true> HashIndex_QUERY11_mPARTSUPP1_L3_1_map_0;
  
  struct QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry {
    long QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY; long P_PARTKEY; DOUBLE_TYPE __av; 
    explicit QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry() { /*QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; P_PARTKEY = 0L; __av = 0.0; */ }
    explicit QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY = c0; P_PARTKEY = c1; __av = c2; }
    QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry(const QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry& other) : QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY( other.QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY ), P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry& modify(const long c0, const long c1) { QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY = c0; P_PARTKEY = c1;  return *this; }
    FORCE_INLINE QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry& modify0(const long c0) { QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry& x, const QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry& y) {
      return x.QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY == y.QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY && x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry& x, const QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry& y) {
      return x.QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY == y.QUERY11_mPARTSUPP1_L3_1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry,DOUBLE_TYPE,
    HashIndex<QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry,DOUBLE_TYPE,QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_mapkey01_idxfn,true>,
    HashIndex<QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry,DOUBLE_TYPE,QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_mapkey0_idxfn,false>
  > QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_map;
  typedef HashIndex<QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry,DOUBLE_TYPE,QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_mapkey01_idxfn,true> HashIndex_QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_map_01;
  typedef HashIndex<QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry,DOUBLE_TYPE,QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_mapkey0_idxfn,false> HashIndex_QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const QUERY11_map& _QUERY11 = get_QUERY11();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(QUERY11), _QUERY11, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const QUERY11_map& get_QUERY11() const {
      return QUERY11;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    QUERY11_map QUERY11;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), QUERY11_mPARTSUPP1_L1_1(0.0) {
      c1 = STRING_TYPE("GERMANY");
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_NATION(const long nation_nationkey, const STRING_TYPE nation_name, const long nation_regionkey, const STRING_TYPE nation_comment) {
      NATION_entry e(nation_nationkey, nation_name, nation_regionkey, nation_comment, 1L);
      NATION.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  //++tN;
        QUERY11_mPARTSUPP1_L1_1 += (QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1.getValueOrDefault(se2.modify(supplier_nationkey)) * QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2.getValueOrDefault(se3.modify(supplier_suppkey)));
        QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1.addOrDelOnZero(se4.modify(supplier_suppkey),QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1.getValueOrDefault(se5.modify(supplier_nationkey)));
        { //slice 
          const HashIndex_QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_map_0* i1 = static_cast<HashIndex_QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_map_0*>(QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2.index[1]);
          const HASH_RES_t h1 = QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_mapkey0_idxfn::hash(se8.modify0(supplier_suppkey));
          HashIndex_QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_map_0::IdxNode* n1 = static_cast<HashIndex_QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_map_0::IdxNode*>(i1->slice(se8, h1));
          QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long p_partkey = e1->P_PARTKEY;
              long v1 = e1->__av;
              QUERY11_mPARTSUPP1_E2_1.addOrDelOnZero(se6.modify(p_partkey),(QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1.getValueOrDefault(se7.modify(supplier_nationkey)) * v1));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_mapkey0_idxfn::equals(se8, *e1)); 
          }
        }{ //slice 
          const HashIndex_QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_map_0* i2 = static_cast<HashIndex_QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_map_0*>(QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2.index[1]);
          const HASH_RES_t h2 = QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_mapkey0_idxfn::hash(se11.modify0(supplier_suppkey));
          HashIndex_QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_map_0::IdxNode* n2 = static_cast<HashIndex_QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_map_0::IdxNode*>(i2->slice(se11, h2));
          QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long p_partkey = e2->P_PARTKEY;
              DOUBLE_TYPE v2 = e2->__av;
              QUERY11_mPARTSUPP1_L3_1.addOrDelOnZero(se9.modify(p_partkey),(QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1.getValueOrDefault(se10.modify(supplier_nationkey)) * v2));
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_mapkey0_idxfn::equals(se11, *e2)); 
          }
        }QUERY11.clear();
        {  // foreach
          const HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0* i3 = static_cast<HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0*>(QUERY11_mPARTSUPP1_E2_1.index[0]);
          HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0::IdxNode* n3; 
          QUERY11_mPARTSUPP1_E2_1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long p_partkey = e3->P_PARTKEY;
                long v3 = e3->__av;
                DOUBLE_TYPE agg1 = 0.0;
                DOUBLE_TYPE l1 = QUERY11_mPARTSUPP1_L3_1.getValueOrDefault(se13.modify(p_partkey));
                DOUBLE_TYPE l2 = (QUERY11_mPARTSUPP1_L1_1 * 0.001);
                (/*if */(l1 > l2) ? agg1 += QUERY11_mPARTSUPP1_L3_1.getValueOrDefault(se14.modify(p_partkey)) : 0.0);
                QUERY11.addOrDelOnZero(se12.modify(p_partkey),((v3 != 0 ? 1L : 0L) * agg1));
              n3 = n3->nxt;
            }
          }
        }
      }
    }
    void on_delete_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  //++tN;
        QUERY11_mPARTSUPP1_L1_1 += (QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1.getValueOrDefault(se16.modify(supplier_nationkey)) * (QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2.getValueOrDefault(se17.modify(supplier_suppkey)) * -1L));
        QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1.addOrDelOnZero(se18.modify(supplier_suppkey),(QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1.getValueOrDefault(se19.modify(supplier_nationkey)) * -1L));
        { //slice 
          const HashIndex_QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_map_0* i4 = static_cast<HashIndex_QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_map_0*>(QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2.index[1]);
          const HASH_RES_t h3 = QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_mapkey0_idxfn::hash(se22.modify0(supplier_suppkey));
          HashIndex_QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_map_0::IdxNode* n4 = static_cast<HashIndex_QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_map_0::IdxNode*>(i4->slice(se22, h3));
          QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long p_partkey = e4->P_PARTKEY;
              long v4 = e4->__av;
              QUERY11_mPARTSUPP1_E2_1.addOrDelOnZero(se20.modify(p_partkey),(QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1.getValueOrDefault(se21.modify(supplier_nationkey)) * (v4 * -1L)));
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h3 == n4->hash &&  QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_mapkey0_idxfn::equals(se22, *e4)); 
          }
        }{ //slice 
          const HashIndex_QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_map_0* i5 = static_cast<HashIndex_QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_map_0*>(QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2.index[1]);
          const HASH_RES_t h4 = QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_mapkey0_idxfn::hash(se25.modify0(supplier_suppkey));
          HashIndex_QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_map_0::IdxNode* n5 = static_cast<HashIndex_QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_map_0::IdxNode*>(i5->slice(se25, h4));
          QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long p_partkey = e5->P_PARTKEY;
              DOUBLE_TYPE v5 = e5->__av;
              QUERY11_mPARTSUPP1_L3_1.addOrDelOnZero(se23.modify(p_partkey),(QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1.getValueOrDefault(se24.modify(supplier_nationkey)) * (v5 * -1L)));
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h4 == n5->hash &&  QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_mapkey0_idxfn::equals(se25, *e5)); 
          }
        }QUERY11.clear();
        {  // foreach
          const HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0* i6 = static_cast<HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0*>(QUERY11_mPARTSUPP1_E2_1.index[0]);
          HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0::IdxNode* n6; 
          QUERY11_mPARTSUPP1_E2_1_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long p_partkey = e6->P_PARTKEY;
                long v6 = e6->__av;
                DOUBLE_TYPE agg2 = 0.0;
                DOUBLE_TYPE l3 = QUERY11_mPARTSUPP1_L3_1.getValueOrDefault(se27.modify(p_partkey));
                DOUBLE_TYPE l4 = (QUERY11_mPARTSUPP1_L1_1 * 0.001);
                (/*if */(l3 > l4) ? agg2 += QUERY11_mPARTSUPP1_L3_1.getValueOrDefault(se28.modify(p_partkey)) : 0.0);
                QUERY11.addOrDelOnZero(se26.modify(p_partkey),((v6 != 0 ? 1L : 0L) * agg2));
              n6 = n6->nxt;
            }
          }
        }
      }
    }
    void on_insert_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  //++tN;
        QUERY11_mPARTSUPP1_L1_1 += (QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1.getValueOrDefault(se30.modify(partsupp_suppkey)) * (partsupp_supplycost * partsupp_availqty));
        QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2.addOrDelOnZero(se31.modify(partsupp_suppkey),(partsupp_supplycost * partsupp_availqty));
        QUERY11_mPARTSUPP1_E2_1.addOrDelOnZero(se32.modify(partsupp_partkey),QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1.getValueOrDefault(se33.modify(partsupp_suppkey)));
        QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2.addOrDelOnZero(se34.modify(partsupp_suppkey,partsupp_partkey),1L);
        QUERY11_mPARTSUPP1_L3_1.addOrDelOnZero(se35.modify(partsupp_partkey),(QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1.getValueOrDefault(se36.modify(partsupp_suppkey)) * (partsupp_supplycost * partsupp_availqty)));
        QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2.addOrDelOnZero(se37.modify(partsupp_suppkey,partsupp_partkey),(partsupp_supplycost * partsupp_availqty));
        QUERY11.clear();
        {  // foreach
          const HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0* i7 = static_cast<HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0*>(QUERY11_mPARTSUPP1_E2_1.index[0]);
          HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0::IdxNode* n7; 
          QUERY11_mPARTSUPP1_E2_1_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long p_partkey = e7->P_PARTKEY;
                long v7 = e7->__av;
                DOUBLE_TYPE agg3 = 0.0;
                DOUBLE_TYPE l5 = QUERY11_mPARTSUPP1_L3_1.getValueOrDefault(se39.modify(p_partkey));
                DOUBLE_TYPE l6 = (QUERY11_mPARTSUPP1_L1_1 * 0.001);
                (/*if */(l5 > l6) ? agg3 += QUERY11_mPARTSUPP1_L3_1.getValueOrDefault(se40.modify(p_partkey)) : 0.0);
                QUERY11.addOrDelOnZero(se38.modify(p_partkey),((v7 != 0 ? 1L : 0L) * agg3));
              n7 = n7->nxt;
            }
          }
        }
      }
    }
    void on_delete_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  //++tN;
        QUERY11_mPARTSUPP1_L1_1 += (QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1.getValueOrDefault(se42.modify(partsupp_suppkey)) * (-1L * (partsupp_supplycost * partsupp_availqty)));
        QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2.addOrDelOnZero(se43.modify(partsupp_suppkey),(-1L * (partsupp_supplycost * partsupp_availqty)));
        QUERY11_mPARTSUPP1_E2_1.addOrDelOnZero(se44.modify(partsupp_partkey),(QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1.getValueOrDefault(se45.modify(partsupp_suppkey)) * -1L));
        QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2.addOrDelOnZero(se46.modify(partsupp_suppkey,partsupp_partkey),-1L);
        QUERY11_mPARTSUPP1_L3_1.addOrDelOnZero(se47.modify(partsupp_partkey),(QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1.getValueOrDefault(se48.modify(partsupp_suppkey)) * (-1L * (partsupp_supplycost * partsupp_availqty))));
        QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2.addOrDelOnZero(se49.modify(partsupp_suppkey,partsupp_partkey),(-1L * (partsupp_supplycost * partsupp_availqty)));
        QUERY11.clear();
        {  // foreach
          const HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0* i8 = static_cast<HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0*>(QUERY11_mPARTSUPP1_E2_1.index[0]);
          HashIndex_QUERY11_mPARTSUPP1_E2_1_map_0::IdxNode* n8; 
          QUERY11_mPARTSUPP1_E2_1_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long p_partkey = e8->P_PARTKEY;
                long v8 = e8->__av;
                DOUBLE_TYPE agg4 = 0.0;
                DOUBLE_TYPE l7 = QUERY11_mPARTSUPP1_L3_1.getValueOrDefault(se51.modify(p_partkey));
                DOUBLE_TYPE l8 = (QUERY11_mPARTSUPP1_L1_1 * 0.001);
                (/*if */(l7 > l8) ? agg4 += QUERY11_mPARTSUPP1_L3_1.getValueOrDefault(se52.modify(p_partkey)) : 0.0);
                QUERY11.addOrDelOnZero(se50.modify(p_partkey),((v8 != 0 ? 1L : 0L) * agg4));
              n8 = n8->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  //
        QUERY11_mPARTSUPP1_L1_1 = 0.0;
        QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1.clear();
        STRING_TYPE l9 = c1;
        { //slice 
          const HashIndex_NATION_map_1* i9 = static_cast<HashIndex_NATION_map_1*>(NATION.index[1]);
          const HASH_RES_t h5 = NATION_mapkey1_idxfn::hash(se55.modify1(l9));
          HashIndex_NATION_map_1::IdxNode* n9 = static_cast<HashIndex_NATION_map_1::IdxNode*>(i9->slice(se55, h5));
          NATION_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              long query11_mpartsupp1_l1_1_msuppliersupplier_nationkey = e9->NATION_NATIONKEY;
              long n_regionkey = e9->NATION_REGIONKEY;
              STRING_TYPE n_comment = e9->NATION_COMMENT;
              long v9 = e9->__av;
              QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1.addOrDelOnZero(se54.modify(query11_mpartsupp1_l1_1_msuppliersupplier_nationkey),v9);
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h5 == n9->hash &&  NATION_mapkey1_idxfn::equals(se55, *e9)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry se2;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry se3;
    QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry se4;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry se5;
    QUERY11_mPARTSUPP1_E2_1_entry se6;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry se7;
    QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry se8;
    QUERY11_mPARTSUPP1_L3_1_entry se9;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry se10;
    QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry se11;
    QUERY11_entry se12;
    QUERY11_mPARTSUPP1_L3_1_entry se13;
    QUERY11_mPARTSUPP1_L3_1_entry se14;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry se16;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry se17;
    QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry se18;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry se19;
    QUERY11_mPARTSUPP1_E2_1_entry se20;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry se21;
    QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry se22;
    QUERY11_mPARTSUPP1_L3_1_entry se23;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry se24;
    QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry se25;
    QUERY11_entry se26;
    QUERY11_mPARTSUPP1_L3_1_entry se27;
    QUERY11_mPARTSUPP1_L3_1_entry se28;
    QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry se30;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry se31;
    QUERY11_mPARTSUPP1_E2_1_entry se32;
    QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry se33;
    QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry se34;
    QUERY11_mPARTSUPP1_L3_1_entry se35;
    QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry se36;
    QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry se37;
    QUERY11_entry se38;
    QUERY11_mPARTSUPP1_L3_1_entry se39;
    QUERY11_mPARTSUPP1_L3_1_entry se40;
    QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry se42;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_entry se43;
    QUERY11_mPARTSUPP1_E2_1_entry se44;
    QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry se45;
    QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_entry se46;
    QUERY11_mPARTSUPP1_L3_1_entry se47;
    QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_entry se48;
    QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_entry se49;
    QUERY11_entry se50;
    QUERY11_mPARTSUPP1_L3_1_entry se51;
    QUERY11_mPARTSUPP1_L3_1_entry se52;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_entry se54;
    NATION_entry se55;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    DOUBLE_TYPE QUERY11_mPARTSUPP1_L1_1;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1_map QUERY11_mPARTSUPP1_L1_1_mSUPPLIER1;
    QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2_map QUERY11_mPARTSUPP1_L1_1_mSUPPLIER2;
    QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1_map QUERY11_mPARTSUPP1_L1_1_mPARTSUPP1;
    QUERY11_mPARTSUPP1_E2_1_map QUERY11_mPARTSUPP1_E2_1;
    QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2_map QUERY11_mPARTSUPP1_E2_1_mSUPPLIER2;
    QUERY11_mPARTSUPP1_L3_1_map QUERY11_mPARTSUPP1_L3_1;
    QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2_map QUERY11_mPARTSUPP1_L3_1_mSUPPLIER2;
    
    /*const static*/ STRING_TYPE c1;
  
  };

}
