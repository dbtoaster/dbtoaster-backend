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
  
  struct DELTA_ORDERS_entry {
    long orders_orderkey; long orders_custkey; STRING_TYPE orders_orderstatus; DOUBLE_TYPE orders_totalprice; date orders_orderdate; STRING_TYPE orders_orderpriority; STRING_TYPE orders_clerk; long orders_shippriority; STRING_TYPE orders_comment; long __av; 
    explicit DELTA_ORDERS_entry() { /*orders_orderkey = 0L; orders_custkey = 0L; orders_orderstatus = ""; orders_totalprice = 0.0; orders_orderdate = 00000000; orders_orderpriority = ""; orders_clerk = ""; orders_shippriority = 0L; orders_comment = ""; __av = 0L; */ }
    explicit DELTA_ORDERS_entry(const long c0, const long c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3, const date c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const long c7, const STRING_TYPE& c8, const long c9) { orders_orderkey = c0; orders_custkey = c1; orders_orderstatus = c2; orders_totalprice = c3; orders_orderdate = c4; orders_orderpriority = c5; orders_clerk = c6; orders_shippriority = c7; orders_comment = c8; __av = c9; }
    DELTA_ORDERS_entry(const DELTA_ORDERS_entry& other) : orders_orderkey( other.orders_orderkey ), orders_custkey( other.orders_custkey ), orders_orderstatus( other.orders_orderstatus ), orders_totalprice( other.orders_totalprice ), orders_orderdate( other.orders_orderdate ), orders_orderpriority( other.orders_orderpriority ), orders_clerk( other.orders_clerk ), orders_shippriority( other.orders_shippriority ), orders_comment( other.orders_comment ), __av( other.__av ) {}
    FORCE_INLINE DELTA_ORDERS_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3, const date c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const long c7, const STRING_TYPE& c8) { orders_orderkey = c0; orders_custkey = c1; orders_orderstatus = c2; orders_totalprice = c3; orders_orderdate = c4; orders_orderpriority = c5; orders_clerk = c6; orders_shippriority = c7; orders_comment = c8;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orders_orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orders_custkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orders_orderstatus);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orders_totalprice);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orders_orderdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orders_orderpriority);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orders_clerk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orders_shippriority);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orders_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_ORDERS_mapkey012345678_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_ORDERS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orders_orderkey);
      hash_combine(h, e.orders_custkey);
      hash_combine(h, e.orders_orderstatus);
      hash_combine(h, e.orders_totalprice);
      hash_combine(h, e.orders_orderdate);
      hash_combine(h, e.orders_orderpriority);
      hash_combine(h, e.orders_clerk);
      hash_combine(h, e.orders_shippriority);
      hash_combine(h, e.orders_comment);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_ORDERS_entry& x, const DELTA_ORDERS_entry& y) {
      return x.orders_orderkey == y.orders_orderkey && x.orders_custkey == y.orders_custkey && x.orders_orderstatus == y.orders_orderstatus && x.orders_totalprice == y.orders_totalprice && x.orders_orderdate == y.orders_orderdate && x.orders_orderpriority == y.orders_orderpriority && x.orders_clerk == y.orders_clerk && x.orders_shippriority == y.orders_shippriority && x.orders_comment == y.orders_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_ORDERS_entry,long,
    HashIndex<DELTA_ORDERS_entry,long,DELTA_ORDERS_mapkey012345678_idxfn,true>
  > DELTA_ORDERS_map;
  typedef HashIndex<DELTA_ORDERS_entry,long,DELTA_ORDERS_mapkey012345678_idxfn,true> HashIndex_DELTA_ORDERS_map_012345678;
  
  struct HIGH_LINE_COUNT_entry {
    STRING_TYPE L_SHIPMODE; long __av; 
    explicit HIGH_LINE_COUNT_entry() { /*L_SHIPMODE = ""; __av = 0L; */ }
    explicit HIGH_LINE_COUNT_entry(const STRING_TYPE& c0, const long c1) { L_SHIPMODE = c0; __av = c1; }
    HIGH_LINE_COUNT_entry(const HIGH_LINE_COUNT_entry& other) : L_SHIPMODE( other.L_SHIPMODE ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNT_entry& modify(const STRING_TYPE& c0) { L_SHIPMODE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPMODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNT_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_SHIPMODE);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNT_entry& x, const HIGH_LINE_COUNT_entry& y) {
      return x.L_SHIPMODE == y.L_SHIPMODE;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNT_entry,long,
    HashIndex<HIGH_LINE_COUNT_entry,long,HIGH_LINE_COUNT_mapkey0_idxfn,true>
  > HIGH_LINE_COUNT_map;
  typedef HashIndex<HIGH_LINE_COUNT_entry,long,HIGH_LINE_COUNT_mapkey0_idxfn,true> HashIndex_HIGH_LINE_COUNT_map_0;
  
  struct HIGH_LINE_COUNTLINEITEM1_DELTA_entry {
    long O_ORDERKEY; STRING_TYPE L_SHIPMODE; long __av; 
    explicit HIGH_LINE_COUNTLINEITEM1_DELTA_entry() { /*O_ORDERKEY = 0L; L_SHIPMODE = ""; __av = 0L; */ }
    explicit HIGH_LINE_COUNTLINEITEM1_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { O_ORDERKEY = c0; L_SHIPMODE = c1; __av = c2; }
    HIGH_LINE_COUNTLINEITEM1_DELTA_entry(const HIGH_LINE_COUNTLINEITEM1_DELTA_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), L_SHIPMODE( other.L_SHIPMODE ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNTLINEITEM1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { O_ORDERKEY = c0; L_SHIPMODE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPMODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNTLINEITEM1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTLINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.L_SHIPMODE);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTLINEITEM1_DELTA_entry& x, const HIGH_LINE_COUNTLINEITEM1_DELTA_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.L_SHIPMODE == y.L_SHIPMODE;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNTLINEITEM1_DELTA_entry,long,
    HashIndex<HIGH_LINE_COUNTLINEITEM1_DELTA_entry,long,HIGH_LINE_COUNTLINEITEM1_DELTA_mapkey01_idxfn,true>
  > HIGH_LINE_COUNTLINEITEM1_DELTA_map;
  typedef HashIndex<HIGH_LINE_COUNTLINEITEM1_DELTA_entry,long,HIGH_LINE_COUNTLINEITEM1_DELTA_mapkey01_idxfn,true> HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01;
  
  struct HIGH_LINE_COUNTLINEITEM1_entry {
    long O_ORDERKEY; long __av; 
    explicit HIGH_LINE_COUNTLINEITEM1_entry() { /*O_ORDERKEY = 0L; __av = 0L; */ }
    explicit HIGH_LINE_COUNTLINEITEM1_entry(const long c0, const long c1) { O_ORDERKEY = c0; __av = c1; }
    HIGH_LINE_COUNTLINEITEM1_entry(const HIGH_LINE_COUNTLINEITEM1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNTLINEITEM1_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNTLINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTLINEITEM1_entry& x, const HIGH_LINE_COUNTLINEITEM1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNTLINEITEM1_entry,long,
    HashIndex<HIGH_LINE_COUNTLINEITEM1_entry,long,HIGH_LINE_COUNTLINEITEM1_mapkey0_idxfn,true>
  > HIGH_LINE_COUNTLINEITEM1_map;
  typedef HashIndex<HIGH_LINE_COUNTLINEITEM1_entry,long,HIGH_LINE_COUNTLINEITEM1_mapkey0_idxfn,true> HashIndex_HIGH_LINE_COUNTLINEITEM1_map_0;
  
  struct HIGH_LINE_COUNTLINEITEM2_DELTA_entry {
    long O_ORDERKEY; STRING_TYPE L_SHIPMODE; long __av; 
    explicit HIGH_LINE_COUNTLINEITEM2_DELTA_entry() { /*O_ORDERKEY = 0L; L_SHIPMODE = ""; __av = 0L; */ }
    explicit HIGH_LINE_COUNTLINEITEM2_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { O_ORDERKEY = c0; L_SHIPMODE = c1; __av = c2; }
    HIGH_LINE_COUNTLINEITEM2_DELTA_entry(const HIGH_LINE_COUNTLINEITEM2_DELTA_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), L_SHIPMODE( other.L_SHIPMODE ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNTLINEITEM2_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { O_ORDERKEY = c0; L_SHIPMODE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPMODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNTLINEITEM2_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTLINEITEM2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.L_SHIPMODE);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTLINEITEM2_DELTA_entry& x, const HIGH_LINE_COUNTLINEITEM2_DELTA_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.L_SHIPMODE == y.L_SHIPMODE;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNTLINEITEM2_DELTA_entry,long,
    HashIndex<HIGH_LINE_COUNTLINEITEM2_DELTA_entry,long,HIGH_LINE_COUNTLINEITEM2_DELTA_mapkey01_idxfn,true>
  > HIGH_LINE_COUNTLINEITEM2_DELTA_map;
  typedef HashIndex<HIGH_LINE_COUNTLINEITEM2_DELTA_entry,long,HIGH_LINE_COUNTLINEITEM2_DELTA_mapkey01_idxfn,true> HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01;
  
  struct HIGH_LINE_COUNTLINEITEM3_entry {
    long O_ORDERKEY; long __av; 
    explicit HIGH_LINE_COUNTLINEITEM3_entry() { /*O_ORDERKEY = 0L; __av = 0L; */ }
    explicit HIGH_LINE_COUNTLINEITEM3_entry(const long c0, const long c1) { O_ORDERKEY = c0; __av = c1; }
    HIGH_LINE_COUNTLINEITEM3_entry(const HIGH_LINE_COUNTLINEITEM3_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNTLINEITEM3_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNTLINEITEM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTLINEITEM3_entry& x, const HIGH_LINE_COUNTLINEITEM3_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNTLINEITEM3_entry,long,
    HashIndex<HIGH_LINE_COUNTLINEITEM3_entry,long,HIGH_LINE_COUNTLINEITEM3_mapkey0_idxfn,true>
  > HIGH_LINE_COUNTLINEITEM3_map;
  typedef HashIndex<HIGH_LINE_COUNTLINEITEM3_entry,long,HIGH_LINE_COUNTLINEITEM3_mapkey0_idxfn,true> HashIndex_HIGH_LINE_COUNTLINEITEM3_map_0;
  
  struct HIGH_LINE_COUNTORDERS1_DELTA_entry {
    long O_ORDERKEY; long __av; 
    explicit HIGH_LINE_COUNTORDERS1_DELTA_entry() { /*O_ORDERKEY = 0L; __av = 0L; */ }
    explicit HIGH_LINE_COUNTORDERS1_DELTA_entry(const long c0, const long c1) { O_ORDERKEY = c0; __av = c1; }
    HIGH_LINE_COUNTORDERS1_DELTA_entry(const HIGH_LINE_COUNTORDERS1_DELTA_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNTORDERS1_DELTA_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNTORDERS1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTORDERS1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTORDERS1_DELTA_entry& x, const HIGH_LINE_COUNTORDERS1_DELTA_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNTORDERS1_DELTA_entry,long,
    HashIndex<HIGH_LINE_COUNTORDERS1_DELTA_entry,long,HIGH_LINE_COUNTORDERS1_DELTA_mapkey0_idxfn,true>
  > HIGH_LINE_COUNTORDERS1_DELTA_map;
  typedef HashIndex<HIGH_LINE_COUNTORDERS1_DELTA_entry,long,HIGH_LINE_COUNTORDERS1_DELTA_mapkey0_idxfn,true> HashIndex_HIGH_LINE_COUNTORDERS1_DELTA_map_0;
  
  struct HIGH_LINE_COUNTORDERS1_entry {
    long O_ORDERKEY; STRING_TYPE L_SHIPMODE; long __av; 
    explicit HIGH_LINE_COUNTORDERS1_entry() { /*O_ORDERKEY = 0L; L_SHIPMODE = ""; __av = 0L; */ }
    explicit HIGH_LINE_COUNTORDERS1_entry(const long c0, const STRING_TYPE& c1, const long c2) { O_ORDERKEY = c0; L_SHIPMODE = c1; __av = c2; }
    HIGH_LINE_COUNTORDERS1_entry(const HIGH_LINE_COUNTORDERS1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), L_SHIPMODE( other.L_SHIPMODE ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNTORDERS1_entry& modify(const long c0, const STRING_TYPE& c1) { O_ORDERKEY = c0; L_SHIPMODE = c1;  return *this; }
    FORCE_INLINE HIGH_LINE_COUNTORDERS1_entry& modify0(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPMODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNTORDERS1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.L_SHIPMODE);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTORDERS1_entry& x, const HIGH_LINE_COUNTORDERS1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.L_SHIPMODE == y.L_SHIPMODE;
    }
  };
  
  struct HIGH_LINE_COUNTORDERS1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTORDERS1_entry& x, const HIGH_LINE_COUNTORDERS1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNTORDERS1_entry,long,
    HashIndex<HIGH_LINE_COUNTORDERS1_entry,long,HIGH_LINE_COUNTORDERS1_mapkey01_idxfn,true>,
    HashIndex<HIGH_LINE_COUNTORDERS1_entry,long,HIGH_LINE_COUNTORDERS1_mapkey0_idxfn,false>
  > HIGH_LINE_COUNTORDERS1_map;
  typedef HashIndex<HIGH_LINE_COUNTORDERS1_entry,long,HIGH_LINE_COUNTORDERS1_mapkey01_idxfn,true> HashIndex_HIGH_LINE_COUNTORDERS1_map_01;
  typedef HashIndex<HIGH_LINE_COUNTORDERS1_entry,long,HIGH_LINE_COUNTORDERS1_mapkey0_idxfn,false> HashIndex_HIGH_LINE_COUNTORDERS1_map_0;
  
  struct HIGH_LINE_COUNTORDERS2_entry {
    long O_ORDERKEY; STRING_TYPE L_SHIPMODE; long __av; 
    explicit HIGH_LINE_COUNTORDERS2_entry() { /*O_ORDERKEY = 0L; L_SHIPMODE = ""; __av = 0L; */ }
    explicit HIGH_LINE_COUNTORDERS2_entry(const long c0, const STRING_TYPE& c1, const long c2) { O_ORDERKEY = c0; L_SHIPMODE = c1; __av = c2; }
    HIGH_LINE_COUNTORDERS2_entry(const HIGH_LINE_COUNTORDERS2_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), L_SHIPMODE( other.L_SHIPMODE ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNTORDERS2_entry& modify(const long c0, const STRING_TYPE& c1) { O_ORDERKEY = c0; L_SHIPMODE = c1;  return *this; }
    FORCE_INLINE HIGH_LINE_COUNTORDERS2_entry& modify0(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPMODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNTORDERS2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTORDERS2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.L_SHIPMODE);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTORDERS2_entry& x, const HIGH_LINE_COUNTORDERS2_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.L_SHIPMODE == y.L_SHIPMODE;
    }
  };
  
  struct HIGH_LINE_COUNTORDERS2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTORDERS2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTORDERS2_entry& x, const HIGH_LINE_COUNTORDERS2_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNTORDERS2_entry,long,
    HashIndex<HIGH_LINE_COUNTORDERS2_entry,long,HIGH_LINE_COUNTORDERS2_mapkey01_idxfn,true>,
    HashIndex<HIGH_LINE_COUNTORDERS2_entry,long,HIGH_LINE_COUNTORDERS2_mapkey0_idxfn,false>
  > HIGH_LINE_COUNTORDERS2_map;
  typedef HashIndex<HIGH_LINE_COUNTORDERS2_entry,long,HIGH_LINE_COUNTORDERS2_mapkey01_idxfn,true> HashIndex_HIGH_LINE_COUNTORDERS2_map_01;
  typedef HashIndex<HIGH_LINE_COUNTORDERS2_entry,long,HIGH_LINE_COUNTORDERS2_mapkey0_idxfn,false> HashIndex_HIGH_LINE_COUNTORDERS2_map_0;
  
  struct HIGH_LINE_COUNTORDERS3_DELTA_entry {
    long O_ORDERKEY; long __av; 
    explicit HIGH_LINE_COUNTORDERS3_DELTA_entry() { /*O_ORDERKEY = 0L; __av = 0L; */ }
    explicit HIGH_LINE_COUNTORDERS3_DELTA_entry(const long c0, const long c1) { O_ORDERKEY = c0; __av = c1; }
    HIGH_LINE_COUNTORDERS3_DELTA_entry(const HIGH_LINE_COUNTORDERS3_DELTA_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNTORDERS3_DELTA_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNTORDERS3_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTORDERS3_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTORDERS3_DELTA_entry& x, const HIGH_LINE_COUNTORDERS3_DELTA_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNTORDERS3_DELTA_entry,long,
    HashIndex<HIGH_LINE_COUNTORDERS3_DELTA_entry,long,HIGH_LINE_COUNTORDERS3_DELTA_mapkey0_idxfn,true>
  > HIGH_LINE_COUNTORDERS3_DELTA_map;
  typedef HashIndex<HIGH_LINE_COUNTORDERS3_DELTA_entry,long,HIGH_LINE_COUNTORDERS3_DELTA_mapkey0_idxfn,true> HashIndex_HIGH_LINE_COUNTORDERS3_DELTA_map_0;
  
  struct LOW_LINE_COUNT_entry {
    STRING_TYPE L_SHIPMODE; long __av; 
    explicit LOW_LINE_COUNT_entry() { /*L_SHIPMODE = ""; __av = 0L; */ }
    explicit LOW_LINE_COUNT_entry(const STRING_TYPE& c0, const long c1) { L_SHIPMODE = c0; __av = c1; }
    LOW_LINE_COUNT_entry(const LOW_LINE_COUNT_entry& other) : L_SHIPMODE( other.L_SHIPMODE ), __av( other.__av ) {}
    FORCE_INLINE LOW_LINE_COUNT_entry& modify(const STRING_TYPE& c0) { L_SHIPMODE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPMODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct LOW_LINE_COUNT_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const LOW_LINE_COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_SHIPMODE);
      return h;
    }
    FORCE_INLINE static bool equals(const LOW_LINE_COUNT_entry& x, const LOW_LINE_COUNT_entry& y) {
      return x.L_SHIPMODE == y.L_SHIPMODE;
    }
  };
  
  typedef MultiHashMap<LOW_LINE_COUNT_entry,long,
    HashIndex<LOW_LINE_COUNT_entry,long,LOW_LINE_COUNT_mapkey0_idxfn,true>
  > LOW_LINE_COUNT_map;
  typedef HashIndex<LOW_LINE_COUNT_entry,long,LOW_LINE_COUNT_mapkey0_idxfn,true> HashIndex_LOW_LINE_COUNT_map_0;
  
  struct LOW_LINE_COUNTLINEITEM1_entry {
    long O_ORDERKEY; long __av; 
    explicit LOW_LINE_COUNTLINEITEM1_entry() { /*O_ORDERKEY = 0L; __av = 0L; */ }
    explicit LOW_LINE_COUNTLINEITEM1_entry(const long c0, const long c1) { O_ORDERKEY = c0; __av = c1; }
    LOW_LINE_COUNTLINEITEM1_entry(const LOW_LINE_COUNTLINEITEM1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE LOW_LINE_COUNTLINEITEM1_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct LOW_LINE_COUNTLINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const LOW_LINE_COUNTLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const LOW_LINE_COUNTLINEITEM1_entry& x, const LOW_LINE_COUNTLINEITEM1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<LOW_LINE_COUNTLINEITEM1_entry,long,
    HashIndex<LOW_LINE_COUNTLINEITEM1_entry,long,LOW_LINE_COUNTLINEITEM1_mapkey0_idxfn,true>
  > LOW_LINE_COUNTLINEITEM1_map;
  typedef HashIndex<LOW_LINE_COUNTLINEITEM1_entry,long,LOW_LINE_COUNTLINEITEM1_mapkey0_idxfn,true> HashIndex_LOW_LINE_COUNTLINEITEM1_map_0;
  
  struct LOW_LINE_COUNTORDERS1_DELTA_entry {
    long O_ORDERKEY; long __av; 
    explicit LOW_LINE_COUNTORDERS1_DELTA_entry() { /*O_ORDERKEY = 0L; __av = 0L; */ }
    explicit LOW_LINE_COUNTORDERS1_DELTA_entry(const long c0, const long c1) { O_ORDERKEY = c0; __av = c1; }
    LOW_LINE_COUNTORDERS1_DELTA_entry(const LOW_LINE_COUNTORDERS1_DELTA_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE LOW_LINE_COUNTORDERS1_DELTA_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct LOW_LINE_COUNTORDERS1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const LOW_LINE_COUNTORDERS1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const LOW_LINE_COUNTORDERS1_DELTA_entry& x, const LOW_LINE_COUNTORDERS1_DELTA_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<LOW_LINE_COUNTORDERS1_DELTA_entry,long,
    HashIndex<LOW_LINE_COUNTORDERS1_DELTA_entry,long,LOW_LINE_COUNTORDERS1_DELTA_mapkey0_idxfn,true>
  > LOW_LINE_COUNTORDERS1_DELTA_map;
  typedef HashIndex<LOW_LINE_COUNTORDERS1_DELTA_entry,long,LOW_LINE_COUNTORDERS1_DELTA_mapkey0_idxfn,true> HashIndex_LOW_LINE_COUNTORDERS1_DELTA_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const HIGH_LINE_COUNT_map& _HIGH_LINE_COUNT = get_HIGH_LINE_COUNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(HIGH_LINE_COUNT), _HIGH_LINE_COUNT, "\t");
      ar << "\n";
      const LOW_LINE_COUNT_map& _LOW_LINE_COUNT = get_LOW_LINE_COUNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(LOW_LINE_COUNT), _LOW_LINE_COUNT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const HIGH_LINE_COUNT_map& get_HIGH_LINE_COUNT() const {
      return HIGH_LINE_COUNT;
    
    }
    const LOW_LINE_COUNT_map& get_LOW_LINE_COUNT() const {
      return LOW_LINE_COUNT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    HIGH_LINE_COUNT_map HIGH_LINE_COUNT;
    LOW_LINE_COUNT_map LOW_LINE_COUNT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c6 = STRING_TYPE("1-URGENT");
      c5 = STRING_TYPE("2-HIGH");
      c1 = STRING_TYPE("SHIP");
      c3 = Udate(STRING_TYPE("1995-1-1"));
      c2 = Udate(STRING_TYPE("1994-1-1"));
      c4 = STRING_TYPE("MAIL");
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


        HIGH_LINE_COUNTLINEITEM2_DELTA.clear();
        HIGH_LINE_COUNTLINEITEM1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                long o_orderkey = DELTA_LINEITEM.orderkey[i];
                // long l_partkey = DELTA_LINEITEM.partkey[i];
                // long l_suppkey = DELTA_LINEITEM.suppkey[i];
                // long l_linenumber = DELTA_LINEITEM.linenumber[i];
                // DOUBLE_TYPE l_quantity = DELTA_LINEITEM.quantity[i];
                // DOUBLE_TYPE l_extendedprice = DELTA_LINEITEM.extendedprice[i];
                // DOUBLE_TYPE l_discount = DELTA_LINEITEM.discount[i];
                // DOUBLE_TYPE l_tax = DELTA_LINEITEM.tax[i];
                // STRING_TYPE l_returnflag = DELTA_LINEITEM.returnflag[i];
                // STRING_TYPE l_linestatus = DELTA_LINEITEM.linestatus[i];
                date l_shipdate = DELTA_LINEITEM.shipdate[i];
                date l_commitdate = DELTA_LINEITEM.commitdate[i];
                date l_receiptdate = DELTA_LINEITEM.receiptdate[i];
                // STRING_TYPE l_shipinstruct = DELTA_LINEITEM.shipinstruct[i];
                STRING_TYPE l_shipmode = DELTA_LINEITEM.shipmode[i];
                // STRING_TYPE l_comment = DELTA_LINEITEM.comment[i];
                long v1 = 1L;
                (/*if */(l_shipmode == c1 && l_receiptdate > l_commitdate && l_commitdate > l_shipdate && l_receiptdate >= c2 && c3 > l_receiptdate) ? HIGH_LINE_COUNTLINEITEM2_DELTA.addOrDelOnZero(se1.modify(o_orderkey,l_shipmode),v1) : (void)0);
                long v2 = 1L;
                (/*if */(l_shipmode == c4 && l_receiptdate > l_commitdate && l_commitdate > l_shipdate && l_receiptdate >= c2 && c3 > l_receiptdate) ? HIGH_LINE_COUNTLINEITEM1_DELTA.addOrDelOnZero(se2.modify(o_orderkey,l_shipmode),v2) : (void)0);

          }
        }

        {  // foreach
          const HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01* i3 = static_cast<HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01*>(HIGH_LINE_COUNTLINEITEM1_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01::IdxNode* n3; 
          HIGH_LINE_COUNTLINEITEM1_DELTA_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long o_orderkey = e3->O_ORDERKEY;
                STRING_TYPE l_shipmode = e3->L_SHIPMODE;
                long v3 = e3->__av;
                HIGH_LINE_COUNT.addOrDelOnZero(se3.modify(l_shipmode),(v3 * HIGH_LINE_COUNTLINEITEM1.getValueOrDefault(se4.modify(o_orderkey))));
              n3 = n3->nxt;
            }
          }
        }{  // foreach
          const HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01* i4 = static_cast<HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01*>(HIGH_LINE_COUNTLINEITEM2_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01::IdxNode* n4; 
          HIGH_LINE_COUNTLINEITEM2_DELTA_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long o_orderkey = e4->O_ORDERKEY;
                STRING_TYPE l_shipmode = e4->L_SHIPMODE;
                long v4 = e4->__av;
                HIGH_LINE_COUNT.addOrDelOnZero(se3.modify(l_shipmode),(v4 * HIGH_LINE_COUNTLINEITEM1.getValueOrDefault(se5.modify(o_orderkey))));
              n4 = n4->nxt;
            }
          }
        }{  // foreach
          const HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01* i5 = static_cast<HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01*>(HIGH_LINE_COUNTLINEITEM1_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01::IdxNode* n5; 
          HIGH_LINE_COUNTLINEITEM1_DELTA_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long o_orderkey = e5->O_ORDERKEY;
                STRING_TYPE l_shipmode = e5->L_SHIPMODE;
                long v5 = e5->__av;
                HIGH_LINE_COUNT.addOrDelOnZero(se3.modify(l_shipmode),(v5 * HIGH_LINE_COUNTLINEITEM3.getValueOrDefault(se6.modify(o_orderkey))));
              n5 = n5->nxt;
            }
          }
        }{  // foreach
          const HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01* i6 = static_cast<HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01*>(HIGH_LINE_COUNTLINEITEM2_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01::IdxNode* n6; 
          HIGH_LINE_COUNTLINEITEM2_DELTA_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long o_orderkey = e6->O_ORDERKEY;
                STRING_TYPE l_shipmode = e6->L_SHIPMODE;
                long v6 = e6->__av;
                HIGH_LINE_COUNT.addOrDelOnZero(se3.modify(l_shipmode),(v6 * HIGH_LINE_COUNTLINEITEM3.getValueOrDefault(se7.modify(o_orderkey))));
              n6 = n6->nxt;
            }
          }
        }{  // foreach
          const HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01* i7 = static_cast<HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01*>(HIGH_LINE_COUNTLINEITEM1_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01::IdxNode* n7; 
          HIGH_LINE_COUNTLINEITEM1_DELTA_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long o_orderkey = e7->O_ORDERKEY;
                STRING_TYPE l_shipmode = e7->L_SHIPMODE;
                long v7 = e7->__av;
                HIGH_LINE_COUNTORDERS1.addOrDelOnZero(se8.modify(o_orderkey,l_shipmode),v7);
              n7 = n7->nxt;
            }
          }
        }{  // foreach
          const HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01* i8 = static_cast<HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01*>(HIGH_LINE_COUNTLINEITEM2_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01::IdxNode* n8; 
          HIGH_LINE_COUNTLINEITEM2_DELTA_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long o_orderkey = e8->O_ORDERKEY;
                STRING_TYPE l_shipmode = e8->L_SHIPMODE;
                long v8 = e8->__av;
                HIGH_LINE_COUNTORDERS2.addOrDelOnZero(se9.modify(o_orderkey,l_shipmode),v8);
              n8 = n8->nxt;
            }
          }
        }{  // foreach
          const HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01* i9 = static_cast<HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01*>(HIGH_LINE_COUNTLINEITEM1_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTLINEITEM1_DELTA_map_01::IdxNode* n9; 
          HIGH_LINE_COUNTLINEITEM1_DELTA_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long o_orderkey = e9->O_ORDERKEY;
                STRING_TYPE l_shipmode = e9->L_SHIPMODE;
                long v9 = e9->__av;
                LOW_LINE_COUNT.addOrDelOnZero(se10.modify(l_shipmode),(v9 * LOW_LINE_COUNTLINEITEM1.getValueOrDefault(se11.modify(o_orderkey))));
              n9 = n9->nxt;
            }
          }
        }{  // foreach
          const HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01* i10 = static_cast<HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01*>(HIGH_LINE_COUNTLINEITEM2_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTLINEITEM2_DELTA_map_01::IdxNode* n10; 
          HIGH_LINE_COUNTLINEITEM2_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long o_orderkey = e10->O_ORDERKEY;
                STRING_TYPE l_shipmode = e10->L_SHIPMODE;
                long v10 = e10->__av;
                LOW_LINE_COUNT.addOrDelOnZero(se10.modify(l_shipmode),(v10 * LOW_LINE_COUNTLINEITEM1.getValueOrDefault(se12.modify(o_orderkey))));
              n10 = n10->nxt;
            }
          }
        }
      }
    }
    void on_batch_update_ORDERS(TPCHOrdersBatch& DELTA_ORDERS) {
      {  
        if (tS > 0) { tS += DELTA_ORDERS.size; return; }         
        tLastN += DELTA_ORDERS.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_ORDERS.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_ORDERS.size;

        HIGH_LINE_COUNTORDERS3_DELTA.clear();
        HIGH_LINE_COUNTORDERS1_DELTA.clear();
        LOW_LINE_COUNTORDERS1_DELTA.clear();        
        {
          for (size_t i = 0; i < DELTA_ORDERS.size; i++)
          {
                long o_orderkey = DELTA_ORDERS.orderkey[i];
                // long o_custkey = DELTA_ORDERS.custkey[i];
                // STRING_TYPE o_orderstatus = DELTA_ORDERS.orderstatus[i];
                // DOUBLE_TYPE o_totalprice = DELTA_ORDERS.totalprice[i];
                // date o_orderdate = DELTA_ORDERS.orderdate[i];
                STRING_TYPE lift1 = DELTA_ORDERS.orderpriority[i];
                // STRING_TYPE o_clerk = DELTA_ORDERS.clerk[i];
                // long o_shippriority = DELTA_ORDERS.shippriority[i];
                // STRING_TYPE o_comment = DELTA_ORDERS.comment[i];
                long v11 = 1L;
                (/*if */(lift1 == c5) ? HIGH_LINE_COUNTORDERS3_DELTA.addOrDelOnZero(se13.modify(o_orderkey),v11) : (void)0);
                long v12 = 1L;
                (/*if */(lift1 == c6) ? HIGH_LINE_COUNTORDERS1_DELTA.addOrDelOnZero(se14.modify(o_orderkey),v12) : (void)0);
                long v13 = 1L;
                (/*if */(c6 != lift1 && c5 != lift1) ? LOW_LINE_COUNTORDERS1_DELTA.addOrDelOnZero(se15.modify(o_orderkey),v13) : (void)0);

          }
        }
        {  // foreach
          const HashIndex_HIGH_LINE_COUNTORDERS1_DELTA_map_0* i14 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS1_DELTA_map_0*>(HIGH_LINE_COUNTORDERS1_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTORDERS1_DELTA_map_0::IdxNode* n14; 
          HIGH_LINE_COUNTORDERS1_DELTA_entry* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
                long o_orderkey = e14->O_ORDERKEY;
                long v14 = e14->__av;
                { //slice 
                  const HashIndex_HIGH_LINE_COUNTORDERS1_map_0* i15 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS1_map_0*>(HIGH_LINE_COUNTORDERS1.index[1]);
                  const HASH_RES_t h1 = HIGH_LINE_COUNTORDERS1_mapkey0_idxfn::hash(se17.modify0(o_orderkey));
                  HashIndex_HIGH_LINE_COUNTORDERS1_map_0::IdxNode* n15 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS1_map_0::IdxNode*>(i15->slice(se17, h1));
                  HIGH_LINE_COUNTORDERS1_entry* e15;
                 
                  if (n15 && (e15 = n15->obj)) {
                    do {                
                      STRING_TYPE l_shipmode = e15->L_SHIPMODE;
                      long v15 = e15->__av;
                      HIGH_LINE_COUNT.addOrDelOnZero(se16.modify(l_shipmode),(v14 * v15));
                      n15 = n15->nxt;
                    } while (n15 && (e15 = n15->obj) && h1 == n15->hash &&  HIGH_LINE_COUNTORDERS1_mapkey0_idxfn::equals(se17, *e15)); 
                  }
                }
              n14 = n14->nxt;
            }
          }
        }{  // foreach
          const HashIndex_HIGH_LINE_COUNTORDERS1_DELTA_map_0* i16 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS1_DELTA_map_0*>(HIGH_LINE_COUNTORDERS1_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTORDERS1_DELTA_map_0::IdxNode* n16; 
          HIGH_LINE_COUNTORDERS1_DELTA_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long o_orderkey = e16->O_ORDERKEY;
                long v16 = e16->__av;
                { //slice 
                  const HashIndex_HIGH_LINE_COUNTORDERS2_map_0* i17 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS2_map_0*>(HIGH_LINE_COUNTORDERS2.index[1]);
                  const HASH_RES_t h2 = HIGH_LINE_COUNTORDERS2_mapkey0_idxfn::hash(se18.modify0(o_orderkey));
                  HashIndex_HIGH_LINE_COUNTORDERS2_map_0::IdxNode* n17 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS2_map_0::IdxNode*>(i17->slice(se18, h2));
                  HIGH_LINE_COUNTORDERS2_entry* e17;
                 
                  if (n17 && (e17 = n17->obj)) {
                    do {                
                      STRING_TYPE l_shipmode = e17->L_SHIPMODE;
                      long v17 = e17->__av;
                      HIGH_LINE_COUNT.addOrDelOnZero(se16.modify(l_shipmode),(v16 * v17));
                      n17 = n17->nxt;
                    } while (n17 && (e17 = n17->obj) && h2 == n17->hash &&  HIGH_LINE_COUNTORDERS2_mapkey0_idxfn::equals(se18, *e17)); 
                  }
                }
              n16 = n16->nxt;
            }
          }
        }{  // foreach
          const HashIndex_HIGH_LINE_COUNTORDERS3_DELTA_map_0* i18 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS3_DELTA_map_0*>(HIGH_LINE_COUNTORDERS3_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTORDERS3_DELTA_map_0::IdxNode* n18; 
          HIGH_LINE_COUNTORDERS3_DELTA_entry* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
                long o_orderkey = e18->O_ORDERKEY;
                long v18 = e18->__av;
                { //slice 
                  const HashIndex_HIGH_LINE_COUNTORDERS1_map_0* i19 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS1_map_0*>(HIGH_LINE_COUNTORDERS1.index[1]);
                  const HASH_RES_t h3 = HIGH_LINE_COUNTORDERS1_mapkey0_idxfn::hash(se19.modify0(o_orderkey));
                  HashIndex_HIGH_LINE_COUNTORDERS1_map_0::IdxNode* n19 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS1_map_0::IdxNode*>(i19->slice(se19, h3));
                  HIGH_LINE_COUNTORDERS1_entry* e19;
                 
                  if (n19 && (e19 = n19->obj)) {
                    do {                
                      STRING_TYPE l_shipmode = e19->L_SHIPMODE;
                      long v19 = e19->__av;
                      HIGH_LINE_COUNT.addOrDelOnZero(se16.modify(l_shipmode),(v18 * v19));
                      n19 = n19->nxt;
                    } while (n19 && (e19 = n19->obj) && h3 == n19->hash &&  HIGH_LINE_COUNTORDERS1_mapkey0_idxfn::equals(se19, *e19)); 
                  }
                }
              n18 = n18->nxt;
            }
          }
        }{  // foreach
          const HashIndex_HIGH_LINE_COUNTORDERS3_DELTA_map_0* i20 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS3_DELTA_map_0*>(HIGH_LINE_COUNTORDERS3_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTORDERS3_DELTA_map_0::IdxNode* n20; 
          HIGH_LINE_COUNTORDERS3_DELTA_entry* e20;
        
          for (size_t i = 0; i < i20->size_; i++)
          {
            n20 = i20->buckets_ + i;
            while (n20 && (e20 = n20->obj))
            {
                long o_orderkey = e20->O_ORDERKEY;
                long v20 = e20->__av;
                { //slice 
                  const HashIndex_HIGH_LINE_COUNTORDERS2_map_0* i21 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS2_map_0*>(HIGH_LINE_COUNTORDERS2.index[1]);
                  const HASH_RES_t h4 = HIGH_LINE_COUNTORDERS2_mapkey0_idxfn::hash(se20.modify0(o_orderkey));
                  HashIndex_HIGH_LINE_COUNTORDERS2_map_0::IdxNode* n21 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS2_map_0::IdxNode*>(i21->slice(se20, h4));
                  HIGH_LINE_COUNTORDERS2_entry* e21;
                 
                  if (n21 && (e21 = n21->obj)) {
                    do {                
                      STRING_TYPE l_shipmode = e21->L_SHIPMODE;
                      long v21 = e21->__av;
                      HIGH_LINE_COUNT.addOrDelOnZero(se16.modify(l_shipmode),(v20 * v21));
                      n21 = n21->nxt;
                    } while (n21 && (e21 = n21->obj) && h4 == n21->hash &&  HIGH_LINE_COUNTORDERS2_mapkey0_idxfn::equals(se20, *e21)); 
                  }
                }
              n20 = n20->nxt;
            }
          }
        }{  // foreach
          const HashIndex_HIGH_LINE_COUNTORDERS1_DELTA_map_0* i22 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS1_DELTA_map_0*>(HIGH_LINE_COUNTORDERS1_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTORDERS1_DELTA_map_0::IdxNode* n22; 
          HIGH_LINE_COUNTORDERS1_DELTA_entry* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
                long o_orderkey = e22->O_ORDERKEY;
                long v22 = e22->__av;
                HIGH_LINE_COUNTLINEITEM1.addOrDelOnZero(se21.modify(o_orderkey),v22);
              n22 = n22->nxt;
            }
          }
        }{  // foreach
          const HashIndex_HIGH_LINE_COUNTORDERS3_DELTA_map_0* i23 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS3_DELTA_map_0*>(HIGH_LINE_COUNTORDERS3_DELTA.index[0]);
          HashIndex_HIGH_LINE_COUNTORDERS3_DELTA_map_0::IdxNode* n23; 
          HIGH_LINE_COUNTORDERS3_DELTA_entry* e23;
        
          for (size_t i = 0; i < i23->size_; i++)
          {
            n23 = i23->buckets_ + i;
            while (n23 && (e23 = n23->obj))
            {
                long o_orderkey = e23->O_ORDERKEY;
                long v23 = e23->__av;
                HIGH_LINE_COUNTLINEITEM3.addOrDelOnZero(se22.modify(o_orderkey),v23);
              n23 = n23->nxt;
            }
          }
        }{  // foreach
          const HashIndex_LOW_LINE_COUNTORDERS1_DELTA_map_0* i24 = static_cast<HashIndex_LOW_LINE_COUNTORDERS1_DELTA_map_0*>(LOW_LINE_COUNTORDERS1_DELTA.index[0]);
          HashIndex_LOW_LINE_COUNTORDERS1_DELTA_map_0::IdxNode* n24; 
          LOW_LINE_COUNTORDERS1_DELTA_entry* e24;
        
          for (size_t i = 0; i < i24->size_; i++)
          {
            n24 = i24->buckets_ + i;
            while (n24 && (e24 = n24->obj))
            {
                long o_orderkey = e24->O_ORDERKEY;
                long v24 = e24->__av;
                { //slice 
                  const HashIndex_HIGH_LINE_COUNTORDERS1_map_0* i25 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS1_map_0*>(HIGH_LINE_COUNTORDERS1.index[1]);
                  const HASH_RES_t h5 = HIGH_LINE_COUNTORDERS1_mapkey0_idxfn::hash(se24.modify0(o_orderkey));
                  HashIndex_HIGH_LINE_COUNTORDERS1_map_0::IdxNode* n25 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS1_map_0::IdxNode*>(i25->slice(se24, h5));
                  HIGH_LINE_COUNTORDERS1_entry* e25;
                 
                  if (n25 && (e25 = n25->obj)) {
                    do {                
                      STRING_TYPE l_shipmode = e25->L_SHIPMODE;
                      long v25 = e25->__av;
                      LOW_LINE_COUNT.addOrDelOnZero(se23.modify(l_shipmode),(v24 * v25));
                      n25 = n25->nxt;
                    } while (n25 && (e25 = n25->obj) && h5 == n25->hash &&  HIGH_LINE_COUNTORDERS1_mapkey0_idxfn::equals(se24, *e25)); 
                  }
                }
              n24 = n24->nxt;
            }
          }
        }{  // foreach
          const HashIndex_LOW_LINE_COUNTORDERS1_DELTA_map_0* i26 = static_cast<HashIndex_LOW_LINE_COUNTORDERS1_DELTA_map_0*>(LOW_LINE_COUNTORDERS1_DELTA.index[0]);
          HashIndex_LOW_LINE_COUNTORDERS1_DELTA_map_0::IdxNode* n26; 
          LOW_LINE_COUNTORDERS1_DELTA_entry* e26;
        
          for (size_t i = 0; i < i26->size_; i++)
          {
            n26 = i26->buckets_ + i;
            while (n26 && (e26 = n26->obj))
            {
                long o_orderkey = e26->O_ORDERKEY;
                long v26 = e26->__av;
                { //slice 
                  const HashIndex_HIGH_LINE_COUNTORDERS2_map_0* i27 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS2_map_0*>(HIGH_LINE_COUNTORDERS2.index[1]);
                  const HASH_RES_t h6 = HIGH_LINE_COUNTORDERS2_mapkey0_idxfn::hash(se25.modify0(o_orderkey));
                  HashIndex_HIGH_LINE_COUNTORDERS2_map_0::IdxNode* n27 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS2_map_0::IdxNode*>(i27->slice(se25, h6));
                  HIGH_LINE_COUNTORDERS2_entry* e27;
                 
                  if (n27 && (e27 = n27->obj)) {
                    do {                
                      STRING_TYPE l_shipmode = e27->L_SHIPMODE;
                      long v27 = e27->__av;
                      LOW_LINE_COUNT.addOrDelOnZero(se23.modify(l_shipmode),(v26 * v27));
                      n27 = n27->nxt;
                    } while (n27 && (e27 = n27->obj) && h6 == n27->hash &&  HIGH_LINE_COUNTORDERS2_mapkey0_idxfn::equals(se25, *e27)); 
                  }
                }
              n26 = n26->nxt;
            }
          }
        }{  // foreach
          const HashIndex_LOW_LINE_COUNTORDERS1_DELTA_map_0* i28 = static_cast<HashIndex_LOW_LINE_COUNTORDERS1_DELTA_map_0*>(LOW_LINE_COUNTORDERS1_DELTA.index[0]);
          HashIndex_LOW_LINE_COUNTORDERS1_DELTA_map_0::IdxNode* n28; 
          LOW_LINE_COUNTORDERS1_DELTA_entry* e28;
        
          for (size_t i = 0; i < i28->size_; i++)
          {
            n28 = i28->buckets_ + i;
            while (n28 && (e28 = n28->obj))
            {
                long o_orderkey = e28->O_ORDERKEY;
                long v28 = e28->__av;
                LOW_LINE_COUNTLINEITEM1.addOrDelOnZero(se26.modify(o_orderkey),v28);
              n28 = n28->nxt;
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
    HIGH_LINE_COUNTLINEITEM2_DELTA_entry se1;
    HIGH_LINE_COUNTLINEITEM1_DELTA_entry se2;
    HIGH_LINE_COUNT_entry se3;
    HIGH_LINE_COUNTLINEITEM1_entry se4;
    HIGH_LINE_COUNTLINEITEM1_entry se5;
    HIGH_LINE_COUNTLINEITEM3_entry se6;
    HIGH_LINE_COUNTLINEITEM3_entry se7;
    HIGH_LINE_COUNTORDERS1_entry se8;
    HIGH_LINE_COUNTORDERS2_entry se9;
    LOW_LINE_COUNT_entry se10;
    LOW_LINE_COUNTLINEITEM1_entry se11;
    LOW_LINE_COUNTLINEITEM1_entry se12;
    HIGH_LINE_COUNTORDERS3_DELTA_entry se13;
    HIGH_LINE_COUNTORDERS1_DELTA_entry se14;
    LOW_LINE_COUNTORDERS1_DELTA_entry se15;
    HIGH_LINE_COUNT_entry se16;
    HIGH_LINE_COUNTORDERS1_entry se17;
    HIGH_LINE_COUNTORDERS2_entry se18;
    HIGH_LINE_COUNTORDERS1_entry se19;
    HIGH_LINE_COUNTORDERS2_entry se20;
    HIGH_LINE_COUNTLINEITEM1_entry se21;
    HIGH_LINE_COUNTLINEITEM3_entry se22;
    LOW_LINE_COUNT_entry se23;
    HIGH_LINE_COUNTORDERS1_entry se24;
    HIGH_LINE_COUNTORDERS2_entry se25;
    LOW_LINE_COUNTLINEITEM1_entry se26;
  
    /* Data structures used for storing materialized views */
    HIGH_LINE_COUNTLINEITEM1_DELTA_map HIGH_LINE_COUNTLINEITEM1_DELTA;
    HIGH_LINE_COUNTLINEITEM1_map HIGH_LINE_COUNTLINEITEM1;
    HIGH_LINE_COUNTLINEITEM2_DELTA_map HIGH_LINE_COUNTLINEITEM2_DELTA;
    HIGH_LINE_COUNTLINEITEM3_map HIGH_LINE_COUNTLINEITEM3;
    HIGH_LINE_COUNTORDERS1_DELTA_map HIGH_LINE_COUNTORDERS1_DELTA;
    HIGH_LINE_COUNTORDERS1_map HIGH_LINE_COUNTORDERS1;
    HIGH_LINE_COUNTORDERS2_map HIGH_LINE_COUNTORDERS2;
    HIGH_LINE_COUNTORDERS3_DELTA_map HIGH_LINE_COUNTORDERS3_DELTA;
    LOW_LINE_COUNTLINEITEM1_map LOW_LINE_COUNTLINEITEM1;
    LOW_LINE_COUNTORDERS1_DELTA_map LOW_LINE_COUNTORDERS1_DELTA;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_ORDERS_map DELTA_ORDERS;
    
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c1;
    /*const static*/ long c3;
    /*const static*/ long c2;
    /*const static*/ STRING_TYPE c4;
  
  };

}
