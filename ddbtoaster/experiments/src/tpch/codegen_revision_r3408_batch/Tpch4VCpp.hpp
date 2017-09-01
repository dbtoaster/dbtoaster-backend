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
  
  struct ORDER_COUNT_entry {
    STRING_TYPE O_ORDERPRIORITY; long __av; 
    explicit ORDER_COUNT_entry() { /*O_ORDERPRIORITY = ""; __av = 0L; */ }
    explicit ORDER_COUNT_entry(const STRING_TYPE& c0, const long c1) { O_ORDERPRIORITY = c0; __av = c1; }
    ORDER_COUNT_entry(const ORDER_COUNT_entry& other) : O_ORDERPRIORITY( other.O_ORDERPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE ORDER_COUNT_entry& modify(const STRING_TYPE& c0) { O_ORDERPRIORITY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct ORDER_COUNT_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNT_entry& x, const ORDER_COUNT_entry& y) {
      return x.O_ORDERPRIORITY == y.O_ORDERPRIORITY;
    }
  };
  
  typedef MultiHashMap<ORDER_COUNT_entry,long,
    HashIndex<ORDER_COUNT_entry,long,ORDER_COUNT_mapkey0_idxfn,true>
  > ORDER_COUNT_map;
  typedef HashIndex<ORDER_COUNT_entry,long,ORDER_COUNT_mapkey0_idxfn,true> HashIndex_ORDER_COUNT_map_0;
  
  struct ORDER_COUNTLINEITEM1_DOMAIN1_entry {
    long O_ORDERKEY; long __av; 
    explicit ORDER_COUNTLINEITEM1_DOMAIN1_entry() { /*O_ORDERKEY = 0L; __av = 0L; */ }
    explicit ORDER_COUNTLINEITEM1_DOMAIN1_entry(const long c0, const long c1) { O_ORDERKEY = c0; __av = c1; }
    ORDER_COUNTLINEITEM1_DOMAIN1_entry(const ORDER_COUNTLINEITEM1_DOMAIN1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE ORDER_COUNTLINEITEM1_DOMAIN1_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct ORDER_COUNTLINEITEM1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNTLINEITEM1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNTLINEITEM1_DOMAIN1_entry& x, const ORDER_COUNTLINEITEM1_DOMAIN1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<ORDER_COUNTLINEITEM1_DOMAIN1_entry,long,
    HashIndex<ORDER_COUNTLINEITEM1_DOMAIN1_entry,long,ORDER_COUNTLINEITEM1_DOMAIN1_mapkey0_idxfn,true>
  > ORDER_COUNTLINEITEM1_DOMAIN1_map;
  typedef HashIndex<ORDER_COUNTLINEITEM1_DOMAIN1_entry,long,ORDER_COUNTLINEITEM1_DOMAIN1_mapkey0_idxfn,true> HashIndex_ORDER_COUNTLINEITEM1_DOMAIN1_map_0;
  
  struct ORDER_COUNTLINEITEM1_entry {
    long O_ORDERKEY; STRING_TYPE O_ORDERPRIORITY; long __av; 
    explicit ORDER_COUNTLINEITEM1_entry() { /*O_ORDERKEY = 0L; O_ORDERPRIORITY = ""; __av = 0L; */ }
    explicit ORDER_COUNTLINEITEM1_entry(const long c0, const STRING_TYPE& c1, const long c2) { O_ORDERKEY = c0; O_ORDERPRIORITY = c1; __av = c2; }
    ORDER_COUNTLINEITEM1_entry(const ORDER_COUNTLINEITEM1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), O_ORDERPRIORITY( other.O_ORDERPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE ORDER_COUNTLINEITEM1_entry& modify(const long c0, const STRING_TYPE& c1) { O_ORDERKEY = c0; O_ORDERPRIORITY = c1;  return *this; }
    FORCE_INLINE ORDER_COUNTLINEITEM1_entry& modify0(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct ORDER_COUNTLINEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNTLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.O_ORDERPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNTLINEITEM1_entry& x, const ORDER_COUNTLINEITEM1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.O_ORDERPRIORITY == y.O_ORDERPRIORITY;
    }
  };
  
  struct ORDER_COUNTLINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNTLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNTLINEITEM1_entry& x, const ORDER_COUNTLINEITEM1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<ORDER_COUNTLINEITEM1_entry,long,
    HashIndex<ORDER_COUNTLINEITEM1_entry,long,ORDER_COUNTLINEITEM1_mapkey01_idxfn,true>,
    HashIndex<ORDER_COUNTLINEITEM1_entry,long,ORDER_COUNTLINEITEM1_mapkey0_idxfn,false>
  > ORDER_COUNTLINEITEM1_map;
  typedef HashIndex<ORDER_COUNTLINEITEM1_entry,long,ORDER_COUNTLINEITEM1_mapkey01_idxfn,true> HashIndex_ORDER_COUNTLINEITEM1_map_01;
  typedef HashIndex<ORDER_COUNTLINEITEM1_entry,long,ORDER_COUNTLINEITEM1_mapkey0_idxfn,false> HashIndex_ORDER_COUNTLINEITEM1_map_0;
  
  struct ORDER_COUNTLINEITEM1_E1_2_DELTA_entry {
    long O_ORDERKEY; long __av; 
    explicit ORDER_COUNTLINEITEM1_E1_2_DELTA_entry() { /*O_ORDERKEY = 0L; __av = 0L; */ }
    explicit ORDER_COUNTLINEITEM1_E1_2_DELTA_entry(const long c0, const long c1) { O_ORDERKEY = c0; __av = c1; }
    ORDER_COUNTLINEITEM1_E1_2_DELTA_entry(const ORDER_COUNTLINEITEM1_E1_2_DELTA_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE ORDER_COUNTLINEITEM1_E1_2_DELTA_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct ORDER_COUNTLINEITEM1_E1_2_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNTLINEITEM1_E1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNTLINEITEM1_E1_2_DELTA_entry& x, const ORDER_COUNTLINEITEM1_E1_2_DELTA_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<ORDER_COUNTLINEITEM1_E1_2_DELTA_entry,long,
    HashIndex<ORDER_COUNTLINEITEM1_E1_2_DELTA_entry,long,ORDER_COUNTLINEITEM1_E1_2_DELTA_mapkey0_idxfn,true>
  > ORDER_COUNTLINEITEM1_E1_2_DELTA_map;
  typedef HashIndex<ORDER_COUNTLINEITEM1_E1_2_DELTA_entry,long,ORDER_COUNTLINEITEM1_E1_2_DELTA_mapkey0_idxfn,true> HashIndex_ORDER_COUNTLINEITEM1_E1_2_DELTA_map_0;
  
  struct ORDER_COUNTORDERS1_DELTA_entry {
    long O_ORDERKEY; STRING_TYPE O_ORDERPRIORITY; long __av; 
    explicit ORDER_COUNTORDERS1_DELTA_entry() { /*O_ORDERKEY = 0L; O_ORDERPRIORITY = ""; __av = 0L; */ }
    explicit ORDER_COUNTORDERS1_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { O_ORDERKEY = c0; O_ORDERPRIORITY = c1; __av = c2; }
    ORDER_COUNTORDERS1_DELTA_entry(const ORDER_COUNTORDERS1_DELTA_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), O_ORDERPRIORITY( other.O_ORDERPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE ORDER_COUNTORDERS1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { O_ORDERKEY = c0; O_ORDERPRIORITY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct ORDER_COUNTORDERS1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNTORDERS1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.O_ORDERPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNTORDERS1_DELTA_entry& x, const ORDER_COUNTORDERS1_DELTA_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.O_ORDERPRIORITY == y.O_ORDERPRIORITY;
    }
  };
  
  typedef MultiHashMap<ORDER_COUNTORDERS1_DELTA_entry,long,
    HashIndex<ORDER_COUNTORDERS1_DELTA_entry,long,ORDER_COUNTORDERS1_DELTA_mapkey01_idxfn,true>
  > ORDER_COUNTORDERS1_DELTA_map;
  typedef HashIndex<ORDER_COUNTORDERS1_DELTA_entry,long,ORDER_COUNTORDERS1_DELTA_mapkey01_idxfn,true> HashIndex_ORDER_COUNTORDERS1_DELTA_map_01;
  
  struct ORDER_COUNTORDERS1_E1_1_entry {
    long O_ORDERKEY; long __av; 
    explicit ORDER_COUNTORDERS1_E1_1_entry() { /*O_ORDERKEY = 0L; __av = 0L; */ }
    explicit ORDER_COUNTORDERS1_E1_1_entry(const long c0, const long c1) { O_ORDERKEY = c0; __av = c1; }
    ORDER_COUNTORDERS1_E1_1_entry(const ORDER_COUNTORDERS1_E1_1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE ORDER_COUNTORDERS1_E1_1_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct ORDER_COUNTORDERS1_E1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNTORDERS1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNTORDERS1_E1_1_entry& x, const ORDER_COUNTORDERS1_E1_1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<ORDER_COUNTORDERS1_E1_1_entry,long,
    HashIndex<ORDER_COUNTORDERS1_E1_1_entry,long,ORDER_COUNTORDERS1_E1_1_mapkey0_idxfn,true>
  > ORDER_COUNTORDERS1_E1_1_map;
  typedef HashIndex<ORDER_COUNTORDERS1_E1_1_entry,long,ORDER_COUNTORDERS1_E1_1_mapkey0_idxfn,true> HashIndex_ORDER_COUNTORDERS1_E1_1_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const ORDER_COUNT_map& _ORDER_COUNT = get_ORDER_COUNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(ORDER_COUNT), _ORDER_COUNT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const ORDER_COUNT_map& get_ORDER_COUNT() const {
      return ORDER_COUNT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    ORDER_COUNT_map ORDER_COUNT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c1 = Udate(STRING_TYPE("1993-10-1"));
      c2 = Udate(STRING_TYPE("1993-7-1"));
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

        ORDER_COUNTLINEITEM1_E1_2_DELTA.clear();
        ORDER_COUNTLINEITEM1_DOMAIN1.clear();        
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
                // date l_shipdate = DELTA_LINEITEM.shipdate[i];
                date l_commitdate = DELTA_LINEITEM.commitdate[i];
                date l_receiptdate = DELTA_LINEITEM.receiptdate[i];
                // STRING_TYPE l_shipinstruct = DELTA_LINEITEM.shipinstruct[i];
                // STRING_TYPE l_shipmode = DELTA_LINEITEM.shipmode[i];
                // STRING_TYPE l_comment = DELTA_LINEITEM.comment[i];
                long v1 = 1L;
                (/*if */(l_receiptdate > l_commitdate) ? ORDER_COUNTLINEITEM1_E1_2_DELTA.addOrDelOnZero(se1.modify(o_orderkey),v1) : (void)0);
                long v2 = 1L;
                (/*if */(l_receiptdate > l_commitdate) ? ORDER_COUNTLINEITEM1_DOMAIN1.addOrDelOnZero(se2.modify(o_orderkey),(v2 != 0 ? 1L : 0L)) : (void)0);
          }
        }

        {  // foreach
          const HashIndex_ORDER_COUNTLINEITEM1_DOMAIN1_map_0* i3 = static_cast<HashIndex_ORDER_COUNTLINEITEM1_DOMAIN1_map_0*>(ORDER_COUNTLINEITEM1_DOMAIN1.index[0]);
          HashIndex_ORDER_COUNTLINEITEM1_DOMAIN1_map_0::IdxNode* n3; 
          ORDER_COUNTLINEITEM1_DOMAIN1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long o_orderkey = e3->O_ORDERKEY;
                long v3 = e3->__av;
                { //slice 
                  const HashIndex_ORDER_COUNTLINEITEM1_map_0* i4 = static_cast<HashIndex_ORDER_COUNTLINEITEM1_map_0*>(ORDER_COUNTLINEITEM1.index[1]);
                  const HASH_RES_t h1 = ORDER_COUNTLINEITEM1_mapkey0_idxfn::hash(se6.modify0(o_orderkey));
                  HashIndex_ORDER_COUNTLINEITEM1_map_0::IdxNode* n4 = static_cast<HashIndex_ORDER_COUNTLINEITEM1_map_0::IdxNode*>(i4->slice(se6, h1));
                  ORDER_COUNTLINEITEM1_entry* e4;
                 
                  if (n4 && (e4 = n4->obj)) {
                    do {                
                      STRING_TYPE o_orderpriority = e4->O_ORDERPRIORITY;
                      long v4 = e4->__av;
                      ORDER_COUNT.addOrDelOnZero(se3.modify(o_orderpriority),((v3 != 0 ? 1L : 0L) * (v4 * ((ORDER_COUNTORDERS1_E1_1.getValueOrDefault(se4.modify(o_orderkey)) + ORDER_COUNTLINEITEM1_E1_2_DELTA.getValueOrDefault(se5.modify(o_orderkey))) != 0 ? 1L : 0L))));
                      n4 = n4->nxt;
                    } while (n4 && (e4 = n4->obj) && h1 == n4->hash &&  ORDER_COUNTLINEITEM1_mapkey0_idxfn::equals(se6, *e4)); 
                  }
                }
              n3 = n3->nxt;
            }
          }
        }{  // foreach
          const HashIndex_ORDER_COUNTLINEITEM1_DOMAIN1_map_0* i5 = static_cast<HashIndex_ORDER_COUNTLINEITEM1_DOMAIN1_map_0*>(ORDER_COUNTLINEITEM1_DOMAIN1.index[0]);
          HashIndex_ORDER_COUNTLINEITEM1_DOMAIN1_map_0::IdxNode* n5; 
          ORDER_COUNTLINEITEM1_DOMAIN1_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long o_orderkey = e5->O_ORDERKEY;
                long v5 = e5->__av;
                { //slice 
                  const HashIndex_ORDER_COUNTLINEITEM1_map_0* i6 = static_cast<HashIndex_ORDER_COUNTLINEITEM1_map_0*>(ORDER_COUNTLINEITEM1.index[1]);
                  const HASH_RES_t h2 = ORDER_COUNTLINEITEM1_mapkey0_idxfn::hash(se8.modify0(o_orderkey));
                  HashIndex_ORDER_COUNTLINEITEM1_map_0::IdxNode* n6 = static_cast<HashIndex_ORDER_COUNTLINEITEM1_map_0::IdxNode*>(i6->slice(se8, h2));
                  ORDER_COUNTLINEITEM1_entry* e6;
                 
                  if (n6 && (e6 = n6->obj)) {
                    do {                
                      STRING_TYPE o_orderpriority = e6->O_ORDERPRIORITY;
                      long v6 = e6->__av;
                      ORDER_COUNT.addOrDelOnZero(se3.modify(o_orderpriority),(((v5 != 0 ? 1L : 0L) * (v6 * (ORDER_COUNTORDERS1_E1_1.getValueOrDefault(se7.modify(o_orderkey)) != 0 ? 1L : 0L))) * -1L));
                      n6 = n6->nxt;
                    } while (n6 && (e6 = n6->obj) && h2 == n6->hash &&  ORDER_COUNTLINEITEM1_mapkey0_idxfn::equals(se8, *e6)); 
                  }
                }
              n5 = n5->nxt;
            }
          }
        }{  // foreach
          const HashIndex_ORDER_COUNTLINEITEM1_E1_2_DELTA_map_0* i7 = static_cast<HashIndex_ORDER_COUNTLINEITEM1_E1_2_DELTA_map_0*>(ORDER_COUNTLINEITEM1_E1_2_DELTA.index[0]);
          HashIndex_ORDER_COUNTLINEITEM1_E1_2_DELTA_map_0::IdxNode* n7; 
          ORDER_COUNTLINEITEM1_E1_2_DELTA_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long o_orderkey = e7->O_ORDERKEY;
                long v7 = e7->__av;
                ORDER_COUNTORDERS1_E1_1.addOrDelOnZero(se9.modify(o_orderkey),v7);
              n7 = n7->nxt;
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

        ORDER_COUNTORDERS1_DELTA.clear();
        {
          for (size_t i = 0; i < DELTA_ORDERS.size; i++) 
          {
                long o_orderkey = DELTA_ORDERS.orderkey[i];
                // long o_custkey = DELTA_ORDERS.custkey[i];
                // STRING_TYPE o_orderstatus = DELTA_ORDERS.orderstatus[i];
                // DOUBLE_TYPE o_totalprice = DELTA_ORDERS.totalprice[i];
                date o_orderdate = DELTA_ORDERS.orderdate[i];
                STRING_TYPE o_orderpriority = DELTA_ORDERS.orderpriority[i];
                // STRING_TYPE o_clerk = DELTA_ORDERS.clerk[i];
                // long o_shippriority = DELTA_ORDERS.shippriority[i];
                // STRING_TYPE o_comment = DELTA_ORDERS.comment[i];
                long v8 = 1L;
                (/*if */(c1 > o_orderdate && o_orderdate >= c2) ? ORDER_COUNTORDERS1_DELTA.addOrDelOnZero(se10.modify(o_orderkey,o_orderpriority),v8) : (void)0);
          }
        }

        {  // foreach
          const HashIndex_ORDER_COUNTORDERS1_DELTA_map_01* i9 = static_cast<HashIndex_ORDER_COUNTORDERS1_DELTA_map_01*>(ORDER_COUNTORDERS1_DELTA.index[0]);
          HashIndex_ORDER_COUNTORDERS1_DELTA_map_01::IdxNode* n9; 
          ORDER_COUNTORDERS1_DELTA_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long o_orderkey = e9->O_ORDERKEY;
                STRING_TYPE o_orderpriority = e9->O_ORDERPRIORITY;
                long v9 = e9->__av;
                ORDER_COUNT.addOrDelOnZero(se11.modify(o_orderpriority),(v9 * (ORDER_COUNTORDERS1_E1_1.getValueOrDefault(se12.modify(o_orderkey)) != 0 ? 1L : 0L)));
              n9 = n9->nxt;
            }
          }
        }{  // foreach
          const HashIndex_ORDER_COUNTORDERS1_DELTA_map_01* i10 = static_cast<HashIndex_ORDER_COUNTORDERS1_DELTA_map_01*>(ORDER_COUNTORDERS1_DELTA.index[0]);
          HashIndex_ORDER_COUNTORDERS1_DELTA_map_01::IdxNode* n10; 
          ORDER_COUNTORDERS1_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long o_orderkey = e10->O_ORDERKEY;
                STRING_TYPE o_orderpriority = e10->O_ORDERPRIORITY;
                long v10 = e10->__av;
                ORDER_COUNTLINEITEM1.addOrDelOnZero(se13.modify(o_orderkey,o_orderpriority),v10);
              n10 = n10->nxt;
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
    ORDER_COUNTLINEITEM1_E1_2_DELTA_entry se1;
    ORDER_COUNTLINEITEM1_DOMAIN1_entry se2;
    ORDER_COUNT_entry se3;
    ORDER_COUNTORDERS1_E1_1_entry se4;
    ORDER_COUNTLINEITEM1_E1_2_DELTA_entry se5;
    ORDER_COUNTLINEITEM1_entry se6;
    ORDER_COUNTORDERS1_E1_1_entry se7;
    ORDER_COUNTLINEITEM1_entry se8;
    ORDER_COUNTORDERS1_E1_1_entry se9;
    ORDER_COUNTORDERS1_DELTA_entry se10;
    ORDER_COUNT_entry se11;
    ORDER_COUNTORDERS1_E1_1_entry se12;
    ORDER_COUNTLINEITEM1_entry se13;
  
    /* Data structures used for storing materialized views */
    ORDER_COUNTLINEITEM1_DOMAIN1_map ORDER_COUNTLINEITEM1_DOMAIN1;
    ORDER_COUNTLINEITEM1_map ORDER_COUNTLINEITEM1;
    ORDER_COUNTLINEITEM1_E1_2_DELTA_map ORDER_COUNTLINEITEM1_E1_2_DELTA;
    ORDER_COUNTORDERS1_DELTA_map ORDER_COUNTORDERS1_DELTA;
    ORDER_COUNTORDERS1_E1_1_map ORDER_COUNTORDERS1_E1_1;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_ORDERS_map DELTA_ORDERS;
    
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ long c2;
  
  };

}
