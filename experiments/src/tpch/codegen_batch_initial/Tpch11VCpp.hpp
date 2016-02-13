#include <sys/time.h>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "hashmap.hpp"
#include "serialization.hpp"
#include "tpch.hpp"

#define ELEM_SEPARATOR "\n\t\t\t"

namespace dbtoaster {
  
  /* Definitions of auxiliary maps for storing materialized views. */
  struct DELTA_SUPPLIER_entry {
    long supplier_suppkey; STRING_TYPE supplier_name; STRING_TYPE supplier_address; long supplier_nationkey; STRING_TYPE supplier_phone; DOUBLE_TYPE supplier_acctbal; STRING_TYPE supplier_comment; long __av; 
    explicit DELTA_SUPPLIER_entry() { /*supplier_suppkey = 0L; supplier_name = ""; supplier_address = ""; supplier_nationkey = 0L; supplier_phone = ""; supplier_acctbal = 0.0; supplier_comment = ""; __av = 0L; */ }
    explicit DELTA_SUPPLIER_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const long c7) { supplier_suppkey = c0; supplier_name = c1; supplier_address = c2; supplier_nationkey = c3; supplier_phone = c4; supplier_acctbal = c5; supplier_comment = c6; __av = c7; }
    DELTA_SUPPLIER_entry(const DELTA_SUPPLIER_entry& other) : supplier_suppkey( other.supplier_suppkey ), supplier_name( other.supplier_name ), supplier_address( other.supplier_address ), supplier_nationkey( other.supplier_nationkey ), supplier_phone( other.supplier_phone ), supplier_acctbal( other.supplier_acctbal ), supplier_comment( other.supplier_comment ), __av( other.__av ) {}
    FORCE_INLINE DELTA_SUPPLIER_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6) { supplier_suppkey = c0; supplier_name = c1; supplier_address = c2; supplier_nationkey = c3; supplier_phone = c4; supplier_acctbal = c5; supplier_comment = c6;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_address);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_nationkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_phone);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_acctbal);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_SUPPLIER_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_SUPPLIER_entry& e) {
      size_t h = 0;
      hash_combine(h, e.supplier_suppkey);
      hash_combine(h, e.supplier_name);
      hash_combine(h, e.supplier_address);
      hash_combine(h, e.supplier_nationkey);
      hash_combine(h, e.supplier_phone);
      hash_combine(h, e.supplier_acctbal);
      hash_combine(h, e.supplier_comment);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_SUPPLIER_entry& x, const DELTA_SUPPLIER_entry& y) {
      return x.supplier_suppkey == y.supplier_suppkey && x.supplier_name == y.supplier_name && x.supplier_address == y.supplier_address && x.supplier_nationkey == y.supplier_nationkey && x.supplier_phone == y.supplier_phone && x.supplier_acctbal == y.supplier_acctbal && x.supplier_comment == y.supplier_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_SUPPLIER_entry,long,
    HashIndex<DELTA_SUPPLIER_entry,long,DELTA_SUPPLIER_mapkey0123456_idxfn,true>
  > DELTA_SUPPLIER_map;
  typedef HashIndex<DELTA_SUPPLIER_entry,long,DELTA_SUPPLIER_mapkey0123456_idxfn,true> HashIndex_DELTA_SUPPLIER_map_0123456;
  
  struct DELTA_PARTSUPP_entry {
    long partsupp_partkey; long partsupp_suppkey; long partsupp_availqty; DOUBLE_TYPE partsupp_supplycost; STRING_TYPE partsupp_comment; long __av; 
    explicit DELTA_PARTSUPP_entry() { /*partsupp_partkey = 0L; partsupp_suppkey = 0L; partsupp_availqty = 0L; partsupp_supplycost = 0.0; partsupp_comment = ""; __av = 0L; */ }
    explicit DELTA_PARTSUPP_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const long c5) { partsupp_partkey = c0; partsupp_suppkey = c1; partsupp_availqty = c2; partsupp_supplycost = c3; partsupp_comment = c4; __av = c5; }
    DELTA_PARTSUPP_entry(const DELTA_PARTSUPP_entry& other) : partsupp_partkey( other.partsupp_partkey ), partsupp_suppkey( other.partsupp_suppkey ), partsupp_availqty( other.partsupp_availqty ), partsupp_supplycost( other.partsupp_supplycost ), partsupp_comment( other.partsupp_comment ), __av( other.__av ) {}
    FORCE_INLINE DELTA_PARTSUPP_entry& modify(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4) { partsupp_partkey = c0; partsupp_suppkey = c1; partsupp_availqty = c2; partsupp_supplycost = c3; partsupp_comment = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partsupp_partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partsupp_suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partsupp_availqty);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partsupp_supplycost);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partsupp_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_PARTSUPP_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_PARTSUPP_entry& e) {
      size_t h = 0;
      hash_combine(h, e.partsupp_partkey);
      hash_combine(h, e.partsupp_suppkey);
      hash_combine(h, e.partsupp_availqty);
      hash_combine(h, e.partsupp_supplycost);
      hash_combine(h, e.partsupp_comment);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_PARTSUPP_entry& x, const DELTA_PARTSUPP_entry& y) {
      return x.partsupp_partkey == y.partsupp_partkey && x.partsupp_suppkey == y.partsupp_suppkey && x.partsupp_availqty == y.partsupp_availqty && x.partsupp_supplycost == y.partsupp_supplycost && x.partsupp_comment == y.partsupp_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_PARTSUPP_entry,long,
    HashIndex<DELTA_PARTSUPP_entry,long,DELTA_PARTSUPP_mapkey01234_idxfn,true>
  > DELTA_PARTSUPP_map;
  typedef HashIndex<DELTA_PARTSUPP_entry,long,DELTA_PARTSUPP_mapkey01234_idxfn,true> HashIndex_DELTA_PARTSUPP_map_01234;
  
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
  
  struct QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry {
    long PS_SUPPKEY; long S_NATIONKEY; long __av; 
    explicit QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry() { /*PS_SUPPKEY = 0L; S_NATIONKEY = 0L; __av = 0L; */ }
    explicit QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry(const long c0, const long c1, const long c2) { PS_SUPPKEY = c0; S_NATIONKEY = c1; __av = c2; }
    QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry(const QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry& modify(const long c0, const long c1) { PS_SUPPKEY = c0; S_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry& x, const QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry,long,
    HashIndex<QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry,long,QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_mapkey01_idxfn,true>
  > QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map;
  typedef HashIndex<QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry,long,QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_mapkey01_idxfn,true> HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01;
  
  struct QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry {
    long S_NATIONKEY; long __av; 
    explicit QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry() { /*S_NATIONKEY = 0L; __av = 0L; */ }
    explicit QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry(const long c0, const long c1) { S_NATIONKEY = c0; __av = c1; }
    QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry(const QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry& other) : S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry& modify(const long c0) { S_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry& x, const QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry,long,
    HashIndex<QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry,long,QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_mapkey0_idxfn,true>
  > QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_map;
  typedef HashIndex<QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry,long,QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_mapkey0_idxfn,true> HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_map_0;
  
  struct QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry {
    long PS_SUPPKEY; DOUBLE_TYPE __av; 
    explicit QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry() { /*PS_SUPPKEY = 0L; __av = 0.0; */ }
    explicit QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry(const long c0, const DOUBLE_TYPE c1) { PS_SUPPKEY = c0; __av = c1; }
    QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry(const QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry& modify(const long c0) { PS_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry& x, const QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,
    HashIndex<QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_mapkey0_idxfn,true>
  > QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_map;
  typedef HashIndex<QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_mapkey0_idxfn,true> HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_map_0;
  
  struct QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry {
    long PS_SUPPKEY; DOUBLE_TYPE __av; 
    explicit QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry() { /*PS_SUPPKEY = 0L; __av = 0.0; */ }
    explicit QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry(const long c0, const DOUBLE_TYPE c1) { PS_SUPPKEY = c0; __av = c1; }
    QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry(const QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry& modify(const long c0) { PS_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry& x, const QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_mapkey0_idxfn,true>
  > QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_map;
  typedef HashIndex<QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_mapkey0_idxfn,true> HashIndex_QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_map_0;
  
  struct QUERY11PARTSUPP1_L1_1PARTSUPP1_entry {
    long PS_SUPPKEY; long __av; 
    explicit QUERY11PARTSUPP1_L1_1PARTSUPP1_entry() { /*PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit QUERY11PARTSUPP1_L1_1PARTSUPP1_entry(const long c0, const long c1) { PS_SUPPKEY = c0; __av = c1; }
    QUERY11PARTSUPP1_L1_1PARTSUPP1_entry(const QUERY11PARTSUPP1_L1_1PARTSUPP1_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_L1_1PARTSUPP1_entry& modify(const long c0) { PS_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_L1_1PARTSUPP1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L1_1PARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L1_1PARTSUPP1_entry& x, const QUERY11PARTSUPP1_L1_1PARTSUPP1_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
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
  
  struct QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry {
    long PS_SUPPKEY; long P_PARTKEY; long __av; 
    explicit QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry() { /*PS_SUPPKEY = 0L; P_PARTKEY = 0L; __av = 0L; */ }
    explicit QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry(const long c0, const long c1, const long c2) { PS_SUPPKEY = c0; P_PARTKEY = c1; __av = c2; }
    QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry(const QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry& modify(const long c0, const long c1) { PS_SUPPKEY = c0; P_PARTKEY = c1;  return *this; }
    FORCE_INLINE QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry& modify0(const long c0) { PS_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry& x, const QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry& x, const QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry,long,
    HashIndex<QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry,long,QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_mapkey01_idxfn,true>,
    HashIndex<QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry,long,QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_mapkey0_idxfn,false>
  > QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_map;
  typedef HashIndex<QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry,long,QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_mapkey01_idxfn,true> HashIndex_QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_map_01;
  typedef HashIndex<QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry,long,QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_mapkey0_idxfn,false> HashIndex_QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_map_0;
  
  struct QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry {
    long PS_SUPPKEY; long P_PARTKEY; long __av; 
    explicit QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry() { /*PS_SUPPKEY = 0L; P_PARTKEY = 0L; __av = 0L; */ }
    explicit QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry(const long c0, const long c1, const long c2) { PS_SUPPKEY = c0; P_PARTKEY = c1; __av = c2; }
    QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry(const QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry& modify(const long c0, const long c1) { PS_SUPPKEY = c0; P_PARTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry& x, const QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry,long,
    HashIndex<QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry,long,QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_mapkey01_idxfn,true>
  > QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_map;
  typedef HashIndex<QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry,long,QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_mapkey01_idxfn,true> HashIndex_QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_map_01;
  
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
  
  struct QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry {
    long PS_SUPPKEY; long P_PARTKEY; DOUBLE_TYPE __av; 
    explicit QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry() { /*PS_SUPPKEY = 0L; P_PARTKEY = 0L; __av = 0.0; */ }
    explicit QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { PS_SUPPKEY = c0; P_PARTKEY = c1; __av = c2; }
    QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry(const QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry& modify(const long c0, const long c1) { PS_SUPPKEY = c0; P_PARTKEY = c1;  return *this; }
    FORCE_INLINE QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry& modify0(const long c0) { PS_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry& x, const QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry& x, const QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,
    HashIndex<QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_mapkey01_idxfn,true>,
    HashIndex<QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_mapkey0_idxfn,false>
  > QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_map;
  typedef HashIndex<QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_mapkey01_idxfn,true> HashIndex_QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_map_01;
  typedef HashIndex<QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_mapkey0_idxfn,false> HashIndex_QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_map_0;
  
  struct QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry {
    long PS_SUPPKEY; long P_PARTKEY; DOUBLE_TYPE __av; 
    explicit QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry() { /*PS_SUPPKEY = 0L; P_PARTKEY = 0L; __av = 0.0; */ }
    explicit QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { PS_SUPPKEY = c0; P_PARTKEY = c1; __av = c2; }
    QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry(const QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry& modify(const long c0, const long c1) { PS_SUPPKEY = c0; P_PARTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry& x, const QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_mapkey01_idxfn,true>
  > QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_map;
  typedef HashIndex<QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry,DOUBLE_TYPE,QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_mapkey01_idxfn,true> HashIndex_QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_map_01;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
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
    void on_batch_update_SUPPLIER(TPCHSupplierBatch& DELTA_SUPPLIER) {
      {
        if (tS > 0) { tS += DELTA_SUPPLIER.size; return; }         
        tLastN += DELTA_SUPPLIER.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_SUPPLIER.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_SUPPLIER.size;

        QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA.clear();
        { 
          for (size_t i = 0; i < DELTA_SUPPLIER.size; i++) 
          {
                long ps_suppkey = DELTA_SUPPLIER.suppkey[i];
                // STRING_TYPE s_name = DELTA_SUPPLIER.name[i];
                // STRING_TYPE s_address = DELTA_SUPPLIER.address[i];
                long s_nationkey = DELTA_SUPPLIER.nationkey[i];
                // STRING_TYPE s_phone = DELTA_SUPPLIER.phone[i];
                // DOUBLE_TYPE s_acctbal = DELTA_SUPPLIER.acctbal[i];
                // STRING_TYPE s_comment = DELTA_SUPPLIER.comment[i];
                long v1 = 1L;
                QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA.addOrDelOnZero(se1.modify(ps_suppkey,s_nationkey),v1);            
          }          
        }

        DOUBLE_TYPE agg1 = 0.0;
        {  // foreach
          const HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01* i2 = static_cast<HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01*>(QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA.index[0]);
          HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01::IdxNode* n2; 
          QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
                long ps_suppkey = e2->PS_SUPPKEY;
                long s_nationkey = e2->S_NATIONKEY;
                long v2 = e2->__av;
                agg1 += (v2 * (QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1.getValueOrDefault(se3.modify(s_nationkey)) * QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2.getValueOrDefault(se4.modify(ps_suppkey))));
              n2 = n2->nxt;
            }
          }
        }QUERY11PARTSUPP1_L1_1 += agg1;
        {  // foreach
          const HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01* i3 = static_cast<HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01*>(QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA.index[0]);
          HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01::IdxNode* n3; 
          QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long ps_suppkey = e3->PS_SUPPKEY;
                long s_nationkey = e3->S_NATIONKEY;
                long v3 = e3->__av;
                QUERY11PARTSUPP1_L1_1PARTSUPP1.addOrDelOnZero(se5.modify(ps_suppkey),(v3 * QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1.getValueOrDefault(se6.modify(s_nationkey))));
              n3 = n3->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01* i4 = static_cast<HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01*>(QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA.index[0]);
          HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01::IdxNode* n4; 
          QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long ps_suppkey = e4->PS_SUPPKEY;
                long s_nationkey = e4->S_NATIONKEY;
                long v4 = e4->__av;
                { //slice 
                  const HashIndex_QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_map_0* i5 = static_cast<HashIndex_QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_map_0*>(QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2.index[1]);
                  const HASH_RES_t h1 = QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_mapkey0_idxfn::hash(se9.modify0(ps_suppkey));
                  HashIndex_QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_map_0::IdxNode* n5 = static_cast<HashIndex_QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_map_0::IdxNode*>(i5->slice(se9, h1));
                  QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry* e5;
                 
                  if (n5 && (e5 = n5->obj)) {
                    do {                
                      long p_partkey = e5->P_PARTKEY;
                      long v5 = e5->__av;
                      QUERY11PARTSUPP1_E2_1.addOrDelOnZero(se7.modify(p_partkey),(v4 * (QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1.getValueOrDefault(se8.modify(s_nationkey)) * v5)));
                      n5 = n5->nxt;
                    } while (n5 && (e5 = n5->obj) && h1 == n5->hash &&  QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_mapkey0_idxfn::equals(se9, *e5)); 
                  }
                }
              n4 = n4->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01* i6 = static_cast<HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01*>(QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA.index[0]);
          HashIndex_QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map_01::IdxNode* n6; 
          QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long ps_suppkey = e6->PS_SUPPKEY;
                long s_nationkey = e6->S_NATIONKEY;
                long v6 = e6->__av;
                { //slice 
                  const HashIndex_QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_map_0* i7 = static_cast<HashIndex_QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_map_0*>(QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2.index[1]);
                  const HASH_RES_t h2 = QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_mapkey0_idxfn::hash(se12.modify0(ps_suppkey));
                  HashIndex_QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_map_0::IdxNode* n7 = static_cast<HashIndex_QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_map_0::IdxNode*>(i7->slice(se12, h2));
                  QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry* e7;
                 
                  if (n7 && (e7 = n7->obj)) {
                    do {                
                      long p_partkey = e7->P_PARTKEY;
                      DOUBLE_TYPE v7 = e7->__av;
                      QUERY11PARTSUPP1_L3_1.addOrDelOnZero(se10.modify(p_partkey),(v6 * (QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1.getValueOrDefault(se11.modify(s_nationkey)) * v7)));
                      n7 = n7->nxt;
                    } while (n7 && (e7 = n7->obj) && h2 == n7->hash &&  QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_mapkey0_idxfn::equals(se12, *e7)); 
                  }
                }
              n6 = n6->nxt;
            }
          }
        }QUERY11.clear();
        {  // foreach
          const HashIndex_QUERY11PARTSUPP1_E2_1_map_0* i8 = static_cast<HashIndex_QUERY11PARTSUPP1_E2_1_map_0*>(QUERY11PARTSUPP1_E2_1.index[0]);
          HashIndex_QUERY11PARTSUPP1_E2_1_map_0::IdxNode* n8; 
          QUERY11PARTSUPP1_E2_1_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long p_partkey = e8->P_PARTKEY;
                long v8 = e8->__av;
                DOUBLE_TYPE agg2 = 0.0;
                DOUBLE_TYPE l1 = QUERY11PARTSUPP1_L3_1.getValueOrDefault(se14.modify(p_partkey));
                DOUBLE_TYPE l2 = (QUERY11PARTSUPP1_L1_1 * 0.001);
                (/*if */(l1 > l2) ? agg2 += QUERY11PARTSUPP1_L3_1.getValueOrDefault(se15.modify(p_partkey)) : 0.0);
                QUERY11.addOrDelOnZero(se13.modify(p_partkey),((v8 != 0 ? 1L : 0L) * agg2));
              n8 = n8->nxt;
            }
          }
        }
      }
    }
    void on_batch_update_PARTSUPP(TPCHPartSuppBatch& DELTA_PARTSUPP) {
      { 
        if (tS > 0) { tS += DELTA_PARTSUPP.size; return; }         
        tLastN += DELTA_PARTSUPP.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_PARTSUPP.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_PARTSUPP.size;


        QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA.clear();
        QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA.clear();
        QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_PARTSUPP.size; i++)
          {
                long ps_partkey = DELTA_PARTSUPP.partkey[i];
                long ps_suppkey = DELTA_PARTSUPP.suppkey[i];
                long ps_availqty = DELTA_PARTSUPP.availqty[i];
                DOUBLE_TYPE ps_supplycost = DELTA_PARTSUPP.supplycost[i];
                // STRING_TYPE ps_comment = DELTA_PARTSUPP.comment[i];
                long v9 = 1L;
                QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA.addOrDelOnZero(se16.modify(ps_suppkey),(v9 * (ps_supplycost * ps_availqty)));
                long v10 = 1L;
                QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA.addOrDelOnZero(se17.modify(ps_suppkey,ps_partkey),v10);
                long v11 = 1L;
                QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA.addOrDelOnZero(se18.modify(ps_suppkey,ps_partkey),(v11 * (ps_supplycost * ps_availqty)));
          }
        }


        DOUBLE_TYPE agg3 = 0.0;
        {  // foreach
          const HashIndex_QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_map_0* i12 = static_cast<HashIndex_QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_map_0*>(QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA.index[0]);
          HashIndex_QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_map_0::IdxNode* n12; 
          QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long ps_suppkey = e12->PS_SUPPKEY;
                DOUBLE_TYPE v12 = e12->__av;
                agg3 += (v12 * QUERY11PARTSUPP1_L1_1PARTSUPP1.getValueOrDefault(se20.modify(ps_suppkey)));
              n12 = n12->nxt;
            }
          }
        }QUERY11PARTSUPP1_L1_1 += agg3;
        {  // foreach
          const HashIndex_QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_map_0* i13 = static_cast<HashIndex_QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_map_0*>(QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA.index[0]);
          HashIndex_QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_map_0::IdxNode* n13; 
          QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long ps_suppkey = e13->PS_SUPPKEY;
                DOUBLE_TYPE v13 = e13->__av;
                QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2.addOrDelOnZero(se21.modify(ps_suppkey),v13);
              n13 = n13->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_map_01* i14 = static_cast<HashIndex_QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_map_01*>(QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA.index[0]);
          HashIndex_QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_map_01::IdxNode* n14; 
          QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
                long ps_suppkey = e14->PS_SUPPKEY;
                long p_partkey = e14->P_PARTKEY;
                long v14 = e14->__av;
                QUERY11PARTSUPP1_E2_1.addOrDelOnZero(se22.modify(p_partkey),(v14 * QUERY11PARTSUPP1_L1_1PARTSUPP1.getValueOrDefault(se23.modify(ps_suppkey))));
              n14 = n14->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_map_01* i15 = static_cast<HashIndex_QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_map_01*>(QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA.index[0]);
          HashIndex_QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_map_01::IdxNode* n15; 
          QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long ps_suppkey = e15->PS_SUPPKEY;
                long p_partkey = e15->P_PARTKEY;
                long v15 = e15->__av;
                QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2.addOrDelOnZero(se24.modify(ps_suppkey,p_partkey),v15);
              n15 = n15->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_map_01* i16 = static_cast<HashIndex_QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_map_01*>(QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA.index[0]);
          HashIndex_QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_map_01::IdxNode* n16; 
          QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long ps_suppkey = e16->PS_SUPPKEY;
                long p_partkey = e16->P_PARTKEY;
                DOUBLE_TYPE v16 = e16->__av;
                QUERY11PARTSUPP1_L3_1.addOrDelOnZero(se25.modify(p_partkey),(v16 * QUERY11PARTSUPP1_L1_1PARTSUPP1.getValueOrDefault(se26.modify(ps_suppkey))));
              n16 = n16->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_map_01* i17 = static_cast<HashIndex_QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_map_01*>(QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA.index[0]);
          HashIndex_QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_map_01::IdxNode* n17; 
          QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long ps_suppkey = e17->PS_SUPPKEY;
                long p_partkey = e17->P_PARTKEY;
                DOUBLE_TYPE v17 = e17->__av;
                QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2.addOrDelOnZero(se27.modify(ps_suppkey,p_partkey),v17);
              n17 = n17->nxt;
            }
          }
        }QUERY11.clear();
        {  // foreach
          const HashIndex_QUERY11PARTSUPP1_E2_1_map_0* i18 = static_cast<HashIndex_QUERY11PARTSUPP1_E2_1_map_0*>(QUERY11PARTSUPP1_E2_1.index[0]);
          HashIndex_QUERY11PARTSUPP1_E2_1_map_0::IdxNode* n18; 
          QUERY11PARTSUPP1_E2_1_entry* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
                long p_partkey = e18->P_PARTKEY;
                long v18 = e18->__av;
                DOUBLE_TYPE agg4 = 0.0;
                DOUBLE_TYPE l3 = QUERY11PARTSUPP1_L3_1.getValueOrDefault(se29.modify(p_partkey));
                DOUBLE_TYPE l4 = (QUERY11PARTSUPP1_L1_1 * 0.001);
                (/*if */(l3 > l4) ? agg4 += QUERY11PARTSUPP1_L3_1.getValueOrDefault(se30.modify(p_partkey)) : 0.0);
                QUERY11.addOrDelOnZero(se28.modify(p_partkey),((v18 != 0 ? 1L : 0L) * agg4));
              n18 = n18->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        QUERY11PARTSUPP1_L1_1 = 0.0;
        QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1.clear();
        STRING_TYPE l5 = c1;
        { //slice 
          const HashIndex_NATION_map_1* i19 = static_cast<HashIndex_NATION_map_1*>(NATION.index[1]);
          const HASH_RES_t h3 = NATION_mapkey1_idxfn::hash(se33.modify1(l5));
          HashIndex_NATION_map_1::IdxNode* n19 = static_cast<HashIndex_NATION_map_1::IdxNode*>(i19->slice(se33, h3));
          NATION_entry* e19;
         
          if (n19 && (e19 = n19->obj)) {
            do {                
              long s_nationkey = e19->NATION_NATIONKEY;
              long n_regionkey = e19->NATION_REGIONKEY;
              STRING_TYPE n_comment = e19->NATION_COMMENT;
              long v19 = e19->__av;
              QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1.addOrDelOnZero(se32.modify(s_nationkey),v19);
              n19 = n19->nxt;
            } while (n19 && (e19 = n19->obj) && h3 == n19->hash &&  NATION_mapkey1_idxfn::equals(se33, *e19)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_entry se1;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry se3;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry se4;
    QUERY11PARTSUPP1_L1_1PARTSUPP1_entry se5;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry se6;
    QUERY11PARTSUPP1_E2_1_entry se7;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry se8;
    QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry se9;
    QUERY11PARTSUPP1_L3_1_entry se10;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry se11;
    QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry se12;
    QUERY11_entry se13;
    QUERY11PARTSUPP1_L3_1_entry se14;
    QUERY11PARTSUPP1_L3_1_entry se15;
    QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_entry se16;
    QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_entry se17;
    QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_entry se18;
    QUERY11PARTSUPP1_L1_1PARTSUPP1_entry se20;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_entry se21;
    QUERY11PARTSUPP1_E2_1_entry se22;
    QUERY11PARTSUPP1_L1_1PARTSUPP1_entry se23;
    QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_entry se24;
    QUERY11PARTSUPP1_L3_1_entry se25;
    QUERY11PARTSUPP1_L1_1PARTSUPP1_entry se26;
    QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_entry se27;
    QUERY11_entry se28;
    QUERY11PARTSUPP1_L3_1_entry se29;
    QUERY11PARTSUPP1_L3_1_entry se30;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_entry se32;
    NATION_entry se33;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    DOUBLE_TYPE QUERY11PARTSUPP1_L1_1;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA_map QUERY11PARTSUPP1_L1_1SUPPLIER1_DELTA;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1_map QUERY11PARTSUPP1_L1_1SUPPLIER1_P_1;
    QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2_map QUERY11PARTSUPP1_L1_1SUPPLIER1_P_2;
    QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA_map QUERY11PARTSUPP1_L1_1PARTSUPP1_DELTA;
    QUERY11PARTSUPP1_L1_1PARTSUPP1_map QUERY11PARTSUPP1_L1_1PARTSUPP1;
    QUERY11PARTSUPP1_E2_1_map QUERY11PARTSUPP1_E2_1;
    QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2_map QUERY11PARTSUPP1_E2_1SUPPLIER1_P_2;
    QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA_map QUERY11PARTSUPP1_E2_1PARTSUPP1_DELTA;
    QUERY11PARTSUPP1_L3_1_map QUERY11PARTSUPP1_L3_1;
    QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2_map QUERY11PARTSUPP1_L3_1SUPPLIER1_P_2;
    QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA_map QUERY11PARTSUPP1_L3_1PARTSUPP1_DELTA;
    DELTA_SUPPLIER_map DELTA_SUPPLIER;
    DELTA_PARTSUPP_map DELTA_PARTSUPP;
    
    /*const static*/ STRING_TYPE c1;
  
  };

}
