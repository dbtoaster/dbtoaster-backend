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
  
  struct AVG_YEARLYPART1_DELTA_entry {
    long L_PARTKEY; long __av; 
    explicit AVG_YEARLYPART1_DELTA_entry() { /*L_PARTKEY = 0L; __av = 0L; */ }
    explicit AVG_YEARLYPART1_DELTA_entry(const long c0, const long c1) { L_PARTKEY = c0; __av = c1; }
    AVG_YEARLYPART1_DELTA_entry(const AVG_YEARLYPART1_DELTA_entry& other) : L_PARTKEY( other.L_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYPART1_DELTA_entry& modify(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYPART1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYPART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYPART1_DELTA_entry& x, const AVG_YEARLYPART1_DELTA_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYPART1_DELTA_entry,long,
    HashIndex<AVG_YEARLYPART1_DELTA_entry,long,AVG_YEARLYPART1_DELTA_mapkey0_idxfn,true>
  > AVG_YEARLYPART1_DELTA_map;
  typedef HashIndex<AVG_YEARLYPART1_DELTA_entry,long,AVG_YEARLYPART1_DELTA_mapkey0_idxfn,true> HashIndex_AVG_YEARLYPART1_DELTA_map_0;
  
  struct AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry {
    long L_PARTKEY; long __av; 
    explicit AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry() { /*L_PARTKEY = 0L; __av = 0L; */ }
    explicit AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry(const long c0, const long c1) { L_PARTKEY = c0; __av = c1; }
    AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry(const AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry& other) : L_PARTKEY( other.L_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry& modify(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM1_DOMAIN1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry& x, const AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry,long,
    HashIndex<AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry,long,AVG_YEARLYLINEITEM1_DOMAIN1_P_3_mapkey0_idxfn,true>
  > AVG_YEARLYLINEITEM1_DOMAIN1_P_3_map;
  typedef HashIndex<AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry,long,AVG_YEARLYLINEITEM1_DOMAIN1_P_3_mapkey0_idxfn,true> HashIndex_AVG_YEARLYLINEITEM1_DOMAIN1_P_3_map_0;
  
  struct AVG_YEARLYLINEITEM1_P_3_entry {
    long L_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_CONTAINER; long __av; 
    explicit AVG_YEARLYLINEITEM1_P_3_entry() { /*L_PARTKEY = 0L; P_BRAND = ""; P_CONTAINER = ""; __av = 0L; */ }
    explicit AVG_YEARLYLINEITEM1_P_3_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { L_PARTKEY = c0; P_BRAND = c1; P_CONTAINER = c2; __av = c3; }
    AVG_YEARLYLINEITEM1_P_3_entry(const AVG_YEARLYLINEITEM1_P_3_entry& other) : L_PARTKEY( other.L_PARTKEY ), P_BRAND( other.P_BRAND ), P_CONTAINER( other.P_CONTAINER ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM1_P_3_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { L_PARTKEY = c0; P_BRAND = c1; P_CONTAINER = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_CONTAINER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM1_P_3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_CONTAINER);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM1_P_3_entry& x, const AVG_YEARLYLINEITEM1_P_3_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_CONTAINER == y.P_CONTAINER;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM1_P_3_entry,long,
    HashIndex<AVG_YEARLYLINEITEM1_P_3_entry,long,AVG_YEARLYLINEITEM1_P_3_mapkey012_idxfn,true>
  > AVG_YEARLYLINEITEM1_P_3_map;
  typedef HashIndex<AVG_YEARLYLINEITEM1_P_3_entry,long,AVG_YEARLYLINEITEM1_P_3_mapkey012_idxfn,true> HashIndex_AVG_YEARLYLINEITEM1_P_3_map_012;
  
  struct AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry {
    long L_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_CONTAINER; long __av; 
    explicit AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry() { /*L_PARTKEY = 0L; P_BRAND = ""; P_CONTAINER = ""; __av = 0L; */ }
    explicit AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { L_PARTKEY = c0; P_BRAND = c1; P_CONTAINER = c2; __av = c3; }
    AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry(const AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry& other) : L_PARTKEY( other.L_PARTKEY ), P_BRAND( other.P_BRAND ), P_CONTAINER( other.P_CONTAINER ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { L_PARTKEY = c0; P_BRAND = c1; P_CONTAINER = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_CONTAINER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM1_P_3PART1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_CONTAINER);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry& x, const AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_CONTAINER == y.P_CONTAINER;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry,long,
    HashIndex<AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry,long,AVG_YEARLYLINEITEM1_P_3PART1_DELTA_mapkey012_idxfn,true>
  > AVG_YEARLYLINEITEM1_P_3PART1_DELTA_map;
  typedef HashIndex<AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry,long,AVG_YEARLYLINEITEM1_P_3PART1_DELTA_mapkey012_idxfn,true> HashIndex_AVG_YEARLYLINEITEM1_P_3PART1_DELTA_map_012;
  
  struct AVG_YEARLYLINEITEM1_P_4_entry {
    long L_PARTKEY; DOUBLE_TYPE L_QUANTITY; DOUBLE_TYPE __av; 
    explicit AVG_YEARLYLINEITEM1_P_4_entry() { /*L_PARTKEY = 0L; L_QUANTITY = 0.0; __av = 0.0; */ }
    explicit AVG_YEARLYLINEITEM1_P_4_entry(const long c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2) { L_PARTKEY = c0; L_QUANTITY = c1; __av = c2; }
    AVG_YEARLYLINEITEM1_P_4_entry(const AVG_YEARLYLINEITEM1_P_4_entry& other) : L_PARTKEY( other.L_PARTKEY ), L_QUANTITY( other.L_QUANTITY ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM1_P_4_entry& modify(const long c0, const DOUBLE_TYPE c1) { L_PARTKEY = c0; L_QUANTITY = c1;  return *this; }
    FORCE_INLINE AVG_YEARLYLINEITEM1_P_4_entry& modify0(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_QUANTITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM1_P_4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM1_P_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      hash_combine(h, e.L_QUANTITY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM1_P_4_entry& x, const AVG_YEARLYLINEITEM1_P_4_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY && x.L_QUANTITY == y.L_QUANTITY;
    }
  };
  
  struct AVG_YEARLYLINEITEM1_P_4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM1_P_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM1_P_4_entry& x, const AVG_YEARLYLINEITEM1_P_4_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM1_P_4_entry,DOUBLE_TYPE,
    HashIndex<AVG_YEARLYLINEITEM1_P_4_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM1_P_4_mapkey01_idxfn,true>,
    HashIndex<AVG_YEARLYLINEITEM1_P_4_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM1_P_4_mapkey0_idxfn,false>
  > AVG_YEARLYLINEITEM1_P_4_map;
  typedef HashIndex<AVG_YEARLYLINEITEM1_P_4_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM1_P_4_mapkey01_idxfn,true> HashIndex_AVG_YEARLYLINEITEM1_P_4_map_01;
  typedef HashIndex<AVG_YEARLYLINEITEM1_P_4_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM1_P_4_mapkey0_idxfn,false> HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0;
  
  struct AVG_YEARLYLINEITEM1_L1_1_L1_1_entry {
    long L_PARTKEY; long __av; 
    explicit AVG_YEARLYLINEITEM1_L1_1_L1_1_entry() { /*L_PARTKEY = 0L; __av = 0L; */ }
    explicit AVG_YEARLYLINEITEM1_L1_1_L1_1_entry(const long c0, const long c1) { L_PARTKEY = c0; __av = c1; }
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry(const AVG_YEARLYLINEITEM1_L1_1_L1_1_entry& other) : L_PARTKEY( other.L_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM1_L1_1_L1_1_entry& modify(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM1_L1_1_L1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM1_L1_1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM1_L1_1_L1_1_entry& x, const AVG_YEARLYLINEITEM1_L1_1_L1_1_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM1_L1_1_L1_1_entry,long,
    HashIndex<AVG_YEARLYLINEITEM1_L1_1_L1_1_entry,long,AVG_YEARLYLINEITEM1_L1_1_L1_1_mapkey0_idxfn,true>
  > AVG_YEARLYLINEITEM1_L1_1_L1_1_map;
  typedef HashIndex<AVG_YEARLYLINEITEM1_L1_1_L1_1_entry,long,AVG_YEARLYLINEITEM1_L1_1_L1_1_mapkey0_idxfn,true> HashIndex_AVG_YEARLYLINEITEM1_L1_1_L1_1_map_0;
  
  struct AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry {
    long L_PARTKEY; long __av; 
    explicit AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry() { /*L_PARTKEY = 0L; __av = 0L; */ }
    explicit AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry(const long c0, const long c1) { L_PARTKEY = c0; __av = c1; }
    AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry(const AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry& other) : L_PARTKEY( other.L_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry& modify(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry& x, const AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry,long,
    HashIndex<AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry,long,AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_mapkey0_idxfn,true>
  > AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_map;
  typedef HashIndex<AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry,long,AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_mapkey0_idxfn,true> HashIndex_AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_map_0;
  
  struct AVG_YEARLYLINEITEM1_L1_2_entry {
    long L_PARTKEY; DOUBLE_TYPE __av; 
    explicit AVG_YEARLYLINEITEM1_L1_2_entry() { /*L_PARTKEY = 0L; __av = 0.0; */ }
    explicit AVG_YEARLYLINEITEM1_L1_2_entry(const long c0, const DOUBLE_TYPE c1) { L_PARTKEY = c0; __av = c1; }
    AVG_YEARLYLINEITEM1_L1_2_entry(const AVG_YEARLYLINEITEM1_L1_2_entry& other) : L_PARTKEY( other.L_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM1_L1_2_entry& modify(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM1_L1_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM1_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM1_L1_2_entry& x, const AVG_YEARLYLINEITEM1_L1_2_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM1_L1_2_entry,DOUBLE_TYPE,
    HashIndex<AVG_YEARLYLINEITEM1_L1_2_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM1_L1_2_mapkey0_idxfn,true>
  > AVG_YEARLYLINEITEM1_L1_2_map;
  typedef HashIndex<AVG_YEARLYLINEITEM1_L1_2_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM1_L1_2_mapkey0_idxfn,true> HashIndex_AVG_YEARLYLINEITEM1_L1_2_map_0;
  
  struct AVG_YEARLYLINEITEM1_L1_4_DELTA_entry {
    long L_PARTKEY; DOUBLE_TYPE __av; 
    explicit AVG_YEARLYLINEITEM1_L1_4_DELTA_entry() { /*L_PARTKEY = 0L; __av = 0.0; */ }
    explicit AVG_YEARLYLINEITEM1_L1_4_DELTA_entry(const long c0, const DOUBLE_TYPE c1) { L_PARTKEY = c0; __av = c1; }
    AVG_YEARLYLINEITEM1_L1_4_DELTA_entry(const AVG_YEARLYLINEITEM1_L1_4_DELTA_entry& other) : L_PARTKEY( other.L_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM1_L1_4_DELTA_entry& modify(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM1_L1_4_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM1_L1_4_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM1_L1_4_DELTA_entry& x, const AVG_YEARLYLINEITEM1_L1_4_DELTA_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM1_L1_4_DELTA_entry,DOUBLE_TYPE,
    HashIndex<AVG_YEARLYLINEITEM1_L1_4_DELTA_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM1_L1_4_DELTA_mapkey0_idxfn,true>
  > AVG_YEARLYLINEITEM1_L1_4_DELTA_map;
  typedef HashIndex<AVG_YEARLYLINEITEM1_L1_4_DELTA_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM1_L1_4_DELTA_mapkey0_idxfn,true> HashIndex_AVG_YEARLYLINEITEM1_L1_4_DELTA_map_0;
  
  struct AVG_YEARLYLINEITEM5_DELTA_entry {
    long L_PARTKEY; DOUBLE_TYPE L_QUANTITY; DOUBLE_TYPE __av; 
    explicit AVG_YEARLYLINEITEM5_DELTA_entry() { /*L_PARTKEY = 0L; L_QUANTITY = 0.0; __av = 0.0; */ }
    explicit AVG_YEARLYLINEITEM5_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2) { L_PARTKEY = c0; L_QUANTITY = c1; __av = c2; }
    AVG_YEARLYLINEITEM5_DELTA_entry(const AVG_YEARLYLINEITEM5_DELTA_entry& other) : L_PARTKEY( other.L_PARTKEY ), L_QUANTITY( other.L_QUANTITY ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM5_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1) { L_PARTKEY = c0; L_QUANTITY = c1;  return *this; }
    FORCE_INLINE AVG_YEARLYLINEITEM5_DELTA_entry& modify0(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_QUANTITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM5_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM5_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      hash_combine(h, e.L_QUANTITY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM5_DELTA_entry& x, const AVG_YEARLYLINEITEM5_DELTA_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY && x.L_QUANTITY == y.L_QUANTITY;
    }
  };
  
  struct AVG_YEARLYLINEITEM5_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM5_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM5_DELTA_entry& x, const AVG_YEARLYLINEITEM5_DELTA_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM5_DELTA_entry,DOUBLE_TYPE,
    HashIndex<AVG_YEARLYLINEITEM5_DELTA_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM5_DELTA_mapkey01_idxfn,true>,
    HashIndex<AVG_YEARLYLINEITEM5_DELTA_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM5_DELTA_mapkey0_idxfn,false>
  > AVG_YEARLYLINEITEM5_DELTA_map;
  typedef HashIndex<AVG_YEARLYLINEITEM5_DELTA_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM5_DELTA_mapkey01_idxfn,true> HashIndex_AVG_YEARLYLINEITEM5_DELTA_map_01;
  typedef HashIndex<AVG_YEARLYLINEITEM5_DELTA_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM5_DELTA_mapkey0_idxfn,false> HashIndex_AVG_YEARLYLINEITEM5_DELTA_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0), AVG_YEARLY(0.0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const DOUBLE_TYPE _AVG_YEARLY = get_AVG_YEARLY();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AVG_YEARLY), _AVG_YEARLY, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const DOUBLE_TYPE get_AVG_YEARLY() const {
      return AVG_YEARLY;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    DOUBLE_TYPE AVG_YEARLY;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c2 = STRING_TYPE("MED BOX");
      c1 = STRING_TYPE("Brand#23");
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

        AVG_YEARLYLINEITEM5_DELTA.clear();
        AVG_YEARLYLINEITEM1_L1_4_DELTA.clear();
        AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA.clear();
        AVG_YEARLYLINEITEM1_DOMAIN1_P_3.clear();
        {
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                // long l_orderkey = DELTA_LINEITEM.orderkey[i];
                long l_partkey = DELTA_LINEITEM.partkey[i];
                // long l_suppkey = DELTA_LINEITEM.suppkey[i];
                // long l_linenumber = DELTA_LINEITEM.linenumber[i];
                DOUBLE_TYPE l_quantity = DELTA_LINEITEM.quantity[i];
                DOUBLE_TYPE l_extendedprice = DELTA_LINEITEM.extendedprice[i];
                // DOUBLE_TYPE l_discount = DELTA_LINEITEM.discount[i];
                // DOUBLE_TYPE l_tax = DELTA_LINEITEM.tax[i];
                // STRING_TYPE l_returnflag = DELTA_LINEITEM.returnflag[i];
                // STRING_TYPE l_linestatus = DELTA_LINEITEM.linestatus[i];
                // date l_shipdate = DELTA_LINEITEM.shipdate[i];
                // date l_commitdate = DELTA_LINEITEM.commitdate[i];
                // date l_receiptdate = DELTA_LINEITEM.receiptdate[i];
                // STRING_TYPE l_shipinstruct = DELTA_LINEITEM.shipinstruct[i];
                // STRING_TYPE l_shipmode = DELTA_LINEITEM.shipmode[i];
                // STRING_TYPE l_comment = DELTA_LINEITEM.comment[i];
                long v1 = 1L;
                AVG_YEARLYLINEITEM5_DELTA.addOrDelOnZero(se1.modify(l_partkey,l_quantity),(v1 * l_extendedprice));            
                long v2 = 1L;
                AVG_YEARLYLINEITEM1_L1_4_DELTA.addOrDelOnZero(se2.modify(l_partkey),(v2 * l_quantity));
                long v3 = 1L;
                AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA.addOrDelOnZero(se3.modify(l_partkey),v3);
                long v4 = 1L;
                AVG_YEARLYLINEITEM1_DOMAIN1_P_3.addOrDelOnZero(se4.modify(l_partkey),(v4 != 0 ? 1L : 0L));
          }
        }
        
        DOUBLE_TYPE agg1 = 0.0;
        STRING_TYPE l1 = c1;
        STRING_TYPE l2 = c2;
        {  // foreach
          const HashIndex_AVG_YEARLYLINEITEM1_DOMAIN1_P_3_map_0* i5 = static_cast<HashIndex_AVG_YEARLYLINEITEM1_DOMAIN1_P_3_map_0*>(AVG_YEARLYLINEITEM1_DOMAIN1_P_3.index[0]);
          HashIndex_AVG_YEARLYLINEITEM1_DOMAIN1_P_3_map_0::IdxNode* n5; 
          AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long l_partkey = e5->L_PARTKEY;
                long v5 = e5->__av;
                DOUBLE_TYPE agg2 = 0.0;
                long l4 = (AVG_YEARLYLINEITEM1_L1_1_L1_1.getValueOrDefault(se7.modify(l_partkey)) + AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA.getValueOrDefault(se8.modify(l_partkey)));
                (/*if */(0L != l4) ? agg2 += Udiv(Ulistmax(1L, l4)) : 0.0);
                DOUBLE_TYPE agg3 = 0.0;
                long l5 = (AVG_YEARLYLINEITEM1_L1_1_L1_1.getValueOrDefault(se10.modify(l_partkey)) + AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA.getValueOrDefault(se11.modify(l_partkey)));
                (/*if */(0L != l5) ? agg3 += Udiv(Ulistmax(1L, l5)) : 0.0);
                DOUBLE_TYPE l3 = ((AVG_YEARLYLINEITEM1_L1_2.getValueOrDefault(se6.modify(l_partkey)) * (agg2 * 0.2)) + (AVG_YEARLYLINEITEM1_L1_4_DELTA.getValueOrDefault(se9.modify(l_partkey)) * (agg3 * 0.2)));
                { //slice 
                  const HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0* i6 = static_cast<HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0*>(AVG_YEARLYLINEITEM1_P_4.index[1]);
                  const HASH_RES_t h1 = AVG_YEARLYLINEITEM1_P_4_mapkey0_idxfn::hash(se13.modify0(l_partkey));
                  HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0::IdxNode* n6 = static_cast<HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0::IdxNode*>(i6->slice(se13, h1));
                  AVG_YEARLYLINEITEM1_P_4_entry* e6;
                 
                  if (n6 && (e6 = n6->obj)) {
                    do {                
                      DOUBLE_TYPE l_quantity = e6->L_QUANTITY;
                      DOUBLE_TYPE v6 = e6->__av;
                      (/*if */(l3 > l_quantity) ? agg1 += ((v5 != 0 ? 1L : 0L) * (AVG_YEARLYLINEITEM1_P_3.getValueOrDefault(se12.modify(l_partkey,l1,l2)) * v6)) : 0.0);
                      n6 = n6->nxt;
                    } while (n6 && (e6 = n6->obj) && h1 == n6->hash &&  AVG_YEARLYLINEITEM1_P_4_mapkey0_idxfn::equals(se13, *e6)); 
                  }
                }
              n5 = n5->nxt;
            }
          }
        }DOUBLE_TYPE agg4 = 0.0;
        STRING_TYPE l6 = c1;
        STRING_TYPE l7 = c2;
        {  // foreach
          const HashIndex_AVG_YEARLYLINEITEM1_DOMAIN1_P_3_map_0* i7 = static_cast<HashIndex_AVG_YEARLYLINEITEM1_DOMAIN1_P_3_map_0*>(AVG_YEARLYLINEITEM1_DOMAIN1_P_3.index[0]);
          HashIndex_AVG_YEARLYLINEITEM1_DOMAIN1_P_3_map_0::IdxNode* n7; 
          AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long l_partkey = e7->L_PARTKEY;
                long v7 = e7->__av;
                DOUBLE_TYPE agg5 = 0.0;
                long l9 = AVG_YEARLYLINEITEM1_L1_1_L1_1.getValueOrDefault(se15.modify(l_partkey));
                (/*if */(0L != l9) ? agg5 += Udiv(Ulistmax(1L, l9)) : 0.0);
                DOUBLE_TYPE l8 = (AVG_YEARLYLINEITEM1_L1_2.getValueOrDefault(se14.modify(l_partkey)) * (agg5 * 0.2));
                { //slice 
                  const HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0* i8 = static_cast<HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0*>(AVG_YEARLYLINEITEM1_P_4.index[1]);
                  const HASH_RES_t h2 = AVG_YEARLYLINEITEM1_P_4_mapkey0_idxfn::hash(se17.modify0(l_partkey));
                  HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0::IdxNode* n8 = static_cast<HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0::IdxNode*>(i8->slice(se17, h2));
                  AVG_YEARLYLINEITEM1_P_4_entry* e8;
                 
                  if (n8 && (e8 = n8->obj)) {
                    do {                
                      DOUBLE_TYPE l_quantity = e8->L_QUANTITY;
                      DOUBLE_TYPE v8 = e8->__av;
                      (/*if */(l8 > l_quantity) ? agg4 += ((v7 != 0 ? 1L : 0L) * (AVG_YEARLYLINEITEM1_P_3.getValueOrDefault(se16.modify(l_partkey,l6,l7)) * v8)) : 0.0);
                      n8 = n8->nxt;
                    } while (n8 && (e8 = n8->obj) && h2 == n8->hash &&  AVG_YEARLYLINEITEM1_P_4_mapkey0_idxfn::equals(se17, *e8)); 
                  }
                }
              n7 = n7->nxt;
            }
          }
        }DOUBLE_TYPE agg6 = 0.0;
        STRING_TYPE l10 = c1;
        STRING_TYPE l11 = c2;
        {  // foreach
          const HashIndex_AVG_YEARLYLINEITEM1_DOMAIN1_P_3_map_0* i9 = static_cast<HashIndex_AVG_YEARLYLINEITEM1_DOMAIN1_P_3_map_0*>(AVG_YEARLYLINEITEM1_DOMAIN1_P_3.index[0]);
          HashIndex_AVG_YEARLYLINEITEM1_DOMAIN1_P_3_map_0::IdxNode* n9; 
          AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long l_partkey = e9->L_PARTKEY;
                long v9 = e9->__av;
                { //slice 
                  const HashIndex_AVG_YEARLYLINEITEM5_DELTA_map_0* i10 = static_cast<HashIndex_AVG_YEARLYLINEITEM5_DELTA_map_0*>(AVG_YEARLYLINEITEM5_DELTA.index[1]);
                  const HASH_RES_t h3 = AVG_YEARLYLINEITEM5_DELTA_mapkey0_idxfn::hash(se25.modify0(l_partkey));
                  HashIndex_AVG_YEARLYLINEITEM5_DELTA_map_0::IdxNode* n10 = static_cast<HashIndex_AVG_YEARLYLINEITEM5_DELTA_map_0::IdxNode*>(i10->slice(se25, h3));
                  AVG_YEARLYLINEITEM5_DELTA_entry* e10;
                 
                  if (n10 && (e10 = n10->obj)) {
                    do {                
                      DOUBLE_TYPE l_quantity = e10->L_QUANTITY;
                      DOUBLE_TYPE v10 = e10->__av;
                      DOUBLE_TYPE agg7 = 0.0;
                      long l13 = (AVG_YEARLYLINEITEM1_L1_1_L1_1.getValueOrDefault(se19.modify(l_partkey)) + AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA.getValueOrDefault(se20.modify(l_partkey)));
                      (/*if */(0L != l13) ? agg7 += Udiv(Ulistmax(1L, l13)) : 0.0);
                      DOUBLE_TYPE agg8 = 0.0;
                      long l14 = (AVG_YEARLYLINEITEM1_L1_1_L1_1.getValueOrDefault(se22.modify(l_partkey)) + AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA.getValueOrDefault(se23.modify(l_partkey)));
                      (/*if */(0L != l14) ? agg8 += Udiv(Ulistmax(1L, l14)) : 0.0);
                      DOUBLE_TYPE l12 = ((AVG_YEARLYLINEITEM1_L1_2.getValueOrDefault(se18.modify(l_partkey)) * (agg7 * 0.2)) + (AVG_YEARLYLINEITEM1_L1_4_DELTA.getValueOrDefault(se21.modify(l_partkey)) * (agg8 * 0.2)));
                      (/*if */(l12 > l_quantity) ? agg6 += ((v9 != 0 ? 1L : 0L) * (v10 * AVG_YEARLYLINEITEM1_P_3.getValueOrDefault(se24.modify(l_partkey,l10,l11)))) : 0.0);
                      n10 = n10->nxt;
                    } while (n10 && (e10 = n10->obj) && h3 == n10->hash &&  AVG_YEARLYLINEITEM5_DELTA_mapkey0_idxfn::equals(se25, *e10)); 
                  }
                }
              n9 = n9->nxt;
            }
          }
        }AVG_YEARLY += ((agg1 + ((agg4 * -1L) + agg6)) * 0.142857142857);
        {  // foreach
          const HashIndex_AVG_YEARLYLINEITEM5_DELTA_map_01* i11 = static_cast<HashIndex_AVG_YEARLYLINEITEM5_DELTA_map_01*>(AVG_YEARLYLINEITEM5_DELTA.index[0]);
          HashIndex_AVG_YEARLYLINEITEM5_DELTA_map_01::IdxNode* n11; 
          AVG_YEARLYLINEITEM5_DELTA_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long l_partkey = e11->L_PARTKEY;
                DOUBLE_TYPE l_quantity = e11->L_QUANTITY;
                DOUBLE_TYPE v11 = e11->__av;
                AVG_YEARLYLINEITEM1_P_4.addOrDelOnZero(se26.modify(l_partkey,l_quantity),v11);
              n11 = n11->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_map_0* i12 = static_cast<HashIndex_AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_map_0*>(AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_map_0::IdxNode* n12; 
          AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long l_partkey = e12->L_PARTKEY;
                long v12 = e12->__av;
                AVG_YEARLYLINEITEM1_L1_1_L1_1.addOrDelOnZero(se27.modify(l_partkey),v12);
              n12 = n12->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AVG_YEARLYLINEITEM1_L1_4_DELTA_map_0* i13 = static_cast<HashIndex_AVG_YEARLYLINEITEM1_L1_4_DELTA_map_0*>(AVG_YEARLYLINEITEM1_L1_4_DELTA.index[0]);
          HashIndex_AVG_YEARLYLINEITEM1_L1_4_DELTA_map_0::IdxNode* n13; 
          AVG_YEARLYLINEITEM1_L1_4_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long l_partkey = e13->L_PARTKEY;
                DOUBLE_TYPE v13 = e13->__av;
                AVG_YEARLYLINEITEM1_L1_2.addOrDelOnZero(se28.modify(l_partkey),v13);
              n13 = n13->nxt;
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

        AVG_YEARLYPART1_DELTA.clear();
        AVG_YEARLYLINEITEM1_P_3PART1_DELTA.clear();
        { 
          for (size_t i = 0; i < DELTA_PART.size; i++) 
          {
                long l_partkey = DELTA_PART.partkey[i];
                // STRING_TYPE p_name = DELTA_PART.name[i];
                // STRING_TYPE p_mfgr = DELTA_PART.mfgr[i];
                STRING_TYPE p_brand = DELTA_PART.brand[i];
                // STRING_TYPE p_type = DELTA_PART.type[i];
                // long p_size = DELTA_PART.psize[i];
                STRING_TYPE p_container = DELTA_PART.container[i];
                // DOUBLE_TYPE p_retailprice = DELTA_PART.retailprice[i];
                // STRING_TYPE p_comment = DELTA_PART.comment[i];
                long v14 = 1L;
                (/*if */(p_brand == c1 && p_container == c2) ? AVG_YEARLYPART1_DELTA.addOrDelOnZero(se29.modify(l_partkey),v14) : (void)0);          
                long v15 = 1L;
                AVG_YEARLYLINEITEM1_P_3PART1_DELTA.addOrDelOnZero(se30.modify(l_partkey,p_brand,p_container),v15);
          }
        }

        DOUBLE_TYPE agg9 = 0.0;
        {  // foreach
          const HashIndex_AVG_YEARLYPART1_DELTA_map_0* i16 = static_cast<HashIndex_AVG_YEARLYPART1_DELTA_map_0*>(AVG_YEARLYPART1_DELTA.index[0]);
          HashIndex_AVG_YEARLYPART1_DELTA_map_0::IdxNode* n16; 
          AVG_YEARLYPART1_DELTA_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long l_partkey = e16->L_PARTKEY;
                long v16 = e16->__av;
                DOUBLE_TYPE agg10 = 0.0;
                long l16 = AVG_YEARLYLINEITEM1_L1_1_L1_1.getValueOrDefault(se33.modify(l_partkey));
                (/*if */(0L != l16) ? agg10 += Udiv(Ulistmax(1L, l16)) : 0.0);
                DOUBLE_TYPE l15 = (AVG_YEARLYLINEITEM1_L1_2.getValueOrDefault(se32.modify(l_partkey)) * (agg10 * 0.2));
                { //slice 
                  const HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0* i17 = static_cast<HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0*>(AVG_YEARLYLINEITEM1_P_4.index[1]);
                  const HASH_RES_t h4 = AVG_YEARLYLINEITEM1_P_4_mapkey0_idxfn::hash(se34.modify0(l_partkey));
                  HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0::IdxNode* n17 = static_cast<HashIndex_AVG_YEARLYLINEITEM1_P_4_map_0::IdxNode*>(i17->slice(se34, h4));
                  AVG_YEARLYLINEITEM1_P_4_entry* e17;
                 
                  if (n17 && (e17 = n17->obj)) {
                    do {                
                      DOUBLE_TYPE l_quantity = e17->L_QUANTITY;
                      DOUBLE_TYPE v17 = e17->__av;
                      (/*if */(l15 > l_quantity) ? agg9 += (v16 * v17) : 0.0);
                      n17 = n17->nxt;
                    } while (n17 && (e17 = n17->obj) && h4 == n17->hash &&  AVG_YEARLYLINEITEM1_P_4_mapkey0_idxfn::equals(se34, *e17)); 
                  }
                }
              n16 = n16->nxt;
            }
          }
        }AVG_YEARLY += (agg9 * 0.142857142857);
        {  // foreach
          const HashIndex_AVG_YEARLYLINEITEM1_P_3PART1_DELTA_map_012* i18 = static_cast<HashIndex_AVG_YEARLYLINEITEM1_P_3PART1_DELTA_map_012*>(AVG_YEARLYLINEITEM1_P_3PART1_DELTA.index[0]);
          HashIndex_AVG_YEARLYLINEITEM1_P_3PART1_DELTA_map_012::IdxNode* n18; 
          AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
                long l_partkey = e18->L_PARTKEY;
                STRING_TYPE p_brand = e18->P_BRAND;
                STRING_TYPE p_container = e18->P_CONTAINER;
                long v18 = e18->__av;
                AVG_YEARLYLINEITEM1_P_3.addOrDelOnZero(se35.modify(l_partkey,p_brand,p_container),v18);
              n18 = n18->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        AVG_YEARLY = 0.0;
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    AVG_YEARLYLINEITEM5_DELTA_entry se1;
    AVG_YEARLYLINEITEM1_L1_4_DELTA_entry se2;
    AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry se3;
    AVG_YEARLYLINEITEM1_DOMAIN1_P_3_entry se4;
    AVG_YEARLYLINEITEM1_L1_2_entry se6;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry se7;
    AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry se8;
    AVG_YEARLYLINEITEM1_L1_4_DELTA_entry se9;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry se10;
    AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry se11;
    AVG_YEARLYLINEITEM1_P_3_entry se12;
    AVG_YEARLYLINEITEM1_P_4_entry se13;
    AVG_YEARLYLINEITEM1_L1_2_entry se14;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry se15;
    AVG_YEARLYLINEITEM1_P_3_entry se16;
    AVG_YEARLYLINEITEM1_P_4_entry se17;
    AVG_YEARLYLINEITEM1_L1_2_entry se18;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry se19;
    AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry se20;
    AVG_YEARLYLINEITEM1_L1_4_DELTA_entry se21;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry se22;
    AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_entry se23;
    AVG_YEARLYLINEITEM1_P_3_entry se24;
    AVG_YEARLYLINEITEM5_DELTA_entry se25;
    AVG_YEARLYLINEITEM1_P_4_entry se26;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry se27;
    AVG_YEARLYLINEITEM1_L1_2_entry se28;
    AVG_YEARLYPART1_DELTA_entry se29;
    AVG_YEARLYLINEITEM1_P_3PART1_DELTA_entry se30;
    AVG_YEARLYLINEITEM1_L1_2_entry se32;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry se33;
    AVG_YEARLYLINEITEM1_P_4_entry se34;
    AVG_YEARLYLINEITEM1_P_3_entry se35;
  
    /* Data structures used for storing materialized views */
    AVG_YEARLYPART1_DELTA_map AVG_YEARLYPART1_DELTA;
    AVG_YEARLYLINEITEM1_DOMAIN1_P_3_map AVG_YEARLYLINEITEM1_DOMAIN1_P_3;
    AVG_YEARLYLINEITEM1_P_3_map AVG_YEARLYLINEITEM1_P_3;
    AVG_YEARLYLINEITEM1_P_3PART1_DELTA_map AVG_YEARLYLINEITEM1_P_3PART1_DELTA;
    AVG_YEARLYLINEITEM1_P_4_map AVG_YEARLYLINEITEM1_P_4;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_map AVG_YEARLYLINEITEM1_L1_1_L1_1;
    AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA_map AVG_YEARLYLINEITEM1_L1_1_L1_2_DELTA;
    AVG_YEARLYLINEITEM1_L1_2_map AVG_YEARLYLINEITEM1_L1_2;
    AVG_YEARLYLINEITEM1_L1_4_DELTA_map AVG_YEARLYLINEITEM1_L1_4_DELTA;
    AVG_YEARLYLINEITEM5_DELTA_map AVG_YEARLYLINEITEM5_DELTA;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_PART_map DELTA_PART;
    
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c1;
  
  };

}
