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
  
  struct QUERY18_entry {
    STRING_TYPE C_NAME; long C_CUSTKEY; long O_ORDERKEY; date O_ORDERDATE; DOUBLE_TYPE O_TOTALPRICE; DOUBLE_TYPE __av; 
    explicit QUERY18_entry() { /*C_NAME = ""; C_CUSTKEY = 0L; O_ORDERKEY = 0L; O_ORDERDATE = 00000000; O_TOTALPRICE = 0.0; __av = 0.0; */ }
    explicit QUERY18_entry(const STRING_TYPE& c0, const long c1, const long c2, const date c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5) { C_NAME = c0; C_CUSTKEY = c1; O_ORDERKEY = c2; O_ORDERDATE = c3; O_TOTALPRICE = c4; __av = c5; }
    QUERY18_entry(const QUERY18_entry& other) : C_NAME( other.C_NAME ), C_CUSTKEY( other.C_CUSTKEY ), O_ORDERKEY( other.O_ORDERKEY ), O_ORDERDATE( other.O_ORDERDATE ), O_TOTALPRICE( other.O_TOTALPRICE ), __av( other.__av ) {}
    FORCE_INLINE QUERY18_entry& modify(const STRING_TYPE& c0, const long c1, const long c2, const date c3, const DOUBLE_TYPE c4) { C_NAME = c0; C_CUSTKEY = c1; O_ORDERKEY = c2; O_ORDERDATE = c3; O_TOTALPRICE = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.O_ORDERDATE);
      hash_combine(h, e.O_TOTALPRICE);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_entry& x, const QUERY18_entry& y) {
      return x.C_NAME == y.C_NAME && x.C_CUSTKEY == y.C_CUSTKEY && x.O_ORDERKEY == y.O_ORDERKEY && x.O_ORDERDATE == y.O_ORDERDATE && x.O_TOTALPRICE == y.O_TOTALPRICE;
    }
  };
  
  typedef MultiHashMap<QUERY18_entry,DOUBLE_TYPE,
    HashIndex<QUERY18_entry,DOUBLE_TYPE,QUERY18_mapkey01234_idxfn,true>
  > QUERY18_map;
  typedef HashIndex<QUERY18_entry,DOUBLE_TYPE,QUERY18_mapkey01234_idxfn,true> HashIndex_QUERY18_map_01234;
  
  struct QUERY18LINEITEM1_DOMAIN1_entry {
    long O_ORDERKEY; long __av; 
    explicit QUERY18LINEITEM1_DOMAIN1_entry() { /*O_ORDERKEY = 0L; __av = 0L; */ }
    explicit QUERY18LINEITEM1_DOMAIN1_entry(const long c0, const long c1) { O_ORDERKEY = c0; __av = c1; }
    QUERY18LINEITEM1_DOMAIN1_entry(const QUERY18LINEITEM1_DOMAIN1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY18LINEITEM1_DOMAIN1_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18LINEITEM1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18LINEITEM1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18LINEITEM1_DOMAIN1_entry& x, const QUERY18LINEITEM1_DOMAIN1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18LINEITEM1_DOMAIN1_entry,long,
    HashIndex<QUERY18LINEITEM1_DOMAIN1_entry,long,QUERY18LINEITEM1_DOMAIN1_mapkey0_idxfn,true>
  > QUERY18LINEITEM1_DOMAIN1_map;
  typedef HashIndex<QUERY18LINEITEM1_DOMAIN1_entry,long,QUERY18LINEITEM1_DOMAIN1_mapkey0_idxfn,true> HashIndex_QUERY18LINEITEM1_DOMAIN1_map_0;
  
  struct QUERY18LINEITEM1_P_1_entry {
    long C_CUSTKEY; STRING_TYPE C_NAME; long O_ORDERKEY; DOUBLE_TYPE O_TOTALPRICE; date O_ORDERDATE; long __av; 
    explicit QUERY18LINEITEM1_P_1_entry() { /*C_CUSTKEY = 0L; C_NAME = ""; O_ORDERKEY = 0L; O_TOTALPRICE = 0.0; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit QUERY18LINEITEM1_P_1_entry(const long c0, const STRING_TYPE& c1, const long c2, const DOUBLE_TYPE c3, const date c4, const long c5) { C_CUSTKEY = c0; C_NAME = c1; O_ORDERKEY = c2; O_TOTALPRICE = c3; O_ORDERDATE = c4; __av = c5; }
    QUERY18LINEITEM1_P_1_entry(const QUERY18LINEITEM1_P_1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_NAME( other.C_NAME ), O_ORDERKEY( other.O_ORDERKEY ), O_TOTALPRICE( other.O_TOTALPRICE ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE QUERY18LINEITEM1_P_1_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const DOUBLE_TYPE c3, const date c4) { C_CUSTKEY = c0; C_NAME = c1; O_ORDERKEY = c2; O_TOTALPRICE = c3; O_ORDERDATE = c4;  return *this; }
    FORCE_INLINE QUERY18LINEITEM1_P_1_entry& modify2(const long c2) { O_ORDERKEY = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18LINEITEM1_P_1_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18LINEITEM1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.O_TOTALPRICE);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18LINEITEM1_P_1_entry& x, const QUERY18LINEITEM1_P_1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_NAME == y.C_NAME && x.O_ORDERKEY == y.O_ORDERKEY && x.O_TOTALPRICE == y.O_TOTALPRICE && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct QUERY18LINEITEM1_P_1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18LINEITEM1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18LINEITEM1_P_1_entry& x, const QUERY18LINEITEM1_P_1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18LINEITEM1_P_1_entry,long,
    HashIndex<QUERY18LINEITEM1_P_1_entry,long,QUERY18LINEITEM1_P_1_mapkey01234_idxfn,true>,
    HashIndex<QUERY18LINEITEM1_P_1_entry,long,QUERY18LINEITEM1_P_1_mapkey2_idxfn,false>
  > QUERY18LINEITEM1_P_1_map;
  typedef HashIndex<QUERY18LINEITEM1_P_1_entry,long,QUERY18LINEITEM1_P_1_mapkey01234_idxfn,true> HashIndex_QUERY18LINEITEM1_P_1_map_01234;
  typedef HashIndex<QUERY18LINEITEM1_P_1_entry,long,QUERY18LINEITEM1_P_1_mapkey2_idxfn,false> HashIndex_QUERY18LINEITEM1_P_1_map_2;
  
  struct QUERY18LINEITEM1_P_1CUSTOMER1_entry {
    long O_ORDERKEY; long C_CUSTKEY; DOUBLE_TYPE O_TOTALPRICE; date O_ORDERDATE; long __av; 
    explicit QUERY18LINEITEM1_P_1CUSTOMER1_entry() { /*O_ORDERKEY = 0L; C_CUSTKEY = 0L; O_TOTALPRICE = 0.0; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit QUERY18LINEITEM1_P_1CUSTOMER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3, const long c4) { O_ORDERKEY = c0; C_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3; __av = c4; }
    QUERY18LINEITEM1_P_1CUSTOMER1_entry(const QUERY18LINEITEM1_P_1CUSTOMER1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), C_CUSTKEY( other.C_CUSTKEY ), O_TOTALPRICE( other.O_TOTALPRICE ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE QUERY18LINEITEM1_P_1CUSTOMER1_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3) { O_ORDERKEY = c0; C_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3;  return *this; }
    FORCE_INLINE QUERY18LINEITEM1_P_1CUSTOMER1_entry& modify0(const long c0) { O_ORDERKEY = c0;  return *this; }
    FORCE_INLINE QUERY18LINEITEM1_P_1CUSTOMER1_entry& modify1(const long c1) { C_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18LINEITEM1_P_1CUSTOMER1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18LINEITEM1_P_1CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.O_TOTALPRICE);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18LINEITEM1_P_1CUSTOMER1_entry& x, const QUERY18LINEITEM1_P_1CUSTOMER1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.C_CUSTKEY == y.C_CUSTKEY && x.O_TOTALPRICE == y.O_TOTALPRICE && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct QUERY18LINEITEM1_P_1CUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18LINEITEM1_P_1CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18LINEITEM1_P_1CUSTOMER1_entry& x, const QUERY18LINEITEM1_P_1CUSTOMER1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  struct QUERY18LINEITEM1_P_1CUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18LINEITEM1_P_1CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18LINEITEM1_P_1CUSTOMER1_entry& x, const QUERY18LINEITEM1_P_1CUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18LINEITEM1_P_1CUSTOMER1_entry,long,
    HashIndex<QUERY18LINEITEM1_P_1CUSTOMER1_entry,long,QUERY18LINEITEM1_P_1CUSTOMER1_mapkey0123_idxfn,true>,
    HashIndex<QUERY18LINEITEM1_P_1CUSTOMER1_entry,long,QUERY18LINEITEM1_P_1CUSTOMER1_mapkey0_idxfn,false>,
    HashIndex<QUERY18LINEITEM1_P_1CUSTOMER1_entry,long,QUERY18LINEITEM1_P_1CUSTOMER1_mapkey1_idxfn,false>
  > QUERY18LINEITEM1_P_1CUSTOMER1_map;
  typedef HashIndex<QUERY18LINEITEM1_P_1CUSTOMER1_entry,long,QUERY18LINEITEM1_P_1CUSTOMER1_mapkey0123_idxfn,true> HashIndex_QUERY18LINEITEM1_P_1CUSTOMER1_map_0123;
  typedef HashIndex<QUERY18LINEITEM1_P_1CUSTOMER1_entry,long,QUERY18LINEITEM1_P_1CUSTOMER1_mapkey0_idxfn,false> HashIndex_QUERY18LINEITEM1_P_1CUSTOMER1_map_0;
  typedef HashIndex<QUERY18LINEITEM1_P_1CUSTOMER1_entry,long,QUERY18LINEITEM1_P_1CUSTOMER1_mapkey1_idxfn,false> HashIndex_QUERY18LINEITEM1_P_1CUSTOMER1_map_1;
  
  struct QUERY18LINEITEM1_L1_2_DELTA_entry {
    long O_ORDERKEY; DOUBLE_TYPE __av; 
    explicit QUERY18LINEITEM1_L1_2_DELTA_entry() { /*O_ORDERKEY = 0L; __av = 0.0; */ }
    explicit QUERY18LINEITEM1_L1_2_DELTA_entry(const long c0, const DOUBLE_TYPE c1) { O_ORDERKEY = c0; __av = c1; }
    QUERY18LINEITEM1_L1_2_DELTA_entry(const QUERY18LINEITEM1_L1_2_DELTA_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY18LINEITEM1_L1_2_DELTA_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18LINEITEM1_L1_2_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18LINEITEM1_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18LINEITEM1_L1_2_DELTA_entry& x, const QUERY18LINEITEM1_L1_2_DELTA_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18LINEITEM1_L1_2_DELTA_entry,DOUBLE_TYPE,
    HashIndex<QUERY18LINEITEM1_L1_2_DELTA_entry,DOUBLE_TYPE,QUERY18LINEITEM1_L1_2_DELTA_mapkey0_idxfn,true>
  > QUERY18LINEITEM1_L1_2_DELTA_map;
  typedef HashIndex<QUERY18LINEITEM1_L1_2_DELTA_entry,DOUBLE_TYPE,QUERY18LINEITEM1_L1_2_DELTA_mapkey0_idxfn,true> HashIndex_QUERY18LINEITEM1_L1_2_DELTA_map_0;
  
  struct QUERY18ORDERS1_DELTA_entry {
    long O_ORDERKEY; long C_CUSTKEY; DOUBLE_TYPE O_TOTALPRICE; date O_ORDERDATE; long __av; 
    explicit QUERY18ORDERS1_DELTA_entry() { /*O_ORDERKEY = 0L; C_CUSTKEY = 0L; O_TOTALPRICE = 0.0; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit QUERY18ORDERS1_DELTA_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3, const long c4) { O_ORDERKEY = c0; C_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3; __av = c4; }
    QUERY18ORDERS1_DELTA_entry(const QUERY18ORDERS1_DELTA_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), C_CUSTKEY( other.C_CUSTKEY ), O_TOTALPRICE( other.O_TOTALPRICE ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE QUERY18ORDERS1_DELTA_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3) { O_ORDERKEY = c0; C_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18ORDERS1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18ORDERS1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.O_TOTALPRICE);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18ORDERS1_DELTA_entry& x, const QUERY18ORDERS1_DELTA_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.C_CUSTKEY == y.C_CUSTKEY && x.O_TOTALPRICE == y.O_TOTALPRICE && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  typedef MultiHashMap<QUERY18ORDERS1_DELTA_entry,long,
    HashIndex<QUERY18ORDERS1_DELTA_entry,long,QUERY18ORDERS1_DELTA_mapkey0123_idxfn,true>
  > QUERY18ORDERS1_DELTA_map;
  typedef HashIndex<QUERY18ORDERS1_DELTA_entry,long,QUERY18ORDERS1_DELTA_mapkey0123_idxfn,true> HashIndex_QUERY18ORDERS1_DELTA_map_0123;
  
  struct QUERY18ORDERS1_P_1_entry {
    long C_CUSTKEY; STRING_TYPE C_NAME; long __av; 
    explicit QUERY18ORDERS1_P_1_entry() { /*C_CUSTKEY = 0L; C_NAME = ""; __av = 0L; */ }
    explicit QUERY18ORDERS1_P_1_entry(const long c0, const STRING_TYPE& c1, const long c2) { C_CUSTKEY = c0; C_NAME = c1; __av = c2; }
    QUERY18ORDERS1_P_1_entry(const QUERY18ORDERS1_P_1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_NAME( other.C_NAME ), __av( other.__av ) {}
    FORCE_INLINE QUERY18ORDERS1_P_1_entry& modify(const long c0, const STRING_TYPE& c1) { C_CUSTKEY = c0; C_NAME = c1;  return *this; }
    FORCE_INLINE QUERY18ORDERS1_P_1_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18ORDERS1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18ORDERS1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18ORDERS1_P_1_entry& x, const QUERY18ORDERS1_P_1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_NAME == y.C_NAME;
    }
  };
  
  struct QUERY18ORDERS1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18ORDERS1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18ORDERS1_P_1_entry& x, const QUERY18ORDERS1_P_1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18ORDERS1_P_1_entry,long,
    HashIndex<QUERY18ORDERS1_P_1_entry,long,QUERY18ORDERS1_P_1_mapkey01_idxfn,true>,
    HashIndex<QUERY18ORDERS1_P_1_entry,long,QUERY18ORDERS1_P_1_mapkey0_idxfn,false>
  > QUERY18ORDERS1_P_1_map;
  typedef HashIndex<QUERY18ORDERS1_P_1_entry,long,QUERY18ORDERS1_P_1_mapkey01_idxfn,true> HashIndex_QUERY18ORDERS1_P_1_map_01;
  typedef HashIndex<QUERY18ORDERS1_P_1_entry,long,QUERY18ORDERS1_P_1_mapkey0_idxfn,false> HashIndex_QUERY18ORDERS1_P_1_map_0;
  
  struct QUERY18CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; STRING_TYPE C_NAME; long __av; 
    explicit QUERY18CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_NAME = ""; __av = 0L; */ }
    explicit QUERY18CUSTOMER1_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { C_CUSTKEY = c0; C_NAME = c1; __av = c2; }
    QUERY18CUSTOMER1_DELTA_entry(const QUERY18CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_NAME( other.C_NAME ), __av( other.__av ) {}
    FORCE_INLINE QUERY18CUSTOMER1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { C_CUSTKEY = c0; C_NAME = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18CUSTOMER1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18CUSTOMER1_DELTA_entry& x, const QUERY18CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_NAME == y.C_NAME;
    }
  };
  
  typedef MultiHashMap<QUERY18CUSTOMER1_DELTA_entry,long,
    HashIndex<QUERY18CUSTOMER1_DELTA_entry,long,QUERY18CUSTOMER1_DELTA_mapkey01_idxfn,true>
  > QUERY18CUSTOMER1_DELTA_map;
  typedef HashIndex<QUERY18CUSTOMER1_DELTA_entry,long,QUERY18CUSTOMER1_DELTA_mapkey01_idxfn,true> HashIndex_QUERY18CUSTOMER1_DELTA_map_01;
  
  struct QUERY18CUSTOMER1_entry {
    long O_ORDERKEY; long C_CUSTKEY; DOUBLE_TYPE O_TOTALPRICE; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit QUERY18CUSTOMER1_entry() { /*O_ORDERKEY = 0L; C_CUSTKEY = 0L; O_TOTALPRICE = 0.0; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit QUERY18CUSTOMER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3, const DOUBLE_TYPE c4) { O_ORDERKEY = c0; C_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3; __av = c4; }
    QUERY18CUSTOMER1_entry(const QUERY18CUSTOMER1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), C_CUSTKEY( other.C_CUSTKEY ), O_TOTALPRICE( other.O_TOTALPRICE ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE QUERY18CUSTOMER1_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3) { O_ORDERKEY = c0; C_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3;  return *this; }
    FORCE_INLINE QUERY18CUSTOMER1_entry& modify1(const long c1) { C_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18CUSTOMER1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.O_TOTALPRICE);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18CUSTOMER1_entry& x, const QUERY18CUSTOMER1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.C_CUSTKEY == y.C_CUSTKEY && x.O_TOTALPRICE == y.O_TOTALPRICE && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct QUERY18CUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18CUSTOMER1_entry& x, const QUERY18CUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18CUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<QUERY18CUSTOMER1_entry,DOUBLE_TYPE,QUERY18CUSTOMER1_mapkey0123_idxfn,true>,
    HashIndex<QUERY18CUSTOMER1_entry,DOUBLE_TYPE,QUERY18CUSTOMER1_mapkey1_idxfn,false>
  > QUERY18CUSTOMER1_map;
  typedef HashIndex<QUERY18CUSTOMER1_entry,DOUBLE_TYPE,QUERY18CUSTOMER1_mapkey0123_idxfn,true> HashIndex_QUERY18CUSTOMER1_map_0123;
  typedef HashIndex<QUERY18CUSTOMER1_entry,DOUBLE_TYPE,QUERY18CUSTOMER1_mapkey1_idxfn,false> HashIndex_QUERY18CUSTOMER1_map_1;
  
  struct QUERY18CUSTOMER1_L1_1_entry {
    long O_ORDERKEY; DOUBLE_TYPE __av; 
    explicit QUERY18CUSTOMER1_L1_1_entry() { /*O_ORDERKEY = 0L; __av = 0.0; */ }
    explicit QUERY18CUSTOMER1_L1_1_entry(const long c0, const DOUBLE_TYPE c1) { O_ORDERKEY = c0; __av = c1; }
    QUERY18CUSTOMER1_L1_1_entry(const QUERY18CUSTOMER1_L1_1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY18CUSTOMER1_L1_1_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18CUSTOMER1_L1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18CUSTOMER1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18CUSTOMER1_L1_1_entry& x, const QUERY18CUSTOMER1_L1_1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18CUSTOMER1_L1_1_entry,DOUBLE_TYPE,
    HashIndex<QUERY18CUSTOMER1_L1_1_entry,DOUBLE_TYPE,QUERY18CUSTOMER1_L1_1_mapkey0_idxfn,true>
  > QUERY18CUSTOMER1_L1_1_map;
  typedef HashIndex<QUERY18CUSTOMER1_L1_1_entry,DOUBLE_TYPE,QUERY18CUSTOMER1_L1_1_mapkey0_idxfn,true> HashIndex_QUERY18CUSTOMER1_L1_1_map_0;
  
  struct tuple5_LSDA_D {
    long _1; STRING_TYPE _2; DOUBLE_TYPE _3; date _4; DOUBLE_TYPE __av;
    explicit tuple5_LSDA_D() { }
    explicit tuple5_LSDA_D(const long c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3, const date c4, DOUBLE_TYPE c__av=0.0) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; __av = c__av;}
    int operator==(const tuple5_LSDA_D &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4)); }
    FORCE_INLINE tuple5_LSDA_D& modify(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2, const date c3, DOUBLE_TYPE c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; __av = c__av; return *this; }
    static bool equals(const tuple5_LSDA_D &x, const tuple5_LSDA_D &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4)); }
    static long hash(const tuple5_LSDA_D &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
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
      const QUERY18_map& _QUERY18 = get_QUERY18();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(QUERY18), _QUERY18, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const QUERY18_map& get_QUERY18() const {
      return QUERY18;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    QUERY18_map QUERY18;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), _c1(16U) {
      
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


        QUERY18LINEITEM1_L1_2_DELTA.clear();
        QUERY18LINEITEM1_DOMAIN1.clear();
        { 
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                long o_orderkey = DELTA_LINEITEM.orderkey[i];
                // long l2_partkey = DELTA_LINEITEM.partkey[i];
                // long l2_suppkey = DELTA_LINEITEM.suppkey[i];
                // long l2_linenumber = DELTA_LINEITEM.linenumber[i];
                DOUBLE_TYPE l2_quantity = DELTA_LINEITEM.quantity[i];
                // DOUBLE_TYPE l2_extendedprice = DELTA_LINEITEM.extendedprice[i];
                // DOUBLE_TYPE l2_discount = DELTA_LINEITEM.discount[i];
                // DOUBLE_TYPE l2_tax = DELTA_LINEITEM.tax[i];
                // STRING_TYPE l2_returnflag = DELTA_LINEITEM.returnflag[i];
                // STRING_TYPE l2_linestatus = DELTA_LINEITEM.linestatus[i];
                // date l2_shipdate = DELTA_LINEITEM.shipdate[i];
                // date l2_commitdate = DELTA_LINEITEM.commitdate[i];
                // date l2_receiptdate = DELTA_LINEITEM.receiptdate[i];
                // STRING_TYPE l2_shipinstruct = DELTA_LINEITEM.shipinstruct[i];
                // STRING_TYPE l2_shipmode = DELTA_LINEITEM.shipmode[i];
                // STRING_TYPE l2_comment = DELTA_LINEITEM.comment[i];
                long v1 = 1L;
                QUERY18LINEITEM1_L1_2_DELTA.addOrDelOnZero(se1.modify(o_orderkey),(v1 * l2_quantity));      
                long v2 = 1L;
                QUERY18LINEITEM1_DOMAIN1.addOrDelOnZero(se2.modify(o_orderkey),(v2 != 0 ? 1L : 0L));
          }
        }

        {  // foreach
          const HashIndex_QUERY18LINEITEM1_DOMAIN1_map_0* i3 = static_cast<HashIndex_QUERY18LINEITEM1_DOMAIN1_map_0*>(QUERY18LINEITEM1_DOMAIN1.index[0]);
          HashIndex_QUERY18LINEITEM1_DOMAIN1_map_0::IdxNode* n3; 
          QUERY18LINEITEM1_DOMAIN1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long o_orderkey = e3->O_ORDERKEY;
                long v3 = e3->__av;
                _c1.clear();
                { //slice 
                  const HashIndex_QUERY18LINEITEM1_P_1_map_2* i4 = static_cast<HashIndex_QUERY18LINEITEM1_P_1_map_2*>(QUERY18LINEITEM1_P_1.index[1]);
                  const HASH_RES_t h1 = QUERY18LINEITEM1_P_1_mapkey2_idxfn::hash(se8.modify2(o_orderkey));
                  HashIndex_QUERY18LINEITEM1_P_1_map_2::IdxNode* n4 = static_cast<HashIndex_QUERY18LINEITEM1_P_1_map_2::IdxNode*>(i4->slice(se8, h1));
                  QUERY18LINEITEM1_P_1_entry* e4;
                 
                  if (n4 && (e4 = n4->obj)) {
                    do {                
                      long c_custkey = e4->C_CUSTKEY;
                      STRING_TYPE c_name = e4->C_NAME;
                      DOUBLE_TYPE o_totalprice = e4->O_TOTALPRICE;
                      date o_orderdate = e4->O_ORDERDATE;
                      long v5 = e4->__av;
                      long agg1 = 0L;
                      DOUBLE_TYPE l1 = (QUERY18CUSTOMER1_L1_1.getValueOrDefault(se5.modify(o_orderkey)) + QUERY18LINEITEM1_L1_2_DELTA.getValueOrDefault(se6.modify(o_orderkey)));
                      (/*if */(l1 > 100L) ? agg1 += 1L : 0L);
                      long agg2 = 0L;
                      DOUBLE_TYPE l2 = QUERY18CUSTOMER1_L1_1.getValueOrDefault(se7.modify(o_orderkey));
                      (/*if */(l2 > 100L) ? agg2 += 1L : 0L);
                      _c1.addOrDelOnZero(st1.modify(c_custkey,c_name,o_totalprice,o_orderdate,(v5 * (QUERY18CUSTOMER1_L1_1.getValueOrDefault(se4.modify(o_orderkey)) * (agg1 + (agg2 * -1L))))), (v5 * (QUERY18CUSTOMER1_L1_1.getValueOrDefault(se4.modify(o_orderkey)) * (agg1 + (agg2 * -1L)))));
                      n4 = n4->nxt;
                    } while (n4 && (e4 = n4->obj) && h1 == n4->hash &&  QUERY18LINEITEM1_P_1_mapkey2_idxfn::equals(se8, *e4)); 
                  }
                }{ //slice 
                  const HashIndex_QUERY18LINEITEM1_P_1_map_2* i5 = static_cast<HashIndex_QUERY18LINEITEM1_P_1_map_2*>(QUERY18LINEITEM1_P_1.index[1]);
                  const HASH_RES_t h2 = QUERY18LINEITEM1_P_1_mapkey2_idxfn::hash(se12.modify2(o_orderkey));
                  HashIndex_QUERY18LINEITEM1_P_1_map_2::IdxNode* n5 = static_cast<HashIndex_QUERY18LINEITEM1_P_1_map_2::IdxNode*>(i5->slice(se12, h2));
                  QUERY18LINEITEM1_P_1_entry* e5;
                 
                  if (n5 && (e5 = n5->obj)) {
                    do {                
                      long c_custkey = e5->C_CUSTKEY;
                      STRING_TYPE c_name = e5->C_NAME;
                      DOUBLE_TYPE o_totalprice = e5->O_TOTALPRICE;
                      date o_orderdate = e5->O_ORDERDATE;
                      long v6 = e5->__av;
                      long agg3 = 0L;
                      DOUBLE_TYPE l3 = (QUERY18CUSTOMER1_L1_1.getValueOrDefault(se10.modify(o_orderkey)) + QUERY18LINEITEM1_L1_2_DELTA.getValueOrDefault(se11.modify(o_orderkey)));
                      (/*if */(l3 > 100L) ? agg3 += 1L : 0L);
                      _c1.addOrDelOnZero(st2.modify(c_custkey,c_name,o_totalprice,o_orderdate,(QUERY18LINEITEM1_L1_2_DELTA.getValueOrDefault(se9.modify(o_orderkey)) * (v6 * agg3))), (QUERY18LINEITEM1_L1_2_DELTA.getValueOrDefault(se9.modify(o_orderkey)) * (v6 * agg3)));
                      n5 = n5->nxt;
                    } while (n5 && (e5 = n5->obj) && h2 == n5->hash &&  QUERY18LINEITEM1_P_1_mapkey2_idxfn::equals(se12, *e5)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple5_LSDA_D, DOUBLE_TYPE>* i6 = static_cast<HashIndex<tuple5_LSDA_D, DOUBLE_TYPE>*>(_c1.index[0]);
                  HashIndex<tuple5_LSDA_D, DOUBLE_TYPE>::IdxNode* n6; 
                  tuple5_LSDA_D* e6;
                
                  for (size_t i = 0; i < i6->size_; i++)
                  {
                    n6 = i6->buckets_ + i;
                    while (n6 && (e6 = n6->obj))
                    {
                      long c_custkey = e6->_1;
                      STRING_TYPE c_name = e6->_2;
                      DOUBLE_TYPE o_totalprice = e6->_3;
                      date o_orderdate = e6->_4;  
                      DOUBLE_TYPE v7 = e6->__av; 
                    QUERY18.addOrDelOnZero(se3.modify(c_name,c_custkey,o_orderkey,o_orderdate,o_totalprice),((v3 != 0 ? 1L : 0L) * v7));      
                      n6 = n6->nxt;
                    }
                  }
                }
              n3 = n3->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY18LINEITEM1_L1_2_DELTA_map_0* i7 = static_cast<HashIndex_QUERY18LINEITEM1_L1_2_DELTA_map_0*>(QUERY18LINEITEM1_L1_2_DELTA.index[0]);
          HashIndex_QUERY18LINEITEM1_L1_2_DELTA_map_0::IdxNode* n7; 
          QUERY18LINEITEM1_L1_2_DELTA_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long o_orderkey = e7->O_ORDERKEY;
                DOUBLE_TYPE v8 = e7->__av;
                { //slice 
                  const HashIndex_QUERY18LINEITEM1_P_1CUSTOMER1_map_0* i8 = static_cast<HashIndex_QUERY18LINEITEM1_P_1CUSTOMER1_map_0*>(QUERY18LINEITEM1_P_1CUSTOMER1.index[1]);
                  const HASH_RES_t h3 = QUERY18LINEITEM1_P_1CUSTOMER1_mapkey0_idxfn::hash(se14.modify0(o_orderkey));
                  HashIndex_QUERY18LINEITEM1_P_1CUSTOMER1_map_0::IdxNode* n8 = static_cast<HashIndex_QUERY18LINEITEM1_P_1CUSTOMER1_map_0::IdxNode*>(i8->slice(se14, h3));
                  QUERY18LINEITEM1_P_1CUSTOMER1_entry* e8;
                 
                  if (n8 && (e8 = n8->obj)) {
                    do {                
                      long c_custkey = e8->C_CUSTKEY;
                      DOUBLE_TYPE o_totalprice = e8->O_TOTALPRICE;
                      date o_orderdate = e8->O_ORDERDATE;
                      long v9 = e8->__av;
                      QUERY18CUSTOMER1.addOrDelOnZero(se13.modify(o_orderkey,c_custkey,o_totalprice,o_orderdate),(v8 * v9));
                      n8 = n8->nxt;
                    } while (n8 && (e8 = n8->obj) && h3 == n8->hash &&  QUERY18LINEITEM1_P_1CUSTOMER1_mapkey0_idxfn::equals(se14, *e8)); 
                  }
                }
              n7 = n7->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY18LINEITEM1_L1_2_DELTA_map_0* i9 = static_cast<HashIndex_QUERY18LINEITEM1_L1_2_DELTA_map_0*>(QUERY18LINEITEM1_L1_2_DELTA.index[0]);
          HashIndex_QUERY18LINEITEM1_L1_2_DELTA_map_0::IdxNode* n9; 
          QUERY18LINEITEM1_L1_2_DELTA_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long o_orderkey = e9->O_ORDERKEY;
                DOUBLE_TYPE v10 = e9->__av;
                QUERY18CUSTOMER1_L1_1.addOrDelOnZero(se15.modify(o_orderkey),v10);
              n9 = n9->nxt;
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


        QUERY18ORDERS1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_ORDERS.size; i++)
          {
                long o_orderkey = DELTA_ORDERS.orderkey[i];
                long c_custkey = DELTA_ORDERS.custkey[i];
                // STRING_TYPE o_orderstatus = DELTA_ORDERS.orderstatus[i];
                DOUBLE_TYPE o_totalprice = DELTA_ORDERS.totalprice[i];
                date o_orderdate = DELTA_ORDERS.orderdate[i];
                // STRING_TYPE o_orderpriority = DELTA_ORDERS.orderpriority[i];
                // STRING_TYPE o_clerk = DELTA_ORDERS.clerk[i];
                // long o_shippriority = DELTA_ORDERS.shippriority[i];
                // STRING_TYPE o_comment = DELTA_ORDERS.comment[i];
                long v11 = 1L;
                QUERY18ORDERS1_DELTA.addOrDelOnZero(se16.modify(o_orderkey,c_custkey,o_totalprice,o_orderdate),v11);            
          }
        }
        {  // foreach
          const HashIndex_QUERY18ORDERS1_DELTA_map_0123* i11 = static_cast<HashIndex_QUERY18ORDERS1_DELTA_map_0123*>(QUERY18ORDERS1_DELTA.index[0]);
          HashIndex_QUERY18ORDERS1_DELTA_map_0123::IdxNode* n11; 
          QUERY18ORDERS1_DELTA_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long o_orderkey = e11->O_ORDERKEY;
                long c_custkey = e11->C_CUSTKEY;
                DOUBLE_TYPE o_totalprice = e11->O_TOTALPRICE;
                date o_orderdate = e11->O_ORDERDATE;
                long v12 = e11->__av;
                { //slice 
                  const HashIndex_QUERY18ORDERS1_P_1_map_0* i12 = static_cast<HashIndex_QUERY18ORDERS1_P_1_map_0*>(QUERY18ORDERS1_P_1.index[1]);
                  const HASH_RES_t h4 = QUERY18ORDERS1_P_1_mapkey0_idxfn::hash(se20.modify0(c_custkey));
                  HashIndex_QUERY18ORDERS1_P_1_map_0::IdxNode* n12 = static_cast<HashIndex_QUERY18ORDERS1_P_1_map_0::IdxNode*>(i12->slice(se20, h4));
                  QUERY18ORDERS1_P_1_entry* e12;
                 
                  if (n12 && (e12 = n12->obj)) {
                    do {                
                      STRING_TYPE c_name = e12->C_NAME;
                      long v13 = e12->__av;
                      long agg4 = 0L;
                      DOUBLE_TYPE l4 = QUERY18CUSTOMER1_L1_1.getValueOrDefault(se19.modify(o_orderkey));
                      (/*if */(l4 > 100L) ? agg4 += 1L : 0L);
                      QUERY18.addOrDelOnZero(se17.modify(c_name,c_custkey,o_orderkey,o_orderdate,o_totalprice),(v12 * (v13 * (QUERY18CUSTOMER1_L1_1.getValueOrDefault(se18.modify(o_orderkey)) * agg4))));
                      n12 = n12->nxt;
                    } while (n12 && (e12 = n12->obj) && h4 == n12->hash &&  QUERY18ORDERS1_P_1_mapkey0_idxfn::equals(se20, *e12)); 
                  }
                }
              n11 = n11->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY18ORDERS1_DELTA_map_0123* i13 = static_cast<HashIndex_QUERY18ORDERS1_DELTA_map_0123*>(QUERY18ORDERS1_DELTA.index[0]);
          HashIndex_QUERY18ORDERS1_DELTA_map_0123::IdxNode* n13; 
          QUERY18ORDERS1_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long o_orderkey = e13->O_ORDERKEY;
                long c_custkey = e13->C_CUSTKEY;
                DOUBLE_TYPE o_totalprice = e13->O_TOTALPRICE;
                date o_orderdate = e13->O_ORDERDATE;
                long v14 = e13->__av;
                { //slice 
                  const HashIndex_QUERY18ORDERS1_P_1_map_0* i14 = static_cast<HashIndex_QUERY18ORDERS1_P_1_map_0*>(QUERY18ORDERS1_P_1.index[1]);
                  const HASH_RES_t h5 = QUERY18ORDERS1_P_1_mapkey0_idxfn::hash(se22.modify0(c_custkey));
                  HashIndex_QUERY18ORDERS1_P_1_map_0::IdxNode* n14 = static_cast<HashIndex_QUERY18ORDERS1_P_1_map_0::IdxNode*>(i14->slice(se22, h5));
                  QUERY18ORDERS1_P_1_entry* e14;
                 
                  if (n14 && (e14 = n14->obj)) {
                    do {                
                      STRING_TYPE c_name = e14->C_NAME;
                      long v15 = e14->__av;
                      QUERY18LINEITEM1_P_1.addOrDelOnZero(se21.modify(c_custkey,c_name,o_orderkey,o_totalprice,o_orderdate),(v14 * v15));
                      n14 = n14->nxt;
                    } while (n14 && (e14 = n14->obj) && h5 == n14->hash &&  QUERY18ORDERS1_P_1_mapkey0_idxfn::equals(se22, *e14)); 
                  }
                }
              n13 = n13->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY18ORDERS1_DELTA_map_0123* i15 = static_cast<HashIndex_QUERY18ORDERS1_DELTA_map_0123*>(QUERY18ORDERS1_DELTA.index[0]);
          HashIndex_QUERY18ORDERS1_DELTA_map_0123::IdxNode* n15; 
          QUERY18ORDERS1_DELTA_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long o_orderkey = e15->O_ORDERKEY;
                long c_custkey = e15->C_CUSTKEY;
                DOUBLE_TYPE o_totalprice = e15->O_TOTALPRICE;
                date o_orderdate = e15->O_ORDERDATE;
                long v16 = e15->__av;
                QUERY18LINEITEM1_P_1CUSTOMER1.addOrDelOnZero(se23.modify(o_orderkey,c_custkey,o_totalprice,o_orderdate),v16);
              n15 = n15->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY18ORDERS1_DELTA_map_0123* i16 = static_cast<HashIndex_QUERY18ORDERS1_DELTA_map_0123*>(QUERY18ORDERS1_DELTA.index[0]);
          HashIndex_QUERY18ORDERS1_DELTA_map_0123::IdxNode* n16; 
          QUERY18ORDERS1_DELTA_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long o_orderkey = e16->O_ORDERKEY;
                long c_custkey = e16->C_CUSTKEY;
                DOUBLE_TYPE o_totalprice = e16->O_TOTALPRICE;
                date o_orderdate = e16->O_ORDERDATE;
                long v17 = e16->__av;
                QUERY18CUSTOMER1.addOrDelOnZero(se24.modify(o_orderkey,c_custkey,o_totalprice,o_orderdate),(v17 * QUERY18CUSTOMER1_L1_1.getValueOrDefault(se25.modify(o_orderkey))));
              n16 = n16->nxt;
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


        QUERY18CUSTOMER1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_CUSTOMER.size; i++)
          {
                long c_custkey = DELTA_CUSTOMER.custkey[i];
                STRING_TYPE c_name = DELTA_CUSTOMER.name[i];
                // STRING_TYPE c_address = DELTA_CUSTOMER.address[i];
                // long c_nationkey = DELTA_CUSTOMER.nationkey[i];
                // STRING_TYPE c_phone = DELTA_CUSTOMER.phone[i];
                // DOUBLE_TYPE c_acctbal = DELTA_CUSTOMER.acctbal[i];
                // STRING_TYPE c_mktsegment = DELTA_CUSTOMER.mktsegment[i];
                // STRING_TYPE c_comment = DELTA_CUSTOMER.comment[i];
                long v18 = 1L;
                QUERY18CUSTOMER1_DELTA.addOrDelOnZero(se26.modify(c_custkey,c_name),v18);            
          }
        }
        {  // foreach
          const HashIndex_QUERY18CUSTOMER1_DELTA_map_01* i18 = static_cast<HashIndex_QUERY18CUSTOMER1_DELTA_map_01*>(QUERY18CUSTOMER1_DELTA.index[0]);
          HashIndex_QUERY18CUSTOMER1_DELTA_map_01::IdxNode* n18; 
          QUERY18CUSTOMER1_DELTA_entry* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
                long c_custkey = e18->C_CUSTKEY;
                STRING_TYPE c_name = e18->C_NAME;
                long v19 = e18->__av;
                { //slice 
                  const HashIndex_QUERY18CUSTOMER1_map_1* i19 = static_cast<HashIndex_QUERY18CUSTOMER1_map_1*>(QUERY18CUSTOMER1.index[1]);
                  const HASH_RES_t h6 = QUERY18CUSTOMER1_mapkey1_idxfn::hash(se29.modify1(c_custkey));
                  HashIndex_QUERY18CUSTOMER1_map_1::IdxNode* n19 = static_cast<HashIndex_QUERY18CUSTOMER1_map_1::IdxNode*>(i19->slice(se29, h6));
                  QUERY18CUSTOMER1_entry* e19;
                 
                  if (n19 && (e19 = n19->obj)) {
                    do {                
                      long o_orderkey = e19->O_ORDERKEY;
                      DOUBLE_TYPE o_totalprice = e19->O_TOTALPRICE;
                      date o_orderdate = e19->O_ORDERDATE;
                      DOUBLE_TYPE v20 = e19->__av;
                      long agg5 = 0L;
                      DOUBLE_TYPE l5 = QUERY18CUSTOMER1_L1_1.getValueOrDefault(se28.modify(o_orderkey));
                      (/*if */(l5 > 100L) ? agg5 += 1L : 0L);
                      QUERY18.addOrDelOnZero(se27.modify(c_name,c_custkey,o_orderkey,o_orderdate,o_totalprice),(v19 * (v20 * agg5)));
                      n19 = n19->nxt;
                    } while (n19 && (e19 = n19->obj) && h6 == n19->hash &&  QUERY18CUSTOMER1_mapkey1_idxfn::equals(se29, *e19)); 
                  }
                }
              n18 = n18->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY18CUSTOMER1_DELTA_map_01* i20 = static_cast<HashIndex_QUERY18CUSTOMER1_DELTA_map_01*>(QUERY18CUSTOMER1_DELTA.index[0]);
          HashIndex_QUERY18CUSTOMER1_DELTA_map_01::IdxNode* n20; 
          QUERY18CUSTOMER1_DELTA_entry* e20;
        
          for (size_t i = 0; i < i20->size_; i++)
          {
            n20 = i20->buckets_ + i;
            while (n20 && (e20 = n20->obj))
            {
                long c_custkey = e20->C_CUSTKEY;
                STRING_TYPE c_name = e20->C_NAME;
                long v21 = e20->__av;
                { //slice 
                  const HashIndex_QUERY18LINEITEM1_P_1CUSTOMER1_map_1* i21 = static_cast<HashIndex_QUERY18LINEITEM1_P_1CUSTOMER1_map_1*>(QUERY18LINEITEM1_P_1CUSTOMER1.index[2]);
                  const HASH_RES_t h7 = QUERY18LINEITEM1_P_1CUSTOMER1_mapkey1_idxfn::hash(se31.modify1(c_custkey));
                  HashIndex_QUERY18LINEITEM1_P_1CUSTOMER1_map_1::IdxNode* n21 = static_cast<HashIndex_QUERY18LINEITEM1_P_1CUSTOMER1_map_1::IdxNode*>(i21->slice(se31, h7));
                  QUERY18LINEITEM1_P_1CUSTOMER1_entry* e21;
                 
                  if (n21 && (e21 = n21->obj)) {
                    do {                
                      long o_orderkey = e21->O_ORDERKEY;
                      DOUBLE_TYPE o_totalprice = e21->O_TOTALPRICE;
                      date o_orderdate = e21->O_ORDERDATE;
                      long v22 = e21->__av;
                      QUERY18LINEITEM1_P_1.addOrDelOnZero(se30.modify(c_custkey,c_name,o_orderkey,o_totalprice,o_orderdate),(v21 * v22));
                      n21 = n21->nxt;
                    } while (n21 && (e21 = n21->obj) && h7 == n21->hash &&  QUERY18LINEITEM1_P_1CUSTOMER1_mapkey1_idxfn::equals(se31, *e21)); 
                  }
                }
              n20 = n20->nxt;
            }
          }
        }{  // foreach
          const HashIndex_QUERY18CUSTOMER1_DELTA_map_01* i22 = static_cast<HashIndex_QUERY18CUSTOMER1_DELTA_map_01*>(QUERY18CUSTOMER1_DELTA.index[0]);
          HashIndex_QUERY18CUSTOMER1_DELTA_map_01::IdxNode* n22; 
          QUERY18CUSTOMER1_DELTA_entry* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
                long c_custkey = e22->C_CUSTKEY;
                STRING_TYPE c_name = e22->C_NAME;
                long v23 = e22->__av;
                QUERY18ORDERS1_P_1.addOrDelOnZero(se32.modify(c_custkey,c_name),v23);
              n22 = n22->nxt;
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
    QUERY18LINEITEM1_L1_2_DELTA_entry se1;
    QUERY18LINEITEM1_DOMAIN1_entry se2;
    QUERY18_entry se3;
    QUERY18CUSTOMER1_L1_1_entry se4;
    QUERY18CUSTOMER1_L1_1_entry se5;
    QUERY18LINEITEM1_L1_2_DELTA_entry se6;
    QUERY18CUSTOMER1_L1_1_entry se7;
    tuple5_LSDA_D st1;
    QUERY18LINEITEM1_P_1_entry se8;
    QUERY18LINEITEM1_L1_2_DELTA_entry se9;
    QUERY18CUSTOMER1_L1_1_entry se10;
    QUERY18LINEITEM1_L1_2_DELTA_entry se11;
    tuple5_LSDA_D st2;
    QUERY18LINEITEM1_P_1_entry se12;
    QUERY18CUSTOMER1_entry se13;
    QUERY18LINEITEM1_P_1CUSTOMER1_entry se14;
    QUERY18CUSTOMER1_L1_1_entry se15;
    QUERY18ORDERS1_DELTA_entry se16;
    QUERY18_entry se17;
    QUERY18CUSTOMER1_L1_1_entry se18;
    QUERY18CUSTOMER1_L1_1_entry se19;
    QUERY18ORDERS1_P_1_entry se20;
    QUERY18LINEITEM1_P_1_entry se21;
    QUERY18ORDERS1_P_1_entry se22;
    QUERY18LINEITEM1_P_1CUSTOMER1_entry se23;
    QUERY18CUSTOMER1_entry se24;
    QUERY18CUSTOMER1_L1_1_entry se25;
    QUERY18CUSTOMER1_DELTA_entry se26;
    QUERY18_entry se27;
    QUERY18CUSTOMER1_L1_1_entry se28;
    QUERY18CUSTOMER1_entry se29;
    QUERY18LINEITEM1_P_1_entry se30;
    QUERY18LINEITEM1_P_1CUSTOMER1_entry se31;
    QUERY18ORDERS1_P_1_entry se32;
  
    /* Data structures used for storing materialized views */
    QUERY18LINEITEM1_DOMAIN1_map QUERY18LINEITEM1_DOMAIN1;
    QUERY18LINEITEM1_P_1_map QUERY18LINEITEM1_P_1;
    QUERY18LINEITEM1_P_1CUSTOMER1_map QUERY18LINEITEM1_P_1CUSTOMER1;
    QUERY18LINEITEM1_L1_2_DELTA_map QUERY18LINEITEM1_L1_2_DELTA;
    QUERY18ORDERS1_DELTA_map QUERY18ORDERS1_DELTA;
    QUERY18ORDERS1_P_1_map QUERY18ORDERS1_P_1;
    QUERY18CUSTOMER1_DELTA_map QUERY18CUSTOMER1_DELTA;
    QUERY18CUSTOMER1_map QUERY18CUSTOMER1;
    QUERY18CUSTOMER1_L1_1_map QUERY18CUSTOMER1_L1_1;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_ORDERS_map DELTA_ORDERS;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    MultiHashMap<tuple5_LSDA_D,DOUBLE_TYPE,HashIndex<tuple5_LSDA_D,DOUBLE_TYPE> > _c1;
    
  
  };

}
