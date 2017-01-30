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
  
  struct SUPPLIER_CNT_entry {
    STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_entry() { /*P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const long c3) { P_BRAND = c0; P_TYPE = c1; P_SIZE = c2; __av = c3; }
    SUPPLIER_CNT_entry(const SUPPLIER_CNT_entry& other) : P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { P_BRAND = c0; P_TYPE = c1; P_SIZE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNT_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_entry& x, const SUPPLIER_CNT_entry& y) {
      return x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_entry,long,
    HashIndex<SUPPLIER_CNT_entry,long,SUPPLIER_CNT_mapkey012_idxfn,true>
  > SUPPLIER_CNT_map;
  typedef HashIndex<SUPPLIER_CNT_entry,long,SUPPLIER_CNT_mapkey012_idxfn,true> HashIndex_SUPPLIER_CNT_map_012;
  
  struct SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry {
    long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry() { /*PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry(const long c0, const long c1) { PS_SUPPKEY = c0; __av = c1; }
    SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry(const SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry& modify(const long c0) { PS_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTSUPPLIER1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry& x, const SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry,long,
    HashIndex<SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry,long,SUPPLIER_CNTSUPPLIER1_DOMAIN1_mapkey0_idxfn,true>
  > SUPPLIER_CNTSUPPLIER1_DOMAIN1_map;
  typedef HashIndex<SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry,long,SUPPLIER_CNTSUPPLIER1_DOMAIN1_mapkey0_idxfn,true> HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0;
  
  struct SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry {
    long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry() { /*PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry(const long c0, const long c1) { PS_SUPPKEY = c0; __av = c1; }
    SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry(const SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry& modify(const long c0) { PS_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry& x, const SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry,long,SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_mapkey0_idxfn,true>
  > SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry,long,SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_mapkey0_idxfn,true> HashIndex_SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_map_0;
  
  struct SUPPLIER_CNTPART1_DOMAIN1_entry {
    STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPART1_DOMAIN1_entry() { /*P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPART1_DOMAIN1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const long c3) { P_BRAND = c0; P_TYPE = c1; P_SIZE = c2; __av = c3; }
    SUPPLIER_CNTPART1_DOMAIN1_entry(const SUPPLIER_CNTPART1_DOMAIN1_entry& other) : P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPART1_DOMAIN1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { P_BRAND = c0; P_TYPE = c1; P_SIZE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPART1_DOMAIN1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_DOMAIN1_entry& x, const SUPPLIER_CNTPART1_DOMAIN1_entry& y) {
      return x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPART1_DOMAIN1_entry,long,
    HashIndex<SUPPLIER_CNTPART1_DOMAIN1_entry,long,SUPPLIER_CNTPART1_DOMAIN1_mapkey012_idxfn,true>
  > SUPPLIER_CNTPART1_DOMAIN1_map;
  typedef HashIndex<SUPPLIER_CNTPART1_DOMAIN1_entry,long,SUPPLIER_CNTPART1_DOMAIN1_mapkey012_idxfn,true> HashIndex_SUPPLIER_CNTPART1_DOMAIN1_map_012;
  
  struct SUPPLIER_CNTPART1_E1_4_entry {
    STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTPART1_E1_4_entry() { /*P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPART1_E1_4_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const long c3, const long c4) { P_BRAND = c0; P_TYPE = c1; P_SIZE = c2; PS_SUPPKEY = c3; __av = c4; }
    SUPPLIER_CNTPART1_E1_4_entry(const SUPPLIER_CNTPART1_E1_4_entry& other) : P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPART1_E1_4_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const long c3) { P_BRAND = c0; P_TYPE = c1; P_SIZE = c2; PS_SUPPKEY = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPART1_E1_4_entry& modify012(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { P_BRAND = c0; P_TYPE = c1; P_SIZE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPART1_E1_4_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_4_entry& x, const SUPPLIER_CNTPART1_E1_4_entry& y) {
      return x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE && x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  struct SUPPLIER_CNTPART1_E1_4_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_4_entry& x, const SUPPLIER_CNTPART1_E1_4_entry& y) {
      return x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPART1_E1_4_entry,long,
    HashIndex<SUPPLIER_CNTPART1_E1_4_entry,long,SUPPLIER_CNTPART1_E1_4_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPART1_E1_4_entry,long,SUPPLIER_CNTPART1_E1_4_mapkey012_idxfn,false>
  > SUPPLIER_CNTPART1_E1_4_map;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_4_entry,long,SUPPLIER_CNTPART1_E1_4_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPART1_E1_4_map_0123;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_4_entry,long,SUPPLIER_CNTPART1_E1_4_mapkey012_idxfn,false> HashIndex_SUPPLIER_CNTPART1_E1_4_map_012;
  
  struct SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry(const SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPART1_E1_4PARTSUPP1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry& x, const SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPART1_E1_4PARTSUPP1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry& x, const SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry,long,
    HashIndex<SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry,long,SUPPLIER_CNTPART1_E1_4PARTSUPP1_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry,long,SUPPLIER_CNTPART1_E1_4PARTSUPP1_mapkey0_idxfn,false>
  > SUPPLIER_CNTPART1_E1_4PARTSUPP1_map;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry,long,SUPPLIER_CNTPART1_E1_4PARTSUPP1_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPART1_E1_4PARTSUPP1_map_0123;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry,long,SUPPLIER_CNTPART1_E1_4PARTSUPP1_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPART1_E1_4PARTSUPP1_map_0;
  
  struct SUPPLIER_CNTPART1_E1_8_DELTA_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPART1_E1_8_DELTA_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPART1_E1_8_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPART1_E1_8_DELTA_entry(const SUPPLIER_CNTPART1_E1_8_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPART1_E1_8_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPART1_E1_8_DELTA_entry& modify123(const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPART1_E1_8_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_8_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_8_DELTA_entry& x, const SUPPLIER_CNTPART1_E1_8_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPART1_E1_8_DELTA_mapkey123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_8_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_8_DELTA_entry& x, const SUPPLIER_CNTPART1_E1_8_DELTA_entry& y) {
      return x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPART1_E1_8_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTPART1_E1_8_DELTA_entry,long,SUPPLIER_CNTPART1_E1_8_DELTA_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPART1_E1_8_DELTA_entry,long,SUPPLIER_CNTPART1_E1_8_DELTA_mapkey123_idxfn,false>
  > SUPPLIER_CNTPART1_E1_8_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_8_DELTA_entry,long,SUPPLIER_CNTPART1_E1_8_DELTA_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPART1_E1_8_DELTA_map_0123;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_8_DELTA_entry,long,SUPPLIER_CNTPART1_E1_8_DELTA_mapkey123_idxfn,false> HashIndex_SUPPLIER_CNTPART1_E1_8_DELTA_map_123;
  
  struct SUPPLIER_CNTPART1_E1_8_entry {
    long PS_PARTKEY; long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTPART1_E1_8_entry() { /*PS_PARTKEY = 0L; PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPART1_E1_8_entry(const long c0, const long c1, const long c2) { PS_PARTKEY = c0; PS_SUPPKEY = c1; __av = c2; }
    SUPPLIER_CNTPART1_E1_8_entry(const SUPPLIER_CNTPART1_E1_8_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPART1_E1_8_entry& modify(const long c0, const long c1) { PS_PARTKEY = c0; PS_SUPPKEY = c1;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPART1_E1_8_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPART1_E1_8_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_8_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_8_entry& x, const SUPPLIER_CNTPART1_E1_8_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  struct SUPPLIER_CNTPART1_E1_8_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_8_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_8_entry& x, const SUPPLIER_CNTPART1_E1_8_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPART1_E1_8_entry,long,
    HashIndex<SUPPLIER_CNTPART1_E1_8_entry,long,SUPPLIER_CNTPART1_E1_8_mapkey01_idxfn,true>,
    HashIndex<SUPPLIER_CNTPART1_E1_8_entry,long,SUPPLIER_CNTPART1_E1_8_mapkey0_idxfn,false>
  > SUPPLIER_CNTPART1_E1_8_map;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_8_entry,long,SUPPLIER_CNTPART1_E1_8_mapkey01_idxfn,true> HashIndex_SUPPLIER_CNTPART1_E1_8_map_01;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_8_entry,long,SUPPLIER_CNTPART1_E1_8_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPART1_E1_8_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry {
    long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry() { /*PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry(const long c0, const long c1) { PS_SUPPKEY = c0; __av = c1; }
    SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry(const SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry& modify(const long c0) { PS_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPARTSUPP1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry& x, const SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry,long,SUPPLIER_CNTPARTSUPP1_DOMAIN1_mapkey0_idxfn,true>
  > SUPPLIER_CNTPARTSUPP1_DOMAIN1_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry,long,SUPPLIER_CNTPARTSUPP1_DOMAIN1_mapkey0_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry {
    long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry() { /*PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry(const long c0, const long c1) { PS_SUPPKEY = c0; __av = c1; }
    SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry(const SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry& modify(const long c0) { PS_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry,long,SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_mapkey0_idxfn,true>
  > SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry,long,SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_mapkey0_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_2_entry {
    long PS_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_2_entry() { /*PS_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_2_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_2_entry(const SUPPLIER_CNTPARTSUPP1_E1_2_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_2_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_2_entry& modify0(const long c0) { PS_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_2_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_2_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_2_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_2_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_2_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_2_entry,long,SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_2_entry,long,SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_2_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_2_entry,long,SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_2_entry,long,SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry(const SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_mapkey0123_idxfn,true>
  > SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry {
    long PS_PARTKEY; long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry() { /*PS_PARTKEY = 0L; PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry(const long c0, const long c1, const long c2) { PS_PARTKEY = c0; PS_SUPPKEY = c1; __av = c2; }
    SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry(const SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry& modify(const long c0, const long c1) { PS_PARTKEY = c0; PS_SUPPKEY = c1;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry& modify1(const long c1) { PS_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_mapkey01_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_mapkey1_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_mapkey01_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_01;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_mapkey1_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_1;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_4_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_4_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_4_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_4_entry(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_4_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_4_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_4_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_4_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_4_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0;
  
  struct tuple4_SSL_L {
    STRING_TYPE _1; STRING_TYPE _2; long _3; long __av;
    explicit tuple4_SSL_L() { }
    explicit tuple4_SSL_L(const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; __av = c__av;}
    int operator==(const tuple4_SSL_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3)); }
    FORCE_INLINE tuple4_SSL_L& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, long c__av) { _1 = c0; _2 = c1; _3 = c2; __av = c__av; return *this; }
    static bool equals(const tuple4_SSL_L &x, const tuple4_SSL_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3)); }
    static long hash(const tuple4_SSL_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      return h;
    }
  };
  struct tuple2_L_L {
    long _1; long __av;
    explicit tuple2_L_L() { }
    explicit tuple2_L_L(const long c1, long c__av=0L) { _1 = c1; __av = c__av;}
    int operator==(const tuple2_L_L &rhs) const { return ((this->_1==rhs._1)); }
    FORCE_INLINE tuple2_L_L& modify(const long c0, long c__av) { _1 = c0; __av = c__av; return *this; }
    static bool equals(const tuple2_L_L &x, const tuple2_L_L &y) { return ((x._1==y._1)); }
    static long hash(const tuple2_L_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
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
      const SUPPLIER_CNT_map& _SUPPLIER_CNT = get_SUPPLIER_CNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(SUPPLIER_CNT), _SUPPLIER_CNT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const SUPPLIER_CNT_map& get_SUPPLIER_CNT() const {
      return SUPPLIER_CNT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    SUPPLIER_CNT_map SUPPLIER_CNT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), agg6(16U), _c1(16U), agg8(16U), agg5(16U), agg4(16U), _c2(16U) {
      c1 = STRING_TYPE("Brand#45");
      /* regex_t init */
      if(regcomp(&preg2, "^.*Customer.*Complaints.*$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^.*Customer.*Complaints.*$/" << endl;
        exit(-1);
      }
      if(regcomp(&preg1, "^MEDIUM POLISHED.*$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^MEDIUM POLISHED.*$/" << endl;
        exit(-1);
      }
    }
  
    ~data_t() {
      regfree(&preg2);
      regfree(&preg1);
    }
  
    /* Trigger functions for table relations */
    
    
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

        SUPPLIER_CNTPART1_E1_8_DELTA.clear();
        SUPPLIER_CNTPART1_DOMAIN1.clear();
        SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA.clear();        
        {  
          for (size_t i = 0; i < DELTA_PART.size; i++) 
          {
                long ps_partkey = DELTA_PART.partkey[i];
                // STRING_TYPE p_name = DELTA_PART.name[i];
                // STRING_TYPE p_mfgr = DELTA_PART.mfgr[i];
                STRING_TYPE p_brand = DELTA_PART.brand[i];
                STRING_TYPE p_type = DELTA_PART.type[i];
                long p_size = DELTA_PART.psize[i];
                // STRING_TYPE p_container = DELTA_PART.container[i];
                // DOUBLE_TYPE p_retailprice = DELTA_PART.retailprice[i];
                // STRING_TYPE p_comment = DELTA_PART.comment[i];
                long v1 = 1L;
                SUPPLIER_CNTPART1_E1_8_DELTA.addOrDelOnZero(se1.modify(ps_partkey,p_brand,p_type,p_size),v1);            
                long v2 = 1L;
                (/*if */(((p_size == 49L) || (p_size == 14L) || (p_size == 23L) || (p_size == 45L) || (p_size == 19L) || (p_size == 3L) || (p_size == 36L) || (p_size == 9L)) && 0L == Upreg_match(preg1,p_type) && p_brand != c1) ? SUPPLIER_CNTPART1_DOMAIN1.addOrDelOnZero(se2.modify(p_brand,p_type,p_size),(v2 != 0 ? 1L : 0L)) : (void)0);
                long v3 = 1L;
                (/*if */(((p_size == 49L) || (p_size == 14L) || (p_size == 23L) || (p_size == 45L) || (p_size == 19L) || (p_size == 3L) || (p_size == 36L) || (p_size == 9L)) && 0L == Upreg_match(preg1,p_type) && p_brand != c1) ? SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA.addOrDelOnZero(se3.modify(ps_partkey,p_brand,p_type,p_size),v3) : (void)0);                
          }
        }

        {  // foreach
          const HashIndex_SUPPLIER_CNTPART1_DOMAIN1_map_012* i4 = static_cast<HashIndex_SUPPLIER_CNTPART1_DOMAIN1_map_012*>(SUPPLIER_CNTPART1_DOMAIN1.index[0]);
          HashIndex_SUPPLIER_CNTPART1_DOMAIN1_map_012::IdxNode* n4; 
          SUPPLIER_CNTPART1_DOMAIN1_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                STRING_TYPE p_brand = e4->P_BRAND;
                STRING_TYPE p_type = e4->P_TYPE;
                long p_size = e4->P_SIZE;
                long v4 = e4->__av;
                long agg1 = 0L;
                _c1.clear();
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_4_map_012* i5 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_4_map_012*>(SUPPLIER_CNTPART1_E1_4.index[1]);
                  const HASH_RES_t h1 = SUPPLIER_CNTPART1_E1_4_mapkey012_idxfn::hash(se6.modify012(p_brand, p_type, p_size));
                  HashIndex_SUPPLIER_CNTPART1_E1_4_map_012::IdxNode* n5 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_4_map_012::IdxNode*>(i5->slice(se6, h1));
                  SUPPLIER_CNTPART1_E1_4_entry* e5;
                 
                  if (n5 && (e5 = n5->obj)) {
                    do {                
                      long ps_suppkey = e5->PS_SUPPKEY;
                      long v6 = e5->__av;
                      long agg2 = 0L;
                      long l1 = SUPPLIER_CNTPARTSUPP1_E1_1_L1_1.getValueOrDefault(se5.modify(ps_suppkey));
                      (/*if */(l1 == 0L) ? agg2 += 1L : 0L);
                      _c1.addOrDelOnZero(st1.modify(ps_suppkey,(v6 * agg2)), (v6 * agg2));
                      n5 = n5->nxt;
                    } while (n5 && (e5 = n5->obj) && h1 == n5->hash &&  SUPPLIER_CNTPART1_E1_4_mapkey012_idxfn::equals(se6, *e5)); 
                  }
                }long l2 = 0L;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_8_DELTA_map_123* i6 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_8_DELTA_map_123*>(SUPPLIER_CNTPART1_E1_8_DELTA.index[1]);
                  const HASH_RES_t h3 = SUPPLIER_CNTPART1_E1_8_DELTA_mapkey123_idxfn::hash(se9.modify123(p_brand, p_type, p_size));
                  HashIndex_SUPPLIER_CNTPART1_E1_8_DELTA_map_123::IdxNode* n6 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_8_DELTA_map_123::IdxNode*>(i6->slice(se9, h3));
                  SUPPLIER_CNTPART1_E1_8_DELTA_entry* e6;
                 
                  if (n6 && (e6 = n6->obj)) {
                    do {                
                      long ps_partkey = e6->PS_PARTKEY;
                      long v7 = e6->__av;
                      { //slice 
                        const HashIndex_SUPPLIER_CNTPART1_E1_8_map_0* i7 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_8_map_0*>(SUPPLIER_CNTPART1_E1_8.index[1]);
                        const HASH_RES_t h2 = SUPPLIER_CNTPART1_E1_8_mapkey0_idxfn::hash(se8.modify0(ps_partkey));
                        HashIndex_SUPPLIER_CNTPART1_E1_8_map_0::IdxNode* n7 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_8_map_0::IdxNode*>(i7->slice(se8, h2));
                        SUPPLIER_CNTPART1_E1_8_entry* e7;
                       
                        if (n7 && (e7 = n7->obj)) {
                          do {                
                            long ps_suppkey = e7->PS_SUPPKEY;
                            long v8 = e7->__av;
                            (/*if */(l2 == SUPPLIER_CNTPARTSUPP1_E1_1_L1_1.getValueOrDefault(se7.modify(ps_suppkey))) ? _c1.addOrDelOnZero(st2.modify(ps_suppkey,(v7 * v8)), (v7 * v8)) : (void)0);
                            n7 = n7->nxt;
                          } while (n7 && (e7 = n7->obj) && h2 == n7->hash &&  SUPPLIER_CNTPART1_E1_8_mapkey0_idxfn::equals(se8, *e7)); 
                        }
                      }
                      n6 = n6->nxt;
                    } while (n6 && (e6 = n6->obj) && h3 == n6->hash &&  SUPPLIER_CNTPART1_E1_8_DELTA_mapkey123_idxfn::equals(se9, *e6)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple2_L_L, long>* i8 = static_cast<HashIndex<tuple2_L_L, long>*>(_c1.index[0]);
                  HashIndex<tuple2_L_L, long>::IdxNode* n8; 
                  tuple2_L_L* e8;
                
                  for (size_t i = 0; i < i8->size_; i++)
                  {
                    n8 = i8->buckets_ + i;
                    while (n8 && (e8 = n8->obj))
                    {
                      long ps_suppkey = e8->_1;  
                      long v9 = e8->__av; 
                    agg1 += ((/*if */(p_brand != c1 && 0L == Upreg_match(preg1,p_type) && ((p_size == 49L) || (p_size == 14L) || (p_size == 23L) || (p_size == 45L) || (p_size == 19L) || (p_size == 3L) || (p_size == 36L) || (p_size == 9L))) ? v9 : 0L) != 0 ? 1L : 0L);      
                      n8 = n8->nxt;
                    }
                  }
                }long agg3 = 0L;
                agg4.clear();
                
                long l3 = 0L;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_4_map_012* i9 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_4_map_012*>(SUPPLIER_CNTPART1_E1_4.index[1]);
                  const HASH_RES_t h4 = SUPPLIER_CNTPART1_E1_4_mapkey012_idxfn::hash(se11.modify012(p_brand, p_type, p_size));
                  HashIndex_SUPPLIER_CNTPART1_E1_4_map_012::IdxNode* n9 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_4_map_012::IdxNode*>(i9->slice(se11, h4));
                  SUPPLIER_CNTPART1_E1_4_entry* e9;
                 
                  if (n9 && (e9 = n9->obj)) {
                    do {                
                      long ps_suppkey = e9->PS_SUPPKEY;
                      long v10 = e9->__av;
                      (/*if */(p_brand != c1 && 0L == Upreg_match(preg1,p_type) && ((p_size == 49L) || (p_size == 14L) || (p_size == 23L) || (p_size == 45L) || (p_size == 19L) || (p_size == 3L) || (p_size == 36L) || (p_size == 9L)) && l3 == SUPPLIER_CNTPARTSUPP1_E1_1_L1_1.getValueOrDefault(se10.modify(ps_suppkey))) ? agg4.addOrDelOnZero(st3.modify(ps_suppkey,v10), v10) : (void)0);
                      n9 = n9->nxt;
                    } while (n9 && (e9 = n9->obj) && h4 == n9->hash &&  SUPPLIER_CNTPART1_E1_4_mapkey012_idxfn::equals(se11, *e9)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple2_L_L, long>* i10 = static_cast<HashIndex<tuple2_L_L, long>*>(agg4.index[0]);
                  HashIndex<tuple2_L_L, long>::IdxNode* n10; 
                  tuple2_L_L* e10;
                
                  for (size_t i = 0; i < i10->size_; i++)
                  {
                    n10 = i10->buckets_ + i;
                    while (n10 && (e10 = n10->obj))
                    {
                      long ps_suppkey = e10->_1;  
                      long v11 = e10->__av; 
                    agg3 += (v11 != 0 ? 1L : 0L);      
                      n10 = n10->nxt;
                    }
                  }
                }SUPPLIER_CNT.addOrDelOnZero(se4.modify(p_brand,p_type,p_size),((v4 != 0 ? 1L : 0L) * (agg1 + (agg3 * -1L))));
              n4 = n4->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPART1_E1_8_DELTA_map_0123* i11 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_8_DELTA_map_0123*>(SUPPLIER_CNTPART1_E1_8_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPART1_E1_8_DELTA_map_0123::IdxNode* n11; 
          SUPPLIER_CNTPART1_E1_8_DELTA_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long ps_partkey = e11->PS_PARTKEY;
                STRING_TYPE p_brand = e11->P_BRAND;
                STRING_TYPE p_type = e11->P_TYPE;
                long p_size = e11->P_SIZE;
                long v12 = e11->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_8_map_0* i12 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_8_map_0*>(SUPPLIER_CNTPART1_E1_8.index[1]);
                  const HASH_RES_t h5 = SUPPLIER_CNTPART1_E1_8_mapkey0_idxfn::hash(se13.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_8_map_0::IdxNode* n12 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_8_map_0::IdxNode*>(i12->slice(se13, h5));
                  SUPPLIER_CNTPART1_E1_8_entry* e12;
                 
                  if (n12 && (e12 = n12->obj)) {
                    do {                
                      long ps_suppkey = e12->PS_SUPPKEY;
                      long v13 = e12->__av;
                      SUPPLIER_CNTPART1_E1_4.addOrDelOnZero(se12.modify(p_brand,p_type,p_size,ps_suppkey),(v12 * v13));
                      n12 = n12->nxt;
                    } while (n12 && (e12 = n12->obj) && h5 == n12->hash &&  SUPPLIER_CNTPART1_E1_8_mapkey0_idxfn::equals(se13, *e12)); 
                  }
                }
              n11 = n11->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPART1_E1_8_DELTA_map_0123* i13 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_8_DELTA_map_0123*>(SUPPLIER_CNTPART1_E1_8_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPART1_E1_8_DELTA_map_0123::IdxNode* n13; 
          SUPPLIER_CNTPART1_E1_8_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long ps_partkey = e13->PS_PARTKEY;
                STRING_TYPE p_brand = e13->P_BRAND;
                STRING_TYPE p_type = e13->P_TYPE;
                long p_size = e13->P_SIZE;
                long v14 = e13->__av;
                SUPPLIER_CNTPART1_E1_4PARTSUPP1.addOrDelOnZero(se14.modify(ps_partkey,p_brand,p_type,p_size),v14);
              n13 = n13->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123* i14 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123::IdxNode* n14; 
          SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
                long ps_partkey = e14->PS_PARTKEY;
                STRING_TYPE p_brand = e14->P_BRAND;
                STRING_TYPE p_type = e14->P_TYPE;
                long p_size = e14->P_SIZE;
                long v15 = e14->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_8_map_0* i15 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_8_map_0*>(SUPPLIER_CNTPART1_E1_8.index[1]);
                  const HASH_RES_t h6 = SUPPLIER_CNTPART1_E1_8_mapkey0_idxfn::hash(se16.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_8_map_0::IdxNode* n15 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_8_map_0::IdxNode*>(i15->slice(se16, h6));
                  SUPPLIER_CNTPART1_E1_8_entry* e15;
                 
                  if (n15 && (e15 = n15->obj)) {
                    do {                
                      long ps_suppkey = e15->PS_SUPPKEY;
                      long v16 = e15->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_2.addOrDelOnZero(se15.modify(ps_suppkey,p_brand,p_type,p_size),(v15 * v16));
                      n15 = n15->nxt;
                    } while (n15 && (e15 = n15->obj) && h6 == n15->hash &&  SUPPLIER_CNTPART1_E1_8_mapkey0_idxfn::equals(se16, *e15)); 
                  }
                }
              n14 = n14->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123* i16 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123::IdxNode* n16; 
          SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long ps_partkey = e16->PS_PARTKEY;
                STRING_TYPE p_brand = e16->P_BRAND;
                STRING_TYPE p_type = e16->P_TYPE;
                long p_size = e16->P_SIZE;
                long v17 = e16->__av;
                SUPPLIER_CNTPARTSUPP1_E1_4.addOrDelOnZero(se17.modify(ps_partkey,p_brand,p_type,p_size),v17);
              n16 = n16->nxt;
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

        SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA.clear();
        SUPPLIER_CNTSUPPLIER1_DOMAIN1.clear();
        {  
          for (size_t i = 0; i < DELTA_SUPPLIER.size; i++) 
          {
                long ps_suppkey = DELTA_SUPPLIER.suppkey[i];
                // STRING_TYPE s_name = DELTA_SUPPLIER.name[i];
                // STRING_TYPE s_address = DELTA_SUPPLIER.address[i];
                // long s_nationkey = DELTA_SUPPLIER.nationkey[i];
                // STRING_TYPE s_phone = DELTA_SUPPLIER.phone[i];
                // DOUBLE_TYPE s_acctbal = DELTA_SUPPLIER.acctbal[i];
                STRING_TYPE s_comment = DELTA_SUPPLIER.comment[i];
                long preg_match = Upreg_match(preg2,s_comment);
                long v18 = 1L;
                (/*if */(0L != preg_match) ? SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA.addOrDelOnZero(se18.modify(ps_suppkey),v18) : (void)0);            
                long v19 = 1L;
                (/*if */(0L != preg_match) ? SUPPLIER_CNTSUPPLIER1_DOMAIN1.addOrDelOnZero(se19.modify(ps_suppkey),(v19 != 0 ? 1L : 0L)) : (void)0);
          }
        }

        {  // foreach
          const HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0* i19 = static_cast<HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0*>(SUPPLIER_CNTSUPPLIER1_DOMAIN1.index[0]);
          HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0::IdxNode* n19; 
          SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long ps_suppkey = e19->PS_SUPPKEY;
                long v20 = e19->__av;
                agg5.clear();
                
                long l4 = (SUPPLIER_CNTPARTSUPP1_E1_1_L1_1.getValueOrDefault(se21.modify(ps_suppkey)) + SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA.getValueOrDefault(se22.modify(ps_suppkey)));
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0* i20 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[1]);
                  const HASH_RES_t h7 = SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::hash(se23.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode* n20 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode*>(i20->slice(se23, h7));
                  SUPPLIER_CNTPARTSUPP1_E1_2_entry* e20;
                 
                  if (n20 && (e20 = n20->obj)) {
                    do {                
                      STRING_TYPE p_brand = e20->P_BRAND;
                      STRING_TYPE p_type = e20->P_TYPE;
                      long p_size = e20->P_SIZE;
                      long v21 = e20->__av;
                      (/*if */(l4 == 0L) ? agg5.addOrDelOnZero(st4.modify(p_brand,p_type,p_size,v21), v21) : (void)0);
                      n20 = n20->nxt;
                    } while (n20 && (e20 = n20->obj) && h7 == n20->hash &&  SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::equals(se23, *e20)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple4_SSL_L, long>* i21 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg5.index[0]);
                  HashIndex<tuple4_SSL_L, long>::IdxNode* n21; 
                  tuple4_SSL_L* e21;
                
                  for (size_t i = 0; i < i21->size_; i++)
                  {
                    n21 = i21->buckets_ + i;
                    while (n21 && (e21 = n21->obj))
                    {
                      STRING_TYPE p_brand = e21->_1;
                      STRING_TYPE p_type = e21->_2;
                      long p_size = e21->_3;  
                      long v22 = e21->__av; 
                    SUPPLIER_CNT.addOrDelOnZero(se20.modify(p_brand,p_type,p_size),((v20 != 0 ? 1L : 0L) * (v22 != 0 ? 1L : 0L)));      
                      n21 = n21->nxt;
                    }
                  }
                }
              n19 = n19->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0* i22 = static_cast<HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0*>(SUPPLIER_CNTSUPPLIER1_DOMAIN1.index[0]);
          HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0::IdxNode* n22; 
          SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
                long ps_suppkey = e22->PS_SUPPKEY;
                long v23 = e22->__av;
                agg6.clear();
                
                long l5 = SUPPLIER_CNTPARTSUPP1_E1_1_L1_1.getValueOrDefault(se24.modify(ps_suppkey));
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0* i23 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[1]);
                  const HASH_RES_t h8 = SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::hash(se25.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode* n23 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode*>(i23->slice(se25, h8));
                  SUPPLIER_CNTPARTSUPP1_E1_2_entry* e23;
                 
                  if (n23 && (e23 = n23->obj)) {
                    do {                
                      STRING_TYPE p_brand = e23->P_BRAND;
                      STRING_TYPE p_type = e23->P_TYPE;
                      long p_size = e23->P_SIZE;
                      long v24 = e23->__av;
                      (/*if */(l5 == 0L) ? agg6.addOrDelOnZero(st5.modify(p_brand,p_type,p_size,v24), v24) : (void)0);
                      n23 = n23->nxt;
                    } while (n23 && (e23 = n23->obj) && h8 == n23->hash &&  SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::equals(se25, *e23)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple4_SSL_L, long>* i24 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg6.index[0]);
                  HashIndex<tuple4_SSL_L, long>::IdxNode* n24; 
                  tuple4_SSL_L* e24;
                
                  for (size_t i = 0; i < i24->size_; i++)
                  {
                    n24 = i24->buckets_ + i;
                    while (n24 && (e24 = n24->obj))
                    {
                      STRING_TYPE p_brand = e24->_1;
                      STRING_TYPE p_type = e24->_2;
                      long p_size = e24->_3;  
                      long v25 = e24->__av; 
                    SUPPLIER_CNT.addOrDelOnZero(se20.modify(p_brand,p_type,p_size),(((v23 != 0 ? 1L : 0L) * (v25 != 0 ? 1L : 0L)) * -1L));      
                      n24 = n24->nxt;
                    }
                  }
                }
              n22 = n22->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_map_0* i25 = static_cast<HashIndex_SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_map_0*>(SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_map_0::IdxNode* n25; 
          SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry* e25;
        
          for (size_t i = 0; i < i25->size_; i++)
          {
            n25 = i25->buckets_ + i;
            while (n25 && (e25 = n25->obj))
            {
                long ps_suppkey = e25->PS_SUPPKEY;
                long v26 = e25->__av;
                SUPPLIER_CNTPARTSUPP1_E1_1_L1_1.addOrDelOnZero(se26.modify(ps_suppkey),v26);
              n25 = n25->nxt;
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

        SUPPLIER_CNTPARTSUPP1_E1_4_DELTA.clear();
        SUPPLIER_CNTPARTSUPP1_DOMAIN1.clear();
        {  
          for (size_t i = 0; i < DELTA_PARTSUPP.size; i++) 
          {
                long ps_partkey = DELTA_PARTSUPP.partkey[i];
                long ps_suppkey = DELTA_PARTSUPP.suppkey[i];
                // long ps_availqty = DELTA_PARTSUPP.availqty[i];
                // DOUBLE_TYPE ps_supplycost = DELTA_PARTSUPP.supplycost[i];
                // STRING_TYPE ps_comment = DELTA_PARTSUPP.comment[i];
                long v27 = 1L;
                SUPPLIER_CNTPARTSUPP1_E1_4_DELTA.addOrDelOnZero(se27.modify(ps_partkey,ps_suppkey),v27);            
                long v28 = 1L;
                SUPPLIER_CNTPARTSUPP1_DOMAIN1.addOrDelOnZero(se28.modify(ps_suppkey),(v28 != 0 ? 1L : 0L));                
          }
        }
        
        {  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0* i28 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0*>(SUPPLIER_CNTPARTSUPP1_DOMAIN1.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0::IdxNode* n28; 
          SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry* e28;
        
          for (size_t i = 0; i < i28->size_; i++)
          {
            n28 = i28->buckets_ + i;
            while (n28 && (e28 = n28->obj))
            {
                long ps_suppkey = e28->PS_SUPPKEY;
                long v29 = e28->__av;
                long agg7 = 0L;
                long l6 = SUPPLIER_CNTPARTSUPP1_E1_1_L1_1.getValueOrDefault(se30.modify(ps_suppkey));
                (/*if */(l6 == 0L) ? agg7 += 1L : 0L);
                _c2.clear();
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0* i29 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[1]);
                  const HASH_RES_t h9 = SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::hash(se31.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode* n29 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode*>(i29->slice(se31, h9));
                  SUPPLIER_CNTPARTSUPP1_E1_2_entry* e29;
                 
                  if (n29 && (e29 = n29->obj)) {
                    do {                
                      STRING_TYPE p_brand = e29->P_BRAND;
                      STRING_TYPE p_type = e29->P_TYPE;
                      long p_size = e29->P_SIZE;
                      long v31 = e29->__av;
                      _c2.addOrDelOnZero(st6.modify(p_brand,p_type,p_size,v31), v31);
                      n29 = n29->nxt;
                    } while (n29 && (e29 = n29->obj) && h9 == n29->hash &&  SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::equals(se31, *e29)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_1* i30 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_1*>(SUPPLIER_CNTPARTSUPP1_E1_4_DELTA.index[1]);
                  const HASH_RES_t h11 = SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_mapkey1_idxfn::hash(se33.modify1(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_1::IdxNode* n30 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_1::IdxNode*>(i30->slice(se33, h11));
                  SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry* e30;
                 
                  if (n30 && (e30 = n30->obj)) {
                    do {                
                      long ps_partkey = e30->PS_PARTKEY;
                      long v32 = e30->__av;
                      { //slice 
                        const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0* i31 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_4.index[1]);
                        const HASH_RES_t h10 = SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::hash(se32.modify0(ps_partkey));
                        HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode* n31 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode*>(i31->slice(se32, h10));
                        SUPPLIER_CNTPARTSUPP1_E1_4_entry* e31;
                       
                        if (n31 && (e31 = n31->obj)) {
                          do {                
                            STRING_TYPE p_brand = e31->P_BRAND;
                            STRING_TYPE p_type = e31->P_TYPE;
                            long p_size = e31->P_SIZE;
                            long v33 = e31->__av;
                            _c2.addOrDelOnZero(st7.modify(p_brand,p_type,p_size,(v32 * v33)), (v32 * v33));
                            n31 = n31->nxt;
                          } while (n31 && (e31 = n31->obj) && h10 == n31->hash &&  SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::equals(se32, *e31)); 
                        }
                      }
                      n30 = n30->nxt;
                    } while (n30 && (e30 = n30->obj) && h11 == n30->hash &&  SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_mapkey1_idxfn::equals(se33, *e30)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple4_SSL_L, long>* i32 = static_cast<HashIndex<tuple4_SSL_L, long>*>(_c2.index[0]);
                  HashIndex<tuple4_SSL_L, long>::IdxNode* n32; 
                  tuple4_SSL_L* e32;
                
                  for (size_t i = 0; i < i32->size_; i++)
                  {
                    n32 = i32->buckets_ + i;
                    while (n32 && (e32 = n32->obj))
                    {
                      STRING_TYPE p_brand = e32->_1;
                      STRING_TYPE p_type = e32->_2;
                      long p_size = e32->_3;  
                      long v34 = e32->__av; 
                    SUPPLIER_CNT.addOrDelOnZero(se29.modify(p_brand,p_type,p_size),((v29 != 0 ? 1L : 0L) * ((agg7 * v34) != 0 ? 1L : 0L)));      
                      n32 = n32->nxt;
                    }
                  }
                }
              n28 = n28->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0* i33 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0*>(SUPPLIER_CNTPARTSUPP1_DOMAIN1.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0::IdxNode* n33; 
          SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry* e33;
        
          for (size_t i = 0; i < i33->size_; i++)
          {
            n33 = i33->buckets_ + i;
            while (n33 && (e33 = n33->obj))
            {
                long ps_suppkey = e33->PS_SUPPKEY;
                long v35 = e33->__av;
                agg8.clear();
                
                long l7 = SUPPLIER_CNTPARTSUPP1_E1_1_L1_1.getValueOrDefault(se34.modify(ps_suppkey));
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0* i34 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[1]);
                  const HASH_RES_t h12 = SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::hash(se35.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode* n34 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode*>(i34->slice(se35, h12));
                  SUPPLIER_CNTPARTSUPP1_E1_2_entry* e34;
                 
                  if (n34 && (e34 = n34->obj)) {
                    do {                
                      STRING_TYPE p_brand = e34->P_BRAND;
                      STRING_TYPE p_type = e34->P_TYPE;
                      long p_size = e34->P_SIZE;
                      long v36 = e34->__av;
                      (/*if */(l7 == 0L) ? agg8.addOrDelOnZero(st8.modify(p_brand,p_type,p_size,v36), v36) : (void)0);
                      n34 = n34->nxt;
                    } while (n34 && (e34 = n34->obj) && h12 == n34->hash &&  SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::equals(se35, *e34)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple4_SSL_L, long>* i35 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg8.index[0]);
                  HashIndex<tuple4_SSL_L, long>::IdxNode* n35; 
                  tuple4_SSL_L* e35;
                
                  for (size_t i = 0; i < i35->size_; i++)
                  {
                    n35 = i35->buckets_ + i;
                    while (n35 && (e35 = n35->obj))
                    {
                      STRING_TYPE p_brand = e35->_1;
                      STRING_TYPE p_type = e35->_2;
                      long p_size = e35->_3;  
                      long v37 = e35->__av; 
                    SUPPLIER_CNT.addOrDelOnZero(se29.modify(p_brand,p_type,p_size),(((v35 != 0 ? 1L : 0L) * (v37 != 0 ? 1L : 0L)) * -1L));      
                      n35 = n35->nxt;
                    }
                  }
                }
              n33 = n33->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_01* i36 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_4_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_01::IdxNode* n36; 
          SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry* e36;
        
          for (size_t i = 0; i < i36->size_; i++)
          {
            n36 = i36->buckets_ + i;
            while (n36 && (e36 = n36->obj))
            {
                long ps_partkey = e36->PS_PARTKEY;
                long ps_suppkey = e36->PS_SUPPKEY;
                long v38 = e36->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_4PARTSUPP1_map_0* i37 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_4PARTSUPP1_map_0*>(SUPPLIER_CNTPART1_E1_4PARTSUPP1.index[1]);
                  const HASH_RES_t h13 = SUPPLIER_CNTPART1_E1_4PARTSUPP1_mapkey0_idxfn::hash(se37.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_4PARTSUPP1_map_0::IdxNode* n37 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_4PARTSUPP1_map_0::IdxNode*>(i37->slice(se37, h13));
                  SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry* e37;
                 
                  if (n37 && (e37 = n37->obj)) {
                    do {                
                      STRING_TYPE p_brand = e37->P_BRAND;
                      STRING_TYPE p_type = e37->P_TYPE;
                      long p_size = e37->P_SIZE;
                      long v39 = e37->__av;
                      SUPPLIER_CNTPART1_E1_4.addOrDelOnZero(se36.modify(p_brand,p_type,p_size,ps_suppkey),(v38 * v39));
                      n37 = n37->nxt;
                    } while (n37 && (e37 = n37->obj) && h13 == n37->hash &&  SUPPLIER_CNTPART1_E1_4PARTSUPP1_mapkey0_idxfn::equals(se37, *e37)); 
                  }
                }
              n36 = n36->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_01* i38 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_4_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_01::IdxNode* n38; 
          SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry* e38;
        
          for (size_t i = 0; i < i38->size_; i++)
          {
            n38 = i38->buckets_ + i;
            while (n38 && (e38 = n38->obj))
            {
                long ps_partkey = e38->PS_PARTKEY;
                long ps_suppkey = e38->PS_SUPPKEY;
                long v40 = e38->__av;
                SUPPLIER_CNTPART1_E1_8.addOrDelOnZero(se38.modify(ps_partkey,ps_suppkey),v40);
              n38 = n38->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_01* i39 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_4_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map_01::IdxNode* n39; 
          SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry* e39;
        
          for (size_t i = 0; i < i39->size_; i++)
          {
            n39 = i39->buckets_ + i;
            while (n39 && (e39 = n39->obj))
            {
                long ps_partkey = e39->PS_PARTKEY;
                long ps_suppkey = e39->PS_SUPPKEY;
                long v41 = e39->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0* i40 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_4.index[1]);
                  const HASH_RES_t h14 = SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::hash(se40.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode* n40 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode*>(i40->slice(se40, h14));
                  SUPPLIER_CNTPARTSUPP1_E1_4_entry* e40;
                 
                  if (n40 && (e40 = n40->obj)) {
                    do {                
                      STRING_TYPE p_brand = e40->P_BRAND;
                      STRING_TYPE p_type = e40->P_TYPE;
                      long p_size = e40->P_SIZE;
                      long v42 = e40->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_2.addOrDelOnZero(se39.modify(ps_suppkey,p_brand,p_type,p_size),(v41 * v42));
                      n40 = n40->nxt;
                    } while (n40 && (e40 = n40->obj) && h14 == n40->hash &&  SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::equals(se40, *e40)); 
                  }
                }
              n39 = n39->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    SUPPLIER_CNTPART1_E1_8_DELTA_entry se1;
    SUPPLIER_CNTPART1_DOMAIN1_entry se2;
    SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry se3;
    SUPPLIER_CNT_entry se4;
    SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry se5;
    tuple2_L_L st1;
    SUPPLIER_CNTPART1_E1_4_entry se6;
    SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry se7;
    tuple2_L_L st2;
    SUPPLIER_CNTPART1_E1_8_entry se8;
    SUPPLIER_CNTPART1_E1_8_DELTA_entry se9;
    SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry se10;
    tuple2_L_L st3;
    SUPPLIER_CNTPART1_E1_4_entry se11;
    SUPPLIER_CNTPART1_E1_4_entry se12;
    SUPPLIER_CNTPART1_E1_8_entry se13;
    SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry se14;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se15;
    SUPPLIER_CNTPART1_E1_8_entry se16;
    SUPPLIER_CNTPARTSUPP1_E1_4_entry se17;
    SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry se18;
    SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry se19;
    SUPPLIER_CNT_entry se20;
    SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry se21;
    SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_entry se22;
    tuple4_SSL_L st4;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se23;
    SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry se24;
    tuple4_SSL_L st5;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se25;
    SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry se26;
    SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry se27;
    SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry se28;
    SUPPLIER_CNT_entry se29;
    SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry se30;
    tuple4_SSL_L st6;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se31;
    tuple4_SSL_L st7;
    SUPPLIER_CNTPARTSUPP1_E1_4_entry se32;
    SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_entry se33;
    SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_entry se34;
    tuple4_SSL_L st8;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se35;
    SUPPLIER_CNTPART1_E1_4_entry se36;
    SUPPLIER_CNTPART1_E1_4PARTSUPP1_entry se37;
    SUPPLIER_CNTPART1_E1_8_entry se38;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se39;
    SUPPLIER_CNTPARTSUPP1_E1_4_entry se40;
    /* regex_t temporary objects */
    regex_t preg2;
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    SUPPLIER_CNTSUPPLIER1_DOMAIN1_map SUPPLIER_CNTSUPPLIER1_DOMAIN1;
    SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA_map SUPPLIER_CNTSUPPLIER1_E1_1_L1_2_DELTA;
    SUPPLIER_CNTPART1_DOMAIN1_map SUPPLIER_CNTPART1_DOMAIN1;
    SUPPLIER_CNTPART1_E1_4_map SUPPLIER_CNTPART1_E1_4;
    SUPPLIER_CNTPART1_E1_4PARTSUPP1_map SUPPLIER_CNTPART1_E1_4PARTSUPP1;
    SUPPLIER_CNTPART1_E1_8_DELTA_map SUPPLIER_CNTPART1_E1_8_DELTA;
    SUPPLIER_CNTPART1_E1_8_map SUPPLIER_CNTPART1_E1_8;
    SUPPLIER_CNTPARTSUPP1_DOMAIN1_map SUPPLIER_CNTPARTSUPP1_DOMAIN1;
    SUPPLIER_CNTPARTSUPP1_E1_1_L1_1_map SUPPLIER_CNTPARTSUPP1_E1_1_L1_1;
    SUPPLIER_CNTPARTSUPP1_E1_2_map SUPPLIER_CNTPARTSUPP1_E1_2;
    SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA;
    SUPPLIER_CNTPARTSUPP1_E1_4_DELTA_map SUPPLIER_CNTPARTSUPP1_E1_4_DELTA;
    SUPPLIER_CNTPARTSUPP1_E1_4_map SUPPLIER_CNTPARTSUPP1_E1_4;
    DELTA_PART_map DELTA_PART;
    DELTA_SUPPLIER_map DELTA_SUPPLIER;
    DELTA_PARTSUPP_map DELTA_PARTSUPP;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg6;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > _c1;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg8;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg5;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg4;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > _c2;
    /*const static*/ STRING_TYPE c1;
  
  };

}
