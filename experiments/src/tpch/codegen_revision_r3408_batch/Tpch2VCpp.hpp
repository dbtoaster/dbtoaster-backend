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
  struct DELTA_PART_entry {
    long part_partkey; STRING_TYPE part_name; STRING_TYPE part_mfgr; STRING_TYPE part_brand; STRING_TYPE part_type; long part_size; STRING_TYPE part_container; DOUBLE_TYPE part_retailprice; STRING_TYPE part_comment; long __av; 
    explicit DELTA_PART_entry() { /*part_partkey = 0L; part_name = ""; part_mfgr = ""; part_brand = ""; part_type = ""; part_size = 0L; part_container = ""; part_retailprice = 0.0; part_comment = ""; __av = 0L; */ }
    explicit DELTA_PART_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const long c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8, const long c9) { part_partkey = c0; part_name = c1; part_mfgr = c2; part_brand = c3; part_type = c4; part_size = c5; part_container = c6; part_retailprice = c7; part_comment = c8; __av = c9; }
    DELTA_PART_entry(const DELTA_PART_entry& other) : part_partkey( other.part_partkey ), part_name( other.part_name ), part_mfgr( other.part_mfgr ), part_brand( other.part_brand ), part_type( other.part_type ), part_size( other.part_size ), part_container( other.part_container ), part_retailprice( other.part_retailprice ), part_comment( other.part_comment ), __av( other.__av ) {}
    FORCE_INLINE DELTA_PART_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const long c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8) { part_partkey = c0; part_name = c1; part_mfgr = c2; part_brand = c3; part_type = c4; part_size = c5; part_container = c6; part_retailprice = c7; part_comment = c8;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_mfgr);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_brand);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_type);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_size);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_container);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_retailprice);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_PART_mapkey012345678_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_PART_entry& e) {
      size_t h = 0;
      hash_combine(h, e.part_partkey);
      hash_combine(h, e.part_name);
      hash_combine(h, e.part_mfgr);
      hash_combine(h, e.part_brand);
      hash_combine(h, e.part_type);
      hash_combine(h, e.part_size);
      hash_combine(h, e.part_container);
      hash_combine(h, e.part_retailprice);
      hash_combine(h, e.part_comment);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_PART_entry& x, const DELTA_PART_entry& y) {
      return x.part_partkey == y.part_partkey && x.part_name == y.part_name && x.part_mfgr == y.part_mfgr && x.part_brand == y.part_brand && x.part_type == y.part_type && x.part_size == y.part_size && x.part_container == y.part_container && x.part_retailprice == y.part_retailprice && x.part_comment == y.part_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_PART_entry,long,
    HashIndex<DELTA_PART_entry,long,DELTA_PART_mapkey012345678_idxfn,true>
  > DELTA_PART_map;
  typedef HashIndex<DELTA_PART_entry,long,DELTA_PART_mapkey012345678_idxfn,true> HashIndex_DELTA_PART_map_012345678;
  
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
    FORCE_INLINE NATION_entry& modify2(const long c2) { NATION_REGIONKEY = c2;  return *this; }
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
  
  struct NATION_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const NATION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NATION_REGIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NATION_entry& x, const NATION_entry& y) {
      return x.NATION_REGIONKEY == y.NATION_REGIONKEY;
    }
  };
  
  typedef MultiHashMap<NATION_entry,long,
    HashIndex<NATION_entry,long,NATION_mapkey0123_idxfn,true>,
    HashIndex<NATION_entry,long,NATION_mapkey2_idxfn,false>
  > NATION_map;
  typedef HashIndex<NATION_entry,long,NATION_mapkey0123_idxfn,true> HashIndex_NATION_map_0123;
  typedef HashIndex<NATION_entry,long,NATION_mapkey2_idxfn,false> HashIndex_NATION_map_2;
  
  struct REGION_entry {
    long REGION_REGIONKEY; STRING_TYPE REGION_NAME; STRING_TYPE REGION_COMMENT; long __av; 
    explicit REGION_entry() { /*REGION_REGIONKEY = 0L; REGION_NAME = ""; REGION_COMMENT = ""; __av = 0L; */ }
    explicit REGION_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { REGION_REGIONKEY = c0; REGION_NAME = c1; REGION_COMMENT = c2; __av = c3; }
    REGION_entry(const REGION_entry& other) : REGION_REGIONKEY( other.REGION_REGIONKEY ), REGION_NAME( other.REGION_NAME ), REGION_COMMENT( other.REGION_COMMENT ), __av( other.__av ) {}
    FORCE_INLINE REGION_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { REGION_REGIONKEY = c0; REGION_NAME = c1; REGION_COMMENT = c2;  return *this; }
    FORCE_INLINE REGION_entry& modify01(const long c0, const STRING_TYPE& c1) { REGION_REGIONKEY = c0; REGION_NAME = c1;  return *this; }
    FORCE_INLINE REGION_entry& modify1(const STRING_TYPE& c1) { REGION_NAME = c1;  return *this; }
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
  
  struct REGION_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REGION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REGION_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REGION_entry& x, const REGION_entry& y) {
      return x.REGION_NAME == y.REGION_NAME;
    }
  };
  
  typedef MultiHashMap<REGION_entry,long,
    HashIndex<REGION_entry,long,REGION_mapkey012_idxfn,true>,
    HashIndex<REGION_entry,long,REGION_mapkey01_idxfn,false>,
    HashIndex<REGION_entry,long,REGION_mapkey1_idxfn,false>
  > REGION_map;
  typedef HashIndex<REGION_entry,long,REGION_mapkey012_idxfn,true> HashIndex_REGION_map_012;
  typedef HashIndex<REGION_entry,long,REGION_mapkey01_idxfn,false> HashIndex_REGION_map_01;
  typedef HashIndex<REGION_entry,long,REGION_mapkey1_idxfn,false> HashIndex_REGION_map_1;
  
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
  
  struct COUNTPARTSUPP1_DOMAIN1_entry {
    long P_PARTKEY; long __av; 
    explicit COUNTPARTSUPP1_DOMAIN1_entry() { /*P_PARTKEY = 0L; __av = 0L; */ }
    explicit COUNTPARTSUPP1_DOMAIN1_entry(const long c0, const long c1) { P_PARTKEY = c0; __av = c1; }
    COUNTPARTSUPP1_DOMAIN1_entry(const COUNTPARTSUPP1_DOMAIN1_entry& other) : P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP1_DOMAIN1_entry& modify(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_DOMAIN1_entry& x, const COUNTPARTSUPP1_DOMAIN1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP1_DOMAIN1_entry,long,
    HashIndex<COUNTPARTSUPP1_DOMAIN1_entry,long,COUNTPARTSUPP1_DOMAIN1_mapkey0_idxfn,true>
  > COUNTPARTSUPP1_DOMAIN1_map;
  typedef HashIndex<COUNTPARTSUPP1_DOMAIN1_entry,long,COUNTPARTSUPP1_DOMAIN1_mapkey0_idxfn,true> HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0;
  
  struct COUNTPARTSUPP1_P_1_entry {
    long P_PARTKEY; STRING_TYPE P_MFGR; long __av; 
    explicit COUNTPARTSUPP1_P_1_entry() { /*P_PARTKEY = 0L; P_MFGR = ""; __av = 0L; */ }
    explicit COUNTPARTSUPP1_P_1_entry(const long c0, const STRING_TYPE& c1, const long c2) { P_PARTKEY = c0; P_MFGR = c1; __av = c2; }
    COUNTPARTSUPP1_P_1_entry(const COUNTPARTSUPP1_P_1_entry& other) : P_PARTKEY( other.P_PARTKEY ), P_MFGR( other.P_MFGR ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP1_P_1_entry& modify(const long c0, const STRING_TYPE& c1) { P_PARTKEY = c0; P_MFGR = c1;  return *this; }
    FORCE_INLINE COUNTPARTSUPP1_P_1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_MFGR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.P_MFGR);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_P_1_entry& x, const COUNTPARTSUPP1_P_1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.P_MFGR == y.P_MFGR;
    }
  };
  
  struct COUNTPARTSUPP1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_P_1_entry& x, const COUNTPARTSUPP1_P_1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP1_P_1_entry,long,
    HashIndex<COUNTPARTSUPP1_P_1_entry,long,COUNTPARTSUPP1_P_1_mapkey01_idxfn,true>,
    HashIndex<COUNTPARTSUPP1_P_1_entry,long,COUNTPARTSUPP1_P_1_mapkey0_idxfn,false>
  > COUNTPARTSUPP1_P_1_map;
  typedef HashIndex<COUNTPARTSUPP1_P_1_entry,long,COUNTPARTSUPP1_P_1_mapkey01_idxfn,true> HashIndex_COUNTPARTSUPP1_P_1_map_01;
  typedef HashIndex<COUNTPARTSUPP1_P_1_entry,long,COUNTPARTSUPP1_P_1_mapkey0_idxfn,false> HashIndex_COUNTPARTSUPP1_P_1_map_0;
  
  struct COUNTPARTSUPP1_L2_2_DELTA_entry {
    long P_PARTKEY; long PS2_SUPPKEY; DOUBLE_TYPE PS2_SUPPLYCOST; long __av; 
    explicit COUNTPARTSUPP1_L2_2_DELTA_entry() { /*P_PARTKEY = 0L; PS2_SUPPKEY = 0L; PS2_SUPPLYCOST = 0.0; __av = 0L; */ }
    explicit COUNTPARTSUPP1_L2_2_DELTA_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const long c3) { P_PARTKEY = c0; PS2_SUPPKEY = c1; PS2_SUPPLYCOST = c2; __av = c3; }
    COUNTPARTSUPP1_L2_2_DELTA_entry(const COUNTPARTSUPP1_L2_2_DELTA_entry& other) : P_PARTKEY( other.P_PARTKEY ), PS2_SUPPKEY( other.PS2_SUPPKEY ), PS2_SUPPLYCOST( other.PS2_SUPPLYCOST ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP1_L2_2_DELTA_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2) { P_PARTKEY = c0; PS2_SUPPKEY = c1; PS2_SUPPLYCOST = c2;  return *this; }
    FORCE_INLINE COUNTPARTSUPP1_L2_2_DELTA_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS2_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP1_L2_2_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_L2_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.PS2_SUPPKEY);
      hash_combine(h, e.PS2_SUPPLYCOST);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_L2_2_DELTA_entry& x, const COUNTPARTSUPP1_L2_2_DELTA_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.PS2_SUPPKEY == y.PS2_SUPPKEY && x.PS2_SUPPLYCOST == y.PS2_SUPPLYCOST;
    }
  };
  
  struct COUNTPARTSUPP1_L2_2_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_L2_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_L2_2_DELTA_entry& x, const COUNTPARTSUPP1_L2_2_DELTA_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP1_L2_2_DELTA_entry,long,
    HashIndex<COUNTPARTSUPP1_L2_2_DELTA_entry,long,COUNTPARTSUPP1_L2_2_DELTA_mapkey012_idxfn,true>,
    HashIndex<COUNTPARTSUPP1_L2_2_DELTA_entry,long,COUNTPARTSUPP1_L2_2_DELTA_mapkey0_idxfn,false>
  > COUNTPARTSUPP1_L2_2_DELTA_map;
  typedef HashIndex<COUNTPARTSUPP1_L2_2_DELTA_entry,long,COUNTPARTSUPP1_L2_2_DELTA_mapkey012_idxfn,true> HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012;
  typedef HashIndex<COUNTPARTSUPP1_L2_2_DELTA_entry,long,COUNTPARTSUPP1_L2_2_DELTA_mapkey0_idxfn,false> HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_0;
  
  struct COUNTPARTSUPP1_L2_2_entry {
    long PS2_SUPPKEY; long __av; 
    explicit COUNTPARTSUPP1_L2_2_entry() { /*PS2_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNTPARTSUPP1_L2_2_entry(const long c0, const long c1) { PS2_SUPPKEY = c0; __av = c1; }
    COUNTPARTSUPP1_L2_2_entry(const COUNTPARTSUPP1_L2_2_entry& other) : PS2_SUPPKEY( other.PS2_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP1_L2_2_entry& modify(const long c0) { PS2_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP1_L2_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_L2_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS2_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_L2_2_entry& x, const COUNTPARTSUPP1_L2_2_entry& y) {
      return x.PS2_SUPPKEY == y.PS2_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP1_L2_2_entry,long,
    HashIndex<COUNTPARTSUPP1_L2_2_entry,long,COUNTPARTSUPP1_L2_2_mapkey0_idxfn,true>
  > COUNTPARTSUPP1_L2_2_map;
  typedef HashIndex<COUNTPARTSUPP1_L2_2_entry,long,COUNTPARTSUPP1_L2_2_mapkey0_idxfn,true> HashIndex_COUNTPARTSUPP1_L2_2_map_0;
  
  struct COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry {
    long PS2_SUPPKEY; long S2_NATIONKEY; long __av; 
    explicit COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry() { /*PS2_SUPPKEY = 0L; S2_NATIONKEY = 0L; __av = 0L; */ }
    explicit COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry(const long c0, const long c1, const long c2) { PS2_SUPPKEY = c0; S2_NATIONKEY = c1; __av = c2; }
    COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry(const COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry& other) : PS2_SUPPKEY( other.PS2_SUPPKEY ), S2_NATIONKEY( other.S2_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry& modify(const long c0, const long c1) { PS2_SUPPKEY = c0; S2_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S2_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS2_SUPPKEY);
      hash_combine(h, e.S2_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry& x, const COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry& y) {
      return x.PS2_SUPPKEY == y.PS2_SUPPKEY && x.S2_NATIONKEY == y.S2_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry,long,
    HashIndex<COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry,long,COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_mapkey01_idxfn,true>
  > COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_map;
  typedef HashIndex<COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry,long,COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_mapkey01_idxfn,true> HashIndex_COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_map_01;
  
  struct COUNTPARTSUPP1_L2_2SUPPLIER1_entry {
    long S2_NATIONKEY; long __av; 
    explicit COUNTPARTSUPP1_L2_2SUPPLIER1_entry() { /*S2_NATIONKEY = 0L; __av = 0L; */ }
    explicit COUNTPARTSUPP1_L2_2SUPPLIER1_entry(const long c0, const long c1) { S2_NATIONKEY = c0; __av = c1; }
    COUNTPARTSUPP1_L2_2SUPPLIER1_entry(const COUNTPARTSUPP1_L2_2SUPPLIER1_entry& other) : S2_NATIONKEY( other.S2_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP1_L2_2SUPPLIER1_entry& modify(const long c0) { S2_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S2_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP1_L2_2SUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_L2_2SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S2_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_L2_2SUPPLIER1_entry& x, const COUNTPARTSUPP1_L2_2SUPPLIER1_entry& y) {
      return x.S2_NATIONKEY == y.S2_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP1_L2_2SUPPLIER1_entry,long,
    HashIndex<COUNTPARTSUPP1_L2_2SUPPLIER1_entry,long,COUNTPARTSUPP1_L2_2SUPPLIER1_mapkey0_idxfn,true>
  > COUNTPARTSUPP1_L2_2SUPPLIER1_map;
  typedef HashIndex<COUNTPARTSUPP1_L2_2SUPPLIER1_entry,long,COUNTPARTSUPP1_L2_2SUPPLIER1_mapkey0_idxfn,true> HashIndex_COUNTPARTSUPP1_L2_2SUPPLIER1_map_0;
  
  struct COUNTPARTSUPP4_P_2_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; DOUBLE_TYPE S_ACCTBAL; STRING_TYPE S_COMMENT; STRING_TYPE N_NAME; long __av; 
    explicit COUNTPARTSUPP4_P_2_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; S_ACCTBAL = 0.0; S_COMMENT = ""; N_NAME = ""; __av = 0L; */ }
    explicit COUNTPARTSUPP4_P_2_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const long c7) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; S_ACCTBAL = c4; S_COMMENT = c5; N_NAME = c6; __av = c7; }
    COUNTPARTSUPP4_P_2_entry(const COUNTPARTSUPP4_P_2_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), S_ACCTBAL( other.S_ACCTBAL ), S_COMMENT( other.S_COMMENT ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP4_P_2_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; S_ACCTBAL = c4; S_COMMENT = c5; N_NAME = c6;  return *this; }
    FORCE_INLINE COUNTPARTSUPP4_P_2_entry& modify0(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
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
  struct COUNTPARTSUPP4_P_2_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP4_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.S_ACCTBAL);
      hash_combine(h, e.S_COMMENT);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP4_P_2_entry& x, const COUNTPARTSUPP4_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE && x.S_ACCTBAL == y.S_ACCTBAL && x.S_COMMENT == y.S_COMMENT && x.N_NAME == y.N_NAME;
    }
  };
  
  struct COUNTPARTSUPP4_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP4_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP4_P_2_entry& x, const COUNTPARTSUPP4_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP4_P_2_entry,long,
    HashIndex<COUNTPARTSUPP4_P_2_entry,long,COUNTPARTSUPP4_P_2_mapkey0123456_idxfn,true>,
    HashIndex<COUNTPARTSUPP4_P_2_entry,long,COUNTPARTSUPP4_P_2_mapkey0_idxfn,false>
  > COUNTPARTSUPP4_P_2_map;
  typedef HashIndex<COUNTPARTSUPP4_P_2_entry,long,COUNTPARTSUPP4_P_2_mapkey0123456_idxfn,true> HashIndex_COUNTPARTSUPP4_P_2_map_0123456;
  typedef HashIndex<COUNTPARTSUPP4_P_2_entry,long,COUNTPARTSUPP4_P_2_mapkey0_idxfn,false> HashIndex_COUNTPARTSUPP4_P_2_map_0;
  
  struct COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; long S_NATIONKEY; STRING_TYPE S_PHONE; DOUBLE_TYPE S_ACCTBAL; STRING_TYPE S_COMMENT; long __av; 
    explicit COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; S_NATIONKEY = 0L; S_PHONE = ""; S_ACCTBAL = 0.0; S_COMMENT = ""; __av = 0L; */ }
    explicit COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const long c7) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_NATIONKEY = c3; S_PHONE = c4; S_ACCTBAL = c5; S_COMMENT = c6; __av = c7; }
    COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry(const COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_NATIONKEY( other.S_NATIONKEY ), S_PHONE( other.S_PHONE ), S_ACCTBAL( other.S_ACCTBAL ), S_COMMENT( other.S_COMMENT ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_NATIONKEY = c3; S_PHONE = c4; S_ACCTBAL = c5; S_COMMENT = c6;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_NATIONKEY);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.S_ACCTBAL);
      hash_combine(h, e.S_COMMENT);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry& x, const COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_NATIONKEY == y.S_NATIONKEY && x.S_PHONE == y.S_PHONE && x.S_ACCTBAL == y.S_ACCTBAL && x.S_COMMENT == y.S_COMMENT;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry,long,
    HashIndex<COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry,long,COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_mapkey0123456_idxfn,true>
  > COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_map;
  typedef HashIndex<COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry,long,COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_mapkey0123456_idxfn,true> HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_map_0123456;
  
  struct COUNTPARTSUPP4_P_2SUPPLIER1_entry {
    long S_NATIONKEY; STRING_TYPE N_NAME; long __av; 
    explicit COUNTPARTSUPP4_P_2SUPPLIER1_entry() { /*S_NATIONKEY = 0L; N_NAME = ""; __av = 0L; */ }
    explicit COUNTPARTSUPP4_P_2SUPPLIER1_entry(const long c0, const STRING_TYPE& c1, const long c2) { S_NATIONKEY = c0; N_NAME = c1; __av = c2; }
    COUNTPARTSUPP4_P_2SUPPLIER1_entry(const COUNTPARTSUPP4_P_2SUPPLIER1_entry& other) : S_NATIONKEY( other.S_NATIONKEY ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP4_P_2SUPPLIER1_entry& modify(const long c0, const STRING_TYPE& c1) { S_NATIONKEY = c0; N_NAME = c1;  return *this; }
    FORCE_INLINE COUNTPARTSUPP4_P_2SUPPLIER1_entry& modify0(const long c0) { S_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP4_P_2SUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP4_P_2SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP4_P_2SUPPLIER1_entry& x, const COUNTPARTSUPP4_P_2SUPPLIER1_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  struct COUNTPARTSUPP4_P_2SUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP4_P_2SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP4_P_2SUPPLIER1_entry& x, const COUNTPARTSUPP4_P_2SUPPLIER1_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP4_P_2SUPPLIER1_entry,long,
    HashIndex<COUNTPARTSUPP4_P_2SUPPLIER1_entry,long,COUNTPARTSUPP4_P_2SUPPLIER1_mapkey01_idxfn,true>,
    HashIndex<COUNTPARTSUPP4_P_2SUPPLIER1_entry,long,COUNTPARTSUPP4_P_2SUPPLIER1_mapkey0_idxfn,false>
  > COUNTPARTSUPP4_P_2SUPPLIER1_map;
  typedef HashIndex<COUNTPARTSUPP4_P_2SUPPLIER1_entry,long,COUNTPARTSUPP4_P_2SUPPLIER1_mapkey01_idxfn,true> HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_01;
  typedef HashIndex<COUNTPARTSUPP4_P_2SUPPLIER1_entry,long,COUNTPARTSUPP4_P_2SUPPLIER1_mapkey0_idxfn,false> HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0;
  
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
  
  struct COUNTSUPPLIER1SUPPLIER1_P_1_entry {
    long P_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE PS_SUPPLYCOST; STRING_TYPE P_MFGR; long __av; 
    explicit COUNTSUPPLIER1SUPPLIER1_P_1_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; PS_SUPPLYCOST = 0.0; P_MFGR = ""; __av = 0L; */ }
    explicit COUNTSUPPLIER1SUPPLIER1_P_1_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3, const long c4) { P_PARTKEY = c0; S_SUPPKEY = c1; PS_SUPPLYCOST = c2; P_MFGR = c3; __av = c4; }
    COUNTSUPPLIER1SUPPLIER1_P_1_entry(const COUNTSUPPLIER1SUPPLIER1_P_1_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), PS_SUPPLYCOST( other.PS_SUPPLYCOST ), P_MFGR( other.P_MFGR ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1SUPPLIER1_P_1_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3) { P_PARTKEY = c0; S_SUPPKEY = c1; PS_SUPPLYCOST = c2; P_MFGR = c3;  return *this; }
    FORCE_INLINE COUNTSUPPLIER1SUPPLIER1_P_1_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_MFGR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1SUPPLIER1_P_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.PS_SUPPLYCOST);
      hash_combine(h, e.P_MFGR);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1SUPPLIER1_P_1_entry& x, const COUNTSUPPLIER1SUPPLIER1_P_1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.PS_SUPPLYCOST == y.PS_SUPPLYCOST && x.P_MFGR == y.P_MFGR;
    }
  };
  
  struct COUNTSUPPLIER1SUPPLIER1_P_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1SUPPLIER1_P_1_entry& x, const COUNTSUPPLIER1SUPPLIER1_P_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1SUPPLIER1_P_1_entry,long,
    HashIndex<COUNTSUPPLIER1SUPPLIER1_P_1_entry,long,COUNTSUPPLIER1SUPPLIER1_P_1_mapkey0123_idxfn,true>,
    HashIndex<COUNTSUPPLIER1SUPPLIER1_P_1_entry,long,COUNTSUPPLIER1SUPPLIER1_P_1_mapkey1_idxfn,false>
  > COUNTSUPPLIER1SUPPLIER1_P_1_map;
  typedef HashIndex<COUNTSUPPLIER1SUPPLIER1_P_1_entry,long,COUNTSUPPLIER1SUPPLIER1_P_1_mapkey0123_idxfn,true> HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1_map_0123;
  typedef HashIndex<COUNTSUPPLIER1SUPPLIER1_P_1_entry,long,COUNTSUPPLIER1SUPPLIER1_P_1_mapkey1_idxfn,false> HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1_map_1;
  
  struct COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry {
    long P_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE PS_SUPPLYCOST; long __av; 
    explicit COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; PS_SUPPLYCOST = 0.0; __av = 0L; */ }
    explicit COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const long c3) { P_PARTKEY = c0; S_SUPPKEY = c1; PS_SUPPLYCOST = c2; __av = c3; }
    COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry(const COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), PS_SUPPLYCOST( other.PS_SUPPLYCOST ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2) { P_PARTKEY = c0; S_SUPPKEY = c1; PS_SUPPLYCOST = c2;  return *this; }
    FORCE_INLINE COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    FORCE_INLINE COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.PS_SUPPLYCOST);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& x, const COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.PS_SUPPLYCOST == y.PS_SUPPLYCOST;
    }
  };
  
  struct COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& x, const COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& x, const COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry,long,
    HashIndex<COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry,long,COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey012_idxfn,true>,
    HashIndex<COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry,long,COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey0_idxfn,false>,
    HashIndex<COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry,long,COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey1_idxfn,false>
  > COUNTSUPPLIER1SUPPLIER1_P_1PART1_map;
  typedef HashIndex<COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry,long,COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey012_idxfn,true> HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_012;
  typedef HashIndex<COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry,long,COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey0_idxfn,false> HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_0;
  typedef HashIndex<COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry,long,COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey1_idxfn,false> HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_1;
  
  struct COUNTPART1_DELTA_entry {
    long P_PARTKEY; STRING_TYPE P_MFGR; long __av; 
    explicit COUNTPART1_DELTA_entry() { /*P_PARTKEY = 0L; P_MFGR = ""; __av = 0L; */ }
    explicit COUNTPART1_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { P_PARTKEY = c0; P_MFGR = c1; __av = c2; }
    COUNTPART1_DELTA_entry(const COUNTPART1_DELTA_entry& other) : P_PARTKEY( other.P_PARTKEY ), P_MFGR( other.P_MFGR ), __av( other.__av ) {}
    FORCE_INLINE COUNTPART1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { P_PARTKEY = c0; P_MFGR = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_MFGR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPART1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.P_MFGR);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPART1_DELTA_entry& x, const COUNTPART1_DELTA_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.P_MFGR == y.P_MFGR;
    }
  };
  
  typedef MultiHashMap<COUNTPART1_DELTA_entry,long,
    HashIndex<COUNTPART1_DELTA_entry,long,COUNTPART1_DELTA_mapkey01_idxfn,true>
  > COUNTPART1_DELTA_map;
  typedef HashIndex<COUNTPART1_DELTA_entry,long,COUNTPART1_DELTA_mapkey01_idxfn,true> HashIndex_COUNTPART1_DELTA_map_01;
  
  struct COUNTPART1_entry {
    STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; DOUBLE_TYPE S_ACCTBAL; STRING_TYPE S_COMMENT; long P_PARTKEY; DOUBLE_TYPE PS_SUPPLYCOST; STRING_TYPE N_NAME; long __av; 
    explicit COUNTPART1_entry() { /*S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; S_ACCTBAL = 0.0; S_COMMENT = ""; P_PARTKEY = 0L; PS_SUPPLYCOST = 0.0; N_NAME = ""; __av = 0L; */ }
    explicit COUNTPART1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const long c5, const DOUBLE_TYPE c6, const STRING_TYPE& c7, const long c8) { S_NAME = c0; S_ADDRESS = c1; S_PHONE = c2; S_ACCTBAL = c3; S_COMMENT = c4; P_PARTKEY = c5; PS_SUPPLYCOST = c6; N_NAME = c7; __av = c8; }
    COUNTPART1_entry(const COUNTPART1_entry& other) : S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), S_ACCTBAL( other.S_ACCTBAL ), S_COMMENT( other.S_COMMENT ), P_PARTKEY( other.P_PARTKEY ), PS_SUPPLYCOST( other.PS_SUPPLYCOST ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTPART1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const long c5, const DOUBLE_TYPE c6, const STRING_TYPE& c7) { S_NAME = c0; S_ADDRESS = c1; S_PHONE = c2; S_ACCTBAL = c3; S_COMMENT = c4; P_PARTKEY = c5; PS_SUPPLYCOST = c6; N_NAME = c7;  return *this; }
    FORCE_INLINE COUNTPART1_entry& modify5(const long c5) { P_PARTKEY = c5;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
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
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPART1_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.S_ACCTBAL);
      hash_combine(h, e.S_COMMENT);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.PS_SUPPLYCOST);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPART1_entry& x, const COUNTPART1_entry& y) {
      return x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE && x.S_ACCTBAL == y.S_ACCTBAL && x.S_COMMENT == y.S_COMMENT && x.P_PARTKEY == y.P_PARTKEY && x.PS_SUPPLYCOST == y.PS_SUPPLYCOST && x.N_NAME == y.N_NAME;
    }
  };
  
  struct COUNTPART1_mapkey5_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPART1_entry& x, const COUNTPART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPART1_entry,long,
    HashIndex<COUNTPART1_entry,long,COUNTPART1_mapkey01234567_idxfn,true>,
    HashIndex<COUNTPART1_entry,long,COUNTPART1_mapkey5_idxfn,false>
  > COUNTPART1_map;
  typedef HashIndex<COUNTPART1_entry,long,COUNTPART1_mapkey01234567_idxfn,true> HashIndex_COUNTPART1_map_01234567;
  typedef HashIndex<COUNTPART1_entry,long,COUNTPART1_mapkey5_idxfn,false> HashIndex_COUNTPART1_map_5;
  
  struct COUNTPART1_L2_1_entry {
    long P_PARTKEY; DOUBLE_TYPE PS2_SUPPLYCOST; long __av; 
    explicit COUNTPART1_L2_1_entry() { /*P_PARTKEY = 0L; PS2_SUPPLYCOST = 0.0; __av = 0L; */ }
    explicit COUNTPART1_L2_1_entry(const long c0, const DOUBLE_TYPE c1, const long c2) { P_PARTKEY = c0; PS2_SUPPLYCOST = c1; __av = c2; }
    COUNTPART1_L2_1_entry(const COUNTPART1_L2_1_entry& other) : P_PARTKEY( other.P_PARTKEY ), PS2_SUPPLYCOST( other.PS2_SUPPLYCOST ), __av( other.__av ) {}
    FORCE_INLINE COUNTPART1_L2_1_entry& modify(const long c0, const DOUBLE_TYPE c1) { P_PARTKEY = c0; PS2_SUPPLYCOST = c1;  return *this; }
    FORCE_INLINE COUNTPART1_L2_1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS2_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPART1_L2_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPART1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.PS2_SUPPLYCOST);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPART1_L2_1_entry& x, const COUNTPART1_L2_1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.PS2_SUPPLYCOST == y.PS2_SUPPLYCOST;
    }
  };
  
  struct COUNTPART1_L2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPART1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPART1_L2_1_entry& x, const COUNTPART1_L2_1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPART1_L2_1_entry,long,
    HashIndex<COUNTPART1_L2_1_entry,long,COUNTPART1_L2_1_mapkey01_idxfn,true>,
    HashIndex<COUNTPART1_L2_1_entry,long,COUNTPART1_L2_1_mapkey0_idxfn,false>
  > COUNTPART1_L2_1_map;
  typedef HashIndex<COUNTPART1_L2_1_entry,long,COUNTPART1_L2_1_mapkey01_idxfn,true> HashIndex_COUNTPART1_L2_1_map_01;
  typedef HashIndex<COUNTPART1_L2_1_entry,long,COUNTPART1_L2_1_mapkey0_idxfn,false> HashIndex_COUNTPART1_L2_1_map_0;
  
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
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
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
    void on_batch_update_PART(TPCHPartBatch& DELTA_PART) {
      {  
        if (tS > 0) { tS += DELTA_PART.size; return; }         
        tLastN += DELTA_PART.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_PART.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_PART.size;

        COUNTPART1_DELTA.clear();
        {
          for (size_t i = 0; i < DELTA_PART.size; i++) 
          {
                long p_partkey = DELTA_PART.partkey[i];
                STRING_TYPE p_name = DELTA_PART.name[i];
                STRING_TYPE p_mfgr = DELTA_PART.mfgr[i];
                STRING_TYPE p_brand = DELTA_PART.brand[i];
                STRING_TYPE p_type = DELTA_PART.type[i];
                long lift1 = DELTA_PART.psize[i];
                STRING_TYPE p_container = DELTA_PART.container[i];
                DOUBLE_TYPE p_retailprice = DELTA_PART.retailprice[i];
                STRING_TYPE p_comment = DELTA_PART.comment[i];
                long v1 = 1L;
                (/*if */(lift1 == 15L && 0L != Upreg_match(preg1,p_type)) ? COUNTPART1_DELTA.addOrDelOnZero(se1.modify(p_partkey,p_mfgr),v1) : (void)0);            
          }
        }

        {  // foreach
          const HashIndex_COUNTPART1_DELTA_map_01* i2 = static_cast<HashIndex_COUNTPART1_DELTA_map_01*>(COUNTPART1_DELTA.index[0]);
          HashIndex_COUNTPART1_DELTA_map_01::IdxNode* n2; 
          COUNTPART1_DELTA_entry* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
                long p_partkey = e2->P_PARTKEY;
                STRING_TYPE p_mfgr = e2->P_MFGR;
                long v2 = e2->__av;
                agg1.clear();
                
                long l1 = 0L;
                { //slice 
                  const HashIndex_COUNTPART1_map_5* i3 = static_cast<HashIndex_COUNTPART1_map_5*>(COUNTPART1.index[1]);
                  const HASH_RES_t h2 = COUNTPART1_mapkey5_idxfn::hash(se4.modify5(p_partkey));
                  HashIndex_COUNTPART1_map_5::IdxNode* n3 = static_cast<HashIndex_COUNTPART1_map_5::IdxNode*>(i3->slice(se4, h2));
                  COUNTPART1_entry* e3;
                 
                  if (n3 && (e3 = n3->obj)) {
                    do {                
                      STRING_TYPE s_name = e3->S_NAME;
                      STRING_TYPE s_address = e3->S_ADDRESS;
                      STRING_TYPE s_phone = e3->S_PHONE;
                      DOUBLE_TYPE s_acctbal = e3->S_ACCTBAL;
                      STRING_TYPE s_comment = e3->S_COMMENT;
                      DOUBLE_TYPE ps_supplycost = e3->PS_SUPPLYCOST;
                      STRING_TYPE n_name = e3->N_NAME;
                      long v3 = e3->__av;
                      long agg2 = 0L;
                      { //slice 
                        const HashIndex_COUNTPART1_L2_1_map_0* i4 = static_cast<HashIndex_COUNTPART1_L2_1_map_0*>(COUNTPART1_L2_1.index[1]);
                        const HASH_RES_t h1 = COUNTPART1_L2_1_mapkey0_idxfn::hash(se3.modify0(p_partkey));
                        HashIndex_COUNTPART1_L2_1_map_0::IdxNode* n4 = static_cast<HashIndex_COUNTPART1_L2_1_map_0::IdxNode*>(i4->slice(se3, h1));
                        COUNTPART1_L2_1_entry* e4;
                       
                        if (n4 && (e4 = n4->obj)) {
                          do {                
                            DOUBLE_TYPE ps2_supplycost = e4->PS2_SUPPLYCOST;
                            long v4 = e4->__av;
                            (/*if */(ps_supplycost > ps2_supplycost) ? agg2 += v4 : 0L);
                            n4 = n4->nxt;
                          } while (n4 && (e4 = n4->obj) && h1 == n4->hash &&  COUNTPART1_L2_1_mapkey0_idxfn::equals(se3, *e4)); 
                        }
                      }(/*if */(l1 == agg2) ? agg1.addOrDelOnZero(st1.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,v3), v3) : (void)0);
                      n3 = n3->nxt;
                    } while (n3 && (e3 = n3->obj) && h2 == n3->hash &&  COUNTPART1_mapkey5_idxfn::equals(se4, *e3)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple7_SSSDSS_L, long>* i5 = static_cast<HashIndex<tuple7_SSSDSS_L, long>*>(agg1.index[0]);
                  HashIndex<tuple7_SSSDSS_L, long>::IdxNode* n5; 
                  tuple7_SSSDSS_L* e5;
                
                  for (size_t i = 0; i < i5->size_; i++)
                  {
                    n5 = i5->buckets_ + i;
                    while (n5 && (e5 = n5->obj))
                    {
                      STRING_TYPE s_name = e5->_1;
                      STRING_TYPE s_address = e5->_2;
                      STRING_TYPE s_phone = e5->_3;
                      DOUBLE_TYPE s_acctbal = e5->_4;
                      STRING_TYPE s_comment = e5->_5;
                      STRING_TYPE n_name = e5->_6;  
                      long v5 = e5->__av; 
                    COUNT.addOrDelOnZero(se2.modify(s_acctbal,s_name,n_name,p_partkey,p_mfgr,s_address,s_phone,s_comment),(v2 * v5));      
                      n5 = n5->nxt;
                    }
                  }
                }
              n2 = n2->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTPART1_DELTA_map_01* i6 = static_cast<HashIndex_COUNTPART1_DELTA_map_01*>(COUNTPART1_DELTA.index[0]);
          HashIndex_COUNTPART1_DELTA_map_01::IdxNode* n6; 
          COUNTPART1_DELTA_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long p_partkey = e6->P_PARTKEY;
                STRING_TYPE p_mfgr = e6->P_MFGR;
                long v6 = e6->__av;
                COUNTPARTSUPP1_P_1.addOrDelOnZero(se5.modify(p_partkey,p_mfgr),v6);
              n6 = n6->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTPART1_DELTA_map_01* i7 = static_cast<HashIndex_COUNTPART1_DELTA_map_01*>(COUNTPART1_DELTA.index[0]);
          HashIndex_COUNTPART1_DELTA_map_01::IdxNode* n7; 
          COUNTPART1_DELTA_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long p_partkey = e7->P_PARTKEY;
                STRING_TYPE p_mfgr = e7->P_MFGR;
                long v7 = e7->__av;
                { //slice 
                  const HashIndex_COUNTPART1_map_5* i8 = static_cast<HashIndex_COUNTPART1_map_5*>(COUNTPART1.index[1]);
                  const HASH_RES_t h3 = COUNTPART1_mapkey5_idxfn::hash(se7.modify5(p_partkey));
                  HashIndex_COUNTPART1_map_5::IdxNode* n8 = static_cast<HashIndex_COUNTPART1_map_5::IdxNode*>(i8->slice(se7, h3));
                  COUNTPART1_entry* e8;
                 
                  if (n8 && (e8 = n8->obj)) {
                    do {                
                      STRING_TYPE s_name = e8->S_NAME;
                      STRING_TYPE s_address = e8->S_ADDRESS;
                      STRING_TYPE s_phone = e8->S_PHONE;
                      DOUBLE_TYPE s_acctbal = e8->S_ACCTBAL;
                      STRING_TYPE s_comment = e8->S_COMMENT;
                      DOUBLE_TYPE ps_supplycost = e8->PS_SUPPLYCOST;
                      STRING_TYPE n_name = e8->N_NAME;
                      long v8 = e8->__av;
                      COUNTSUPPLIER1.addOrDelOnZero(se6.modify(p_partkey,p_mfgr,s_name,s_address,s_phone,s_acctbal,s_comment,ps_supplycost,n_name),(v7 * v8));
                      n8 = n8->nxt;
                    } while (n8 && (e8 = n8->obj) && h3 == n8->hash &&  COUNTPART1_mapkey5_idxfn::equals(se7, *e8)); 
                  }
                }
              n7 = n7->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTPART1_DELTA_map_01* i9 = static_cast<HashIndex_COUNTPART1_DELTA_map_01*>(COUNTPART1_DELTA.index[0]);
          HashIndex_COUNTPART1_DELTA_map_01::IdxNode* n9; 
          COUNTPART1_DELTA_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long p_partkey = e9->P_PARTKEY;
                STRING_TYPE p_mfgr = e9->P_MFGR;
                long v9 = e9->__av;
                { //slice 
                  const HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_0* i10 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_0*>(COUNTSUPPLIER1SUPPLIER1_P_1PART1.index[1]);
                  const HASH_RES_t h4 = COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey0_idxfn::hash(se9.modify0(p_partkey));
                  HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_0::IdxNode* n10 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_0::IdxNode*>(i10->slice(se9, h4));
                  COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry* e10;
                 
                  if (n10 && (e10 = n10->obj)) {
                    do {                
                      long s_suppkey = e10->S_SUPPKEY;
                      DOUBLE_TYPE ps_supplycost = e10->PS_SUPPLYCOST;
                      long v10 = e10->__av;
                      COUNTSUPPLIER1SUPPLIER1_P_1.addOrDelOnZero(se8.modify(p_partkey,s_suppkey,ps_supplycost,p_mfgr),(v9 * v10));
                      n10 = n10->nxt;
                    } while (n10 && (e10 = n10->obj) && h4 == n10->hash &&  COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey0_idxfn::equals(se9, *e10)); 
                  }
                }
              n9 = n9->nxt;
            }
          }
        }
      }
    }
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

        COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA.clear();
        COUNTPARTSUPP4_P_2SUPPLIER1_DELTA.clear();
        {
          for (size_t i = 0; i < DELTA_SUPPLIER.size; i++) 
          {
                long ps2_suppkey = DELTA_SUPPLIER.suppkey[i];
                STRING_TYPE s2_name = DELTA_SUPPLIER.name[i];
                STRING_TYPE s2_address = DELTA_SUPPLIER.address[i];
                long s2_nationkey = DELTA_SUPPLIER.nationkey[i];
                STRING_TYPE s2_phone = DELTA_SUPPLIER.phone[i];
                DOUBLE_TYPE s2_acctbal = DELTA_SUPPLIER.acctbal[i];
                STRING_TYPE s2_comment = DELTA_SUPPLIER.comment[i];
                long v11 = 1L;
                COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA.addOrDelOnZero(se10.modify(ps2_suppkey,s2_nationkey),v11);
                long v12 = 1L;
                COUNTPARTSUPP4_P_2SUPPLIER1_DELTA.addOrDelOnZero(se11.modify(ps2_suppkey,s2_name,s2_address,s2_nationkey,s2_phone,s2_acctbal,s2_comment),v12);

          }
        }

        {  // foreach
          const HashIndex_COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_map_01* i13 = static_cast<HashIndex_COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_map_01*>(COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA.index[0]);
          HashIndex_COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_map_01::IdxNode* n13; 
          COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long ps2_suppkey = e13->PS2_SUPPKEY;
                long s2_nationkey = e13->S2_NATIONKEY;
                long v13 = e13->__av;
                COUNTPARTSUPP1_L2_2.addOrDelOnZero(se12.modify(ps2_suppkey),(v13 * COUNTPARTSUPP1_L2_2SUPPLIER1.getValueOrDefault(se13.modify(s2_nationkey))));
              n13 = n13->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_map_0123456* i14 = static_cast<HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_map_0123456*>(COUNTPARTSUPP4_P_2SUPPLIER1_DELTA.index[0]);
          HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_map_0123456::IdxNode* n14; 
          COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
                long s_suppkey = e14->S_SUPPKEY;
                STRING_TYPE s_name = e14->S_NAME;
                STRING_TYPE s_address = e14->S_ADDRESS;
                long s_nationkey = e14->S_NATIONKEY;
                STRING_TYPE s_phone = e14->S_PHONE;
                DOUBLE_TYPE s_acctbal = e14->S_ACCTBAL;
                STRING_TYPE s_comment = e14->S_COMMENT;
                long v14 = e14->__av;
                { //slice 
                  const HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0* i15 = static_cast<HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0*>(COUNTPARTSUPP4_P_2SUPPLIER1.index[1]);
                  const HASH_RES_t h5 = COUNTPARTSUPP4_P_2SUPPLIER1_mapkey0_idxfn::hash(se15.modify0(s_nationkey));
                  HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0::IdxNode* n15 = static_cast<HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0::IdxNode*>(i15->slice(se15, h5));
                  COUNTPARTSUPP4_P_2SUPPLIER1_entry* e15;
                 
                  if (n15 && (e15 = n15->obj)) {
                    do {                
                      STRING_TYPE n_name = e15->N_NAME;
                      long v15 = e15->__av;
                      COUNTPARTSUPP4_P_2.addOrDelOnZero(se14.modify(s_suppkey,s_name,s_address,s_phone,s_acctbal,s_comment,n_name),(v14 * v15));
                      n15 = n15->nxt;
                    } while (n15 && (e15 = n15->obj) && h5 == n15->hash &&  COUNTPARTSUPP4_P_2SUPPLIER1_mapkey0_idxfn::equals(se15, *e15)); 
                  }
                }
              n14 = n14->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_map_0123456* i16 = static_cast<HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_map_0123456*>(COUNTPARTSUPP4_P_2SUPPLIER1_DELTA.index[0]);
          HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_map_0123456::IdxNode* n16; 
          COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long s_suppkey = e16->S_SUPPKEY;
                STRING_TYPE s_name = e16->S_NAME;
                STRING_TYPE s_address = e16->S_ADDRESS;
                long s_nationkey = e16->S_NATIONKEY;
                STRING_TYPE s_phone = e16->S_PHONE;
                DOUBLE_TYPE s_acctbal = e16->S_ACCTBAL;
                STRING_TYPE s_comment = e16->S_COMMENT;
                long v16 = e16->__av;
                { //slice 
                  const HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1_map_1* i17 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1_map_1*>(COUNTSUPPLIER1SUPPLIER1_P_1.index[1]);
                  const HASH_RES_t h7 = COUNTSUPPLIER1SUPPLIER1_P_1_mapkey1_idxfn::hash(se18.modify1(s_suppkey));
                  HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1_map_1::IdxNode* n17 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1_map_1::IdxNode*>(i17->slice(se18, h7));
                  COUNTSUPPLIER1SUPPLIER1_P_1_entry* e17;
                 
                  if (n17 && (e17 = n17->obj)) {
                    do {                
                      long p_partkey = e17->P_PARTKEY;
                      DOUBLE_TYPE ps_supplycost = e17->PS_SUPPLYCOST;
                      STRING_TYPE p_mfgr = e17->P_MFGR;
                      long v17 = e17->__av;
                      { //slice 
                        const HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0* i18 = static_cast<HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0*>(COUNTPARTSUPP4_P_2SUPPLIER1.index[1]);
                        const HASH_RES_t h6 = COUNTPARTSUPP4_P_2SUPPLIER1_mapkey0_idxfn::hash(se17.modify0(s_nationkey));
                        HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0::IdxNode* n18 = static_cast<HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0::IdxNode*>(i18->slice(se17, h6));
                        COUNTPARTSUPP4_P_2SUPPLIER1_entry* e18;
                       
                        if (n18 && (e18 = n18->obj)) {
                          do {                
                            STRING_TYPE n_name = e18->N_NAME;
                            long v18 = e18->__av;
                            COUNTSUPPLIER1.addOrDelOnZero(se16.modify(p_partkey,p_mfgr,s_name,s_address,s_phone,s_acctbal,s_comment,ps_supplycost,n_name),(v16 * (v17 * v18)));
                            n18 = n18->nxt;
                          } while (n18 && (e18 = n18->obj) && h6 == n18->hash &&  COUNTPARTSUPP4_P_2SUPPLIER1_mapkey0_idxfn::equals(se17, *e18)); 
                        }
                      }
                      n17 = n17->nxt;
                    } while (n17 && (e17 = n17->obj) && h7 == n17->hash &&  COUNTSUPPLIER1SUPPLIER1_P_1_mapkey1_idxfn::equals(se18, *e17)); 
                  }
                }
              n16 = n16->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_map_0123456* i19 = static_cast<HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_map_0123456*>(COUNTPARTSUPP4_P_2SUPPLIER1_DELTA.index[0]);
          HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_map_0123456::IdxNode* n19; 
          COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long s_suppkey = e19->S_SUPPKEY;
                STRING_TYPE s_name = e19->S_NAME;
                STRING_TYPE s_address = e19->S_ADDRESS;
                long s_nationkey = e19->S_NATIONKEY;
                STRING_TYPE s_phone = e19->S_PHONE;
                DOUBLE_TYPE s_acctbal = e19->S_ACCTBAL;
                STRING_TYPE s_comment = e19->S_COMMENT;
                long v19 = e19->__av;
                { //slice 
                  const HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0* i20 = static_cast<HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0*>(COUNTPARTSUPP4_P_2SUPPLIER1.index[1]);
                  const HASH_RES_t h9 = COUNTPARTSUPP4_P_2SUPPLIER1_mapkey0_idxfn::hash(se21.modify0(s_nationkey));
                  HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0::IdxNode* n20 = static_cast<HashIndex_COUNTPARTSUPP4_P_2SUPPLIER1_map_0::IdxNode*>(i20->slice(se21, h9));
                  COUNTPARTSUPP4_P_2SUPPLIER1_entry* e20;
                 
                  if (n20 && (e20 = n20->obj)) {
                    do {                
                      STRING_TYPE n_name = e20->N_NAME;
                      long v20 = e20->__av;
                      { //slice 
                        const HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_1* i21 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_1*>(COUNTSUPPLIER1SUPPLIER1_P_1PART1.index[2]);
                        const HASH_RES_t h8 = COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey1_idxfn::hash(se20.modify1(s_suppkey));
                        HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_1::IdxNode* n21 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_1::IdxNode*>(i21->slice(se20, h8));
                        COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry* e21;
                       
                        if (n21 && (e21 = n21->obj)) {
                          do {                
                            long p_partkey = e21->P_PARTKEY;
                            DOUBLE_TYPE ps_supplycost = e21->PS_SUPPLYCOST;
                            long v21 = e21->__av;
                            COUNTPART1.addOrDelOnZero(se19.modify(s_name,s_address,s_phone,s_acctbal,s_comment,p_partkey,ps_supplycost,n_name),(v19 * (v20 * v21)));
                            n21 = n21->nxt;
                          } while (n21 && (e21 = n21->obj) && h8 == n21->hash &&  COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey1_idxfn::equals(se20, *e21)); 
                        }
                      }
                      n20 = n20->nxt;
                    } while (n20 && (e20 = n20->obj) && h9 == n20->hash &&  COUNTPARTSUPP4_P_2SUPPLIER1_mapkey0_idxfn::equals(se21, *e20)); 
                  }
                }
              n19 = n19->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_map_01* i22 = static_cast<HashIndex_COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_map_01*>(COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA.index[0]);
          HashIndex_COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_map_01::IdxNode* n22; 
          COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
                long ps2_suppkey = e22->PS2_SUPPKEY;
                long s2_nationkey = e22->S2_NATIONKEY;
                long v22 = e22->__av;
                { //slice 
                  const HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_1* i23 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_1*>(COUNTSUPPLIER1SUPPLIER1_P_1PART1.index[2]);
                  const HASH_RES_t h10 = COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey1_idxfn::hash(se24.modify1(ps2_suppkey));
                  HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_1::IdxNode* n23 = static_cast<HashIndex_COUNTSUPPLIER1SUPPLIER1_P_1PART1_map_1::IdxNode*>(i23->slice(se24, h10));
                  COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry* e23;
                 
                  if (n23 && (e23 = n23->obj)) {
                    do {                
                      long p_partkey = e23->P_PARTKEY;
                      DOUBLE_TYPE ps2_supplycost = e23->PS_SUPPLYCOST;
                      long v23 = e23->__av;
                      COUNTPART1_L2_1.addOrDelOnZero(se22.modify(p_partkey,ps2_supplycost),(v22 * (COUNTPARTSUPP1_L2_2SUPPLIER1.getValueOrDefault(se23.modify(s2_nationkey)) * v23)));
                      n23 = n23->nxt;
                    } while (n23 && (e23 = n23->obj) && h10 == n23->hash &&  COUNTSUPPLIER1SUPPLIER1_P_1PART1_mapkey1_idxfn::equals(se24, *e23)); 
                  }
                }
              n22 = n22->nxt;
            }
          }
        }COUNT.clear();
        long l2 = 0L;
        {  // foreach
          const HashIndex_COUNTSUPPLIER1_map_012345678* i24 = static_cast<HashIndex_COUNTSUPPLIER1_map_012345678*>(COUNTSUPPLIER1.index[0]);
          HashIndex_COUNTSUPPLIER1_map_012345678::IdxNode* n24; 
          COUNTSUPPLIER1_entry* e24;
        
          for (size_t i = 0; i < i24->size_; i++)
          {
            n24 = i24->buckets_ + i;
            while (n24 && (e24 = n24->obj))
            {
                long p_partkey = e24->P_PARTKEY;
                STRING_TYPE p_mfgr = e24->P_MFGR;
                STRING_TYPE s_name = e24->S_NAME;
                STRING_TYPE s_address = e24->S_ADDRESS;
                STRING_TYPE s_phone = e24->S_PHONE;
                DOUBLE_TYPE s_acctbal = e24->S_ACCTBAL;
                STRING_TYPE s_comment = e24->S_COMMENT;
                DOUBLE_TYPE ps_supplycost = e24->PS_SUPPLYCOST;
                STRING_TYPE n_name = e24->N_NAME;
                long v24 = e24->__av;
                long agg3 = 0L;
                { //slice 
                  const HashIndex_COUNTPART1_L2_1_map_0* i25 = static_cast<HashIndex_COUNTPART1_L2_1_map_0*>(COUNTPART1_L2_1.index[1]);
                  const HASH_RES_t h11 = COUNTPART1_L2_1_mapkey0_idxfn::hash(se26.modify0(p_partkey));
                  HashIndex_COUNTPART1_L2_1_map_0::IdxNode* n25 = static_cast<HashIndex_COUNTPART1_L2_1_map_0::IdxNode*>(i25->slice(se26, h11));
                  COUNTPART1_L2_1_entry* e25;
                 
                  if (n25 && (e25 = n25->obj)) {
                    do {                
                      DOUBLE_TYPE ps2_supplycost = e25->PS2_SUPPLYCOST;
                      long v25 = e25->__av;
                      (/*if */(ps_supplycost > ps2_supplycost) ? agg3 += v25 : 0L);
                      n25 = n25->nxt;
                    } while (n25 && (e25 = n25->obj) && h11 == n25->hash &&  COUNTPART1_L2_1_mapkey0_idxfn::equals(se26, *e25)); 
                  }
                }(/*if */(l2 == agg3) ? COUNT.addOrDelOnZero(se25.modify(s_acctbal,s_name,n_name,p_partkey,p_mfgr,s_address,s_phone,s_comment),v24) : (void)0);
              n24 = n24->nxt;
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

        COUNTPARTSUPP1_L2_2_DELTA.clear();
        COUNTPARTSUPP1_DOMAIN1.clear();
        { 
          for (size_t i = 0; i < DELTA_PARTSUPP.size; i++) 
          {
            long p_partkey = DELTA_PARTSUPP.partkey[i];
            long ps2_suppkey = DELTA_PARTSUPP.suppkey[i];
            // long ps2_availqty = DELTA_PARTSUPP.availqty[i];
            DOUBLE_TYPE ps2_supplycost = DELTA_PARTSUPP.supplycost[i];
            // STRING_TYPE ps2_comment = DELTA_PARTSUPP.comment[i];
            long v26 = 1L;
            COUNTPARTSUPP1_L2_2_DELTA.addOrDelOnZero(se27.modify(p_partkey,ps2_suppkey,ps2_supplycost),v26);
            long v27 = 1L;
            COUNTPARTSUPP1_DOMAIN1.addOrDelOnZero(se28.modify(p_partkey),(v27 != 0 ? 1L : 0L));

          }
        }

        {  // foreach
          const HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0* i28 = static_cast<HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0*>(COUNTPARTSUPP1_DOMAIN1.index[0]);
          HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0::IdxNode* n28; 
          COUNTPARTSUPP1_DOMAIN1_entry* e28;
        
          for (size_t i = 0; i < i28->size_; i++)
          {
            n28 = i28->buckets_ + i;
            while (n28 && (e28 = n28->obj))
            {
                long p_partkey = e28->P_PARTKEY;
                long v28 = e28->__av;
                { //slice 
                  const HashIndex_COUNTPARTSUPP1_P_1_map_0* i29 = static_cast<HashIndex_COUNTPARTSUPP1_P_1_map_0*>(COUNTPARTSUPP1_P_1.index[1]);
                  const HASH_RES_t h17 = COUNTPARTSUPP1_P_1_mapkey0_idxfn::hash(se36.modify0(p_partkey));
                  HashIndex_COUNTPARTSUPP1_P_1_map_0::IdxNode* n29 = static_cast<HashIndex_COUNTPARTSUPP1_P_1_map_0::IdxNode*>(i29->slice(se36, h17));
                  COUNTPARTSUPP1_P_1_entry* e29;
                 
                  if (n29 && (e29 = n29->obj)) {
                    do {                
                      STRING_TYPE p_mfgr = e29->P_MFGR;
                      long v29 = e29->__av;
                      _c1.clear();
                      long l3 = 0L;
                      { //slice 
                        const HashIndex_COUNTPART1_map_5* i30 = static_cast<HashIndex_COUNTPART1_map_5*>(COUNTPART1.index[1]);
                        const HASH_RES_t h14 = COUNTPART1_mapkey5_idxfn::hash(se33.modify5(p_partkey));
                        HashIndex_COUNTPART1_map_5::IdxNode* n30 = static_cast<HashIndex_COUNTPART1_map_5::IdxNode*>(i30->slice(se33, h14));
                        COUNTPART1_entry* e30;
                       
                        if (n30 && (e30 = n30->obj)) {
                          do {                
                            STRING_TYPE s_name = e30->S_NAME;
                            STRING_TYPE s_address = e30->S_ADDRESS;
                            STRING_TYPE s_phone = e30->S_PHONE;
                            DOUBLE_TYPE s_acctbal = e30->S_ACCTBAL;
                            STRING_TYPE s_comment = e30->S_COMMENT;
                            DOUBLE_TYPE ps_supplycost = e30->PS_SUPPLYCOST;
                            STRING_TYPE n_name = e30->N_NAME;
                            long v31 = e30->__av;
                            long agg4 = 0L;
                            { //slice 
                              const HashIndex_COUNTPART1_L2_1_map_0* i31 = static_cast<HashIndex_COUNTPART1_L2_1_map_0*>(COUNTPART1_L2_1.index[1]);
                              const HASH_RES_t h12 = COUNTPART1_L2_1_mapkey0_idxfn::hash(se30.modify0(p_partkey));
                              HashIndex_COUNTPART1_L2_1_map_0::IdxNode* n31 = static_cast<HashIndex_COUNTPART1_L2_1_map_0::IdxNode*>(i31->slice(se30, h12));
                              COUNTPART1_L2_1_entry* e31;
                             
                              if (n31 && (e31 = n31->obj)) {
                                do {                
                                  DOUBLE_TYPE ps2_supplycost = e31->PS2_SUPPLYCOST;
                                  long v32 = e31->__av;
                                  (/*if */(ps_supplycost > ps2_supplycost) ? agg4 += v32 : 0L);
                                  n31 = n31->nxt;
                                } while (n31 && (e31 = n31->obj) && h12 == n31->hash &&  COUNTPART1_L2_1_mapkey0_idxfn::equals(se30, *e31)); 
                              }
                            }long agg5 = 0L;
                            { //slice 
                              const HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_0* i32 = static_cast<HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_0*>(COUNTPARTSUPP1_L2_2_DELTA.index[1]);
                              const HASH_RES_t h13 = COUNTPARTSUPP1_L2_2_DELTA_mapkey0_idxfn::hash(se32.modify0(p_partkey));
                              HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_0::IdxNode* n32 = static_cast<HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_0::IdxNode*>(i32->slice(se32, h13));
                              COUNTPARTSUPP1_L2_2_DELTA_entry* e32;
                             
                              if (n32 && (e32 = n32->obj)) {
                                do {                
                                  long ps2_suppkey = e32->PS2_SUPPKEY;
                                  DOUBLE_TYPE ps2_supplycost = e32->PS2_SUPPLYCOST;
                                  long v33 = e32->__av;
                                  (/*if */(ps_supplycost > ps2_supplycost) ? agg5 += (v33 * COUNTPARTSUPP1_L2_2.getValueOrDefault(se31.modify(ps2_suppkey))) : 0L);
                                  n32 = n32->nxt;
                                } while (n32 && (e32 = n32->obj) && h13 == n32->hash &&  COUNTPARTSUPP1_L2_2_DELTA_mapkey0_idxfn::equals(se32, *e32)); 
                              }
                            }(/*if */(l3 == (agg4 + agg5)) ? _c1.addOrDelOnZero(st2.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,v31), v31) : (void)0);
                            n30 = n30->nxt;
                          } while (n30 && (e30 = n30->obj) && h14 == n30->hash &&  COUNTPART1_mapkey5_idxfn::equals(se33, *e30)); 
                        }
                      }long l4 = 0L;
                      { //slice 
                        const HashIndex_COUNTPART1_map_5* i33 = static_cast<HashIndex_COUNTPART1_map_5*>(COUNTPART1.index[1]);
                        const HASH_RES_t h16 = COUNTPART1_mapkey5_idxfn::hash(se35.modify5(p_partkey));
                        HashIndex_COUNTPART1_map_5::IdxNode* n33 = static_cast<HashIndex_COUNTPART1_map_5::IdxNode*>(i33->slice(se35, h16));
                        COUNTPART1_entry* e33;
                       
                        if (n33 && (e33 = n33->obj)) {
                          do {                
                            STRING_TYPE s_name = e33->S_NAME;
                            STRING_TYPE s_address = e33->S_ADDRESS;
                            STRING_TYPE s_phone = e33->S_PHONE;
                            DOUBLE_TYPE s_acctbal = e33->S_ACCTBAL;
                            STRING_TYPE s_comment = e33->S_COMMENT;
                            DOUBLE_TYPE ps_supplycost = e33->PS_SUPPLYCOST;
                            STRING_TYPE n_name = e33->N_NAME;
                            long v34 = e33->__av;
                            long agg6 = 0L;
                            { //slice 
                              const HashIndex_COUNTPART1_L2_1_map_0* i34 = static_cast<HashIndex_COUNTPART1_L2_1_map_0*>(COUNTPART1_L2_1.index[1]);
                              const HASH_RES_t h15 = COUNTPART1_L2_1_mapkey0_idxfn::hash(se34.modify0(p_partkey));
                              HashIndex_COUNTPART1_L2_1_map_0::IdxNode* n34 = static_cast<HashIndex_COUNTPART1_L2_1_map_0::IdxNode*>(i34->slice(se34, h15));
                              COUNTPART1_L2_1_entry* e34;
                             
                              if (n34 && (e34 = n34->obj)) {
                                do {                
                                  DOUBLE_TYPE ps2_supplycost = e34->PS2_SUPPLYCOST;
                                  long v35 = e34->__av;
                                  (/*if */(ps_supplycost > ps2_supplycost) ? agg6 += v35 : 0L);
                                  n34 = n34->nxt;
                                } while (n34 && (e34 = n34->obj) && h15 == n34->hash &&  COUNTPART1_L2_1_mapkey0_idxfn::equals(se34, *e34)); 
                              }
                            }(/*if */(l4 == agg6) ? _c1.addOrDelOnZero(st3.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,(v34 * -1L)), (v34 * -1L)) : (void)0);
                            n33 = n33->nxt;
                          } while (n33 && (e33 = n33->obj) && h16 == n33->hash &&  COUNTPART1_mapkey5_idxfn::equals(se35, *e33)); 
                        }
                      }{  // temp foreach
                        const HashIndex<tuple7_SSSDSS_L, long>* i35 = static_cast<HashIndex<tuple7_SSSDSS_L, long>*>(_c1.index[0]);
                        HashIndex<tuple7_SSSDSS_L, long>::IdxNode* n35; 
                        tuple7_SSSDSS_L* e35;
                      
                        for (size_t i = 0; i < i35->size_; i++)
                        {
                          n35 = i35->buckets_ + i;
                          while (n35 && (e35 = n35->obj))
                          {
                            STRING_TYPE s_name = e35->_1;
                            STRING_TYPE s_address = e35->_2;
                            STRING_TYPE s_phone = e35->_3;
                            DOUBLE_TYPE s_acctbal = e35->_4;
                            STRING_TYPE s_comment = e35->_5;
                            STRING_TYPE n_name = e35->_6;  
                            long v36 = e35->__av; 
                          COUNT.addOrDelOnZero(se29.modify(s_acctbal,s_name,n_name,p_partkey,p_mfgr,s_address,s_phone,s_comment),((v28 != 0 ? 1L : 0L) * (v29 * v36)));      
                            n35 = n35->nxt;
                          }
                        }
                      }
                      n29 = n29->nxt;
                    } while (n29 && (e29 = n29->obj) && h17 == n29->hash &&  COUNTPARTSUPP1_P_1_mapkey0_idxfn::equals(se36, *e29)); 
                  }
                }
              n28 = n28->nxt;
            }
          }
        }long l5 = 0L;
        {  // foreach
          const HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012* i36 = static_cast<HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012*>(COUNTPARTSUPP1_L2_2_DELTA.index[0]);
          HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012::IdxNode* n36; 
          COUNTPARTSUPP1_L2_2_DELTA_entry* e36;
        
          for (size_t i = 0; i < i36->size_; i++)
          {
            n36 = i36->buckets_ + i;
            while (n36 && (e36 = n36->obj))
            {
                long p_partkey = e36->P_PARTKEY;
                long s_suppkey = e36->PS2_SUPPKEY;
                DOUBLE_TYPE ps_supplycost = e36->PS2_SUPPLYCOST;
                long v37 = e36->__av;
                long agg7 = 0L;
                { //slice 
                  const HashIndex_COUNTPART1_L2_1_map_0* i37 = static_cast<HashIndex_COUNTPART1_L2_1_map_0*>(COUNTPART1_L2_1.index[1]);
                  const HASH_RES_t h18 = COUNTPART1_L2_1_mapkey0_idxfn::hash(se37.modify0(p_partkey));
                  HashIndex_COUNTPART1_L2_1_map_0::IdxNode* n37 = static_cast<HashIndex_COUNTPART1_L2_1_map_0::IdxNode*>(i37->slice(se37, h18));
                  COUNTPART1_L2_1_entry* e37;
                 
                  if (n37 && (e37 = n37->obj)) {
                    do {                
                      DOUBLE_TYPE ps2_supplycost = e37->PS2_SUPPLYCOST;
                      long v38 = e37->__av;
                      (/*if */(ps_supplycost > ps2_supplycost) ? agg7 += v38 : 0L);
                      n37 = n37->nxt;
                    } while (n37 && (e37 = n37->obj) && h18 == n37->hash &&  COUNTPART1_L2_1_mapkey0_idxfn::equals(se37, *e37)); 
                  }
                }long agg8 = 0L;
                { //slice 
                  const HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_0* i38 = static_cast<HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_0*>(COUNTPARTSUPP1_L2_2_DELTA.index[1]);
                  const HASH_RES_t h19 = COUNTPARTSUPP1_L2_2_DELTA_mapkey0_idxfn::hash(se39.modify0(p_partkey));
                  HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_0::IdxNode* n38 = static_cast<HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_0::IdxNode*>(i38->slice(se39, h19));
                  COUNTPARTSUPP1_L2_2_DELTA_entry* e38;
                 
                  if (n38 && (e38 = n38->obj)) {
                    do {                
                      long ps2_suppkey = e38->PS2_SUPPKEY;
                      DOUBLE_TYPE ps2_supplycost = e38->PS2_SUPPLYCOST;
                      long v39 = e38->__av;
                      (/*if */(ps_supplycost > ps2_supplycost) ? agg8 += (v39 * COUNTPARTSUPP1_L2_2.getValueOrDefault(se38.modify(ps2_suppkey))) : 0L);
                      n38 = n38->nxt;
                    } while (n38 && (e38 = n38->obj) && h19 == n38->hash &&  COUNTPARTSUPP1_L2_2_DELTA_mapkey0_idxfn::equals(se39, *e38)); 
                  }
                }{ //slice 
                  const HashIndex_COUNTPARTSUPP1_P_1_map_0* i39 = static_cast<HashIndex_COUNTPARTSUPP1_P_1_map_0*>(COUNTPARTSUPP1_P_1.index[1]);
                  const HASH_RES_t h21 = COUNTPARTSUPP1_P_1_mapkey0_idxfn::hash(se41.modify0(p_partkey));
                  HashIndex_COUNTPARTSUPP1_P_1_map_0::IdxNode* n39 = static_cast<HashIndex_COUNTPARTSUPP1_P_1_map_0::IdxNode*>(i39->slice(se41, h21));
                  COUNTPARTSUPP1_P_1_entry* e39;
                 
                  if (n39 && (e39 = n39->obj)) {
                    do {                
                      STRING_TYPE p_mfgr = e39->P_MFGR;
                      long v40 = e39->__av;
                      { //slice 
                        const HashIndex_COUNTPARTSUPP4_P_2_map_0* i40 = static_cast<HashIndex_COUNTPARTSUPP4_P_2_map_0*>(COUNTPARTSUPP4_P_2.index[1]);
                        const HASH_RES_t h20 = COUNTPARTSUPP4_P_2_mapkey0_idxfn::hash(se40.modify0(s_suppkey));
                        HashIndex_COUNTPARTSUPP4_P_2_map_0::IdxNode* n40 = static_cast<HashIndex_COUNTPARTSUPP4_P_2_map_0::IdxNode*>(i40->slice(se40, h20));
                        COUNTPARTSUPP4_P_2_entry* e40;
                       
                        if (n40 && (e40 = n40->obj)) {
                          do {                
                            STRING_TYPE s_name = e40->S_NAME;
                            STRING_TYPE s_address = e40->S_ADDRESS;
                            STRING_TYPE s_phone = e40->S_PHONE;
                            DOUBLE_TYPE s_acctbal = e40->S_ACCTBAL;
                            STRING_TYPE s_comment = e40->S_COMMENT;
                            STRING_TYPE n_name = e40->N_NAME;
                            long v41 = e40->__av;
                            (/*if */(l5 == (agg7 + agg8)) ? COUNT.addOrDelOnZero(se29.modify(s_acctbal,s_name,n_name,p_partkey,p_mfgr,s_address,s_phone,s_comment),(v37 * (v40 * v41))) : (void)0);
                            n40 = n40->nxt;
                          } while (n40 && (e40 = n40->obj) && h20 == n40->hash &&  COUNTPARTSUPP4_P_2_mapkey0_idxfn::equals(se40, *e40)); 
                        }
                      }
                      n39 = n39->nxt;
                    } while (n39 && (e39 = n39->obj) && h21 == n39->hash &&  COUNTPARTSUPP1_P_1_mapkey0_idxfn::equals(se41, *e39)); 
                  }
                }
              n36 = n36->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012* i41 = static_cast<HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012*>(COUNTPARTSUPP1_L2_2_DELTA.index[0]);
          HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012::IdxNode* n41; 
          COUNTPARTSUPP1_L2_2_DELTA_entry* e41;
        
          for (size_t i = 0; i < i41->size_; i++)
          {
            n41 = i41->buckets_ + i;
            while (n41 && (e41 = n41->obj))
            {
                long p_partkey = e41->P_PARTKEY;
                long s_suppkey = e41->PS2_SUPPKEY;
                DOUBLE_TYPE ps_supplycost = e41->PS2_SUPPLYCOST;
                long v42 = e41->__av;
                { //slice 
                  const HashIndex_COUNTPARTSUPP1_P_1_map_0* i42 = static_cast<HashIndex_COUNTPARTSUPP1_P_1_map_0*>(COUNTPARTSUPP1_P_1.index[1]);
                  const HASH_RES_t h23 = COUNTPARTSUPP1_P_1_mapkey0_idxfn::hash(se44.modify0(p_partkey));
                  HashIndex_COUNTPARTSUPP1_P_1_map_0::IdxNode* n42 = static_cast<HashIndex_COUNTPARTSUPP1_P_1_map_0::IdxNode*>(i42->slice(se44, h23));
                  COUNTPARTSUPP1_P_1_entry* e42;
                 
                  if (n42 && (e42 = n42->obj)) {
                    do {                
                      STRING_TYPE p_mfgr = e42->P_MFGR;
                      long v43 = e42->__av;
                      { //slice 
                        const HashIndex_COUNTPARTSUPP4_P_2_map_0* i43 = static_cast<HashIndex_COUNTPARTSUPP4_P_2_map_0*>(COUNTPARTSUPP4_P_2.index[1]);
                        const HASH_RES_t h22 = COUNTPARTSUPP4_P_2_mapkey0_idxfn::hash(se43.modify0(s_suppkey));
                        HashIndex_COUNTPARTSUPP4_P_2_map_0::IdxNode* n43 = static_cast<HashIndex_COUNTPARTSUPP4_P_2_map_0::IdxNode*>(i43->slice(se43, h22));
                        COUNTPARTSUPP4_P_2_entry* e43;
                       
                        if (n43 && (e43 = n43->obj)) {
                          do {                
                            STRING_TYPE s_name = e43->S_NAME;
                            STRING_TYPE s_address = e43->S_ADDRESS;
                            STRING_TYPE s_phone = e43->S_PHONE;
                            DOUBLE_TYPE s_acctbal = e43->S_ACCTBAL;
                            STRING_TYPE s_comment = e43->S_COMMENT;
                            STRING_TYPE n_name = e43->N_NAME;
                            long v44 = e43->__av;
                            COUNTSUPPLIER1.addOrDelOnZero(se42.modify(p_partkey,p_mfgr,s_name,s_address,s_phone,s_acctbal,s_comment,ps_supplycost,n_name),(v42 * (v43 * v44)));
                            n43 = n43->nxt;
                          } while (n43 && (e43 = n43->obj) && h22 == n43->hash &&  COUNTPARTSUPP4_P_2_mapkey0_idxfn::equals(se43, *e43)); 
                        }
                      }
                      n42 = n42->nxt;
                    } while (n42 && (e42 = n42->obj) && h23 == n42->hash &&  COUNTPARTSUPP1_P_1_mapkey0_idxfn::equals(se44, *e42)); 
                  }
                }
              n41 = n41->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012* i44 = static_cast<HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012*>(COUNTPARTSUPP1_L2_2_DELTA.index[0]);
          HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012::IdxNode* n44; 
          COUNTPARTSUPP1_L2_2_DELTA_entry* e44;
        
          for (size_t i = 0; i < i44->size_; i++)
          {
            n44 = i44->buckets_ + i;
            while (n44 && (e44 = n44->obj))
            {
                long p_partkey = e44->P_PARTKEY;
                long s_suppkey = e44->PS2_SUPPKEY;
                DOUBLE_TYPE ps_supplycost = e44->PS2_SUPPLYCOST;
                long v45 = e44->__av;
                { //slice 
                  const HashIndex_COUNTPARTSUPP1_P_1_map_0* i45 = static_cast<HashIndex_COUNTPARTSUPP1_P_1_map_0*>(COUNTPARTSUPP1_P_1.index[1]);
                  const HASH_RES_t h24 = COUNTPARTSUPP1_P_1_mapkey0_idxfn::hash(se46.modify0(p_partkey));
                  HashIndex_COUNTPARTSUPP1_P_1_map_0::IdxNode* n45 = static_cast<HashIndex_COUNTPARTSUPP1_P_1_map_0::IdxNode*>(i45->slice(se46, h24));
                  COUNTPARTSUPP1_P_1_entry* e45;
                 
                  if (n45 && (e45 = n45->obj)) {
                    do {                
                      STRING_TYPE p_mfgr = e45->P_MFGR;
                      long v46 = e45->__av;
                      COUNTSUPPLIER1SUPPLIER1_P_1.addOrDelOnZero(se45.modify(p_partkey,s_suppkey,ps_supplycost,p_mfgr),(v45 * v46));
                      n45 = n45->nxt;
                    } while (n45 && (e45 = n45->obj) && h24 == n45->hash &&  COUNTPARTSUPP1_P_1_mapkey0_idxfn::equals(se46, *e45)); 
                  }
                }
              n44 = n44->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012* i46 = static_cast<HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012*>(COUNTPARTSUPP1_L2_2_DELTA.index[0]);
          HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012::IdxNode* n46; 
          COUNTPARTSUPP1_L2_2_DELTA_entry* e46;
        
          for (size_t i = 0; i < i46->size_; i++)
          {
            n46 = i46->buckets_ + i;
            while (n46 && (e46 = n46->obj))
            {
                long p_partkey = e46->P_PARTKEY;
                long s_suppkey = e46->PS2_SUPPKEY;
                DOUBLE_TYPE ps_supplycost = e46->PS2_SUPPLYCOST;
                long v47 = e46->__av;
                COUNTSUPPLIER1SUPPLIER1_P_1PART1.addOrDelOnZero(se47.modify(p_partkey,s_suppkey,ps_supplycost),v47);
              n46 = n46->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012* i47 = static_cast<HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012*>(COUNTPARTSUPP1_L2_2_DELTA.index[0]);
          HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012::IdxNode* n47; 
          COUNTPARTSUPP1_L2_2_DELTA_entry* e47;
        
          for (size_t i = 0; i < i47->size_; i++)
          {
            n47 = i47->buckets_ + i;
            while (n47 && (e47 = n47->obj))
            {
                long p_partkey = e47->P_PARTKEY;
                long s_suppkey = e47->PS2_SUPPKEY;
                DOUBLE_TYPE ps_supplycost = e47->PS2_SUPPLYCOST;
                long v48 = e47->__av;
                { //slice 
                  const HashIndex_COUNTPARTSUPP4_P_2_map_0* i48 = static_cast<HashIndex_COUNTPARTSUPP4_P_2_map_0*>(COUNTPARTSUPP4_P_2.index[1]);
                  const HASH_RES_t h25 = COUNTPARTSUPP4_P_2_mapkey0_idxfn::hash(se49.modify0(s_suppkey));
                  HashIndex_COUNTPARTSUPP4_P_2_map_0::IdxNode* n48 = static_cast<HashIndex_COUNTPARTSUPP4_P_2_map_0::IdxNode*>(i48->slice(se49, h25));
                  COUNTPARTSUPP4_P_2_entry* e48;
                 
                  if (n48 && (e48 = n48->obj)) {
                    do {                
                      STRING_TYPE s_name = e48->S_NAME;
                      STRING_TYPE s_address = e48->S_ADDRESS;
                      STRING_TYPE s_phone = e48->S_PHONE;
                      DOUBLE_TYPE s_acctbal = e48->S_ACCTBAL;
                      STRING_TYPE s_comment = e48->S_COMMENT;
                      STRING_TYPE n_name = e48->N_NAME;
                      long v49 = e48->__av;
                      COUNTPART1.addOrDelOnZero(se48.modify(s_name,s_address,s_phone,s_acctbal,s_comment,p_partkey,ps_supplycost,n_name),(v48 * v49));
                      n48 = n48->nxt;
                    } while (n48 && (e48 = n48->obj) && h25 == n48->hash &&  COUNTPARTSUPP4_P_2_mapkey0_idxfn::equals(se49, *e48)); 
                  }
                }
              n47 = n47->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012* i49 = static_cast<HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012*>(COUNTPARTSUPP1_L2_2_DELTA.index[0]);
          HashIndex_COUNTPARTSUPP1_L2_2_DELTA_map_012::IdxNode* n49; 
          COUNTPARTSUPP1_L2_2_DELTA_entry* e49;
        
          for (size_t i = 0; i < i49->size_; i++)
          {
            n49 = i49->buckets_ + i;
            while (n49 && (e49 = n49->obj))
            {
                long p_partkey = e49->P_PARTKEY;
                long ps2_suppkey = e49->PS2_SUPPKEY;
                DOUBLE_TYPE ps2_supplycost = e49->PS2_SUPPLYCOST;
                long v50 = e49->__av;
                COUNTPART1_L2_1.addOrDelOnZero(se50.modify(p_partkey,ps2_supplycost),(v50 * COUNTPARTSUPP1_L2_2.getValueOrDefault(se51.modify(ps2_suppkey))));
              n49 = n49->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        COUNTPARTSUPP1_L2_2SUPPLIER1.clear();
        STRING_TYPE l6 = c1;
        {  // foreach
          const HashIndex_NATION_map_0123* i50 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n50; 
          NATION_entry* e50;
        
          for (size_t i = 0; i < i50->size_; i++)
          {
            n50 = i50->buckets_ + i;
            while (n50 && (e50 = n50->obj))
            {
                long s2_nationkey = e50->NATION_NATIONKEY;
                STRING_TYPE n2_name = e50->NATION_NAME;
                long n2_regionkey = e50->NATION_REGIONKEY;
                STRING_TYPE n2_comment = e50->NATION_COMMENT;
                long v51 = e50->__av;
                { //slice 
                  const HashIndex_REGION_map_01* i51 = static_cast<HashIndex_REGION_map_01*>(REGION.index[1]);
                  const HASH_RES_t h26 = REGION_mapkey01_idxfn::hash(se53.modify01(n2_regionkey, l6));
                  HashIndex_REGION_map_01::IdxNode* n51 = static_cast<HashIndex_REGION_map_01::IdxNode*>(i51->slice(se53, h26));
                  REGION_entry* e51;
                 
                  if (n51 && (e51 = n51->obj)) {
                    do {                
                      STRING_TYPE r2_comment = e51->REGION_COMMENT;
                      long v52 = e51->__av;
                      COUNTPARTSUPP1_L2_2SUPPLIER1.addOrDelOnZero(se52.modify(s2_nationkey),(v51 * v52));
                      n51 = n51->nxt;
                    } while (n51 && (e51 = n51->obj) && h26 == n51->hash &&  REGION_mapkey01_idxfn::equals(se53, *e51)); 
                  }
                }
              n50 = n50->nxt;
            }
          }
        }COUNTPARTSUPP4_P_2SUPPLIER1.clear();
        STRING_TYPE l7 = c1;
        { //slice 
          const HashIndex_REGION_map_1* i52 = static_cast<HashIndex_REGION_map_1*>(REGION.index[2]);
          const HASH_RES_t h28 = REGION_mapkey1_idxfn::hash(se56.modify1(l7));
          HashIndex_REGION_map_1::IdxNode* n52 = static_cast<HashIndex_REGION_map_1::IdxNode*>(i52->slice(se56, h28));
          REGION_entry* e52;
         
          if (n52 && (e52 = n52->obj)) {
            do {                
              long n_regionkey = e52->REGION_REGIONKEY;
              STRING_TYPE r_comment = e52->REGION_COMMENT;
              long v53 = e52->__av;
              { //slice 
                const HashIndex_NATION_map_2* i53 = static_cast<HashIndex_NATION_map_2*>(NATION.index[1]);
                const HASH_RES_t h27 = NATION_mapkey2_idxfn::hash(se55.modify2(n_regionkey));
                HashIndex_NATION_map_2::IdxNode* n53 = static_cast<HashIndex_NATION_map_2::IdxNode*>(i53->slice(se55, h27));
                NATION_entry* e53;
               
                if (n53 && (e53 = n53->obj)) {
                  do {                
                    long s_nationkey = e53->NATION_NATIONKEY;
                    STRING_TYPE n_name = e53->NATION_NAME;
                    STRING_TYPE n_comment = e53->NATION_COMMENT;
                    long v54 = e53->__av;
                    COUNTPARTSUPP4_P_2SUPPLIER1.addOrDelOnZero(se54.modify(s_nationkey,n_name),(v53 * v54));
                    n53 = n53->nxt;
                  } while (n53 && (e53 = n53->obj) && h27 == n53->hash &&  NATION_mapkey2_idxfn::equals(se55, *e53)); 
                }
              }
              n52 = n52->nxt;
            } while (n52 && (e52 = n52->obj) && h28 == n52->hash &&  REGION_mapkey1_idxfn::equals(se56, *e52)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNTPART1_DELTA_entry se1;
    COUNT_entry se2;
    COUNTPART1_L2_1_entry se3;
    tuple7_SSSDSS_L st1;
    COUNTPART1_entry se4;
    COUNTPARTSUPP1_P_1_entry se5;
    COUNTSUPPLIER1_entry se6;
    COUNTPART1_entry se7;
    COUNTSUPPLIER1SUPPLIER1_P_1_entry se8;
    COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry se9;
    COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_entry se10;
    COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_entry se11;
    COUNTPARTSUPP1_L2_2_entry se12;
    COUNTPARTSUPP1_L2_2SUPPLIER1_entry se13;
    COUNTPARTSUPP4_P_2_entry se14;
    COUNTPARTSUPP4_P_2SUPPLIER1_entry se15;
    COUNTSUPPLIER1_entry se16;
    COUNTPARTSUPP4_P_2SUPPLIER1_entry se17;
    COUNTSUPPLIER1SUPPLIER1_P_1_entry se18;
    COUNTPART1_entry se19;
    COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry se20;
    COUNTPARTSUPP4_P_2SUPPLIER1_entry se21;
    COUNTPART1_L2_1_entry se22;
    COUNTPARTSUPP1_L2_2SUPPLIER1_entry se23;
    COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry se24;
    COUNT_entry se25;
    COUNTPART1_L2_1_entry se26;
    COUNTPARTSUPP1_L2_2_DELTA_entry se27;
    COUNTPARTSUPP1_DOMAIN1_entry se28;
    COUNT_entry se29;
    COUNTPART1_L2_1_entry se30;
    COUNTPARTSUPP1_L2_2_entry se31;
    COUNTPARTSUPP1_L2_2_DELTA_entry se32;
    tuple7_SSSDSS_L st2;
    COUNTPART1_entry se33;
    COUNTPART1_L2_1_entry se34;
    tuple7_SSSDSS_L st3;
    COUNTPART1_entry se35;
    COUNTPARTSUPP1_P_1_entry se36;
    COUNTPART1_L2_1_entry se37;
    COUNTPARTSUPP1_L2_2_entry se38;
    COUNTPARTSUPP1_L2_2_DELTA_entry se39;
    COUNTPARTSUPP4_P_2_entry se40;
    COUNTPARTSUPP1_P_1_entry se41;
    COUNTSUPPLIER1_entry se42;
    COUNTPARTSUPP4_P_2_entry se43;
    COUNTPARTSUPP1_P_1_entry se44;
    COUNTSUPPLIER1SUPPLIER1_P_1_entry se45;
    COUNTPARTSUPP1_P_1_entry se46;
    COUNTSUPPLIER1SUPPLIER1_P_1PART1_entry se47;
    COUNTPART1_entry se48;
    COUNTPARTSUPP4_P_2_entry se49;
    COUNTPART1_L2_1_entry se50;
    COUNTPARTSUPP1_L2_2_entry se51;
    COUNTPARTSUPP1_L2_2SUPPLIER1_entry se52;
    REGION_entry se53;
    COUNTPARTSUPP4_P_2SUPPLIER1_entry se54;
    NATION_entry se55;
    REGION_entry se56;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REGION_map REGION;
    COUNTPARTSUPP1_DOMAIN1_map COUNTPARTSUPP1_DOMAIN1;
    COUNTPARTSUPP1_P_1_map COUNTPARTSUPP1_P_1;
    COUNTPARTSUPP1_L2_2_DELTA_map COUNTPARTSUPP1_L2_2_DELTA;
    COUNTPARTSUPP1_L2_2_map COUNTPARTSUPP1_L2_2;
    COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA_map COUNTPARTSUPP1_L2_2SUPPLIER1_DELTA;
    COUNTPARTSUPP1_L2_2SUPPLIER1_map COUNTPARTSUPP1_L2_2SUPPLIER1;
    COUNTPARTSUPP4_P_2_map COUNTPARTSUPP4_P_2;
    COUNTPARTSUPP4_P_2SUPPLIER1_DELTA_map COUNTPARTSUPP4_P_2SUPPLIER1_DELTA;
    COUNTPARTSUPP4_P_2SUPPLIER1_map COUNTPARTSUPP4_P_2SUPPLIER1;
    COUNTSUPPLIER1_map COUNTSUPPLIER1;
    COUNTSUPPLIER1SUPPLIER1_P_1_map COUNTSUPPLIER1SUPPLIER1_P_1;
    COUNTSUPPLIER1SUPPLIER1_P_1PART1_map COUNTSUPPLIER1SUPPLIER1_P_1PART1;
    COUNTPART1_DELTA_map COUNTPART1_DELTA;
    COUNTPART1_map COUNTPART1;
    COUNTPART1_L2_1_map COUNTPART1_L2_1;
    DELTA_PART_map DELTA_PART;
    DELTA_SUPPLIER_map DELTA_SUPPLIER;
    DELTA_PARTSUPP_map DELTA_PARTSUPP;
    MultiHashMap<tuple7_SSSDSS_L,long,HashIndex<tuple7_SSSDSS_L,long> > _c1;
    MultiHashMap<tuple7_SSSDSS_L,long,HashIndex<tuple7_SSSDSS_L,long> > agg1;
    /*const static*/ STRING_TYPE c1;
  
  };

}
