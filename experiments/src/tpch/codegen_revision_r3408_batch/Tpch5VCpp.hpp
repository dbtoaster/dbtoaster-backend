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
  
  struct NATION_entry {
    long NATION_NATIONKEY; STRING_TYPE NATION_NAME; long NATION_REGIONKEY; STRING_TYPE NATION_COMMENT; long __av; 
    explicit NATION_entry() { /*NATION_NATIONKEY = 0L; NATION_NAME = ""; NATION_REGIONKEY = 0L; NATION_COMMENT = ""; __av = 0L; */ }
    explicit NATION_entry(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3, const long c4) { NATION_NATIONKEY = c0; NATION_NAME = c1; NATION_REGIONKEY = c2; NATION_COMMENT = c3; __av = c4; }
    NATION_entry(const NATION_entry& other) : NATION_NATIONKEY( other.NATION_NATIONKEY ), NATION_NAME( other.NATION_NAME ), NATION_REGIONKEY( other.NATION_REGIONKEY ), NATION_COMMENT( other.NATION_COMMENT ), __av( other.__av ) {}
    FORCE_INLINE NATION_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3) { NATION_NATIONKEY = c0; NATION_NAME = c1; NATION_REGIONKEY = c2; NATION_COMMENT = c3;  return *this; }
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
  
  typedef MultiHashMap<NATION_entry,long,
    HashIndex<NATION_entry,long,NATION_mapkey0123_idxfn,true>
  > NATION_map;
  typedef HashIndex<NATION_entry,long,NATION_mapkey0123_idxfn,true> HashIndex_NATION_map_0123;
  
  struct REGION_entry {
    long REGION_REGIONKEY; STRING_TYPE REGION_NAME; STRING_TYPE REGION_COMMENT; long __av; 
    explicit REGION_entry() { /*REGION_REGIONKEY = 0L; REGION_NAME = ""; REGION_COMMENT = ""; __av = 0L; */ }
    explicit REGION_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { REGION_REGIONKEY = c0; REGION_NAME = c1; REGION_COMMENT = c2; __av = c3; }
    REGION_entry(const REGION_entry& other) : REGION_REGIONKEY( other.REGION_REGIONKEY ), REGION_NAME( other.REGION_NAME ), REGION_COMMENT( other.REGION_COMMENT ), __av( other.__av ) {}
    FORCE_INLINE REGION_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { REGION_REGIONKEY = c0; REGION_NAME = c1; REGION_COMMENT = c2;  return *this; }
    FORCE_INLINE REGION_entry& modify01(const long c0, const STRING_TYPE& c1) { REGION_REGIONKEY = c0; REGION_NAME = c1;  return *this; }
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
  
  typedef MultiHashMap<REGION_entry,long,
    HashIndex<REGION_entry,long,REGION_mapkey012_idxfn,true>,
    HashIndex<REGION_entry,long,REGION_mapkey01_idxfn,false>
  > REGION_map;
  typedef HashIndex<REGION_entry,long,REGION_mapkey012_idxfn,true> HashIndex_REGION_map_012;
  typedef HashIndex<REGION_entry,long,REGION_mapkey01_idxfn,false> HashIndex_REGION_map_01;
  
  struct REVENUE_entry {
    STRING_TYPE N_NAME; DOUBLE_TYPE __av; 
    explicit REVENUE_entry() { /*N_NAME = ""; __av = 0.0; */ }
    explicit REVENUE_entry(const STRING_TYPE& c0, const DOUBLE_TYPE c1) { N_NAME = c0; __av = c1; }
    REVENUE_entry(const REVENUE_entry& other) : N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_entry& modify(const STRING_TYPE& c0) { N_NAME = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_entry& x, const REVENUE_entry& y) {
      return x.N_NAME == y.N_NAME;
    }
  };
  
  typedef MultiHashMap<REVENUE_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_entry,DOUBLE_TYPE,REVENUE_mapkey0_idxfn,true>
  > REVENUE_map;
  typedef HashIndex<REVENUE_entry,DOUBLE_TYPE,REVENUE_mapkey0_idxfn,true> HashIndex_REVENUE_map_0;
  
  struct REVENUESUPPLIER1_DELTA_entry {
    long L_SUPPKEY; long C_NATIONKEY; long __av; 
    explicit REVENUESUPPLIER1_DELTA_entry() { /*L_SUPPKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUESUPPLIER1_DELTA_entry(const long c0, const long c1, const long c2) { L_SUPPKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUESUPPLIER1_DELTA_entry(const REVENUESUPPLIER1_DELTA_entry& other) : L_SUPPKEY( other.L_SUPPKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER1_DELTA_entry& modify(const long c0, const long c1) { L_SUPPKEY = c0; C_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_SUPPKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_DELTA_entry& x, const REVENUESUPPLIER1_DELTA_entry& y) {
      return x.L_SUPPKEY == y.L_SUPPKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER1_DELTA_entry,long,
    HashIndex<REVENUESUPPLIER1_DELTA_entry,long,REVENUESUPPLIER1_DELTA_mapkey01_idxfn,true>
  > REVENUESUPPLIER1_DELTA_map;
  typedef HashIndex<REVENUESUPPLIER1_DELTA_entry,long,REVENUESUPPLIER1_DELTA_mapkey01_idxfn,true> HashIndex_REVENUESUPPLIER1_DELTA_map_01;
  
  struct REVENUESUPPLIER1_P_2_entry {
    long L_SUPPKEY; long C_NATIONKEY; DOUBLE_TYPE __av; 
    explicit REVENUESUPPLIER1_P_2_entry() { /*L_SUPPKEY = 0L; C_NATIONKEY = 0L; __av = 0.0; */ }
    explicit REVENUESUPPLIER1_P_2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { L_SUPPKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUESUPPLIER1_P_2_entry(const REVENUESUPPLIER1_P_2_entry& other) : L_SUPPKEY( other.L_SUPPKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER1_P_2_entry& modify(const long c0, const long c1) { L_SUPPKEY = c0; C_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_SUPPKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_P_2_entry& x, const REVENUESUPPLIER1_P_2_entry& y) {
      return x.L_SUPPKEY == y.L_SUPPKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER1_P_2_entry,DOUBLE_TYPE,
    HashIndex<REVENUESUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2_mapkey01_idxfn,true>
  > REVENUESUPPLIER1_P_2_map;
  typedef HashIndex<REVENUESUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2_mapkey01_idxfn,true> HashIndex_REVENUESUPPLIER1_P_2_map_01;
  
  struct REVENUESUPPLIER1_P_2ORDERS1_P_1_entry {
    long O_ORDERKEY; long L_SUPPKEY; DOUBLE_TYPE __av; 
    explicit REVENUESUPPLIER1_P_2ORDERS1_P_1_entry() { /*O_ORDERKEY = 0L; L_SUPPKEY = 0L; __av = 0.0; */ }
    explicit REVENUESUPPLIER1_P_2ORDERS1_P_1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { O_ORDERKEY = c0; L_SUPPKEY = c1; __av = c2; }
    REVENUESUPPLIER1_P_2ORDERS1_P_1_entry(const REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), L_SUPPKEY( other.L_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& modify(const long c0, const long c1) { O_ORDERKEY = c0; L_SUPPKEY = c1;  return *this; }
    FORCE_INLINE REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& modify0(const long c0) { O_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& modify1(const long c1) { L_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.L_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& x, const REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.L_SUPPKEY == y.L_SUPPKEY;
    }
  };
  
  struct REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& x, const REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  struct REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& x, const REVENUESUPPLIER1_P_2ORDERS1_P_1_entry& y) {
      return x.L_SUPPKEY == y.L_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER1_P_2ORDERS1_P_1_entry,DOUBLE_TYPE,
    HashIndex<REVENUESUPPLIER1_P_2ORDERS1_P_1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey01_idxfn,true>,
    HashIndex<REVENUESUPPLIER1_P_2ORDERS1_P_1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey0_idxfn,false>,
    HashIndex<REVENUESUPPLIER1_P_2ORDERS1_P_1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey1_idxfn,false>
  > REVENUESUPPLIER1_P_2ORDERS1_P_1_map;
  typedef HashIndex<REVENUESUPPLIER1_P_2ORDERS1_P_1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey01_idxfn,true> HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_01;
  typedef HashIndex<REVENUESUPPLIER1_P_2ORDERS1_P_1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey0_idxfn,false> HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_0;
  typedef HashIndex<REVENUESUPPLIER1_P_2ORDERS1_P_1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey1_idxfn,false> HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_1;
  
  struct REVENUESUPPLIER1_P_2CUSTOMER1_entry {
    long L_SUPPKEY; long C_CUSTKEY; DOUBLE_TYPE __av; 
    explicit REVENUESUPPLIER1_P_2CUSTOMER1_entry() { /*L_SUPPKEY = 0L; C_CUSTKEY = 0L; __av = 0.0; */ }
    explicit REVENUESUPPLIER1_P_2CUSTOMER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { L_SUPPKEY = c0; C_CUSTKEY = c1; __av = c2; }
    REVENUESUPPLIER1_P_2CUSTOMER1_entry(const REVENUESUPPLIER1_P_2CUSTOMER1_entry& other) : L_SUPPKEY( other.L_SUPPKEY ), C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER1_P_2CUSTOMER1_entry& modify(const long c0, const long c1) { L_SUPPKEY = c0; C_CUSTKEY = c1;  return *this; }
    FORCE_INLINE REVENUESUPPLIER1_P_2CUSTOMER1_entry& modify1(const long c1) { C_CUSTKEY = c1;  return *this; }
    FORCE_INLINE REVENUESUPPLIER1_P_2CUSTOMER1_entry& modify0(const long c0) { L_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER1_P_2CUSTOMER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_P_2CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_SUPPKEY);
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_P_2CUSTOMER1_entry& x, const REVENUESUPPLIER1_P_2CUSTOMER1_entry& y) {
      return x.L_SUPPKEY == y.L_SUPPKEY && x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  struct REVENUESUPPLIER1_P_2CUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_P_2CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_P_2CUSTOMER1_entry& x, const REVENUESUPPLIER1_P_2CUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  struct REVENUESUPPLIER1_P_2CUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_P_2CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_P_2CUSTOMER1_entry& x, const REVENUESUPPLIER1_P_2CUSTOMER1_entry& y) {
      return x.L_SUPPKEY == y.L_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER1_P_2CUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<REVENUESUPPLIER1_P_2CUSTOMER1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2CUSTOMER1_mapkey01_idxfn,true>,
    HashIndex<REVENUESUPPLIER1_P_2CUSTOMER1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2CUSTOMER1_mapkey1_idxfn,false>,
    HashIndex<REVENUESUPPLIER1_P_2CUSTOMER1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2CUSTOMER1_mapkey0_idxfn,false>
  > REVENUESUPPLIER1_P_2CUSTOMER1_map;
  typedef HashIndex<REVENUESUPPLIER1_P_2CUSTOMER1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2CUSTOMER1_mapkey01_idxfn,true> HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1_map_01;
  typedef HashIndex<REVENUESUPPLIER1_P_2CUSTOMER1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2CUSTOMER1_mapkey1_idxfn,false> HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1_map_1;
  typedef HashIndex<REVENUESUPPLIER1_P_2CUSTOMER1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_P_2CUSTOMER1_mapkey0_idxfn,false> HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1_map_0;
  
  struct REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry {
    long O_ORDERKEY; long C_CUSTKEY; long __av; 
    explicit REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry() { /*O_ORDERKEY = 0L; C_CUSTKEY = 0L; __av = 0L; */ }
    explicit REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry(const long c0, const long c1, const long c2) { O_ORDERKEY = c0; C_CUSTKEY = c1; __av = c2; }
    REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry(const REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& modify(const long c0, const long c1) { O_ORDERKEY = c0; C_CUSTKEY = c1;  return *this; }
    FORCE_INLINE REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& modify0(const long c0) { O_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& modify1(const long c1) { C_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& x, const REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  struct REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& x, const REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  struct REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& x, const REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry,long,
    HashIndex<REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry,long,REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey01_idxfn,true>,
    HashIndex<REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry,long,REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey0_idxfn,false>,
    HashIndex<REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry,long,REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey1_idxfn,false>
  > REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map;
  typedef HashIndex<REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry,long,REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey01_idxfn,true> HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_01;
  typedef HashIndex<REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry,long,REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey0_idxfn,false> HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_0;
  typedef HashIndex<REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry,long,REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey1_idxfn,false> HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_1;
  
  struct REVENUELINEITEM1_DELTA_entry {
    long O_ORDERKEY; long L_SUPPKEY; DOUBLE_TYPE __av; 
    explicit REVENUELINEITEM1_DELTA_entry() { /*O_ORDERKEY = 0L; L_SUPPKEY = 0L; __av = 0.0; */ }
    explicit REVENUELINEITEM1_DELTA_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { O_ORDERKEY = c0; L_SUPPKEY = c1; __av = c2; }
    REVENUELINEITEM1_DELTA_entry(const REVENUELINEITEM1_DELTA_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), L_SUPPKEY( other.L_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_DELTA_entry& modify(const long c0, const long c1) { O_ORDERKEY = c0; L_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.L_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_DELTA_entry& x, const REVENUELINEITEM1_DELTA_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.L_SUPPKEY == y.L_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,REVENUELINEITEM1_DELTA_mapkey01_idxfn,true>
  > REVENUELINEITEM1_DELTA_map;
  typedef HashIndex<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,REVENUELINEITEM1_DELTA_mapkey01_idxfn,true> HashIndex_REVENUELINEITEM1_DELTA_map_01;
  
  struct REVENUELINEITEM1_T_2_entry {
    long L_SUPPKEY; long C_NATIONKEY; long __av; 
    explicit REVENUELINEITEM1_T_2_entry() { /*L_SUPPKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUELINEITEM1_T_2_entry(const long c0, const long c1, const long c2) { L_SUPPKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUELINEITEM1_T_2_entry(const REVENUELINEITEM1_T_2_entry& other) : L_SUPPKEY( other.L_SUPPKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_T_2_entry& modify(const long c0, const long c1) { L_SUPPKEY = c0; C_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUELINEITEM1_T_2_entry& modify0(const long c0) { L_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_T_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_SUPPKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_2_entry& x, const REVENUELINEITEM1_T_2_entry& y) {
      return x.L_SUPPKEY == y.L_SUPPKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  struct REVENUELINEITEM1_T_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_2_entry& x, const REVENUELINEITEM1_T_2_entry& y) {
      return x.L_SUPPKEY == y.L_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_T_2_entry,long,
    HashIndex<REVENUELINEITEM1_T_2_entry,long,REVENUELINEITEM1_T_2_mapkey01_idxfn,true>,
    HashIndex<REVENUELINEITEM1_T_2_entry,long,REVENUELINEITEM1_T_2_mapkey0_idxfn,false>
  > REVENUELINEITEM1_T_2_map;
  typedef HashIndex<REVENUELINEITEM1_T_2_entry,long,REVENUELINEITEM1_T_2_mapkey01_idxfn,true> HashIndex_REVENUELINEITEM1_T_2_map_01;
  typedef HashIndex<REVENUELINEITEM1_T_2_entry,long,REVENUELINEITEM1_T_2_mapkey0_idxfn,false> HashIndex_REVENUELINEITEM1_T_2_map_0;
  
  struct REVENUELINEITEM1_T_3_entry {
    long O_ORDERKEY; long C_NATIONKEY; long __av; 
    explicit REVENUELINEITEM1_T_3_entry() { /*O_ORDERKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUELINEITEM1_T_3_entry(const long c0, const long c1, const long c2) { O_ORDERKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUELINEITEM1_T_3_entry(const REVENUELINEITEM1_T_3_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_T_3_entry& modify(const long c0, const long c1) { O_ORDERKEY = c0; C_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUELINEITEM1_T_3_entry& modify0(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_T_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_3_entry& x, const REVENUELINEITEM1_T_3_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  struct REVENUELINEITEM1_T_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_3_entry& x, const REVENUELINEITEM1_T_3_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_T_3_entry,long,
    HashIndex<REVENUELINEITEM1_T_3_entry,long,REVENUELINEITEM1_T_3_mapkey01_idxfn,true>,
    HashIndex<REVENUELINEITEM1_T_3_entry,long,REVENUELINEITEM1_T_3_mapkey0_idxfn,false>
  > REVENUELINEITEM1_T_3_map;
  typedef HashIndex<REVENUELINEITEM1_T_3_entry,long,REVENUELINEITEM1_T_3_mapkey01_idxfn,true> HashIndex_REVENUELINEITEM1_T_3_map_01;
  typedef HashIndex<REVENUELINEITEM1_T_3_entry,long,REVENUELINEITEM1_T_3_mapkey0_idxfn,false> HashIndex_REVENUELINEITEM1_T_3_map_0;
  
  struct REVENUEORDERS1_DELTA_entry {
    long O_ORDERKEY; long C_CUSTKEY; long __av; 
    explicit REVENUEORDERS1_DELTA_entry() { /*O_ORDERKEY = 0L; C_CUSTKEY = 0L; __av = 0L; */ }
    explicit REVENUEORDERS1_DELTA_entry(const long c0, const long c1, const long c2) { O_ORDERKEY = c0; C_CUSTKEY = c1; __av = c2; }
    REVENUEORDERS1_DELTA_entry(const REVENUEORDERS1_DELTA_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUEORDERS1_DELTA_entry& modify(const long c0, const long c1) { O_ORDERKEY = c0; C_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEORDERS1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_DELTA_entry& x, const REVENUEORDERS1_DELTA_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEORDERS1_DELTA_entry,long,
    HashIndex<REVENUEORDERS1_DELTA_entry,long,REVENUEORDERS1_DELTA_mapkey01_idxfn,true>
  > REVENUEORDERS1_DELTA_map;
  typedef HashIndex<REVENUEORDERS1_DELTA_entry,long,REVENUEORDERS1_DELTA_mapkey01_idxfn,true> HashIndex_REVENUEORDERS1_DELTA_map_01;
  
  struct REVENUEORDERS1_T_2_entry {
    long C_NATIONKEY; long O_ORDERKEY; DOUBLE_TYPE __av; 
    explicit REVENUEORDERS1_T_2_entry() { /*C_NATIONKEY = 0L; O_ORDERKEY = 0L; __av = 0.0; */ }
    explicit REVENUEORDERS1_T_2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { C_NATIONKEY = c0; O_ORDERKEY = c1; __av = c2; }
    REVENUEORDERS1_T_2_entry(const REVENUEORDERS1_T_2_entry& other) : C_NATIONKEY( other.C_NATIONKEY ), O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUEORDERS1_T_2_entry& modify(const long c0, const long c1) { C_NATIONKEY = c0; O_ORDERKEY = c1;  return *this; }
    FORCE_INLINE REVENUEORDERS1_T_2_entry& modify1(const long c1) { O_ORDERKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEORDERS1_T_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_T_2_entry& x, const REVENUEORDERS1_T_2_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  struct REVENUEORDERS1_T_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_T_2_entry& x, const REVENUEORDERS1_T_2_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEORDERS1_T_2_entry,DOUBLE_TYPE,
    HashIndex<REVENUEORDERS1_T_2_entry,DOUBLE_TYPE,REVENUEORDERS1_T_2_mapkey01_idxfn,true>,
    HashIndex<REVENUEORDERS1_T_2_entry,DOUBLE_TYPE,REVENUEORDERS1_T_2_mapkey1_idxfn,false>
  > REVENUEORDERS1_T_2_map;
  typedef HashIndex<REVENUEORDERS1_T_2_entry,DOUBLE_TYPE,REVENUEORDERS1_T_2_mapkey01_idxfn,true> HashIndex_REVENUEORDERS1_T_2_map_01;
  typedef HashIndex<REVENUEORDERS1_T_2_entry,DOUBLE_TYPE,REVENUEORDERS1_T_2_mapkey1_idxfn,false> HashIndex_REVENUEORDERS1_T_2_map_1;
  
  struct REVENUEORDERS1_T_3_entry {
    long C_CUSTKEY; long C_NATIONKEY; long __av; 
    explicit REVENUEORDERS1_T_3_entry() { /*C_CUSTKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUEORDERS1_T_3_entry(const long c0, const long c1, const long c2) { C_CUSTKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUEORDERS1_T_3_entry(const REVENUEORDERS1_T_3_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUEORDERS1_T_3_entry& modify(const long c0, const long c1) { C_CUSTKEY = c0; C_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUEORDERS1_T_3_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEORDERS1_T_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_T_3_entry& x, const REVENUEORDERS1_T_3_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  struct REVENUEORDERS1_T_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_T_3_entry& x, const REVENUEORDERS1_T_3_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEORDERS1_T_3_entry,long,
    HashIndex<REVENUEORDERS1_T_3_entry,long,REVENUEORDERS1_T_3_mapkey01_idxfn,true>,
    HashIndex<REVENUEORDERS1_T_3_entry,long,REVENUEORDERS1_T_3_mapkey0_idxfn,false>
  > REVENUEORDERS1_T_3_map;
  typedef HashIndex<REVENUEORDERS1_T_3_entry,long,REVENUEORDERS1_T_3_mapkey01_idxfn,true> HashIndex_REVENUEORDERS1_T_3_map_01;
  typedef HashIndex<REVENUEORDERS1_T_3_entry,long,REVENUEORDERS1_T_3_mapkey0_idxfn,false> HashIndex_REVENUEORDERS1_T_3_map_0;
  
  struct REVENUECUSTOMER1_DELTA_entry {
    long C_CUSTKEY; long C_NATIONKEY; long __av; 
    explicit REVENUECUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUECUSTOMER1_DELTA_entry(const long c0, const long c1, const long c2) { C_CUSTKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUECUSTOMER1_DELTA_entry(const REVENUECUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1_DELTA_entry& modify(const long c0, const long c1) { C_CUSTKEY = c0; C_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_DELTA_entry& x, const REVENUECUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1_DELTA_entry,long,
    HashIndex<REVENUECUSTOMER1_DELTA_entry,long,REVENUECUSTOMER1_DELTA_mapkey01_idxfn,true>
  > REVENUECUSTOMER1_DELTA_map;
  typedef HashIndex<REVENUECUSTOMER1_DELTA_entry,long,REVENUECUSTOMER1_DELTA_mapkey01_idxfn,true> HashIndex_REVENUECUSTOMER1_DELTA_map_01;
  
  struct REVENUECUSTOMER1_P_1_entry {
    long C_NATIONKEY; STRING_TYPE N_NAME; long __av; 
    explicit REVENUECUSTOMER1_P_1_entry() { /*C_NATIONKEY = 0L; N_NAME = ""; __av = 0L; */ }
    explicit REVENUECUSTOMER1_P_1_entry(const long c0, const STRING_TYPE& c1, const long c2) { C_NATIONKEY = c0; N_NAME = c1; __av = c2; }
    REVENUECUSTOMER1_P_1_entry(const REVENUECUSTOMER1_P_1_entry& other) : C_NATIONKEY( other.C_NATIONKEY ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1_P_1_entry& modify(const long c0, const STRING_TYPE& c1) { C_NATIONKEY = c0; N_NAME = c1;  return *this; }
    FORCE_INLINE REVENUECUSTOMER1_P_1_entry& modify0(const long c0) { C_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_P_1_entry& x, const REVENUECUSTOMER1_P_1_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  struct REVENUECUSTOMER1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_P_1_entry& x, const REVENUECUSTOMER1_P_1_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1_P_1_entry,long,
    HashIndex<REVENUECUSTOMER1_P_1_entry,long,REVENUECUSTOMER1_P_1_mapkey01_idxfn,true>,
    HashIndex<REVENUECUSTOMER1_P_1_entry,long,REVENUECUSTOMER1_P_1_mapkey0_idxfn,false>
  > REVENUECUSTOMER1_P_1_map;
  typedef HashIndex<REVENUECUSTOMER1_P_1_entry,long,REVENUECUSTOMER1_P_1_mapkey01_idxfn,true> HashIndex_REVENUECUSTOMER1_P_1_map_01;
  typedef HashIndex<REVENUECUSTOMER1_P_1_entry,long,REVENUECUSTOMER1_P_1_mapkey0_idxfn,false> HashIndex_REVENUECUSTOMER1_P_1_map_0;
  
  struct REVENUECUSTOMER1_P_2_entry {
    long C_NATIONKEY; long C_CUSTKEY; DOUBLE_TYPE __av; 
    explicit REVENUECUSTOMER1_P_2_entry() { /*C_NATIONKEY = 0L; C_CUSTKEY = 0L; __av = 0.0; */ }
    explicit REVENUECUSTOMER1_P_2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { C_NATIONKEY = c0; C_CUSTKEY = c1; __av = c2; }
    REVENUECUSTOMER1_P_2_entry(const REVENUECUSTOMER1_P_2_entry& other) : C_NATIONKEY( other.C_NATIONKEY ), C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1_P_2_entry& modify(const long c0, const long c1) { C_NATIONKEY = c0; C_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_P_2_entry& x, const REVENUECUSTOMER1_P_2_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1_P_2_entry,DOUBLE_TYPE,
    HashIndex<REVENUECUSTOMER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1_P_2_mapkey01_idxfn,true>
  > REVENUECUSTOMER1_P_2_map;
  typedef HashIndex<REVENUECUSTOMER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1_P_2_mapkey01_idxfn,true> HashIndex_REVENUECUSTOMER1_P_2_map_01;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const REVENUE_map& _REVENUE = get_REVENUE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(REVENUE), _REVENUE, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const REVENUE_map& get_REVENUE() const {
      return REVENUE;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    REVENUE_map REVENUE;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c2 = Udate(STRING_TYPE("1995-1-1"));
      c1 = Udate(STRING_TYPE("1994-1-1"));
      c3 = STRING_TYPE("ASIA");
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

        REVENUELINEITEM1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                long o_orderkey = DELTA_LINEITEM.orderkey[i];
                // long l_partkey = DELTA_LINEITEM.partkey[i];
                long l_suppkey = DELTA_LINEITEM.suppkey[i];
                // long l_linenumber = DELTA_LINEITEM.linenumber[i];
                // DOUBLE_TYPE l_quantity = DELTA_LINEITEM.quantity[i];
                DOUBLE_TYPE l_extendedprice = DELTA_LINEITEM.extendedprice[i];
                DOUBLE_TYPE l_discount = DELTA_LINEITEM.discount[i];
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
                REVENUELINEITEM1_DELTA.addOrDelOnZero(se1.modify(o_orderkey,l_suppkey),(v1 * (l_extendedprice * (1L + (-1L * l_discount)))));
          }
        }

        {  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_01* i2 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_01*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_01::IdxNode* n2; 
          REVENUELINEITEM1_DELTA_entry* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
                long o_orderkey = e2->O_ORDERKEY;
                long l_suppkey = e2->L_SUPPKEY;
                DOUBLE_TYPE v2 = e2->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_T_2_map_0* i3 = static_cast<HashIndex_REVENUELINEITEM1_T_2_map_0*>(REVENUELINEITEM1_T_2.index[1]);
                  const HASH_RES_t h2 = REVENUELINEITEM1_T_2_mapkey0_idxfn::hash(se5.modify0(l_suppkey));
                  HashIndex_REVENUELINEITEM1_T_2_map_0::IdxNode* n3 = static_cast<HashIndex_REVENUELINEITEM1_T_2_map_0::IdxNode*>(i3->slice(se5, h2));
                  REVENUELINEITEM1_T_2_entry* e3;
                 
                  if (n3 && (e3 = n3->obj)) {
                    do {                
                      long c_nationkey = e3->C_NATIONKEY;
                      long v3 = e3->__av;
                      { //slice 
                        const HashIndex_REVENUECUSTOMER1_P_1_map_0* i4 = static_cast<HashIndex_REVENUECUSTOMER1_P_1_map_0*>(REVENUECUSTOMER1_P_1.index[1]);
                        const HASH_RES_t h1 = REVENUECUSTOMER1_P_1_mapkey0_idxfn::hash(se4.modify0(c_nationkey));
                        HashIndex_REVENUECUSTOMER1_P_1_map_0::IdxNode* n4 = static_cast<HashIndex_REVENUECUSTOMER1_P_1_map_0::IdxNode*>(i4->slice(se4, h1));
                        REVENUECUSTOMER1_P_1_entry* e4;
                       
                        if (n4 && (e4 = n4->obj)) {
                          do {                
                            STRING_TYPE n_name = e4->N_NAME;
                            long v4 = e4->__av;
                            REVENUE.addOrDelOnZero(se2.modify(n_name),(v2 * (v3 * (REVENUELINEITEM1_T_3.getValueOrDefault(se3.modify(o_orderkey,c_nationkey)) * v4))));
                            n4 = n4->nxt;
                          } while (n4 && (e4 = n4->obj) && h1 == n4->hash &&  REVENUECUSTOMER1_P_1_mapkey0_idxfn::equals(se4, *e4)); 
                        }
                      }
                      n3 = n3->nxt;
                    } while (n3 && (e3 = n3->obj) && h2 == n3->hash &&  REVENUELINEITEM1_T_2_mapkey0_idxfn::equals(se5, *e3)); 
                  }
                }
              n2 = n2->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_01* i5 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_01*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_01::IdxNode* n5; 
          REVENUELINEITEM1_DELTA_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long o_orderkey = e5->O_ORDERKEY;
                long l_suppkey = e5->L_SUPPKEY;
                DOUBLE_TYPE v5 = e5->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_T_3_map_0* i6 = static_cast<HashIndex_REVENUELINEITEM1_T_3_map_0*>(REVENUELINEITEM1_T_3.index[1]);
                  const HASH_RES_t h3 = REVENUELINEITEM1_T_3_mapkey0_idxfn::hash(se7.modify0(o_orderkey));
                  HashIndex_REVENUELINEITEM1_T_3_map_0::IdxNode* n6 = static_cast<HashIndex_REVENUELINEITEM1_T_3_map_0::IdxNode*>(i6->slice(se7, h3));
                  REVENUELINEITEM1_T_3_entry* e6;
                 
                  if (n6 && (e6 = n6->obj)) {
                    do {                
                      long c_nationkey = e6->C_NATIONKEY;
                      long v6 = e6->__av;
                      REVENUESUPPLIER1_P_2.addOrDelOnZero(se6.modify(l_suppkey,c_nationkey),(v5 * v6));
                      n6 = n6->nxt;
                    } while (n6 && (e6 = n6->obj) && h3 == n6->hash &&  REVENUELINEITEM1_T_3_mapkey0_idxfn::equals(se7, *e6)); 
                  }
                }
              n5 = n5->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_01* i7 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_01*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_01::IdxNode* n7; 
          REVENUELINEITEM1_DELTA_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long o_orderkey = e7->O_ORDERKEY;
                long l_suppkey = e7->L_SUPPKEY;
                DOUBLE_TYPE v7 = e7->__av;
                REVENUESUPPLIER1_P_2ORDERS1_P_1.addOrDelOnZero(se8.modify(o_orderkey,l_suppkey),v7);
              n7 = n7->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_01* i8 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_01*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_01::IdxNode* n8; 
          REVENUELINEITEM1_DELTA_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long o_orderkey = e8->O_ORDERKEY;
                long l_suppkey = e8->L_SUPPKEY;
                DOUBLE_TYPE v8 = e8->__av;
                { //slice 
                  const HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_0* i9 = static_cast<HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_0*>(REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1.index[1]);
                  const HASH_RES_t h4 = REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey0_idxfn::hash(se10.modify0(o_orderkey));
                  HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_0::IdxNode* n9 = static_cast<HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_0::IdxNode*>(i9->slice(se10, h4));
                  REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry* e9;
                 
                  if (n9 && (e9 = n9->obj)) {
                    do {                
                      long c_custkey = e9->C_CUSTKEY;
                      long v9 = e9->__av;
                      REVENUESUPPLIER1_P_2CUSTOMER1.addOrDelOnZero(se9.modify(l_suppkey,c_custkey),(v8 * v9));
                      n9 = n9->nxt;
                    } while (n9 && (e9 = n9->obj) && h4 == n9->hash &&  REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey0_idxfn::equals(se10, *e9)); 
                  }
                }
              n8 = n8->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_01* i10 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_01*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_01::IdxNode* n10; 
          REVENUELINEITEM1_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long o_orderkey = e10->O_ORDERKEY;
                long l_suppkey = e10->L_SUPPKEY;
                DOUBLE_TYPE v10 = e10->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_T_2_map_0* i11 = static_cast<HashIndex_REVENUELINEITEM1_T_2_map_0*>(REVENUELINEITEM1_T_2.index[1]);
                  const HASH_RES_t h5 = REVENUELINEITEM1_T_2_mapkey0_idxfn::hash(se12.modify0(l_suppkey));
                  HashIndex_REVENUELINEITEM1_T_2_map_0::IdxNode* n11 = static_cast<HashIndex_REVENUELINEITEM1_T_2_map_0::IdxNode*>(i11->slice(se12, h5));
                  REVENUELINEITEM1_T_2_entry* e11;
                 
                  if (n11 && (e11 = n11->obj)) {
                    do {                
                      long c_nationkey = e11->C_NATIONKEY;
                      long v11 = e11->__av;
                      REVENUEORDERS1_T_2.addOrDelOnZero(se11.modify(c_nationkey,o_orderkey),(v10 * v11));
                      n11 = n11->nxt;
                    } while (n11 && (e11 = n11->obj) && h5 == n11->hash &&  REVENUELINEITEM1_T_2_mapkey0_idxfn::equals(se12, *e11)); 
                  }
                }
              n10 = n10->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_01* i12 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_01*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_01::IdxNode* n12; 
          REVENUELINEITEM1_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long o_orderkey = e12->O_ORDERKEY;
                long l_suppkey = e12->L_SUPPKEY;
                DOUBLE_TYPE v12 = e12->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_T_2_map_0* i13 = static_cast<HashIndex_REVENUELINEITEM1_T_2_map_0*>(REVENUELINEITEM1_T_2.index[1]);
                  const HASH_RES_t h7 = REVENUELINEITEM1_T_2_mapkey0_idxfn::hash(se15.modify0(l_suppkey));
                  HashIndex_REVENUELINEITEM1_T_2_map_0::IdxNode* n13 = static_cast<HashIndex_REVENUELINEITEM1_T_2_map_0::IdxNode*>(i13->slice(se15, h7));
                  REVENUELINEITEM1_T_2_entry* e13;
                 
                  if (n13 && (e13 = n13->obj)) {
                    do {                
                      long c_nationkey = e13->C_NATIONKEY;
                      long v13 = e13->__av;
                      { //slice 
                        const HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_0* i14 = static_cast<HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_0*>(REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1.index[1]);
                        const HASH_RES_t h6 = REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey0_idxfn::hash(se14.modify0(o_orderkey));
                        HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_0::IdxNode* n14 = static_cast<HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_0::IdxNode*>(i14->slice(se14, h6));
                        REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry* e14;
                       
                        if (n14 && (e14 = n14->obj)) {
                          do {                
                            long c_custkey = e14->C_CUSTKEY;
                            long v14 = e14->__av;
                            REVENUECUSTOMER1_P_2.addOrDelOnZero(se13.modify(c_nationkey,c_custkey),(v12 * (v13 * v14)));
                            n14 = n14->nxt;
                          } while (n14 && (e14 = n14->obj) && h6 == n14->hash &&  REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey0_idxfn::equals(se14, *e14)); 
                        }
                      }
                      n13 = n13->nxt;
                    } while (n13 && (e13 = n13->obj) && h7 == n13->hash &&  REVENUELINEITEM1_T_2_mapkey0_idxfn::equals(se15, *e13)); 
                  }
                }
              n12 = n12->nxt;
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

        REVENUEORDERS1_DELTA.clear();
        { 
          for (size_t i = 0; i < DELTA_ORDERS.size; i++) 
          {
                long o_orderkey = DELTA_ORDERS.orderkey[i];
                long c_custkey = DELTA_ORDERS.custkey[i];
                // STRING_TYPE o_orderstatus = DELTA_ORDERS.orderstatus[i];
                // DOUBLE_TYPE o_totalprice = DELTA_ORDERS.totalprice[i];
                date o_orderdate = DELTA_ORDERS.orderdate[i];
                // STRING_TYPE o_orderpriority = DELTA_ORDERS.orderpriority[i];
                // STRING_TYPE o_clerk = DELTA_ORDERS.clerk[i];
                // long o_shippriority = DELTA_ORDERS.shippriority[i];
                // STRING_TYPE o_comment = DELTA_ORDERS.comment[i];
                long v15 = 1L;
                (/*if */(o_orderdate >= c1 && c2 > o_orderdate) ? REVENUEORDERS1_DELTA.addOrDelOnZero(se16.modify(o_orderkey,c_custkey),v15) : (void)0);
          }
        }

        {  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i16 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n16; 
          REVENUEORDERS1_DELTA_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long o_orderkey = e16->O_ORDERKEY;
                long c_custkey = e16->C_CUSTKEY;
                long v16 = e16->__av;
                { //slice 
                  const HashIndex_REVENUEORDERS1_T_2_map_1* i17 = static_cast<HashIndex_REVENUEORDERS1_T_2_map_1*>(REVENUEORDERS1_T_2.index[1]);
                  const HASH_RES_t h9 = REVENUEORDERS1_T_2_mapkey1_idxfn::hash(se20.modify1(o_orderkey));
                  HashIndex_REVENUEORDERS1_T_2_map_1::IdxNode* n17 = static_cast<HashIndex_REVENUEORDERS1_T_2_map_1::IdxNode*>(i17->slice(se20, h9));
                  REVENUEORDERS1_T_2_entry* e17;
                 
                  if (n17 && (e17 = n17->obj)) {
                    do {                
                      long c_nationkey = e17->C_NATIONKEY;
                      DOUBLE_TYPE v17 = e17->__av;
                      { //slice 
                        const HashIndex_REVENUECUSTOMER1_P_1_map_0* i18 = static_cast<HashIndex_REVENUECUSTOMER1_P_1_map_0*>(REVENUECUSTOMER1_P_1.index[1]);
                        const HASH_RES_t h8 = REVENUECUSTOMER1_P_1_mapkey0_idxfn::hash(se19.modify0(c_nationkey));
                        HashIndex_REVENUECUSTOMER1_P_1_map_0::IdxNode* n18 = static_cast<HashIndex_REVENUECUSTOMER1_P_1_map_0::IdxNode*>(i18->slice(se19, h8));
                        REVENUECUSTOMER1_P_1_entry* e18;
                       
                        if (n18 && (e18 = n18->obj)) {
                          do {                
                            STRING_TYPE n_name = e18->N_NAME;
                            long v18 = e18->__av;
                            REVENUE.addOrDelOnZero(se17.modify(n_name),(v16 * (v17 * (REVENUEORDERS1_T_3.getValueOrDefault(se18.modify(c_custkey,c_nationkey)) * v18))));
                            n18 = n18->nxt;
                          } while (n18 && (e18 = n18->obj) && h8 == n18->hash &&  REVENUECUSTOMER1_P_1_mapkey0_idxfn::equals(se19, *e18)); 
                        }
                      }
                      n17 = n17->nxt;
                    } while (n17 && (e17 = n17->obj) && h9 == n17->hash &&  REVENUEORDERS1_T_2_mapkey1_idxfn::equals(se20, *e17)); 
                  }
                }
              n16 = n16->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i19 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n19; 
          REVENUEORDERS1_DELTA_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long o_orderkey = e19->O_ORDERKEY;
                long c_custkey = e19->C_CUSTKEY;
                long v19 = e19->__av;
                { //slice 
                  const HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_0* i20 = static_cast<HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_0*>(REVENUESUPPLIER1_P_2ORDERS1_P_1.index[1]);
                  const HASH_RES_t h11 = REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey0_idxfn::hash(se23.modify0(o_orderkey));
                  HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_0::IdxNode* n20 = static_cast<HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_0::IdxNode*>(i20->slice(se23, h11));
                  REVENUESUPPLIER1_P_2ORDERS1_P_1_entry* e20;
                 
                  if (n20 && (e20 = n20->obj)) {
                    do {                
                      long l_suppkey = e20->L_SUPPKEY;
                      DOUBLE_TYPE v20 = e20->__av;
                      { //slice 
                        const HashIndex_REVENUEORDERS1_T_3_map_0* i21 = static_cast<HashIndex_REVENUEORDERS1_T_3_map_0*>(REVENUEORDERS1_T_3.index[1]);
                        const HASH_RES_t h10 = REVENUEORDERS1_T_3_mapkey0_idxfn::hash(se22.modify0(c_custkey));
                        HashIndex_REVENUEORDERS1_T_3_map_0::IdxNode* n21 = static_cast<HashIndex_REVENUEORDERS1_T_3_map_0::IdxNode*>(i21->slice(se22, h10));
                        REVENUEORDERS1_T_3_entry* e21;
                       
                        if (n21 && (e21 = n21->obj)) {
                          do {                
                            long c_nationkey = e21->C_NATIONKEY;
                            long v21 = e21->__av;
                            REVENUESUPPLIER1_P_2.addOrDelOnZero(se21.modify(l_suppkey,c_nationkey),(v19 * (v20 * v21)));
                            n21 = n21->nxt;
                          } while (n21 && (e21 = n21->obj) && h10 == n21->hash &&  REVENUEORDERS1_T_3_mapkey0_idxfn::equals(se22, *e21)); 
                        }
                      }
                      n20 = n20->nxt;
                    } while (n20 && (e20 = n20->obj) && h11 == n20->hash &&  REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey0_idxfn::equals(se23, *e20)); 
                  }
                }
              n19 = n19->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i22 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n22; 
          REVENUEORDERS1_DELTA_entry* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
                long o_orderkey = e22->O_ORDERKEY;
                long c_custkey = e22->C_CUSTKEY;
                long v22 = e22->__av;
                { //slice 
                  const HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_0* i23 = static_cast<HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_0*>(REVENUESUPPLIER1_P_2ORDERS1_P_1.index[1]);
                  const HASH_RES_t h12 = REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey0_idxfn::hash(se25.modify0(o_orderkey));
                  HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_0::IdxNode* n23 = static_cast<HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_0::IdxNode*>(i23->slice(se25, h12));
                  REVENUESUPPLIER1_P_2ORDERS1_P_1_entry* e23;
                 
                  if (n23 && (e23 = n23->obj)) {
                    do {                
                      long l_suppkey = e23->L_SUPPKEY;
                      DOUBLE_TYPE v23 = e23->__av;
                      REVENUESUPPLIER1_P_2CUSTOMER1.addOrDelOnZero(se24.modify(l_suppkey,c_custkey),(v22 * v23));
                      n23 = n23->nxt;
                    } while (n23 && (e23 = n23->obj) && h12 == n23->hash &&  REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey0_idxfn::equals(se25, *e23)); 
                  }
                }
              n22 = n22->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i24 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n24; 
          REVENUEORDERS1_DELTA_entry* e24;
        
          for (size_t i = 0; i < i24->size_; i++)
          {
            n24 = i24->buckets_ + i;
            while (n24 && (e24 = n24->obj))
            {
                long o_orderkey = e24->O_ORDERKEY;
                long c_custkey = e24->C_CUSTKEY;
                long v24 = e24->__av;
                REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1.addOrDelOnZero(se26.modify(o_orderkey,c_custkey),v24);
              n24 = n24->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i25 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n25; 
          REVENUEORDERS1_DELTA_entry* e25;
        
          for (size_t i = 0; i < i25->size_; i++)
          {
            n25 = i25->buckets_ + i;
            while (n25 && (e25 = n25->obj))
            {
                long o_orderkey = e25->O_ORDERKEY;
                long c_custkey = e25->C_CUSTKEY;
                long v25 = e25->__av;
                { //slice 
                  const HashIndex_REVENUEORDERS1_T_3_map_0* i26 = static_cast<HashIndex_REVENUEORDERS1_T_3_map_0*>(REVENUEORDERS1_T_3.index[1]);
                  const HASH_RES_t h13 = REVENUEORDERS1_T_3_mapkey0_idxfn::hash(se28.modify0(c_custkey));
                  HashIndex_REVENUEORDERS1_T_3_map_0::IdxNode* n26 = static_cast<HashIndex_REVENUEORDERS1_T_3_map_0::IdxNode*>(i26->slice(se28, h13));
                  REVENUEORDERS1_T_3_entry* e26;
                 
                  if (n26 && (e26 = n26->obj)) {
                    do {                
                      long c_nationkey = e26->C_NATIONKEY;
                      long v26 = e26->__av;
                      REVENUELINEITEM1_T_3.addOrDelOnZero(se27.modify(o_orderkey,c_nationkey),(v25 * v26));
                      n26 = n26->nxt;
                    } while (n26 && (e26 = n26->obj) && h13 == n26->hash &&  REVENUEORDERS1_T_3_mapkey0_idxfn::equals(se28, *e26)); 
                  }
                }
              n25 = n25->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i27 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n27; 
          REVENUEORDERS1_DELTA_entry* e27;
        
          for (size_t i = 0; i < i27->size_; i++)
          {
            n27 = i27->buckets_ + i;
            while (n27 && (e27 = n27->obj))
            {
                long o_orderkey = e27->O_ORDERKEY;
                long c_custkey = e27->C_CUSTKEY;
                long v27 = e27->__av;
                { //slice 
                  const HashIndex_REVENUEORDERS1_T_2_map_1* i28 = static_cast<HashIndex_REVENUEORDERS1_T_2_map_1*>(REVENUEORDERS1_T_2.index[1]);
                  const HASH_RES_t h14 = REVENUEORDERS1_T_2_mapkey1_idxfn::hash(se30.modify1(o_orderkey));
                  HashIndex_REVENUEORDERS1_T_2_map_1::IdxNode* n28 = static_cast<HashIndex_REVENUEORDERS1_T_2_map_1::IdxNode*>(i28->slice(se30, h14));
                  REVENUEORDERS1_T_2_entry* e28;
                 
                  if (n28 && (e28 = n28->obj)) {
                    do {                
                      long c_nationkey = e28->C_NATIONKEY;
                      DOUBLE_TYPE v28 = e28->__av;
                      REVENUECUSTOMER1_P_2.addOrDelOnZero(se29.modify(c_nationkey,c_custkey),(v27 * v28));
                      n28 = n28->nxt;
                    } while (n28 && (e28 = n28->obj) && h14 == n28->hash &&  REVENUEORDERS1_T_2_mapkey1_idxfn::equals(se30, *e28)); 
                  }
                }
              n27 = n27->nxt;
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

        REVENUECUSTOMER1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_CUSTOMER.size; i++) 
          {
                long c_custkey = DELTA_CUSTOMER.custkey[i];
                // STRING_TYPE c_name = DELTA_CUSTOMER.name[i];
                // STRING_TYPE c_address = DELTA_CUSTOMER.address[i];
                long c_nationkey = DELTA_CUSTOMER.nationkey[i];
                // STRING_TYPE c_phone = DELTA_CUSTOMER.phone[i];
                // DOUBLE_TYPE c_acctbal = DELTA_CUSTOMER.acctbal[i];
                // STRING_TYPE c_mktsegment = DELTA_CUSTOMER.mktsegment[i];
                // STRING_TYPE c_comment = DELTA_CUSTOMER.comment[i];
                long v29 = 1L;
                REVENUECUSTOMER1_DELTA.addOrDelOnZero(se31.modify(c_custkey,c_nationkey),v29);
          }
        }

        {  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_01* i30 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_01*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_01::IdxNode* n30; 
          REVENUECUSTOMER1_DELTA_entry* e30;
        
          for (size_t i = 0; i < i30->size_; i++)
          {
            n30 = i30->buckets_ + i;
            while (n30 && (e30 = n30->obj))
            {
                long c_custkey = e30->C_CUSTKEY;
                long c_nationkey = e30->C_NATIONKEY;
                long v30 = e30->__av;
                { //slice 
                  const HashIndex_REVENUECUSTOMER1_P_1_map_0* i31 = static_cast<HashIndex_REVENUECUSTOMER1_P_1_map_0*>(REVENUECUSTOMER1_P_1.index[1]);
                  const HASH_RES_t h15 = REVENUECUSTOMER1_P_1_mapkey0_idxfn::hash(se34.modify0(c_nationkey));
                  HashIndex_REVENUECUSTOMER1_P_1_map_0::IdxNode* n31 = static_cast<HashIndex_REVENUECUSTOMER1_P_1_map_0::IdxNode*>(i31->slice(se34, h15));
                  REVENUECUSTOMER1_P_1_entry* e31;
                 
                  if (n31 && (e31 = n31->obj)) {
                    do {                
                      STRING_TYPE n_name = e31->N_NAME;
                      long v31 = e31->__av;
                      REVENUE.addOrDelOnZero(se32.modify(n_name),(v30 * (REVENUECUSTOMER1_P_2.getValueOrDefault(se33.modify(c_nationkey,c_custkey)) * v31)));
                      n31 = n31->nxt;
                    } while (n31 && (e31 = n31->obj) && h15 == n31->hash &&  REVENUECUSTOMER1_P_1_mapkey0_idxfn::equals(se34, *e31)); 
                  }
                }
              n30 = n30->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_01* i32 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_01*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_01::IdxNode* n32; 
          REVENUECUSTOMER1_DELTA_entry* e32;
        
          for (size_t i = 0; i < i32->size_; i++)
          {
            n32 = i32->buckets_ + i;
            while (n32 && (e32 = n32->obj))
            {
                long c_custkey = e32->C_CUSTKEY;
                long c_nationkey = e32->C_NATIONKEY;
                long v32 = e32->__av;
                { //slice 
                  const HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1_map_1* i33 = static_cast<HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1_map_1*>(REVENUESUPPLIER1_P_2CUSTOMER1.index[1]);
                  const HASH_RES_t h16 = REVENUESUPPLIER1_P_2CUSTOMER1_mapkey1_idxfn::hash(se36.modify1(c_custkey));
                  HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1_map_1::IdxNode* n33 = static_cast<HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1_map_1::IdxNode*>(i33->slice(se36, h16));
                  REVENUESUPPLIER1_P_2CUSTOMER1_entry* e33;
                 
                  if (n33 && (e33 = n33->obj)) {
                    do {                
                      long l_suppkey = e33->L_SUPPKEY;
                      DOUBLE_TYPE v33 = e33->__av;
                      REVENUESUPPLIER1_P_2.addOrDelOnZero(se35.modify(l_suppkey,c_nationkey),(v32 * v33));
                      n33 = n33->nxt;
                    } while (n33 && (e33 = n33->obj) && h16 == n33->hash &&  REVENUESUPPLIER1_P_2CUSTOMER1_mapkey1_idxfn::equals(se36, *e33)); 
                  }
                }
              n32 = n32->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_01* i34 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_01*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_01::IdxNode* n34; 
          REVENUECUSTOMER1_DELTA_entry* e34;
        
          for (size_t i = 0; i < i34->size_; i++)
          {
            n34 = i34->buckets_ + i;
            while (n34 && (e34 = n34->obj))
            {
                long c_custkey = e34->C_CUSTKEY;
                long c_nationkey = e34->C_NATIONKEY;
                long v34 = e34->__av;
                { //slice 
                  const HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_1* i35 = static_cast<HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_1*>(REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1.index[2]);
                  const HASH_RES_t h17 = REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey1_idxfn::hash(se38.modify1(c_custkey));
                  HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_1::IdxNode* n35 = static_cast<HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map_1::IdxNode*>(i35->slice(se38, h17));
                  REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry* e35;
                 
                  if (n35 && (e35 = n35->obj)) {
                    do {                
                      long o_orderkey = e35->O_ORDERKEY;
                      long v35 = e35->__av;
                      REVENUELINEITEM1_T_3.addOrDelOnZero(se37.modify(o_orderkey,c_nationkey),(v34 * v35));
                      n35 = n35->nxt;
                    } while (n35 && (e35 = n35->obj) && h17 == n35->hash &&  REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_mapkey1_idxfn::equals(se38, *e35)); 
                  }
                }
              n34 = n34->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_01* i36 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_01*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_01::IdxNode* n36; 
          REVENUECUSTOMER1_DELTA_entry* e36;
        
          for (size_t i = 0; i < i36->size_; i++)
          {
            n36 = i36->buckets_ + i;
            while (n36 && (e36 = n36->obj))
            {
                long c_custkey = e36->C_CUSTKEY;
                long c_nationkey = e36->C_NATIONKEY;
                long v36 = e36->__av;
                REVENUEORDERS1_T_3.addOrDelOnZero(se39.modify(c_custkey,c_nationkey),v36);
              n36 = n36->nxt;
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

        REVENUESUPPLIER1_DELTA.clear();
        { 
          for (size_t i = 0; i < DELTA_SUPPLIER.size; i++) 
          {
                long l_suppkey = DELTA_SUPPLIER.suppkey[i];
                // STRING_TYPE s_name = DELTA_SUPPLIER.name[i];
                // STRING_TYPE s_address = DELTA_SUPPLIER.address[i];
                long c_nationkey = DELTA_SUPPLIER.nationkey[i];
                // STRING_TYPE s_phone = DELTA_SUPPLIER.phone[i];
                // DOUBLE_TYPE s_acctbal = DELTA_SUPPLIER.acctbal[i];
                // STRING_TYPE s_comment = DELTA_SUPPLIER.comment[i];
                long v37 = 1L;
                REVENUESUPPLIER1_DELTA.addOrDelOnZero(se40.modify(l_suppkey,c_nationkey),v37);
          }
        }

        {  // foreach
          const HashIndex_REVENUESUPPLIER1_DELTA_map_01* i38 = static_cast<HashIndex_REVENUESUPPLIER1_DELTA_map_01*>(REVENUESUPPLIER1_DELTA.index[0]);
          HashIndex_REVENUESUPPLIER1_DELTA_map_01::IdxNode* n38; 
          REVENUESUPPLIER1_DELTA_entry* e38;
        
          for (size_t i = 0; i < i38->size_; i++)
          {
            n38 = i38->buckets_ + i;
            while (n38 && (e38 = n38->obj))
            {
                long l_suppkey = e38->L_SUPPKEY;
                long c_nationkey = e38->C_NATIONKEY;
                long v38 = e38->__av;
                { //slice 
                  const HashIndex_REVENUECUSTOMER1_P_1_map_0* i39 = static_cast<HashIndex_REVENUECUSTOMER1_P_1_map_0*>(REVENUECUSTOMER1_P_1.index[1]);
                  const HASH_RES_t h18 = REVENUECUSTOMER1_P_1_mapkey0_idxfn::hash(se43.modify0(c_nationkey));
                  HashIndex_REVENUECUSTOMER1_P_1_map_0::IdxNode* n39 = static_cast<HashIndex_REVENUECUSTOMER1_P_1_map_0::IdxNode*>(i39->slice(se43, h18));
                  REVENUECUSTOMER1_P_1_entry* e39;
                 
                  if (n39 && (e39 = n39->obj)) {
                    do {                
                      STRING_TYPE n_name = e39->N_NAME;
                      long v39 = e39->__av;
                      REVENUE.addOrDelOnZero(se41.modify(n_name),(v38 * (REVENUESUPPLIER1_P_2.getValueOrDefault(se42.modify(l_suppkey,c_nationkey)) * v39)));
                      n39 = n39->nxt;
                    } while (n39 && (e39 = n39->obj) && h18 == n39->hash &&  REVENUECUSTOMER1_P_1_mapkey0_idxfn::equals(se43, *e39)); 
                  }
                }
              n38 = n38->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUESUPPLIER1_DELTA_map_01* i40 = static_cast<HashIndex_REVENUESUPPLIER1_DELTA_map_01*>(REVENUESUPPLIER1_DELTA.index[0]);
          HashIndex_REVENUESUPPLIER1_DELTA_map_01::IdxNode* n40; 
          REVENUESUPPLIER1_DELTA_entry* e40;
        
          for (size_t i = 0; i < i40->size_; i++)
          {
            n40 = i40->buckets_ + i;
            while (n40 && (e40 = n40->obj))
            {
                long l_suppkey = e40->L_SUPPKEY;
                long c_nationkey = e40->C_NATIONKEY;
                long v40 = e40->__av;
                REVENUELINEITEM1_T_2.addOrDelOnZero(se44.modify(l_suppkey,c_nationkey),v40);
              n40 = n40->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUESUPPLIER1_DELTA_map_01* i41 = static_cast<HashIndex_REVENUESUPPLIER1_DELTA_map_01*>(REVENUESUPPLIER1_DELTA.index[0]);
          HashIndex_REVENUESUPPLIER1_DELTA_map_01::IdxNode* n41; 
          REVENUESUPPLIER1_DELTA_entry* e41;
        
          for (size_t i = 0; i < i41->size_; i++)
          {
            n41 = i41->buckets_ + i;
            while (n41 && (e41 = n41->obj))
            {
                long l_suppkey = e41->L_SUPPKEY;
                long c_nationkey = e41->C_NATIONKEY;
                long v41 = e41->__av;
                { //slice 
                  const HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_1* i42 = static_cast<HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_1*>(REVENUESUPPLIER1_P_2ORDERS1_P_1.index[2]);
                  const HASH_RES_t h19 = REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey1_idxfn::hash(se46.modify1(l_suppkey));
                  HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_1::IdxNode* n42 = static_cast<HashIndex_REVENUESUPPLIER1_P_2ORDERS1_P_1_map_1::IdxNode*>(i42->slice(se46, h19));
                  REVENUESUPPLIER1_P_2ORDERS1_P_1_entry* e42;
                 
                  if (n42 && (e42 = n42->obj)) {
                    do {                
                      long o_orderkey = e42->O_ORDERKEY;
                      DOUBLE_TYPE v42 = e42->__av;
                      REVENUEORDERS1_T_2.addOrDelOnZero(se45.modify(c_nationkey,o_orderkey),(v41 * v42));
                      n42 = n42->nxt;
                    } while (n42 && (e42 = n42->obj) && h19 == n42->hash &&  REVENUESUPPLIER1_P_2ORDERS1_P_1_mapkey1_idxfn::equals(se46, *e42)); 
                  }
                }
              n41 = n41->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUESUPPLIER1_DELTA_map_01* i43 = static_cast<HashIndex_REVENUESUPPLIER1_DELTA_map_01*>(REVENUESUPPLIER1_DELTA.index[0]);
          HashIndex_REVENUESUPPLIER1_DELTA_map_01::IdxNode* n43; 
          REVENUESUPPLIER1_DELTA_entry* e43;
        
          for (size_t i = 0; i < i43->size_; i++)
          {
            n43 = i43->buckets_ + i;
            while (n43 && (e43 = n43->obj))
            {
                long l_suppkey = e43->L_SUPPKEY;
                long c_nationkey = e43->C_NATIONKEY;
                long v43 = e43->__av;
                { //slice 
                  const HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1_map_0* i44 = static_cast<HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1_map_0*>(REVENUESUPPLIER1_P_2CUSTOMER1.index[2]);
                  const HASH_RES_t h20 = REVENUESUPPLIER1_P_2CUSTOMER1_mapkey0_idxfn::hash(se48.modify0(l_suppkey));
                  HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1_map_0::IdxNode* n44 = static_cast<HashIndex_REVENUESUPPLIER1_P_2CUSTOMER1_map_0::IdxNode*>(i44->slice(se48, h20));
                  REVENUESUPPLIER1_P_2CUSTOMER1_entry* e44;
                 
                  if (n44 && (e44 = n44->obj)) {
                    do {                
                      long c_custkey = e44->C_CUSTKEY;
                      DOUBLE_TYPE v44 = e44->__av;
                      REVENUECUSTOMER1_P_2.addOrDelOnZero(se47.modify(c_nationkey,c_custkey),(v43 * v44));
                      n44 = n44->nxt;
                    } while (n44 && (e44 = n44->obj) && h20 == n44->hash &&  REVENUESUPPLIER1_P_2CUSTOMER1_mapkey0_idxfn::equals(se48, *e44)); 
                  }
                }
              n43 = n43->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        REVENUECUSTOMER1_P_1.clear();
        STRING_TYPE l1 = c3;
        {  // foreach
          const HashIndex_NATION_map_0123* i45 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n45; 
          NATION_entry* e45;
        
          for (size_t i = 0; i < i45->size_; i++)
          {
            n45 = i45->buckets_ + i;
            while (n45 && (e45 = n45->obj))
            {
                long c_nationkey = e45->NATION_NATIONKEY;
                STRING_TYPE n_name = e45->NATION_NAME;
                long n_regionkey = e45->NATION_REGIONKEY;
                STRING_TYPE n_comment = e45->NATION_COMMENT;
                long v45 = e45->__av;
                { //slice 
                  const HashIndex_REGION_map_01* i46 = static_cast<HashIndex_REGION_map_01*>(REGION.index[1]);
                  const HASH_RES_t h21 = REGION_mapkey01_idxfn::hash(se50.modify01(n_regionkey, l1));
                  HashIndex_REGION_map_01::IdxNode* n46 = static_cast<HashIndex_REGION_map_01::IdxNode*>(i46->slice(se50, h21));
                  REGION_entry* e46;
                 
                  if (n46 && (e46 = n46->obj)) {
                    do {                
                      STRING_TYPE r_comment = e46->REGION_COMMENT;
                      long v46 = e46->__av;
                      REVENUECUSTOMER1_P_1.addOrDelOnZero(se49.modify(c_nationkey,n_name),(v45 * v46));
                      n46 = n46->nxt;
                    } while (n46 && (e46 = n46->obj) && h21 == n46->hash &&  REGION_mapkey01_idxfn::equals(se50, *e46)); 
                  }
                }
              n45 = n45->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    REVENUELINEITEM1_DELTA_entry se1;
    REVENUE_entry se2;
    REVENUELINEITEM1_T_3_entry se3;
    REVENUECUSTOMER1_P_1_entry se4;
    REVENUELINEITEM1_T_2_entry se5;
    REVENUESUPPLIER1_P_2_entry se6;
    REVENUELINEITEM1_T_3_entry se7;
    REVENUESUPPLIER1_P_2ORDERS1_P_1_entry se8;
    REVENUESUPPLIER1_P_2CUSTOMER1_entry se9;
    REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry se10;
    REVENUEORDERS1_T_2_entry se11;
    REVENUELINEITEM1_T_2_entry se12;
    REVENUECUSTOMER1_P_2_entry se13;
    REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry se14;
    REVENUELINEITEM1_T_2_entry se15;
    REVENUEORDERS1_DELTA_entry se16;
    REVENUE_entry se17;
    REVENUEORDERS1_T_3_entry se18;
    REVENUECUSTOMER1_P_1_entry se19;
    REVENUEORDERS1_T_2_entry se20;
    REVENUESUPPLIER1_P_2_entry se21;
    REVENUEORDERS1_T_3_entry se22;
    REVENUESUPPLIER1_P_2ORDERS1_P_1_entry se23;
    REVENUESUPPLIER1_P_2CUSTOMER1_entry se24;
    REVENUESUPPLIER1_P_2ORDERS1_P_1_entry se25;
    REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry se26;
    REVENUELINEITEM1_T_3_entry se27;
    REVENUEORDERS1_T_3_entry se28;
    REVENUECUSTOMER1_P_2_entry se29;
    REVENUEORDERS1_T_2_entry se30;
    REVENUECUSTOMER1_DELTA_entry se31;
    REVENUE_entry se32;
    REVENUECUSTOMER1_P_2_entry se33;
    REVENUECUSTOMER1_P_1_entry se34;
    REVENUESUPPLIER1_P_2_entry se35;
    REVENUESUPPLIER1_P_2CUSTOMER1_entry se36;
    REVENUELINEITEM1_T_3_entry se37;
    REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_entry se38;
    REVENUEORDERS1_T_3_entry se39;
    REVENUESUPPLIER1_DELTA_entry se40;
    REVENUE_entry se41;
    REVENUESUPPLIER1_P_2_entry se42;
    REVENUECUSTOMER1_P_1_entry se43;
    REVENUELINEITEM1_T_2_entry se44;
    REVENUEORDERS1_T_2_entry se45;
    REVENUESUPPLIER1_P_2ORDERS1_P_1_entry se46;
    REVENUECUSTOMER1_P_2_entry se47;
    REVENUESUPPLIER1_P_2CUSTOMER1_entry se48;
    REVENUECUSTOMER1_P_1_entry se49;
    REGION_entry se50;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REGION_map REGION;
    REVENUESUPPLIER1_DELTA_map REVENUESUPPLIER1_DELTA;
    REVENUESUPPLIER1_P_2_map REVENUESUPPLIER1_P_2;
    REVENUESUPPLIER1_P_2ORDERS1_P_1_map REVENUESUPPLIER1_P_2ORDERS1_P_1;
    REVENUESUPPLIER1_P_2CUSTOMER1_map REVENUESUPPLIER1_P_2CUSTOMER1;
    REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1_map REVENUESUPPLIER1_P_2CUSTOMER1LINEITEM1;
    REVENUELINEITEM1_DELTA_map REVENUELINEITEM1_DELTA;
    REVENUELINEITEM1_T_2_map REVENUELINEITEM1_T_2;
    REVENUELINEITEM1_T_3_map REVENUELINEITEM1_T_3;
    REVENUEORDERS1_DELTA_map REVENUEORDERS1_DELTA;
    REVENUEORDERS1_T_2_map REVENUEORDERS1_T_2;
    REVENUEORDERS1_T_3_map REVENUEORDERS1_T_3;
    REVENUECUSTOMER1_DELTA_map REVENUECUSTOMER1_DELTA;
    REVENUECUSTOMER1_P_1_map REVENUECUSTOMER1_P_1;
    REVENUECUSTOMER1_P_2_map REVENUECUSTOMER1_P_2;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_ORDERS_map DELTA_ORDERS;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    DELTA_SUPPLIER_map DELTA_SUPPLIER;
    
    /*const static*/ long c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
  
  };

}
