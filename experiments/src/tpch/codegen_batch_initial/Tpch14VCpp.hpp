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
  
  struct PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry {
    long L_PARTKEY; long __av; 
    explicit PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry() { /*L_PARTKEY = 0L; __av = 0L; */ }
    explicit PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry(const long c0, const long c1) { L_PARTKEY = c0; __av = c1; }
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry(const PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry& other) : L_PARTKEY( other.L_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry& modify(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry& x, const PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry,long,
    HashIndex<PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry,long,PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_mapkey0_idxfn,true>
  > PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_map;
  typedef HashIndex<PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry,long,PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_mapkey0_idxfn,true> HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_map_0;
  
  struct PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry {
    long L_PARTKEY; DOUBLE_TYPE __av; 
    explicit PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry() { /*L_PARTKEY = 0L; __av = 0.0; */ }
    explicit PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry(const long c0, const DOUBLE_TYPE c1) { L_PARTKEY = c0; __av = c1; }
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry(const PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry& other) : L_PARTKEY( other.L_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry& modify(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry& x, const PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry,DOUBLE_TYPE,
    HashIndex<PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry,DOUBLE_TYPE,PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_mapkey0_idxfn,true>
  > PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_map;
  typedef HashIndex<PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry,DOUBLE_TYPE,PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_mapkey0_idxfn,true> HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_map_0;
  
  struct PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry {
    long L_PARTKEY; DOUBLE_TYPE __av; 
    explicit PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry() { /*L_PARTKEY = 0L; __av = 0.0; */ }
    explicit PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry(const long c0, const DOUBLE_TYPE c1) { L_PARTKEY = c0; __av = c1; }
    PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry(const PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry& other) : L_PARTKEY( other.L_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry& modify(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry& x, const PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry,DOUBLE_TYPE,PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_mapkey0_idxfn,true>
  > PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_map;
  typedef HashIndex<PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry,DOUBLE_TYPE,PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_mapkey0_idxfn,true> HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_map_0;
  
  struct PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry {
    long L_PARTKEY; long __av; 
    explicit PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry() { /*L_PARTKEY = 0L; __av = 0L; */ }
    explicit PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry(const long c0, const long c1) { L_PARTKEY = c0; __av = c1; }
    PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry(const PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry& other) : L_PARTKEY( other.L_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry& modify(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry& x, const PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry,long,
    HashIndex<PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry,long,PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_mapkey0_idxfn,true>
  > PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_map;
  typedef HashIndex<PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry,long,PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_mapkey0_idxfn,true> HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_map_0;
  
  struct PROMO_REVENUELINEITEM2PART1_DELTA_entry {
    long L_PARTKEY; long __av; 
    explicit PROMO_REVENUELINEITEM2PART1_DELTA_entry() { /*L_PARTKEY = 0L; __av = 0L; */ }
    explicit PROMO_REVENUELINEITEM2PART1_DELTA_entry(const long c0, const long c1) { L_PARTKEY = c0; __av = c1; }
    PROMO_REVENUELINEITEM2PART1_DELTA_entry(const PROMO_REVENUELINEITEM2PART1_DELTA_entry& other) : L_PARTKEY( other.L_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE PROMO_REVENUELINEITEM2PART1_DELTA_entry& modify(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMO_REVENUELINEITEM2PART1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const PROMO_REVENUELINEITEM2PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMO_REVENUELINEITEM2PART1_DELTA_entry& x, const PROMO_REVENUELINEITEM2PART1_DELTA_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<PROMO_REVENUELINEITEM2PART1_DELTA_entry,long,
    HashIndex<PROMO_REVENUELINEITEM2PART1_DELTA_entry,long,PROMO_REVENUELINEITEM2PART1_DELTA_mapkey0_idxfn,true>
  > PROMO_REVENUELINEITEM2PART1_DELTA_map;
  typedef HashIndex<PROMO_REVENUELINEITEM2PART1_DELTA_entry,long,PROMO_REVENUELINEITEM2PART1_DELTA_mapkey0_idxfn,true> HashIndex_PROMO_REVENUELINEITEM2PART1_DELTA_map_0;
  
  struct PROMO_REVENUELINEITEM2LINEITEM1_entry {
    long L_PARTKEY; long __av; 
    explicit PROMO_REVENUELINEITEM2LINEITEM1_entry() { /*L_PARTKEY = 0L; __av = 0L; */ }
    explicit PROMO_REVENUELINEITEM2LINEITEM1_entry(const long c0, const long c1) { L_PARTKEY = c0; __av = c1; }
    PROMO_REVENUELINEITEM2LINEITEM1_entry(const PROMO_REVENUELINEITEM2LINEITEM1_entry& other) : L_PARTKEY( other.L_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE PROMO_REVENUELINEITEM2LINEITEM1_entry& modify(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMO_REVENUELINEITEM2LINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const PROMO_REVENUELINEITEM2LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMO_REVENUELINEITEM2LINEITEM1_entry& x, const PROMO_REVENUELINEITEM2LINEITEM1_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<PROMO_REVENUELINEITEM2LINEITEM1_entry,long,
    HashIndex<PROMO_REVENUELINEITEM2LINEITEM1_entry,long,PROMO_REVENUELINEITEM2LINEITEM1_mapkey0_idxfn,true>
  > PROMO_REVENUELINEITEM2LINEITEM1_map;
  typedef HashIndex<PROMO_REVENUELINEITEM2LINEITEM1_entry,long,PROMO_REVENUELINEITEM2LINEITEM1_mapkey0_idxfn,true> HashIndex_PROMO_REVENUELINEITEM2LINEITEM1_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0), PROMO_REVENUE(0.0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const DOUBLE_TYPE _PROMO_REVENUE = get_PROMO_REVENUE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(PROMO_REVENUE), _PROMO_REVENUE, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const DOUBLE_TYPE get_PROMO_REVENUE() const {
      return PROMO_REVENUE;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    DOUBLE_TYPE PROMO_REVENUE;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), PROMO_REVENUELINEITEM1_L1_1_L1_1(0.0), PROMO_REVENUELINEITEM2(0.0) {
      c1 = Udate(STRING_TYPE("1995-9-1"));
      c2 = Udate(STRING_TYPE("1995-10-1"));
      /* regex_t init */
      if(regcomp(&preg1, "^PROMO.*$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^PROMO.*$/" << endl;
        exit(-1);
      }
    }
  
    ~data_t() {
      regfree(&preg1);
    }
  
    /* Trigger functions for table relations */
    
    
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


        PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                // long l_orderkey = DELTA_LINEITEM.orderkey[i];
                long l_partkey = DELTA_LINEITEM.partkey[i];
                // long l_suppkey = DELTA_LINEITEM.suppkey[i];
                // long l_linenumber = DELTA_LINEITEM.linenumber[i];
                // DOUBLE_TYPE l_quantity = DELTA_LINEITEM.quantity[i];
                DOUBLE_TYPE l_extendedprice = DELTA_LINEITEM.extendedprice[i];
                DOUBLE_TYPE l_discount = DELTA_LINEITEM.discount[i];
                // DOUBLE_TYPE l_tax = DELTA_LINEITEM.tax[i];
                // STRING_TYPE l_returnflag = DELTA_LINEITEM.returnflag[i];
                // STRING_TYPE l_linestatus = DELTA_LINEITEM.linestatus[i];
                date l_shipdate = DELTA_LINEITEM.shipdate[i];
                // date l_commitdate = DELTA_LINEITEM.commitdate[i];
                // date l_receiptdate = DELTA_LINEITEM.receiptdate[i];
                // STRING_TYPE l_shipinstruct = DELTA_LINEITEM.shipinstruct[i];
                // STRING_TYPE l_shipmode = DELTA_LINEITEM.shipmode[i];
                // STRING_TYPE l_comment = DELTA_LINEITEM.comment[i];
                long v1 = 1L;
                (/*if */(l_shipdate >= c1 && c2 > l_shipdate) ? PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA.addOrDelOnZero(se1.modify(l_partkey),(v1 * (l_extendedprice * (1L + (-1L * l_discount))))) : (void)0);
          }
        }

        DOUBLE_TYPE agg1 = 0.0;
        {  // foreach
          const HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_map_0* i2 = static_cast<HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_map_0*>(PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA.index[0]);
          HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_map_0::IdxNode* n2; 
          PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
                long l_partkey = e2->L_PARTKEY;
                DOUBLE_TYPE v2 = e2->__av;
                agg1 += (v2 * PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1.getValueOrDefault(se3.modify(l_partkey)));
              n2 = n2->nxt;
            }
          }
        }PROMO_REVENUELINEITEM1_L1_1_L1_1 += agg1;
        {  // foreach
          const HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_map_0* i3 = static_cast<HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_map_0*>(PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA.index[0]);
          HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_map_0::IdxNode* n3; 
          PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long l_partkey = e3->L_PARTKEY;
                DOUBLE_TYPE v3 = e3->__av;
                PROMO_REVENUELINEITEM1_L1_1_L1_1PART1.addOrDelOnZero(se4.modify(l_partkey),v3);
              n3 = n3->nxt;
            }
          }
        }DOUBLE_TYPE agg2 = 0.0;
        {  // foreach
          const HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_map_0* i4 = static_cast<HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_map_0*>(PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA.index[0]);
          HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_map_0::IdxNode* n4; 
          PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long l_partkey = e4->L_PARTKEY;
                DOUBLE_TYPE v4 = e4->__av;
                agg2 += (v4 * PROMO_REVENUELINEITEM2LINEITEM1.getValueOrDefault(se6.modify(l_partkey)));
              n4 = n4->nxt;
            }
          }
        }PROMO_REVENUELINEITEM2 += agg2;
        DOUBLE_TYPE agg3 = 0.0;
        DOUBLE_TYPE agg4 = 0.0;
        DOUBLE_TYPE l2 = PROMO_REVENUELINEITEM1_L1_1_L1_1;
        agg4 += Ulistmax(1L, l2);
        DOUBLE_TYPE l1 = agg4;
        agg3 += Udiv(l1);
        PROMO_REVENUE = (agg3 * (PROMO_REVENUELINEITEM2 * 100.0));
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


        PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA.clear();
        PROMO_REVENUELINEITEM2PART1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_PART.size; i++)
          {
                long l_partkey = DELTA_PART.partkey[i];
                // STRING_TYPE p_name = DELTA_PART.name[i];
                // STRING_TYPE p_mfgr = DELTA_PART.mfgr[i];
                // STRING_TYPE p_brand = DELTA_PART.brand[i];
                STRING_TYPE p_type = DELTA_PART.type[i];
                // long p_size = DELTA_PART.psize[i];
                // STRING_TYPE p_container = DELTA_PART.container[i];
                // DOUBLE_TYPE p_retailprice = DELTA_PART.retailprice[i];
                // STRING_TYPE p_comment = DELTA_PART.comment[i];
                long v5 = 1L;
                PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA.addOrDelOnZero(se8.modify(l_partkey),v5);
                long v6 = 1L;
                (/*if */(0L != Upreg_match(preg1,p_type)) ? PROMO_REVENUELINEITEM2PART1_DELTA.addOrDelOnZero(se9.modify(l_partkey),v6) : (void)0);
          }
        }
        
        DOUBLE_TYPE agg5 = 0.0;
        {  // foreach
          const HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_map_0* i7 = static_cast<HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_map_0*>(PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA.index[0]);
          HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_map_0::IdxNode* n7; 
          PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long l_partkey = e7->L_PARTKEY;
                long v7 = e7->__av;
                agg5 += (v7 * PROMO_REVENUELINEITEM1_L1_1_L1_1PART1.getValueOrDefault(se11.modify(l_partkey)));
              n7 = n7->nxt;
            }
          }
        }PROMO_REVENUELINEITEM1_L1_1_L1_1 += agg5;
        {  // foreach
          const HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_map_0* i8 = static_cast<HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_map_0*>(PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA.index[0]);
          HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_map_0::IdxNode* n8; 
          PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long l_partkey = e8->L_PARTKEY;
                long v8 = e8->__av;
                PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1.addOrDelOnZero(se12.modify(l_partkey),v8);
              n8 = n8->nxt;
            }
          }
        }DOUBLE_TYPE agg6 = 0.0;
        {  // foreach
          const HashIndex_PROMO_REVENUELINEITEM2PART1_DELTA_map_0* i9 = static_cast<HashIndex_PROMO_REVENUELINEITEM2PART1_DELTA_map_0*>(PROMO_REVENUELINEITEM2PART1_DELTA.index[0]);
          HashIndex_PROMO_REVENUELINEITEM2PART1_DELTA_map_0::IdxNode* n9; 
          PROMO_REVENUELINEITEM2PART1_DELTA_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long l_partkey = e9->L_PARTKEY;
                long v9 = e9->__av;
                agg6 += (v9 * PROMO_REVENUELINEITEM1_L1_1_L1_1PART1.getValueOrDefault(se14.modify(l_partkey)));
              n9 = n9->nxt;
            }
          }
        }PROMO_REVENUELINEITEM2 += agg6;
        {  // foreach
          const HashIndex_PROMO_REVENUELINEITEM2PART1_DELTA_map_0* i10 = static_cast<HashIndex_PROMO_REVENUELINEITEM2PART1_DELTA_map_0*>(PROMO_REVENUELINEITEM2PART1_DELTA.index[0]);
          HashIndex_PROMO_REVENUELINEITEM2PART1_DELTA_map_0::IdxNode* n10; 
          PROMO_REVENUELINEITEM2PART1_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long l_partkey = e10->L_PARTKEY;
                long v10 = e10->__av;
                PROMO_REVENUELINEITEM2LINEITEM1.addOrDelOnZero(se15.modify(l_partkey),v10);
              n10 = n10->nxt;
            }
          }
        }DOUBLE_TYPE agg7 = 0.0;
        DOUBLE_TYPE agg8 = 0.0;
        DOUBLE_TYPE l4 = PROMO_REVENUELINEITEM1_L1_1_L1_1;
        agg8 += Ulistmax(1L, l4);
        DOUBLE_TYPE l3 = agg8;
        agg7 += Udiv(l3);
        PROMO_REVENUE = (agg7 * (PROMO_REVENUELINEITEM2 * 100.0));
      }
    }
    void on_system_ready_event() {
      {  
        PROMO_REVENUE = 0.0;
        PROMO_REVENUELINEITEM1_L1_1_L1_1 = 0.0;
        PROMO_REVENUELINEITEM2 = 0.0;
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_entry se1;
    PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry se3;
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry se4;
    PROMO_REVENUELINEITEM2LINEITEM1_entry se6;
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_entry se8;
    PROMO_REVENUELINEITEM2PART1_DELTA_entry se9;
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry se11;
    PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_entry se12;
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry se14;
    PROMO_REVENUELINEITEM2LINEITEM1_entry se15;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    DOUBLE_TYPE PROMO_REVENUELINEITEM1_L1_1_L1_1;
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA_map PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_DELTA;
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_map PROMO_REVENUELINEITEM1_L1_1_L1_1PART1;
    PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA_map PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_DELTA;
    PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1_map PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM1;
    DOUBLE_TYPE PROMO_REVENUELINEITEM2;
    PROMO_REVENUELINEITEM2PART1_DELTA_map PROMO_REVENUELINEITEM2PART1_DELTA;
    PROMO_REVENUELINEITEM2LINEITEM1_map PROMO_REVENUELINEITEM2LINEITEM1;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_PART_map DELTA_PART;
    
    /*const static*/ long c1;
    /*const static*/ long c2;
  
  };

}
