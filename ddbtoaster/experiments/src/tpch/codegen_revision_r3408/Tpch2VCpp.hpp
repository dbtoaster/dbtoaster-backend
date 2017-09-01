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
  
  struct COUNT_entry {
    DOUBLE_TYPE S_ACCTBAL; STRING_TYPE S_NAME; STRING_TYPE N_NAME; long P_PARTKEY; STRING_TYPE P_MFGR; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; STRING_TYPE S_COMMENT; long __av; 
    explicit COUNT_entry() { /*S_ACCTBAL = 0.0; S_NAME = ""; N_NAME = ""; P_PARTKEY = 0L; P_MFGR = ""; S_ADDRESS = ""; S_PHONE = ""; S_COMMENT = ""; __av = 0L; */ }
    explicit COUNT_entry(const DOUBLE_TYPE c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const STRING_TYPE& c7, const long c8) { S_ACCTBAL = c0; S_NAME = c1; N_NAME = c2; P_PARTKEY = c3; P_MFGR = c4; S_ADDRESS = c5; S_PHONE = c6; S_COMMENT = c7; __av = c8; }
    COUNT_entry(const COUNT_entry& other) : S_ACCTBAL( other.S_ACCTBAL ), S_NAME( other.S_NAME ), N_NAME( other.N_NAME ), P_PARTKEY( other.P_PARTKEY ), P_MFGR( other.P_MFGR ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), S_COMMENT( other.S_COMMENT ), __av( other.__av ) {}
    FORCE_INLINE COUNT_entry& modify(const DOUBLE_TYPE c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const STRING_TYPE& c7) { S_ACCTBAL = c0; S_NAME = c1; N_NAME = c2; P_PARTKEY = c3; P_MFGR = c4; S_ADDRESS = c5; S_PHONE = c6; S_COMMENT = c7;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_MFGR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_ACCTBAL);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.N_NAME);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.P_MFGR);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.S_COMMENT);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_entry& x, const COUNT_entry& y) {
      return x.S_ACCTBAL == y.S_ACCTBAL && x.S_NAME == y.S_NAME && x.N_NAME == y.N_NAME && x.P_PARTKEY == y.P_PARTKEY && x.P_MFGR == y.P_MFGR && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE && x.S_COMMENT == y.S_COMMENT;
    }
  };
  
  typedef MultiHashMap<COUNT_entry,long,
    HashIndex<COUNT_entry,long,COUNT_mapkey01234567_idxfn,true>
  > COUNT_map;
  typedef HashIndex<COUNT_entry,long,COUNT_mapkey01234567_idxfn,true> HashIndex_COUNT_map_01234567;
  
  struct COUNTPARTSUPP2_entry {
    long COUNTPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE P_MFGR; long __av; 
    explicit COUNTPARTSUPP2_entry() { /*COUNTPARTSUPPPARTSUPP_PARTKEY = 0L; P_MFGR = ""; __av = 0L; */ }
    explicit COUNTPARTSUPP2_entry(const long c0, const STRING_TYPE& c1, const long c2) { COUNTPARTSUPPPARTSUPP_PARTKEY = c0; P_MFGR = c1; __av = c2; }
    COUNTPARTSUPP2_entry(const COUNTPARTSUPP2_entry& other) : COUNTPARTSUPPPARTSUPP_PARTKEY( other.COUNTPARTSUPPPARTSUPP_PARTKEY ), P_MFGR( other.P_MFGR ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP2_entry& modify(const long c0, const STRING_TYPE& c1) { COUNTPARTSUPPPARTSUPP_PARTKEY = c0; P_MFGR = c1;  return *this; }
    FORCE_INLINE COUNTPARTSUPP2_entry& modify0(const long c0) { COUNTPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTPARTSUPPPARTSUPP_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_MFGR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.P_MFGR);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP2_entry& x, const COUNTPARTSUPP2_entry& y) {
      return x.COUNTPARTSUPPPARTSUPP_PARTKEY == y.COUNTPARTSUPPPARTSUPP_PARTKEY && x.P_MFGR == y.P_MFGR;
    }
  };
  
  struct COUNTPARTSUPP2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP2_entry& x, const COUNTPARTSUPP2_entry& y) {
      return x.COUNTPARTSUPPPARTSUPP_PARTKEY == y.COUNTPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP2_entry,long,
    HashIndex<COUNTPARTSUPP2_entry,long,COUNTPARTSUPP2_mapkey01_idxfn,true>,
    HashIndex<COUNTPARTSUPP2_entry,long,COUNTPARTSUPP2_mapkey0_idxfn,false>
  > COUNTPARTSUPP2_map;
  typedef HashIndex<COUNTPARTSUPP2_entry,long,COUNTPARTSUPP2_mapkey01_idxfn,true> HashIndex_COUNTPARTSUPP2_map_01;
  typedef HashIndex<COUNTPARTSUPP2_entry,long,COUNTPARTSUPP2_mapkey0_idxfn,false> HashIndex_COUNTPARTSUPP2_map_0;
  
  struct COUNTPARTSUPP3_entry {
    long COUNTPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; DOUBLE_TYPE S_ACCTBAL; STRING_TYPE S_COMMENT; STRING_TYPE N_NAME; long __av; 
    explicit COUNTPARTSUPP3_entry() { /*COUNTPARTSUPPPARTSUPP_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; S_ACCTBAL = 0.0; S_COMMENT = ""; N_NAME = ""; __av = 0L; */ }
    explicit COUNTPARTSUPP3_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const long c7) { COUNTPARTSUPPPARTSUPP_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; S_ACCTBAL = c4; S_COMMENT = c5; N_NAME = c6; __av = c7; }
    COUNTPARTSUPP3_entry(const COUNTPARTSUPP3_entry& other) : COUNTPARTSUPPPARTSUPP_SUPPKEY( other.COUNTPARTSUPPPARTSUPP_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), S_ACCTBAL( other.S_ACCTBAL ), S_COMMENT( other.S_COMMENT ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP3_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6) { COUNTPARTSUPPPARTSUPP_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; S_ACCTBAL = c4; S_COMMENT = c5; N_NAME = c6;  return *this; }
    FORCE_INLINE COUNTPARTSUPP3_entry& modify0(const long c0) { COUNTPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTPARTSUPPPARTSUPP_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP3_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.S_ACCTBAL);
      hash_combine(h, e.S_COMMENT);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP3_entry& x, const COUNTPARTSUPP3_entry& y) {
      return x.COUNTPARTSUPPPARTSUPP_SUPPKEY == y.COUNTPARTSUPPPARTSUPP_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE && x.S_ACCTBAL == y.S_ACCTBAL && x.S_COMMENT == y.S_COMMENT && x.N_NAME == y.N_NAME;
    }
  };
  
  struct COUNTPARTSUPP3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP3_entry& x, const COUNTPARTSUPP3_entry& y) {
      return x.COUNTPARTSUPPPARTSUPP_SUPPKEY == y.COUNTPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP3_entry,long,
    HashIndex<COUNTPARTSUPP3_entry,long,COUNTPARTSUPP3_mapkey0123456_idxfn,true>,
    HashIndex<COUNTPARTSUPP3_entry,long,COUNTPARTSUPP3_mapkey0_idxfn,false>
  > COUNTPARTSUPP3_map;
  typedef HashIndex<COUNTPARTSUPP3_entry,long,COUNTPARTSUPP3_mapkey0123456_idxfn,true> HashIndex_COUNTPARTSUPP3_map_0123456;
  typedef HashIndex<COUNTPARTSUPP3_entry,long,COUNTPARTSUPP3_mapkey0_idxfn,false> HashIndex_COUNTPARTSUPP3_map_0;
  
  struct COUNTPARTSUPP3SUPPLIER1_entry {
    long COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY; STRING_TYPE N_NAME; long __av; 
    explicit COUNTPARTSUPP3SUPPLIER1_entry() { /*COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY = 0L; N_NAME = ""; __av = 0L; */ }
    explicit COUNTPARTSUPP3SUPPLIER1_entry(const long c0, const STRING_TYPE& c1, const long c2) { COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY = c0; N_NAME = c1; __av = c2; }
    COUNTPARTSUPP3SUPPLIER1_entry(const COUNTPARTSUPP3SUPPLIER1_entry& other) : COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY( other.COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP3SUPPLIER1_entry& modify(const long c0, const STRING_TYPE& c1) { COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY = c0; N_NAME = c1;  return *this; }
    FORCE_INLINE COUNTPARTSUPP3SUPPLIER1_entry& modify0(const long c0) { COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP3SUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP3SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP3SUPPLIER1_entry& x, const COUNTPARTSUPP3SUPPLIER1_entry& y) {
      return x.COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY == y.COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  struct COUNTPARTSUPP3SUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP3SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP3SUPPLIER1_entry& x, const COUNTPARTSUPP3SUPPLIER1_entry& y) {
      return x.COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY == y.COUNTPARTSUPP3SUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP3SUPPLIER1_entry,long,
    HashIndex<COUNTPARTSUPP3SUPPLIER1_entry,long,COUNTPARTSUPP3SUPPLIER1_mapkey01_idxfn,true>,
    HashIndex<COUNTPARTSUPP3SUPPLIER1_entry,long,COUNTPARTSUPP3SUPPLIER1_mapkey0_idxfn,false>
  > COUNTPARTSUPP3SUPPLIER1_map;
  typedef HashIndex<COUNTPARTSUPP3SUPPLIER1_entry,long,COUNTPARTSUPP3SUPPLIER1_mapkey01_idxfn,true> HashIndex_COUNTPARTSUPP3SUPPLIER1_map_01;
  typedef HashIndex<COUNTPARTSUPP3SUPPLIER1_entry,long,COUNTPARTSUPP3SUPPLIER1_mapkey0_idxfn,false> HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0;
  
  struct COUNTPARTSUPP4_L2_3_entry {
    long COUNTPARTSUPPPARTSUPP_SUPPKEY; long __av; 
    explicit COUNTPARTSUPP4_L2_3_entry() { /*COUNTPARTSUPPPARTSUPP_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNTPARTSUPP4_L2_3_entry(const long c0, const long c1) { COUNTPARTSUPPPARTSUPP_SUPPKEY = c0; __av = c1; }
    COUNTPARTSUPP4_L2_3_entry(const COUNTPARTSUPP4_L2_3_entry& other) : COUNTPARTSUPPPARTSUPP_SUPPKEY( other.COUNTPARTSUPPPARTSUPP_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP4_L2_3_entry& modify(const long c0) { COUNTPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTPARTSUPPPARTSUPP_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP4_L2_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP4_L2_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP4_L2_3_entry& x, const COUNTPARTSUPP4_L2_3_entry& y) {
      return x.COUNTPARTSUPPPARTSUPP_SUPPKEY == y.COUNTPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP4_L2_3_entry,long,
    HashIndex<COUNTPARTSUPP4_L2_3_entry,long,COUNTPARTSUPP4_L2_3_mapkey0_idxfn,true>
  > COUNTPARTSUPP4_L2_3_map;
  typedef HashIndex<COUNTPARTSUPP4_L2_3_entry,long,COUNTPARTSUPP4_L2_3_mapkey0_idxfn,true> HashIndex_COUNTPARTSUPP4_L2_3_map_0;
  
  struct COUNTPARTSUPP4_L2_3SUPPLIER1_entry {
    long COUNTPARTSUPP4_L2_3SUPPLIERSUPPLIER_NATIONKEY; long __av; 
    explicit COUNTPARTSUPP4_L2_3SUPPLIER1_entry() { /*COUNTPARTSUPP4_L2_3SUPPLIERSUPPLIER_NATIONKEY = 0L; __av = 0L; */ }
    explicit COUNTPARTSUPP4_L2_3SUPPLIER1_entry(const long c0, const long c1) { COUNTPARTSUPP4_L2_3SUPPLIERSUPPLIER_NATIONKEY = c0; __av = c1; }
    COUNTPARTSUPP4_L2_3SUPPLIER1_entry(const COUNTPARTSUPP4_L2_3SUPPLIER1_entry& other) : COUNTPARTSUPP4_L2_3SUPPLIERSUPPLIER_NATIONKEY( other.COUNTPARTSUPP4_L2_3SUPPLIERSUPPLIER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP4_L2_3SUPPLIER1_entry& modify(const long c0) { COUNTPARTSUPP4_L2_3SUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTPARTSUPP4_L2_3SUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP4_L2_3SUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP4_L2_3SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTSUPP4_L2_3SUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP4_L2_3SUPPLIER1_entry& x, const COUNTPARTSUPP4_L2_3SUPPLIER1_entry& y) {
      return x.COUNTPARTSUPP4_L2_3SUPPLIERSUPPLIER_NATIONKEY == y.COUNTPARTSUPP4_L2_3SUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP4_L2_3SUPPLIER1_entry,long,
    HashIndex<COUNTPARTSUPP4_L2_3SUPPLIER1_entry,long,COUNTPARTSUPP4_L2_3SUPPLIER1_mapkey0_idxfn,true>
  > COUNTPARTSUPP4_L2_3SUPPLIER1_map;
  typedef HashIndex<COUNTPARTSUPP4_L2_3SUPPLIER1_entry,long,COUNTPARTSUPP4_L2_3SUPPLIER1_mapkey0_idxfn,true> HashIndex_COUNTPARTSUPP4_L2_3SUPPLIER1_map_0;
  
  struct COUNTSUPPLIER1_entry {
    long P_PARTKEY; STRING_TYPE P_MFGR; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; DOUBLE_TYPE S_ACCTBAL; STRING_TYPE S_COMMENT; DOUBLE_TYPE PS_SUPPLYCOST; STRING_TYPE N_NAME; long __av; 
    explicit COUNTSUPPLIER1_entry() { /*P_PARTKEY = 0L; P_MFGR = ""; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; S_ACCTBAL = 0.0; S_COMMENT = ""; PS_SUPPLYCOST = 0.0; N_NAME = ""; __av = 0L; */ }
    explicit COUNTSUPPLIER1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8, const long c9) { P_PARTKEY = c0; P_MFGR = c1; S_NAME = c2; S_ADDRESS = c3; S_PHONE = c4; S_ACCTBAL = c5; S_COMMENT = c6; PS_SUPPLYCOST = c7; N_NAME = c8; __av = c9; }
    COUNTSUPPLIER1_entry(const COUNTSUPPLIER1_entry& other) : P_PARTKEY( other.P_PARTKEY ), P_MFGR( other.P_MFGR ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), S_ACCTBAL( other.S_ACCTBAL ), S_COMMENT( other.S_COMMENT ), PS_SUPPLYCOST( other.PS_SUPPLYCOST ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8) { P_PARTKEY = c0; P_MFGR = c1; S_NAME = c2; S_ADDRESS = c3; S_PHONE = c4; S_ACCTBAL = c5; S_COMMENT = c6; PS_SUPPLYCOST = c7; N_NAME = c8;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_MFGR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1_mapkey012345678_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.P_MFGR);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.S_ACCTBAL);
      hash_combine(h, e.S_COMMENT);
      hash_combine(h, e.PS_SUPPLYCOST);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1_entry& x, const COUNTSUPPLIER1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.P_MFGR == y.P_MFGR && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE && x.S_ACCTBAL == y.S_ACCTBAL && x.S_COMMENT == y.S_COMMENT && x.PS_SUPPLYCOST == y.PS_SUPPLYCOST && x.N_NAME == y.N_NAME;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1_entry,long,
    HashIndex<COUNTSUPPLIER1_entry,long,COUNTSUPPLIER1_mapkey012345678_idxfn,true>
  > COUNTSUPPLIER1_map;
  typedef HashIndex<COUNTSUPPLIER1_entry,long,COUNTSUPPLIER1_mapkey012345678_idxfn,true> HashIndex_COUNTSUPPLIER1_map_012345678;
  
  struct COUNTSUPPLIER1SUPPLIER2_entry {
    long P_PARTKEY; long COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE PS_SUPPLYCOST; STRING_TYPE P_MFGR; long __av; 
    explicit COUNTSUPPLIER1SUPPLIER2_entry() { /*P_PARTKEY = 0L; COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY = 0L; PS_SUPPLYCOST = 0.0; P_MFGR = ""; __av = 0L; */ }
    explicit COUNTSUPPLIER1SUPPLIER2_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3, const long c4) { P_PARTKEY = c0; COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY = c1; PS_SUPPLYCOST = c2; P_MFGR = c3; __av = c4; }
    COUNTSUPPLIER1SUPPLIER2_entry(const COUNTSUPPLIER1SUPPLIER2_entry& other) : P_PARTKEY( other.P_PARTKEY ), COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY( other.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY ), PS_SUPPLYCOST( other.PS_SUPPLYCOST ), P_MFGR( other.P_MFGR ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1SUPPLIER2_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3) { P_PARTKEY = c0; COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY = c1; PS_SUPPLYCOST = c2; P_MFGR = c3;  return *this; }
    FORCE_INLINE COUNTSUPPLIER1SUPPLIER2_entry& modify1(const long c1) { COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_MFGR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1SUPPLIER2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1SUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.PS_SUPPLYCOST);
      hash_combine(h, e.P_MFGR);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1SUPPLIER2_entry& x, const COUNTSUPPLIER1SUPPLIER2_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY == y.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY && x.PS_SUPPLYCOST == y.PS_SUPPLYCOST && x.P_MFGR == y.P_MFGR;
    }
  };
  
  struct COUNTSUPPLIER1SUPPLIER2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1SUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1SUPPLIER2_entry& x, const COUNTSUPPLIER1SUPPLIER2_entry& y) {
      return x.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY == y.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1SUPPLIER2_entry,long,
    HashIndex<COUNTSUPPLIER1SUPPLIER2_entry,long,COUNTSUPPLIER1SUPPLIER2_mapkey0123_idxfn,true>,
    HashIndex<COUNTSUPPLIER1SUPPLIER2_entry,long,COUNTSUPPLIER1SUPPLIER2_mapkey1_idxfn,false>
  > COUNTSUPPLIER1SUPPLIER2_map;
  typedef HashIndex<COUNTSUPPLIER1SUPPLIER2_entry,long,COUNTSUPPLIER1SUPPLIER2_mapkey0123_idxfn,true> HashIndex_COUNTSUPPLIER1SUPPLIER2_map_0123;
  typedef HashIndex<COUNTSUPPLIER1SUPPLIER2_entry,long,COUNTSUPPLIER1SUPPLIER2_mapkey1_idxfn,false> HashIndex_COUNTSUPPLIER1SUPPLIER2_map_1;
  
  struct COUNTSUPPLIER1SUPPLIER2PART3_entry {
    long COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY; long COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE PS_SUPPLYCOST; long __av; 
    explicit COUNTSUPPLIER1SUPPLIER2PART3_entry() { /*COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY = 0L; COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY = 0L; PS_SUPPLYCOST = 0.0; __av = 0L; */ }
    explicit COUNTSUPPLIER1SUPPLIER2PART3_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const long c3) { COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY = c0; COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY = c1; PS_SUPPLYCOST = c2; __av = c3; }
    COUNTSUPPLIER1SUPPLIER2PART3_entry(const COUNTSUPPLIER1SUPPLIER2PART3_entry& other) : COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY( other.COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY ), COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY( other.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY ), PS_SUPPLYCOST( other.PS_SUPPLYCOST ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1SUPPLIER2PART3_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2) { COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY = c0; COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY = c1; PS_SUPPLYCOST = c2;  return *this; }
    FORCE_INLINE COUNTSUPPLIER1SUPPLIER2PART3_entry& modify0(const long c0) { COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE COUNTSUPPLIER1SUPPLIER2PART3_entry& modify1(const long c1) { COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1SUPPLIER2PART3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1SUPPLIER2PART3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY);
      hash_combine(h, e.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.PS_SUPPLYCOST);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1SUPPLIER2PART3_entry& x, const COUNTSUPPLIER1SUPPLIER2PART3_entry& y) {
      return x.COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY == y.COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY && x.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY == y.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY && x.PS_SUPPLYCOST == y.PS_SUPPLYCOST;
    }
  };
  
  struct COUNTSUPPLIER1SUPPLIER2PART3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1SUPPLIER2PART3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1SUPPLIER2PART3_entry& x, const COUNTSUPPLIER1SUPPLIER2PART3_entry& y) {
      return x.COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY == y.COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY;
    }
  };
  
  struct COUNTSUPPLIER1SUPPLIER2PART3_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1SUPPLIER2PART3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1SUPPLIER2PART3_entry& x, const COUNTSUPPLIER1SUPPLIER2PART3_entry& y) {
      return x.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY == y.COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1SUPPLIER2PART3_entry,long,
    HashIndex<COUNTSUPPLIER1SUPPLIER2PART3_entry,long,COUNTSUPPLIER1SUPPLIER2PART3_mapkey012_idxfn,true>,
    HashIndex<COUNTSUPPLIER1SUPPLIER2PART3_entry,long,COUNTSUPPLIER1SUPPLIER2PART3_mapkey0_idxfn,false>,
    HashIndex<COUNTSUPPLIER1SUPPLIER2PART3_entry,long,COUNTSUPPLIER1SUPPLIER2PART3_mapkey1_idxfn,false>
  > COUNTSUPPLIER1SUPPLIER2PART3_map;
  typedef HashIndex<COUNTSUPPLIER1SUPPLIER2PART3_entry,long,COUNTSUPPLIER1SUPPLIER2PART3_mapkey012_idxfn,true> HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_012;
  typedef HashIndex<COUNTSUPPLIER1SUPPLIER2PART3_entry,long,COUNTSUPPLIER1SUPPLIER2PART3_mapkey0_idxfn,false> HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_0;
  typedef HashIndex<COUNTSUPPLIER1SUPPLIER2PART3_entry,long,COUNTSUPPLIER1SUPPLIER2PART3_mapkey1_idxfn,false> HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_1;
  
  struct COUNTPART3_entry {
    long COUNTPARTPART_PARTKEY; DOUBLE_TYPE PS_SUPPLYCOST; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; DOUBLE_TYPE S_ACCTBAL; STRING_TYPE S_COMMENT; STRING_TYPE N_NAME; long __av; 
    explicit COUNTPART3_entry() { /*COUNTPARTPART_PARTKEY = 0L; PS_SUPPLYCOST = 0.0; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; S_ACCTBAL = 0.0; S_COMMENT = ""; N_NAME = ""; __av = 0L; */ }
    explicit COUNTPART3_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const STRING_TYPE& c7, const long c8) { COUNTPARTPART_PARTKEY = c0; PS_SUPPLYCOST = c1; S_NAME = c2; S_ADDRESS = c3; S_PHONE = c4; S_ACCTBAL = c5; S_COMMENT = c6; N_NAME = c7; __av = c8; }
    COUNTPART3_entry(const COUNTPART3_entry& other) : COUNTPARTPART_PARTKEY( other.COUNTPARTPART_PARTKEY ), PS_SUPPLYCOST( other.PS_SUPPLYCOST ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), S_ACCTBAL( other.S_ACCTBAL ), S_COMMENT( other.S_COMMENT ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTPART3_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const STRING_TYPE& c7) { COUNTPARTPART_PARTKEY = c0; PS_SUPPLYCOST = c1; S_NAME = c2; S_ADDRESS = c3; S_PHONE = c4; S_ACCTBAL = c5; S_COMMENT = c6; N_NAME = c7;  return *this; }
    FORCE_INLINE COUNTPART3_entry& modify0(const long c0) { COUNTPARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPART3_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPART3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTPART_PARTKEY);
      hash_combine(h, e.PS_SUPPLYCOST);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.S_ACCTBAL);
      hash_combine(h, e.S_COMMENT);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPART3_entry& x, const COUNTPART3_entry& y) {
      return x.COUNTPARTPART_PARTKEY == y.COUNTPARTPART_PARTKEY && x.PS_SUPPLYCOST == y.PS_SUPPLYCOST && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE && x.S_ACCTBAL == y.S_ACCTBAL && x.S_COMMENT == y.S_COMMENT && x.N_NAME == y.N_NAME;
    }
  };
  
  struct COUNTPART3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPART3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPART3_entry& x, const COUNTPART3_entry& y) {
      return x.COUNTPARTPART_PARTKEY == y.COUNTPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPART3_entry,long,
    HashIndex<COUNTPART3_entry,long,COUNTPART3_mapkey01234567_idxfn,true>,
    HashIndex<COUNTPART3_entry,long,COUNTPART3_mapkey0_idxfn,false>
  > COUNTPART3_map;
  typedef HashIndex<COUNTPART3_entry,long,COUNTPART3_mapkey01234567_idxfn,true> HashIndex_COUNTPART3_map_01234567;
  typedef HashIndex<COUNTPART3_entry,long,COUNTPART3_mapkey0_idxfn,false> HashIndex_COUNTPART3_map_0;
  
  struct COUNTPART3_L2_1_entry {
    long COUNTPARTPART_PARTKEY; DOUBLE_TYPE PS2_SUPPLYCOST; long __av; 
    explicit COUNTPART3_L2_1_entry() { /*COUNTPARTPART_PARTKEY = 0L; PS2_SUPPLYCOST = 0.0; __av = 0L; */ }
    explicit COUNTPART3_L2_1_entry(const long c0, const DOUBLE_TYPE c1, const long c2) { COUNTPARTPART_PARTKEY = c0; PS2_SUPPLYCOST = c1; __av = c2; }
    COUNTPART3_L2_1_entry(const COUNTPART3_L2_1_entry& other) : COUNTPARTPART_PARTKEY( other.COUNTPARTPART_PARTKEY ), PS2_SUPPLYCOST( other.PS2_SUPPLYCOST ), __av( other.__av ) {}
    FORCE_INLINE COUNTPART3_L2_1_entry& modify(const long c0, const DOUBLE_TYPE c1) { COUNTPARTPART_PARTKEY = c0; PS2_SUPPLYCOST = c1;  return *this; }
    FORCE_INLINE COUNTPART3_L2_1_entry& modify0(const long c0) { COUNTPARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS2_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPART3_L2_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPART3_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTPART_PARTKEY);
      hash_combine(h, e.PS2_SUPPLYCOST);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPART3_L2_1_entry& x, const COUNTPART3_L2_1_entry& y) {
      return x.COUNTPARTPART_PARTKEY == y.COUNTPARTPART_PARTKEY && x.PS2_SUPPLYCOST == y.PS2_SUPPLYCOST;
    }
  };
  
  struct COUNTPART3_L2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPART3_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPART3_L2_1_entry& x, const COUNTPART3_L2_1_entry& y) {
      return x.COUNTPARTPART_PARTKEY == y.COUNTPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPART3_L2_1_entry,long,
    HashIndex<COUNTPART3_L2_1_entry,long,COUNTPART3_L2_1_mapkey01_idxfn,true>,
    HashIndex<COUNTPART3_L2_1_entry,long,COUNTPART3_L2_1_mapkey0_idxfn,false>
  > COUNTPART3_L2_1_map;
  typedef HashIndex<COUNTPART3_L2_1_entry,long,COUNTPART3_L2_1_mapkey01_idxfn,true> HashIndex_COUNTPART3_L2_1_map_01;
  typedef HashIndex<COUNTPART3_L2_1_entry,long,COUNTPART3_L2_1_mapkey0_idxfn,false> HashIndex_COUNTPART3_L2_1_map_0;
  
  struct tuple7_SSSDSS_L {
    STRING_TYPE _1; STRING_TYPE _2; STRING_TYPE _3; DOUBLE_TYPE _4; STRING_TYPE _5; STRING_TYPE _6; long __av;
    explicit tuple7_SSSDSS_L() { }
    explicit tuple7_SSSDSS_L(const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; _5 = c5; _6 = c6; __av = c__av;}
    int operator==(const tuple7_SSSDSS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4) && (this->_5==rhs._5) && (this->_6==rhs._6)); }
    FORCE_INLINE tuple7_SSSDSS_L& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const STRING_TYPE& c5, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; _5 = c4; _6 = c5; __av = c__av; return *this; }
    static bool equals(const tuple7_SSSDSS_L &x, const tuple7_SSSDSS_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4) && (x._5==y._5) && (x._6==y._6)); }
    static long hash(const tuple7_SSSDSS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
      hash_combine(h, e._5);
      hash_combine(h, e._6);
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
    data_t(): tlq_t(), _c1(16U), agg1(16U) {
      c1 = STRING_TYPE("EUROPE");
      /* regex_t init */
      if(regcomp(&preg1, "^.*BRASS$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^.*BRASS$/" << endl;
        exit(-1);
      }
    }
  
    ~data_t() {
      regfree(&preg1);
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
    void on_insert_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        agg1.clear();
        
        long l1 = 0L;
        { //slice 
          const HashIndex_COUNTPART3_map_0* i1 = static_cast<HashIndex_COUNTPART3_map_0*>(COUNTPART3.index[1]);
          const HASH_RES_t h2 = COUNTPART3_mapkey0_idxfn::hash(se3.modify0(part_partkey));
          HashIndex_COUNTPART3_map_0::IdxNode* n1 = static_cast<HashIndex_COUNTPART3_map_0::IdxNode*>(i1->slice(se3, h2));
          COUNTPART3_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              DOUBLE_TYPE ps_supplycost = e1->PS_SUPPLYCOST;
              STRING_TYPE s_name = e1->S_NAME;
              STRING_TYPE s_address = e1->S_ADDRESS;
              STRING_TYPE s_phone = e1->S_PHONE;
              DOUBLE_TYPE s_acctbal = e1->S_ACCTBAL;
              STRING_TYPE s_comment = e1->S_COMMENT;
              STRING_TYPE n_name = e1->N_NAME;
              long v1 = e1->__av;
              long agg2 = 0L;
              { //slice 
                const HashIndex_COUNTPART3_L2_1_map_0* i2 = static_cast<HashIndex_COUNTPART3_L2_1_map_0*>(COUNTPART3_L2_1.index[1]);
                const HASH_RES_t h1 = COUNTPART3_L2_1_mapkey0_idxfn::hash(se2.modify0(part_partkey));
                HashIndex_COUNTPART3_L2_1_map_0::IdxNode* n2 = static_cast<HashIndex_COUNTPART3_L2_1_map_0::IdxNode*>(i2->slice(se2, h1));
                COUNTPART3_L2_1_entry* e2;
               
                if (n2 && (e2 = n2->obj)) {
                  do {                
                    DOUBLE_TYPE ps2_supplycost = e2->PS2_SUPPLYCOST;
                    long v2 = e2->__av;
                    (/*if */(ps_supplycost > ps2_supplycost) ? agg2 += v2 : 0L);
                    n2 = n2->nxt;
                  } while (n2 && (e2 = n2->obj) && h1 == n2->hash &&  COUNTPART3_L2_1_mapkey0_idxfn::equals(se2, *e2)); 
                }
              }(/*if */(l1 == agg2) ? agg1.addOrDelOnZero(st1.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,v1), v1) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h2 == n1->hash &&  COUNTPART3_mapkey0_idxfn::equals(se3, *e1)); 
          }
        }{  // temp foreach
          const HashIndex<tuple7_SSSDSS_L, long>* i3 = static_cast<HashIndex<tuple7_SSSDSS_L, long>*>(agg1.index[0]);
          HashIndex<tuple7_SSSDSS_L, long>::IdxNode* n3; 
          tuple7_SSSDSS_L* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
              STRING_TYPE s_name = e3->_1;
              STRING_TYPE s_address = e3->_2;
              STRING_TYPE s_phone = e3->_3;
              DOUBLE_TYPE s_acctbal = e3->_4;
              STRING_TYPE s_comment = e3->_5;
              STRING_TYPE n_name = e3->_6;  
              long v3 = e3->__av; 
            (/*if */(0L != Upreg_match(preg1,part_type) && part_size == 15L) ? COUNT.addOrDelOnZero(se1.modify(s_acctbal,s_name,n_name,part_partkey,part_mfgr,s_address,s_phone,s_comment),v3) : (void)0);      
              n3 = n3->nxt;
            }
          }
        }(/*if */(0L != Upreg_match(preg1,part_type) && part_size == 15L) ? COUNTPARTSUPP2.addOrDelOnZero(se4.modify(part_partkey,part_mfgr),1L) : (void)0);
        { //slice 
          const HashIndex_COUNTPART3_map_0* i4 = static_cast<HashIndex_COUNTPART3_map_0*>(COUNTPART3.index[1]);
          const HASH_RES_t h3 = COUNTPART3_mapkey0_idxfn::hash(se6.modify0(part_partkey));
          HashIndex_COUNTPART3_map_0::IdxNode* n4 = static_cast<HashIndex_COUNTPART3_map_0::IdxNode*>(i4->slice(se6, h3));
          COUNTPART3_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              DOUBLE_TYPE ps_supplycost = e4->PS_SUPPLYCOST;
              STRING_TYPE s_name = e4->S_NAME;
              STRING_TYPE s_address = e4->S_ADDRESS;
              STRING_TYPE s_phone = e4->S_PHONE;
              DOUBLE_TYPE s_acctbal = e4->S_ACCTBAL;
              STRING_TYPE s_comment = e4->S_COMMENT;
              STRING_TYPE n_name = e4->N_NAME;
              long v4 = e4->__av;
              (/*if */(0L != Upreg_match(preg1,part_type) && part_size == 15L) ? COUNTSUPPLIER1.addOrDelOnZero(se5.modify(part_partkey,part_mfgr,s_name,s_address,s_phone,s_acctbal,s_comment,ps_supplycost,n_name),v4) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h3 == n4->hash &&  COUNTPART3_mapkey0_idxfn::equals(se6, *e4)); 
          }
        }{ //slice 
          const HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_0* i5 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_0*>(COUNTSUPPLIER1SUPPLIER2PART3.index[1]);
          const HASH_RES_t h4 = COUNTSUPPLIER1SUPPLIER2PART3_mapkey0_idxfn::hash(se8.modify0(part_partkey));
          HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_0::IdxNode* n5 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_0::IdxNode*>(i5->slice(se8, h4));
          COUNTSUPPLIER1SUPPLIER2PART3_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long countsupplier1suppliersupplier_suppkey = e5->COUNTSUPPLIER1SUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE ps_supplycost = e5->PS_SUPPLYCOST;
              long v5 = e5->__av;
              (/*if */(0L != Upreg_match(preg1,part_type) && part_size == 15L) ? COUNTSUPPLIER1SUPPLIER2.addOrDelOnZero(se7.modify(part_partkey,countsupplier1suppliersupplier_suppkey,ps_supplycost,part_mfgr),v5) : (void)0);
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h4 == n5->hash &&  COUNTSUPPLIER1SUPPLIER2PART3_mapkey0_idxfn::equals(se8, *e5)); 
          }
        }
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0* i6 = static_cast<HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0*>(COUNTPARTSUPP3SUPPLIER1.index[1]);
          const HASH_RES_t h5 = COUNTPARTSUPP3SUPPLIER1_mapkey0_idxfn::hash(se10.modify0(supplier_nationkey));
          HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0::IdxNode* n6 = static_cast<HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0::IdxNode*>(i6->slice(se10, h5));
          COUNTPARTSUPP3SUPPLIER1_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              STRING_TYPE n_name = e6->N_NAME;
              long v6 = e6->__av;
              COUNTPARTSUPP3.addOrDelOnZero(se9.modify(supplier_suppkey,supplier_name,supplier_address,supplier_phone,supplier_acctbal,supplier_comment,n_name),v6);
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h5 == n6->hash &&  COUNTPARTSUPP3SUPPLIER1_mapkey0_idxfn::equals(se10, *e6)); 
          }
        }COUNTPARTSUPP4_L2_3.addOrDelOnZero(se11.modify(supplier_suppkey),COUNTPARTSUPP4_L2_3SUPPLIER1.getValueOrDefault(se12.modify(supplier_nationkey)));
        { //slice 
          const HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0* i7 = static_cast<HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0*>(COUNTPARTSUPP3SUPPLIER1.index[1]);
          const HASH_RES_t h7 = COUNTPARTSUPP3SUPPLIER1_mapkey0_idxfn::hash(se15.modify0(supplier_nationkey));
          HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0::IdxNode* n7 = static_cast<HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0::IdxNode*>(i7->slice(se15, h7));
          COUNTPARTSUPP3SUPPLIER1_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              STRING_TYPE n_name = e7->N_NAME;
              long v7 = e7->__av;
              { //slice 
                const HashIndex_COUNTSUPPLIER1SUPPLIER2_map_1* i8 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER2_map_1*>(COUNTSUPPLIER1SUPPLIER2.index[1]);
                const HASH_RES_t h6 = COUNTSUPPLIER1SUPPLIER2_mapkey1_idxfn::hash(se14.modify1(supplier_suppkey));
                HashIndex_COUNTSUPPLIER1SUPPLIER2_map_1::IdxNode* n8 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER2_map_1::IdxNode*>(i8->slice(se14, h6));
                COUNTSUPPLIER1SUPPLIER2_entry* e8;
               
                if (n8 && (e8 = n8->obj)) {
                  do {                
                    long p_partkey = e8->P_PARTKEY;
                    DOUBLE_TYPE ps_supplycost = e8->PS_SUPPLYCOST;
                    STRING_TYPE p_mfgr = e8->P_MFGR;
                    long v8 = e8->__av;
                    COUNTSUPPLIER1.addOrDelOnZero(se13.modify(p_partkey,p_mfgr,supplier_name,supplier_address,supplier_phone,supplier_acctbal,supplier_comment,ps_supplycost,n_name),(v7 * v8));
                    n8 = n8->nxt;
                  } while (n8 && (e8 = n8->obj) && h6 == n8->hash &&  COUNTSUPPLIER1SUPPLIER2_mapkey1_idxfn::equals(se14, *e8)); 
                }
              }
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h7 == n7->hash &&  COUNTPARTSUPP3SUPPLIER1_mapkey0_idxfn::equals(se15, *e7)); 
          }
        }{ //slice 
          const HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0* i9 = static_cast<HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0*>(COUNTPARTSUPP3SUPPLIER1.index[1]);
          const HASH_RES_t h9 = COUNTPARTSUPP3SUPPLIER1_mapkey0_idxfn::hash(se18.modify0(supplier_nationkey));
          HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0::IdxNode* n9 = static_cast<HashIndex_COUNTPARTSUPP3SUPPLIER1_map_0::IdxNode*>(i9->slice(se18, h9));
          COUNTPARTSUPP3SUPPLIER1_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              STRING_TYPE n_name = e9->N_NAME;
              long v9 = e9->__av;
              { //slice 
                const HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_1* i10 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_1*>(COUNTSUPPLIER1SUPPLIER2PART3.index[2]);
                const HASH_RES_t h8 = COUNTSUPPLIER1SUPPLIER2PART3_mapkey1_idxfn::hash(se17.modify1(supplier_suppkey));
                HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_1::IdxNode* n10 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_1::IdxNode*>(i10->slice(se17, h8));
                COUNTSUPPLIER1SUPPLIER2PART3_entry* e10;
               
                if (n10 && (e10 = n10->obj)) {
                  do {                
                    long countpartpart_partkey = e10->COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY;
                    DOUBLE_TYPE ps_supplycost = e10->PS_SUPPLYCOST;
                    long v10 = e10->__av;
                    COUNTPART3.addOrDelOnZero(se16.modify(countpartpart_partkey,ps_supplycost,supplier_name,supplier_address,supplier_phone,supplier_acctbal,supplier_comment,n_name),(v9 * v10));
                    n10 = n10->nxt;
                  } while (n10 && (e10 = n10->obj) && h8 == n10->hash &&  COUNTSUPPLIER1SUPPLIER2PART3_mapkey1_idxfn::equals(se17, *e10)); 
                }
              }
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h9 == n9->hash &&  COUNTPARTSUPP3SUPPLIER1_mapkey0_idxfn::equals(se18, *e9)); 
          }
        }{ //slice 
          const HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_1* i11 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_1*>(COUNTSUPPLIER1SUPPLIER2PART3.index[2]);
          const HASH_RES_t h10 = COUNTSUPPLIER1SUPPLIER2PART3_mapkey1_idxfn::hash(se21.modify1(supplier_suppkey));
          HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_1::IdxNode* n11 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER2PART3_map_1::IdxNode*>(i11->slice(se21, h10));
          COUNTSUPPLIER1SUPPLIER2PART3_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              long countpartpart_partkey = e11->COUNTSUPPLIER1SUPPLIER2PARTPART_PARTKEY;
              DOUBLE_TYPE ps2_supplycost = e11->PS_SUPPLYCOST;
              long v11 = e11->__av;
              COUNTPART3_L2_1.addOrDelOnZero(se19.modify(countpartpart_partkey,ps2_supplycost),(COUNTPARTSUPP4_L2_3SUPPLIER1.getValueOrDefault(se20.modify(supplier_nationkey)) * v11));
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h10 == n11->hash &&  COUNTSUPPLIER1SUPPLIER2PART3_mapkey1_idxfn::equals(se21, *e11)); 
          }
        }COUNT.clear();
        long l2 = 0L;
        {  // foreach
          const HashIndex_COUNTSUPPLIER1_map_012345678* i12 = static_cast<HashIndex_COUNTSUPPLIER1_map_012345678*>(COUNTSUPPLIER1.index[0]);
          HashIndex_COUNTSUPPLIER1_map_012345678::IdxNode* n12; 
          COUNTSUPPLIER1_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long p_partkey = e12->P_PARTKEY;
                STRING_TYPE p_mfgr = e12->P_MFGR;
                STRING_TYPE s_name = e12->S_NAME;
                STRING_TYPE s_address = e12->S_ADDRESS;
                STRING_TYPE s_phone = e12->S_PHONE;
                DOUBLE_TYPE s_acctbal = e12->S_ACCTBAL;
                STRING_TYPE s_comment = e12->S_COMMENT;
                DOUBLE_TYPE ps_supplycost = e12->PS_SUPPLYCOST;
                STRING_TYPE n_name = e12->N_NAME;
                long v12 = e12->__av;
                long agg3 = 0L;
                { //slice 
                  const HashIndex_COUNTPART3_L2_1_map_0* i13 = static_cast<HashIndex_COUNTPART3_L2_1_map_0*>(COUNTPART3_L2_1.index[1]);
                  const HASH_RES_t h11 = COUNTPART3_L2_1_mapkey0_idxfn::hash(se23.modify0(p_partkey));
                  HashIndex_COUNTPART3_L2_1_map_0::IdxNode* n13 = static_cast<HashIndex_COUNTPART3_L2_1_map_0::IdxNode*>(i13->slice(se23, h11));
                  COUNTPART3_L2_1_entry* e13;
                 
                  if (n13 && (e13 = n13->obj)) {
                    do {                
                      DOUBLE_TYPE ps2_supplycost = e13->PS2_SUPPLYCOST;
                      long v13 = e13->__av;
                      (/*if */(ps_supplycost > ps2_supplycost) ? agg3 += v13 : 0L);
                      n13 = n13->nxt;
                    } while (n13 && (e13 = n13->obj) && h11 == n13->hash &&  COUNTPART3_L2_1_mapkey0_idxfn::equals(se23, *e13)); 
                  }
                }(/*if */(l2 == agg3) ? COUNT.addOrDelOnZero(se22.modify(s_acctbal,s_name,n_name,p_partkey,p_mfgr,s_address,s_phone,s_comment),v12) : (void)0);
              n12 = n12->nxt;
            }
          }
        }
      }
    }
    void on_insert_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        _c1.clear();
        long l3 = 0L;
        { //slice 
          const HashIndex_COUNTPART3_map_0* i14 = static_cast<HashIndex_COUNTPART3_map_0*>(COUNTPART3.index[1]);
          const HASH_RES_t h13 = COUNTPART3_mapkey0_idxfn::hash(se27.modify0(partsupp_partkey));
          HashIndex_COUNTPART3_map_0::IdxNode* n14 = static_cast<HashIndex_COUNTPART3_map_0::IdxNode*>(i14->slice(se27, h13));
          COUNTPART3_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              DOUBLE_TYPE ps_supplycost = e14->PS_SUPPLYCOST;
              STRING_TYPE s_name = e14->S_NAME;
              STRING_TYPE s_address = e14->S_ADDRESS;
              STRING_TYPE s_phone = e14->S_PHONE;
              DOUBLE_TYPE s_acctbal = e14->S_ACCTBAL;
              STRING_TYPE s_comment = e14->S_COMMENT;
              STRING_TYPE n_name = e14->N_NAME;
              long v15 = e14->__av;
              long agg4 = 0L;
              { //slice 
                const HashIndex_COUNTPART3_L2_1_map_0* i15 = static_cast<HashIndex_COUNTPART3_L2_1_map_0*>(COUNTPART3_L2_1.index[1]);
                const HASH_RES_t h12 = COUNTPART3_L2_1_mapkey0_idxfn::hash(se25.modify0(partsupp_partkey));
                HashIndex_COUNTPART3_L2_1_map_0::IdxNode* n15 = static_cast<HashIndex_COUNTPART3_L2_1_map_0::IdxNode*>(i15->slice(se25, h12));
                COUNTPART3_L2_1_entry* e15;
               
                if (n15 && (e15 = n15->obj)) {
                  do {                
                    DOUBLE_TYPE ps2_supplycost = e15->PS2_SUPPLYCOST;
                    long v16 = e15->__av;
                    (/*if */(ps_supplycost > ps2_supplycost) ? agg4 += v16 : 0L);
                    n15 = n15->nxt;
                  } while (n15 && (e15 = n15->obj) && h12 == n15->hash &&  COUNTPART3_L2_1_mapkey0_idxfn::equals(se25, *e15)); 
                }
              }(/*if */(l3 == (agg4 + (/*if */(ps_supplycost > partsupp_supplycost) ? COUNTPARTSUPP4_L2_3.getValueOrDefault(se26.modify(partsupp_suppkey)) : 0L))) ? _c1.addOrDelOnZero(st2.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,v15), v15) : (void)0);
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h13 == n14->hash &&  COUNTPART3_mapkey0_idxfn::equals(se27, *e14)); 
          }
        }long agg5 = 0L;
        long agg6 = 0L;
        { //slice 
          const HashIndex_COUNTPART3_L2_1_map_0* i16 = static_cast<HashIndex_COUNTPART3_L2_1_map_0*>(COUNTPART3_L2_1.index[1]);
          const HASH_RES_t h14 = COUNTPART3_L2_1_mapkey0_idxfn::hash(se28.modify0(partsupp_partkey));
          HashIndex_COUNTPART3_L2_1_map_0::IdxNode* n16 = static_cast<HashIndex_COUNTPART3_L2_1_map_0::IdxNode*>(i16->slice(se28, h14));
          COUNTPART3_L2_1_entry* e16;
         
          if (n16 && (e16 = n16->obj)) {
            do {                
              DOUBLE_TYPE ps2_supplycost = e16->PS2_SUPPLYCOST;
              long v17 = e16->__av;
              (/*if */(partsupp_supplycost > ps2_supplycost) ? agg6 += v17 : 0L);
              n16 = n16->nxt;
            } while (n16 && (e16 = n16->obj) && h14 == n16->hash &&  COUNTPART3_L2_1_mapkey0_idxfn::equals(se28, *e16)); 
          }
        }long l4 = agg6;
        (/*if */(l4 == 0L) ? agg5 += 1L : 0L);
        { //slice 
          const HashIndex_COUNTPARTSUPP3_map_0* i17 = static_cast<HashIndex_COUNTPARTSUPP3_map_0*>(COUNTPARTSUPP3.index[1]);
          const HASH_RES_t h15 = COUNTPARTSUPP3_mapkey0_idxfn::hash(se29.modify0(partsupp_suppkey));
          HashIndex_COUNTPARTSUPP3_map_0::IdxNode* n17 = static_cast<HashIndex_COUNTPARTSUPP3_map_0::IdxNode*>(i17->slice(se29, h15));
          COUNTPARTSUPP3_entry* e17;
         
          if (n17 && (e17 = n17->obj)) {
            do {                
              STRING_TYPE s_name = e17->S_NAME;
              STRING_TYPE s_address = e17->S_ADDRESS;
              STRING_TYPE s_phone = e17->S_PHONE;
              DOUBLE_TYPE s_acctbal = e17->S_ACCTBAL;
              STRING_TYPE s_comment = e17->S_COMMENT;
              STRING_TYPE n_name = e17->N_NAME;
              long v18 = e17->__av;
              _c1.addOrDelOnZero(st3.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,(agg5 * v18)), (agg5 * v18));
              n17 = n17->nxt;
            } while (n17 && (e17 = n17->obj) && h15 == n17->hash &&  COUNTPARTSUPP3_mapkey0_idxfn::equals(se29, *e17)); 
          }
        }long l5 = 0L;
        { //slice 
          const HashIndex_COUNTPART3_map_0* i18 = static_cast<HashIndex_COUNTPART3_map_0*>(COUNTPART3.index[1]);
          const HASH_RES_t h17 = COUNTPART3_mapkey0_idxfn::hash(se31.modify0(partsupp_partkey));
          HashIndex_COUNTPART3_map_0::IdxNode* n18 = static_cast<HashIndex_COUNTPART3_map_0::IdxNode*>(i18->slice(se31, h17));
          COUNTPART3_entry* e18;
         
          if (n18 && (e18 = n18->obj)) {
            do {                
              DOUBLE_TYPE ps_supplycost = e18->PS_SUPPLYCOST;
              STRING_TYPE s_name = e18->S_NAME;
              STRING_TYPE s_address = e18->S_ADDRESS;
              STRING_TYPE s_phone = e18->S_PHONE;
              DOUBLE_TYPE s_acctbal = e18->S_ACCTBAL;
              STRING_TYPE s_comment = e18->S_COMMENT;
              STRING_TYPE n_name = e18->N_NAME;
              long v19 = e18->__av;
              long agg7 = 0L;
              { //slice 
                const HashIndex_COUNTPART3_L2_1_map_0* i19 = static_cast<HashIndex_COUNTPART3_L2_1_map_0*>(COUNTPART3_L2_1.index[1]);
                const HASH_RES_t h16 = COUNTPART3_L2_1_mapkey0_idxfn::hash(se30.modify0(partsupp_partkey));
                HashIndex_COUNTPART3_L2_1_map_0::IdxNode* n19 = static_cast<HashIndex_COUNTPART3_L2_1_map_0::IdxNode*>(i19->slice(se30, h16));
                COUNTPART3_L2_1_entry* e19;
               
                if (n19 && (e19 = n19->obj)) {
                  do {                
                    DOUBLE_TYPE ps2_supplycost = e19->PS2_SUPPLYCOST;
                    long v20 = e19->__av;
                    (/*if */(ps_supplycost > ps2_supplycost) ? agg7 += v20 : 0L);
                    n19 = n19->nxt;
                  } while (n19 && (e19 = n19->obj) && h16 == n19->hash &&  COUNTPART3_L2_1_mapkey0_idxfn::equals(se30, *e19)); 
                }
              }(/*if */(l5 == agg7) ? _c1.addOrDelOnZero(st4.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,(v19 * -1L)), (v19 * -1L)) : (void)0);
              n18 = n18->nxt;
            } while (n18 && (e18 = n18->obj) && h17 == n18->hash &&  COUNTPART3_mapkey0_idxfn::equals(se31, *e18)); 
          }
        }{  // temp foreach
          const HashIndex<tuple7_SSSDSS_L, long>* i20 = static_cast<HashIndex<tuple7_SSSDSS_L, long>*>(_c1.index[0]);
          HashIndex<tuple7_SSSDSS_L, long>::IdxNode* n20; 
          tuple7_SSSDSS_L* e20;
        
          for (size_t i = 0; i < i20->size_; i++)
          {
            n20 = i20->buckets_ + i;
            while (n20 && (e20 = n20->obj))
            {
              STRING_TYPE s_name = e20->_1;
              STRING_TYPE s_address = e20->_2;
              STRING_TYPE s_phone = e20->_3;
              DOUBLE_TYPE s_acctbal = e20->_4;
              STRING_TYPE s_comment = e20->_5;
              STRING_TYPE n_name = e20->_6;  
              long v21 = e20->__av; 
            { //slice 
              const HashIndex_COUNTPARTSUPP2_map_0* i21 = static_cast<HashIndex_COUNTPARTSUPP2_map_0*>(COUNTPARTSUPP2.index[1]);
              const HASH_RES_t h18 = COUNTPARTSUPP2_mapkey0_idxfn::hash(se32.modify0(partsupp_partkey));
              HashIndex_COUNTPARTSUPP2_map_0::IdxNode* n21 = static_cast<HashIndex_COUNTPARTSUPP2_map_0::IdxNode*>(i21->slice(se32, h18));
              COUNTPARTSUPP2_entry* e21;
             
              if (n21 && (e21 = n21->obj)) {
                do {                
                  STRING_TYPE p_mfgr = e21->P_MFGR;
                  long v22 = e21->__av;
                  COUNT.addOrDelOnZero(se24.modify(s_acctbal,s_name,n_name,partsupp_partkey,p_mfgr,s_address,s_phone,s_comment),(v21 * v22));
                  n21 = n21->nxt;
                } while (n21 && (e21 = n21->obj) && h18 == n21->hash &&  COUNTPARTSUPP2_mapkey0_idxfn::equals(se32, *e21)); 
              }
            }      
              n20 = n20->nxt;
            }
          }
        }{ //slice 
          const HashIndex_COUNTPARTSUPP3_map_0* i22 = static_cast<HashIndex_COUNTPARTSUPP3_map_0*>(COUNTPARTSUPP3.index[1]);
          const HASH_RES_t h20 = COUNTPARTSUPP3_mapkey0_idxfn::hash(se35.modify0(partsupp_suppkey));
          HashIndex_COUNTPARTSUPP3_map_0::IdxNode* n22 = static_cast<HashIndex_COUNTPARTSUPP3_map_0::IdxNode*>(i22->slice(se35, h20));
          COUNTPARTSUPP3_entry* e22;
         
          if (n22 && (e22 = n22->obj)) {
            do {                
              STRING_TYPE s_name = e22->S_NAME;
              STRING_TYPE s_address = e22->S_ADDRESS;
              STRING_TYPE s_phone = e22->S_PHONE;
              DOUBLE_TYPE s_acctbal = e22->S_ACCTBAL;
              STRING_TYPE s_comment = e22->S_COMMENT;
              STRING_TYPE n_name = e22->N_NAME;
              long v23 = e22->__av;
              { //slice 
                const HashIndex_COUNTPARTSUPP2_map_0* i23 = static_cast<HashIndex_COUNTPARTSUPP2_map_0*>(COUNTPARTSUPP2.index[1]);
                const HASH_RES_t h19 = COUNTPARTSUPP2_mapkey0_idxfn::hash(se34.modify0(partsupp_partkey));
                HashIndex_COUNTPARTSUPP2_map_0::IdxNode* n23 = static_cast<HashIndex_COUNTPARTSUPP2_map_0::IdxNode*>(i23->slice(se34, h19));
                COUNTPARTSUPP2_entry* e23;
               
                if (n23 && (e23 = n23->obj)) {
                  do {                
                    STRING_TYPE p_mfgr = e23->P_MFGR;
                    long v24 = e23->__av;
                    COUNTSUPPLIER1.addOrDelOnZero(se33.modify(partsupp_partkey,p_mfgr,s_name,s_address,s_phone,s_acctbal,s_comment,partsupp_supplycost,n_name),(v23 * v24));
                    n23 = n23->nxt;
                  } while (n23 && (e23 = n23->obj) && h19 == n23->hash &&  COUNTPARTSUPP2_mapkey0_idxfn::equals(se34, *e23)); 
                }
              }
              n22 = n22->nxt;
            } while (n22 && (e22 = n22->obj) && h20 == n22->hash &&  COUNTPARTSUPP3_mapkey0_idxfn::equals(se35, *e22)); 
          }
        }{ //slice 
          const HashIndex_COUNTPARTSUPP2_map_0* i24 = static_cast<HashIndex_COUNTPARTSUPP2_map_0*>(COUNTPARTSUPP2.index[1]);
          const HASH_RES_t h21 = COUNTPARTSUPP2_mapkey0_idxfn::hash(se37.modify0(partsupp_partkey));
          HashIndex_COUNTPARTSUPP2_map_0::IdxNode* n24 = static_cast<HashIndex_COUNTPARTSUPP2_map_0::IdxNode*>(i24->slice(se37, h21));
          COUNTPARTSUPP2_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              STRING_TYPE p_mfgr = e24->P_MFGR;
              long v25 = e24->__av;
              COUNTSUPPLIER1SUPPLIER2.addOrDelOnZero(se36.modify(partsupp_partkey,partsupp_suppkey,partsupp_supplycost,p_mfgr),v25);
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h21 == n24->hash &&  COUNTPARTSUPP2_mapkey0_idxfn::equals(se37, *e24)); 
          }
        }COUNTSUPPLIER1SUPPLIER2PART3.addOrDelOnZero(se38.modify(partsupp_partkey,partsupp_suppkey,partsupp_supplycost),1L);
        { //slice 
          const HashIndex_COUNTPARTSUPP3_map_0* i25 = static_cast<HashIndex_COUNTPARTSUPP3_map_0*>(COUNTPARTSUPP3.index[1]);
          const HASH_RES_t h22 = COUNTPARTSUPP3_mapkey0_idxfn::hash(se40.modify0(partsupp_suppkey));
          HashIndex_COUNTPARTSUPP3_map_0::IdxNode* n25 = static_cast<HashIndex_COUNTPARTSUPP3_map_0::IdxNode*>(i25->slice(se40, h22));
          COUNTPARTSUPP3_entry* e25;
         
          if (n25 && (e25 = n25->obj)) {
            do {                
              STRING_TYPE s_name = e25->S_NAME;
              STRING_TYPE s_address = e25->S_ADDRESS;
              STRING_TYPE s_phone = e25->S_PHONE;
              DOUBLE_TYPE s_acctbal = e25->S_ACCTBAL;
              STRING_TYPE s_comment = e25->S_COMMENT;
              STRING_TYPE n_name = e25->N_NAME;
              long v26 = e25->__av;
              COUNTPART3.addOrDelOnZero(se39.modify(partsupp_partkey,partsupp_supplycost,s_name,s_address,s_phone,s_acctbal,s_comment,n_name),v26);
              n25 = n25->nxt;
            } while (n25 && (e25 = n25->obj) && h22 == n25->hash &&  COUNTPARTSUPP3_mapkey0_idxfn::equals(se40, *e25)); 
          }
        }COUNTPART3_L2_1.addOrDelOnZero(se41.modify(partsupp_partkey,partsupp_supplycost),COUNTPARTSUPP4_L2_3.getValueOrDefault(se42.modify(partsupp_suppkey)));
      }
    }
    void on_system_ready_event() {
      {  
        COUNTPARTSUPP3SUPPLIER1.clear();
        STRING_TYPE l6 = c1;
        {  // foreach
          const HashIndex_NATION_map_0123* i26 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n26; 
          NATION_entry* e26;
        
          for (size_t i = 0; i < i26->size_; i++)
          {
            n26 = i26->buckets_ + i;
            while (n26 && (e26 = n26->obj))
            {
                long countpartsupp3suppliersupplier_nationkey = e26->NATION_NATIONKEY;
                STRING_TYPE n_name = e26->NATION_NAME;
                long n_regionkey = e26->NATION_REGIONKEY;
                STRING_TYPE n_comment = e26->NATION_COMMENT;
                long v27 = e26->__av;
                { //slice 
                  const HashIndex_REGION_map_01* i27 = static_cast<HashIndex_REGION_map_01*>(REGION.index[1]);
                  const HASH_RES_t h23 = REGION_mapkey01_idxfn::hash(se44.modify01(n_regionkey, l6));
                  HashIndex_REGION_map_01::IdxNode* n27 = static_cast<HashIndex_REGION_map_01::IdxNode*>(i27->slice(se44, h23));
                  REGION_entry* e27;
                 
                  if (n27 && (e27 = n27->obj)) {
                    do {                
                      STRING_TYPE r_comment = e27->REGION_COMMENT;
                      long v28 = e27->__av;
                      COUNTPARTSUPP3SUPPLIER1.addOrDelOnZero(se43.modify(countpartsupp3suppliersupplier_nationkey,n_name),(v27 * v28));
                      n27 = n27->nxt;
                    } while (n27 && (e27 = n27->obj) && h23 == n27->hash &&  REGION_mapkey01_idxfn::equals(se44, *e27)); 
                  }
                }
              n26 = n26->nxt;
            }
          }
        }COUNTPARTSUPP4_L2_3SUPPLIER1.clear();
        STRING_TYPE l7 = c1;
        {  // foreach
          const HashIndex_NATION_map_0123* i28 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n28; 
          NATION_entry* e28;
        
          for (size_t i = 0; i < i28->size_; i++)
          {
            n28 = i28->buckets_ + i;
            while (n28 && (e28 = n28->obj))
            {
                long countpartsupp4_l2_3suppliersupplier_nationkey = e28->NATION_NATIONKEY;
                STRING_TYPE n2_name = e28->NATION_NAME;
                long n2_regionkey = e28->NATION_REGIONKEY;
                STRING_TYPE n2_comment = e28->NATION_COMMENT;
                long v29 = e28->__av;
                { //slice 
                  const HashIndex_REGION_map_01* i29 = static_cast<HashIndex_REGION_map_01*>(REGION.index[1]);
                  const HASH_RES_t h24 = REGION_mapkey01_idxfn::hash(se46.modify01(n2_regionkey, l7));
                  HashIndex_REGION_map_01::IdxNode* n29 = static_cast<HashIndex_REGION_map_01::IdxNode*>(i29->slice(se46, h24));
                  REGION_entry* e29;
                 
                  if (n29 && (e29 = n29->obj)) {
                    do {                
                      STRING_TYPE r2_comment = e29->REGION_COMMENT;
                      long v30 = e29->__av;
                      COUNTPARTSUPP4_L2_3SUPPLIER1.addOrDelOnZero(se45.modify(countpartsupp4_l2_3suppliersupplier_nationkey),(v29 * v30));
                      n29 = n29->nxt;
                    } while (n29 && (e29 = n29->obj) && h24 == n29->hash &&  REGION_mapkey01_idxfn::equals(se46, *e29)); 
                  }
                }
              n28 = n28->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNT_entry se1;
    COUNTPART3_L2_1_entry se2;
    tuple7_SSSDSS_L st1;
    COUNTPART3_entry se3;
    COUNTPARTSUPP2_entry se4;
    COUNTSUPPLIER1_entry se5;
    COUNTPART3_entry se6;
    COUNTSUPPLIER1SUPPLIER2_entry se7;
    COUNTSUPPLIER1SUPPLIER2PART3_entry se8;
    COUNTPARTSUPP3_entry se9;
    COUNTPARTSUPP3SUPPLIER1_entry se10;
    COUNTPARTSUPP4_L2_3_entry se11;
    COUNTPARTSUPP4_L2_3SUPPLIER1_entry se12;
    COUNTSUPPLIER1_entry se13;
    COUNTSUPPLIER1SUPPLIER2_entry se14;
    COUNTPARTSUPP3SUPPLIER1_entry se15;
    COUNTPART3_entry se16;
    COUNTSUPPLIER1SUPPLIER2PART3_entry se17;
    COUNTPARTSUPP3SUPPLIER1_entry se18;
    COUNTPART3_L2_1_entry se19;
    COUNTPARTSUPP4_L2_3SUPPLIER1_entry se20;
    COUNTSUPPLIER1SUPPLIER2PART3_entry se21;
    COUNT_entry se22;
    COUNTPART3_L2_1_entry se23;
    COUNT_entry se24;
    COUNTPART3_L2_1_entry se25;
    COUNTPARTSUPP4_L2_3_entry se26;
    tuple7_SSSDSS_L st2;
    COUNTPART3_entry se27;
    COUNTPART3_L2_1_entry se28;
    tuple7_SSSDSS_L st3;
    COUNTPARTSUPP3_entry se29;
    COUNTPART3_L2_1_entry se30;
    tuple7_SSSDSS_L st4;
    COUNTPART3_entry se31;
    COUNTPARTSUPP2_entry se32;
    COUNTSUPPLIER1_entry se33;
    COUNTPARTSUPP2_entry se34;
    COUNTPARTSUPP3_entry se35;
    COUNTSUPPLIER1SUPPLIER2_entry se36;
    COUNTPARTSUPP2_entry se37;
    COUNTSUPPLIER1SUPPLIER2PART3_entry se38;
    COUNTPART3_entry se39;
    COUNTPARTSUPP3_entry se40;
    COUNTPART3_L2_1_entry se41;
    COUNTPARTSUPP4_L2_3_entry se42;
    COUNTPARTSUPP3SUPPLIER1_entry se43;
    REGION_entry se44;
    COUNTPARTSUPP4_L2_3SUPPLIER1_entry se45;
    REGION_entry se46;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REGION_map REGION;
    COUNTPARTSUPP2_map COUNTPARTSUPP2;
    COUNTPARTSUPP3_map COUNTPARTSUPP3;
    COUNTPARTSUPP3SUPPLIER1_map COUNTPARTSUPP3SUPPLIER1;
    COUNTPARTSUPP4_L2_3_map COUNTPARTSUPP4_L2_3;
    COUNTPARTSUPP4_L2_3SUPPLIER1_map COUNTPARTSUPP4_L2_3SUPPLIER1;
    COUNTSUPPLIER1_map COUNTSUPPLIER1;
    COUNTSUPPLIER1SUPPLIER2_map COUNTSUPPLIER1SUPPLIER2;
    COUNTSUPPLIER1SUPPLIER2PART3_map COUNTSUPPLIER1SUPPLIER2PART3;
    COUNTPART3_map COUNTPART3;
    COUNTPART3_L2_1_map COUNTPART3_L2_1;
    MultiHashMap<tuple7_SSSDSS_L,long,HashIndex<tuple7_SSSDSS_L,long> > _c1;
    MultiHashMap<tuple7_SSSDSS_L,long,HashIndex<tuple7_SSSDSS_L,long> > agg1;
    /*const static*/ STRING_TYPE c1;
  
  };

}
