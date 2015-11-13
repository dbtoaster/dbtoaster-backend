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
  
  struct REVENUE_entry {
    long C_CUSTKEY; STRING_TYPE C_NAME; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE N_NAME; STRING_TYPE C_ADDRESS; STRING_TYPE C_PHONE; STRING_TYPE C_COMMENT; DOUBLE_TYPE __av; 
    explicit REVENUE_entry() { /*C_CUSTKEY = 0L; C_NAME = ""; C_ACCTBAL = 0.0; N_NAME = ""; C_ADDRESS = ""; C_PHONE = ""; C_COMMENT = ""; __av = 0.0; */ }
    explicit REVENUE_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7) { C_CUSTKEY = c0; C_NAME = c1; C_ACCTBAL = c2; N_NAME = c3; C_ADDRESS = c4; C_PHONE = c5; C_COMMENT = c6; __av = c7; }
    REVENUE_entry(const REVENUE_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_NAME( other.C_NAME ), C_ACCTBAL( other.C_ACCTBAL ), N_NAME( other.N_NAME ), C_ADDRESS( other.C_ADDRESS ), C_PHONE( other.C_PHONE ), C_COMMENT( other.C_COMMENT ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_entry& modify(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6) { C_CUSTKEY = c0; C_NAME = c1; C_ACCTBAL = c2; N_NAME = c3; C_ADDRESS = c4; C_PHONE = c5; C_COMMENT = c6;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.N_NAME);
      hash_combine(h, e.C_ADDRESS);
      hash_combine(h, e.C_PHONE);
      hash_combine(h, e.C_COMMENT);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_entry& x, const REVENUE_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_NAME == y.C_NAME && x.C_ACCTBAL == y.C_ACCTBAL && x.N_NAME == y.N_NAME && x.C_ADDRESS == y.C_ADDRESS && x.C_PHONE == y.C_PHONE && x.C_COMMENT == y.C_COMMENT;
    }
  };
  
  typedef MultiHashMap<REVENUE_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_entry,DOUBLE_TYPE,REVENUE_mapkey0123456_idxfn,true>
  > REVENUE_map;
  typedef HashIndex<REVENUE_entry,DOUBLE_TYPE,REVENUE_mapkey0123456_idxfn,true> HashIndex_REVENUE_map_0123456;
  
  struct REVENUELINEITEM1_DELTA_entry {
    long O_ORDERKEY; DOUBLE_TYPE __av; 
    explicit REVENUELINEITEM1_DELTA_entry() { /*O_ORDERKEY = 0L; __av = 0.0; */ }
    explicit REVENUELINEITEM1_DELTA_entry(const long c0, const DOUBLE_TYPE c1) { O_ORDERKEY = c0; __av = c1; }
    REVENUELINEITEM1_DELTA_entry(const REVENUELINEITEM1_DELTA_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_DELTA_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_DELTA_entry& x, const REVENUELINEITEM1_DELTA_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,REVENUELINEITEM1_DELTA_mapkey0_idxfn,true>
  > REVENUELINEITEM1_DELTA_map;
  typedef HashIndex<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,REVENUELINEITEM1_DELTA_mapkey0_idxfn,true> HashIndex_REVENUELINEITEM1_DELTA_map_0;
  
  struct REVENUELINEITEM1_entry {
    long C_CUSTKEY; STRING_TYPE C_NAME; STRING_TYPE C_ADDRESS; STRING_TYPE C_PHONE; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE C_COMMENT; long O_ORDERKEY; STRING_TYPE N_NAME; long __av; 
    explicit REVENUELINEITEM1_entry() { /*C_CUSTKEY = 0L; C_NAME = ""; C_ADDRESS = ""; C_PHONE = ""; C_ACCTBAL = 0.0; C_COMMENT = ""; O_ORDERKEY = 0L; N_NAME = ""; __av = 0L; */ }
    explicit REVENUELINEITEM1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const long c6, const STRING_TYPE& c7, const long c8) { C_CUSTKEY = c0; C_NAME = c1; C_ADDRESS = c2; C_PHONE = c3; C_ACCTBAL = c4; C_COMMENT = c5; O_ORDERKEY = c6; N_NAME = c7; __av = c8; }
    REVENUELINEITEM1_entry(const REVENUELINEITEM1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_NAME( other.C_NAME ), C_ADDRESS( other.C_ADDRESS ), C_PHONE( other.C_PHONE ), C_ACCTBAL( other.C_ACCTBAL ), C_COMMENT( other.C_COMMENT ), O_ORDERKEY( other.O_ORDERKEY ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const long c6, const STRING_TYPE& c7) { C_CUSTKEY = c0; C_NAME = c1; C_ADDRESS = c2; C_PHONE = c3; C_ACCTBAL = c4; C_COMMENT = c5; O_ORDERKEY = c6; N_NAME = c7;  return *this; }
    FORCE_INLINE REVENUELINEITEM1_entry& modify6(const long c6) { O_ORDERKEY = c6;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.C_ADDRESS);
      hash_combine(h, e.C_PHONE);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.C_COMMENT);
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_entry& x, const REVENUELINEITEM1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_NAME == y.C_NAME && x.C_ADDRESS == y.C_ADDRESS && x.C_PHONE == y.C_PHONE && x.C_ACCTBAL == y.C_ACCTBAL && x.C_COMMENT == y.C_COMMENT && x.O_ORDERKEY == y.O_ORDERKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  struct REVENUELINEITEM1_mapkey6_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_entry& x, const REVENUELINEITEM1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_entry,long,
    HashIndex<REVENUELINEITEM1_entry,long,REVENUELINEITEM1_mapkey01234567_idxfn,true>,
    HashIndex<REVENUELINEITEM1_entry,long,REVENUELINEITEM1_mapkey6_idxfn,false>
  > REVENUELINEITEM1_map;
  typedef HashIndex<REVENUELINEITEM1_entry,long,REVENUELINEITEM1_mapkey01234567_idxfn,true> HashIndex_REVENUELINEITEM1_map_01234567;
  typedef HashIndex<REVENUELINEITEM1_entry,long,REVENUELINEITEM1_mapkey6_idxfn,false> HashIndex_REVENUELINEITEM1_map_6;
  
  struct REVENUELINEITEM1CUSTOMER1_P_1_entry {
    long O_ORDERKEY; long C_CUSTKEY; long __av; 
    explicit REVENUELINEITEM1CUSTOMER1_P_1_entry() { /*O_ORDERKEY = 0L; C_CUSTKEY = 0L; __av = 0L; */ }
    explicit REVENUELINEITEM1CUSTOMER1_P_1_entry(const long c0, const long c1, const long c2) { O_ORDERKEY = c0; C_CUSTKEY = c1; __av = c2; }
    REVENUELINEITEM1CUSTOMER1_P_1_entry(const REVENUELINEITEM1CUSTOMER1_P_1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1CUSTOMER1_P_1_entry& modify(const long c0, const long c1) { O_ORDERKEY = c0; C_CUSTKEY = c1;  return *this; }
    FORCE_INLINE REVENUELINEITEM1CUSTOMER1_P_1_entry& modify0(const long c0) { O_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUELINEITEM1CUSTOMER1_P_1_entry& modify1(const long c1) { C_CUSTKEY = c1;  return *this; }
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
  struct REVENUELINEITEM1CUSTOMER1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1CUSTOMER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1CUSTOMER1_P_1_entry& x, const REVENUELINEITEM1CUSTOMER1_P_1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  struct REVENUELINEITEM1CUSTOMER1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1CUSTOMER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1CUSTOMER1_P_1_entry& x, const REVENUELINEITEM1CUSTOMER1_P_1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  struct REVENUELINEITEM1CUSTOMER1_P_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1CUSTOMER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1CUSTOMER1_P_1_entry& x, const REVENUELINEITEM1CUSTOMER1_P_1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1CUSTOMER1_P_1_entry,long,
    HashIndex<REVENUELINEITEM1CUSTOMER1_P_1_entry,long,REVENUELINEITEM1CUSTOMER1_P_1_mapkey01_idxfn,true>,
    HashIndex<REVENUELINEITEM1CUSTOMER1_P_1_entry,long,REVENUELINEITEM1CUSTOMER1_P_1_mapkey0_idxfn,false>,
    HashIndex<REVENUELINEITEM1CUSTOMER1_P_1_entry,long,REVENUELINEITEM1CUSTOMER1_P_1_mapkey1_idxfn,false>
  > REVENUELINEITEM1CUSTOMER1_P_1_map;
  typedef HashIndex<REVENUELINEITEM1CUSTOMER1_P_1_entry,long,REVENUELINEITEM1CUSTOMER1_P_1_mapkey01_idxfn,true> HashIndex_REVENUELINEITEM1CUSTOMER1_P_1_map_01;
  typedef HashIndex<REVENUELINEITEM1CUSTOMER1_P_1_entry,long,REVENUELINEITEM1CUSTOMER1_P_1_mapkey0_idxfn,false> HashIndex_REVENUELINEITEM1CUSTOMER1_P_1_map_0;
  typedef HashIndex<REVENUELINEITEM1CUSTOMER1_P_1_entry,long,REVENUELINEITEM1CUSTOMER1_P_1_mapkey1_idxfn,false> HashIndex_REVENUELINEITEM1CUSTOMER1_P_1_map_1;
  
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
  
  struct REVENUEORDERS1_P_1_entry {
    long O_ORDERKEY; DOUBLE_TYPE __av; 
    explicit REVENUEORDERS1_P_1_entry() { /*O_ORDERKEY = 0L; __av = 0.0; */ }
    explicit REVENUEORDERS1_P_1_entry(const long c0, const DOUBLE_TYPE c1) { O_ORDERKEY = c0; __av = c1; }
    REVENUEORDERS1_P_1_entry(const REVENUEORDERS1_P_1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUEORDERS1_P_1_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEORDERS1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_P_1_entry& x, const REVENUEORDERS1_P_1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEORDERS1_P_1_entry,DOUBLE_TYPE,
    HashIndex<REVENUEORDERS1_P_1_entry,DOUBLE_TYPE,REVENUEORDERS1_P_1_mapkey0_idxfn,true>
  > REVENUEORDERS1_P_1_map;
  typedef HashIndex<REVENUEORDERS1_P_1_entry,DOUBLE_TYPE,REVENUEORDERS1_P_1_mapkey0_idxfn,true> HashIndex_REVENUEORDERS1_P_1_map_0;
  
  struct REVENUEORDERS1_P_2_entry {
    long C_CUSTKEY; STRING_TYPE C_NAME; STRING_TYPE C_ADDRESS; STRING_TYPE C_PHONE; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE C_COMMENT; STRING_TYPE N_NAME; long __av; 
    explicit REVENUEORDERS1_P_2_entry() { /*C_CUSTKEY = 0L; C_NAME = ""; C_ADDRESS = ""; C_PHONE = ""; C_ACCTBAL = 0.0; C_COMMENT = ""; N_NAME = ""; __av = 0L; */ }
    explicit REVENUEORDERS1_P_2_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const long c7) { C_CUSTKEY = c0; C_NAME = c1; C_ADDRESS = c2; C_PHONE = c3; C_ACCTBAL = c4; C_COMMENT = c5; N_NAME = c6; __av = c7; }
    REVENUEORDERS1_P_2_entry(const REVENUEORDERS1_P_2_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_NAME( other.C_NAME ), C_ADDRESS( other.C_ADDRESS ), C_PHONE( other.C_PHONE ), C_ACCTBAL( other.C_ACCTBAL ), C_COMMENT( other.C_COMMENT ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUEORDERS1_P_2_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6) { C_CUSTKEY = c0; C_NAME = c1; C_ADDRESS = c2; C_PHONE = c3; C_ACCTBAL = c4; C_COMMENT = c5; N_NAME = c6;  return *this; }
    FORCE_INLINE REVENUEORDERS1_P_2_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEORDERS1_P_2_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.C_ADDRESS);
      hash_combine(h, e.C_PHONE);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.C_COMMENT);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_P_2_entry& x, const REVENUEORDERS1_P_2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_NAME == y.C_NAME && x.C_ADDRESS == y.C_ADDRESS && x.C_PHONE == y.C_PHONE && x.C_ACCTBAL == y.C_ACCTBAL && x.C_COMMENT == y.C_COMMENT && x.N_NAME == y.N_NAME;
    }
  };
  
  struct REVENUEORDERS1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_P_2_entry& x, const REVENUEORDERS1_P_2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEORDERS1_P_2_entry,long,
    HashIndex<REVENUEORDERS1_P_2_entry,long,REVENUEORDERS1_P_2_mapkey0123456_idxfn,true>,
    HashIndex<REVENUEORDERS1_P_2_entry,long,REVENUEORDERS1_P_2_mapkey0_idxfn,false>
  > REVENUEORDERS1_P_2_map;
  typedef HashIndex<REVENUEORDERS1_P_2_entry,long,REVENUEORDERS1_P_2_mapkey0123456_idxfn,true> HashIndex_REVENUEORDERS1_P_2_map_0123456;
  typedef HashIndex<REVENUEORDERS1_P_2_entry,long,REVENUEORDERS1_P_2_mapkey0_idxfn,false> HashIndex_REVENUEORDERS1_P_2_map_0;
  
  struct REVENUECUSTOMER1_DELTA_entry {
    long C_CUSTKEY; STRING_TYPE C_NAME; STRING_TYPE C_ADDRESS; long C_NATIONKEY; STRING_TYPE C_PHONE; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE C_COMMENT; long __av; 
    explicit REVENUECUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_NAME = ""; C_ADDRESS = ""; C_NATIONKEY = 0L; C_PHONE = ""; C_ACCTBAL = 0.0; C_COMMENT = ""; __av = 0L; */ }
    explicit REVENUECUSTOMER1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const long c7) { C_CUSTKEY = c0; C_NAME = c1; C_ADDRESS = c2; C_NATIONKEY = c3; C_PHONE = c4; C_ACCTBAL = c5; C_COMMENT = c6; __av = c7; }
    REVENUECUSTOMER1_DELTA_entry(const REVENUECUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_NAME( other.C_NAME ), C_ADDRESS( other.C_ADDRESS ), C_NATIONKEY( other.C_NATIONKEY ), C_PHONE( other.C_PHONE ), C_ACCTBAL( other.C_ACCTBAL ), C_COMMENT( other.C_COMMENT ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6) { C_CUSTKEY = c0; C_NAME = c1; C_ADDRESS = c2; C_NATIONKEY = c3; C_PHONE = c4; C_ACCTBAL = c5; C_COMMENT = c6;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1_DELTA_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.C_ADDRESS);
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.C_PHONE);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.C_COMMENT);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_DELTA_entry& x, const REVENUECUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_NAME == y.C_NAME && x.C_ADDRESS == y.C_ADDRESS && x.C_NATIONKEY == y.C_NATIONKEY && x.C_PHONE == y.C_PHONE && x.C_ACCTBAL == y.C_ACCTBAL && x.C_COMMENT == y.C_COMMENT;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1_DELTA_entry,long,
    HashIndex<REVENUECUSTOMER1_DELTA_entry,long,REVENUECUSTOMER1_DELTA_mapkey0123456_idxfn,true>
  > REVENUECUSTOMER1_DELTA_map;
  typedef HashIndex<REVENUECUSTOMER1_DELTA_entry,long,REVENUECUSTOMER1_DELTA_mapkey0123456_idxfn,true> HashIndex_REVENUECUSTOMER1_DELTA_map_0123456;
  
  struct REVENUECUSTOMER1_P_1_entry {
    long C_CUSTKEY; DOUBLE_TYPE __av; 
    explicit REVENUECUSTOMER1_P_1_entry() { /*C_CUSTKEY = 0L; __av = 0.0; */ }
    explicit REVENUECUSTOMER1_P_1_entry(const long c0, const DOUBLE_TYPE c1) { C_CUSTKEY = c0; __av = c1; }
    REVENUECUSTOMER1_P_1_entry(const REVENUECUSTOMER1_P_1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1_P_1_entry& modify(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_P_1_entry& x, const REVENUECUSTOMER1_P_1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1_P_1_entry,DOUBLE_TYPE,
    HashIndex<REVENUECUSTOMER1_P_1_entry,DOUBLE_TYPE,REVENUECUSTOMER1_P_1_mapkey0_idxfn,true>
  > REVENUECUSTOMER1_P_1_map;
  typedef HashIndex<REVENUECUSTOMER1_P_1_entry,DOUBLE_TYPE,REVENUECUSTOMER1_P_1_mapkey0_idxfn,true> HashIndex_REVENUECUSTOMER1_P_1_map_0;
  
  struct REVENUECUSTOMER1_P_2_entry {
    long C_NATIONKEY; STRING_TYPE N_NAME; long __av; 
    explicit REVENUECUSTOMER1_P_2_entry() { /*C_NATIONKEY = 0L; N_NAME = ""; __av = 0L; */ }
    explicit REVENUECUSTOMER1_P_2_entry(const long c0, const STRING_TYPE& c1, const long c2) { C_NATIONKEY = c0; N_NAME = c1; __av = c2; }
    REVENUECUSTOMER1_P_2_entry(const REVENUECUSTOMER1_P_2_entry& other) : C_NATIONKEY( other.C_NATIONKEY ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1_P_2_entry& modify(const long c0, const STRING_TYPE& c1) { C_NATIONKEY = c0; N_NAME = c1;  return *this; }
    FORCE_INLINE REVENUECUSTOMER1_P_2_entry& modify0(const long c0) { C_NATIONKEY = c0;  return *this; }
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
  struct REVENUECUSTOMER1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_P_2_entry& x, const REVENUECUSTOMER1_P_2_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  struct REVENUECUSTOMER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_P_2_entry& x, const REVENUECUSTOMER1_P_2_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1_P_2_entry,long,
    HashIndex<REVENUECUSTOMER1_P_2_entry,long,REVENUECUSTOMER1_P_2_mapkey01_idxfn,true>,
    HashIndex<REVENUECUSTOMER1_P_2_entry,long,REVENUECUSTOMER1_P_2_mapkey0_idxfn,false>
  > REVENUECUSTOMER1_P_2_map;
  typedef HashIndex<REVENUECUSTOMER1_P_2_entry,long,REVENUECUSTOMER1_P_2_mapkey01_idxfn,true> HashIndex_REVENUECUSTOMER1_P_2_map_01;
  typedef HashIndex<REVENUECUSTOMER1_P_2_entry,long,REVENUECUSTOMER1_P_2_mapkey0_idxfn,false> HashIndex_REVENUECUSTOMER1_P_2_map_0;
  
  
  
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
      c1 = STRING_TYPE("R");
      c3 = Udate(STRING_TYPE("1994-1-1"));
      c2 = Udate(STRING_TYPE("1993-10-1"));
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


        REVENUELINEITEM1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                long o_orderkey = DELTA_LINEITEM.orderkey[i];
                long l_partkey = DELTA_LINEITEM.partkey[i];
                long l_suppkey = DELTA_LINEITEM.suppkey[i];
                long l_linenumber = DELTA_LINEITEM.linenumber[i];
                DOUBLE_TYPE l_quantity = DELTA_LINEITEM.quantity[i];
                DOUBLE_TYPE l_extendedprice = DELTA_LINEITEM.extendedprice[i];
                DOUBLE_TYPE l_discount = DELTA_LINEITEM.discount[i];
                DOUBLE_TYPE l_tax = DELTA_LINEITEM.tax[i];
                STRING_TYPE lift1 = DELTA_LINEITEM.returnflag[i];
                STRING_TYPE l_linestatus = DELTA_LINEITEM.linestatus[i];
                date l_shipdate = DELTA_LINEITEM.shipdate[i];
                date l_commitdate = DELTA_LINEITEM.commitdate[i];
                date l_receiptdate = DELTA_LINEITEM.receiptdate[i];
                STRING_TYPE l_shipinstruct = DELTA_LINEITEM.shipinstruct[i];
                STRING_TYPE l_shipmode = DELTA_LINEITEM.shipmode[i];
                STRING_TYPE l_comment = DELTA_LINEITEM.comment[i];
                long v1 = 1L;
                (/*if */(lift1 == c1) ? REVENUELINEITEM1_DELTA.addOrDelOnZero(se1.modify(o_orderkey),(v1 * (l_extendedprice * (1L + (-1L * l_discount))))) : (void)0);

          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_0* i2 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_0*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_0::IdxNode* n2; 
          REVENUELINEITEM1_DELTA_entry* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
                long o_orderkey = e2->O_ORDERKEY;
                DOUBLE_TYPE v2 = e2->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_map_6* i3 = static_cast<HashIndex_REVENUELINEITEM1_map_6*>(REVENUELINEITEM1.index[1]);
                  const HASH_RES_t h1 = REVENUELINEITEM1_mapkey6_idxfn::hash(se3.modify6(o_orderkey));
                  HashIndex_REVENUELINEITEM1_map_6::IdxNode* n3 = static_cast<HashIndex_REVENUELINEITEM1_map_6::IdxNode*>(i3->slice(se3, h1));
                  REVENUELINEITEM1_entry* e3;
                 
                  if (n3 && (e3 = n3->obj)) {
                    do {                
                      long c_custkey = e3->C_CUSTKEY;
                      STRING_TYPE c_name = e3->C_NAME;
                      STRING_TYPE c_address = e3->C_ADDRESS;
                      STRING_TYPE c_phone = e3->C_PHONE;
                      DOUBLE_TYPE c_acctbal = e3->C_ACCTBAL;
                      STRING_TYPE c_comment = e3->C_COMMENT;
                      STRING_TYPE n_name = e3->N_NAME;
                      long v3 = e3->__av;
                      REVENUE.addOrDelOnZero(se2.modify(c_custkey,c_name,c_acctbal,n_name,c_address,c_phone,c_comment),(v2 * v3));
                      n3 = n3->nxt;
                    } while (n3 && (e3 = n3->obj) && h1 == n3->hash &&  REVENUELINEITEM1_mapkey6_idxfn::equals(se3, *e3)); 
                  }
                }
              n2 = n2->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_0* i4 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_0*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_0::IdxNode* n4; 
          REVENUELINEITEM1_DELTA_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long o_orderkey = e4->O_ORDERKEY;
                DOUBLE_TYPE v4 = e4->__av;
                REVENUEORDERS1_P_1.addOrDelOnZero(se4.modify(o_orderkey),v4);
              n4 = n4->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_0* i5 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_0*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_0::IdxNode* n5; 
          REVENUELINEITEM1_DELTA_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long o_orderkey = e5->O_ORDERKEY;
                DOUBLE_TYPE v5 = e5->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1CUSTOMER1_P_1_map_0* i6 = static_cast<HashIndex_REVENUELINEITEM1CUSTOMER1_P_1_map_0*>(REVENUELINEITEM1CUSTOMER1_P_1.index[1]);
                  const HASH_RES_t h2 = REVENUELINEITEM1CUSTOMER1_P_1_mapkey0_idxfn::hash(se6.modify0(o_orderkey));
                  HashIndex_REVENUELINEITEM1CUSTOMER1_P_1_map_0::IdxNode* n6 = static_cast<HashIndex_REVENUELINEITEM1CUSTOMER1_P_1_map_0::IdxNode*>(i6->slice(se6, h2));
                  REVENUELINEITEM1CUSTOMER1_P_1_entry* e6;
                 
                  if (n6 && (e6 = n6->obj)) {
                    do {                
                      long c_custkey = e6->C_CUSTKEY;
                      long v6 = e6->__av;
                      REVENUECUSTOMER1_P_1.addOrDelOnZero(se5.modify(c_custkey),(v5 * v6));
                      n6 = n6->nxt;
                    } while (n6 && (e6 = n6->obj) && h2 == n6->hash &&  REVENUELINEITEM1CUSTOMER1_P_1_mapkey0_idxfn::equals(se6, *e6)); 
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

        REVENUEORDERS1_DELTA.clear();
        { 
          for (size_t i = 0; i < DELTA_ORDERS.size; i++)
          {
                long o_orderkey = DELTA_ORDERS.orderkey[i];
                long c_custkey = DELTA_ORDERS.custkey[i];
                STRING_TYPE o_orderstatus = DELTA_ORDERS.orderstatus[i];
                DOUBLE_TYPE o_totalprice = DELTA_ORDERS.totalprice[i];
                date o_orderdate = DELTA_ORDERS.orderdate[i];
                STRING_TYPE o_orderpriority = DELTA_ORDERS.orderpriority[i];
                STRING_TYPE o_clerk = DELTA_ORDERS.clerk[i];
                long o_shippriority = DELTA_ORDERS.shippriority[i];
                STRING_TYPE o_comment = DELTA_ORDERS.comment[i];
                long v7 = 1L;
                (/*if */(o_orderdate >= c2 && c3 > o_orderdate) ? REVENUEORDERS1_DELTA.addOrDelOnZero(se7.modify(o_orderkey,c_custkey),v7) : (void)0);
          }
        }
        {  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i8 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n8; 
          REVENUEORDERS1_DELTA_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long o_orderkey = e8->O_ORDERKEY;
                long c_custkey = e8->C_CUSTKEY;
                long v8 = e8->__av;
                { //slice 
                  const HashIndex_REVENUEORDERS1_P_2_map_0* i9 = static_cast<HashIndex_REVENUEORDERS1_P_2_map_0*>(REVENUEORDERS1_P_2.index[1]);
                  const HASH_RES_t h3 = REVENUEORDERS1_P_2_mapkey0_idxfn::hash(se10.modify0(c_custkey));
                  HashIndex_REVENUEORDERS1_P_2_map_0::IdxNode* n9 = static_cast<HashIndex_REVENUEORDERS1_P_2_map_0::IdxNode*>(i9->slice(se10, h3));
                  REVENUEORDERS1_P_2_entry* e9;
                 
                  if (n9 && (e9 = n9->obj)) {
                    do {                
                      STRING_TYPE c_name = e9->C_NAME;
                      STRING_TYPE c_address = e9->C_ADDRESS;
                      STRING_TYPE c_phone = e9->C_PHONE;
                      DOUBLE_TYPE c_acctbal = e9->C_ACCTBAL;
                      STRING_TYPE c_comment = e9->C_COMMENT;
                      STRING_TYPE n_name = e9->N_NAME;
                      long v9 = e9->__av;
                      REVENUE.addOrDelOnZero(se8.modify(c_custkey,c_name,c_acctbal,n_name,c_address,c_phone,c_comment),(v8 * (REVENUEORDERS1_P_1.getValueOrDefault(se9.modify(o_orderkey)) * v9)));
                      n9 = n9->nxt;
                    } while (n9 && (e9 = n9->obj) && h3 == n9->hash &&  REVENUEORDERS1_P_2_mapkey0_idxfn::equals(se10, *e9)); 
                  }
                }
              n8 = n8->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i10 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n10; 
          REVENUEORDERS1_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long o_orderkey = e10->O_ORDERKEY;
                long c_custkey = e10->C_CUSTKEY;
                long v10 = e10->__av;
                { //slice 
                  const HashIndex_REVENUEORDERS1_P_2_map_0* i11 = static_cast<HashIndex_REVENUEORDERS1_P_2_map_0*>(REVENUEORDERS1_P_2.index[1]);
                  const HASH_RES_t h4 = REVENUEORDERS1_P_2_mapkey0_idxfn::hash(se12.modify0(c_custkey));
                  HashIndex_REVENUEORDERS1_P_2_map_0::IdxNode* n11 = static_cast<HashIndex_REVENUEORDERS1_P_2_map_0::IdxNode*>(i11->slice(se12, h4));
                  REVENUEORDERS1_P_2_entry* e11;
                 
                  if (n11 && (e11 = n11->obj)) {
                    do {                
                      STRING_TYPE c_name = e11->C_NAME;
                      STRING_TYPE c_address = e11->C_ADDRESS;
                      STRING_TYPE c_phone = e11->C_PHONE;
                      DOUBLE_TYPE c_acctbal = e11->C_ACCTBAL;
                      STRING_TYPE c_comment = e11->C_COMMENT;
                      STRING_TYPE n_name = e11->N_NAME;
                      long v11 = e11->__av;
                      REVENUELINEITEM1.addOrDelOnZero(se11.modify(c_custkey,c_name,c_address,c_phone,c_acctbal,c_comment,o_orderkey,n_name),(v10 * v11));
                      n11 = n11->nxt;
                    } while (n11 && (e11 = n11->obj) && h4 == n11->hash &&  REVENUEORDERS1_P_2_mapkey0_idxfn::equals(se12, *e11)); 
                  }
                }
              n10 = n10->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i12 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n12; 
          REVENUEORDERS1_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long o_orderkey = e12->O_ORDERKEY;
                long c_custkey = e12->C_CUSTKEY;
                long v12 = e12->__av;
                REVENUELINEITEM1CUSTOMER1_P_1.addOrDelOnZero(se13.modify(o_orderkey,c_custkey),v12);
              n12 = n12->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i13 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n13; 
          REVENUEORDERS1_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long o_orderkey = e13->O_ORDERKEY;
                long c_custkey = e13->C_CUSTKEY;
                long v13 = e13->__av;
                REVENUECUSTOMER1_P_1.addOrDelOnZero(se14.modify(c_custkey),(v13 * REVENUEORDERS1_P_1.getValueOrDefault(se15.modify(o_orderkey))));
              n13 = n13->nxt;
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
                STRING_TYPE c_name = DELTA_CUSTOMER.name[i];
                STRING_TYPE c_address = DELTA_CUSTOMER.address[i];
                long c_nationkey = DELTA_CUSTOMER.nationkey[i];
                STRING_TYPE c_phone = DELTA_CUSTOMER.phone[i];
                DOUBLE_TYPE c_acctbal = DELTA_CUSTOMER.acctbal[i];
                STRING_TYPE c_mktsegment = DELTA_CUSTOMER.mktsegment[i];
                STRING_TYPE c_comment = DELTA_CUSTOMER.comment[i];
                long v14 = 1L;
                REVENUECUSTOMER1_DELTA.addOrDelOnZero(se16.modify(c_custkey,c_name,c_address,c_nationkey,c_phone,c_acctbal,c_comment),v14);
          }
        }{  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_0123456* i15 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_0123456*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_0123456::IdxNode* n15; 
          REVENUECUSTOMER1_DELTA_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long c_custkey = e15->C_CUSTKEY;
                STRING_TYPE c_name = e15->C_NAME;
                STRING_TYPE c_address = e15->C_ADDRESS;
                long c_nationkey = e15->C_NATIONKEY;
                STRING_TYPE c_phone = e15->C_PHONE;
                DOUBLE_TYPE c_acctbal = e15->C_ACCTBAL;
                STRING_TYPE c_comment = e15->C_COMMENT;
                long v15 = e15->__av;
                { //slice 
                  const HashIndex_REVENUECUSTOMER1_P_2_map_0* i16 = static_cast<HashIndex_REVENUECUSTOMER1_P_2_map_0*>(REVENUECUSTOMER1_P_2.index[1]);
                  const HASH_RES_t h5 = REVENUECUSTOMER1_P_2_mapkey0_idxfn::hash(se19.modify0(c_nationkey));
                  HashIndex_REVENUECUSTOMER1_P_2_map_0::IdxNode* n16 = static_cast<HashIndex_REVENUECUSTOMER1_P_2_map_0::IdxNode*>(i16->slice(se19, h5));
                  REVENUECUSTOMER1_P_2_entry* e16;
                 
                  if (n16 && (e16 = n16->obj)) {
                    do {                
                      STRING_TYPE n_name = e16->N_NAME;
                      long v16 = e16->__av;
                      REVENUE.addOrDelOnZero(se17.modify(c_custkey,c_name,c_acctbal,n_name,c_address,c_phone,c_comment),(v15 * (REVENUECUSTOMER1_P_1.getValueOrDefault(se18.modify(c_custkey)) * v16)));
                      n16 = n16->nxt;
                    } while (n16 && (e16 = n16->obj) && h5 == n16->hash &&  REVENUECUSTOMER1_P_2_mapkey0_idxfn::equals(se19, *e16)); 
                  }
                }
              n15 = n15->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_0123456* i17 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_0123456*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_0123456::IdxNode* n17; 
          REVENUECUSTOMER1_DELTA_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long c_custkey = e17->C_CUSTKEY;
                STRING_TYPE c_name = e17->C_NAME;
                STRING_TYPE c_address = e17->C_ADDRESS;
                long c_nationkey = e17->C_NATIONKEY;
                STRING_TYPE c_phone = e17->C_PHONE;
                DOUBLE_TYPE c_acctbal = e17->C_ACCTBAL;
                STRING_TYPE c_comment = e17->C_COMMENT;
                long v17 = e17->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1CUSTOMER1_P_1_map_1* i18 = static_cast<HashIndex_REVENUELINEITEM1CUSTOMER1_P_1_map_1*>(REVENUELINEITEM1CUSTOMER1_P_1.index[2]);
                  const HASH_RES_t h7 = REVENUELINEITEM1CUSTOMER1_P_1_mapkey1_idxfn::hash(se22.modify1(c_custkey));
                  HashIndex_REVENUELINEITEM1CUSTOMER1_P_1_map_1::IdxNode* n18 = static_cast<HashIndex_REVENUELINEITEM1CUSTOMER1_P_1_map_1::IdxNode*>(i18->slice(se22, h7));
                  REVENUELINEITEM1CUSTOMER1_P_1_entry* e18;
                 
                  if (n18 && (e18 = n18->obj)) {
                    do {                
                      long o_orderkey = e18->O_ORDERKEY;
                      long v18 = e18->__av;
                      { //slice 
                        const HashIndex_REVENUECUSTOMER1_P_2_map_0* i19 = static_cast<HashIndex_REVENUECUSTOMER1_P_2_map_0*>(REVENUECUSTOMER1_P_2.index[1]);
                        const HASH_RES_t h6 = REVENUECUSTOMER1_P_2_mapkey0_idxfn::hash(se21.modify0(c_nationkey));
                        HashIndex_REVENUECUSTOMER1_P_2_map_0::IdxNode* n19 = static_cast<HashIndex_REVENUECUSTOMER1_P_2_map_0::IdxNode*>(i19->slice(se21, h6));
                        REVENUECUSTOMER1_P_2_entry* e19;
                       
                        if (n19 && (e19 = n19->obj)) {
                          do {                
                            STRING_TYPE n_name = e19->N_NAME;
                            long v19 = e19->__av;
                            REVENUELINEITEM1.addOrDelOnZero(se20.modify(c_custkey,c_name,c_address,c_phone,c_acctbal,c_comment,o_orderkey,n_name),(v17 * (v18 * v19)));
                            n19 = n19->nxt;
                          } while (n19 && (e19 = n19->obj) && h6 == n19->hash &&  REVENUECUSTOMER1_P_2_mapkey0_idxfn::equals(se21, *e19)); 
                        }
                      }
                      n18 = n18->nxt;
                    } while (n18 && (e18 = n18->obj) && h7 == n18->hash &&  REVENUELINEITEM1CUSTOMER1_P_1_mapkey1_idxfn::equals(se22, *e18)); 
                  }
                }
              n17 = n17->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_0123456* i20 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_0123456*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_0123456::IdxNode* n20; 
          REVENUECUSTOMER1_DELTA_entry* e20;
        
          for (size_t i = 0; i < i20->size_; i++)
          {
            n20 = i20->buckets_ + i;
            while (n20 && (e20 = n20->obj))
            {
                long c_custkey = e20->C_CUSTKEY;
                STRING_TYPE c_name = e20->C_NAME;
                STRING_TYPE c_address = e20->C_ADDRESS;
                long c_nationkey = e20->C_NATIONKEY;
                STRING_TYPE c_phone = e20->C_PHONE;
                DOUBLE_TYPE c_acctbal = e20->C_ACCTBAL;
                STRING_TYPE c_comment = e20->C_COMMENT;
                long v20 = e20->__av;
                { //slice 
                  const HashIndex_REVENUECUSTOMER1_P_2_map_0* i21 = static_cast<HashIndex_REVENUECUSTOMER1_P_2_map_0*>(REVENUECUSTOMER1_P_2.index[1]);
                  const HASH_RES_t h8 = REVENUECUSTOMER1_P_2_mapkey0_idxfn::hash(se24.modify0(c_nationkey));
                  HashIndex_REVENUECUSTOMER1_P_2_map_0::IdxNode* n21 = static_cast<HashIndex_REVENUECUSTOMER1_P_2_map_0::IdxNode*>(i21->slice(se24, h8));
                  REVENUECUSTOMER1_P_2_entry* e21;
                 
                  if (n21 && (e21 = n21->obj)) {
                    do {                
                      STRING_TYPE n_name = e21->N_NAME;
                      long v21 = e21->__av;
                      REVENUEORDERS1_P_2.addOrDelOnZero(se23.modify(c_custkey,c_name,c_address,c_phone,c_acctbal,c_comment,n_name),(v20 * v21));
                      n21 = n21->nxt;
                    } while (n21 && (e21 = n21->obj) && h8 == n21->hash &&  REVENUECUSTOMER1_P_2_mapkey0_idxfn::equals(se24, *e21)); 
                  }
                }
              n20 = n20->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        REVENUECUSTOMER1_P_2.clear();
        {  // foreach
          const HashIndex_NATION_map_0123* i22 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n22; 
          NATION_entry* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
                long c_nationkey = e22->NATION_NATIONKEY;
                STRING_TYPE n_name = e22->NATION_NAME;
                long n_regionkey = e22->NATION_REGIONKEY;
                STRING_TYPE n_comment = e22->NATION_COMMENT;
                long v22 = e22->__av;
                REVENUECUSTOMER1_P_2.addOrDelOnZero(se25.modify(c_nationkey,n_name),v22);
              n22 = n22->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    REVENUELINEITEM1_DELTA_entry se1;
    REVENUE_entry se2;
    REVENUELINEITEM1_entry se3;
    REVENUEORDERS1_P_1_entry se4;
    REVENUECUSTOMER1_P_1_entry se5;
    REVENUELINEITEM1CUSTOMER1_P_1_entry se6;
    REVENUEORDERS1_DELTA_entry se7;
    REVENUE_entry se8;
    REVENUEORDERS1_P_1_entry se9;
    REVENUEORDERS1_P_2_entry se10;
    REVENUELINEITEM1_entry se11;
    REVENUEORDERS1_P_2_entry se12;
    REVENUELINEITEM1CUSTOMER1_P_1_entry se13;
    REVENUECUSTOMER1_P_1_entry se14;
    REVENUEORDERS1_P_1_entry se15;
    REVENUECUSTOMER1_DELTA_entry se16;
    REVENUE_entry se17;
    REVENUECUSTOMER1_P_1_entry se18;
    REVENUECUSTOMER1_P_2_entry se19;
    REVENUELINEITEM1_entry se20;
    REVENUECUSTOMER1_P_2_entry se21;
    REVENUELINEITEM1CUSTOMER1_P_1_entry se22;
    REVENUEORDERS1_P_2_entry se23;
    REVENUECUSTOMER1_P_2_entry se24;
    REVENUECUSTOMER1_P_2_entry se25;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REVENUELINEITEM1_DELTA_map REVENUELINEITEM1_DELTA;
    REVENUELINEITEM1_map REVENUELINEITEM1;
    REVENUELINEITEM1CUSTOMER1_P_1_map REVENUELINEITEM1CUSTOMER1_P_1;
    REVENUEORDERS1_DELTA_map REVENUEORDERS1_DELTA;
    REVENUEORDERS1_P_1_map REVENUEORDERS1_P_1;
    REVENUEORDERS1_P_2_map REVENUEORDERS1_P_2;
    REVENUECUSTOMER1_DELTA_map REVENUECUSTOMER1_DELTA;
    REVENUECUSTOMER1_P_1_map REVENUECUSTOMER1_P_1;
    REVENUECUSTOMER1_P_2_map REVENUECUSTOMER1_P_2;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_ORDERS_map DELTA_ORDERS;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    
    /*const static*/ STRING_TYPE c1;
    /*const static*/ long c3;
    /*const static*/ long c2;
    /*const static*/ STRING_TYPE c5;
  
  };

}
