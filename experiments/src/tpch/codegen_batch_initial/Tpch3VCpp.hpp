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
  
  struct DELTA_CUSTOMER_entry {
    long customer_custkey; STRING_TYPE customer_name; STRING_TYPE customer_address; long customer_nationkey; STRING_TYPE customer_phone; DOUBLE_TYPE customer_acctbal; STRING_TYPE customer_mktsegment; STRING_TYPE customer_comment; long __av; 
    explicit DELTA_CUSTOMER_entry() { /*customer_custkey = 0L; customer_name = ""; customer_address = ""; customer_nationkey = 0L; customer_phone = ""; customer_acctbal = 0.0; customer_mktsegment = ""; customer_comment = ""; __av = 0L; */ }
    explicit DELTA_CUSTOMER_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const STRING_TYPE& c7, const long c8) { customer_custkey = c0; customer_name = c1; customer_address = c2; customer_nationkey = c3; customer_phone = c4; customer_acctbal = c5; customer_mktsegment = c6; customer_comment = c7; __av = c8; }
    DELTA_CUSTOMER_entry(const DELTA_CUSTOMER_entry& other) : customer_custkey( other.customer_custkey ), customer_name( other.customer_name ), customer_address( other.customer_address ), customer_nationkey( other.customer_nationkey ), customer_phone( other.customer_phone ), customer_acctbal( other.customer_acctbal ), customer_mktsegment( other.customer_mktsegment ), customer_comment( other.customer_comment ), __av( other.__av ) {}
    FORCE_INLINE DELTA_CUSTOMER_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const STRING_TYPE& c7) { customer_custkey = c0; customer_name = c1; customer_address = c2; customer_nationkey = c3; customer_phone = c4; customer_acctbal = c5; customer_mktsegment = c6; customer_comment = c7;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_custkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_nationkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_phone);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_acctbal);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_mktsegment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_CUSTOMER_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_CUSTOMER_entry& e) {
      size_t h = 0;
      hash_combine(h, e.customer_custkey);
      hash_combine(h, e.customer_name);
      hash_combine(h, e.customer_address);
      hash_combine(h, e.customer_nationkey);
      hash_combine(h, e.customer_phone);
      hash_combine(h, e.customer_acctbal);
      hash_combine(h, e.customer_mktsegment);
      hash_combine(h, e.customer_comment);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_CUSTOMER_entry& x, const DELTA_CUSTOMER_entry& y) {
      return x.customer_custkey == y.customer_custkey && x.customer_name == y.customer_name && x.customer_address == y.customer_address && x.customer_nationkey == y.customer_nationkey && x.customer_phone == y.customer_phone && x.customer_acctbal == y.customer_acctbal && x.customer_mktsegment == y.customer_mktsegment && x.customer_comment == y.customer_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_CUSTOMER_entry,long,
    HashIndex<DELTA_CUSTOMER_entry,long,DELTA_CUSTOMER_mapkey01234567_idxfn,true>
  > DELTA_CUSTOMER_map;
  typedef HashIndex<DELTA_CUSTOMER_entry,long,DELTA_CUSTOMER_mapkey01234567_idxfn,true> HashIndex_DELTA_CUSTOMER_map_01234567;
  
  struct QUERY3_entry {
    long ORDERS_ORDERKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; DOUBLE_TYPE __av; 
    explicit QUERY3_entry() { /*ORDERS_ORDERKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0.0; */ }
    explicit QUERY3_entry(const long c0, const date c1, const long c2, const DOUBLE_TYPE c3) { ORDERS_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2; __av = c3; }
    QUERY3_entry(const QUERY3_entry& other) : ORDERS_ORDERKEY( other.ORDERS_ORDERKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3_entry& modify(const long c0, const date c1, const long c2) { ORDERS_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_entry& x, const QUERY3_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  typedef MultiHashMap<QUERY3_entry,DOUBLE_TYPE,
    HashIndex<QUERY3_entry,DOUBLE_TYPE,QUERY3_mapkey012_idxfn,true>
  > QUERY3_map;
  typedef HashIndex<QUERY3_entry,DOUBLE_TYPE,QUERY3_mapkey012_idxfn,true> HashIndex_QUERY3_map_012;
  
  struct QUERY3LINEITEM1_DELTA_entry {
    long ORDERS_ORDERKEY; DOUBLE_TYPE __av; 
    explicit QUERY3LINEITEM1_DELTA_entry() { /*ORDERS_ORDERKEY = 0L; __av = 0.0; */ }
    explicit QUERY3LINEITEM1_DELTA_entry(const long c0, const DOUBLE_TYPE c1) { ORDERS_ORDERKEY = c0; __av = c1; }
    QUERY3LINEITEM1_DELTA_entry(const QUERY3LINEITEM1_DELTA_entry& other) : ORDERS_ORDERKEY( other.ORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3LINEITEM1_DELTA_entry& modify(const long c0) { ORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3LINEITEM1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3LINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3LINEITEM1_DELTA_entry& x, const QUERY3LINEITEM1_DELTA_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3LINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<QUERY3LINEITEM1_DELTA_entry,DOUBLE_TYPE,QUERY3LINEITEM1_DELTA_mapkey0_idxfn,true>
  > QUERY3LINEITEM1_DELTA_map;
  typedef HashIndex<QUERY3LINEITEM1_DELTA_entry,DOUBLE_TYPE,QUERY3LINEITEM1_DELTA_mapkey0_idxfn,true> HashIndex_QUERY3LINEITEM1_DELTA_map_0;
  
  struct QUERY3LINEITEM1_entry {
    long ORDERS_ORDERKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; long __av; 
    explicit QUERY3LINEITEM1_entry() { /*ORDERS_ORDERKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0L; */ }
    explicit QUERY3LINEITEM1_entry(const long c0, const date c1, const long c2, const long c3) { ORDERS_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2; __av = c3; }
    QUERY3LINEITEM1_entry(const QUERY3LINEITEM1_entry& other) : ORDERS_ORDERKEY( other.ORDERS_ORDERKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3LINEITEM1_entry& modify(const long c0, const date c1, const long c2) { ORDERS_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2;  return *this; }
    FORCE_INLINE QUERY3LINEITEM1_entry& modify0(const long c0) { ORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3LINEITEM1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3LINEITEM1_entry& x, const QUERY3LINEITEM1_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  struct QUERY3LINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3LINEITEM1_entry& x, const QUERY3LINEITEM1_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3LINEITEM1_entry,long,
    HashIndex<QUERY3LINEITEM1_entry,long,QUERY3LINEITEM1_mapkey012_idxfn,true>,
    HashIndex<QUERY3LINEITEM1_entry,long,QUERY3LINEITEM1_mapkey0_idxfn,false>
  > QUERY3LINEITEM1_map;
  typedef HashIndex<QUERY3LINEITEM1_entry,long,QUERY3LINEITEM1_mapkey012_idxfn,true> HashIndex_QUERY3LINEITEM1_map_012;
  typedef HashIndex<QUERY3LINEITEM1_entry,long,QUERY3LINEITEM1_mapkey0_idxfn,false> HashIndex_QUERY3LINEITEM1_map_0;
  
  struct QUERY3LINEITEM1CUSTOMER1_entry {
    long ORDERS_ORDERKEY; long CUSTOMER_CUSTKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; long __av; 
    explicit QUERY3LINEITEM1CUSTOMER1_entry() { /*ORDERS_ORDERKEY = 0L; CUSTOMER_CUSTKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0L; */ }
    explicit QUERY3LINEITEM1CUSTOMER1_entry(const long c0, const long c1, const date c2, const long c3, const long c4) { ORDERS_ORDERKEY = c0; CUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3; __av = c4; }
    QUERY3LINEITEM1CUSTOMER1_entry(const QUERY3LINEITEM1CUSTOMER1_entry& other) : ORDERS_ORDERKEY( other.ORDERS_ORDERKEY ), CUSTOMER_CUSTKEY( other.CUSTOMER_CUSTKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3LINEITEM1CUSTOMER1_entry& modify(const long c0, const long c1, const date c2, const long c3) { ORDERS_ORDERKEY = c0; CUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3;  return *this; }
    FORCE_INLINE QUERY3LINEITEM1CUSTOMER1_entry& modify0(const long c0) { ORDERS_ORDERKEY = c0;  return *this; }
    FORCE_INLINE QUERY3LINEITEM1CUSTOMER1_entry& modify1(const long c1) { CUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3LINEITEM1CUSTOMER1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3LINEITEM1CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      hash_combine(h, e.CUSTOMER_CUSTKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3LINEITEM1CUSTOMER1_entry& x, const QUERY3LINEITEM1CUSTOMER1_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY && x.CUSTOMER_CUSTKEY == y.CUSTOMER_CUSTKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  struct QUERY3LINEITEM1CUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3LINEITEM1CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3LINEITEM1CUSTOMER1_entry& x, const QUERY3LINEITEM1CUSTOMER1_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY;
    }
  };
  
  struct QUERY3LINEITEM1CUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3LINEITEM1CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3LINEITEM1CUSTOMER1_entry& x, const QUERY3LINEITEM1CUSTOMER1_entry& y) {
      return x.CUSTOMER_CUSTKEY == y.CUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3LINEITEM1CUSTOMER1_entry,long,
    HashIndex<QUERY3LINEITEM1CUSTOMER1_entry,long,QUERY3LINEITEM1CUSTOMER1_mapkey0123_idxfn,true>,
    HashIndex<QUERY3LINEITEM1CUSTOMER1_entry,long,QUERY3LINEITEM1CUSTOMER1_mapkey0_idxfn,false>,
    HashIndex<QUERY3LINEITEM1CUSTOMER1_entry,long,QUERY3LINEITEM1CUSTOMER1_mapkey1_idxfn,false>
  > QUERY3LINEITEM1CUSTOMER1_map;
  typedef HashIndex<QUERY3LINEITEM1CUSTOMER1_entry,long,QUERY3LINEITEM1CUSTOMER1_mapkey0123_idxfn,true> HashIndex_QUERY3LINEITEM1CUSTOMER1_map_0123;
  typedef HashIndex<QUERY3LINEITEM1CUSTOMER1_entry,long,QUERY3LINEITEM1CUSTOMER1_mapkey0_idxfn,false> HashIndex_QUERY3LINEITEM1CUSTOMER1_map_0;
  typedef HashIndex<QUERY3LINEITEM1CUSTOMER1_entry,long,QUERY3LINEITEM1CUSTOMER1_mapkey1_idxfn,false> HashIndex_QUERY3LINEITEM1CUSTOMER1_map_1;
  
  struct QUERY3ORDERS1_DELTA_entry {
    long ORDERS_ORDERKEY; long CUSTOMER_CUSTKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; long __av; 
    explicit QUERY3ORDERS1_DELTA_entry() { /*ORDERS_ORDERKEY = 0L; CUSTOMER_CUSTKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0L; */ }
    explicit QUERY3ORDERS1_DELTA_entry(const long c0, const long c1, const date c2, const long c3, const long c4) { ORDERS_ORDERKEY = c0; CUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3; __av = c4; }
    QUERY3ORDERS1_DELTA_entry(const QUERY3ORDERS1_DELTA_entry& other) : ORDERS_ORDERKEY( other.ORDERS_ORDERKEY ), CUSTOMER_CUSTKEY( other.CUSTOMER_CUSTKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3ORDERS1_DELTA_entry& modify(const long c0, const long c1, const date c2, const long c3) { ORDERS_ORDERKEY = c0; CUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3ORDERS1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3ORDERS1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      hash_combine(h, e.CUSTOMER_CUSTKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3ORDERS1_DELTA_entry& x, const QUERY3ORDERS1_DELTA_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY && x.CUSTOMER_CUSTKEY == y.CUSTOMER_CUSTKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  typedef MultiHashMap<QUERY3ORDERS1_DELTA_entry,long,
    HashIndex<QUERY3ORDERS1_DELTA_entry,long,QUERY3ORDERS1_DELTA_mapkey0123_idxfn,true>
  > QUERY3ORDERS1_DELTA_map;
  typedef HashIndex<QUERY3ORDERS1_DELTA_entry,long,QUERY3ORDERS1_DELTA_mapkey0123_idxfn,true> HashIndex_QUERY3ORDERS1_DELTA_map_0123;
  
  struct QUERY3ORDERS1_P_1_entry {
    long CUSTOMER_CUSTKEY; long __av; 
    explicit QUERY3ORDERS1_P_1_entry() { /*CUSTOMER_CUSTKEY = 0L; __av = 0L; */ }
    explicit QUERY3ORDERS1_P_1_entry(const long c0, const long c1) { CUSTOMER_CUSTKEY = c0; __av = c1; }
    QUERY3ORDERS1_P_1_entry(const QUERY3ORDERS1_P_1_entry& other) : CUSTOMER_CUSTKEY( other.CUSTOMER_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3ORDERS1_P_1_entry& modify(const long c0) { CUSTOMER_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3ORDERS1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3ORDERS1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3ORDERS1_P_1_entry& x, const QUERY3ORDERS1_P_1_entry& y) {
      return x.CUSTOMER_CUSTKEY == y.CUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3ORDERS1_P_1_entry,long,
    HashIndex<QUERY3ORDERS1_P_1_entry,long,QUERY3ORDERS1_P_1_mapkey0_idxfn,true>
  > QUERY3ORDERS1_P_1_map;
  typedef HashIndex<QUERY3ORDERS1_P_1_entry,long,QUERY3ORDERS1_P_1_mapkey0_idxfn,true> HashIndex_QUERY3ORDERS1_P_1_map_0;
  
  struct QUERY3ORDERS1_P_2_entry {
    long ORDERS_ORDERKEY; DOUBLE_TYPE __av; 
    explicit QUERY3ORDERS1_P_2_entry() { /*ORDERS_ORDERKEY = 0L; __av = 0.0; */ }
    explicit QUERY3ORDERS1_P_2_entry(const long c0, const DOUBLE_TYPE c1) { ORDERS_ORDERKEY = c0; __av = c1; }
    QUERY3ORDERS1_P_2_entry(const QUERY3ORDERS1_P_2_entry& other) : ORDERS_ORDERKEY( other.ORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3ORDERS1_P_2_entry& modify(const long c0) { ORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3ORDERS1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3ORDERS1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3ORDERS1_P_2_entry& x, const QUERY3ORDERS1_P_2_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3ORDERS1_P_2_entry,DOUBLE_TYPE,
    HashIndex<QUERY3ORDERS1_P_2_entry,DOUBLE_TYPE,QUERY3ORDERS1_P_2_mapkey0_idxfn,true>
  > QUERY3ORDERS1_P_2_map;
  typedef HashIndex<QUERY3ORDERS1_P_2_entry,DOUBLE_TYPE,QUERY3ORDERS1_P_2_mapkey0_idxfn,true> HashIndex_QUERY3ORDERS1_P_2_map_0;
  
  struct QUERY3CUSTOMER1_DELTA_entry {
    long CUSTOMER_CUSTKEY; long __av; 
    explicit QUERY3CUSTOMER1_DELTA_entry() { /*CUSTOMER_CUSTKEY = 0L; __av = 0L; */ }
    explicit QUERY3CUSTOMER1_DELTA_entry(const long c0, const long c1) { CUSTOMER_CUSTKEY = c0; __av = c1; }
    QUERY3CUSTOMER1_DELTA_entry(const QUERY3CUSTOMER1_DELTA_entry& other) : CUSTOMER_CUSTKEY( other.CUSTOMER_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3CUSTOMER1_DELTA_entry& modify(const long c0) { CUSTOMER_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3CUSTOMER1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3CUSTOMER1_DELTA_entry& x, const QUERY3CUSTOMER1_DELTA_entry& y) {
      return x.CUSTOMER_CUSTKEY == y.CUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3CUSTOMER1_DELTA_entry,long,
    HashIndex<QUERY3CUSTOMER1_DELTA_entry,long,QUERY3CUSTOMER1_DELTA_mapkey0_idxfn,true>
  > QUERY3CUSTOMER1_DELTA_map;
  typedef HashIndex<QUERY3CUSTOMER1_DELTA_entry,long,QUERY3CUSTOMER1_DELTA_mapkey0_idxfn,true> HashIndex_QUERY3CUSTOMER1_DELTA_map_0;
  
  struct QUERY3CUSTOMER1_entry {
    long ORDERS_ORDERKEY; long CUSTOMER_CUSTKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; DOUBLE_TYPE __av; 
    explicit QUERY3CUSTOMER1_entry() { /*ORDERS_ORDERKEY = 0L; CUSTOMER_CUSTKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0.0; */ }
    explicit QUERY3CUSTOMER1_entry(const long c0, const long c1, const date c2, const long c3, const DOUBLE_TYPE c4) { ORDERS_ORDERKEY = c0; CUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3; __av = c4; }
    QUERY3CUSTOMER1_entry(const QUERY3CUSTOMER1_entry& other) : ORDERS_ORDERKEY( other.ORDERS_ORDERKEY ), CUSTOMER_CUSTKEY( other.CUSTOMER_CUSTKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3CUSTOMER1_entry& modify(const long c0, const long c1, const date c2, const long c3) { ORDERS_ORDERKEY = c0; CUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3;  return *this; }
    FORCE_INLINE QUERY3CUSTOMER1_entry& modify1(const long c1) { CUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3CUSTOMER1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      hash_combine(h, e.CUSTOMER_CUSTKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3CUSTOMER1_entry& x, const QUERY3CUSTOMER1_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY && x.CUSTOMER_CUSTKEY == y.CUSTOMER_CUSTKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  struct QUERY3CUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3CUSTOMER1_entry& x, const QUERY3CUSTOMER1_entry& y) {
      return x.CUSTOMER_CUSTKEY == y.CUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3CUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<QUERY3CUSTOMER1_entry,DOUBLE_TYPE,QUERY3CUSTOMER1_mapkey0123_idxfn,true>,
    HashIndex<QUERY3CUSTOMER1_entry,DOUBLE_TYPE,QUERY3CUSTOMER1_mapkey1_idxfn,false>
  > QUERY3CUSTOMER1_map;
  typedef HashIndex<QUERY3CUSTOMER1_entry,DOUBLE_TYPE,QUERY3CUSTOMER1_mapkey0123_idxfn,true> HashIndex_QUERY3CUSTOMER1_map_0123;
  typedef HashIndex<QUERY3CUSTOMER1_entry,DOUBLE_TYPE,QUERY3CUSTOMER1_mapkey1_idxfn,false> HashIndex_QUERY3CUSTOMER1_map_1;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const QUERY3_map& _QUERY3 = get_QUERY3();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(QUERY3), _QUERY3, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const QUERY3_map& get_QUERY3() const {
      return QUERY3;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    QUERY3_map QUERY3;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c2 = STRING_TYPE("BUILDING");
      c1 = Udate(STRING_TYPE("1995-3-15"));
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

        QUERY3LINEITEM1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
            long orders_orderkey = DELTA_LINEITEM.orderkey[i];
            // long lineitem_partkey = DELTA_LINEITEM.partkey[i];
            // long lineitem_suppkey = DELTA_LINEITEM.suppkey[i];
            // long lineitem_linenumber = DELTA_LINEITEM.linenumber[i];
            // DOUBLE_TYPE lineitem_quantity = DELTA_LINEITEM.quantity[i];
            DOUBLE_TYPE lineitem_extendedprice = DELTA_LINEITEM.extendedprice[i];
            DOUBLE_TYPE lineitem_discount = DELTA_LINEITEM.discount[i];
            // DOUBLE_TYPE lineitem_tax = DELTA_LINEITEM.tax[i];
            // STRING_TYPE lineitem_returnflag = DELTA_LINEITEM.returnflag[i];
            // STRING_TYPE lineitem_linestatus = DELTA_LINEITEM.linestatus[i];
            date lineitem_shipdate = DELTA_LINEITEM.shipdate[i];
            // date lineitem_commitdate = DELTA_LINEITEM.commitdate[i];
            // date lineitem_receiptdate = DELTA_LINEITEM.receiptdate[i];
            // STRING_TYPE lineitem_shipinstruct = DELTA_LINEITEM.shipinstruct[i];
            // STRING_TYPE lineitem_shipmode = DELTA_LINEITEM.shipmode[i];
            // STRING_TYPE lineitem_comment = DELTA_LINEITEM.comment[i];
            long v1 = 1L;
            (/*if */(lineitem_shipdate > c1) ? QUERY3LINEITEM1_DELTA.addOrDelOnZero(se1.modify(orders_orderkey),(v1 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);

          }
        }{  // foreach
          const HashIndex_QUERY3LINEITEM1_DELTA_map_0* i2 = static_cast<HashIndex_QUERY3LINEITEM1_DELTA_map_0*>(QUERY3LINEITEM1_DELTA.index[0]);
          HashIndex_QUERY3LINEITEM1_DELTA_map_0::IdxNode* n2; 
          QUERY3LINEITEM1_DELTA_entry* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
                long orders_orderkey = e2->ORDERS_ORDERKEY;
                DOUBLE_TYPE v2 = e2->__av;
                { //slice 
                  const HashIndex_QUERY3LINEITEM1_map_0* i3 = static_cast<HashIndex_QUERY3LINEITEM1_map_0*>(QUERY3LINEITEM1.index[1]);
                  const HASH_RES_t h1 = QUERY3LINEITEM1_mapkey0_idxfn::hash(se3.modify0(orders_orderkey));
                  HashIndex_QUERY3LINEITEM1_map_0::IdxNode* n3 = static_cast<HashIndex_QUERY3LINEITEM1_map_0::IdxNode*>(i3->slice(se3, h1));
                  QUERY3LINEITEM1_entry* e3;
                 
                  if (n3 && (e3 = n3->obj)) {
                    do {                
                      date orders_orderdate = e3->ORDERS_ORDERDATE;
                      long orders_shippriority = e3->ORDERS_SHIPPRIORITY;
                      long v3 = e3->__av;
                      QUERY3.addOrDelOnZero(se2.modify(orders_orderkey,orders_orderdate,orders_shippriority),(v2 * v3));
                      n3 = n3->nxt;
                    } while (n3 && (e3 = n3->obj) && h1 == n3->hash &&  QUERY3LINEITEM1_mapkey0_idxfn::equals(se3, *e3)); 
                  }
                }
              n2 = n2->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY3LINEITEM1_DELTA_map_0* i4 = static_cast<HashIndex_QUERY3LINEITEM1_DELTA_map_0*>(QUERY3LINEITEM1_DELTA.index[0]);
          HashIndex_QUERY3LINEITEM1_DELTA_map_0::IdxNode* n4; 
          QUERY3LINEITEM1_DELTA_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long orders_orderkey = e4->ORDERS_ORDERKEY;
                DOUBLE_TYPE v4 = e4->__av;
                QUERY3ORDERS1_P_2.addOrDelOnZero(se4.modify(orders_orderkey),v4);
              n4 = n4->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY3LINEITEM1_DELTA_map_0* i5 = static_cast<HashIndex_QUERY3LINEITEM1_DELTA_map_0*>(QUERY3LINEITEM1_DELTA.index[0]);
          HashIndex_QUERY3LINEITEM1_DELTA_map_0::IdxNode* n5; 
          QUERY3LINEITEM1_DELTA_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long orders_orderkey = e5->ORDERS_ORDERKEY;
                DOUBLE_TYPE v5 = e5->__av;
                { //slice 
                  const HashIndex_QUERY3LINEITEM1CUSTOMER1_map_0* i6 = static_cast<HashIndex_QUERY3LINEITEM1CUSTOMER1_map_0*>(QUERY3LINEITEM1CUSTOMER1.index[1]);
                  const HASH_RES_t h2 = QUERY3LINEITEM1CUSTOMER1_mapkey0_idxfn::hash(se6.modify0(orders_orderkey));
                  HashIndex_QUERY3LINEITEM1CUSTOMER1_map_0::IdxNode* n6 = static_cast<HashIndex_QUERY3LINEITEM1CUSTOMER1_map_0::IdxNode*>(i6->slice(se6, h2));
                  QUERY3LINEITEM1CUSTOMER1_entry* e6;
                 
                  if (n6 && (e6 = n6->obj)) {
                    do {                
                      long customer_custkey = e6->CUSTOMER_CUSTKEY;
                      date orders_orderdate = e6->ORDERS_ORDERDATE;
                      long orders_shippriority = e6->ORDERS_SHIPPRIORITY;
                      long v6 = e6->__av;
                      QUERY3CUSTOMER1.addOrDelOnZero(se5.modify(orders_orderkey,customer_custkey,orders_orderdate,orders_shippriority),(v5 * v6));
                      n6 = n6->nxt;
                    } while (n6 && (e6 = n6->obj) && h2 == n6->hash &&  QUERY3LINEITEM1CUSTOMER1_mapkey0_idxfn::equals(se6, *e6)); 
                  }
                }
              n5 = n5->nxt;
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

        QUERY3ORDERS1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_ORDERS.size; i++)
          {
            long orders_orderkey = DELTA_ORDERS.orderkey[i];
            long customer_custkey = DELTA_ORDERS.custkey[i];
            // STRING_TYPE orders_orderstatus = DELTA_ORDERS.orderstatus[i];
            // DOUBLE_TYPE orders_totalprice = DELTA_ORDERS.totalprice[i];
            date orders_orderdate = DELTA_ORDERS.orderdate[i];
            // STRING_TYPE orders_orderpriority = DELTA_ORDERS.orderpriority[i];
            // STRING_TYPE orders_clerk = DELTA_ORDERS.clerk[i];
            long orders_shippriority = DELTA_ORDERS.shippriority[i];
            // STRING_TYPE orders_comment = DELTA_ORDERS.comment[i];
            long v7 = 1L;
            (/*if */(c1 > orders_orderdate) ? QUERY3ORDERS1_DELTA.addOrDelOnZero(se7.modify(orders_orderkey,customer_custkey,orders_orderdate,orders_shippriority),v7) : (void)0);
          }
        }{  // foreach
          const HashIndex_QUERY3ORDERS1_DELTA_map_0123* i8 = static_cast<HashIndex_QUERY3ORDERS1_DELTA_map_0123*>(QUERY3ORDERS1_DELTA.index[0]);
          HashIndex_QUERY3ORDERS1_DELTA_map_0123::IdxNode* n8; 
          QUERY3ORDERS1_DELTA_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long orders_orderkey = e8->ORDERS_ORDERKEY;
                long customer_custkey = e8->CUSTOMER_CUSTKEY;
                date orders_orderdate = e8->ORDERS_ORDERDATE;
                long orders_shippriority = e8->ORDERS_SHIPPRIORITY;
                long v8 = e8->__av;
                QUERY3.addOrDelOnZero(se8.modify(orders_orderkey,orders_orderdate,orders_shippriority),(v8 * (QUERY3ORDERS1_P_1.getValueOrDefault(se9.modify(customer_custkey)) * QUERY3ORDERS1_P_2.getValueOrDefault(se10.modify(orders_orderkey)))));
              n8 = n8->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY3ORDERS1_DELTA_map_0123* i9 = static_cast<HashIndex_QUERY3ORDERS1_DELTA_map_0123*>(QUERY3ORDERS1_DELTA.index[0]);
          HashIndex_QUERY3ORDERS1_DELTA_map_0123::IdxNode* n9; 
          QUERY3ORDERS1_DELTA_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long orders_orderkey = e9->ORDERS_ORDERKEY;
                long customer_custkey = e9->CUSTOMER_CUSTKEY;
                date orders_orderdate = e9->ORDERS_ORDERDATE;
                long orders_shippriority = e9->ORDERS_SHIPPRIORITY;
                long v9 = e9->__av;
                QUERY3LINEITEM1.addOrDelOnZero(se11.modify(orders_orderkey,orders_orderdate,orders_shippriority),(v9 * QUERY3ORDERS1_P_1.getValueOrDefault(se12.modify(customer_custkey))));
              n9 = n9->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY3ORDERS1_DELTA_map_0123* i10 = static_cast<HashIndex_QUERY3ORDERS1_DELTA_map_0123*>(QUERY3ORDERS1_DELTA.index[0]);
          HashIndex_QUERY3ORDERS1_DELTA_map_0123::IdxNode* n10; 
          QUERY3ORDERS1_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long orders_orderkey = e10->ORDERS_ORDERKEY;
                long customer_custkey = e10->CUSTOMER_CUSTKEY;
                date orders_orderdate = e10->ORDERS_ORDERDATE;
                long orders_shippriority = e10->ORDERS_SHIPPRIORITY;
                long v10 = e10->__av;
                QUERY3LINEITEM1CUSTOMER1.addOrDelOnZero(se13.modify(orders_orderkey,customer_custkey,orders_orderdate,orders_shippriority),v10);
              n10 = n10->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY3ORDERS1_DELTA_map_0123* i11 = static_cast<HashIndex_QUERY3ORDERS1_DELTA_map_0123*>(QUERY3ORDERS1_DELTA.index[0]);
          HashIndex_QUERY3ORDERS1_DELTA_map_0123::IdxNode* n11; 
          QUERY3ORDERS1_DELTA_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long orders_orderkey = e11->ORDERS_ORDERKEY;
                long customer_custkey = e11->CUSTOMER_CUSTKEY;
                date orders_orderdate = e11->ORDERS_ORDERDATE;
                long orders_shippriority = e11->ORDERS_SHIPPRIORITY;
                long v11 = e11->__av;
                QUERY3CUSTOMER1.addOrDelOnZero(se14.modify(orders_orderkey,customer_custkey,orders_orderdate,orders_shippriority),(v11 * QUERY3ORDERS1_P_2.getValueOrDefault(se15.modify(orders_orderkey))));
              n11 = n11->nxt;
            }
          }
        }
      }
    }
    void on_batch_update_CUSTOMER(TPCHCustomerBatch& DELTA_CUSTOMER) {
      {  
        if (tS > 0) { tS += DELTA_CUSTOMER.size; return; }         
        tLastN += DELTA_CUSTOMER.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_CUSTOMER.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_CUSTOMER.size;

        QUERY3CUSTOMER1_DELTA.clear();
        {  

          for (size_t i = 0; i < DELTA_CUSTOMER.size; i++)
          {
            long customer_custkey = DELTA_CUSTOMER.custkey[i];
            // STRING_TYPE customer_name = DELTA_CUSTOMER.name[i];
            // STRING_TYPE customer_address = DELTA_CUSTOMER.address[i];
            // long customer_nationkey = DELTA_CUSTOMER.nationkey[i];
            // STRING_TYPE customer_phone = DELTA_CUSTOMER.phone[i];
            // DOUBLE_TYPE customer_acctbal = DELTA_CUSTOMER.acctbal[i];
            STRING_TYPE lift1 = DELTA_CUSTOMER.mktsegment[i];
            // STRING_TYPE customer_comment = DELTA_CUSTOMER.comment[i];
            long v12 = 1L;
            (/*if */(lift1 == c2) ? QUERY3CUSTOMER1_DELTA.addOrDelOnZero(se16.modify(customer_custkey),v12) : (void)0);
          }
        }{  // foreach
          const HashIndex_QUERY3CUSTOMER1_DELTA_map_0* i13 = static_cast<HashIndex_QUERY3CUSTOMER1_DELTA_map_0*>(QUERY3CUSTOMER1_DELTA.index[0]);
          HashIndex_QUERY3CUSTOMER1_DELTA_map_0::IdxNode* n13; 
          QUERY3CUSTOMER1_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long customer_custkey = e13->CUSTOMER_CUSTKEY;
                long v13 = e13->__av;
                { //slice 
                  const HashIndex_QUERY3CUSTOMER1_map_1* i14 = static_cast<HashIndex_QUERY3CUSTOMER1_map_1*>(QUERY3CUSTOMER1.index[1]);
                  const HASH_RES_t h3 = QUERY3CUSTOMER1_mapkey1_idxfn::hash(se18.modify1(customer_custkey));
                  HashIndex_QUERY3CUSTOMER1_map_1::IdxNode* n14 = static_cast<HashIndex_QUERY3CUSTOMER1_map_1::IdxNode*>(i14->slice(se18, h3));
                  QUERY3CUSTOMER1_entry* e14;
                 
                  if (n14 && (e14 = n14->obj)) {
                    do {                
                      long orders_orderkey = e14->ORDERS_ORDERKEY;
                      date orders_orderdate = e14->ORDERS_ORDERDATE;
                      long orders_shippriority = e14->ORDERS_SHIPPRIORITY;
                      DOUBLE_TYPE v14 = e14->__av;
                      QUERY3.addOrDelOnZero(se17.modify(orders_orderkey,orders_orderdate,orders_shippriority),(v13 * v14));
                      n14 = n14->nxt;
                    } while (n14 && (e14 = n14->obj) && h3 == n14->hash &&  QUERY3CUSTOMER1_mapkey1_idxfn::equals(se18, *e14)); 
                  }
                }
              n13 = n13->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY3CUSTOMER1_DELTA_map_0* i15 = static_cast<HashIndex_QUERY3CUSTOMER1_DELTA_map_0*>(QUERY3CUSTOMER1_DELTA.index[0]);
          HashIndex_QUERY3CUSTOMER1_DELTA_map_0::IdxNode* n15; 
          QUERY3CUSTOMER1_DELTA_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long customer_custkey = e15->CUSTOMER_CUSTKEY;
                long v15 = e15->__av;
                { //slice 
                  const HashIndex_QUERY3LINEITEM1CUSTOMER1_map_1* i16 = static_cast<HashIndex_QUERY3LINEITEM1CUSTOMER1_map_1*>(QUERY3LINEITEM1CUSTOMER1.index[2]);
                  const HASH_RES_t h4 = QUERY3LINEITEM1CUSTOMER1_mapkey1_idxfn::hash(se20.modify1(customer_custkey));
                  HashIndex_QUERY3LINEITEM1CUSTOMER1_map_1::IdxNode* n16 = static_cast<HashIndex_QUERY3LINEITEM1CUSTOMER1_map_1::IdxNode*>(i16->slice(se20, h4));
                  QUERY3LINEITEM1CUSTOMER1_entry* e16;
                 
                  if (n16 && (e16 = n16->obj)) {
                    do {                
                      long orders_orderkey = e16->ORDERS_ORDERKEY;
                      date orders_orderdate = e16->ORDERS_ORDERDATE;
                      long orders_shippriority = e16->ORDERS_SHIPPRIORITY;
                      long v16 = e16->__av;
                      QUERY3LINEITEM1.addOrDelOnZero(se19.modify(orders_orderkey,orders_orderdate,orders_shippriority),(v15 * v16));
                      n16 = n16->nxt;
                    } while (n16 && (e16 = n16->obj) && h4 == n16->hash &&  QUERY3LINEITEM1CUSTOMER1_mapkey1_idxfn::equals(se20, *e16)); 
                  }
                }
              n15 = n15->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY3CUSTOMER1_DELTA_map_0* i17 = static_cast<HashIndex_QUERY3CUSTOMER1_DELTA_map_0*>(QUERY3CUSTOMER1_DELTA.index[0]);
          HashIndex_QUERY3CUSTOMER1_DELTA_map_0::IdxNode* n17; 
          QUERY3CUSTOMER1_DELTA_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long customer_custkey = e17->CUSTOMER_CUSTKEY;
                long v17 = e17->__av;
                QUERY3ORDERS1_P_1.addOrDelOnZero(se21.modify(customer_custkey),v17);
              n17 = n17->nxt;
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
    QUERY3LINEITEM1_DELTA_entry se1;
    QUERY3_entry se2;
    QUERY3LINEITEM1_entry se3;
    QUERY3ORDERS1_P_2_entry se4;
    QUERY3CUSTOMER1_entry se5;
    QUERY3LINEITEM1CUSTOMER1_entry se6;
    QUERY3ORDERS1_DELTA_entry se7;
    QUERY3_entry se8;
    QUERY3ORDERS1_P_1_entry se9;
    QUERY3ORDERS1_P_2_entry se10;
    QUERY3LINEITEM1_entry se11;
    QUERY3ORDERS1_P_1_entry se12;
    QUERY3LINEITEM1CUSTOMER1_entry se13;
    QUERY3CUSTOMER1_entry se14;
    QUERY3ORDERS1_P_2_entry se15;
    QUERY3CUSTOMER1_DELTA_entry se16;
    QUERY3_entry se17;
    QUERY3CUSTOMER1_entry se18;
    QUERY3LINEITEM1_entry se19;
    QUERY3LINEITEM1CUSTOMER1_entry se20;
    QUERY3ORDERS1_P_1_entry se21;
  
    /* Data structures used for storing materialized views */
    QUERY3LINEITEM1_DELTA_map QUERY3LINEITEM1_DELTA;
    QUERY3LINEITEM1_map QUERY3LINEITEM1;
    QUERY3LINEITEM1CUSTOMER1_map QUERY3LINEITEM1CUSTOMER1;
    QUERY3ORDERS1_DELTA_map QUERY3ORDERS1_DELTA;
    QUERY3ORDERS1_P_1_map QUERY3ORDERS1_P_1;
    QUERY3ORDERS1_P_2_map QUERY3ORDERS1_P_2;
    QUERY3CUSTOMER1_DELTA_map QUERY3CUSTOMER1_DELTA;
    QUERY3CUSTOMER1_map QUERY3CUSTOMER1;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_ORDERS_map DELTA_ORDERS;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    
    /*const static*/ STRING_TYPE c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
  
  };

}
