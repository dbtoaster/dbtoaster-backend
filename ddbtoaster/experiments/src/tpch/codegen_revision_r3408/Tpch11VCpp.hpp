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
  
  struct QUERY11PARTSUPP1_L1_1SUPPLIER1_entry {
    long QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_NATIONKEY; long __av; 
    explicit QUERY11PARTSUPP1_L1_1SUPPLIER1_entry() { /*QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_NATIONKEY = 0L; __av = 0L; */ }
    explicit QUERY11PARTSUPP1_L1_1SUPPLIER1_entry(const long c0, const long c1) { QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_NATIONKEY = c0; __av = c1; }
    QUERY11PARTSUPP1_L1_1SUPPLIER1_entry(const QUERY11PARTSUPP1_L1_1SUPPLIER1_entry& other) : QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_NATIONKEY( other.QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_L1_1SUPPLIER1_entry& modify(const long c0) { QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_L1_1SUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L1_1SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L1_1SUPPLIER1_entry& x, const QUERY11PARTSUPP1_L1_1SUPPLIER1_entry& y) {
      return x.QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_NATIONKEY == y.QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_L1_1SUPPLIER1_entry,long,
    HashIndex<QUERY11PARTSUPP1_L1_1SUPPLIER1_entry,long,QUERY11PARTSUPP1_L1_1SUPPLIER1_mapkey0_idxfn,true>
  > QUERY11PARTSUPP1_L1_1SUPPLIER1_map;
  typedef HashIndex<QUERY11PARTSUPP1_L1_1SUPPLIER1_entry,long,QUERY11PARTSUPP1_L1_1SUPPLIER1_mapkey0_idxfn,true> HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_map_0;
  
  struct QUERY11PARTSUPP1_L1_1SUPPLIER2_entry {
    long QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit QUERY11PARTSUPP1_L1_1SUPPLIER2_entry() { /*QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit QUERY11PARTSUPP1_L1_1SUPPLIER2_entry(const long c0, const DOUBLE_TYPE c1) { QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_SUPPKEY = c0; __av = c1; }
    QUERY11PARTSUPP1_L1_1SUPPLIER2_entry(const QUERY11PARTSUPP1_L1_1SUPPLIER2_entry& other) : QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_SUPPKEY( other.QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_L1_1SUPPLIER2_entry& modify(const long c0) { QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_L1_1SUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L1_1SUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L1_1SUPPLIER2_entry& x, const QUERY11PARTSUPP1_L1_1SUPPLIER2_entry& y) {
      return x.QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_SUPPKEY == y.QUERY11PARTSUPP1_L1_1SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_L1_1SUPPLIER2_entry,DOUBLE_TYPE,
    HashIndex<QUERY11PARTSUPP1_L1_1SUPPLIER2_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L1_1SUPPLIER2_mapkey0_idxfn,true>
  > QUERY11PARTSUPP1_L1_1SUPPLIER2_map;
  typedef HashIndex<QUERY11PARTSUPP1_L1_1SUPPLIER2_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L1_1SUPPLIER2_mapkey0_idxfn,true> HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER2_map_0;
  
  struct QUERY11PARTSUPP1_L1_1PARTSUPP1_entry {
    long QUERY11PARTSUPP1_L1_1PARTSUPPPARTSUPP_SUPPKEY; long __av; 
    explicit QUERY11PARTSUPP1_L1_1PARTSUPP1_entry() { /*QUERY11PARTSUPP1_L1_1PARTSUPPPARTSUPP_SUPPKEY = 0L; __av = 0L; */ }
    explicit QUERY11PARTSUPP1_L1_1PARTSUPP1_entry(const long c0, const long c1) { QUERY11PARTSUPP1_L1_1PARTSUPPPARTSUPP_SUPPKEY = c0; __av = c1; }
    QUERY11PARTSUPP1_L1_1PARTSUPP1_entry(const QUERY11PARTSUPP1_L1_1PARTSUPP1_entry& other) : QUERY11PARTSUPP1_L1_1PARTSUPPPARTSUPP_SUPPKEY( other.QUERY11PARTSUPP1_L1_1PARTSUPPPARTSUPP_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_L1_1PARTSUPP1_entry& modify(const long c0) { QUERY11PARTSUPP1_L1_1PARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY11PARTSUPP1_L1_1PARTSUPPPARTSUPP_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_L1_1PARTSUPP1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L1_1PARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11PARTSUPP1_L1_1PARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L1_1PARTSUPP1_entry& x, const QUERY11PARTSUPP1_L1_1PARTSUPP1_entry& y) {
      return x.QUERY11PARTSUPP1_L1_1PARTSUPPPARTSUPP_SUPPKEY == y.QUERY11PARTSUPP1_L1_1PARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_L1_1PARTSUPP1_entry,long,
    HashIndex<QUERY11PARTSUPP1_L1_1PARTSUPP1_entry,long,QUERY11PARTSUPP1_L1_1PARTSUPP1_mapkey0_idxfn,true>
  > QUERY11PARTSUPP1_L1_1PARTSUPP1_map;
  typedef HashIndex<QUERY11PARTSUPP1_L1_1PARTSUPP1_entry,long,QUERY11PARTSUPP1_L1_1PARTSUPP1_mapkey0_idxfn,true> HashIndex_QUERY11PARTSUPP1_L1_1PARTSUPP1_map_0;
  
  struct QUERY11PARTSUPP1_E2_1_entry {
    long P_PARTKEY; long __av; 
    explicit QUERY11PARTSUPP1_E2_1_entry() { /*P_PARTKEY = 0L; __av = 0L; */ }
    explicit QUERY11PARTSUPP1_E2_1_entry(const long c0, const long c1) { P_PARTKEY = c0; __av = c1; }
    QUERY11PARTSUPP1_E2_1_entry(const QUERY11PARTSUPP1_E2_1_entry& other) : P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_E2_1_entry& modify(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_E2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_E2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_E2_1_entry& x, const QUERY11PARTSUPP1_E2_1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_E2_1_entry,long,
    HashIndex<QUERY11PARTSUPP1_E2_1_entry,long,QUERY11PARTSUPP1_E2_1_mapkey0_idxfn,true>
  > QUERY11PARTSUPP1_E2_1_map;
  typedef HashIndex<QUERY11PARTSUPP1_E2_1_entry,long,QUERY11PARTSUPP1_E2_1_mapkey0_idxfn,true> HashIndex_QUERY11PARTSUPP1_E2_1_map_0;
  
  struct QUERY11PARTSUPP1_E2_1SUPPLIER2_entry {
    long QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY; long P_PARTKEY; long __av; 
    explicit QUERY11PARTSUPP1_E2_1SUPPLIER2_entry() { /*QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY = 0L; P_PARTKEY = 0L; __av = 0L; */ }
    explicit QUERY11PARTSUPP1_E2_1SUPPLIER2_entry(const long c0, const long c1, const long c2) { QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY = c0; P_PARTKEY = c1; __av = c2; }
    QUERY11PARTSUPP1_E2_1SUPPLIER2_entry(const QUERY11PARTSUPP1_E2_1SUPPLIER2_entry& other) : QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY( other.QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY ), P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_E2_1SUPPLIER2_entry& modify(const long c0, const long c1) { QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY = c0; P_PARTKEY = c1;  return *this; }
    FORCE_INLINE QUERY11PARTSUPP1_E2_1SUPPLIER2_entry& modify0(const long c0) { QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_E2_1SUPPLIER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_E2_1SUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_E2_1SUPPLIER2_entry& x, const QUERY11PARTSUPP1_E2_1SUPPLIER2_entry& y) {
      return x.QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY == y.QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY && x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct QUERY11PARTSUPP1_E2_1SUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_E2_1SUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_E2_1SUPPLIER2_entry& x, const QUERY11PARTSUPP1_E2_1SUPPLIER2_entry& y) {
      return x.QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY == y.QUERY11PARTSUPP1_E2_1SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_E2_1SUPPLIER2_entry,long,
    HashIndex<QUERY11PARTSUPP1_E2_1SUPPLIER2_entry,long,QUERY11PARTSUPP1_E2_1SUPPLIER2_mapkey01_idxfn,true>,
    HashIndex<QUERY11PARTSUPP1_E2_1SUPPLIER2_entry,long,QUERY11PARTSUPP1_E2_1SUPPLIER2_mapkey0_idxfn,false>
  > QUERY11PARTSUPP1_E2_1SUPPLIER2_map;
  typedef HashIndex<QUERY11PARTSUPP1_E2_1SUPPLIER2_entry,long,QUERY11PARTSUPP1_E2_1SUPPLIER2_mapkey01_idxfn,true> HashIndex_QUERY11PARTSUPP1_E2_1SUPPLIER2_map_01;
  typedef HashIndex<QUERY11PARTSUPP1_E2_1SUPPLIER2_entry,long,QUERY11PARTSUPP1_E2_1SUPPLIER2_mapkey0_idxfn,false> HashIndex_QUERY11PARTSUPP1_E2_1SUPPLIER2_map_0;
  
  struct QUERY11PARTSUPP1_L3_1_entry {
    long P_PARTKEY; DOUBLE_TYPE __av; 
    explicit QUERY11PARTSUPP1_L3_1_entry() { /*P_PARTKEY = 0L; __av = 0.0; */ }
    explicit QUERY11PARTSUPP1_L3_1_entry(const long c0, const DOUBLE_TYPE c1) { P_PARTKEY = c0; __av = c1; }
    QUERY11PARTSUPP1_L3_1_entry(const QUERY11PARTSUPP1_L3_1_entry& other) : P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_L3_1_entry& modify(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_L3_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L3_1_entry& x, const QUERY11PARTSUPP1_L3_1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_L3_1_entry,DOUBLE_TYPE,
    HashIndex<QUERY11PARTSUPP1_L3_1_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L3_1_mapkey0_idxfn,true>
  > QUERY11PARTSUPP1_L3_1_map;
  typedef HashIndex<QUERY11PARTSUPP1_L3_1_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L3_1_mapkey0_idxfn,true> HashIndex_QUERY11PARTSUPP1_L3_1_map_0;
  
  struct QUERY11PARTSUPP1_L3_1SUPPLIER2_entry {
    long QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY; long P_PARTKEY; DOUBLE_TYPE __av; 
    explicit QUERY11PARTSUPP1_L3_1SUPPLIER2_entry() { /*QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY = 0L; P_PARTKEY = 0L; __av = 0.0; */ }
    explicit QUERY11PARTSUPP1_L3_1SUPPLIER2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY = c0; P_PARTKEY = c1; __av = c2; }
    QUERY11PARTSUPP1_L3_1SUPPLIER2_entry(const QUERY11PARTSUPP1_L3_1SUPPLIER2_entry& other) : QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY( other.QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY ), P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_L3_1SUPPLIER2_entry& modify(const long c0, const long c1) { QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY = c0; P_PARTKEY = c1;  return *this; }
    FORCE_INLINE QUERY11PARTSUPP1_L3_1SUPPLIER2_entry& modify0(const long c0) { QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_L3_1SUPPLIER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L3_1SUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L3_1SUPPLIER2_entry& x, const QUERY11PARTSUPP1_L3_1SUPPLIER2_entry& y) {
      return x.QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY == y.QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY && x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct QUERY11PARTSUPP1_L3_1SUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L3_1SUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L3_1SUPPLIER2_entry& x, const QUERY11PARTSUPP1_L3_1SUPPLIER2_entry& y) {
      return x.QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY == y.QUERY11PARTSUPP1_L3_1SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_L3_1SUPPLIER2_entry,DOUBLE_TYPE,
    HashIndex<QUERY11PARTSUPP1_L3_1SUPPLIER2_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L3_1SUPPLIER2_mapkey01_idxfn,true>,
    HashIndex<QUERY11PARTSUPP1_L3_1SUPPLIER2_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L3_1SUPPLIER2_mapkey0_idxfn,false>
  > QUERY11PARTSUPP1_L3_1SUPPLIER2_map;
  typedef HashIndex<QUERY11PARTSUPP1_L3_1SUPPLIER2_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L3_1SUPPLIER2_mapkey01_idxfn,true> HashIndex_QUERY11PARTSUPP1_L3_1SUPPLIER2_map_01;
  typedef HashIndex<QUERY11PARTSUPP1_L3_1SUPPLIER2_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L3_1SUPPLIER2_mapkey0_idxfn,false> HashIndex_QUERY11PARTSUPP1_L3_1SUPPLIER2_map_0;
  
  
  
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
    data_t(): tlq_t(), QUERY11PARTSUPP1_L1_1(0.0) {
      c1 = STRING_TYPE("GERMANY");
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_NATION(const long nation_nationkey, const STRING_TYPE nation_name, const long nation_regionkey, const STRING_TYPE nation_comment) {
      NATION_entry e(nation_nationkey, nation_name, nation_regionkey, nation_comment, 1L);
      NATION.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        QUERY11PARTSUPP1_L1_1 += (QUERY11PARTSUPP1_L1_1SUPPLIER1.getValueOrDefault(se2.modify(supplier_nationkey)) * QUERY11PARTSUPP1_L1_1SUPPLIER2.getValueOrDefault(se3.modify(supplier_suppkey)));
        QUERY11PARTSUPP1_L1_1PARTSUPP1.addOrDelOnZero(se4.modify(supplier_suppkey),QUERY11PARTSUPP1_L1_1SUPPLIER1.getValueOrDefault(se5.modify(supplier_nationkey)));
        { //slice 
          const HashIndex_QUERY11PARTSUPP1_E2_1SUPPLIER2_map_0* i1 = static_cast<HashIndex_QUERY11PARTSUPP1_E2_1SUPPLIER2_map_0*>(QUERY11PARTSUPP1_E2_1SUPPLIER2.index[1]);
          const HASH_RES_t h1 = QUERY11PARTSUPP1_E2_1SUPPLIER2_mapkey0_idxfn::hash(se8.modify0(supplier_suppkey));
          HashIndex_QUERY11PARTSUPP1_E2_1SUPPLIER2_map_0::IdxNode* n1 = static_cast<HashIndex_QUERY11PARTSUPP1_E2_1SUPPLIER2_map_0::IdxNode*>(i1->slice(se8, h1));
          QUERY11PARTSUPP1_E2_1SUPPLIER2_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long p_partkey = e1->P_PARTKEY;
              long v1 = e1->__av;
              QUERY11PARTSUPP1_E2_1.addOrDelOnZero(se6.modify(p_partkey),(QUERY11PARTSUPP1_L1_1SUPPLIER1.getValueOrDefault(se7.modify(supplier_nationkey)) * v1));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  QUERY11PARTSUPP1_E2_1SUPPLIER2_mapkey0_idxfn::equals(se8, *e1)); 
          }
        }{ //slice 
          const HashIndex_QUERY11PARTSUPP1_L3_1SUPPLIER2_map_0* i2 = static_cast<HashIndex_QUERY11PARTSUPP1_L3_1SUPPLIER2_map_0*>(QUERY11PARTSUPP1_L3_1SUPPLIER2.index[1]);
          const HASH_RES_t h2 = QUERY11PARTSUPP1_L3_1SUPPLIER2_mapkey0_idxfn::hash(se11.modify0(supplier_suppkey));
          HashIndex_QUERY11PARTSUPP1_L3_1SUPPLIER2_map_0::IdxNode* n2 = static_cast<HashIndex_QUERY11PARTSUPP1_L3_1SUPPLIER2_map_0::IdxNode*>(i2->slice(se11, h2));
          QUERY11PARTSUPP1_L3_1SUPPLIER2_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long p_partkey = e2->P_PARTKEY;
              DOUBLE_TYPE v2 = e2->__av;
              QUERY11PARTSUPP1_L3_1.addOrDelOnZero(se9.modify(p_partkey),(QUERY11PARTSUPP1_L1_1SUPPLIER1.getValueOrDefault(se10.modify(supplier_nationkey)) * v2));
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  QUERY11PARTSUPP1_L3_1SUPPLIER2_mapkey0_idxfn::equals(se11, *e2)); 
          }
        }QUERY11.clear();
        {  // foreach
          const HashIndex_QUERY11PARTSUPP1_E2_1_map_0* i3 = static_cast<HashIndex_QUERY11PARTSUPP1_E2_1_map_0*>(QUERY11PARTSUPP1_E2_1.index[0]);
          HashIndex_QUERY11PARTSUPP1_E2_1_map_0::IdxNode* n3; 
          QUERY11PARTSUPP1_E2_1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long p_partkey = e3->P_PARTKEY;
                long v3 = e3->__av;
                DOUBLE_TYPE agg1 = 0.0;
                DOUBLE_TYPE l1 = QUERY11PARTSUPP1_L3_1.getValueOrDefault(se13.modify(p_partkey));
                DOUBLE_TYPE l2 = (QUERY11PARTSUPP1_L1_1 * 0.001);
                (/*if */(l1 > l2) ? agg1 += QUERY11PARTSUPP1_L3_1.getValueOrDefault(se14.modify(p_partkey)) : 0.0);
                QUERY11.addOrDelOnZero(se12.modify(p_partkey),((v3 != 0 ? 1L : 0L) * agg1));
              n3 = n3->nxt;
            }
          }
        }
      }
    }
    void on_insert_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        QUERY11PARTSUPP1_L1_1 += (QUERY11PARTSUPP1_L1_1PARTSUPP1.getValueOrDefault(se16.modify(partsupp_suppkey)) * (partsupp_supplycost * partsupp_availqty));
        QUERY11PARTSUPP1_L1_1SUPPLIER2.addOrDelOnZero(se17.modify(partsupp_suppkey),(partsupp_supplycost * partsupp_availqty));
        QUERY11PARTSUPP1_E2_1.addOrDelOnZero(se18.modify(partsupp_partkey),QUERY11PARTSUPP1_L1_1PARTSUPP1.getValueOrDefault(se19.modify(partsupp_suppkey)));
        QUERY11PARTSUPP1_E2_1SUPPLIER2.addOrDelOnZero(se20.modify(partsupp_suppkey,partsupp_partkey),1L);
        QUERY11PARTSUPP1_L3_1.addOrDelOnZero(se21.modify(partsupp_partkey),(QUERY11PARTSUPP1_L1_1PARTSUPP1.getValueOrDefault(se22.modify(partsupp_suppkey)) * (partsupp_supplycost * partsupp_availqty)));
        QUERY11PARTSUPP1_L3_1SUPPLIER2.addOrDelOnZero(se23.modify(partsupp_suppkey,partsupp_partkey),(partsupp_supplycost * partsupp_availqty));
        QUERY11.clear();
        {  // foreach
          const HashIndex_QUERY11PARTSUPP1_E2_1_map_0* i4 = static_cast<HashIndex_QUERY11PARTSUPP1_E2_1_map_0*>(QUERY11PARTSUPP1_E2_1.index[0]);
          HashIndex_QUERY11PARTSUPP1_E2_1_map_0::IdxNode* n4; 
          QUERY11PARTSUPP1_E2_1_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long p_partkey = e4->P_PARTKEY;
                long v4 = e4->__av;
                DOUBLE_TYPE agg2 = 0.0;
                DOUBLE_TYPE l3 = QUERY11PARTSUPP1_L3_1.getValueOrDefault(se25.modify(p_partkey));
                DOUBLE_TYPE l4 = (QUERY11PARTSUPP1_L1_1 * 0.001);
                (/*if */(l3 > l4) ? agg2 += QUERY11PARTSUPP1_L3_1.getValueOrDefault(se26.modify(p_partkey)) : 0.0);
                QUERY11.addOrDelOnZero(se24.modify(p_partkey),((v4 != 0 ? 1L : 0L) * agg2));
              n4 = n4->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        QUERY11PARTSUPP1_L1_1 = 0.0;
        QUERY11PARTSUPP1_L1_1SUPPLIER1.clear();
        STRING_TYPE l5 = c1;
        { //slice 
          const HashIndex_NATION_map_1* i5 = static_cast<HashIndex_NATION_map_1*>(NATION.index[1]);
          const HASH_RES_t h3 = NATION_mapkey1_idxfn::hash(se29.modify1(l5));
          HashIndex_NATION_map_1::IdxNode* n5 = static_cast<HashIndex_NATION_map_1::IdxNode*>(i5->slice(se29, h3));
          NATION_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long query11partsupp1_l1_1suppliersupplier_nationkey = e5->NATION_NATIONKEY;
              long n_regionkey = e5->NATION_REGIONKEY;
              STRING_TYPE n_comment = e5->NATION_COMMENT;
              long v5 = e5->__av;
              QUERY11PARTSUPP1_L1_1SUPPLIER1.addOrDelOnZero(se28.modify(query11partsupp1_l1_1suppliersupplier_nationkey),v5);
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h3 == n5->hash &&  NATION_mapkey1_idxfn::equals(se29, *e5)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    QUERY11PARTSUPP1_L1_1SUPPLIER1_entry se2;
    QUERY11PARTSUPP1_L1_1SUPPLIER2_entry se3;
    QUERY11PARTSUPP1_L1_1PARTSUPP1_entry se4;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_entry se5;
    QUERY11PARTSUPP1_E2_1_entry se6;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_entry se7;
    QUERY11PARTSUPP1_E2_1SUPPLIER2_entry se8;
    QUERY11PARTSUPP1_L3_1_entry se9;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_entry se10;
    QUERY11PARTSUPP1_L3_1SUPPLIER2_entry se11;
    QUERY11_entry se12;
    QUERY11PARTSUPP1_L3_1_entry se13;
    QUERY11PARTSUPP1_L3_1_entry se14;
    QUERY11PARTSUPP1_L1_1PARTSUPP1_entry se16;
    QUERY11PARTSUPP1_L1_1SUPPLIER2_entry se17;
    QUERY11PARTSUPP1_E2_1_entry se18;
    QUERY11PARTSUPP1_L1_1PARTSUPP1_entry se19;
    QUERY11PARTSUPP1_E2_1SUPPLIER2_entry se20;
    QUERY11PARTSUPP1_L3_1_entry se21;
    QUERY11PARTSUPP1_L1_1PARTSUPP1_entry se22;
    QUERY11PARTSUPP1_L3_1SUPPLIER2_entry se23;
    QUERY11_entry se24;
    QUERY11PARTSUPP1_L3_1_entry se25;
    QUERY11PARTSUPP1_L3_1_entry se26;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_entry se28;
    NATION_entry se29;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    DOUBLE_TYPE QUERY11PARTSUPP1_L1_1;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_map QUERY11PARTSUPP1_L1_1SUPPLIER1;
    QUERY11PARTSUPP1_L1_1SUPPLIER2_map QUERY11PARTSUPP1_L1_1SUPPLIER2;
    QUERY11PARTSUPP1_L1_1PARTSUPP1_map QUERY11PARTSUPP1_L1_1PARTSUPP1;
    QUERY11PARTSUPP1_E2_1_map QUERY11PARTSUPP1_E2_1;
    QUERY11PARTSUPP1_E2_1SUPPLIER2_map QUERY11PARTSUPP1_E2_1SUPPLIER2;
    QUERY11PARTSUPP1_L3_1_map QUERY11PARTSUPP1_L3_1;
    QUERY11PARTSUPP1_L3_1SUPPLIER2_map QUERY11PARTSUPP1_L3_1SUPPLIER2;
    
    /*const static*/ STRING_TYPE c1;
  
  };

}
