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
  struct DELTA_LINEITEM_entry {
    long lineitem_orderkey; long lineitem_partkey; long lineitem_suppkey; long lineitem_linenumber; DOUBLE_TYPE lineitem_quantity; DOUBLE_TYPE lineitem_extendedprice; DOUBLE_TYPE lineitem_discount; DOUBLE_TYPE lineitem_tax; STRING_TYPE lineitem_returnflag; STRING_TYPE lineitem_linestatus; date lineitem_shipdate; date lineitem_commitdate; date lineitem_receiptdate; STRING_TYPE lineitem_shipinstruct; STRING_TYPE lineitem_shipmode; STRING_TYPE lineitem_comment; long __av; 
    explicit DELTA_LINEITEM_entry() { /*lineitem_orderkey = 0L; lineitem_partkey = 0L; lineitem_suppkey = 0L; lineitem_linenumber = 0L; lineitem_quantity = 0.0; lineitem_extendedprice = 0.0; lineitem_discount = 0.0; lineitem_tax = 0.0; lineitem_returnflag = ""; lineitem_linestatus = ""; lineitem_shipdate = 00000000; lineitem_commitdate = 00000000; lineitem_receiptdate = 00000000; lineitem_shipinstruct = ""; lineitem_shipmode = ""; lineitem_comment = ""; __av = 0L; */ }
    explicit DELTA_LINEITEM_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8, const STRING_TYPE& c9, const date c10, const date c11, const date c12, const STRING_TYPE& c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const long c16) { lineitem_orderkey = c0; lineitem_partkey = c1; lineitem_suppkey = c2; lineitem_linenumber = c3; lineitem_quantity = c4; lineitem_extendedprice = c5; lineitem_discount = c6; lineitem_tax = c7; lineitem_returnflag = c8; lineitem_linestatus = c9; lineitem_shipdate = c10; lineitem_commitdate = c11; lineitem_receiptdate = c12; lineitem_shipinstruct = c13; lineitem_shipmode = c14; lineitem_comment = c15; __av = c16; }
    DELTA_LINEITEM_entry(const DELTA_LINEITEM_entry& other) : lineitem_orderkey( other.lineitem_orderkey ), lineitem_partkey( other.lineitem_partkey ), lineitem_suppkey( other.lineitem_suppkey ), lineitem_linenumber( other.lineitem_linenumber ), lineitem_quantity( other.lineitem_quantity ), lineitem_extendedprice( other.lineitem_extendedprice ), lineitem_discount( other.lineitem_discount ), lineitem_tax( other.lineitem_tax ), lineitem_returnflag( other.lineitem_returnflag ), lineitem_linestatus( other.lineitem_linestatus ), lineitem_shipdate( other.lineitem_shipdate ), lineitem_commitdate( other.lineitem_commitdate ), lineitem_receiptdate( other.lineitem_receiptdate ), lineitem_shipinstruct( other.lineitem_shipinstruct ), lineitem_shipmode( other.lineitem_shipmode ), lineitem_comment( other.lineitem_comment ), __av( other.__av ) {}
    FORCE_INLINE DELTA_LINEITEM_entry& modify(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8, const STRING_TYPE& c9, const date c10, const date c11, const date c12, const STRING_TYPE& c13, const STRING_TYPE& c14, const STRING_TYPE& c15) { lineitem_orderkey = c0; lineitem_partkey = c1; lineitem_suppkey = c2; lineitem_linenumber = c3; lineitem_quantity = c4; lineitem_extendedprice = c5; lineitem_discount = c6; lineitem_tax = c7; lineitem_returnflag = c8; lineitem_linestatus = c9; lineitem_shipdate = c10; lineitem_commitdate = c11; lineitem_receiptdate = c12; lineitem_shipinstruct = c13; lineitem_shipmode = c14; lineitem_comment = c15;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_linenumber);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_quantity);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_extendedprice);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_discount);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_tax);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_returnflag);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_linestatus);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_shipdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_commitdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_receiptdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_shipinstruct);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_shipmode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_LINEITEM_mapkey0123456789101112131415_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_LINEITEM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.lineitem_orderkey);
      hash_combine(h, e.lineitem_partkey);
      hash_combine(h, e.lineitem_suppkey);
      hash_combine(h, e.lineitem_linenumber);
      hash_combine(h, e.lineitem_quantity);
      hash_combine(h, e.lineitem_extendedprice);
      hash_combine(h, e.lineitem_discount);
      hash_combine(h, e.lineitem_tax);
      hash_combine(h, e.lineitem_returnflag);
      hash_combine(h, e.lineitem_linestatus);
      hash_combine(h, e.lineitem_shipdate);
      hash_combine(h, e.lineitem_commitdate);
      hash_combine(h, e.lineitem_receiptdate);
      hash_combine(h, e.lineitem_shipinstruct);
      hash_combine(h, e.lineitem_shipmode);
      hash_combine(h, e.lineitem_comment);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_LINEITEM_entry& x, const DELTA_LINEITEM_entry& y) {
      return x.lineitem_orderkey == y.lineitem_orderkey && x.lineitem_partkey == y.lineitem_partkey && x.lineitem_suppkey == y.lineitem_suppkey && x.lineitem_linenumber == y.lineitem_linenumber && x.lineitem_quantity == y.lineitem_quantity && x.lineitem_extendedprice == y.lineitem_extendedprice && x.lineitem_discount == y.lineitem_discount && x.lineitem_tax == y.lineitem_tax && x.lineitem_returnflag == y.lineitem_returnflag && x.lineitem_linestatus == y.lineitem_linestatus && x.lineitem_shipdate == y.lineitem_shipdate && x.lineitem_commitdate == y.lineitem_commitdate && x.lineitem_receiptdate == y.lineitem_receiptdate && x.lineitem_shipinstruct == y.lineitem_shipinstruct && x.lineitem_shipmode == y.lineitem_shipmode && x.lineitem_comment == y.lineitem_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_LINEITEM_entry,long,
    HashIndex<DELTA_LINEITEM_entry,long,DELTA_LINEITEM_mapkey0123456789101112131415_idxfn,true>
  > DELTA_LINEITEM_map;
  typedef HashIndex<DELTA_LINEITEM_entry,long,DELTA_LINEITEM_mapkey0123456789101112131415_idxfn,true> HashIndex_DELTA_LINEITEM_map_0123456789101112131415;
  
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
  
  struct COUNT_entry {
    STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; long __av; 
    explicit COUNT_entry() { /*S_NAME = ""; S_ADDRESS = ""; __av = 0L; */ }
    explicit COUNT_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { S_NAME = c0; S_ADDRESS = c1; __av = c2; }
    COUNT_entry(const COUNT_entry& other) : S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), __av( other.__av ) {}
    FORCE_INLINE COUNT_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { S_NAME = c0; S_ADDRESS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_entry& x, const COUNT_entry& y) {
      return x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS;
    }
  };
  
  typedef MultiHashMap<COUNT_entry,long,
    HashIndex<COUNT_entry,long,COUNT_mapkey01_idxfn,true>
  > COUNT_map;
  typedef HashIndex<COUNT_entry,long,COUNT_mapkey01_idxfn,true> HashIndex_COUNT_map_01;
  
  struct COUNTPART1_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; long __av; 
    explicit COUNTPART1_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; __av = 0L; */ }
    explicit COUNTPART1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; __av = c3; }
    COUNTPART1_entry(const COUNTPART1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), __av( other.__av ) {}
    FORCE_INLINE COUNTPART1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPART1_entry& x, const COUNTPART1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS;
    }
  };
  
  typedef MultiHashMap<COUNTPART1_entry,long,
    HashIndex<COUNTPART1_entry,long,COUNTPART1_mapkey012_idxfn,true>
  > COUNTPART1_map;
  typedef HashIndex<COUNTPART1_entry,long,COUNTPART1_mapkey012_idxfn,true> HashIndex_COUNTPART1_map_012;
  
  struct COUNTLINEITEM1_DOMAIN1_entry {
    STRING_TYPE N_NAME; long S_SUPPKEY; long __av; 
    explicit COUNTLINEITEM1_DOMAIN1_entry() { /*N_NAME = ""; S_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNTLINEITEM1_DOMAIN1_entry(const STRING_TYPE& c0, const long c1, const long c2) { N_NAME = c0; S_SUPPKEY = c1; __av = c2; }
    COUNTLINEITEM1_DOMAIN1_entry(const COUNTLINEITEM1_DOMAIN1_entry& other) : N_NAME( other.N_NAME ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_DOMAIN1_entry& modify(const STRING_TYPE& c0, const long c1) { N_NAME = c0; S_SUPPKEY = c1;  return *this; }
    FORCE_INLINE COUNTLINEITEM1_DOMAIN1_entry& modify0(const STRING_TYPE& c0) { N_NAME = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_DOMAIN1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.N_NAME);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_DOMAIN1_entry& x, const COUNTLINEITEM1_DOMAIN1_entry& y) {
      return x.N_NAME == y.N_NAME && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  struct COUNTLINEITEM1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_DOMAIN1_entry& x, const COUNTLINEITEM1_DOMAIN1_entry& y) {
      return x.N_NAME == y.N_NAME;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_DOMAIN1_entry,long,
    HashIndex<COUNTLINEITEM1_DOMAIN1_entry,long,COUNTLINEITEM1_DOMAIN1_mapkey01_idxfn,true>,
    HashIndex<COUNTLINEITEM1_DOMAIN1_entry,long,COUNTLINEITEM1_DOMAIN1_mapkey0_idxfn,false>
  > COUNTLINEITEM1_DOMAIN1_map;
  typedef HashIndex<COUNTLINEITEM1_DOMAIN1_entry,long,COUNTLINEITEM1_DOMAIN1_mapkey01_idxfn,true> HashIndex_COUNTLINEITEM1_DOMAIN1_map_01;
  typedef HashIndex<COUNTLINEITEM1_DOMAIN1_entry,long,COUNTLINEITEM1_DOMAIN1_mapkey0_idxfn,false> HashIndex_COUNTLINEITEM1_DOMAIN1_map_0;
  
  struct COUNTLINEITEM1_E1_1_L1_3_DELTA_entry {
    long PS_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit COUNTLINEITEM1_E1_1_L1_3_DELTA_entry() { /*PS_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit COUNTLINEITEM1_E1_1_L1_3_DELTA_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { PS_PARTKEY = c0; S_SUPPKEY = c1; __av = c2; }
    COUNTLINEITEM1_E1_1_L1_3_DELTA_entry(const COUNTLINEITEM1_E1_1_L1_3_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_E1_1_L1_3_DELTA_entry& modify(const long c0, const long c1) { PS_PARTKEY = c0; S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_E1_1_L1_3_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_E1_1_L1_3_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_E1_1_L1_3_DELTA_entry& x, const COUNTLINEITEM1_E1_1_L1_3_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_E1_1_L1_3_DELTA_entry,DOUBLE_TYPE,
    HashIndex<COUNTLINEITEM1_E1_1_L1_3_DELTA_entry,DOUBLE_TYPE,COUNTLINEITEM1_E1_1_L1_3_DELTA_mapkey01_idxfn,true>
  > COUNTLINEITEM1_E1_1_L1_3_DELTA_map;
  typedef HashIndex<COUNTLINEITEM1_E1_1_L1_3_DELTA_entry,DOUBLE_TYPE,COUNTLINEITEM1_E1_1_L1_3_DELTA_mapkey01_idxfn,true> HashIndex_COUNTLINEITEM1_E1_1_L1_3_DELTA_map_01;
  
  struct COUNTPARTSUPP1_DOMAIN1_entry {
    STRING_TYPE N_NAME; long S_SUPPKEY; long __av; 
    explicit COUNTPARTSUPP1_DOMAIN1_entry() { /*N_NAME = ""; S_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNTPARTSUPP1_DOMAIN1_entry(const STRING_TYPE& c0, const long c1, const long c2) { N_NAME = c0; S_SUPPKEY = c1; __av = c2; }
    COUNTPARTSUPP1_DOMAIN1_entry(const COUNTPARTSUPP1_DOMAIN1_entry& other) : N_NAME( other.N_NAME ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP1_DOMAIN1_entry& modify(const STRING_TYPE& c0, const long c1) { N_NAME = c0; S_SUPPKEY = c1;  return *this; }
    FORCE_INLINE COUNTPARTSUPP1_DOMAIN1_entry& modify0(const STRING_TYPE& c0) { N_NAME = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP1_DOMAIN1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.N_NAME);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_DOMAIN1_entry& x, const COUNTPARTSUPP1_DOMAIN1_entry& y) {
      return x.N_NAME == y.N_NAME && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  struct COUNTPARTSUPP1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_DOMAIN1_entry& x, const COUNTPARTSUPP1_DOMAIN1_entry& y) {
      return x.N_NAME == y.N_NAME;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP1_DOMAIN1_entry,long,
    HashIndex<COUNTPARTSUPP1_DOMAIN1_entry,long,COUNTPARTSUPP1_DOMAIN1_mapkey01_idxfn,true>,
    HashIndex<COUNTPARTSUPP1_DOMAIN1_entry,long,COUNTPARTSUPP1_DOMAIN1_mapkey0_idxfn,false>
  > COUNTPARTSUPP1_DOMAIN1_map;
  typedef HashIndex<COUNTPARTSUPP1_DOMAIN1_entry,long,COUNTPARTSUPP1_DOMAIN1_mapkey01_idxfn,true> HashIndex_COUNTPARTSUPP1_DOMAIN1_map_01;
  typedef HashIndex<COUNTPARTSUPP1_DOMAIN1_entry,long,COUNTPARTSUPP1_DOMAIN1_mapkey0_idxfn,false> HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0;
  
  struct COUNTPARTSUPP1_P_2_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE N_NAME; long __av; 
    explicit COUNTPARTSUPP1_P_2_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; N_NAME = ""; __av = 0L; */ }
    explicit COUNTPARTSUPP1_P_2_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; N_NAME = c3; __av = c4; }
    COUNTPARTSUPP1_P_2_entry(const COUNTPARTSUPP1_P_2_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP1_P_2_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; N_NAME = c3;  return *this; }
    FORCE_INLINE COUNTPARTSUPP1_P_2_entry& modify03(const long c0, const STRING_TYPE& c3) { S_SUPPKEY = c0; N_NAME = c3;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP1_P_2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_P_2_entry& x, const COUNTPARTSUPP1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.N_NAME == y.N_NAME;
    }
  };
  
  struct COUNTPARTSUPP1_P_2_mapkey03_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_P_2_entry& x, const COUNTPARTSUPP1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP1_P_2_entry,long,
    HashIndex<COUNTPARTSUPP1_P_2_entry,long,COUNTPARTSUPP1_P_2_mapkey0123_idxfn,true>,
    HashIndex<COUNTPARTSUPP1_P_2_entry,long,COUNTPARTSUPP1_P_2_mapkey03_idxfn,false>
  > COUNTPARTSUPP1_P_2_map;
  typedef HashIndex<COUNTPARTSUPP1_P_2_entry,long,COUNTPARTSUPP1_P_2_mapkey0123_idxfn,true> HashIndex_COUNTPARTSUPP1_P_2_map_0123;
  typedef HashIndex<COUNTPARTSUPP1_P_2_entry,long,COUNTPARTSUPP1_P_2_mapkey03_idxfn,false> HashIndex_COUNTPARTSUPP1_P_2_map_03;
  
  struct COUNTPARTSUPP1_P_2SUPPLIER1_entry {
    long S_NATIONKEY; STRING_TYPE N_NAME; long __av; 
    explicit COUNTPARTSUPP1_P_2SUPPLIER1_entry() { /*S_NATIONKEY = 0L; N_NAME = ""; __av = 0L; */ }
    explicit COUNTPARTSUPP1_P_2SUPPLIER1_entry(const long c0, const STRING_TYPE& c1, const long c2) { S_NATIONKEY = c0; N_NAME = c1; __av = c2; }
    COUNTPARTSUPP1_P_2SUPPLIER1_entry(const COUNTPARTSUPP1_P_2SUPPLIER1_entry& other) : S_NATIONKEY( other.S_NATIONKEY ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP1_P_2SUPPLIER1_entry& modify(const long c0, const STRING_TYPE& c1) { S_NATIONKEY = c0; N_NAME = c1;  return *this; }
    FORCE_INLINE COUNTPARTSUPP1_P_2SUPPLIER1_entry& modify0(const long c0) { S_NATIONKEY = c0;  return *this; }
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
  struct COUNTPARTSUPP1_P_2SUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_P_2SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_P_2SUPPLIER1_entry& x, const COUNTPARTSUPP1_P_2SUPPLIER1_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  struct COUNTPARTSUPP1_P_2SUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_P_2SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_P_2SUPPLIER1_entry& x, const COUNTPARTSUPP1_P_2SUPPLIER1_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP1_P_2SUPPLIER1_entry,long,
    HashIndex<COUNTPARTSUPP1_P_2SUPPLIER1_entry,long,COUNTPARTSUPP1_P_2SUPPLIER1_mapkey01_idxfn,true>,
    HashIndex<COUNTPARTSUPP1_P_2SUPPLIER1_entry,long,COUNTPARTSUPP1_P_2SUPPLIER1_mapkey0_idxfn,false>
  > COUNTPARTSUPP1_P_2SUPPLIER1_map;
  typedef HashIndex<COUNTPARTSUPP1_P_2SUPPLIER1_entry,long,COUNTPARTSUPP1_P_2SUPPLIER1_mapkey01_idxfn,true> HashIndex_COUNTPARTSUPP1_P_2SUPPLIER1_map_01;
  typedef HashIndex<COUNTPARTSUPP1_P_2SUPPLIER1_entry,long,COUNTPARTSUPP1_P_2SUPPLIER1_mapkey0_idxfn,false> HashIndex_COUNTPARTSUPP1_P_2SUPPLIER1_map_0;
  
  struct COUNTPARTSUPP1_E1_2_DELTA_entry {
    long PS_PARTKEY; long S_SUPPKEY; long PS_AVAILQTY; long __av; 
    explicit COUNTPARTSUPP1_E1_2_DELTA_entry() { /*PS_PARTKEY = 0L; S_SUPPKEY = 0L; PS_AVAILQTY = 0L; __av = 0L; */ }
    explicit COUNTPARTSUPP1_E1_2_DELTA_entry(const long c0, const long c1, const long c2, const long c3) { PS_PARTKEY = c0; S_SUPPKEY = c1; PS_AVAILQTY = c2; __av = c3; }
    COUNTPARTSUPP1_E1_2_DELTA_entry(const COUNTPARTSUPP1_E1_2_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), PS_AVAILQTY( other.PS_AVAILQTY ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP1_E1_2_DELTA_entry& modify(const long c0, const long c1, const long c2) { PS_PARTKEY = c0; S_SUPPKEY = c1; PS_AVAILQTY = c2;  return *this; }
    FORCE_INLINE COUNTPARTSUPP1_E1_2_DELTA_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_AVAILQTY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP1_E1_2_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_E1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.PS_AVAILQTY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_E1_2_DELTA_entry& x, const COUNTPARTSUPP1_E1_2_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.PS_AVAILQTY == y.PS_AVAILQTY;
    }
  };
  
  struct COUNTPARTSUPP1_E1_2_DELTA_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_E1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_E1_2_DELTA_entry& x, const COUNTPARTSUPP1_E1_2_DELTA_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP1_E1_2_DELTA_entry,long,
    HashIndex<COUNTPARTSUPP1_E1_2_DELTA_entry,long,COUNTPARTSUPP1_E1_2_DELTA_mapkey012_idxfn,true>,
    HashIndex<COUNTPARTSUPP1_E1_2_DELTA_entry,long,COUNTPARTSUPP1_E1_2_DELTA_mapkey1_idxfn,false>
  > COUNTPARTSUPP1_E1_2_DELTA_map;
  typedef HashIndex<COUNTPARTSUPP1_E1_2_DELTA_entry,long,COUNTPARTSUPP1_E1_2_DELTA_mapkey012_idxfn,true> HashIndex_COUNTPARTSUPP1_E1_2_DELTA_map_012;
  typedef HashIndex<COUNTPARTSUPP1_E1_2_DELTA_entry,long,COUNTPARTSUPP1_E1_2_DELTA_mapkey1_idxfn,false> HashIndex_COUNTPARTSUPP1_E1_2_DELTA_map_1;
  
  struct COUNTSUPPLIER1_DELTA_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; long S_NATIONKEY; long __av; 
    explicit COUNTSUPPLIER1_DELTA_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; S_NATIONKEY = 0L; __av = 0L; */ }
    explicit COUNTSUPPLIER1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_NATIONKEY = c3; __av = c4; }
    COUNTSUPPLIER1_DELTA_entry(const COUNTSUPPLIER1_DELTA_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_NATIONKEY = c3;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1_DELTA_entry& x, const COUNTSUPPLIER1_DELTA_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1_DELTA_entry,long,
    HashIndex<COUNTSUPPLIER1_DELTA_entry,long,COUNTSUPPLIER1_DELTA_mapkey0123_idxfn,true>
  > COUNTSUPPLIER1_DELTA_map;
  typedef HashIndex<COUNTSUPPLIER1_DELTA_entry,long,COUNTSUPPLIER1_DELTA_mapkey0123_idxfn,true> HashIndex_COUNTSUPPLIER1_DELTA_map_0123;
  
  struct COUNTSUPPLIER1_entry {
    long S_NATIONKEY; long __av; 
    explicit COUNTSUPPLIER1_entry() { /*S_NATIONKEY = 0L; __av = 0L; */ }
    explicit COUNTSUPPLIER1_entry(const long c0, const long c1) { S_NATIONKEY = c0; __av = c1; }
    COUNTSUPPLIER1_entry(const COUNTSUPPLIER1_entry& other) : S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1_entry& modify(const long c0) { S_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1_entry& x, const COUNTSUPPLIER1_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1_entry,long,
    HashIndex<COUNTSUPPLIER1_entry,long,COUNTSUPPLIER1_mapkey0_idxfn,true>
  > COUNTSUPPLIER1_map;
  typedef HashIndex<COUNTSUPPLIER1_entry,long,COUNTSUPPLIER1_mapkey0_idxfn,true> HashIndex_COUNTSUPPLIER1_map_0;
  
  struct COUNTSUPPLIER1_E1_1_entry {
    long PS_PARTKEY; long S_SUPPKEY; long PS_AVAILQTY; long __av; 
    explicit COUNTSUPPLIER1_E1_1_entry() { /*PS_PARTKEY = 0L; S_SUPPKEY = 0L; PS_AVAILQTY = 0L; __av = 0L; */ }
    explicit COUNTSUPPLIER1_E1_1_entry(const long c0, const long c1, const long c2, const long c3) { PS_PARTKEY = c0; S_SUPPKEY = c1; PS_AVAILQTY = c2; __av = c3; }
    COUNTSUPPLIER1_E1_1_entry(const COUNTSUPPLIER1_E1_1_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), PS_AVAILQTY( other.PS_AVAILQTY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1_E1_1_entry& modify(const long c0, const long c1, const long c2) { PS_PARTKEY = c0; S_SUPPKEY = c1; PS_AVAILQTY = c2;  return *this; }
    FORCE_INLINE COUNTSUPPLIER1_E1_1_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_AVAILQTY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1_E1_1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.PS_AVAILQTY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1_E1_1_entry& x, const COUNTSUPPLIER1_E1_1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.PS_AVAILQTY == y.PS_AVAILQTY;
    }
  };
  
  struct COUNTSUPPLIER1_E1_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1_E1_1_entry& x, const COUNTSUPPLIER1_E1_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1_E1_1_entry,long,
    HashIndex<COUNTSUPPLIER1_E1_1_entry,long,COUNTSUPPLIER1_E1_1_mapkey012_idxfn,true>,
    HashIndex<COUNTSUPPLIER1_E1_1_entry,long,COUNTSUPPLIER1_E1_1_mapkey1_idxfn,false>
  > COUNTSUPPLIER1_E1_1_map;
  typedef HashIndex<COUNTSUPPLIER1_E1_1_entry,long,COUNTSUPPLIER1_E1_1_mapkey012_idxfn,true> HashIndex_COUNTSUPPLIER1_E1_1_map_012;
  typedef HashIndex<COUNTSUPPLIER1_E1_1_entry,long,COUNTSUPPLIER1_E1_1_mapkey1_idxfn,false> HashIndex_COUNTSUPPLIER1_E1_1_map_1;
  
  struct COUNTSUPPLIER1_E1_1_L1_1_entry {
    long PS_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit COUNTSUPPLIER1_E1_1_L1_1_entry() { /*PS_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit COUNTSUPPLIER1_E1_1_L1_1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { PS_PARTKEY = c0; S_SUPPKEY = c1; __av = c2; }
    COUNTSUPPLIER1_E1_1_L1_1_entry(const COUNTSUPPLIER1_E1_1_L1_1_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1_E1_1_L1_1_entry& modify(const long c0, const long c1) { PS_PARTKEY = c0; S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1_E1_1_L1_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1_E1_1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1_E1_1_L1_1_entry& x, const COUNTSUPPLIER1_E1_1_L1_1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1_E1_1_L1_1_entry,DOUBLE_TYPE,
    HashIndex<COUNTSUPPLIER1_E1_1_L1_1_entry,DOUBLE_TYPE,COUNTSUPPLIER1_E1_1_L1_1_mapkey01_idxfn,true>
  > COUNTSUPPLIER1_E1_1_L1_1_map;
  typedef HashIndex<COUNTSUPPLIER1_E1_1_L1_1_entry,DOUBLE_TYPE,COUNTSUPPLIER1_E1_1_L1_1_mapkey01_idxfn,true> HashIndex_COUNTSUPPLIER1_E1_1_L1_1_map_01;
  
  struct COUNTSUPPLIER1_E1_1_E2_1_entry {
    long PS_PARTKEY; long __av; 
    explicit COUNTSUPPLIER1_E1_1_E2_1_entry() { /*PS_PARTKEY = 0L; __av = 0L; */ }
    explicit COUNTSUPPLIER1_E1_1_E2_1_entry(const long c0, const long c1) { PS_PARTKEY = c0; __av = c1; }
    COUNTSUPPLIER1_E1_1_E2_1_entry(const COUNTSUPPLIER1_E1_1_E2_1_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1_E1_1_E2_1_entry& modify(const long c0) { PS_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1_E1_1_E2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1_E1_1_E2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1_E1_1_E2_1_entry& x, const COUNTSUPPLIER1_E1_1_E2_1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1_E1_1_E2_1_entry,long,
    HashIndex<COUNTSUPPLIER1_E1_1_E2_1_entry,long,COUNTSUPPLIER1_E1_1_E2_1_mapkey0_idxfn,true>
  > COUNTSUPPLIER1_E1_1_E2_1_map;
  typedef HashIndex<COUNTSUPPLIER1_E1_1_E2_1_entry,long,COUNTSUPPLIER1_E1_1_E2_1_mapkey0_idxfn,true> HashIndex_COUNTSUPPLIER1_E1_1_E2_1_map_0;
  
  struct COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry {
    long PS_PARTKEY; long __av; 
    explicit COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry() { /*PS_PARTKEY = 0L; __av = 0L; */ }
    explicit COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry(const long c0, const long c1) { PS_PARTKEY = c0; __av = c1; }
    COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry(const COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry& modify(const long c0) { PS_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry& x, const COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry,long,
    HashIndex<COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry,long,COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_mapkey0_idxfn,true>
  > COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_map;
  typedef HashIndex<COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry,long,COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_mapkey0_idxfn,true> HashIndex_COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_map_0;
  
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
    data_t(): tlq_t(), agg6(16U), agg1(16U) {
      c2 = Udate(STRING_TYPE("1995-1-1"));
      c1 = Udate(STRING_TYPE("1994-1-1"));
      c3 = STRING_TYPE("CANADA");
      /* regex_t init */
      if(regcomp(&preg1, "^forest.*$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^forest.*$/" << endl;
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
    
    
    
    /* Trigger functions for stream relations */
    void on_batch_update_LINEITEM(TPCHLineitemBatch& DELTA_LINEITEM) {
      { 
        if (tS > 0) { tS += DELTA_LINEITEM.size; return; }         
        tLastN += DELTA_LINEITEM.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_LINEITEM.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_LINEITEM.size;


        COUNTLINEITEM1_E1_1_L1_3_DELTA.clear();
        COUNTLINEITEM1_DOMAIN1.clear();
        STRING_TYPE l1 = c3;
        agg1.clear();        
        {
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                long l_orderkey = DELTA_LINEITEM.orderkey[i];
                long ps_partkey = DELTA_LINEITEM.partkey[i];
                long s_suppkey = DELTA_LINEITEM.suppkey[i];
                long l_linenumber = DELTA_LINEITEM.linenumber[i];
                DOUBLE_TYPE l_quantity = DELTA_LINEITEM.quantity[i];
                DOUBLE_TYPE l_extendedprice = DELTA_LINEITEM.extendedprice[i];
                DOUBLE_TYPE l_discount = DELTA_LINEITEM.discount[i];
                DOUBLE_TYPE l_tax = DELTA_LINEITEM.tax[i];
                STRING_TYPE l_returnflag = DELTA_LINEITEM.returnflag[i];
                STRING_TYPE l_linestatus = DELTA_LINEITEM.linestatus[i];
                date l_shipdate = DELTA_LINEITEM.shipdate[i];
                date l_commitdate = DELTA_LINEITEM.commitdate[i];
                date l_receiptdate = DELTA_LINEITEM.receiptdate[i];
                STRING_TYPE l_shipinstruct = DELTA_LINEITEM.shipinstruct[i];
                STRING_TYPE l_shipmode = DELTA_LINEITEM.shipmode[i];
                STRING_TYPE l_comment = DELTA_LINEITEM.comment[i];
                long v1 = 1L;
                (/*if */(l_shipdate >= c1 && c2 > l_shipdate) ? COUNTLINEITEM1_E1_1_L1_3_DELTA.addOrDelOnZero(se1.modify(ps_partkey,s_suppkey),(v1 * l_quantity)) : (void)0);
                long v2 = 1L;
                (/*if */(l_shipdate >= c1 && c2 > l_shipdate) ? agg1.addOrDelOnZero(st1.modify(s_suppkey,(v2 != 0 ? 1L : 0L)), (v2 != 0 ? 1L : 0L)) : (void)0);                
          }
        }
        
        {  // temp foreach
          const HashIndex<tuple2_L_L, long>* i3 = static_cast<HashIndex<tuple2_L_L, long>*>(agg1.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n3; 
          tuple2_L_L* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
              long s_suppkey = e3->_1;  
              long v3 = e3->__av; 
            COUNTLINEITEM1_DOMAIN1.addOrDelOnZero(se2.modify(l1,s_suppkey),v3);      
              n3 = n3->nxt;
            }
          }
        }STRING_TYPE l2 = c3;
        { //slice 
          const HashIndex_COUNTLINEITEM1_DOMAIN1_map_0* i4 = static_cast<HashIndex_COUNTLINEITEM1_DOMAIN1_map_0*>(COUNTLINEITEM1_DOMAIN1.index[1]);
          const HASH_RES_t h3 = COUNTLINEITEM1_DOMAIN1_mapkey0_idxfn::hash(se9.modify0(l2));
          HashIndex_COUNTLINEITEM1_DOMAIN1_map_0::IdxNode* n4 = static_cast<HashIndex_COUNTLINEITEM1_DOMAIN1_map_0::IdxNode*>(i4->slice(se9, h3));
          COUNTLINEITEM1_DOMAIN1_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long s_suppkey = e4->S_SUPPKEY;
              long v4 = e4->__av;
              { //slice 
                const HashIndex_COUNTPARTSUPP1_P_2_map_03* i5 = static_cast<HashIndex_COUNTPARTSUPP1_P_2_map_03*>(COUNTPARTSUPP1_P_2.index[1]);
                const HASH_RES_t h2 = COUNTPARTSUPP1_P_2_mapkey03_idxfn::hash(se8.modify03(s_suppkey, l2));
                HashIndex_COUNTPARTSUPP1_P_2_map_03::IdxNode* n5 = static_cast<HashIndex_COUNTPARTSUPP1_P_2_map_03::IdxNode*>(i5->slice(se8, h2));
                COUNTPARTSUPP1_P_2_entry* e5;
               
                if (n5 && (e5 = n5->obj)) {
                  do {                
                    STRING_TYPE s_name = e5->S_NAME;
                    STRING_TYPE s_address = e5->S_ADDRESS;
                    long v5 = e5->__av;
                    long agg2 = 0L;
                    { //slice 
                      const HashIndex_COUNTSUPPLIER1_E1_1_map_1* i6 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_map_1*>(COUNTSUPPLIER1_E1_1.index[1]);
                      const HASH_RES_t h1 = COUNTSUPPLIER1_E1_1_mapkey1_idxfn::hash(se7.modify1(s_suppkey));
                      HashIndex_COUNTSUPPLIER1_E1_1_map_1::IdxNode* n6 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_map_1::IdxNode*>(i6->slice(se7, h1));
                      COUNTSUPPLIER1_E1_1_entry* e6;
                     
                      if (n6 && (e6 = n6->obj)) {
                        do {                
                          long ps_partkey = e6->PS_PARTKEY;
                          long ps_availqty = e6->PS_AVAILQTY;
                          long v6 = e6->__av;
                          DOUBLE_TYPE l3 = ((COUNTSUPPLIER1_E1_1_L1_1.getValueOrDefault(se4.modify(ps_partkey,s_suppkey)) + COUNTLINEITEM1_E1_1_L1_3_DELTA.getValueOrDefault(se5.modify(ps_partkey,s_suppkey))) * 0.5);
                          (/*if */(ps_availqty > l3) ? agg2 += (v6 * (COUNTSUPPLIER1_E1_1_E2_1.getValueOrDefault(se6.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                          n6 = n6->nxt;
                        } while (n6 && (e6 = n6->obj) && h1 == n6->hash &&  COUNTSUPPLIER1_E1_1_mapkey1_idxfn::equals(se7, *e6)); 
                      }
                    }COUNT.addOrDelOnZero(se3.modify(s_name,s_address),((v4 != 0 ? 1L : 0L) * (v5 * (agg2 != 0 ? 1L : 0L))));
                    n5 = n5->nxt;
                  } while (n5 && (e5 = n5->obj) && h2 == n5->hash &&  COUNTPARTSUPP1_P_2_mapkey03_idxfn::equals(se8, *e5)); 
                }
              }
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h3 == n4->hash &&  COUNTLINEITEM1_DOMAIN1_mapkey0_idxfn::equals(se9, *e4)); 
          }
        }STRING_TYPE l4 = c3;
        { //slice 
          const HashIndex_COUNTLINEITEM1_DOMAIN1_map_0* i7 = static_cast<HashIndex_COUNTLINEITEM1_DOMAIN1_map_0*>(COUNTLINEITEM1_DOMAIN1.index[1]);
          const HASH_RES_t h6 = COUNTLINEITEM1_DOMAIN1_mapkey0_idxfn::hash(se14.modify0(l4));
          HashIndex_COUNTLINEITEM1_DOMAIN1_map_0::IdxNode* n7 = static_cast<HashIndex_COUNTLINEITEM1_DOMAIN1_map_0::IdxNode*>(i7->slice(se14, h6));
          COUNTLINEITEM1_DOMAIN1_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              long s_suppkey = e7->S_SUPPKEY;
              long v7 = e7->__av;
              { //slice 
                const HashIndex_COUNTPARTSUPP1_P_2_map_03* i8 = static_cast<HashIndex_COUNTPARTSUPP1_P_2_map_03*>(COUNTPARTSUPP1_P_2.index[1]);
                const HASH_RES_t h5 = COUNTPARTSUPP1_P_2_mapkey03_idxfn::hash(se13.modify03(s_suppkey, l4));
                HashIndex_COUNTPARTSUPP1_P_2_map_03::IdxNode* n8 = static_cast<HashIndex_COUNTPARTSUPP1_P_2_map_03::IdxNode*>(i8->slice(se13, h5));
                COUNTPARTSUPP1_P_2_entry* e8;
               
                if (n8 && (e8 = n8->obj)) {
                  do {                
                    STRING_TYPE s_name = e8->S_NAME;
                    STRING_TYPE s_address = e8->S_ADDRESS;
                    long v8 = e8->__av;
                    long agg3 = 0L;
                    { //slice 
                      const HashIndex_COUNTSUPPLIER1_E1_1_map_1* i9 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_map_1*>(COUNTSUPPLIER1_E1_1.index[1]);
                      const HASH_RES_t h4 = COUNTSUPPLIER1_E1_1_mapkey1_idxfn::hash(se12.modify1(s_suppkey));
                      HashIndex_COUNTSUPPLIER1_E1_1_map_1::IdxNode* n9 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_map_1::IdxNode*>(i9->slice(se12, h4));
                      COUNTSUPPLIER1_E1_1_entry* e9;
                     
                      if (n9 && (e9 = n9->obj)) {
                        do {                
                          long ps_partkey = e9->PS_PARTKEY;
                          long ps_availqty = e9->PS_AVAILQTY;
                          long v9 = e9->__av;
                          DOUBLE_TYPE l5 = (COUNTSUPPLIER1_E1_1_L1_1.getValueOrDefault(se10.modify(ps_partkey,s_suppkey)) * 0.5);
                          (/*if */(ps_availqty > l5) ? agg3 += (v9 * (COUNTSUPPLIER1_E1_1_E2_1.getValueOrDefault(se11.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                          n9 = n9->nxt;
                        } while (n9 && (e9 = n9->obj) && h4 == n9->hash &&  COUNTSUPPLIER1_E1_1_mapkey1_idxfn::equals(se12, *e9)); 
                      }
                    }COUNT.addOrDelOnZero(se3.modify(s_name,s_address),(((v7 != 0 ? 1L : 0L) * (v8 * (agg3 != 0 ? 1L : 0L))) * -1L));
                    n8 = n8->nxt;
                  } while (n8 && (e8 = n8->obj) && h5 == n8->hash &&  COUNTPARTSUPP1_P_2_mapkey03_idxfn::equals(se13, *e8)); 
                }
              }
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h6 == n7->hash &&  COUNTLINEITEM1_DOMAIN1_mapkey0_idxfn::equals(se14, *e7)); 
          }
        }{  // foreach
          const HashIndex_COUNTLINEITEM1_E1_1_L1_3_DELTA_map_01* i10 = static_cast<HashIndex_COUNTLINEITEM1_E1_1_L1_3_DELTA_map_01*>(COUNTLINEITEM1_E1_1_L1_3_DELTA.index[0]);
          HashIndex_COUNTLINEITEM1_E1_1_L1_3_DELTA_map_01::IdxNode* n10; 
          COUNTLINEITEM1_E1_1_L1_3_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long ps_partkey = e10->PS_PARTKEY;
                long s_suppkey = e10->S_SUPPKEY;
                DOUBLE_TYPE v10 = e10->__av;
                COUNTSUPPLIER1_E1_1_L1_1.addOrDelOnZero(se15.modify(ps_partkey,s_suppkey),v10);
              n10 = n10->nxt;
            }
          }
        }
      }
    }
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


        COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA.clear();
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
                long v11 = 1L;
                (/*if */(0L != Upreg_match(preg1,p_name)) ? COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA.addOrDelOnZero(se16.modify(ps_partkey),v11) : (void)0);            
          }
        }
        {  // foreach
          const HashIndex_COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_map_0* i12 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_map_0*>(COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA.index[0]);
          HashIndex_COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_map_0::IdxNode* n12; 
          COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long ps_partkey = e12->PS_PARTKEY;
                long v12 = e12->__av;
                COUNTSUPPLIER1_E1_1_E2_1.addOrDelOnZero(se17.modify(ps_partkey),v12);
              n12 = n12->nxt;
            }
          }
        }COUNT.clear();
        {  // foreach
          const HashIndex_COUNTPART1_map_012* i13 = static_cast<HashIndex_COUNTPART1_map_012*>(COUNTPART1.index[0]);
          HashIndex_COUNTPART1_map_012::IdxNode* n13; 
          COUNTPART1_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long s_suppkey = e13->S_SUPPKEY;
                STRING_TYPE s_name = e13->S_NAME;
                STRING_TYPE s_address = e13->S_ADDRESS;
                long v13 = e13->__av;
                long agg4 = 0L;
                { //slice 
                  const HashIndex_COUNTSUPPLIER1_E1_1_map_1* i14 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_map_1*>(COUNTSUPPLIER1_E1_1.index[1]);
                  const HASH_RES_t h7 = COUNTSUPPLIER1_E1_1_mapkey1_idxfn::hash(se21.modify1(s_suppkey));
                  HashIndex_COUNTSUPPLIER1_E1_1_map_1::IdxNode* n14 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_map_1::IdxNode*>(i14->slice(se21, h7));
                  COUNTSUPPLIER1_E1_1_entry* e14;
                 
                  if (n14 && (e14 = n14->obj)) {
                    do {                
                      long ps_partkey = e14->PS_PARTKEY;
                      long ps_availqty = e14->PS_AVAILQTY;
                      long v14 = e14->__av;
                      DOUBLE_TYPE l6 = (COUNTSUPPLIER1_E1_1_L1_1.getValueOrDefault(se19.modify(ps_partkey,s_suppkey)) * 0.5);
                      (/*if */(ps_availqty > l6) ? agg4 += (v14 * (COUNTSUPPLIER1_E1_1_E2_1.getValueOrDefault(se20.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                      n14 = n14->nxt;
                    } while (n14 && (e14 = n14->obj) && h7 == n14->hash &&  COUNTSUPPLIER1_E1_1_mapkey1_idxfn::equals(se21, *e14)); 
                  }
                }COUNT.addOrDelOnZero(se18.modify(s_name,s_address),(v13 * (agg4 != 0 ? 1L : 0L)));
              n13 = n13->nxt;
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


        COUNTSUPPLIER1_DELTA.clear();
        { 
          for (size_t i = 0; i < DELTA_SUPPLIER.size; i++) 
          {
                long s_suppkey = DELTA_SUPPLIER.suppkey[i];
                STRING_TYPE s_name = DELTA_SUPPLIER.name[i];
                STRING_TYPE s_address = DELTA_SUPPLIER.address[i];
                long s_nationkey = DELTA_SUPPLIER.nationkey[i];
                STRING_TYPE s_phone = DELTA_SUPPLIER.phone[i];
                DOUBLE_TYPE s_acctbal = DELTA_SUPPLIER.acctbal[i];
                STRING_TYPE s_comment = DELTA_SUPPLIER.comment[i];
                long v15 = 1L;
                COUNTSUPPLIER1_DELTA.addOrDelOnZero(se22.modify(s_suppkey,s_name,s_address,s_nationkey),v15);            
          }
        }
        {  // foreach
          const HashIndex_COUNTSUPPLIER1_DELTA_map_0123* i16 = static_cast<HashIndex_COUNTSUPPLIER1_DELTA_map_0123*>(COUNTSUPPLIER1_DELTA.index[0]);
          HashIndex_COUNTSUPPLIER1_DELTA_map_0123::IdxNode* n16; 
          COUNTSUPPLIER1_DELTA_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long s_suppkey = e16->S_SUPPKEY;
                STRING_TYPE s_name = e16->S_NAME;
                STRING_TYPE s_address = e16->S_ADDRESS;
                long s_nationkey = e16->S_NATIONKEY;
                long v16 = e16->__av;
                long agg5 = 0L;
                { //slice 
                  const HashIndex_COUNTSUPPLIER1_E1_1_map_1* i17 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_map_1*>(COUNTSUPPLIER1_E1_1.index[1]);
                  const HASH_RES_t h8 = COUNTSUPPLIER1_E1_1_mapkey1_idxfn::hash(se27.modify1(s_suppkey));
                  HashIndex_COUNTSUPPLIER1_E1_1_map_1::IdxNode* n17 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_map_1::IdxNode*>(i17->slice(se27, h8));
                  COUNTSUPPLIER1_E1_1_entry* e17;
                 
                  if (n17 && (e17 = n17->obj)) {
                    do {                
                      long ps_partkey = e17->PS_PARTKEY;
                      long ps_availqty = e17->PS_AVAILQTY;
                      long v17 = e17->__av;
                      DOUBLE_TYPE l7 = (COUNTSUPPLIER1_E1_1_L1_1.getValueOrDefault(se25.modify(ps_partkey,s_suppkey)) * 0.5);
                      (/*if */(ps_availqty > l7) ? agg5 += (v17 * (COUNTSUPPLIER1_E1_1_E2_1.getValueOrDefault(se26.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                      n17 = n17->nxt;
                    } while (n17 && (e17 = n17->obj) && h8 == n17->hash &&  COUNTSUPPLIER1_E1_1_mapkey1_idxfn::equals(se27, *e17)); 
                  }
                }COUNT.addOrDelOnZero(se23.modify(s_name,s_address),(v16 * (COUNTSUPPLIER1.getValueOrDefault(se24.modify(s_nationkey)) * (agg5 != 0 ? 1L : 0L))));
              n16 = n16->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSUPPLIER1_DELTA_map_0123* i18 = static_cast<HashIndex_COUNTSUPPLIER1_DELTA_map_0123*>(COUNTSUPPLIER1_DELTA.index[0]);
          HashIndex_COUNTSUPPLIER1_DELTA_map_0123::IdxNode* n18; 
          COUNTSUPPLIER1_DELTA_entry* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
                long s_suppkey = e18->S_SUPPKEY;
                STRING_TYPE s_name = e18->S_NAME;
                STRING_TYPE s_address = e18->S_ADDRESS;
                long s_nationkey = e18->S_NATIONKEY;
                long v18 = e18->__av;
                COUNTPART1.addOrDelOnZero(se28.modify(s_suppkey,s_name,s_address),(v18 * COUNTSUPPLIER1.getValueOrDefault(se29.modify(s_nationkey))));
              n18 = n18->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSUPPLIER1_DELTA_map_0123* i19 = static_cast<HashIndex_COUNTSUPPLIER1_DELTA_map_0123*>(COUNTSUPPLIER1_DELTA.index[0]);
          HashIndex_COUNTSUPPLIER1_DELTA_map_0123::IdxNode* n19; 
          COUNTSUPPLIER1_DELTA_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long s_suppkey = e19->S_SUPPKEY;
                STRING_TYPE s_name = e19->S_NAME;
                STRING_TYPE s_address = e19->S_ADDRESS;
                long s_nationkey = e19->S_NATIONKEY;
                long v19 = e19->__av;
                { //slice 
                  const HashIndex_COUNTPARTSUPP1_P_2SUPPLIER1_map_0* i20 = static_cast<HashIndex_COUNTPARTSUPP1_P_2SUPPLIER1_map_0*>(COUNTPARTSUPP1_P_2SUPPLIER1.index[1]);
                  const HASH_RES_t h9 = COUNTPARTSUPP1_P_2SUPPLIER1_mapkey0_idxfn::hash(se31.modify0(s_nationkey));
                  HashIndex_COUNTPARTSUPP1_P_2SUPPLIER1_map_0::IdxNode* n20 = static_cast<HashIndex_COUNTPARTSUPP1_P_2SUPPLIER1_map_0::IdxNode*>(i20->slice(se31, h9));
                  COUNTPARTSUPP1_P_2SUPPLIER1_entry* e20;
                 
                  if (n20 && (e20 = n20->obj)) {
                    do {                
                      STRING_TYPE n_name = e20->N_NAME;
                      long v20 = e20->__av;
                      COUNTPARTSUPP1_P_2.addOrDelOnZero(se30.modify(s_suppkey,s_name,s_address,n_name),(v19 * v20));
                      n20 = n20->nxt;
                    } while (n20 && (e20 = n20->obj) && h9 == n20->hash &&  COUNTPARTSUPP1_P_2SUPPLIER1_mapkey0_idxfn::equals(se31, *e20)); 
                  }
                }
              n19 = n19->nxt;
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


        COUNTPARTSUPP1_E1_2_DELTA.clear();
        COUNTPARTSUPP1_DOMAIN1.clear();
        STRING_TYPE l8 = c3;
        agg6.clear();        
        { 
          for (size_t i = 0; i < DELTA_PARTSUPP.size; i++)
          {
                long ps_partkey = DELTA_PARTSUPP.partkey[i];
                long s_suppkey = DELTA_PARTSUPP.suppkey[i];
                long ps_availqty = DELTA_PARTSUPP.availqty[i];
                DOUBLE_TYPE ps_supplycost = DELTA_PARTSUPP.supplycost[i];
                STRING_TYPE ps_comment = DELTA_PARTSUPP.comment[i];
                long v21 = 1L;
                COUNTPARTSUPP1_E1_2_DELTA.addOrDelOnZero(se32.modify(ps_partkey,s_suppkey,ps_availqty),v21);            
                long v22 = 1L;
                agg6.addOrDelOnZero(st2.modify(s_suppkey,(v22 != 0 ? 1L : 0L)), (v22 != 0 ? 1L : 0L));                
          }
        }

        {  // temp foreach
          const HashIndex<tuple2_L_L, long>* i23 = static_cast<HashIndex<tuple2_L_L, long>*>(agg6.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n23; 
          tuple2_L_L* e23;
        
          for (size_t i = 0; i < i23->size_; i++)
          {
            n23 = i23->buckets_ + i;
            while (n23 && (e23 = n23->obj))
            {
              long s_suppkey = e23->_1;  
              long v23 = e23->__av; 
            COUNTPARTSUPP1_DOMAIN1.addOrDelOnZero(se33.modify(l8,s_suppkey),v23);      
              n23 = n23->nxt;
            }
          }
        }STRING_TYPE l9 = c3;
        { //slice 
          const HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0* i24 = static_cast<HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0*>(COUNTPARTSUPP1_DOMAIN1.index[1]);
          const HASH_RES_t h13 = COUNTPARTSUPP1_DOMAIN1_mapkey0_idxfn::hash(se42.modify0(l9));
          HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0::IdxNode* n24 = static_cast<HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0::IdxNode*>(i24->slice(se42, h13));
          COUNTPARTSUPP1_DOMAIN1_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              long s_suppkey = e24->S_SUPPKEY;
              long v24 = e24->__av;
              { //slice 
                const HashIndex_COUNTPARTSUPP1_P_2_map_03* i25 = static_cast<HashIndex_COUNTPARTSUPP1_P_2_map_03*>(COUNTPARTSUPP1_P_2.index[1]);
                const HASH_RES_t h12 = COUNTPARTSUPP1_P_2_mapkey03_idxfn::hash(se41.modify03(s_suppkey, l9));
                HashIndex_COUNTPARTSUPP1_P_2_map_03::IdxNode* n25 = static_cast<HashIndex_COUNTPARTSUPP1_P_2_map_03::IdxNode*>(i25->slice(se41, h12));
                COUNTPARTSUPP1_P_2_entry* e25;
               
                if (n25 && (e25 = n25->obj)) {
                  do {                
                    STRING_TYPE s_name = e25->S_NAME;
                    STRING_TYPE s_address = e25->S_ADDRESS;
                    long v25 = e25->__av;
                    long agg7 = 0L;
                    { //slice 
                      const HashIndex_COUNTSUPPLIER1_E1_1_map_1* i26 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_map_1*>(COUNTSUPPLIER1_E1_1.index[1]);
                      const HASH_RES_t h10 = COUNTSUPPLIER1_E1_1_mapkey1_idxfn::hash(se37.modify1(s_suppkey));
                      HashIndex_COUNTSUPPLIER1_E1_1_map_1::IdxNode* n26 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_map_1::IdxNode*>(i26->slice(se37, h10));
                      COUNTSUPPLIER1_E1_1_entry* e26;
                     
                      if (n26 && (e26 = n26->obj)) {
                        do {                
                          long ps_partkey = e26->PS_PARTKEY;
                          long ps_availqty = e26->PS_AVAILQTY;
                          long v26 = e26->__av;
                          DOUBLE_TYPE l10 = (COUNTSUPPLIER1_E1_1_L1_1.getValueOrDefault(se35.modify(ps_partkey,s_suppkey)) * 0.5);
                          (/*if */(ps_availqty > l10) ? agg7 += (v26 * (COUNTSUPPLIER1_E1_1_E2_1.getValueOrDefault(se36.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                          n26 = n26->nxt;
                        } while (n26 && (e26 = n26->obj) && h10 == n26->hash &&  COUNTSUPPLIER1_E1_1_mapkey1_idxfn::equals(se37, *e26)); 
                      }
                    }long agg8 = 0L;
                    { //slice 
                      const HashIndex_COUNTPARTSUPP1_E1_2_DELTA_map_1* i27 = static_cast<HashIndex_COUNTPARTSUPP1_E1_2_DELTA_map_1*>(COUNTPARTSUPP1_E1_2_DELTA.index[1]);
                      const HASH_RES_t h11 = COUNTPARTSUPP1_E1_2_DELTA_mapkey1_idxfn::hash(se40.modify1(s_suppkey));
                      HashIndex_COUNTPARTSUPP1_E1_2_DELTA_map_1::IdxNode* n27 = static_cast<HashIndex_COUNTPARTSUPP1_E1_2_DELTA_map_1::IdxNode*>(i27->slice(se40, h11));
                      COUNTPARTSUPP1_E1_2_DELTA_entry* e27;
                     
                      if (n27 && (e27 = n27->obj)) {
                        do {                
                          long ps_partkey = e27->PS_PARTKEY;
                          long ps_availqty = e27->PS_AVAILQTY;
                          long v27 = e27->__av;
                          DOUBLE_TYPE l11 = (COUNTSUPPLIER1_E1_1_L1_1.getValueOrDefault(se38.modify(ps_partkey,s_suppkey)) * 0.5);
                          (/*if */(ps_availqty > l11) ? agg8 += (v27 * (COUNTSUPPLIER1_E1_1_E2_1.getValueOrDefault(se39.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                          n27 = n27->nxt;
                        } while (n27 && (e27 = n27->obj) && h11 == n27->hash &&  COUNTPARTSUPP1_E1_2_DELTA_mapkey1_idxfn::equals(se40, *e27)); 
                      }
                    }COUNT.addOrDelOnZero(se34.modify(s_name,s_address),((v24 != 0 ? 1L : 0L) * (v25 * ((agg7 + agg8) != 0 ? 1L : 0L))));
                    n25 = n25->nxt;
                  } while (n25 && (e25 = n25->obj) && h12 == n25->hash &&  COUNTPARTSUPP1_P_2_mapkey03_idxfn::equals(se41, *e25)); 
                }
              }
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h13 == n24->hash &&  COUNTPARTSUPP1_DOMAIN1_mapkey0_idxfn::equals(se42, *e24)); 
          }
        }STRING_TYPE l12 = c3;
        { //slice 
          const HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0* i28 = static_cast<HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0*>(COUNTPARTSUPP1_DOMAIN1.index[1]);
          const HASH_RES_t h16 = COUNTPARTSUPP1_DOMAIN1_mapkey0_idxfn::hash(se47.modify0(l12));
          HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0::IdxNode* n28 = static_cast<HashIndex_COUNTPARTSUPP1_DOMAIN1_map_0::IdxNode*>(i28->slice(se47, h16));
          COUNTPARTSUPP1_DOMAIN1_entry* e28;
         
          if (n28 && (e28 = n28->obj)) {
            do {                
              long s_suppkey = e28->S_SUPPKEY;
              long v28 = e28->__av;
              { //slice 
                const HashIndex_COUNTPARTSUPP1_P_2_map_03* i29 = static_cast<HashIndex_COUNTPARTSUPP1_P_2_map_03*>(COUNTPARTSUPP1_P_2.index[1]);
                const HASH_RES_t h15 = COUNTPARTSUPP1_P_2_mapkey03_idxfn::hash(se46.modify03(s_suppkey, l12));
                HashIndex_COUNTPARTSUPP1_P_2_map_03::IdxNode* n29 = static_cast<HashIndex_COUNTPARTSUPP1_P_2_map_03::IdxNode*>(i29->slice(se46, h15));
                COUNTPARTSUPP1_P_2_entry* e29;
               
                if (n29 && (e29 = n29->obj)) {
                  do {                
                    STRING_TYPE s_name = e29->S_NAME;
                    STRING_TYPE s_address = e29->S_ADDRESS;
                    long v29 = e29->__av;
                    long agg9 = 0L;
                    { //slice 
                      const HashIndex_COUNTSUPPLIER1_E1_1_map_1* i30 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_map_1*>(COUNTSUPPLIER1_E1_1.index[1]);
                      const HASH_RES_t h14 = COUNTSUPPLIER1_E1_1_mapkey1_idxfn::hash(se45.modify1(s_suppkey));
                      HashIndex_COUNTSUPPLIER1_E1_1_map_1::IdxNode* n30 = static_cast<HashIndex_COUNTSUPPLIER1_E1_1_map_1::IdxNode*>(i30->slice(se45, h14));
                      COUNTSUPPLIER1_E1_1_entry* e30;
                     
                      if (n30 && (e30 = n30->obj)) {
                        do {                
                          long ps_partkey = e30->PS_PARTKEY;
                          long ps_availqty = e30->PS_AVAILQTY;
                          long v30 = e30->__av;
                          DOUBLE_TYPE l13 = (COUNTSUPPLIER1_E1_1_L1_1.getValueOrDefault(se43.modify(ps_partkey,s_suppkey)) * 0.5);
                          (/*if */(ps_availqty > l13) ? agg9 += (v30 * (COUNTSUPPLIER1_E1_1_E2_1.getValueOrDefault(se44.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                          n30 = n30->nxt;
                        } while (n30 && (e30 = n30->obj) && h14 == n30->hash &&  COUNTSUPPLIER1_E1_1_mapkey1_idxfn::equals(se45, *e30)); 
                      }
                    }COUNT.addOrDelOnZero(se34.modify(s_name,s_address),(((v28 != 0 ? 1L : 0L) * (v29 * (agg9 != 0 ? 1L : 0L))) * -1L));
                    n29 = n29->nxt;
                  } while (n29 && (e29 = n29->obj) && h15 == n29->hash &&  COUNTPARTSUPP1_P_2_mapkey03_idxfn::equals(se46, *e29)); 
                }
              }
              n28 = n28->nxt;
            } while (n28 && (e28 = n28->obj) && h16 == n28->hash &&  COUNTPARTSUPP1_DOMAIN1_mapkey0_idxfn::equals(se47, *e28)); 
          }
        }{  // foreach
          const HashIndex_COUNTPARTSUPP1_E1_2_DELTA_map_012* i31 = static_cast<HashIndex_COUNTPARTSUPP1_E1_2_DELTA_map_012*>(COUNTPARTSUPP1_E1_2_DELTA.index[0]);
          HashIndex_COUNTPARTSUPP1_E1_2_DELTA_map_012::IdxNode* n31; 
          COUNTPARTSUPP1_E1_2_DELTA_entry* e31;
        
          for (size_t i = 0; i < i31->size_; i++)
          {
            n31 = i31->buckets_ + i;
            while (n31 && (e31 = n31->obj))
            {
                long ps_partkey = e31->PS_PARTKEY;
                long s_suppkey = e31->S_SUPPKEY;
                long ps_availqty = e31->PS_AVAILQTY;
                long v31 = e31->__av;
                COUNTSUPPLIER1_E1_1.addOrDelOnZero(se48.modify(ps_partkey,s_suppkey,ps_availqty),v31);
              n31 = n31->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        COUNTPARTSUPP1_P_2SUPPLIER1.clear();
        {  // foreach
          const HashIndex_NATION_map_0123* i32 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n32; 
          NATION_entry* e32;
        
          for (size_t i = 0; i < i32->size_; i++)
          {
            n32 = i32->buckets_ + i;
            while (n32 && (e32 = n32->obj))
            {
                long s_nationkey = e32->NATION_NATIONKEY;
                STRING_TYPE n_name = e32->NATION_NAME;
                long n_regionkey = e32->NATION_REGIONKEY;
                STRING_TYPE n_comment = e32->NATION_COMMENT;
                long v32 = e32->__av;
                COUNTPARTSUPP1_P_2SUPPLIER1.addOrDelOnZero(se49.modify(s_nationkey,n_name),v32);
              n32 = n32->nxt;
            }
          }
        }COUNTSUPPLIER1.clear();
        STRING_TYPE l14 = c3;
        { //slice 
          const HashIndex_NATION_map_1* i33 = static_cast<HashIndex_NATION_map_1*>(NATION.index[1]);
          const HASH_RES_t h17 = NATION_mapkey1_idxfn::hash(se51.modify1(l14));
          HashIndex_NATION_map_1::IdxNode* n33 = static_cast<HashIndex_NATION_map_1::IdxNode*>(i33->slice(se51, h17));
          NATION_entry* e33;
         
          if (n33 && (e33 = n33->obj)) {
            do {                
              long s_nationkey = e33->NATION_NATIONKEY;
              long n_regionkey = e33->NATION_REGIONKEY;
              STRING_TYPE n_comment = e33->NATION_COMMENT;
              long v33 = e33->__av;
              COUNTSUPPLIER1.addOrDelOnZero(se50.modify(s_nationkey),v33);
              n33 = n33->nxt;
            } while (n33 && (e33 = n33->obj) && h17 == n33->hash &&  NATION_mapkey1_idxfn::equals(se51, *e33)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNTLINEITEM1_E1_1_L1_3_DELTA_entry se1;
    COUNTLINEITEM1_DOMAIN1_entry se2;
    tuple2_L_L st1;
    COUNT_entry se3;
    COUNTSUPPLIER1_E1_1_L1_1_entry se4;
    COUNTLINEITEM1_E1_1_L1_3_DELTA_entry se5;
    COUNTSUPPLIER1_E1_1_E2_1_entry se6;
    COUNTSUPPLIER1_E1_1_entry se7;
    COUNTPARTSUPP1_P_2_entry se8;
    COUNTLINEITEM1_DOMAIN1_entry se9;
    COUNTSUPPLIER1_E1_1_L1_1_entry se10;
    COUNTSUPPLIER1_E1_1_E2_1_entry se11;
    COUNTSUPPLIER1_E1_1_entry se12;
    COUNTPARTSUPP1_P_2_entry se13;
    COUNTLINEITEM1_DOMAIN1_entry se14;
    COUNTSUPPLIER1_E1_1_L1_1_entry se15;
    COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_entry se16;
    COUNTSUPPLIER1_E1_1_E2_1_entry se17;
    COUNT_entry se18;
    COUNTSUPPLIER1_E1_1_L1_1_entry se19;
    COUNTSUPPLIER1_E1_1_E2_1_entry se20;
    COUNTSUPPLIER1_E1_1_entry se21;
    COUNTSUPPLIER1_DELTA_entry se22;
    COUNT_entry se23;
    COUNTSUPPLIER1_entry se24;
    COUNTSUPPLIER1_E1_1_L1_1_entry se25;
    COUNTSUPPLIER1_E1_1_E2_1_entry se26;
    COUNTSUPPLIER1_E1_1_entry se27;
    COUNTPART1_entry se28;
    COUNTSUPPLIER1_entry se29;
    COUNTPARTSUPP1_P_2_entry se30;
    COUNTPARTSUPP1_P_2SUPPLIER1_entry se31;
    COUNTPARTSUPP1_E1_2_DELTA_entry se32;
    COUNTPARTSUPP1_DOMAIN1_entry se33;
    tuple2_L_L st2;
    COUNT_entry se34;
    COUNTSUPPLIER1_E1_1_L1_1_entry se35;
    COUNTSUPPLIER1_E1_1_E2_1_entry se36;
    COUNTSUPPLIER1_E1_1_entry se37;
    COUNTSUPPLIER1_E1_1_L1_1_entry se38;
    COUNTSUPPLIER1_E1_1_E2_1_entry se39;
    COUNTPARTSUPP1_E1_2_DELTA_entry se40;
    COUNTPARTSUPP1_P_2_entry se41;
    COUNTPARTSUPP1_DOMAIN1_entry se42;
    COUNTSUPPLIER1_E1_1_L1_1_entry se43;
    COUNTSUPPLIER1_E1_1_E2_1_entry se44;
    COUNTSUPPLIER1_E1_1_entry se45;
    COUNTPARTSUPP1_P_2_entry se46;
    COUNTPARTSUPP1_DOMAIN1_entry se47;
    COUNTSUPPLIER1_E1_1_entry se48;
    COUNTPARTSUPP1_P_2SUPPLIER1_entry se49;
    COUNTSUPPLIER1_entry se50;
    NATION_entry se51;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    COUNTPART1_map COUNTPART1;
    COUNTLINEITEM1_DOMAIN1_map COUNTLINEITEM1_DOMAIN1;
    COUNTLINEITEM1_E1_1_L1_3_DELTA_map COUNTLINEITEM1_E1_1_L1_3_DELTA;
    COUNTPARTSUPP1_DOMAIN1_map COUNTPARTSUPP1_DOMAIN1;
    COUNTPARTSUPP1_P_2_map COUNTPARTSUPP1_P_2;
    COUNTPARTSUPP1_P_2SUPPLIER1_map COUNTPARTSUPP1_P_2SUPPLIER1;
    COUNTPARTSUPP1_E1_2_DELTA_map COUNTPARTSUPP1_E1_2_DELTA;
    COUNTSUPPLIER1_DELTA_map COUNTSUPPLIER1_DELTA;
    COUNTSUPPLIER1_map COUNTSUPPLIER1;
    COUNTSUPPLIER1_E1_1_map COUNTSUPPLIER1_E1_1;
    COUNTSUPPLIER1_E1_1_L1_1_map COUNTSUPPLIER1_E1_1_L1_1;
    COUNTSUPPLIER1_E1_1_E2_1_map COUNTSUPPLIER1_E1_1_E2_1;
    COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA_map COUNTSUPPLIER1_E1_1_E2_1PART1_DELTA;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_PART_map DELTA_PART;
    DELTA_SUPPLIER_map DELTA_SUPPLIER;
    DELTA_PARTSUPP_map DELTA_PARTSUPP;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg6;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg1;
    /*const static*/ long c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
  
  };

}
