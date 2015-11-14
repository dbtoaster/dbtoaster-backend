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
  
  struct SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry {
    long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry() { /*PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry(const long c0, const long c1) { PS_SUPPKEY = c0; __av = c1; }
    SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry(const SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry& modify(const long c0) { PS_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry& x, const SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry,long,SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_mapkey0_idxfn,true>
  > SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry,long,SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_mapkey0_idxfn,true> HashIndex_SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_map_0;
  
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
  
  struct SUPPLIER_CNTPART1_E1_1_entry {
    long PS_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPART1_E1_1_entry() { /*PS_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPART1_E1_1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPART1_E1_1_entry(const SUPPLIER_CNTPART1_E1_1_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPART1_E1_1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPART1_E1_1_entry& modify123(const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
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
  struct SUPPLIER_CNTPART1_E1_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_1_entry& x, const SUPPLIER_CNTPART1_E1_1_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPART1_E1_1_mapkey123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_1_entry& x, const SUPPLIER_CNTPART1_E1_1_entry& y) {
      return x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPART1_E1_1_entry,long,
    HashIndex<SUPPLIER_CNTPART1_E1_1_entry,long,SUPPLIER_CNTPART1_E1_1_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPART1_E1_1_entry,long,SUPPLIER_CNTPART1_E1_1_mapkey123_idxfn,false>
  > SUPPLIER_CNTPART1_E1_1_map;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_1_entry,long,SUPPLIER_CNTPART1_E1_1_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPART1_E1_1_map_0123;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_1_entry,long,SUPPLIER_CNTPART1_E1_1_mapkey123_idxfn,false> HashIndex_SUPPLIER_CNTPART1_E1_1_map_123;
  
  struct SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry(const SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPART1_E1_1PARTSUPP1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry& x, const SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPART1_E1_1PARTSUPP1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry& x, const SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry,long,
    HashIndex<SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry,long,SUPPLIER_CNTPART1_E1_1PARTSUPP1_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry,long,SUPPLIER_CNTPART1_E1_1PARTSUPP1_mapkey0_idxfn,false>
  > SUPPLIER_CNTPART1_E1_1PARTSUPP1_map;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry,long,SUPPLIER_CNTPART1_E1_1PARTSUPP1_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPART1_E1_1PARTSUPP1_map_0123;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry,long,SUPPLIER_CNTPART1_E1_1PARTSUPP1_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPART1_E1_1PARTSUPP1_map_0;
  
  struct SUPPLIER_CNTPART1_E1_33_DELTA_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPART1_E1_33_DELTA_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPART1_E1_33_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPART1_E1_33_DELTA_entry(const SUPPLIER_CNTPART1_E1_33_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPART1_E1_33_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPART1_E1_33_DELTA_entry& modify123(const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
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
  struct SUPPLIER_CNTPART1_E1_33_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_33_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_33_DELTA_entry& x, const SUPPLIER_CNTPART1_E1_33_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPART1_E1_33_DELTA_mapkey123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_33_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_33_DELTA_entry& x, const SUPPLIER_CNTPART1_E1_33_DELTA_entry& y) {
      return x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPART1_E1_33_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTPART1_E1_33_DELTA_entry,long,SUPPLIER_CNTPART1_E1_33_DELTA_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPART1_E1_33_DELTA_entry,long,SUPPLIER_CNTPART1_E1_33_DELTA_mapkey123_idxfn,false>
  > SUPPLIER_CNTPART1_E1_33_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_33_DELTA_entry,long,SUPPLIER_CNTPART1_E1_33_DELTA_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPART1_E1_33_DELTA_map_0123;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_33_DELTA_entry,long,SUPPLIER_CNTPART1_E1_33_DELTA_mapkey123_idxfn,false> HashIndex_SUPPLIER_CNTPART1_E1_33_DELTA_map_123;
  
  struct SUPPLIER_CNTPART1_E1_33_entry {
    long PS_PARTKEY; long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTPART1_E1_33_entry() { /*PS_PARTKEY = 0L; PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPART1_E1_33_entry(const long c0, const long c1, const long c2) { PS_PARTKEY = c0; PS_SUPPKEY = c1; __av = c2; }
    SUPPLIER_CNTPART1_E1_33_entry(const SUPPLIER_CNTPART1_E1_33_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPART1_E1_33_entry& modify(const long c0, const long c1) { PS_PARTKEY = c0; PS_SUPPKEY = c1;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPART1_E1_33_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPART1_E1_33_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_33_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_33_entry& x, const SUPPLIER_CNTPART1_E1_33_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  struct SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART1_E1_33_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART1_E1_33_entry& x, const SUPPLIER_CNTPART1_E1_33_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPART1_E1_33_entry,long,
    HashIndex<SUPPLIER_CNTPART1_E1_33_entry,long,SUPPLIER_CNTPART1_E1_33_mapkey01_idxfn,true>,
    HashIndex<SUPPLIER_CNTPART1_E1_33_entry,long,SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn,false>
  > SUPPLIER_CNTPART1_E1_33_map;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_33_entry,long,SUPPLIER_CNTPART1_E1_33_mapkey01_idxfn,true> HashIndex_SUPPLIER_CNTPART1_E1_33_map_01;
  typedef HashIndex<SUPPLIER_CNTPART1_E1_33_entry,long,SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPART1_E1_33_map_0;
  
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
  
  struct SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry {
    long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry() { /*PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry(const long c0, const long c1) { PS_SUPPKEY = c0; __av = c1; }
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry(const SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry& modify(const long c0) { PS_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry,long,SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_mapkey0_idxfn,true>
  > SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry,long,SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_mapkey0_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_map_0;
  
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
  
  struct SUPPLIER_CNTPARTSUPP1_E1_4_entry {
    long PS_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_4_entry() { /*PS_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_4_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_4_entry(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_4_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_4_entry& modify0(const long c0) { PS_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_4_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_4_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_4_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry(const SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_mapkey0123_idxfn,true>
  > SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_map_0123;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_6_entry {
    long PS_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_6_entry() { /*PS_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_6_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_6_entry(const SUPPLIER_CNTPARTSUPP1_E1_6_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_6_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_6_entry& modify0(const long c0) { PS_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_6_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_6_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_6_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_6_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_6_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_6_entry,long,SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_6_entry,long,SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_6_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_6_entry,long,SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_6_entry,long,SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry(const SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_mapkey0123_idxfn,true>
  > SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_map_0123;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_8_entry {
    long PS_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_8_entry() { /*PS_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_8_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_8_entry(const SUPPLIER_CNTPARTSUPP1_E1_8_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_8_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_8_entry& modify0(const long c0) { PS_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_8_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_8_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_8_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_8_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_8_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_8_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_8_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_8_entry,long,SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_8_entry,long,SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_8_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_8_entry,long,SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_8_entry,long,SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry(const SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_mapkey0123_idxfn,true>
  > SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_map_0123;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_10_entry {
    long PS_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_10_entry() { /*PS_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_10_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_10_entry(const SUPPLIER_CNTPARTSUPP1_E1_10_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_10_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_10_entry& modify0(const long c0) { PS_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_10_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_10_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_10_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_10_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_10_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_10_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_10_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_10_entry,long,SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_10_entry,long,SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_10_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_10_entry,long,SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_10_entry,long,SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry(const SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_mapkey0123_idxfn,true>
  > SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_map_0123;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_12_entry {
    long PS_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_12_entry() { /*PS_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_12_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_12_entry(const SUPPLIER_CNTPARTSUPP1_E1_12_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_12_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_12_entry& modify0(const long c0) { PS_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_12_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_12_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_12_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_12_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_12_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_12_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_12_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_12_entry,long,SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_12_entry,long,SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_12_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_12_entry,long,SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_12_entry,long,SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry(const SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_mapkey0123_idxfn,true>
  > SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_map_0123;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_14_entry {
    long PS_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_14_entry() { /*PS_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_14_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_14_entry(const SUPPLIER_CNTPARTSUPP1_E1_14_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_14_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_14_entry& modify0(const long c0) { PS_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_14_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_14_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_14_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_14_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_14_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_14_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_14_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_14_entry,long,SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_14_entry,long,SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_14_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_14_entry,long,SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_14_entry,long,SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry(const SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_mapkey0123_idxfn,true>
  > SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_map_0123;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_16_entry {
    long PS_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_16_entry() { /*PS_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_16_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_16_entry(const SUPPLIER_CNTPARTSUPP1_E1_16_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_16_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_16_entry& modify0(const long c0) { PS_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_16_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_16_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_16_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_16_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_16_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_16_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_16_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_16_entry,long,SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_16_entry,long,SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_16_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_16_entry,long,SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_16_entry,long,SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry(const SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_mapkey0123_idxfn,true>
  > SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_map_0123;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry {
    long PS_PARTKEY; long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry() { /*PS_PARTKEY = 0L; PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry(const long c0, const long c1, const long c2) { PS_PARTKEY = c0; PS_SUPPKEY = c1; __av = c2; }
    SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry(const SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry& modify(const long c0, const long c1) { PS_PARTKEY = c0; PS_SUPPKEY = c1;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry& modify1(const long c1) { PS_SUPPKEY = c1;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_mapkey01_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_mapkey1_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_mapkey01_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry,long,SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_mapkey1_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_1;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_18_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_18_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_18_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_18_entry(const SUPPLIER_CNTPARTSUPP1_E1_18_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_18_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_18_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_18_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_18_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_18_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_18_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_18_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_18_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_18_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_18_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_18_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_18_entry,long,SUPPLIER_CNTPARTSUPP1_E1_18_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_18_entry,long,SUPPLIER_CNTPARTSUPP1_E1_18_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_18_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_18_entry,long,SUPPLIER_CNTPARTSUPP1_E1_18_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_18_entry,long,SUPPLIER_CNTPARTSUPP1_E1_18_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_20_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_20_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_20_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_20_entry(const SUPPLIER_CNTPARTSUPP1_E1_20_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_20_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_20_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_20_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_20_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_20_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_20_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_20_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_20_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_20_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_20_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_20_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_20_entry,long,SUPPLIER_CNTPARTSUPP1_E1_20_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_20_entry,long,SUPPLIER_CNTPARTSUPP1_E1_20_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_20_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_20_entry,long,SUPPLIER_CNTPARTSUPP1_E1_20_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_20_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_20_entry,long,SUPPLIER_CNTPARTSUPP1_E1_20_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_20_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_22_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_22_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_22_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_22_entry(const SUPPLIER_CNTPARTSUPP1_E1_22_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_22_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_22_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_22_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_22_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_22_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_22_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_22_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_22_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_22_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_22_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_22_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_22_entry,long,SUPPLIER_CNTPARTSUPP1_E1_22_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_22_entry,long,SUPPLIER_CNTPARTSUPP1_E1_22_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_22_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_22_entry,long,SUPPLIER_CNTPARTSUPP1_E1_22_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_22_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_22_entry,long,SUPPLIER_CNTPARTSUPP1_E1_22_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_22_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_24_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_24_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_24_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_24_entry(const SUPPLIER_CNTPARTSUPP1_E1_24_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_24_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_24_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_24_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_24_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_24_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_24_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_24_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_24_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_24_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_24_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_24_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_24_entry,long,SUPPLIER_CNTPARTSUPP1_E1_24_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_24_entry,long,SUPPLIER_CNTPARTSUPP1_E1_24_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_24_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_24_entry,long,SUPPLIER_CNTPARTSUPP1_E1_24_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_24_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_24_entry,long,SUPPLIER_CNTPARTSUPP1_E1_24_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_24_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_26_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_26_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_26_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_26_entry(const SUPPLIER_CNTPARTSUPP1_E1_26_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_26_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_26_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_26_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_26_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_26_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_26_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_26_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_26_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_26_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_26_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_26_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_26_entry,long,SUPPLIER_CNTPARTSUPP1_E1_26_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_26_entry,long,SUPPLIER_CNTPARTSUPP1_E1_26_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_26_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_26_entry,long,SUPPLIER_CNTPARTSUPP1_E1_26_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_26_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_26_entry,long,SUPPLIER_CNTPARTSUPP1_E1_26_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_26_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_28_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_28_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_28_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_28_entry(const SUPPLIER_CNTPARTSUPP1_E1_28_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_28_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_28_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_28_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_28_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_28_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_28_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_28_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_28_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_28_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_28_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_28_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_28_entry,long,SUPPLIER_CNTPARTSUPP1_E1_28_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_28_entry,long,SUPPLIER_CNTPARTSUPP1_E1_28_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_28_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_28_entry,long,SUPPLIER_CNTPARTSUPP1_E1_28_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_28_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_28_entry,long,SUPPLIER_CNTPARTSUPP1_E1_28_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_28_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_30_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_30_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_30_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_30_entry(const SUPPLIER_CNTPARTSUPP1_E1_30_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_30_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_30_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_30_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_30_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_30_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_30_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_30_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_30_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_30_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_30_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_30_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_30_entry,long,SUPPLIER_CNTPARTSUPP1_E1_30_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_30_entry,long,SUPPLIER_CNTPARTSUPP1_E1_30_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_30_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_30_entry,long,SUPPLIER_CNTPARTSUPP1_E1_30_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_30_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_30_entry,long,SUPPLIER_CNTPARTSUPP1_E1_30_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_30_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_32_entry {
    long PS_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_32_entry() { /*PS_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_32_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_32_entry(const SUPPLIER_CNTPARTSUPP1_E1_32_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_32_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_32_entry& modify0(const long c0) { PS_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNTPARTSUPP1_E1_32_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_32_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_32_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_32_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_32_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_32_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_32_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_32_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_32_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_32_entry,long,SUPPLIER_CNTPARTSUPP1_E1_32_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_32_entry,long,SUPPLIER_CNTPARTSUPP1_E1_32_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_32_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_32_entry,long,SUPPLIER_CNTPARTSUPP1_E1_32_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_32_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_32_entry,long,SUPPLIER_CNTPARTSUPP1_E1_32_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_32_map_0;
  
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
  struct tuple5_LSSL_L {
    long _1; STRING_TYPE _2; STRING_TYPE _3; long _4; long __av;
    explicit tuple5_LSSL_L() { }
    explicit tuple5_LSSL_L(const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; __av = c__av;}
    int operator==(const tuple5_LSSL_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4)); }
    FORCE_INLINE tuple5_LSSL_L& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; __av = c__av; return *this; }
    static bool equals(const tuple5_LSSL_L &x, const tuple5_LSSL_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4)); }
    static long hash(const tuple5_LSSL_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
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
    data_t(): tlq_t(), agg11(16U), agg6(16U), agg13(16U), agg8(16U), agg2(16U), agg10(16U), agg4(16U), agg12(16U), agg7(16U), agg1(16U), agg14(16U), agg9(16U) {
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

        SUPPLIER_CNTPART1_E1_33_DELTA.clear();
        SUPPLIER_CNTPART1_DOMAIN1.clear();
        SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA.clear();
        SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA.clear();
        SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA.clear();
        SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA.clear();
        SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA.clear();
        SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA.clear();
        SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA.clear();
        SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_PART.size; i++)
          {
                long ps_partkey = DELTA_PART.partkey[i];
                STRING_TYPE p_name = DELTA_PART.name[i];
                STRING_TYPE p_mfgr = DELTA_PART.mfgr[i];
                STRING_TYPE p_brand = DELTA_PART.brand[i];
                STRING_TYPE p_type = DELTA_PART.type[i];
                long p_size = DELTA_PART.psize[i];
                STRING_TYPE p_container = DELTA_PART.container[i];
                DOUBLE_TYPE p_retailprice = DELTA_PART.retailprice[i];
                STRING_TYPE p_comment = DELTA_PART.comment[i];
                long v1 = 1L;
                SUPPLIER_CNTPART1_E1_33_DELTA.addOrDelOnZero(se1.modify(ps_partkey,p_brand,p_type,p_size),v1);            
                long v2 = 1L;
                long upreg_match = Upreg_match(preg1,p_type);
                (/*if */(p_brand != c1 && 0L == upreg_match) ? SUPPLIER_CNTPART1_DOMAIN1.addOrDelOnZero(se2.modify(p_brand,p_type,p_size),(v2 != 0 ? 1L : 0L)) : (void)0);
                long v3 = 1L;
                (/*if */(p_size == 49L && p_brand != c1 && 0L == upreg_match) ? SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA.addOrDelOnZero(se3.modify(ps_partkey,p_brand,p_type,p_size),v3) : (void)0);
                long v4 = 1L;
                (/*if */(p_size == 14L && p_brand != c1 && 0L == upreg_match) ? SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA.addOrDelOnZero(se4.modify(ps_partkey,p_brand,p_type,p_size),v4) : (void)0);
                long v5 = 1L;
                (/*if */(p_size == 23L && p_brand != c1 && 0L == upreg_match) ? SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA.addOrDelOnZero(se5.modify(ps_partkey,p_brand,p_type,p_size),v5) : (void)0);
                long v6 = 1L;
                (/*if */(p_size == 45L && p_brand != c1 && 0L == upreg_match) ? SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA.addOrDelOnZero(se6.modify(ps_partkey,p_brand,p_type,p_size),v6) : (void)0);
                long v7 = 1L;
                (/*if */(p_size == 19L && p_brand != c1 && 0L == upreg_match) ? SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA.addOrDelOnZero(se7.modify(ps_partkey,p_brand,p_type,p_size),v7) : (void)0);
                long v8 = 1L;
                (/*if */(p_size == 3L && p_brand != c1 && 0L == upreg_match) ? SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA.addOrDelOnZero(se8.modify(ps_partkey,p_brand,p_type,p_size),v8) : (void)0);
                long v9 = 1L;
                (/*if */(p_size == 36L && p_brand != c1 && 0L == upreg_match) ? SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA.addOrDelOnZero(se9.modify(ps_partkey,p_brand,p_type,p_size),v9) : (void)0);
                long v10 = 1L;
                (/*if */(p_size == 9L && p_brand != c1 && 0L == upreg_match) ? SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA.addOrDelOnZero(se10.modify(ps_partkey,p_brand,p_type,p_size),v10) : (void)0);
          }
        }
        
        agg1.clear();
        
        agg2.clear();
        
        long l1 = 0L;
        {  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0123* i11 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0123::IdxNode* n11; 
          SUPPLIER_CNTPARTSUPP1_E1_2_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long ps_suppkey = e11->PS_SUPPKEY;
                STRING_TYPE p_brand = e11->P_BRAND;
                STRING_TYPE p_type = e11->P_TYPE;
                long p_size = e11->P_SIZE;
                long v11 = e11->__av;
                (/*if */(l1 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se12.modify(ps_suppkey))) ? agg2.addOrDelOnZero(st1.modify(ps_suppkey,p_brand,p_type,p_size,v11), v11) : (void)0);
              n11 = n11->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0123* i12 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_4.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0123::IdxNode* n12; 
          SUPPLIER_CNTPARTSUPP1_E1_4_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long ps_suppkey = e12->PS_SUPPKEY;
                STRING_TYPE p_brand = e12->P_BRAND;
                STRING_TYPE p_type = e12->P_TYPE;
                long p_size = e12->P_SIZE;
                long v12 = e12->__av;
                (/*if */(l1 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se13.modify(ps_suppkey))) ? agg2.addOrDelOnZero(st2.modify(ps_suppkey,p_brand,p_type,p_size,v12), v12) : (void)0);
              n12 = n12->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0123* i13 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_6.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0123::IdxNode* n13; 
          SUPPLIER_CNTPARTSUPP1_E1_6_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long ps_suppkey = e13->PS_SUPPKEY;
                STRING_TYPE p_brand = e13->P_BRAND;
                STRING_TYPE p_type = e13->P_TYPE;
                long p_size = e13->P_SIZE;
                long v13 = e13->__av;
                (/*if */(l1 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se14.modify(ps_suppkey))) ? agg2.addOrDelOnZero(st3.modify(ps_suppkey,p_brand,p_type,p_size,v13), v13) : (void)0);
              n13 = n13->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0123* i14 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_8.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0123::IdxNode* n14; 
          SUPPLIER_CNTPARTSUPP1_E1_8_entry* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
                long ps_suppkey = e14->PS_SUPPKEY;
                STRING_TYPE p_brand = e14->P_BRAND;
                STRING_TYPE p_type = e14->P_TYPE;
                long p_size = e14->P_SIZE;
                long v14 = e14->__av;
                (/*if */(l1 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se15.modify(ps_suppkey))) ? agg2.addOrDelOnZero(st4.modify(ps_suppkey,p_brand,p_type,p_size,v14), v14) : (void)0);
              n14 = n14->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0123* i15 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_10.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0123::IdxNode* n15; 
          SUPPLIER_CNTPARTSUPP1_E1_10_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long ps_suppkey = e15->PS_SUPPKEY;
                STRING_TYPE p_brand = e15->P_BRAND;
                STRING_TYPE p_type = e15->P_TYPE;
                long p_size = e15->P_SIZE;
                long v15 = e15->__av;
                (/*if */(l1 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se16.modify(ps_suppkey))) ? agg2.addOrDelOnZero(st5.modify(ps_suppkey,p_brand,p_type,p_size,v15), v15) : (void)0);
              n15 = n15->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0123* i16 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_12.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0123::IdxNode* n16; 
          SUPPLIER_CNTPARTSUPP1_E1_12_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long ps_suppkey = e16->PS_SUPPKEY;
                STRING_TYPE p_brand = e16->P_BRAND;
                STRING_TYPE p_type = e16->P_TYPE;
                long p_size = e16->P_SIZE;
                long v16 = e16->__av;
                (/*if */(l1 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se17.modify(ps_suppkey))) ? agg2.addOrDelOnZero(st6.modify(ps_suppkey,p_brand,p_type,p_size,v16), v16) : (void)0);
              n16 = n16->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0123* i17 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_14.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0123::IdxNode* n17; 
          SUPPLIER_CNTPARTSUPP1_E1_14_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long ps_suppkey = e17->PS_SUPPKEY;
                STRING_TYPE p_brand = e17->P_BRAND;
                STRING_TYPE p_type = e17->P_TYPE;
                long p_size = e17->P_SIZE;
                long v17 = e17->__av;
                (/*if */(l1 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se18.modify(ps_suppkey))) ? agg2.addOrDelOnZero(st7.modify(ps_suppkey,p_brand,p_type,p_size,v17), v17) : (void)0);
              n17 = n17->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0123* i18 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_16.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0123::IdxNode* n18; 
          SUPPLIER_CNTPARTSUPP1_E1_16_entry* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
                long ps_suppkey = e18->PS_SUPPKEY;
                STRING_TYPE p_brand = e18->P_BRAND;
                STRING_TYPE p_type = e18->P_TYPE;
                long p_size = e18->P_SIZE;
                long v18 = e18->__av;
                (/*if */(l1 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se19.modify(ps_suppkey))) ? agg2.addOrDelOnZero(st8.modify(ps_suppkey,p_brand,p_type,p_size,v18), v18) : (void)0);
              n18 = n18->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple5_LSSL_L, long>* i19 = static_cast<HashIndex<tuple5_LSSL_L, long>*>(agg2.index[0]);
          HashIndex<tuple5_LSSL_L, long>::IdxNode* n19; 
          tuple5_LSSL_L* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
              long ps_suppkey = e19->_1;
              STRING_TYPE p_brand = e19->_2;
              STRING_TYPE p_type = e19->_3;
              long p_size = e19->_4;  
              long v19 = e19->__av; 
            agg1.addOrDelOnZero(st9.modify(p_brand,p_type,p_size,(v19 != 0 ? 1L : 0L)), (v19 != 0 ? 1L : 0L));      
              n19 = n19->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i20 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg1.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n20; 
          tuple4_SSL_L* e20;
        
          for (size_t i = 0; i < i20->size_; i++)
          {
            n20 = i20->buckets_ + i;
            while (n20 && (e20 = n20->obj))
            {
              STRING_TYPE p_brand = e20->_1;
              STRING_TYPE p_type = e20->_2;
              long p_size = e20->_3;  
              long v20 = e20->__av; 
            if (SUPPLIER_CNT.getValueOrDefault(se11.modify(p_brand,p_type,p_size))==0) SUPPLIER_CNT.setOrDelOnZero(se11, v20);      
              n20 = n20->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPART1_DOMAIN1_map_012* i21 = static_cast<HashIndex_SUPPLIER_CNTPART1_DOMAIN1_map_012*>(SUPPLIER_CNTPART1_DOMAIN1.index[0]);
          HashIndex_SUPPLIER_CNTPART1_DOMAIN1_map_012::IdxNode* n21; 
          SUPPLIER_CNTPART1_DOMAIN1_entry* e21;
        
          for (size_t i = 0; i < i21->size_; i++)
          {
            n21 = i21->buckets_ + i;
            while (n21 && (e21 = n21->obj))
            {
                STRING_TYPE p_brand = e21->P_BRAND;
                STRING_TYPE p_type = e21->P_TYPE;
                long p_size = e21->P_SIZE;
                long v21 = e21->__av;
                long agg3 = 0L;
                agg4.clear();
                
                long l2 = 0L;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_1_map_123* i22 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_1_map_123*>(SUPPLIER_CNTPART1_E1_1.index[1]);
                  const HASH_RES_t h1 = SUPPLIER_CNTPART1_E1_1_mapkey123_idxfn::hash(se21.modify123(p_brand, p_type, p_size));
                  HashIndex_SUPPLIER_CNTPART1_E1_1_map_123::IdxNode* n22 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_1_map_123::IdxNode*>(i22->slice(se21, h1));
                  SUPPLIER_CNTPART1_E1_1_entry* e22;
                 
                  if (n22 && (e22 = n22->obj)) {
                    do {                
                      long ps_suppkey = e22->PS_SUPPKEY;
                      long v22 = e22->__av;
                      (/*if */(p_brand != c1 && 0L == Upreg_match(preg1,p_type) && l2 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se20.modify(ps_suppkey))) ? agg4.addOrDelOnZero(st10.modify(ps_suppkey,(((/*if */(p_size == 49L) ? 1L : 0L) + ((/*if */(p_size == 14L) ? 1L : 0L) + ((/*if */(p_size == 23L) ? 1L : 0L) + ((/*if */(p_size == 45L) ? 1L : 0L) + ((/*if */(p_size == 19L) ? 1L : 0L) + ((/*if */(p_size == 3L) ? 1L : 0L) + ((/*if */(p_size == 36L) ? 1L : 0L) + (/*if */(p_size == 9L) ? 1L : 0L)))))))) * v22)), (((/*if */(p_size == 49L) ? 1L : 0L) + ((/*if */(p_size == 14L) ? 1L : 0L) + ((/*if */(p_size == 23L) ? 1L : 0L) + ((/*if */(p_size == 45L) ? 1L : 0L) + ((/*if */(p_size == 19L) ? 1L : 0L) + ((/*if */(p_size == 3L) ? 1L : 0L) + ((/*if */(p_size == 36L) ? 1L : 0L) + (/*if */(p_size == 9L) ? 1L : 0L)))))))) * v22)) : (void)0);
                      n22 = n22->nxt;
                    } while (n22 && (e22 = n22->obj) && h1 == n22->hash &&  SUPPLIER_CNTPART1_E1_1_mapkey123_idxfn::equals(se21, *e22)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_33_DELTA_map_123* i23 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_DELTA_map_123*>(SUPPLIER_CNTPART1_E1_33_DELTA.index[1]);
                  const HASH_RES_t h3 = SUPPLIER_CNTPART1_E1_33_DELTA_mapkey123_idxfn::hash(se24.modify123(p_brand, p_type, p_size));
                  HashIndex_SUPPLIER_CNTPART1_E1_33_DELTA_map_123::IdxNode* n23 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_DELTA_map_123::IdxNode*>(i23->slice(se24, h3));
                  SUPPLIER_CNTPART1_E1_33_DELTA_entry* e23;
                 
                  if (n23 && (e23 = n23->obj)) {
                    do {                
                      long ps_partkey = e23->PS_PARTKEY;
                      long v23 = e23->__av;
                      { //slice 
                        const HashIndex_SUPPLIER_CNTPART1_E1_33_map_0* i24 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0*>(SUPPLIER_CNTPART1_E1_33.index[1]);
                        const HASH_RES_t h2 = SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::hash(se23.modify0(ps_partkey));
                        HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode* n24 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode*>(i24->slice(se23, h2));
                        SUPPLIER_CNTPART1_E1_33_entry* e24;
                       
                        if (n24 && (e24 = n24->obj)) {
                          do {                
                            long ps_suppkey = e24->PS_SUPPKEY;
                            long v24 = e24->__av;
                            (/*if */(p_brand != c1 && 0L == Upreg_match(preg1,p_type) && l2 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se22.modify(ps_suppkey))) ? agg4.addOrDelOnZero(st11.modify(ps_suppkey,(((/*if */(p_size == 49L) ? 1L : 0L) + ((/*if */(p_size == 14L) ? 1L : 0L) + ((/*if */(p_size == 23L) ? 1L : 0L) + ((/*if */(p_size == 45L) ? 1L : 0L) + ((/*if */(p_size == 19L) ? 1L : 0L) + ((/*if */(p_size == 3L) ? 1L : 0L) + ((/*if */(p_size == 36L) ? 1L : 0L) + (/*if */(p_size == 9L) ? 1L : 0L)))))))) * (v23 * v24))), (((/*if */(p_size == 49L) ? 1L : 0L) + ((/*if */(p_size == 14L) ? 1L : 0L) + ((/*if */(p_size == 23L) ? 1L : 0L) + ((/*if */(p_size == 45L) ? 1L : 0L) + ((/*if */(p_size == 19L) ? 1L : 0L) + ((/*if */(p_size == 3L) ? 1L : 0L) + ((/*if */(p_size == 36L) ? 1L : 0L) + (/*if */(p_size == 9L) ? 1L : 0L)))))))) * (v23 * v24))) : (void)0);
                            n24 = n24->nxt;
                          } while (n24 && (e24 = n24->obj) && h2 == n24->hash &&  SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::equals(se23, *e24)); 
                        }
                      }
                      n23 = n23->nxt;
                    } while (n23 && (e23 = n23->obj) && h3 == n23->hash &&  SUPPLIER_CNTPART1_E1_33_DELTA_mapkey123_idxfn::equals(se24, *e23)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple2_L_L, long>* i25 = static_cast<HashIndex<tuple2_L_L, long>*>(agg4.index[0]);
                  HashIndex<tuple2_L_L, long>::IdxNode* n25; 
                  tuple2_L_L* e25;
                
                  for (size_t i = 0; i < i25->size_; i++)
                  {
                    n25 = i25->buckets_ + i;
                    while (n25 && (e25 = n25->obj))
                    {
                      long ps_suppkey = e25->_1;  
                      long v25 = e25->__av; 
                    agg3 += (v25 != 0 ? 1L : 0L);      
                      n25 = n25->nxt;
                    }
                  }
                }long agg5 = 0L;
                agg6.clear();
                
                long l3 = 0L;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_1_map_123* i26 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_1_map_123*>(SUPPLIER_CNTPART1_E1_1.index[1]);
                  const HASH_RES_t h4 = SUPPLIER_CNTPART1_E1_1_mapkey123_idxfn::hash(se26.modify123(p_brand, p_type, p_size));
                  HashIndex_SUPPLIER_CNTPART1_E1_1_map_123::IdxNode* n26 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_1_map_123::IdxNode*>(i26->slice(se26, h4));
                  SUPPLIER_CNTPART1_E1_1_entry* e26;
                 
                  if (n26 && (e26 = n26->obj)) {
                    do {                
                      long ps_suppkey = e26->PS_SUPPKEY;
                      long v26 = e26->__av;
                      (/*if */(l3 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se25.modify(ps_suppkey)) && p_brand != c1 && 0L == Upreg_match(preg1,p_type)) ? agg6.addOrDelOnZero(st12.modify(ps_suppkey,(v26 * ((/*if */(p_size == 49L) ? 1L : 0L) + ((/*if */(p_size == 14L) ? 1L : 0L) + ((/*if */(p_size == 23L) ? 1L : 0L) + ((/*if */(p_size == 45L) ? 1L : 0L) + ((/*if */(p_size == 19L) ? 1L : 0L) + ((/*if */(p_size == 3L) ? 1L : 0L) + ((/*if */(p_size == 36L) ? 1L : 0L) + (/*if */(p_size == 9L) ? 1L : 0L)))))))))), (v26 * ((/*if */(p_size == 49L) ? 1L : 0L) + ((/*if */(p_size == 14L) ? 1L : 0L) + ((/*if */(p_size == 23L) ? 1L : 0L) + ((/*if */(p_size == 45L) ? 1L : 0L) + ((/*if */(p_size == 19L) ? 1L : 0L) + ((/*if */(p_size == 3L) ? 1L : 0L) + ((/*if */(p_size == 36L) ? 1L : 0L) + (/*if */(p_size == 9L) ? 1L : 0L)))))))))) : (void)0);
                      n26 = n26->nxt;
                    } while (n26 && (e26 = n26->obj) && h4 == n26->hash &&  SUPPLIER_CNTPART1_E1_1_mapkey123_idxfn::equals(se26, *e26)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple2_L_L, long>* i27 = static_cast<HashIndex<tuple2_L_L, long>*>(agg6.index[0]);
                  HashIndex<tuple2_L_L, long>::IdxNode* n27; 
                  tuple2_L_L* e27;
                
                  for (size_t i = 0; i < i27->size_; i++)
                  {
                    n27 = i27->buckets_ + i;
                    while (n27 && (e27 = n27->obj))
                    {
                      long ps_suppkey = e27->_1;  
                      long v27 = e27->__av; 
                    agg5 += (v27 != 0 ? 1L : 0L);      
                      n27 = n27->nxt;
                    }
                  }
                }SUPPLIER_CNT.addOrDelOnZero(se11.modify(p_brand,p_type,p_size),((v21 != 0 ? 1L : 0L) * (agg3 + (agg5 * -1L))));
              n21 = n21->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPART1_E1_33_DELTA_map_0123* i28 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_DELTA_map_0123*>(SUPPLIER_CNTPART1_E1_33_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPART1_E1_33_DELTA_map_0123::IdxNode* n28; 
          SUPPLIER_CNTPART1_E1_33_DELTA_entry* e28;
        
          for (size_t i = 0; i < i28->size_; i++)
          {
            n28 = i28->buckets_ + i;
            while (n28 && (e28 = n28->obj))
            {
                long ps_partkey = e28->PS_PARTKEY;
                STRING_TYPE p_brand = e28->P_BRAND;
                STRING_TYPE p_type = e28->P_TYPE;
                long p_size = e28->P_SIZE;
                long v28 = e28->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_33_map_0* i29 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0*>(SUPPLIER_CNTPART1_E1_33.index[1]);
                  const HASH_RES_t h5 = SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::hash(se28.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode* n29 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode*>(i29->slice(se28, h5));
                  SUPPLIER_CNTPART1_E1_33_entry* e29;
                 
                  if (n29 && (e29 = n29->obj)) {
                    do {                
                      long ps_suppkey = e29->PS_SUPPKEY;
                      long v29 = e29->__av;
                      SUPPLIER_CNTPART1_E1_1.addOrDelOnZero(se27.modify(ps_suppkey,p_brand,p_type,p_size),(v28 * v29));
                      n29 = n29->nxt;
                    } while (n29 && (e29 = n29->obj) && h5 == n29->hash &&  SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::equals(se28, *e29)); 
                  }
                }
              n28 = n28->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPART1_E1_33_DELTA_map_0123* i30 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_DELTA_map_0123*>(SUPPLIER_CNTPART1_E1_33_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPART1_E1_33_DELTA_map_0123::IdxNode* n30; 
          SUPPLIER_CNTPART1_E1_33_DELTA_entry* e30;
        
          for (size_t i = 0; i < i30->size_; i++)
          {
            n30 = i30->buckets_ + i;
            while (n30 && (e30 = n30->obj))
            {
                long ps_partkey = e30->PS_PARTKEY;
                STRING_TYPE p_brand = e30->P_BRAND;
                STRING_TYPE p_type = e30->P_TYPE;
                long p_size = e30->P_SIZE;
                long v30 = e30->__av;
                SUPPLIER_CNTPART1_E1_1PARTSUPP1.addOrDelOnZero(se29.modify(ps_partkey,p_brand,p_type,p_size),v30);
              n30 = n30->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123* i31 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123::IdxNode* n31; 
          SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry* e31;
        
          for (size_t i = 0; i < i31->size_; i++)
          {
            n31 = i31->buckets_ + i;
            while (n31 && (e31 = n31->obj))
            {
                long ps_partkey = e31->PS_PARTKEY;
                STRING_TYPE p_brand = e31->P_BRAND;
                STRING_TYPE p_type = e31->P_TYPE;
                long p_size = e31->P_SIZE;
                long v31 = e31->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_33_map_0* i32 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0*>(SUPPLIER_CNTPART1_E1_33.index[1]);
                  const HASH_RES_t h6 = SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::hash(se31.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode* n32 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode*>(i32->slice(se31, h6));
                  SUPPLIER_CNTPART1_E1_33_entry* e32;
                 
                  if (n32 && (e32 = n32->obj)) {
                    do {                
                      long ps_suppkey = e32->PS_SUPPKEY;
                      long v32 = e32->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_2.addOrDelOnZero(se30.modify(ps_suppkey,p_brand,p_type,p_size),(v31 * v32));
                      n32 = n32->nxt;
                    } while (n32 && (e32 = n32->obj) && h6 == n32->hash &&  SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::equals(se31, *e32)); 
                  }
                }
              n31 = n31->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_map_0123* i33 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_map_0123::IdxNode* n33; 
          SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry* e33;
        
          for (size_t i = 0; i < i33->size_; i++)
          {
            n33 = i33->buckets_ + i;
            while (n33 && (e33 = n33->obj))
            {
                long ps_partkey = e33->PS_PARTKEY;
                STRING_TYPE p_brand = e33->P_BRAND;
                STRING_TYPE p_type = e33->P_TYPE;
                long p_size = e33->P_SIZE;
                long v33 = e33->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_33_map_0* i34 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0*>(SUPPLIER_CNTPART1_E1_33.index[1]);
                  const HASH_RES_t h7 = SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::hash(se33.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode* n34 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode*>(i34->slice(se33, h7));
                  SUPPLIER_CNTPART1_E1_33_entry* e34;
                 
                  if (n34 && (e34 = n34->obj)) {
                    do {                
                      long ps_suppkey = e34->PS_SUPPKEY;
                      long v34 = e34->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_4.addOrDelOnZero(se32.modify(ps_suppkey,p_brand,p_type,p_size),(v33 * v34));
                      n34 = n34->nxt;
                    } while (n34 && (e34 = n34->obj) && h7 == n34->hash &&  SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::equals(se33, *e34)); 
                  }
                }
              n33 = n33->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_map_0123* i35 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_map_0123::IdxNode* n35; 
          SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry* e35;
        
          for (size_t i = 0; i < i35->size_; i++)
          {
            n35 = i35->buckets_ + i;
            while (n35 && (e35 = n35->obj))
            {
                long ps_partkey = e35->PS_PARTKEY;
                STRING_TYPE p_brand = e35->P_BRAND;
                STRING_TYPE p_type = e35->P_TYPE;
                long p_size = e35->P_SIZE;
                long v35 = e35->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_33_map_0* i36 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0*>(SUPPLIER_CNTPART1_E1_33.index[1]);
                  const HASH_RES_t h8 = SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::hash(se35.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode* n36 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode*>(i36->slice(se35, h8));
                  SUPPLIER_CNTPART1_E1_33_entry* e36;
                 
                  if (n36 && (e36 = n36->obj)) {
                    do {                
                      long ps_suppkey = e36->PS_SUPPKEY;
                      long v36 = e36->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_6.addOrDelOnZero(se34.modify(ps_suppkey,p_brand,p_type,p_size),(v35 * v36));
                      n36 = n36->nxt;
                    } while (n36 && (e36 = n36->obj) && h8 == n36->hash &&  SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::equals(se35, *e36)); 
                  }
                }
              n35 = n35->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_map_0123* i37 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_map_0123::IdxNode* n37; 
          SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry* e37;
        
          for (size_t i = 0; i < i37->size_; i++)
          {
            n37 = i37->buckets_ + i;
            while (n37 && (e37 = n37->obj))
            {
                long ps_partkey = e37->PS_PARTKEY;
                STRING_TYPE p_brand = e37->P_BRAND;
                STRING_TYPE p_type = e37->P_TYPE;
                long p_size = e37->P_SIZE;
                long v37 = e37->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_33_map_0* i38 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0*>(SUPPLIER_CNTPART1_E1_33.index[1]);
                  const HASH_RES_t h9 = SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::hash(se37.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode* n38 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode*>(i38->slice(se37, h9));
                  SUPPLIER_CNTPART1_E1_33_entry* e38;
                 
                  if (n38 && (e38 = n38->obj)) {
                    do {                
                      long ps_suppkey = e38->PS_SUPPKEY;
                      long v38 = e38->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_8.addOrDelOnZero(se36.modify(ps_suppkey,p_brand,p_type,p_size),(v37 * v38));
                      n38 = n38->nxt;
                    } while (n38 && (e38 = n38->obj) && h9 == n38->hash &&  SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::equals(se37, *e38)); 
                  }
                }
              n37 = n37->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_map_0123* i39 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_map_0123::IdxNode* n39; 
          SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry* e39;
        
          for (size_t i = 0; i < i39->size_; i++)
          {
            n39 = i39->buckets_ + i;
            while (n39 && (e39 = n39->obj))
            {
                long ps_partkey = e39->PS_PARTKEY;
                STRING_TYPE p_brand = e39->P_BRAND;
                STRING_TYPE p_type = e39->P_TYPE;
                long p_size = e39->P_SIZE;
                long v39 = e39->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_33_map_0* i40 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0*>(SUPPLIER_CNTPART1_E1_33.index[1]);
                  const HASH_RES_t h10 = SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::hash(se39.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode* n40 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode*>(i40->slice(se39, h10));
                  SUPPLIER_CNTPART1_E1_33_entry* e40;
                 
                  if (n40 && (e40 = n40->obj)) {
                    do {                
                      long ps_suppkey = e40->PS_SUPPKEY;
                      long v40 = e40->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_10.addOrDelOnZero(se38.modify(ps_suppkey,p_brand,p_type,p_size),(v39 * v40));
                      n40 = n40->nxt;
                    } while (n40 && (e40 = n40->obj) && h10 == n40->hash &&  SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::equals(se39, *e40)); 
                  }
                }
              n39 = n39->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_map_0123* i41 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_map_0123::IdxNode* n41; 
          SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry* e41;
        
          for (size_t i = 0; i < i41->size_; i++)
          {
            n41 = i41->buckets_ + i;
            while (n41 && (e41 = n41->obj))
            {
                long ps_partkey = e41->PS_PARTKEY;
                STRING_TYPE p_brand = e41->P_BRAND;
                STRING_TYPE p_type = e41->P_TYPE;
                long p_size = e41->P_SIZE;
                long v41 = e41->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_33_map_0* i42 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0*>(SUPPLIER_CNTPART1_E1_33.index[1]);
                  const HASH_RES_t h11 = SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::hash(se41.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode* n42 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode*>(i42->slice(se41, h11));
                  SUPPLIER_CNTPART1_E1_33_entry* e42;
                 
                  if (n42 && (e42 = n42->obj)) {
                    do {                
                      long ps_suppkey = e42->PS_SUPPKEY;
                      long v42 = e42->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_12.addOrDelOnZero(se40.modify(ps_suppkey,p_brand,p_type,p_size),(v41 * v42));
                      n42 = n42->nxt;
                    } while (n42 && (e42 = n42->obj) && h11 == n42->hash &&  SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::equals(se41, *e42)); 
                  }
                }
              n41 = n41->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_map_0123* i43 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_map_0123::IdxNode* n43; 
          SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry* e43;
        
          for (size_t i = 0; i < i43->size_; i++)
          {
            n43 = i43->buckets_ + i;
            while (n43 && (e43 = n43->obj))
            {
                long ps_partkey = e43->PS_PARTKEY;
                STRING_TYPE p_brand = e43->P_BRAND;
                STRING_TYPE p_type = e43->P_TYPE;
                long p_size = e43->P_SIZE;
                long v43 = e43->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_33_map_0* i44 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0*>(SUPPLIER_CNTPART1_E1_33.index[1]);
                  const HASH_RES_t h12 = SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::hash(se43.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode* n44 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode*>(i44->slice(se43, h12));
                  SUPPLIER_CNTPART1_E1_33_entry* e44;
                 
                  if (n44 && (e44 = n44->obj)) {
                    do {                
                      long ps_suppkey = e44->PS_SUPPKEY;
                      long v44 = e44->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_14.addOrDelOnZero(se42.modify(ps_suppkey,p_brand,p_type,p_size),(v43 * v44));
                      n44 = n44->nxt;
                    } while (n44 && (e44 = n44->obj) && h12 == n44->hash &&  SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::equals(se43, *e44)); 
                  }
                }
              n43 = n43->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_map_0123* i45 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_map_0123::IdxNode* n45; 
          SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry* e45;
        
          for (size_t i = 0; i < i45->size_; i++)
          {
            n45 = i45->buckets_ + i;
            while (n45 && (e45 = n45->obj))
            {
                long ps_partkey = e45->PS_PARTKEY;
                STRING_TYPE p_brand = e45->P_BRAND;
                STRING_TYPE p_type = e45->P_TYPE;
                long p_size = e45->P_SIZE;
                long v45 = e45->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_33_map_0* i46 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0*>(SUPPLIER_CNTPART1_E1_33.index[1]);
                  const HASH_RES_t h13 = SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::hash(se45.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode* n46 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_33_map_0::IdxNode*>(i46->slice(se45, h13));
                  SUPPLIER_CNTPART1_E1_33_entry* e46;
                 
                  if (n46 && (e46 = n46->obj)) {
                    do {                
                      long ps_suppkey = e46->PS_SUPPKEY;
                      long v46 = e46->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_16.addOrDelOnZero(se44.modify(ps_suppkey,p_brand,p_type,p_size),(v45 * v46));
                      n46 = n46->nxt;
                    } while (n46 && (e46 = n46->obj) && h13 == n46->hash &&  SUPPLIER_CNTPART1_E1_33_mapkey0_idxfn::equals(se45, *e46)); 
                  }
                }
              n45 = n45->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123* i47 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map_0123::IdxNode* n47; 
          SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry* e47;
        
          for (size_t i = 0; i < i47->size_; i++)
          {
            n47 = i47->buckets_ + i;
            while (n47 && (e47 = n47->obj))
            {
                long ps_partkey = e47->PS_PARTKEY;
                STRING_TYPE p_brand = e47->P_BRAND;
                STRING_TYPE p_type = e47->P_TYPE;
                long p_size = e47->P_SIZE;
                long v47 = e47->__av;
                SUPPLIER_CNTPARTSUPP1_E1_18.addOrDelOnZero(se46.modify(ps_partkey,p_brand,p_type,p_size),v47);
              n47 = n47->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_map_0123* i48 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_map_0123::IdxNode* n48; 
          SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry* e48;
        
          for (size_t i = 0; i < i48->size_; i++)
          {
            n48 = i48->buckets_ + i;
            while (n48 && (e48 = n48->obj))
            {
                long ps_partkey = e48->PS_PARTKEY;
                STRING_TYPE p_brand = e48->P_BRAND;
                STRING_TYPE p_type = e48->P_TYPE;
                long p_size = e48->P_SIZE;
                long v48 = e48->__av;
                SUPPLIER_CNTPARTSUPP1_E1_20.addOrDelOnZero(se47.modify(ps_partkey,p_brand,p_type,p_size),v48);
              n48 = n48->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_map_0123* i49 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_map_0123::IdxNode* n49; 
          SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry* e49;
        
          for (size_t i = 0; i < i49->size_; i++)
          {
            n49 = i49->buckets_ + i;
            while (n49 && (e49 = n49->obj))
            {
                long ps_partkey = e49->PS_PARTKEY;
                STRING_TYPE p_brand = e49->P_BRAND;
                STRING_TYPE p_type = e49->P_TYPE;
                long p_size = e49->P_SIZE;
                long v49 = e49->__av;
                SUPPLIER_CNTPARTSUPP1_E1_22.addOrDelOnZero(se48.modify(ps_partkey,p_brand,p_type,p_size),v49);
              n49 = n49->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_map_0123* i50 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_map_0123::IdxNode* n50; 
          SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry* e50;
        
          for (size_t i = 0; i < i50->size_; i++)
          {
            n50 = i50->buckets_ + i;
            while (n50 && (e50 = n50->obj))
            {
                long ps_partkey = e50->PS_PARTKEY;
                STRING_TYPE p_brand = e50->P_BRAND;
                STRING_TYPE p_type = e50->P_TYPE;
                long p_size = e50->P_SIZE;
                long v50 = e50->__av;
                SUPPLIER_CNTPARTSUPP1_E1_24.addOrDelOnZero(se49.modify(ps_partkey,p_brand,p_type,p_size),v50);
              n50 = n50->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_map_0123* i51 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_map_0123::IdxNode* n51; 
          SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry* e51;
        
          for (size_t i = 0; i < i51->size_; i++)
          {
            n51 = i51->buckets_ + i;
            while (n51 && (e51 = n51->obj))
            {
                long ps_partkey = e51->PS_PARTKEY;
                STRING_TYPE p_brand = e51->P_BRAND;
                STRING_TYPE p_type = e51->P_TYPE;
                long p_size = e51->P_SIZE;
                long v51 = e51->__av;
                SUPPLIER_CNTPARTSUPP1_E1_26.addOrDelOnZero(se50.modify(ps_partkey,p_brand,p_type,p_size),v51);
              n51 = n51->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_map_0123* i52 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_map_0123::IdxNode* n52; 
          SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry* e52;
        
          for (size_t i = 0; i < i52->size_; i++)
          {
            n52 = i52->buckets_ + i;
            while (n52 && (e52 = n52->obj))
            {
                long ps_partkey = e52->PS_PARTKEY;
                STRING_TYPE p_brand = e52->P_BRAND;
                STRING_TYPE p_type = e52->P_TYPE;
                long p_size = e52->P_SIZE;
                long v52 = e52->__av;
                SUPPLIER_CNTPARTSUPP1_E1_28.addOrDelOnZero(se51.modify(ps_partkey,p_brand,p_type,p_size),v52);
              n52 = n52->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_map_0123* i53 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_map_0123::IdxNode* n53; 
          SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry* e53;
        
          for (size_t i = 0; i < i53->size_; i++)
          {
            n53 = i53->buckets_ + i;
            while (n53 && (e53 = n53->obj))
            {
                long ps_partkey = e53->PS_PARTKEY;
                STRING_TYPE p_brand = e53->P_BRAND;
                STRING_TYPE p_type = e53->P_TYPE;
                long p_size = e53->P_SIZE;
                long v53 = e53->__av;
                SUPPLIER_CNTPARTSUPP1_E1_30.addOrDelOnZero(se52.modify(ps_partkey,p_brand,p_type,p_size),v53);
              n53 = n53->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_map_0123* i54 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_map_0123::IdxNode* n54; 
          SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry* e54;
        
          for (size_t i = 0; i < i54->size_; i++)
          {
            n54 = i54->buckets_ + i;
            while (n54 && (e54 = n54->obj))
            {
                long ps_partkey = e54->PS_PARTKEY;
                STRING_TYPE p_brand = e54->P_BRAND;
                STRING_TYPE p_type = e54->P_TYPE;
                long p_size = e54->P_SIZE;
                long v54 = e54->__av;
                SUPPLIER_CNTPARTSUPP1_E1_32.addOrDelOnZero(se53.modify(ps_partkey,p_brand,p_type,p_size),v54);
              n54 = n54->nxt;
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


        SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA.clear();
        SUPPLIER_CNTSUPPLIER1_DOMAIN1.clear();
        {
          for (size_t i = 0; i < DELTA_SUPPLIER.size; i++) 
          {
                long ps_suppkey = DELTA_SUPPLIER.suppkey[i];
                STRING_TYPE s_name = DELTA_SUPPLIER.name[i];
                STRING_TYPE s_address = DELTA_SUPPLIER.address[i];
                long s_nationkey = DELTA_SUPPLIER.nationkey[i];
                STRING_TYPE s_phone = DELTA_SUPPLIER.phone[i];
                DOUBLE_TYPE s_acctbal = DELTA_SUPPLIER.acctbal[i];
                STRING_TYPE s_comment = DELTA_SUPPLIER.comment[i];
                long v55 = 1L;
                long upreg_match = Upreg_match(preg2,s_comment);
                (/*if */(0L != upreg_match) ? SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA.addOrDelOnZero(se54.modify(ps_suppkey),v55) : (void)0);    
                long v56 = 1L;
                (/*if */(0L != upreg_match) ? SUPPLIER_CNTSUPPLIER1_DOMAIN1.addOrDelOnZero(se55.modify(ps_suppkey),(v56 != 0 ? 1L : 0L)) : (void)0);
          }
        }
        
        agg7.clear();
        
        agg8.clear();
        
        long l4 = 0L;
        {  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0123* i57 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0123::IdxNode* n57; 
          SUPPLIER_CNTPARTSUPP1_E1_2_entry* e57;
        
          for (size_t i = 0; i < i57->size_; i++)
          {
            n57 = i57->buckets_ + i;
            while (n57 && (e57 = n57->obj))
            {
                long ps_suppkey = e57->PS_SUPPKEY;
                STRING_TYPE p_brand = e57->P_BRAND;
                STRING_TYPE p_type = e57->P_TYPE;
                long p_size = e57->P_SIZE;
                long v57 = e57->__av;
                (/*if */(l4 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se57.modify(ps_suppkey))) ? agg8.addOrDelOnZero(st13.modify(ps_suppkey,p_brand,p_type,p_size,v57), v57) : (void)0);
              n57 = n57->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0123* i58 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_4.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0123::IdxNode* n58; 
          SUPPLIER_CNTPARTSUPP1_E1_4_entry* e58;
        
          for (size_t i = 0; i < i58->size_; i++)
          {
            n58 = i58->buckets_ + i;
            while (n58 && (e58 = n58->obj))
            {
                long ps_suppkey = e58->PS_SUPPKEY;
                STRING_TYPE p_brand = e58->P_BRAND;
                STRING_TYPE p_type = e58->P_TYPE;
                long p_size = e58->P_SIZE;
                long v58 = e58->__av;
                (/*if */(l4 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se58.modify(ps_suppkey))) ? agg8.addOrDelOnZero(st14.modify(ps_suppkey,p_brand,p_type,p_size,v58), v58) : (void)0);
              n58 = n58->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0123* i59 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_6.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0123::IdxNode* n59; 
          SUPPLIER_CNTPARTSUPP1_E1_6_entry* e59;
        
          for (size_t i = 0; i < i59->size_; i++)
          {
            n59 = i59->buckets_ + i;
            while (n59 && (e59 = n59->obj))
            {
                long ps_suppkey = e59->PS_SUPPKEY;
                STRING_TYPE p_brand = e59->P_BRAND;
                STRING_TYPE p_type = e59->P_TYPE;
                long p_size = e59->P_SIZE;
                long v59 = e59->__av;
                (/*if */(l4 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se59.modify(ps_suppkey))) ? agg8.addOrDelOnZero(st15.modify(ps_suppkey,p_brand,p_type,p_size,v59), v59) : (void)0);
              n59 = n59->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0123* i60 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_8.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0123::IdxNode* n60; 
          SUPPLIER_CNTPARTSUPP1_E1_8_entry* e60;
        
          for (size_t i = 0; i < i60->size_; i++)
          {
            n60 = i60->buckets_ + i;
            while (n60 && (e60 = n60->obj))
            {
                long ps_suppkey = e60->PS_SUPPKEY;
                STRING_TYPE p_brand = e60->P_BRAND;
                STRING_TYPE p_type = e60->P_TYPE;
                long p_size = e60->P_SIZE;
                long v60 = e60->__av;
                (/*if */(l4 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se60.modify(ps_suppkey))) ? agg8.addOrDelOnZero(st16.modify(ps_suppkey,p_brand,p_type,p_size,v60), v60) : (void)0);
              n60 = n60->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0123* i61 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_10.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0123::IdxNode* n61; 
          SUPPLIER_CNTPARTSUPP1_E1_10_entry* e61;
        
          for (size_t i = 0; i < i61->size_; i++)
          {
            n61 = i61->buckets_ + i;
            while (n61 && (e61 = n61->obj))
            {
                long ps_suppkey = e61->PS_SUPPKEY;
                STRING_TYPE p_brand = e61->P_BRAND;
                STRING_TYPE p_type = e61->P_TYPE;
                long p_size = e61->P_SIZE;
                long v61 = e61->__av;
                (/*if */(l4 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se61.modify(ps_suppkey))) ? agg8.addOrDelOnZero(st17.modify(ps_suppkey,p_brand,p_type,p_size,v61), v61) : (void)0);
              n61 = n61->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0123* i62 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_12.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0123::IdxNode* n62; 
          SUPPLIER_CNTPARTSUPP1_E1_12_entry* e62;
        
          for (size_t i = 0; i < i62->size_; i++)
          {
            n62 = i62->buckets_ + i;
            while (n62 && (e62 = n62->obj))
            {
                long ps_suppkey = e62->PS_SUPPKEY;
                STRING_TYPE p_brand = e62->P_BRAND;
                STRING_TYPE p_type = e62->P_TYPE;
                long p_size = e62->P_SIZE;
                long v62 = e62->__av;
                (/*if */(l4 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se62.modify(ps_suppkey))) ? agg8.addOrDelOnZero(st18.modify(ps_suppkey,p_brand,p_type,p_size,v62), v62) : (void)0);
              n62 = n62->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0123* i63 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_14.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0123::IdxNode* n63; 
          SUPPLIER_CNTPARTSUPP1_E1_14_entry* e63;
        
          for (size_t i = 0; i < i63->size_; i++)
          {
            n63 = i63->buckets_ + i;
            while (n63 && (e63 = n63->obj))
            {
                long ps_suppkey = e63->PS_SUPPKEY;
                STRING_TYPE p_brand = e63->P_BRAND;
                STRING_TYPE p_type = e63->P_TYPE;
                long p_size = e63->P_SIZE;
                long v63 = e63->__av;
                (/*if */(l4 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se63.modify(ps_suppkey))) ? agg8.addOrDelOnZero(st19.modify(ps_suppkey,p_brand,p_type,p_size,v63), v63) : (void)0);
              n63 = n63->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0123* i64 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_16.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0123::IdxNode* n64; 
          SUPPLIER_CNTPARTSUPP1_E1_16_entry* e64;
        
          for (size_t i = 0; i < i64->size_; i++)
          {
            n64 = i64->buckets_ + i;
            while (n64 && (e64 = n64->obj))
            {
                long ps_suppkey = e64->PS_SUPPKEY;
                STRING_TYPE p_brand = e64->P_BRAND;
                STRING_TYPE p_type = e64->P_TYPE;
                long p_size = e64->P_SIZE;
                long v64 = e64->__av;
                (/*if */(l4 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se64.modify(ps_suppkey))) ? agg8.addOrDelOnZero(st20.modify(ps_suppkey,p_brand,p_type,p_size,v64), v64) : (void)0);
              n64 = n64->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple5_LSSL_L, long>* i65 = static_cast<HashIndex<tuple5_LSSL_L, long>*>(agg8.index[0]);
          HashIndex<tuple5_LSSL_L, long>::IdxNode* n65; 
          tuple5_LSSL_L* e65;
        
          for (size_t i = 0; i < i65->size_; i++)
          {
            n65 = i65->buckets_ + i;
            while (n65 && (e65 = n65->obj))
            {
              long ps_suppkey = e65->_1;
              STRING_TYPE p_brand = e65->_2;
              STRING_TYPE p_type = e65->_3;
              long p_size = e65->_4;  
              long v65 = e65->__av; 
            agg7.addOrDelOnZero(st21.modify(p_brand,p_type,p_size,(v65 != 0 ? 1L : 0L)), (v65 != 0 ? 1L : 0L));      
              n65 = n65->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i66 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg7.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n66; 
          tuple4_SSL_L* e66;
        
          for (size_t i = 0; i < i66->size_; i++)
          {
            n66 = i66->buckets_ + i;
            while (n66 && (e66 = n66->obj))
            {
              STRING_TYPE p_brand = e66->_1;
              STRING_TYPE p_type = e66->_2;
              long p_size = e66->_3;  
              long v66 = e66->__av; 
            if (SUPPLIER_CNT.getValueOrDefault(se56.modify(p_brand,p_type,p_size))==0) SUPPLIER_CNT.setOrDelOnZero(se56, v66);      
              n66 = n66->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0* i67 = static_cast<HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0*>(SUPPLIER_CNTSUPPLIER1_DOMAIN1.index[0]);
          HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0::IdxNode* n67; 
          SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry* e67;
        
          for (size_t i = 0; i < i67->size_; i++)
          {
            n67 = i67->buckets_ + i;
            while (n67 && (e67 = n67->obj))
            {
                long ps_suppkey = e67->PS_SUPPKEY;
                long v67 = e67->__av;
                agg9.clear();
                
                long l5 = (SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se65.modify(ps_suppkey)) + SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA.getValueOrDefault(se66.modify(ps_suppkey)));
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0* i68 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[1]);
                  const HASH_RES_t h14 = SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::hash(se67.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode* n68 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode*>(i68->slice(se67, h14));
                  SUPPLIER_CNTPARTSUPP1_E1_2_entry* e68;
                 
                  if (n68 && (e68 = n68->obj)) {
                    do {                
                      STRING_TYPE p_brand = e68->P_BRAND;
                      STRING_TYPE p_type = e68->P_TYPE;
                      long p_size = e68->P_SIZE;
                      long v68 = e68->__av;
                      (/*if */(l5 == 0L) ? agg9.addOrDelOnZero(st22.modify(p_brand,p_type,p_size,v68), v68) : (void)0);
                      n68 = n68->nxt;
                    } while (n68 && (e68 = n68->obj) && h14 == n68->hash &&  SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::equals(se67, *e68)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0* i69 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_4.index[1]);
                  const HASH_RES_t h15 = SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::hash(se68.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode* n69 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode*>(i69->slice(se68, h15));
                  SUPPLIER_CNTPARTSUPP1_E1_4_entry* e69;
                 
                  if (n69 && (e69 = n69->obj)) {
                    do {                
                      STRING_TYPE p_brand = e69->P_BRAND;
                      STRING_TYPE p_type = e69->P_TYPE;
                      long p_size = e69->P_SIZE;
                      long v69 = e69->__av;
                      (/*if */(l5 == 0L) ? agg9.addOrDelOnZero(st23.modify(p_brand,p_type,p_size,v69), v69) : (void)0);
                      n69 = n69->nxt;
                    } while (n69 && (e69 = n69->obj) && h15 == n69->hash &&  SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::equals(se68, *e69)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0* i70 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_6.index[1]);
                  const HASH_RES_t h16 = SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0_idxfn::hash(se69.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0::IdxNode* n70 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0::IdxNode*>(i70->slice(se69, h16));
                  SUPPLIER_CNTPARTSUPP1_E1_6_entry* e70;
                 
                  if (n70 && (e70 = n70->obj)) {
                    do {                
                      STRING_TYPE p_brand = e70->P_BRAND;
                      STRING_TYPE p_type = e70->P_TYPE;
                      long p_size = e70->P_SIZE;
                      long v70 = e70->__av;
                      (/*if */(l5 == 0L) ? agg9.addOrDelOnZero(st24.modify(p_brand,p_type,p_size,v70), v70) : (void)0);
                      n70 = n70->nxt;
                    } while (n70 && (e70 = n70->obj) && h16 == n70->hash &&  SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0_idxfn::equals(se69, *e70)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0* i71 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_8.index[1]);
                  const HASH_RES_t h17 = SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0_idxfn::hash(se70.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0::IdxNode* n71 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0::IdxNode*>(i71->slice(se70, h17));
                  SUPPLIER_CNTPARTSUPP1_E1_8_entry* e71;
                 
                  if (n71 && (e71 = n71->obj)) {
                    do {                
                      STRING_TYPE p_brand = e71->P_BRAND;
                      STRING_TYPE p_type = e71->P_TYPE;
                      long p_size = e71->P_SIZE;
                      long v71 = e71->__av;
                      (/*if */(l5 == 0L) ? agg9.addOrDelOnZero(st25.modify(p_brand,p_type,p_size,v71), v71) : (void)0);
                      n71 = n71->nxt;
                    } while (n71 && (e71 = n71->obj) && h17 == n71->hash &&  SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0_idxfn::equals(se70, *e71)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0* i72 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_10.index[1]);
                  const HASH_RES_t h18 = SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0_idxfn::hash(se71.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0::IdxNode* n72 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0::IdxNode*>(i72->slice(se71, h18));
                  SUPPLIER_CNTPARTSUPP1_E1_10_entry* e72;
                 
                  if (n72 && (e72 = n72->obj)) {
                    do {                
                      STRING_TYPE p_brand = e72->P_BRAND;
                      STRING_TYPE p_type = e72->P_TYPE;
                      long p_size = e72->P_SIZE;
                      long v72 = e72->__av;
                      (/*if */(l5 == 0L) ? agg9.addOrDelOnZero(st26.modify(p_brand,p_type,p_size,v72), v72) : (void)0);
                      n72 = n72->nxt;
                    } while (n72 && (e72 = n72->obj) && h18 == n72->hash &&  SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0_idxfn::equals(se71, *e72)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0* i73 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_12.index[1]);
                  const HASH_RES_t h19 = SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0_idxfn::hash(se72.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0::IdxNode* n73 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0::IdxNode*>(i73->slice(se72, h19));
                  SUPPLIER_CNTPARTSUPP1_E1_12_entry* e73;
                 
                  if (n73 && (e73 = n73->obj)) {
                    do {                
                      STRING_TYPE p_brand = e73->P_BRAND;
                      STRING_TYPE p_type = e73->P_TYPE;
                      long p_size = e73->P_SIZE;
                      long v73 = e73->__av;
                      (/*if */(l5 == 0L) ? agg9.addOrDelOnZero(st27.modify(p_brand,p_type,p_size,v73), v73) : (void)0);
                      n73 = n73->nxt;
                    } while (n73 && (e73 = n73->obj) && h19 == n73->hash &&  SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0_idxfn::equals(se72, *e73)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0* i74 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_14.index[1]);
                  const HASH_RES_t h20 = SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0_idxfn::hash(se73.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0::IdxNode* n74 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0::IdxNode*>(i74->slice(se73, h20));
                  SUPPLIER_CNTPARTSUPP1_E1_14_entry* e74;
                 
                  if (n74 && (e74 = n74->obj)) {
                    do {                
                      STRING_TYPE p_brand = e74->P_BRAND;
                      STRING_TYPE p_type = e74->P_TYPE;
                      long p_size = e74->P_SIZE;
                      long v74 = e74->__av;
                      (/*if */(l5 == 0L) ? agg9.addOrDelOnZero(st28.modify(p_brand,p_type,p_size,v74), v74) : (void)0);
                      n74 = n74->nxt;
                    } while (n74 && (e74 = n74->obj) && h20 == n74->hash &&  SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0_idxfn::equals(se73, *e74)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0* i75 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_16.index[1]);
                  const HASH_RES_t h21 = SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0_idxfn::hash(se74.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0::IdxNode* n75 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0::IdxNode*>(i75->slice(se74, h21));
                  SUPPLIER_CNTPARTSUPP1_E1_16_entry* e75;
                 
                  if (n75 && (e75 = n75->obj)) {
                    do {                
                      STRING_TYPE p_brand = e75->P_BRAND;
                      STRING_TYPE p_type = e75->P_TYPE;
                      long p_size = e75->P_SIZE;
                      long v75 = e75->__av;
                      (/*if */(l5 == 0L) ? agg9.addOrDelOnZero(st29.modify(p_brand,p_type,p_size,v75), v75) : (void)0);
                      n75 = n75->nxt;
                    } while (n75 && (e75 = n75->obj) && h21 == n75->hash &&  SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0_idxfn::equals(se74, *e75)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple4_SSL_L, long>* i76 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg9.index[0]);
                  HashIndex<tuple4_SSL_L, long>::IdxNode* n76; 
                  tuple4_SSL_L* e76;
                
                  for (size_t i = 0; i < i76->size_; i++)
                  {
                    n76 = i76->buckets_ + i;
                    while (n76 && (e76 = n76->obj))
                    {
                      STRING_TYPE p_brand = e76->_1;
                      STRING_TYPE p_type = e76->_2;
                      long p_size = e76->_3;  
                      long v76 = e76->__av; 
                    SUPPLIER_CNT.addOrDelOnZero(se56.modify(p_brand,p_type,p_size),((v67 != 0 ? 1L : 0L) * (v76 != 0 ? 1L : 0L)));      
                      n76 = n76->nxt;
                    }
                  }
                }
              n67 = n67->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0* i77 = static_cast<HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0*>(SUPPLIER_CNTSUPPLIER1_DOMAIN1.index[0]);
          HashIndex_SUPPLIER_CNTSUPPLIER1_DOMAIN1_map_0::IdxNode* n77; 
          SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry* e77;
        
          for (size_t i = 0; i < i77->size_; i++)
          {
            n77 = i77->buckets_ + i;
            while (n77 && (e77 = n77->obj))
            {
                long ps_suppkey = e77->PS_SUPPKEY;
                long v77 = e77->__av;
                agg10.clear();
                
                long l6 = SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se75.modify(ps_suppkey));
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0* i78 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[1]);
                  const HASH_RES_t h22 = SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::hash(se76.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode* n78 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode*>(i78->slice(se76, h22));
                  SUPPLIER_CNTPARTSUPP1_E1_2_entry* e78;
                 
                  if (n78 && (e78 = n78->obj)) {
                    do {                
                      STRING_TYPE p_brand = e78->P_BRAND;
                      STRING_TYPE p_type = e78->P_TYPE;
                      long p_size = e78->P_SIZE;
                      long v78 = e78->__av;
                      (/*if */(l6 == 0L) ? agg10.addOrDelOnZero(st30.modify(p_brand,p_type,p_size,v78), v78) : (void)0);
                      n78 = n78->nxt;
                    } while (n78 && (e78 = n78->obj) && h22 == n78->hash &&  SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::equals(se76, *e78)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0* i79 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_4.index[1]);
                  const HASH_RES_t h23 = SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::hash(se77.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode* n79 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode*>(i79->slice(se77, h23));
                  SUPPLIER_CNTPARTSUPP1_E1_4_entry* e79;
                 
                  if (n79 && (e79 = n79->obj)) {
                    do {                
                      STRING_TYPE p_brand = e79->P_BRAND;
                      STRING_TYPE p_type = e79->P_TYPE;
                      long p_size = e79->P_SIZE;
                      long v79 = e79->__av;
                      (/*if */(l6 == 0L) ? agg10.addOrDelOnZero(st31.modify(p_brand,p_type,p_size,v79), v79) : (void)0);
                      n79 = n79->nxt;
                    } while (n79 && (e79 = n79->obj) && h23 == n79->hash &&  SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::equals(se77, *e79)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0* i80 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_6.index[1]);
                  const HASH_RES_t h24 = SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0_idxfn::hash(se78.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0::IdxNode* n80 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0::IdxNode*>(i80->slice(se78, h24));
                  SUPPLIER_CNTPARTSUPP1_E1_6_entry* e80;
                 
                  if (n80 && (e80 = n80->obj)) {
                    do {                
                      STRING_TYPE p_brand = e80->P_BRAND;
                      STRING_TYPE p_type = e80->P_TYPE;
                      long p_size = e80->P_SIZE;
                      long v80 = e80->__av;
                      (/*if */(l6 == 0L) ? agg10.addOrDelOnZero(st32.modify(p_brand,p_type,p_size,v80), v80) : (void)0);
                      n80 = n80->nxt;
                    } while (n80 && (e80 = n80->obj) && h24 == n80->hash &&  SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0_idxfn::equals(se78, *e80)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0* i81 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_8.index[1]);
                  const HASH_RES_t h25 = SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0_idxfn::hash(se79.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0::IdxNode* n81 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0::IdxNode*>(i81->slice(se79, h25));
                  SUPPLIER_CNTPARTSUPP1_E1_8_entry* e81;
                 
                  if (n81 && (e81 = n81->obj)) {
                    do {                
                      STRING_TYPE p_brand = e81->P_BRAND;
                      STRING_TYPE p_type = e81->P_TYPE;
                      long p_size = e81->P_SIZE;
                      long v81 = e81->__av;
                      (/*if */(l6 == 0L) ? agg10.addOrDelOnZero(st33.modify(p_brand,p_type,p_size,v81), v81) : (void)0);
                      n81 = n81->nxt;
                    } while (n81 && (e81 = n81->obj) && h25 == n81->hash &&  SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0_idxfn::equals(se79, *e81)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0* i82 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_10.index[1]);
                  const HASH_RES_t h26 = SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0_idxfn::hash(se80.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0::IdxNode* n82 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0::IdxNode*>(i82->slice(se80, h26));
                  SUPPLIER_CNTPARTSUPP1_E1_10_entry* e82;
                 
                  if (n82 && (e82 = n82->obj)) {
                    do {                
                      STRING_TYPE p_brand = e82->P_BRAND;
                      STRING_TYPE p_type = e82->P_TYPE;
                      long p_size = e82->P_SIZE;
                      long v82 = e82->__av;
                      (/*if */(l6 == 0L) ? agg10.addOrDelOnZero(st34.modify(p_brand,p_type,p_size,v82), v82) : (void)0);
                      n82 = n82->nxt;
                    } while (n82 && (e82 = n82->obj) && h26 == n82->hash &&  SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0_idxfn::equals(se80, *e82)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0* i83 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_12.index[1]);
                  const HASH_RES_t h27 = SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0_idxfn::hash(se81.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0::IdxNode* n83 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0::IdxNode*>(i83->slice(se81, h27));
                  SUPPLIER_CNTPARTSUPP1_E1_12_entry* e83;
                 
                  if (n83 && (e83 = n83->obj)) {
                    do {                
                      STRING_TYPE p_brand = e83->P_BRAND;
                      STRING_TYPE p_type = e83->P_TYPE;
                      long p_size = e83->P_SIZE;
                      long v83 = e83->__av;
                      (/*if */(l6 == 0L) ? agg10.addOrDelOnZero(st35.modify(p_brand,p_type,p_size,v83), v83) : (void)0);
                      n83 = n83->nxt;
                    } while (n83 && (e83 = n83->obj) && h27 == n83->hash &&  SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0_idxfn::equals(se81, *e83)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0* i84 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_14.index[1]);
                  const HASH_RES_t h28 = SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0_idxfn::hash(se82.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0::IdxNode* n84 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0::IdxNode*>(i84->slice(se82, h28));
                  SUPPLIER_CNTPARTSUPP1_E1_14_entry* e84;
                 
                  if (n84 && (e84 = n84->obj)) {
                    do {                
                      STRING_TYPE p_brand = e84->P_BRAND;
                      STRING_TYPE p_type = e84->P_TYPE;
                      long p_size = e84->P_SIZE;
                      long v84 = e84->__av;
                      (/*if */(l6 == 0L) ? agg10.addOrDelOnZero(st36.modify(p_brand,p_type,p_size,v84), v84) : (void)0);
                      n84 = n84->nxt;
                    } while (n84 && (e84 = n84->obj) && h28 == n84->hash &&  SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0_idxfn::equals(se82, *e84)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0* i85 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_16.index[1]);
                  const HASH_RES_t h29 = SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0_idxfn::hash(se83.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0::IdxNode* n85 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0::IdxNode*>(i85->slice(se83, h29));
                  SUPPLIER_CNTPARTSUPP1_E1_16_entry* e85;
                 
                  if (n85 && (e85 = n85->obj)) {
                    do {                
                      STRING_TYPE p_brand = e85->P_BRAND;
                      STRING_TYPE p_type = e85->P_TYPE;
                      long p_size = e85->P_SIZE;
                      long v85 = e85->__av;
                      (/*if */(l6 == 0L) ? agg10.addOrDelOnZero(st37.modify(p_brand,p_type,p_size,v85), v85) : (void)0);
                      n85 = n85->nxt;
                    } while (n85 && (e85 = n85->obj) && h29 == n85->hash &&  SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0_idxfn::equals(se83, *e85)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple4_SSL_L, long>* i86 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg10.index[0]);
                  HashIndex<tuple4_SSL_L, long>::IdxNode* n86; 
                  tuple4_SSL_L* e86;
                
                  for (size_t i = 0; i < i86->size_; i++)
                  {
                    n86 = i86->buckets_ + i;
                    while (n86 && (e86 = n86->obj))
                    {
                      STRING_TYPE p_brand = e86->_1;
                      STRING_TYPE p_type = e86->_2;
                      long p_size = e86->_3;  
                      long v86 = e86->__av; 
                    SUPPLIER_CNT.addOrDelOnZero(se56.modify(p_brand,p_type,p_size),(((v77 != 0 ? 1L : 0L) * (v86 != 0 ? 1L : 0L)) * -1L));      
                      n86 = n86->nxt;
                    }
                  }
                }
              n77 = n77->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_map_0* i87 = static_cast<HashIndex_SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_map_0*>(SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_map_0::IdxNode* n87; 
          SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry* e87;
        
          for (size_t i = 0; i < i87->size_; i++)
          {
            n87 = i87->buckets_ + i;
            while (n87 && (e87 = n87->obj))
            {
                long ps_suppkey = e87->PS_SUPPKEY;
                long v87 = e87->__av;
                SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.addOrDelOnZero(se84.modify(ps_suppkey),v87);
              n87 = n87->nxt;
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


        SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.clear();
        SUPPLIER_CNTPARTSUPP1_DOMAIN1.clear();
        {  
          for (size_t i = 0; i < DELTA_PARTSUPP.size; i++)
          {
                long ps_partkey = DELTA_PARTSUPP.partkey[i];
                long ps_suppkey = DELTA_PARTSUPP.suppkey[i];
                long ps_availqty = DELTA_PARTSUPP.availqty[i];
                DOUBLE_TYPE ps_supplycost = DELTA_PARTSUPP.supplycost[i];
                STRING_TYPE ps_comment = DELTA_PARTSUPP.comment[i];
                long v88 = 1L;
                SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.addOrDelOnZero(se85.modify(ps_partkey,ps_suppkey),v88);            
                long v89 = 1L;
                SUPPLIER_CNTPARTSUPP1_DOMAIN1.addOrDelOnZero(se86.modify(ps_suppkey),(v89 != 0 ? 1L : 0L));
          }
        }
        agg11.clear();
        
        agg12.clear();
        
        long l7 = 0L;
        {  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0123* i90 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0123::IdxNode* n90; 
          SUPPLIER_CNTPARTSUPP1_E1_2_entry* e90;
        
          for (size_t i = 0; i < i90->size_; i++)
          {
            n90 = i90->buckets_ + i;
            while (n90 && (e90 = n90->obj))
            {
                long ps_suppkey = e90->PS_SUPPKEY;
                STRING_TYPE p_brand = e90->P_BRAND;
                STRING_TYPE p_type = e90->P_TYPE;
                long p_size = e90->P_SIZE;
                long v90 = e90->__av;
                (/*if */(l7 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se88.modify(ps_suppkey))) ? agg12.addOrDelOnZero(st38.modify(ps_suppkey,p_brand,p_type,p_size,v90), v90) : (void)0);
              n90 = n90->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0123* i91 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_4.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0123::IdxNode* n91; 
          SUPPLIER_CNTPARTSUPP1_E1_4_entry* e91;
        
          for (size_t i = 0; i < i91->size_; i++)
          {
            n91 = i91->buckets_ + i;
            while (n91 && (e91 = n91->obj))
            {
                long ps_suppkey = e91->PS_SUPPKEY;
                STRING_TYPE p_brand = e91->P_BRAND;
                STRING_TYPE p_type = e91->P_TYPE;
                long p_size = e91->P_SIZE;
                long v91 = e91->__av;
                (/*if */(l7 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se89.modify(ps_suppkey))) ? agg12.addOrDelOnZero(st39.modify(ps_suppkey,p_brand,p_type,p_size,v91), v91) : (void)0);
              n91 = n91->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0123* i92 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_6.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0123::IdxNode* n92; 
          SUPPLIER_CNTPARTSUPP1_E1_6_entry* e92;
        
          for (size_t i = 0; i < i92->size_; i++)
          {
            n92 = i92->buckets_ + i;
            while (n92 && (e92 = n92->obj))
            {
                long ps_suppkey = e92->PS_SUPPKEY;
                STRING_TYPE p_brand = e92->P_BRAND;
                STRING_TYPE p_type = e92->P_TYPE;
                long p_size = e92->P_SIZE;
                long v92 = e92->__av;
                (/*if */(l7 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se90.modify(ps_suppkey))) ? agg12.addOrDelOnZero(st40.modify(ps_suppkey,p_brand,p_type,p_size,v92), v92) : (void)0);
              n92 = n92->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0123* i93 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_8.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0123::IdxNode* n93; 
          SUPPLIER_CNTPARTSUPP1_E1_8_entry* e93;
        
          for (size_t i = 0; i < i93->size_; i++)
          {
            n93 = i93->buckets_ + i;
            while (n93 && (e93 = n93->obj))
            {
                long ps_suppkey = e93->PS_SUPPKEY;
                STRING_TYPE p_brand = e93->P_BRAND;
                STRING_TYPE p_type = e93->P_TYPE;
                long p_size = e93->P_SIZE;
                long v93 = e93->__av;
                (/*if */(l7 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se91.modify(ps_suppkey))) ? agg12.addOrDelOnZero(st41.modify(ps_suppkey,p_brand,p_type,p_size,v93), v93) : (void)0);
              n93 = n93->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0123* i94 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_10.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0123::IdxNode* n94; 
          SUPPLIER_CNTPARTSUPP1_E1_10_entry* e94;
        
          for (size_t i = 0; i < i94->size_; i++)
          {
            n94 = i94->buckets_ + i;
            while (n94 && (e94 = n94->obj))
            {
                long ps_suppkey = e94->PS_SUPPKEY;
                STRING_TYPE p_brand = e94->P_BRAND;
                STRING_TYPE p_type = e94->P_TYPE;
                long p_size = e94->P_SIZE;
                long v94 = e94->__av;
                (/*if */(l7 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se92.modify(ps_suppkey))) ? agg12.addOrDelOnZero(st42.modify(ps_suppkey,p_brand,p_type,p_size,v94), v94) : (void)0);
              n94 = n94->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0123* i95 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_12.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0123::IdxNode* n95; 
          SUPPLIER_CNTPARTSUPP1_E1_12_entry* e95;
        
          for (size_t i = 0; i < i95->size_; i++)
          {
            n95 = i95->buckets_ + i;
            while (n95 && (e95 = n95->obj))
            {
                long ps_suppkey = e95->PS_SUPPKEY;
                STRING_TYPE p_brand = e95->P_BRAND;
                STRING_TYPE p_type = e95->P_TYPE;
                long p_size = e95->P_SIZE;
                long v95 = e95->__av;
                (/*if */(l7 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se93.modify(ps_suppkey))) ? agg12.addOrDelOnZero(st43.modify(ps_suppkey,p_brand,p_type,p_size,v95), v95) : (void)0);
              n95 = n95->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0123* i96 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_14.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0123::IdxNode* n96; 
          SUPPLIER_CNTPARTSUPP1_E1_14_entry* e96;
        
          for (size_t i = 0; i < i96->size_; i++)
          {
            n96 = i96->buckets_ + i;
            while (n96 && (e96 = n96->obj))
            {
                long ps_suppkey = e96->PS_SUPPKEY;
                STRING_TYPE p_brand = e96->P_BRAND;
                STRING_TYPE p_type = e96->P_TYPE;
                long p_size = e96->P_SIZE;
                long v96 = e96->__av;
                (/*if */(l7 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se94.modify(ps_suppkey))) ? agg12.addOrDelOnZero(st44.modify(ps_suppkey,p_brand,p_type,p_size,v96), v96) : (void)0);
              n96 = n96->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0123* i97 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0123*>(SUPPLIER_CNTPARTSUPP1_E1_16.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0123::IdxNode* n97; 
          SUPPLIER_CNTPARTSUPP1_E1_16_entry* e97;
        
          for (size_t i = 0; i < i97->size_; i++)
          {
            n97 = i97->buckets_ + i;
            while (n97 && (e97 = n97->obj))
            {
                long ps_suppkey = e97->PS_SUPPKEY;
                STRING_TYPE p_brand = e97->P_BRAND;
                STRING_TYPE p_type = e97->P_TYPE;
                long p_size = e97->P_SIZE;
                long v97 = e97->__av;
                (/*if */(l7 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se95.modify(ps_suppkey))) ? agg12.addOrDelOnZero(st45.modify(ps_suppkey,p_brand,p_type,p_size,v97), v97) : (void)0);
              n97 = n97->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple5_LSSL_L, long>* i98 = static_cast<HashIndex<tuple5_LSSL_L, long>*>(agg12.index[0]);
          HashIndex<tuple5_LSSL_L, long>::IdxNode* n98; 
          tuple5_LSSL_L* e98;
        
          for (size_t i = 0; i < i98->size_; i++)
          {
            n98 = i98->buckets_ + i;
            while (n98 && (e98 = n98->obj))
            {
              long ps_suppkey = e98->_1;
              STRING_TYPE p_brand = e98->_2;
              STRING_TYPE p_type = e98->_3;
              long p_size = e98->_4;  
              long v98 = e98->__av; 
            agg11.addOrDelOnZero(st46.modify(p_brand,p_type,p_size,(v98 != 0 ? 1L : 0L)), (v98 != 0 ? 1L : 0L));      
              n98 = n98->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i99 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg11.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n99; 
          tuple4_SSL_L* e99;
        
          for (size_t i = 0; i < i99->size_; i++)
          {
            n99 = i99->buckets_ + i;
            while (n99 && (e99 = n99->obj))
            {
              STRING_TYPE p_brand = e99->_1;
              STRING_TYPE p_type = e99->_2;
              long p_size = e99->_3;  
              long v99 = e99->__av; 
            if (SUPPLIER_CNT.getValueOrDefault(se87.modify(p_brand,p_type,p_size))==0) SUPPLIER_CNT.setOrDelOnZero(se87, v99);      
              n99 = n99->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0* i100 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0*>(SUPPLIER_CNTPARTSUPP1_DOMAIN1.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0::IdxNode* n100; 
          SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry* e100;
        
          for (size_t i = 0; i < i100->size_; i++)
          {
            n100 = i100->buckets_ + i;
            while (n100 && (e100 = n100->obj))
            {
                long ps_suppkey = e100->PS_SUPPKEY;
                long v100 = e100->__av;
                agg13.clear();
                
                long l8 = SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se96.modify(ps_suppkey));
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_1* i101 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_1*>(SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.index[1]);
                  const HASH_RES_t h38 = SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_mapkey1_idxfn::hash(se105.modify1(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_1::IdxNode* n101 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_1::IdxNode*>(i101->slice(se105, h38));
                  SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry* e101;
                 
                  if (n101 && (e101 = n101->obj)) {
                    do {                
                      long ps_partkey = e101->PS_PARTKEY;
                      long v101 = e101->__av;
                      { //slice 
                        const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_map_0* i102 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_18.index[1]);
                        const HASH_RES_t h30 = SUPPLIER_CNTPARTSUPP1_E1_18_mapkey0_idxfn::hash(se97.modify0(ps_partkey));
                        HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_map_0::IdxNode* n102 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_map_0::IdxNode*>(i102->slice(se97, h30));
                        SUPPLIER_CNTPARTSUPP1_E1_18_entry* e102;
                       
                        if (n102 && (e102 = n102->obj)) {
                          do {                
                            STRING_TYPE p_brand = e102->P_BRAND;
                            STRING_TYPE p_type = e102->P_TYPE;
                            long p_size = e102->P_SIZE;
                            long v102 = e102->__av;
                            (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st47.modify(p_brand,p_type,p_size,(v101 * v102)), (v101 * v102)) : (void)0);
                            n102 = n102->nxt;
                          } while (n102 && (e102 = n102->obj) && h30 == n102->hash &&  SUPPLIER_CNTPARTSUPP1_E1_18_mapkey0_idxfn::equals(se97, *e102)); 
                        }
                      }{ //slice 
                        const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_20_map_0* i103 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_20_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_20.index[1]);
                        const HASH_RES_t h31 = SUPPLIER_CNTPARTSUPP1_E1_20_mapkey0_idxfn::hash(se98.modify0(ps_partkey));
                        HashIndex_SUPPLIER_CNTPARTSUPP1_E1_20_map_0::IdxNode* n103 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_20_map_0::IdxNode*>(i103->slice(se98, h31));
                        SUPPLIER_CNTPARTSUPP1_E1_20_entry* e103;
                       
                        if (n103 && (e103 = n103->obj)) {
                          do {                
                            STRING_TYPE p_brand = e103->P_BRAND;
                            STRING_TYPE p_type = e103->P_TYPE;
                            long p_size = e103->P_SIZE;
                            long v103 = e103->__av;
                            (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st48.modify(p_brand,p_type,p_size,(v101 * v103)), (v101 * v103)) : (void)0);
                            n103 = n103->nxt;
                          } while (n103 && (e103 = n103->obj) && h31 == n103->hash &&  SUPPLIER_CNTPARTSUPP1_E1_20_mapkey0_idxfn::equals(se98, *e103)); 
                        }
                      }{ //slice 
                        const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_22_map_0* i104 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_22_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_22.index[1]);
                        const HASH_RES_t h32 = SUPPLIER_CNTPARTSUPP1_E1_22_mapkey0_idxfn::hash(se99.modify0(ps_partkey));
                        HashIndex_SUPPLIER_CNTPARTSUPP1_E1_22_map_0::IdxNode* n104 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_22_map_0::IdxNode*>(i104->slice(se99, h32));
                        SUPPLIER_CNTPARTSUPP1_E1_22_entry* e104;
                       
                        if (n104 && (e104 = n104->obj)) {
                          do {                
                            STRING_TYPE p_brand = e104->P_BRAND;
                            STRING_TYPE p_type = e104->P_TYPE;
                            long p_size = e104->P_SIZE;
                            long v104 = e104->__av;
                            (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st49.modify(p_brand,p_type,p_size,(v101 * v104)), (v101 * v104)) : (void)0);
                            n104 = n104->nxt;
                          } while (n104 && (e104 = n104->obj) && h32 == n104->hash &&  SUPPLIER_CNTPARTSUPP1_E1_22_mapkey0_idxfn::equals(se99, *e104)); 
                        }
                      }{ //slice 
                        const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_24_map_0* i105 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_24_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_24.index[1]);
                        const HASH_RES_t h33 = SUPPLIER_CNTPARTSUPP1_E1_24_mapkey0_idxfn::hash(se100.modify0(ps_partkey));
                        HashIndex_SUPPLIER_CNTPARTSUPP1_E1_24_map_0::IdxNode* n105 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_24_map_0::IdxNode*>(i105->slice(se100, h33));
                        SUPPLIER_CNTPARTSUPP1_E1_24_entry* e105;
                       
                        if (n105 && (e105 = n105->obj)) {
                          do {                
                            STRING_TYPE p_brand = e105->P_BRAND;
                            STRING_TYPE p_type = e105->P_TYPE;
                            long p_size = e105->P_SIZE;
                            long v105 = e105->__av;
                            (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st50.modify(p_brand,p_type,p_size,(v101 * v105)), (v101 * v105)) : (void)0);
                            n105 = n105->nxt;
                          } while (n105 && (e105 = n105->obj) && h33 == n105->hash &&  SUPPLIER_CNTPARTSUPP1_E1_24_mapkey0_idxfn::equals(se100, *e105)); 
                        }
                      }{ //slice 
                        const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_26_map_0* i106 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_26_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_26.index[1]);
                        const HASH_RES_t h34 = SUPPLIER_CNTPARTSUPP1_E1_26_mapkey0_idxfn::hash(se101.modify0(ps_partkey));
                        HashIndex_SUPPLIER_CNTPARTSUPP1_E1_26_map_0::IdxNode* n106 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_26_map_0::IdxNode*>(i106->slice(se101, h34));
                        SUPPLIER_CNTPARTSUPP1_E1_26_entry* e106;
                       
                        if (n106 && (e106 = n106->obj)) {
                          do {                
                            STRING_TYPE p_brand = e106->P_BRAND;
                            STRING_TYPE p_type = e106->P_TYPE;
                            long p_size = e106->P_SIZE;
                            long v106 = e106->__av;
                            (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st51.modify(p_brand,p_type,p_size,(v101 * v106)), (v101 * v106)) : (void)0);
                            n106 = n106->nxt;
                          } while (n106 && (e106 = n106->obj) && h34 == n106->hash &&  SUPPLIER_CNTPARTSUPP1_E1_26_mapkey0_idxfn::equals(se101, *e106)); 
                        }
                      }{ //slice 
                        const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_28_map_0* i107 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_28_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_28.index[1]);
                        const HASH_RES_t h35 = SUPPLIER_CNTPARTSUPP1_E1_28_mapkey0_idxfn::hash(se102.modify0(ps_partkey));
                        HashIndex_SUPPLIER_CNTPARTSUPP1_E1_28_map_0::IdxNode* n107 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_28_map_0::IdxNode*>(i107->slice(se102, h35));
                        SUPPLIER_CNTPARTSUPP1_E1_28_entry* e107;
                       
                        if (n107 && (e107 = n107->obj)) {
                          do {                
                            STRING_TYPE p_brand = e107->P_BRAND;
                            STRING_TYPE p_type = e107->P_TYPE;
                            long p_size = e107->P_SIZE;
                            long v107 = e107->__av;
                            (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st52.modify(p_brand,p_type,p_size,(v101 * v107)), (v101 * v107)) : (void)0);
                            n107 = n107->nxt;
                          } while (n107 && (e107 = n107->obj) && h35 == n107->hash &&  SUPPLIER_CNTPARTSUPP1_E1_28_mapkey0_idxfn::equals(se102, *e107)); 
                        }
                      }{ //slice 
                        const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_30_map_0* i108 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_30_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_30.index[1]);
                        const HASH_RES_t h36 = SUPPLIER_CNTPARTSUPP1_E1_30_mapkey0_idxfn::hash(se103.modify0(ps_partkey));
                        HashIndex_SUPPLIER_CNTPARTSUPP1_E1_30_map_0::IdxNode* n108 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_30_map_0::IdxNode*>(i108->slice(se103, h36));
                        SUPPLIER_CNTPARTSUPP1_E1_30_entry* e108;
                       
                        if (n108 && (e108 = n108->obj)) {
                          do {                
                            STRING_TYPE p_brand = e108->P_BRAND;
                            STRING_TYPE p_type = e108->P_TYPE;
                            long p_size = e108->P_SIZE;
                            long v108 = e108->__av;
                            (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st53.modify(p_brand,p_type,p_size,(v101 * v108)), (v101 * v108)) : (void)0);
                            n108 = n108->nxt;
                          } while (n108 && (e108 = n108->obj) && h36 == n108->hash &&  SUPPLIER_CNTPARTSUPP1_E1_30_mapkey0_idxfn::equals(se103, *e108)); 
                        }
                      }{ //slice 
                        const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_32_map_0* i109 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_32_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_32.index[1]);
                        const HASH_RES_t h37 = SUPPLIER_CNTPARTSUPP1_E1_32_mapkey0_idxfn::hash(se104.modify0(ps_partkey));
                        HashIndex_SUPPLIER_CNTPARTSUPP1_E1_32_map_0::IdxNode* n109 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_32_map_0::IdxNode*>(i109->slice(se104, h37));
                        SUPPLIER_CNTPARTSUPP1_E1_32_entry* e109;
                       
                        if (n109 && (e109 = n109->obj)) {
                          do {                
                            STRING_TYPE p_brand = e109->P_BRAND;
                            STRING_TYPE p_type = e109->P_TYPE;
                            long p_size = e109->P_SIZE;
                            long v109 = e109->__av;
                            (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st54.modify(p_brand,p_type,p_size,(v101 * v109)), (v101 * v109)) : (void)0);
                            n109 = n109->nxt;
                          } while (n109 && (e109 = n109->obj) && h37 == n109->hash &&  SUPPLIER_CNTPARTSUPP1_E1_32_mapkey0_idxfn::equals(se104, *e109)); 
                        }
                      }
                      n101 = n101->nxt;
                    } while (n101 && (e101 = n101->obj) && h38 == n101->hash &&  SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_mapkey1_idxfn::equals(se105, *e101)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0* i110 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[1]);
                  const HASH_RES_t h39 = SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::hash(se106.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode* n110 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode*>(i110->slice(se106, h39));
                  SUPPLIER_CNTPARTSUPP1_E1_2_entry* e110;
                 
                  if (n110 && (e110 = n110->obj)) {
                    do {                
                      STRING_TYPE p_brand = e110->P_BRAND;
                      STRING_TYPE p_type = e110->P_TYPE;
                      long p_size = e110->P_SIZE;
                      long v110 = e110->__av;
                      (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st55.modify(p_brand,p_type,p_size,v110), v110) : (void)0);
                      n110 = n110->nxt;
                    } while (n110 && (e110 = n110->obj) && h39 == n110->hash &&  SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::equals(se106, *e110)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0* i111 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_4.index[1]);
                  const HASH_RES_t h40 = SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::hash(se107.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode* n111 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode*>(i111->slice(se107, h40));
                  SUPPLIER_CNTPARTSUPP1_E1_4_entry* e111;
                 
                  if (n111 && (e111 = n111->obj)) {
                    do {                
                      STRING_TYPE p_brand = e111->P_BRAND;
                      STRING_TYPE p_type = e111->P_TYPE;
                      long p_size = e111->P_SIZE;
                      long v111 = e111->__av;
                      (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st56.modify(p_brand,p_type,p_size,v111), v111) : (void)0);
                      n111 = n111->nxt;
                    } while (n111 && (e111 = n111->obj) && h40 == n111->hash &&  SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::equals(se107, *e111)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0* i112 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_6.index[1]);
                  const HASH_RES_t h41 = SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0_idxfn::hash(se108.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0::IdxNode* n112 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0::IdxNode*>(i112->slice(se108, h41));
                  SUPPLIER_CNTPARTSUPP1_E1_6_entry* e112;
                 
                  if (n112 && (e112 = n112->obj)) {
                    do {                
                      STRING_TYPE p_brand = e112->P_BRAND;
                      STRING_TYPE p_type = e112->P_TYPE;
                      long p_size = e112->P_SIZE;
                      long v112 = e112->__av;
                      (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st57.modify(p_brand,p_type,p_size,v112), v112) : (void)0);
                      n112 = n112->nxt;
                    } while (n112 && (e112 = n112->obj) && h41 == n112->hash &&  SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0_idxfn::equals(se108, *e112)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0* i113 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_8.index[1]);
                  const HASH_RES_t h42 = SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0_idxfn::hash(se109.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0::IdxNode* n113 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0::IdxNode*>(i113->slice(se109, h42));
                  SUPPLIER_CNTPARTSUPP1_E1_8_entry* e113;
                 
                  if (n113 && (e113 = n113->obj)) {
                    do {                
                      STRING_TYPE p_brand = e113->P_BRAND;
                      STRING_TYPE p_type = e113->P_TYPE;
                      long p_size = e113->P_SIZE;
                      long v113 = e113->__av;
                      (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st58.modify(p_brand,p_type,p_size,v113), v113) : (void)0);
                      n113 = n113->nxt;
                    } while (n113 && (e113 = n113->obj) && h42 == n113->hash &&  SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0_idxfn::equals(se109, *e113)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0* i114 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_10.index[1]);
                  const HASH_RES_t h43 = SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0_idxfn::hash(se110.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0::IdxNode* n114 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0::IdxNode*>(i114->slice(se110, h43));
                  SUPPLIER_CNTPARTSUPP1_E1_10_entry* e114;
                 
                  if (n114 && (e114 = n114->obj)) {
                    do {                
                      STRING_TYPE p_brand = e114->P_BRAND;
                      STRING_TYPE p_type = e114->P_TYPE;
                      long p_size = e114->P_SIZE;
                      long v114 = e114->__av;
                      (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st59.modify(p_brand,p_type,p_size,v114), v114) : (void)0);
                      n114 = n114->nxt;
                    } while (n114 && (e114 = n114->obj) && h43 == n114->hash &&  SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0_idxfn::equals(se110, *e114)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0* i115 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_12.index[1]);
                  const HASH_RES_t h44 = SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0_idxfn::hash(se111.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0::IdxNode* n115 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0::IdxNode*>(i115->slice(se111, h44));
                  SUPPLIER_CNTPARTSUPP1_E1_12_entry* e115;
                 
                  if (n115 && (e115 = n115->obj)) {
                    do {                
                      STRING_TYPE p_brand = e115->P_BRAND;
                      STRING_TYPE p_type = e115->P_TYPE;
                      long p_size = e115->P_SIZE;
                      long v115 = e115->__av;
                      (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st60.modify(p_brand,p_type,p_size,v115), v115) : (void)0);
                      n115 = n115->nxt;
                    } while (n115 && (e115 = n115->obj) && h44 == n115->hash &&  SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0_idxfn::equals(se111, *e115)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0* i116 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_14.index[1]);
                  const HASH_RES_t h45 = SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0_idxfn::hash(se112.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0::IdxNode* n116 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0::IdxNode*>(i116->slice(se112, h45));
                  SUPPLIER_CNTPARTSUPP1_E1_14_entry* e116;
                 
                  if (n116 && (e116 = n116->obj)) {
                    do {                
                      STRING_TYPE p_brand = e116->P_BRAND;
                      STRING_TYPE p_type = e116->P_TYPE;
                      long p_size = e116->P_SIZE;
                      long v116 = e116->__av;
                      (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st61.modify(p_brand,p_type,p_size,v116), v116) : (void)0);
                      n116 = n116->nxt;
                    } while (n116 && (e116 = n116->obj) && h45 == n116->hash &&  SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0_idxfn::equals(se112, *e116)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0* i117 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_16.index[1]);
                  const HASH_RES_t h46 = SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0_idxfn::hash(se113.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0::IdxNode* n117 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0::IdxNode*>(i117->slice(se113, h46));
                  SUPPLIER_CNTPARTSUPP1_E1_16_entry* e117;
                 
                  if (n117 && (e117 = n117->obj)) {
                    do {                
                      STRING_TYPE p_brand = e117->P_BRAND;
                      STRING_TYPE p_type = e117->P_TYPE;
                      long p_size = e117->P_SIZE;
                      long v117 = e117->__av;
                      (/*if */(l8 == 0L) ? agg13.addOrDelOnZero(st62.modify(p_brand,p_type,p_size,v117), v117) : (void)0);
                      n117 = n117->nxt;
                    } while (n117 && (e117 = n117->obj) && h46 == n117->hash &&  SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0_idxfn::equals(se113, *e117)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple4_SSL_L, long>* i118 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg13.index[0]);
                  HashIndex<tuple4_SSL_L, long>::IdxNode* n118; 
                  tuple4_SSL_L* e118;
                
                  for (size_t i = 0; i < i118->size_; i++)
                  {
                    n118 = i118->buckets_ + i;
                    while (n118 && (e118 = n118->obj))
                    {
                      STRING_TYPE p_brand = e118->_1;
                      STRING_TYPE p_type = e118->_2;
                      long p_size = e118->_3;  
                      long v118 = e118->__av; 
                    SUPPLIER_CNT.addOrDelOnZero(se87.modify(p_brand,p_type,p_size),((v100 != 0 ? 1L : 0L) * (v118 != 0 ? 1L : 0L)));      
                      n118 = n118->nxt;
                    }
                  }
                }
              n100 = n100->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0* i119 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0*>(SUPPLIER_CNTPARTSUPP1_DOMAIN1.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_DOMAIN1_map_0::IdxNode* n119; 
          SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry* e119;
        
          for (size_t i = 0; i < i119->size_; i++)
          {
            n119 = i119->buckets_ + i;
            while (n119 && (e119 = n119->obj))
            {
                long ps_suppkey = e119->PS_SUPPKEY;
                long v119 = e119->__av;
                agg14.clear();
                
                long l9 = SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se114.modify(ps_suppkey));
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0* i120 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[1]);
                  const HASH_RES_t h47 = SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::hash(se115.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode* n120 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode*>(i120->slice(se115, h47));
                  SUPPLIER_CNTPARTSUPP1_E1_2_entry* e120;
                 
                  if (n120 && (e120 = n120->obj)) {
                    do {                
                      STRING_TYPE p_brand = e120->P_BRAND;
                      STRING_TYPE p_type = e120->P_TYPE;
                      long p_size = e120->P_SIZE;
                      long v120 = e120->__av;
                      (/*if */(l9 == 0L) ? agg14.addOrDelOnZero(st63.modify(p_brand,p_type,p_size,v120), v120) : (void)0);
                      n120 = n120->nxt;
                    } while (n120 && (e120 = n120->obj) && h47 == n120->hash &&  SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::equals(se115, *e120)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0* i121 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_4.index[1]);
                  const HASH_RES_t h48 = SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::hash(se116.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode* n121 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode*>(i121->slice(se116, h48));
                  SUPPLIER_CNTPARTSUPP1_E1_4_entry* e121;
                 
                  if (n121 && (e121 = n121->obj)) {
                    do {                
                      STRING_TYPE p_brand = e121->P_BRAND;
                      STRING_TYPE p_type = e121->P_TYPE;
                      long p_size = e121->P_SIZE;
                      long v121 = e121->__av;
                      (/*if */(l9 == 0L) ? agg14.addOrDelOnZero(st64.modify(p_brand,p_type,p_size,v121), v121) : (void)0);
                      n121 = n121->nxt;
                    } while (n121 && (e121 = n121->obj) && h48 == n121->hash &&  SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::equals(se116, *e121)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0* i122 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_6.index[1]);
                  const HASH_RES_t h49 = SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0_idxfn::hash(se117.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0::IdxNode* n122 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_6_map_0::IdxNode*>(i122->slice(se117, h49));
                  SUPPLIER_CNTPARTSUPP1_E1_6_entry* e122;
                 
                  if (n122 && (e122 = n122->obj)) {
                    do {                
                      STRING_TYPE p_brand = e122->P_BRAND;
                      STRING_TYPE p_type = e122->P_TYPE;
                      long p_size = e122->P_SIZE;
                      long v122 = e122->__av;
                      (/*if */(l9 == 0L) ? agg14.addOrDelOnZero(st65.modify(p_brand,p_type,p_size,v122), v122) : (void)0);
                      n122 = n122->nxt;
                    } while (n122 && (e122 = n122->obj) && h49 == n122->hash &&  SUPPLIER_CNTPARTSUPP1_E1_6_mapkey0_idxfn::equals(se117, *e122)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0* i123 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_8.index[1]);
                  const HASH_RES_t h50 = SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0_idxfn::hash(se118.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0::IdxNode* n123 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_8_map_0::IdxNode*>(i123->slice(se118, h50));
                  SUPPLIER_CNTPARTSUPP1_E1_8_entry* e123;
                 
                  if (n123 && (e123 = n123->obj)) {
                    do {                
                      STRING_TYPE p_brand = e123->P_BRAND;
                      STRING_TYPE p_type = e123->P_TYPE;
                      long p_size = e123->P_SIZE;
                      long v123 = e123->__av;
                      (/*if */(l9 == 0L) ? agg14.addOrDelOnZero(st66.modify(p_brand,p_type,p_size,v123), v123) : (void)0);
                      n123 = n123->nxt;
                    } while (n123 && (e123 = n123->obj) && h50 == n123->hash &&  SUPPLIER_CNTPARTSUPP1_E1_8_mapkey0_idxfn::equals(se118, *e123)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0* i124 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_10.index[1]);
                  const HASH_RES_t h51 = SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0_idxfn::hash(se119.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0::IdxNode* n124 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_10_map_0::IdxNode*>(i124->slice(se119, h51));
                  SUPPLIER_CNTPARTSUPP1_E1_10_entry* e124;
                 
                  if (n124 && (e124 = n124->obj)) {
                    do {                
                      STRING_TYPE p_brand = e124->P_BRAND;
                      STRING_TYPE p_type = e124->P_TYPE;
                      long p_size = e124->P_SIZE;
                      long v124 = e124->__av;
                      (/*if */(l9 == 0L) ? agg14.addOrDelOnZero(st67.modify(p_brand,p_type,p_size,v124), v124) : (void)0);
                      n124 = n124->nxt;
                    } while (n124 && (e124 = n124->obj) && h51 == n124->hash &&  SUPPLIER_CNTPARTSUPP1_E1_10_mapkey0_idxfn::equals(se119, *e124)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0* i125 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_12.index[1]);
                  const HASH_RES_t h52 = SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0_idxfn::hash(se120.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0::IdxNode* n125 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_12_map_0::IdxNode*>(i125->slice(se120, h52));
                  SUPPLIER_CNTPARTSUPP1_E1_12_entry* e125;
                 
                  if (n125 && (e125 = n125->obj)) {
                    do {                
                      STRING_TYPE p_brand = e125->P_BRAND;
                      STRING_TYPE p_type = e125->P_TYPE;
                      long p_size = e125->P_SIZE;
                      long v125 = e125->__av;
                      (/*if */(l9 == 0L) ? agg14.addOrDelOnZero(st68.modify(p_brand,p_type,p_size,v125), v125) : (void)0);
                      n125 = n125->nxt;
                    } while (n125 && (e125 = n125->obj) && h52 == n125->hash &&  SUPPLIER_CNTPARTSUPP1_E1_12_mapkey0_idxfn::equals(se120, *e125)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0* i126 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_14.index[1]);
                  const HASH_RES_t h53 = SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0_idxfn::hash(se121.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0::IdxNode* n126 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_14_map_0::IdxNode*>(i126->slice(se121, h53));
                  SUPPLIER_CNTPARTSUPP1_E1_14_entry* e126;
                 
                  if (n126 && (e126 = n126->obj)) {
                    do {                
                      STRING_TYPE p_brand = e126->P_BRAND;
                      STRING_TYPE p_type = e126->P_TYPE;
                      long p_size = e126->P_SIZE;
                      long v126 = e126->__av;
                      (/*if */(l9 == 0L) ? agg14.addOrDelOnZero(st69.modify(p_brand,p_type,p_size,v126), v126) : (void)0);
                      n126 = n126->nxt;
                    } while (n126 && (e126 = n126->obj) && h53 == n126->hash &&  SUPPLIER_CNTPARTSUPP1_E1_14_mapkey0_idxfn::equals(se121, *e126)); 
                  }
                }{ //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0* i127 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_16.index[1]);
                  const HASH_RES_t h54 = SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0_idxfn::hash(se122.modify0(ps_suppkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0::IdxNode* n127 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_16_map_0::IdxNode*>(i127->slice(se122, h54));
                  SUPPLIER_CNTPARTSUPP1_E1_16_entry* e127;
                 
                  if (n127 && (e127 = n127->obj)) {
                    do {                
                      STRING_TYPE p_brand = e127->P_BRAND;
                      STRING_TYPE p_type = e127->P_TYPE;
                      long p_size = e127->P_SIZE;
                      long v127 = e127->__av;
                      (/*if */(l9 == 0L) ? agg14.addOrDelOnZero(st70.modify(p_brand,p_type,p_size,v127), v127) : (void)0);
                      n127 = n127->nxt;
                    } while (n127 && (e127 = n127->obj) && h54 == n127->hash &&  SUPPLIER_CNTPARTSUPP1_E1_16_mapkey0_idxfn::equals(se122, *e127)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple4_SSL_L, long>* i128 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg14.index[0]);
                  HashIndex<tuple4_SSL_L, long>::IdxNode* n128; 
                  tuple4_SSL_L* e128;
                
                  for (size_t i = 0; i < i128->size_; i++)
                  {
                    n128 = i128->buckets_ + i;
                    while (n128 && (e128 = n128->obj))
                    {
                      STRING_TYPE p_brand = e128->_1;
                      STRING_TYPE p_type = e128->_2;
                      long p_size = e128->_3;  
                      long v128 = e128->__av; 
                    SUPPLIER_CNT.addOrDelOnZero(se87.modify(p_brand,p_type,p_size),(((v119 != 0 ? 1L : 0L) * (v128 != 0 ? 1L : 0L)) * -1L));      
                      n128 = n128->nxt;
                    }
                  }
                }
              n119 = n119->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01* i129 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01::IdxNode* n129; 
          SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry* e129;
        
          for (size_t i = 0; i < i129->size_; i++)
          {
            n129 = i129->buckets_ + i;
            while (n129 && (e129 = n129->obj))
            {
                long ps_partkey = e129->PS_PARTKEY;
                long ps_suppkey = e129->PS_SUPPKEY;
                long v129 = e129->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPART1_E1_1PARTSUPP1_map_0* i130 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_1PARTSUPP1_map_0*>(SUPPLIER_CNTPART1_E1_1PARTSUPP1.index[1]);
                  const HASH_RES_t h55 = SUPPLIER_CNTPART1_E1_1PARTSUPP1_mapkey0_idxfn::hash(se124.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPART1_E1_1PARTSUPP1_map_0::IdxNode* n130 = static_cast<HashIndex_SUPPLIER_CNTPART1_E1_1PARTSUPP1_map_0::IdxNode*>(i130->slice(se124, h55));
                  SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry* e130;
                 
                  if (n130 && (e130 = n130->obj)) {
                    do {                
                      STRING_TYPE p_brand = e130->P_BRAND;
                      STRING_TYPE p_type = e130->P_TYPE;
                      long p_size = e130->P_SIZE;
                      long v130 = e130->__av;
                      SUPPLIER_CNTPART1_E1_1.addOrDelOnZero(se123.modify(ps_suppkey,p_brand,p_type,p_size),(v129 * v130));
                      n130 = n130->nxt;
                    } while (n130 && (e130 = n130->obj) && h55 == n130->hash &&  SUPPLIER_CNTPART1_E1_1PARTSUPP1_mapkey0_idxfn::equals(se124, *e130)); 
                  }
                }
              n129 = n129->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01* i131 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01::IdxNode* n131; 
          SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry* e131;
        
          for (size_t i = 0; i < i131->size_; i++)
          {
            n131 = i131->buckets_ + i;
            while (n131 && (e131 = n131->obj))
            {
                long ps_partkey = e131->PS_PARTKEY;
                long ps_suppkey = e131->PS_SUPPKEY;
                long v131 = e131->__av;
                SUPPLIER_CNTPART1_E1_33.addOrDelOnZero(se125.modify(ps_partkey,ps_suppkey),v131);
              n131 = n131->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01* i132 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01::IdxNode* n132; 
          SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry* e132;
        
          for (size_t i = 0; i < i132->size_; i++)
          {
            n132 = i132->buckets_ + i;
            while (n132 && (e132 = n132->obj))
            {
                long ps_partkey = e132->PS_PARTKEY;
                long ps_suppkey = e132->PS_SUPPKEY;
                long v132 = e132->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_map_0* i133 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_18.index[1]);
                  const HASH_RES_t h56 = SUPPLIER_CNTPARTSUPP1_E1_18_mapkey0_idxfn::hash(se127.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_map_0::IdxNode* n133 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_map_0::IdxNode*>(i133->slice(se127, h56));
                  SUPPLIER_CNTPARTSUPP1_E1_18_entry* e133;
                 
                  if (n133 && (e133 = n133->obj)) {
                    do {                
                      STRING_TYPE p_brand = e133->P_BRAND;
                      STRING_TYPE p_type = e133->P_TYPE;
                      long p_size = e133->P_SIZE;
                      long v133 = e133->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_2.addOrDelOnZero(se126.modify(ps_suppkey,p_brand,p_type,p_size),(v132 * v133));
                      n133 = n133->nxt;
                    } while (n133 && (e133 = n133->obj) && h56 == n133->hash &&  SUPPLIER_CNTPARTSUPP1_E1_18_mapkey0_idxfn::equals(se127, *e133)); 
                  }
                }
              n132 = n132->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01* i134 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01::IdxNode* n134; 
          SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry* e134;
        
          for (size_t i = 0; i < i134->size_; i++)
          {
            n134 = i134->buckets_ + i;
            while (n134 && (e134 = n134->obj))
            {
                long ps_partkey = e134->PS_PARTKEY;
                long ps_suppkey = e134->PS_SUPPKEY;
                long v134 = e134->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_20_map_0* i135 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_20_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_20.index[1]);
                  const HASH_RES_t h57 = SUPPLIER_CNTPARTSUPP1_E1_20_mapkey0_idxfn::hash(se129.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_20_map_0::IdxNode* n135 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_20_map_0::IdxNode*>(i135->slice(se129, h57));
                  SUPPLIER_CNTPARTSUPP1_E1_20_entry* e135;
                 
                  if (n135 && (e135 = n135->obj)) {
                    do {                
                      STRING_TYPE p_brand = e135->P_BRAND;
                      STRING_TYPE p_type = e135->P_TYPE;
                      long p_size = e135->P_SIZE;
                      long v135 = e135->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_4.addOrDelOnZero(se128.modify(ps_suppkey,p_brand,p_type,p_size),(v134 * v135));
                      n135 = n135->nxt;
                    } while (n135 && (e135 = n135->obj) && h57 == n135->hash &&  SUPPLIER_CNTPARTSUPP1_E1_20_mapkey0_idxfn::equals(se129, *e135)); 
                  }
                }
              n134 = n134->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01* i136 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01::IdxNode* n136; 
          SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry* e136;
        
          for (size_t i = 0; i < i136->size_; i++)
          {
            n136 = i136->buckets_ + i;
            while (n136 && (e136 = n136->obj))
            {
                long ps_partkey = e136->PS_PARTKEY;
                long ps_suppkey = e136->PS_SUPPKEY;
                long v136 = e136->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_22_map_0* i137 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_22_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_22.index[1]);
                  const HASH_RES_t h58 = SUPPLIER_CNTPARTSUPP1_E1_22_mapkey0_idxfn::hash(se131.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_22_map_0::IdxNode* n137 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_22_map_0::IdxNode*>(i137->slice(se131, h58));
                  SUPPLIER_CNTPARTSUPP1_E1_22_entry* e137;
                 
                  if (n137 && (e137 = n137->obj)) {
                    do {                
                      STRING_TYPE p_brand = e137->P_BRAND;
                      STRING_TYPE p_type = e137->P_TYPE;
                      long p_size = e137->P_SIZE;
                      long v137 = e137->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_6.addOrDelOnZero(se130.modify(ps_suppkey,p_brand,p_type,p_size),(v136 * v137));
                      n137 = n137->nxt;
                    } while (n137 && (e137 = n137->obj) && h58 == n137->hash &&  SUPPLIER_CNTPARTSUPP1_E1_22_mapkey0_idxfn::equals(se131, *e137)); 
                  }
                }
              n136 = n136->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01* i138 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01::IdxNode* n138; 
          SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry* e138;
        
          for (size_t i = 0; i < i138->size_; i++)
          {
            n138 = i138->buckets_ + i;
            while (n138 && (e138 = n138->obj))
            {
                long ps_partkey = e138->PS_PARTKEY;
                long ps_suppkey = e138->PS_SUPPKEY;
                long v138 = e138->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_24_map_0* i139 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_24_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_24.index[1]);
                  const HASH_RES_t h59 = SUPPLIER_CNTPARTSUPP1_E1_24_mapkey0_idxfn::hash(se133.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_24_map_0::IdxNode* n139 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_24_map_0::IdxNode*>(i139->slice(se133, h59));
                  SUPPLIER_CNTPARTSUPP1_E1_24_entry* e139;
                 
                  if (n139 && (e139 = n139->obj)) {
                    do {                
                      STRING_TYPE p_brand = e139->P_BRAND;
                      STRING_TYPE p_type = e139->P_TYPE;
                      long p_size = e139->P_SIZE;
                      long v139 = e139->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_8.addOrDelOnZero(se132.modify(ps_suppkey,p_brand,p_type,p_size),(v138 * v139));
                      n139 = n139->nxt;
                    } while (n139 && (e139 = n139->obj) && h59 == n139->hash &&  SUPPLIER_CNTPARTSUPP1_E1_24_mapkey0_idxfn::equals(se133, *e139)); 
                  }
                }
              n138 = n138->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01* i140 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01::IdxNode* n140; 
          SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry* e140;
        
          for (size_t i = 0; i < i140->size_; i++)
          {
            n140 = i140->buckets_ + i;
            while (n140 && (e140 = n140->obj))
            {
                long ps_partkey = e140->PS_PARTKEY;
                long ps_suppkey = e140->PS_SUPPKEY;
                long v140 = e140->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_26_map_0* i141 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_26_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_26.index[1]);
                  const HASH_RES_t h60 = SUPPLIER_CNTPARTSUPP1_E1_26_mapkey0_idxfn::hash(se135.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_26_map_0::IdxNode* n141 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_26_map_0::IdxNode*>(i141->slice(se135, h60));
                  SUPPLIER_CNTPARTSUPP1_E1_26_entry* e141;
                 
                  if (n141 && (e141 = n141->obj)) {
                    do {                
                      STRING_TYPE p_brand = e141->P_BRAND;
                      STRING_TYPE p_type = e141->P_TYPE;
                      long p_size = e141->P_SIZE;
                      long v141 = e141->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_10.addOrDelOnZero(se134.modify(ps_suppkey,p_brand,p_type,p_size),(v140 * v141));
                      n141 = n141->nxt;
                    } while (n141 && (e141 = n141->obj) && h60 == n141->hash &&  SUPPLIER_CNTPARTSUPP1_E1_26_mapkey0_idxfn::equals(se135, *e141)); 
                  }
                }
              n140 = n140->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01* i142 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01::IdxNode* n142; 
          SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry* e142;
        
          for (size_t i = 0; i < i142->size_; i++)
          {
            n142 = i142->buckets_ + i;
            while (n142 && (e142 = n142->obj))
            {
                long ps_partkey = e142->PS_PARTKEY;
                long ps_suppkey = e142->PS_SUPPKEY;
                long v142 = e142->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_28_map_0* i143 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_28_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_28.index[1]);
                  const HASH_RES_t h61 = SUPPLIER_CNTPARTSUPP1_E1_28_mapkey0_idxfn::hash(se137.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_28_map_0::IdxNode* n143 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_28_map_0::IdxNode*>(i143->slice(se137, h61));
                  SUPPLIER_CNTPARTSUPP1_E1_28_entry* e143;
                 
                  if (n143 && (e143 = n143->obj)) {
                    do {                
                      STRING_TYPE p_brand = e143->P_BRAND;
                      STRING_TYPE p_type = e143->P_TYPE;
                      long p_size = e143->P_SIZE;
                      long v143 = e143->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_12.addOrDelOnZero(se136.modify(ps_suppkey,p_brand,p_type,p_size),(v142 * v143));
                      n143 = n143->nxt;
                    } while (n143 && (e143 = n143->obj) && h61 == n143->hash &&  SUPPLIER_CNTPARTSUPP1_E1_28_mapkey0_idxfn::equals(se137, *e143)); 
                  }
                }
              n142 = n142->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01* i144 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01::IdxNode* n144; 
          SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry* e144;
        
          for (size_t i = 0; i < i144->size_; i++)
          {
            n144 = i144->buckets_ + i;
            while (n144 && (e144 = n144->obj))
            {
                long ps_partkey = e144->PS_PARTKEY;
                long ps_suppkey = e144->PS_SUPPKEY;
                long v144 = e144->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_30_map_0* i145 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_30_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_30.index[1]);
                  const HASH_RES_t h62 = SUPPLIER_CNTPARTSUPP1_E1_30_mapkey0_idxfn::hash(se139.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_30_map_0::IdxNode* n145 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_30_map_0::IdxNode*>(i145->slice(se139, h62));
                  SUPPLIER_CNTPARTSUPP1_E1_30_entry* e145;
                 
                  if (n145 && (e145 = n145->obj)) {
                    do {                
                      STRING_TYPE p_brand = e145->P_BRAND;
                      STRING_TYPE p_type = e145->P_TYPE;
                      long p_size = e145->P_SIZE;
                      long v145 = e145->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_14.addOrDelOnZero(se138.modify(ps_suppkey,p_brand,p_type,p_size),(v144 * v145));
                      n145 = n145->nxt;
                    } while (n145 && (e145 = n145->obj) && h62 == n145->hash &&  SUPPLIER_CNTPARTSUPP1_E1_30_mapkey0_idxfn::equals(se139, *e145)); 
                  }
                }
              n144 = n144->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01* i146 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01*>(SUPPLIER_CNTPARTSUPP1_E1_18_DELTA.index[0]);
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map_01::IdxNode* n146; 
          SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry* e146;
        
          for (size_t i = 0; i < i146->size_; i++)
          {
            n146 = i146->buckets_ + i;
            while (n146 && (e146 = n146->obj))
            {
                long ps_partkey = e146->PS_PARTKEY;
                long ps_suppkey = e146->PS_SUPPKEY;
                long v146 = e146->__av;
                { //slice 
                  const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_32_map_0* i147 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_32_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_32.index[1]);
                  const HASH_RES_t h63 = SUPPLIER_CNTPARTSUPP1_E1_32_mapkey0_idxfn::hash(se141.modify0(ps_partkey));
                  HashIndex_SUPPLIER_CNTPARTSUPP1_E1_32_map_0::IdxNode* n147 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_32_map_0::IdxNode*>(i147->slice(se141, h63));
                  SUPPLIER_CNTPARTSUPP1_E1_32_entry* e147;
                 
                  if (n147 && (e147 = n147->obj)) {
                    do {                
                      STRING_TYPE p_brand = e147->P_BRAND;
                      STRING_TYPE p_type = e147->P_TYPE;
                      long p_size = e147->P_SIZE;
                      long v147 = e147->__av;
                      SUPPLIER_CNTPARTSUPP1_E1_16.addOrDelOnZero(se140.modify(ps_suppkey,p_brand,p_type,p_size),(v146 * v147));
                      n147 = n147->nxt;
                    } while (n147 && (e147 = n147->obj) && h63 == n147->hash &&  SUPPLIER_CNTPARTSUPP1_E1_32_mapkey0_idxfn::equals(se141, *e147)); 
                  }
                }
              n146 = n146->nxt;
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
    SUPPLIER_CNTPART1_E1_33_DELTA_entry se1;
    SUPPLIER_CNTPART1_DOMAIN1_entry se2;
    SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_entry se3;
    SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_entry se4;
    SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_entry se5;
    SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_entry se6;
    SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_entry se7;
    SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_entry se8;
    SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_entry se9;
    SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_entry se10;
    SUPPLIER_CNT_entry se11;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se12;
    tuple5_LSSL_L st1;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se13;
    tuple5_LSSL_L st2;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se14;
    tuple5_LSSL_L st3;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se15;
    tuple5_LSSL_L st4;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se16;
    tuple5_LSSL_L st5;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se17;
    tuple5_LSSL_L st6;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se18;
    tuple5_LSSL_L st7;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se19;
    tuple5_LSSL_L st8;
    tuple4_SSL_L st9;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se20;
    tuple2_L_L st10;
    SUPPLIER_CNTPART1_E1_1_entry se21;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se22;
    tuple2_L_L st11;
    SUPPLIER_CNTPART1_E1_33_entry se23;
    SUPPLIER_CNTPART1_E1_33_DELTA_entry se24;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se25;
    tuple2_L_L st12;
    SUPPLIER_CNTPART1_E1_1_entry se26;
    SUPPLIER_CNTPART1_E1_1_entry se27;
    SUPPLIER_CNTPART1_E1_33_entry se28;
    SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry se29;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se30;
    SUPPLIER_CNTPART1_E1_33_entry se31;
    SUPPLIER_CNTPARTSUPP1_E1_4_entry se32;
    SUPPLIER_CNTPART1_E1_33_entry se33;
    SUPPLIER_CNTPARTSUPP1_E1_6_entry se34;
    SUPPLIER_CNTPART1_E1_33_entry se35;
    SUPPLIER_CNTPARTSUPP1_E1_8_entry se36;
    SUPPLIER_CNTPART1_E1_33_entry se37;
    SUPPLIER_CNTPARTSUPP1_E1_10_entry se38;
    SUPPLIER_CNTPART1_E1_33_entry se39;
    SUPPLIER_CNTPARTSUPP1_E1_12_entry se40;
    SUPPLIER_CNTPART1_E1_33_entry se41;
    SUPPLIER_CNTPARTSUPP1_E1_14_entry se42;
    SUPPLIER_CNTPART1_E1_33_entry se43;
    SUPPLIER_CNTPARTSUPP1_E1_16_entry se44;
    SUPPLIER_CNTPART1_E1_33_entry se45;
    SUPPLIER_CNTPARTSUPP1_E1_18_entry se46;
    SUPPLIER_CNTPARTSUPP1_E1_20_entry se47;
    SUPPLIER_CNTPARTSUPP1_E1_22_entry se48;
    SUPPLIER_CNTPARTSUPP1_E1_24_entry se49;
    SUPPLIER_CNTPARTSUPP1_E1_26_entry se50;
    SUPPLIER_CNTPARTSUPP1_E1_28_entry se51;
    SUPPLIER_CNTPARTSUPP1_E1_30_entry se52;
    SUPPLIER_CNTPARTSUPP1_E1_32_entry se53;
    SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry se54;
    SUPPLIER_CNTSUPPLIER1_DOMAIN1_entry se55;
    SUPPLIER_CNT_entry se56;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se57;
    tuple5_LSSL_L st13;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se58;
    tuple5_LSSL_L st14;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se59;
    tuple5_LSSL_L st15;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se60;
    tuple5_LSSL_L st16;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se61;
    tuple5_LSSL_L st17;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se62;
    tuple5_LSSL_L st18;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se63;
    tuple5_LSSL_L st19;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se64;
    tuple5_LSSL_L st20;
    tuple4_SSL_L st21;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se65;
    SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_entry se66;
    tuple4_SSL_L st22;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se67;
    tuple4_SSL_L st23;
    SUPPLIER_CNTPARTSUPP1_E1_4_entry se68;
    tuple4_SSL_L st24;
    SUPPLIER_CNTPARTSUPP1_E1_6_entry se69;
    tuple4_SSL_L st25;
    SUPPLIER_CNTPARTSUPP1_E1_8_entry se70;
    tuple4_SSL_L st26;
    SUPPLIER_CNTPARTSUPP1_E1_10_entry se71;
    tuple4_SSL_L st27;
    SUPPLIER_CNTPARTSUPP1_E1_12_entry se72;
    tuple4_SSL_L st28;
    SUPPLIER_CNTPARTSUPP1_E1_14_entry se73;
    tuple4_SSL_L st29;
    SUPPLIER_CNTPARTSUPP1_E1_16_entry se74;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se75;
    tuple4_SSL_L st30;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se76;
    tuple4_SSL_L st31;
    SUPPLIER_CNTPARTSUPP1_E1_4_entry se77;
    tuple4_SSL_L st32;
    SUPPLIER_CNTPARTSUPP1_E1_6_entry se78;
    tuple4_SSL_L st33;
    SUPPLIER_CNTPARTSUPP1_E1_8_entry se79;
    tuple4_SSL_L st34;
    SUPPLIER_CNTPARTSUPP1_E1_10_entry se80;
    tuple4_SSL_L st35;
    SUPPLIER_CNTPARTSUPP1_E1_12_entry se81;
    tuple4_SSL_L st36;
    SUPPLIER_CNTPARTSUPP1_E1_14_entry se82;
    tuple4_SSL_L st37;
    SUPPLIER_CNTPARTSUPP1_E1_16_entry se83;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se84;
    SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry se85;
    SUPPLIER_CNTPARTSUPP1_DOMAIN1_entry se86;
    SUPPLIER_CNT_entry se87;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se88;
    tuple5_LSSL_L st38;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se89;
    tuple5_LSSL_L st39;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se90;
    tuple5_LSSL_L st40;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se91;
    tuple5_LSSL_L st41;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se92;
    tuple5_LSSL_L st42;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se93;
    tuple5_LSSL_L st43;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se94;
    tuple5_LSSL_L st44;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se95;
    tuple5_LSSL_L st45;
    tuple4_SSL_L st46;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se96;
    tuple4_SSL_L st47;
    SUPPLIER_CNTPARTSUPP1_E1_18_entry se97;
    tuple4_SSL_L st48;
    SUPPLIER_CNTPARTSUPP1_E1_20_entry se98;
    tuple4_SSL_L st49;
    SUPPLIER_CNTPARTSUPP1_E1_22_entry se99;
    tuple4_SSL_L st50;
    SUPPLIER_CNTPARTSUPP1_E1_24_entry se100;
    tuple4_SSL_L st51;
    SUPPLIER_CNTPARTSUPP1_E1_26_entry se101;
    tuple4_SSL_L st52;
    SUPPLIER_CNTPARTSUPP1_E1_28_entry se102;
    tuple4_SSL_L st53;
    SUPPLIER_CNTPARTSUPP1_E1_30_entry se103;
    tuple4_SSL_L st54;
    SUPPLIER_CNTPARTSUPP1_E1_32_entry se104;
    SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_entry se105;
    tuple4_SSL_L st55;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se106;
    tuple4_SSL_L st56;
    SUPPLIER_CNTPARTSUPP1_E1_4_entry se107;
    tuple4_SSL_L st57;
    SUPPLIER_CNTPARTSUPP1_E1_6_entry se108;
    tuple4_SSL_L st58;
    SUPPLIER_CNTPARTSUPP1_E1_8_entry se109;
    tuple4_SSL_L st59;
    SUPPLIER_CNTPARTSUPP1_E1_10_entry se110;
    tuple4_SSL_L st60;
    SUPPLIER_CNTPARTSUPP1_E1_12_entry se111;
    tuple4_SSL_L st61;
    SUPPLIER_CNTPARTSUPP1_E1_14_entry se112;
    tuple4_SSL_L st62;
    SUPPLIER_CNTPARTSUPP1_E1_16_entry se113;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se114;
    tuple4_SSL_L st63;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se115;
    tuple4_SSL_L st64;
    SUPPLIER_CNTPARTSUPP1_E1_4_entry se116;
    tuple4_SSL_L st65;
    SUPPLIER_CNTPARTSUPP1_E1_6_entry se117;
    tuple4_SSL_L st66;
    SUPPLIER_CNTPARTSUPP1_E1_8_entry se118;
    tuple4_SSL_L st67;
    SUPPLIER_CNTPARTSUPP1_E1_10_entry se119;
    tuple4_SSL_L st68;
    SUPPLIER_CNTPARTSUPP1_E1_12_entry se120;
    tuple4_SSL_L st69;
    SUPPLIER_CNTPARTSUPP1_E1_14_entry se121;
    tuple4_SSL_L st70;
    SUPPLIER_CNTPARTSUPP1_E1_16_entry se122;
    SUPPLIER_CNTPART1_E1_1_entry se123;
    SUPPLIER_CNTPART1_E1_1PARTSUPP1_entry se124;
    SUPPLIER_CNTPART1_E1_33_entry se125;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se126;
    SUPPLIER_CNTPARTSUPP1_E1_18_entry se127;
    SUPPLIER_CNTPARTSUPP1_E1_4_entry se128;
    SUPPLIER_CNTPARTSUPP1_E1_20_entry se129;
    SUPPLIER_CNTPARTSUPP1_E1_6_entry se130;
    SUPPLIER_CNTPARTSUPP1_E1_22_entry se131;
    SUPPLIER_CNTPARTSUPP1_E1_8_entry se132;
    SUPPLIER_CNTPARTSUPP1_E1_24_entry se133;
    SUPPLIER_CNTPARTSUPP1_E1_10_entry se134;
    SUPPLIER_CNTPARTSUPP1_E1_26_entry se135;
    SUPPLIER_CNTPARTSUPP1_E1_12_entry se136;
    SUPPLIER_CNTPARTSUPP1_E1_28_entry se137;
    SUPPLIER_CNTPARTSUPP1_E1_14_entry se138;
    SUPPLIER_CNTPARTSUPP1_E1_30_entry se139;
    SUPPLIER_CNTPARTSUPP1_E1_16_entry se140;
    SUPPLIER_CNTPARTSUPP1_E1_32_entry se141;
    /* regex_t temporary objects */
    regex_t preg2;
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    SUPPLIER_CNTSUPPLIER1_DOMAIN1_map SUPPLIER_CNTSUPPLIER1_DOMAIN1;
    SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA_map SUPPLIER_CNTSUPPLIER1_E1_2_L2_2_DELTA;
    SUPPLIER_CNTPART1_DOMAIN1_map SUPPLIER_CNTPART1_DOMAIN1;
    SUPPLIER_CNTPART1_E1_1_map SUPPLIER_CNTPART1_E1_1;
    SUPPLIER_CNTPART1_E1_1PARTSUPP1_map SUPPLIER_CNTPART1_E1_1PARTSUPP1;
    SUPPLIER_CNTPART1_E1_33_DELTA_map SUPPLIER_CNTPART1_E1_33_DELTA;
    SUPPLIER_CNTPART1_E1_33_map SUPPLIER_CNTPART1_E1_33;
    SUPPLIER_CNTPARTSUPP1_DOMAIN1_map SUPPLIER_CNTPARTSUPP1_DOMAIN1;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_map SUPPLIER_CNTPARTSUPP1_E1_1_L2_1;
    SUPPLIER_CNTPARTSUPP1_E1_2_map SUPPLIER_CNTPARTSUPP1_E1_2;
    SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA_map SUPPLIER_CNTPARTSUPP1_E1_2PART1_DELTA;
    SUPPLIER_CNTPARTSUPP1_E1_4_map SUPPLIER_CNTPARTSUPP1_E1_4;
    SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA_map SUPPLIER_CNTPARTSUPP1_E1_4PART1_DELTA;
    SUPPLIER_CNTPARTSUPP1_E1_6_map SUPPLIER_CNTPARTSUPP1_E1_6;
    SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA_map SUPPLIER_CNTPARTSUPP1_E1_6PART1_DELTA;
    SUPPLIER_CNTPARTSUPP1_E1_8_map SUPPLIER_CNTPARTSUPP1_E1_8;
    SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA_map SUPPLIER_CNTPARTSUPP1_E1_8PART1_DELTA;
    SUPPLIER_CNTPARTSUPP1_E1_10_map SUPPLIER_CNTPARTSUPP1_E1_10;
    SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA_map SUPPLIER_CNTPARTSUPP1_E1_10PART1_DELTA;
    SUPPLIER_CNTPARTSUPP1_E1_12_map SUPPLIER_CNTPARTSUPP1_E1_12;
    SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA_map SUPPLIER_CNTPARTSUPP1_E1_12PART1_DELTA;
    SUPPLIER_CNTPARTSUPP1_E1_14_map SUPPLIER_CNTPARTSUPP1_E1_14;
    SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA_map SUPPLIER_CNTPARTSUPP1_E1_14PART1_DELTA;
    SUPPLIER_CNTPARTSUPP1_E1_16_map SUPPLIER_CNTPARTSUPP1_E1_16;
    SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA_map SUPPLIER_CNTPARTSUPP1_E1_16PART1_DELTA;
    SUPPLIER_CNTPARTSUPP1_E1_18_DELTA_map SUPPLIER_CNTPARTSUPP1_E1_18_DELTA;
    SUPPLIER_CNTPARTSUPP1_E1_18_map SUPPLIER_CNTPARTSUPP1_E1_18;
    SUPPLIER_CNTPARTSUPP1_E1_20_map SUPPLIER_CNTPARTSUPP1_E1_20;
    SUPPLIER_CNTPARTSUPP1_E1_22_map SUPPLIER_CNTPARTSUPP1_E1_22;
    SUPPLIER_CNTPARTSUPP1_E1_24_map SUPPLIER_CNTPARTSUPP1_E1_24;
    SUPPLIER_CNTPARTSUPP1_E1_26_map SUPPLIER_CNTPARTSUPP1_E1_26;
    SUPPLIER_CNTPARTSUPP1_E1_28_map SUPPLIER_CNTPARTSUPP1_E1_28;
    SUPPLIER_CNTPARTSUPP1_E1_30_map SUPPLIER_CNTPARTSUPP1_E1_30;
    SUPPLIER_CNTPARTSUPP1_E1_32_map SUPPLIER_CNTPARTSUPP1_E1_32;
    DELTA_PART_map DELTA_PART;
    DELTA_SUPPLIER_map DELTA_SUPPLIER;
    DELTA_PARTSUPP_map DELTA_PARTSUPP;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg11;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg6;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg13;
    MultiHashMap<tuple5_LSSL_L,long,HashIndex<tuple5_LSSL_L,long> > agg8;
    MultiHashMap<tuple5_LSSL_L,long,HashIndex<tuple5_LSSL_L,long> > agg2;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg10;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg4;
    MultiHashMap<tuple5_LSSL_L,long,HashIndex<tuple5_LSSL_L,long> > agg12;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg7;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg1;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg14;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg9;
    /*const static*/ STRING_TYPE c1;
  
  };

}
