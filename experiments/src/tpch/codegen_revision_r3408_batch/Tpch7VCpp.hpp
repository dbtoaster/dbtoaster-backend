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
  
  struct REVENUE_entry {
    STRING_TYPE SHIPPING_SUPP_NATION; STRING_TYPE SHIPPING_CUST_NATION; long SHIPPING_L_YEAR; DOUBLE_TYPE __av; 
    explicit REVENUE_entry() { /*SHIPPING_SUPP_NATION = ""; SHIPPING_CUST_NATION = ""; SHIPPING_L_YEAR = 0L; __av = 0.0; */ }
    explicit REVENUE_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const DOUBLE_TYPE c3) { SHIPPING_SUPP_NATION = c0; SHIPPING_CUST_NATION = c1; SHIPPING_L_YEAR = c2; __av = c3; }
    REVENUE_entry(const REVENUE_entry& other) : SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { SHIPPING_SUPP_NATION = c0; SHIPPING_CUST_NATION = c1; SHIPPING_L_YEAR = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      hash_combine(h, e.SHIPPING_L_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_entry& x, const REVENUE_entry& y) {
      return x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR;
    }
  };
  
  typedef MultiHashMap<REVENUE_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_entry,DOUBLE_TYPE,REVENUE_mapkey012_idxfn,true>
  > REVENUE_map;
  typedef HashIndex<REVENUE_entry,DOUBLE_TYPE,REVENUE_mapkey012_idxfn,true> HashIndex_REVENUE_map_012;
  
  struct REVENUECUSTOMER1_DELTA_entry {
    long O_CUSTKEY; long C_NATIONKEY; long __av; 
    explicit REVENUECUSTOMER1_DELTA_entry() { /*O_CUSTKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUECUSTOMER1_DELTA_entry(const long c0, const long c1, const long c2) { O_CUSTKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUECUSTOMER1_DELTA_entry(const REVENUECUSTOMER1_DELTA_entry& other) : O_CUSTKEY( other.O_CUSTKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1_DELTA_entry& modify(const long c0, const long c1) { O_CUSTKEY = c0; C_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_DELTA_entry& x, const REVENUECUSTOMER1_DELTA_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1_DELTA_entry,long,
    HashIndex<REVENUECUSTOMER1_DELTA_entry,long,REVENUECUSTOMER1_DELTA_mapkey01_idxfn,true>
  > REVENUECUSTOMER1_DELTA_map;
  typedef HashIndex<REVENUECUSTOMER1_DELTA_entry,long,REVENUECUSTOMER1_DELTA_mapkey01_idxfn,true> HashIndex_REVENUECUSTOMER1_DELTA_map_01;
  
  struct REVENUECUSTOMER1_entry {
    long O_CUSTKEY; long C_NATIONKEY; long SHIPPING_L_YEAR; STRING_TYPE SHIPPING_SUPP_NATION; STRING_TYPE SHIPPING_CUST_NATION; DOUBLE_TYPE __av; 
    explicit REVENUECUSTOMER1_entry() { /*O_CUSTKEY = 0L; C_NATIONKEY = 0L; SHIPPING_L_YEAR = 0L; SHIPPING_SUPP_NATION = ""; SHIPPING_CUST_NATION = ""; __av = 0.0; */ }
    explicit REVENUECUSTOMER1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5) { O_CUSTKEY = c0; C_NATIONKEY = c1; SHIPPING_L_YEAR = c2; SHIPPING_SUPP_NATION = c3; SHIPPING_CUST_NATION = c4; __av = c5; }
    REVENUECUSTOMER1_entry(const REVENUECUSTOMER1_entry& other) : O_CUSTKEY( other.O_CUSTKEY ), C_NATIONKEY( other.C_NATIONKEY ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const STRING_TYPE& c4) { O_CUSTKEY = c0; C_NATIONKEY = c1; SHIPPING_L_YEAR = c2; SHIPPING_SUPP_NATION = c3; SHIPPING_CUST_NATION = c4;  return *this; }
    FORCE_INLINE REVENUECUSTOMER1_entry& modify01(const long c0, const long c1) { O_CUSTKEY = c0; C_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.SHIPPING_L_YEAR);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_entry& x, const REVENUECUSTOMER1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY && x.C_NATIONKEY == y.C_NATIONKEY && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION;
    }
  };
  
  struct REVENUECUSTOMER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_entry& x, const REVENUECUSTOMER1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<REVENUECUSTOMER1_entry,DOUBLE_TYPE,REVENUECUSTOMER1_mapkey01234_idxfn,true>,
    HashIndex<REVENUECUSTOMER1_entry,DOUBLE_TYPE,REVENUECUSTOMER1_mapkey01_idxfn,false>
  > REVENUECUSTOMER1_map;
  typedef HashIndex<REVENUECUSTOMER1_entry,DOUBLE_TYPE,REVENUECUSTOMER1_mapkey01234_idxfn,true> HashIndex_REVENUECUSTOMER1_map_01234;
  typedef HashIndex<REVENUECUSTOMER1_entry,DOUBLE_TYPE,REVENUECUSTOMER1_mapkey01_idxfn,false> HashIndex_REVENUECUSTOMER1_map_01;
  
  struct REVENUECUSTOMER1ORDERS1_entry {
    long L_ORDERKEY; long C_NATIONKEY; long SHIPPING_L_YEAR; STRING_TYPE SHIPPING_SUPP_NATION; STRING_TYPE SHIPPING_CUST_NATION; DOUBLE_TYPE __av; 
    explicit REVENUECUSTOMER1ORDERS1_entry() { /*L_ORDERKEY = 0L; C_NATIONKEY = 0L; SHIPPING_L_YEAR = 0L; SHIPPING_SUPP_NATION = ""; SHIPPING_CUST_NATION = ""; __av = 0.0; */ }
    explicit REVENUECUSTOMER1ORDERS1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5) { L_ORDERKEY = c0; C_NATIONKEY = c1; SHIPPING_L_YEAR = c2; SHIPPING_SUPP_NATION = c3; SHIPPING_CUST_NATION = c4; __av = c5; }
    REVENUECUSTOMER1ORDERS1_entry(const REVENUECUSTOMER1ORDERS1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), C_NATIONKEY( other.C_NATIONKEY ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1ORDERS1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const STRING_TYPE& c4) { L_ORDERKEY = c0; C_NATIONKEY = c1; SHIPPING_L_YEAR = c2; SHIPPING_SUPP_NATION = c3; SHIPPING_CUST_NATION = c4;  return *this; }
    FORCE_INLINE REVENUECUSTOMER1ORDERS1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1ORDERS1_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1ORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.SHIPPING_L_YEAR);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1ORDERS1_entry& x, const REVENUECUSTOMER1ORDERS1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.C_NATIONKEY == y.C_NATIONKEY && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION;
    }
  };
  
  struct REVENUECUSTOMER1ORDERS1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1ORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1ORDERS1_entry& x, const REVENUECUSTOMER1ORDERS1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1ORDERS1_entry,DOUBLE_TYPE,
    HashIndex<REVENUECUSTOMER1ORDERS1_entry,DOUBLE_TYPE,REVENUECUSTOMER1ORDERS1_mapkey01234_idxfn,true>,
    HashIndex<REVENUECUSTOMER1ORDERS1_entry,DOUBLE_TYPE,REVENUECUSTOMER1ORDERS1_mapkey0_idxfn,false>
  > REVENUECUSTOMER1ORDERS1_map;
  typedef HashIndex<REVENUECUSTOMER1ORDERS1_entry,DOUBLE_TYPE,REVENUECUSTOMER1ORDERS1_mapkey01234_idxfn,true> HashIndex_REVENUECUSTOMER1ORDERS1_map_01234;
  typedef HashIndex<REVENUECUSTOMER1ORDERS1_entry,DOUBLE_TYPE,REVENUECUSTOMER1ORDERS1_mapkey0_idxfn,false> HashIndex_REVENUECUSTOMER1ORDERS1_map_0;
  
  struct REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry {
    long L_ORDERKEY; long S_SUPPKEY; long SHIPPING_L_YEAR; DOUBLE_TYPE __av; 
    explicit REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry() { /*L_ORDERKEY = 0L; S_SUPPKEY = 0L; SHIPPING_L_YEAR = 0L; __av = 0.0; */ }
    explicit REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; S_SUPPKEY = c1; SHIPPING_L_YEAR = c2; __av = c3; }
    REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry(const REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), S_SUPPKEY( other.S_SUPPKEY ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; S_SUPPKEY = c1; SHIPPING_L_YEAR = c2;  return *this; }
    FORCE_INLINE REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.SHIPPING_L_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& x, const REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR;
    }
  };
  
  struct REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& x, const REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& x, const REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry,DOUBLE_TYPE,
    HashIndex<REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey012_idxfn,true>,
    HashIndex<REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey0_idxfn,false>,
    HashIndex<REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey1_idxfn,false>
  > REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map;
  typedef HashIndex<REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey012_idxfn,true> HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_012;
  typedef HashIndex<REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey0_idxfn,false> HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_0;
  typedef HashIndex<REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey1_idxfn,false> HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_1;
  
  struct REVENUECUSTOMER1LINEITEM1_P_1_entry {
    long L_ORDERKEY; long O_CUSTKEY; long __av; 
    explicit REVENUECUSTOMER1LINEITEM1_P_1_entry() { /*L_ORDERKEY = 0L; O_CUSTKEY = 0L; __av = 0L; */ }
    explicit REVENUECUSTOMER1LINEITEM1_P_1_entry(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; O_CUSTKEY = c1; __av = c2; }
    REVENUECUSTOMER1LINEITEM1_P_1_entry(const REVENUECUSTOMER1LINEITEM1_P_1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), O_CUSTKEY( other.O_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1LINEITEM1_P_1_entry& modify(const long c0, const long c1) { L_ORDERKEY = c0; O_CUSTKEY = c1;  return *this; }
    FORCE_INLINE REVENUECUSTOMER1LINEITEM1_P_1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUECUSTOMER1LINEITEM1_P_1_entry& modify1(const long c1) { O_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1LINEITEM1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1LINEITEM1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1LINEITEM1_P_1_entry& x, const REVENUECUSTOMER1LINEITEM1_P_1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  struct REVENUECUSTOMER1LINEITEM1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1LINEITEM1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1LINEITEM1_P_1_entry& x, const REVENUECUSTOMER1LINEITEM1_P_1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct REVENUECUSTOMER1LINEITEM1_P_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1LINEITEM1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1LINEITEM1_P_1_entry& x, const REVENUECUSTOMER1LINEITEM1_P_1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1LINEITEM1_P_1_entry,long,
    HashIndex<REVENUECUSTOMER1LINEITEM1_P_1_entry,long,REVENUECUSTOMER1LINEITEM1_P_1_mapkey01_idxfn,true>,
    HashIndex<REVENUECUSTOMER1LINEITEM1_P_1_entry,long,REVENUECUSTOMER1LINEITEM1_P_1_mapkey0_idxfn,false>,
    HashIndex<REVENUECUSTOMER1LINEITEM1_P_1_entry,long,REVENUECUSTOMER1LINEITEM1_P_1_mapkey1_idxfn,false>
  > REVENUECUSTOMER1LINEITEM1_P_1_map;
  typedef HashIndex<REVENUECUSTOMER1LINEITEM1_P_1_entry,long,REVENUECUSTOMER1LINEITEM1_P_1_mapkey01_idxfn,true> HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_01;
  typedef HashIndex<REVENUECUSTOMER1LINEITEM1_P_1_entry,long,REVENUECUSTOMER1LINEITEM1_P_1_mapkey0_idxfn,false> HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_0;
  typedef HashIndex<REVENUECUSTOMER1LINEITEM1_P_1_entry,long,REVENUECUSTOMER1LINEITEM1_P_1_mapkey1_idxfn,false> HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_1;
  
  struct REVENUECUSTOMER1LINEITEM1_P_2_entry {
    long S_SUPPKEY; long C_NATIONKEY; STRING_TYPE SHIPPING_SUPP_NATION; STRING_TYPE SHIPPING_CUST_NATION; long __av; 
    explicit REVENUECUSTOMER1LINEITEM1_P_2_entry() { /*S_SUPPKEY = 0L; C_NATIONKEY = 0L; SHIPPING_SUPP_NATION = ""; SHIPPING_CUST_NATION = ""; __av = 0L; */ }
    explicit REVENUECUSTOMER1LINEITEM1_P_2_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { S_SUPPKEY = c0; C_NATIONKEY = c1; SHIPPING_SUPP_NATION = c2; SHIPPING_CUST_NATION = c3; __av = c4; }
    REVENUECUSTOMER1LINEITEM1_P_2_entry(const REVENUECUSTOMER1LINEITEM1_P_2_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), C_NATIONKEY( other.C_NATIONKEY ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1LINEITEM1_P_2_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { S_SUPPKEY = c0; C_NATIONKEY = c1; SHIPPING_SUPP_NATION = c2; SHIPPING_CUST_NATION = c3;  return *this; }
    FORCE_INLINE REVENUECUSTOMER1LINEITEM1_P_2_entry& modify0(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1LINEITEM1_P_2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1LINEITEM1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1LINEITEM1_P_2_entry& x, const REVENUECUSTOMER1LINEITEM1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.C_NATIONKEY == y.C_NATIONKEY && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION;
    }
  };
  
  struct REVENUECUSTOMER1LINEITEM1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1LINEITEM1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1LINEITEM1_P_2_entry& x, const REVENUECUSTOMER1LINEITEM1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1LINEITEM1_P_2_entry,long,
    HashIndex<REVENUECUSTOMER1LINEITEM1_P_2_entry,long,REVENUECUSTOMER1LINEITEM1_P_2_mapkey0123_idxfn,true>,
    HashIndex<REVENUECUSTOMER1LINEITEM1_P_2_entry,long,REVENUECUSTOMER1LINEITEM1_P_2_mapkey0_idxfn,false>
  > REVENUECUSTOMER1LINEITEM1_P_2_map;
  typedef HashIndex<REVENUECUSTOMER1LINEITEM1_P_2_entry,long,REVENUECUSTOMER1LINEITEM1_P_2_mapkey0123_idxfn,true> HashIndex_REVENUECUSTOMER1LINEITEM1_P_2_map_0123;
  typedef HashIndex<REVENUECUSTOMER1LINEITEM1_P_2_entry,long,REVENUECUSTOMER1LINEITEM1_P_2_mapkey0_idxfn,false> HashIndex_REVENUECUSTOMER1LINEITEM1_P_2_map_0;
  
  struct REVENUECUSTOMER1SUPPLIER1_P_2_entry {
    long S_SUPPKEY; long O_CUSTKEY; long SHIPPING_L_YEAR; DOUBLE_TYPE __av; 
    explicit REVENUECUSTOMER1SUPPLIER1_P_2_entry() { /*S_SUPPKEY = 0L; O_CUSTKEY = 0L; SHIPPING_L_YEAR = 0L; __av = 0.0; */ }
    explicit REVENUECUSTOMER1SUPPLIER1_P_2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { S_SUPPKEY = c0; O_CUSTKEY = c1; SHIPPING_L_YEAR = c2; __av = c3; }
    REVENUECUSTOMER1SUPPLIER1_P_2_entry(const REVENUECUSTOMER1SUPPLIER1_P_2_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), O_CUSTKEY( other.O_CUSTKEY ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1SUPPLIER1_P_2_entry& modify(const long c0, const long c1, const long c2) { S_SUPPKEY = c0; O_CUSTKEY = c1; SHIPPING_L_YEAR = c2;  return *this; }
    FORCE_INLINE REVENUECUSTOMER1SUPPLIER1_P_2_entry& modify1(const long c1) { O_CUSTKEY = c1;  return *this; }
    FORCE_INLINE REVENUECUSTOMER1SUPPLIER1_P_2_entry& modify0(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1SUPPLIER1_P_2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.SHIPPING_L_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1SUPPLIER1_P_2_entry& x, const REVENUECUSTOMER1SUPPLIER1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.O_CUSTKEY == y.O_CUSTKEY && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR;
    }
  };
  
  struct REVENUECUSTOMER1SUPPLIER1_P_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1SUPPLIER1_P_2_entry& x, const REVENUECUSTOMER1SUPPLIER1_P_2_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  struct REVENUECUSTOMER1SUPPLIER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1SUPPLIER1_P_2_entry& x, const REVENUECUSTOMER1SUPPLIER1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1SUPPLIER1_P_2_entry,DOUBLE_TYPE,
    HashIndex<REVENUECUSTOMER1SUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1SUPPLIER1_P_2_mapkey012_idxfn,true>,
    HashIndex<REVENUECUSTOMER1SUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1SUPPLIER1_P_2_mapkey1_idxfn,false>,
    HashIndex<REVENUECUSTOMER1SUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1SUPPLIER1_P_2_mapkey0_idxfn,false>
  > REVENUECUSTOMER1SUPPLIER1_P_2_map;
  typedef HashIndex<REVENUECUSTOMER1SUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1SUPPLIER1_P_2_mapkey012_idxfn,true> HashIndex_REVENUECUSTOMER1SUPPLIER1_P_2_map_012;
  typedef HashIndex<REVENUECUSTOMER1SUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1SUPPLIER1_P_2_mapkey1_idxfn,false> HashIndex_REVENUECUSTOMER1SUPPLIER1_P_2_map_1;
  typedef HashIndex<REVENUECUSTOMER1SUPPLIER1_P_2_entry,DOUBLE_TYPE,REVENUECUSTOMER1SUPPLIER1_P_2_mapkey0_idxfn,false> HashIndex_REVENUECUSTOMER1SUPPLIER1_P_2_map_0;
  
  struct REVENUEORDERS1_DELTA_entry {
    long L_ORDERKEY; long O_CUSTKEY; long __av; 
    explicit REVENUEORDERS1_DELTA_entry() { /*L_ORDERKEY = 0L; O_CUSTKEY = 0L; __av = 0L; */ }
    explicit REVENUEORDERS1_DELTA_entry(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; O_CUSTKEY = c1; __av = c2; }
    REVENUEORDERS1_DELTA_entry(const REVENUEORDERS1_DELTA_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), O_CUSTKEY( other.O_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUEORDERS1_DELTA_entry& modify(const long c0, const long c1) { L_ORDERKEY = c0; O_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEORDERS1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_DELTA_entry& x, const REVENUEORDERS1_DELTA_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEORDERS1_DELTA_entry,long,
    HashIndex<REVENUEORDERS1_DELTA_entry,long,REVENUEORDERS1_DELTA_mapkey01_idxfn,true>
  > REVENUEORDERS1_DELTA_map;
  typedef HashIndex<REVENUEORDERS1_DELTA_entry,long,REVENUEORDERS1_DELTA_mapkey01_idxfn,true> HashIndex_REVENUEORDERS1_DELTA_map_01;
  
  struct REVENUEORDERS1_T_2_entry {
    long O_CUSTKEY; long C_NATIONKEY; long __av; 
    explicit REVENUEORDERS1_T_2_entry() { /*O_CUSTKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUEORDERS1_T_2_entry(const long c0, const long c1, const long c2) { O_CUSTKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUEORDERS1_T_2_entry(const REVENUEORDERS1_T_2_entry& other) : O_CUSTKEY( other.O_CUSTKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUEORDERS1_T_2_entry& modify(const long c0, const long c1) { O_CUSTKEY = c0; C_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUEORDERS1_T_2_entry& modify0(const long c0) { O_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEORDERS1_T_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_T_2_entry& x, const REVENUEORDERS1_T_2_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  struct REVENUEORDERS1_T_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_T_2_entry& x, const REVENUEORDERS1_T_2_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEORDERS1_T_2_entry,long,
    HashIndex<REVENUEORDERS1_T_2_entry,long,REVENUEORDERS1_T_2_mapkey01_idxfn,true>,
    HashIndex<REVENUEORDERS1_T_2_entry,long,REVENUEORDERS1_T_2_mapkey0_idxfn,false>
  > REVENUEORDERS1_T_2_map;
  typedef HashIndex<REVENUEORDERS1_T_2_entry,long,REVENUEORDERS1_T_2_mapkey01_idxfn,true> HashIndex_REVENUEORDERS1_T_2_map_01;
  typedef HashIndex<REVENUEORDERS1_T_2_entry,long,REVENUEORDERS1_T_2_mapkey0_idxfn,false> HashIndex_REVENUEORDERS1_T_2_map_0;
  
  struct REVENUEORDERS1_T_3_entry {
    long L_ORDERKEY; long S_NATIONKEY; long SHIPPING_L_YEAR; DOUBLE_TYPE __av; 
    explicit REVENUEORDERS1_T_3_entry() { /*L_ORDERKEY = 0L; S_NATIONKEY = 0L; SHIPPING_L_YEAR = 0L; __av = 0.0; */ }
    explicit REVENUEORDERS1_T_3_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; S_NATIONKEY = c1; SHIPPING_L_YEAR = c2; __av = c3; }
    REVENUEORDERS1_T_3_entry(const REVENUEORDERS1_T_3_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), S_NATIONKEY( other.S_NATIONKEY ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), __av( other.__av ) {}
    FORCE_INLINE REVENUEORDERS1_T_3_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; S_NATIONKEY = c1; SHIPPING_L_YEAR = c2;  return *this; }
    FORCE_INLINE REVENUEORDERS1_T_3_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEORDERS1_T_3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.S_NATIONKEY);
      hash_combine(h, e.SHIPPING_L_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_T_3_entry& x, const REVENUEORDERS1_T_3_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.S_NATIONKEY == y.S_NATIONKEY && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR;
    }
  };
  
  struct REVENUEORDERS1_T_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS1_T_3_entry& x, const REVENUEORDERS1_T_3_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEORDERS1_T_3_entry,DOUBLE_TYPE,
    HashIndex<REVENUEORDERS1_T_3_entry,DOUBLE_TYPE,REVENUEORDERS1_T_3_mapkey012_idxfn,true>,
    HashIndex<REVENUEORDERS1_T_3_entry,DOUBLE_TYPE,REVENUEORDERS1_T_3_mapkey0_idxfn,false>
  > REVENUEORDERS1_T_3_map;
  typedef HashIndex<REVENUEORDERS1_T_3_entry,DOUBLE_TYPE,REVENUEORDERS1_T_3_mapkey012_idxfn,true> HashIndex_REVENUEORDERS1_T_3_map_012;
  typedef HashIndex<REVENUEORDERS1_T_3_entry,DOUBLE_TYPE,REVENUEORDERS1_T_3_mapkey0_idxfn,false> HashIndex_REVENUEORDERS1_T_3_map_0;
  
  struct REVENUELINEITEM1_DOMAIN1_entry {
    long SHIPPING_L_YEAR; long __av; 
    explicit REVENUELINEITEM1_DOMAIN1_entry() { /*SHIPPING_L_YEAR = 0L; __av = 0L; */ }
    explicit REVENUELINEITEM1_DOMAIN1_entry(const long c0, const long c1) { SHIPPING_L_YEAR = c0; __av = c1; }
    REVENUELINEITEM1_DOMAIN1_entry(const REVENUELINEITEM1_DOMAIN1_entry& other) : SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_DOMAIN1_entry& modify(const long c0) { SHIPPING_L_YEAR = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SHIPPING_L_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_DOMAIN1_entry& x, const REVENUELINEITEM1_DOMAIN1_entry& y) {
      return x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_DOMAIN1_entry,long,
    HashIndex<REVENUELINEITEM1_DOMAIN1_entry,long,REVENUELINEITEM1_DOMAIN1_mapkey0_idxfn,true>
  > REVENUELINEITEM1_DOMAIN1_map;
  typedef HashIndex<REVENUELINEITEM1_DOMAIN1_entry,long,REVENUELINEITEM1_DOMAIN1_mapkey0_idxfn,true> HashIndex_REVENUELINEITEM1_DOMAIN1_map_0;
  
  struct REVENUELINEITEM1_DELTA_entry {
    long L_ORDERKEY; long S_SUPPKEY; long SHIPPING_L_YEAR; DOUBLE_TYPE __av; 
    explicit REVENUELINEITEM1_DELTA_entry() { /*L_ORDERKEY = 0L; S_SUPPKEY = 0L; SHIPPING_L_YEAR = 0L; __av = 0.0; */ }
    explicit REVENUELINEITEM1_DELTA_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; S_SUPPKEY = c1; SHIPPING_L_YEAR = c2; __av = c3; }
    REVENUELINEITEM1_DELTA_entry(const REVENUELINEITEM1_DELTA_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), S_SUPPKEY( other.S_SUPPKEY ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_DELTA_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; S_SUPPKEY = c1; SHIPPING_L_YEAR = c2;  return *this; }
    FORCE_INLINE REVENUELINEITEM1_DELTA_entry& modify2(const long c2) { SHIPPING_L_YEAR = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.SHIPPING_L_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_DELTA_entry& x, const REVENUELINEITEM1_DELTA_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR;
    }
  };
  
  struct REVENUELINEITEM1_DELTA_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SHIPPING_L_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_DELTA_entry& x, const REVENUELINEITEM1_DELTA_entry& y) {
      return x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,REVENUELINEITEM1_DELTA_mapkey012_idxfn,true>,
    HashIndex<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,REVENUELINEITEM1_DELTA_mapkey2_idxfn,false>
  > REVENUELINEITEM1_DELTA_map;
  typedef HashIndex<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,REVENUELINEITEM1_DELTA_mapkey012_idxfn,true> HashIndex_REVENUELINEITEM1_DELTA_map_012;
  typedef HashIndex<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,REVENUELINEITEM1_DELTA_mapkey2_idxfn,false> HashIndex_REVENUELINEITEM1_DELTA_map_2;
  
  struct REVENUELINEITEM1_T_1_entry {
    long C_NATIONKEY; long S_NATIONKEY; STRING_TYPE SHIPPING_CUST_NATION; STRING_TYPE SHIPPING_SUPP_NATION; long __av; 
    explicit REVENUELINEITEM1_T_1_entry() { /*C_NATIONKEY = 0L; S_NATIONKEY = 0L; SHIPPING_CUST_NATION = ""; SHIPPING_SUPP_NATION = ""; __av = 0L; */ }
    explicit REVENUELINEITEM1_T_1_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { C_NATIONKEY = c0; S_NATIONKEY = c1; SHIPPING_CUST_NATION = c2; SHIPPING_SUPP_NATION = c3; __av = c4; }
    REVENUELINEITEM1_T_1_entry(const REVENUELINEITEM1_T_1_entry& other) : C_NATIONKEY( other.C_NATIONKEY ), S_NATIONKEY( other.S_NATIONKEY ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_T_1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { C_NATIONKEY = c0; S_NATIONKEY = c1; SHIPPING_CUST_NATION = c2; SHIPPING_SUPP_NATION = c3;  return *this; }
    FORCE_INLINE REVENUELINEITEM1_T_1_entry& modify01(const long c0, const long c1) { C_NATIONKEY = c0; S_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUELINEITEM1_T_1_entry& modify0(const long c0) { C_NATIONKEY = c0;  return *this; }
    FORCE_INLINE REVENUELINEITEM1_T_1_entry& modify1(const long c1) { S_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_T_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.S_NATIONKEY);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_1_entry& x, const REVENUELINEITEM1_T_1_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.S_NATIONKEY == y.S_NATIONKEY && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION;
    }
  };
  
  struct REVENUELINEITEM1_T_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_1_entry& x, const REVENUELINEITEM1_T_1_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  struct REVENUELINEITEM1_T_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_1_entry& x, const REVENUELINEITEM1_T_1_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  struct REVENUELINEITEM1_T_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_1_entry& x, const REVENUELINEITEM1_T_1_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_T_1_entry,long,
    HashIndex<REVENUELINEITEM1_T_1_entry,long,REVENUELINEITEM1_T_1_mapkey0123_idxfn,true>,
    HashIndex<REVENUELINEITEM1_T_1_entry,long,REVENUELINEITEM1_T_1_mapkey01_idxfn,false>,
    HashIndex<REVENUELINEITEM1_T_1_entry,long,REVENUELINEITEM1_T_1_mapkey0_idxfn,false>,
    HashIndex<REVENUELINEITEM1_T_1_entry,long,REVENUELINEITEM1_T_1_mapkey1_idxfn,false>
  > REVENUELINEITEM1_T_1_map;
  typedef HashIndex<REVENUELINEITEM1_T_1_entry,long,REVENUELINEITEM1_T_1_mapkey0123_idxfn,true> HashIndex_REVENUELINEITEM1_T_1_map_0123;
  typedef HashIndex<REVENUELINEITEM1_T_1_entry,long,REVENUELINEITEM1_T_1_mapkey01_idxfn,false> HashIndex_REVENUELINEITEM1_T_1_map_01;
  typedef HashIndex<REVENUELINEITEM1_T_1_entry,long,REVENUELINEITEM1_T_1_mapkey0_idxfn,false> HashIndex_REVENUELINEITEM1_T_1_map_0;
  typedef HashIndex<REVENUELINEITEM1_T_1_entry,long,REVENUELINEITEM1_T_1_mapkey1_idxfn,false> HashIndex_REVENUELINEITEM1_T_1_map_1;
  
  struct REVENUELINEITEM1_T_2_entry {
    long C_NATIONKEY; long L_ORDERKEY; long __av; 
    explicit REVENUELINEITEM1_T_2_entry() { /*C_NATIONKEY = 0L; L_ORDERKEY = 0L; __av = 0L; */ }
    explicit REVENUELINEITEM1_T_2_entry(const long c0, const long c1, const long c2) { C_NATIONKEY = c0; L_ORDERKEY = c1; __av = c2; }
    REVENUELINEITEM1_T_2_entry(const REVENUELINEITEM1_T_2_entry& other) : C_NATIONKEY( other.C_NATIONKEY ), L_ORDERKEY( other.L_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_T_2_entry& modify(const long c0, const long c1) { C_NATIONKEY = c0; L_ORDERKEY = c1;  return *this; }
    FORCE_INLINE REVENUELINEITEM1_T_2_entry& modify1(const long c1) { L_ORDERKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_T_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_2_entry& x, const REVENUELINEITEM1_T_2_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct REVENUELINEITEM1_T_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_2_entry& x, const REVENUELINEITEM1_T_2_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_T_2_entry,long,
    HashIndex<REVENUELINEITEM1_T_2_entry,long,REVENUELINEITEM1_T_2_mapkey01_idxfn,true>,
    HashIndex<REVENUELINEITEM1_T_2_entry,long,REVENUELINEITEM1_T_2_mapkey1_idxfn,false>
  > REVENUELINEITEM1_T_2_map;
  typedef HashIndex<REVENUELINEITEM1_T_2_entry,long,REVENUELINEITEM1_T_2_mapkey01_idxfn,true> HashIndex_REVENUELINEITEM1_T_2_map_01;
  typedef HashIndex<REVENUELINEITEM1_T_2_entry,long,REVENUELINEITEM1_T_2_mapkey1_idxfn,false> HashIndex_REVENUELINEITEM1_T_2_map_1;
  
  struct REVENUELINEITEM1_T_3_entry {
    long S_SUPPKEY; long S_NATIONKEY; long __av; 
    explicit REVENUELINEITEM1_T_3_entry() { /*S_SUPPKEY = 0L; S_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUELINEITEM1_T_3_entry(const long c0, const long c1, const long c2) { S_SUPPKEY = c0; S_NATIONKEY = c1; __av = c2; }
    REVENUELINEITEM1_T_3_entry(const REVENUELINEITEM1_T_3_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_T_3_entry& modify(const long c0, const long c1) { S_SUPPKEY = c0; S_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUELINEITEM1_T_3_entry& modify0(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_T_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_3_entry& x, const REVENUELINEITEM1_T_3_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  struct REVENUELINEITEM1_T_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_3_entry& x, const REVENUELINEITEM1_T_3_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_T_3_entry,long,
    HashIndex<REVENUELINEITEM1_T_3_entry,long,REVENUELINEITEM1_T_3_mapkey01_idxfn,true>,
    HashIndex<REVENUELINEITEM1_T_3_entry,long,REVENUELINEITEM1_T_3_mapkey0_idxfn,false>
  > REVENUELINEITEM1_T_3_map;
  typedef HashIndex<REVENUELINEITEM1_T_3_entry,long,REVENUELINEITEM1_T_3_mapkey01_idxfn,true> HashIndex_REVENUELINEITEM1_T_3_map_01;
  typedef HashIndex<REVENUELINEITEM1_T_3_entry,long,REVENUELINEITEM1_T_3_mapkey0_idxfn,false> HashIndex_REVENUELINEITEM1_T_3_map_0;
  
  struct REVENUESUPPLIER1_DELTA_entry {
    long S_SUPPKEY; long S_NATIONKEY; long __av; 
    explicit REVENUESUPPLIER1_DELTA_entry() { /*S_SUPPKEY = 0L; S_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUESUPPLIER1_DELTA_entry(const long c0, const long c1, const long c2) { S_SUPPKEY = c0; S_NATIONKEY = c1; __av = c2; }
    REVENUESUPPLIER1_DELTA_entry(const REVENUESUPPLIER1_DELTA_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER1_DELTA_entry& modify(const long c0, const long c1) { S_SUPPKEY = c0; S_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_DELTA_entry& x, const REVENUESUPPLIER1_DELTA_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER1_DELTA_entry,long,
    HashIndex<REVENUESUPPLIER1_DELTA_entry,long,REVENUESUPPLIER1_DELTA_mapkey01_idxfn,true>
  > REVENUESUPPLIER1_DELTA_map;
  typedef HashIndex<REVENUESUPPLIER1_DELTA_entry,long,REVENUESUPPLIER1_DELTA_mapkey01_idxfn,true> HashIndex_REVENUESUPPLIER1_DELTA_map_01;
  
  struct REVENUESUPPLIER1_entry {
    long S_SUPPKEY; long S_NATIONKEY; long SHIPPING_L_YEAR; STRING_TYPE SHIPPING_SUPP_NATION; STRING_TYPE SHIPPING_CUST_NATION; DOUBLE_TYPE __av; 
    explicit REVENUESUPPLIER1_entry() { /*S_SUPPKEY = 0L; S_NATIONKEY = 0L; SHIPPING_L_YEAR = 0L; SHIPPING_SUPP_NATION = ""; SHIPPING_CUST_NATION = ""; __av = 0.0; */ }
    explicit REVENUESUPPLIER1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5) { S_SUPPKEY = c0; S_NATIONKEY = c1; SHIPPING_L_YEAR = c2; SHIPPING_SUPP_NATION = c3; SHIPPING_CUST_NATION = c4; __av = c5; }
    REVENUESUPPLIER1_entry(const REVENUESUPPLIER1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NATIONKEY( other.S_NATIONKEY ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const STRING_TYPE& c4) { S_SUPPKEY = c0; S_NATIONKEY = c1; SHIPPING_L_YEAR = c2; SHIPPING_SUPP_NATION = c3; SHIPPING_CUST_NATION = c4;  return *this; }
    FORCE_INLINE REVENUESUPPLIER1_entry& modify01(const long c0, const long c1) { S_SUPPKEY = c0; S_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER1_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NATIONKEY);
      hash_combine(h, e.SHIPPING_L_YEAR);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_entry& x, const REVENUESUPPLIER1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NATIONKEY == y.S_NATIONKEY && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION;
    }
  };
  
  struct REVENUESUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1_entry& x, const REVENUESUPPLIER1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER1_entry,DOUBLE_TYPE,
    HashIndex<REVENUESUPPLIER1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_mapkey01234_idxfn,true>,
    HashIndex<REVENUESUPPLIER1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_mapkey01_idxfn,false>
  > REVENUESUPPLIER1_map;
  typedef HashIndex<REVENUESUPPLIER1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_mapkey01234_idxfn,true> HashIndex_REVENUESUPPLIER1_map_01234;
  typedef HashIndex<REVENUESUPPLIER1_entry,DOUBLE_TYPE,REVENUESUPPLIER1_mapkey01_idxfn,false> HashIndex_REVENUESUPPLIER1_map_01;
  
  struct REVENUESUPPLIER1ORDERS1_P_1_entry {
    long O_CUSTKEY; long S_NATIONKEY; STRING_TYPE SHIPPING_SUPP_NATION; STRING_TYPE SHIPPING_CUST_NATION; long __av; 
    explicit REVENUESUPPLIER1ORDERS1_P_1_entry() { /*O_CUSTKEY = 0L; S_NATIONKEY = 0L; SHIPPING_SUPP_NATION = ""; SHIPPING_CUST_NATION = ""; __av = 0L; */ }
    explicit REVENUESUPPLIER1ORDERS1_P_1_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { O_CUSTKEY = c0; S_NATIONKEY = c1; SHIPPING_SUPP_NATION = c2; SHIPPING_CUST_NATION = c3; __av = c4; }
    REVENUESUPPLIER1ORDERS1_P_1_entry(const REVENUESUPPLIER1ORDERS1_P_1_entry& other) : O_CUSTKEY( other.O_CUSTKEY ), S_NATIONKEY( other.S_NATIONKEY ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER1ORDERS1_P_1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { O_CUSTKEY = c0; S_NATIONKEY = c1; SHIPPING_SUPP_NATION = c2; SHIPPING_CUST_NATION = c3;  return *this; }
    FORCE_INLINE REVENUESUPPLIER1ORDERS1_P_1_entry& modify0(const long c0) { O_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER1ORDERS1_P_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1ORDERS1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.S_NATIONKEY);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1ORDERS1_P_1_entry& x, const REVENUESUPPLIER1ORDERS1_P_1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY && x.S_NATIONKEY == y.S_NATIONKEY && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION;
    }
  };
  
  struct REVENUESUPPLIER1ORDERS1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1ORDERS1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1ORDERS1_P_1_entry& x, const REVENUESUPPLIER1ORDERS1_P_1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER1ORDERS1_P_1_entry,long,
    HashIndex<REVENUESUPPLIER1ORDERS1_P_1_entry,long,REVENUESUPPLIER1ORDERS1_P_1_mapkey0123_idxfn,true>,
    HashIndex<REVENUESUPPLIER1ORDERS1_P_1_entry,long,REVENUESUPPLIER1ORDERS1_P_1_mapkey0_idxfn,false>
  > REVENUESUPPLIER1ORDERS1_P_1_map;
  typedef HashIndex<REVENUESUPPLIER1ORDERS1_P_1_entry,long,REVENUESUPPLIER1ORDERS1_P_1_mapkey0123_idxfn,true> HashIndex_REVENUESUPPLIER1ORDERS1_P_1_map_0123;
  typedef HashIndex<REVENUESUPPLIER1ORDERS1_P_1_entry,long,REVENUESUPPLIER1ORDERS1_P_1_mapkey0_idxfn,false> HashIndex_REVENUESUPPLIER1ORDERS1_P_1_map_0;
  
  struct REVENUESUPPLIER1LINEITEM1_entry {
    long L_ORDERKEY; long S_NATIONKEY; STRING_TYPE SHIPPING_SUPP_NATION; STRING_TYPE SHIPPING_CUST_NATION; long __av; 
    explicit REVENUESUPPLIER1LINEITEM1_entry() { /*L_ORDERKEY = 0L; S_NATIONKEY = 0L; SHIPPING_SUPP_NATION = ""; SHIPPING_CUST_NATION = ""; __av = 0L; */ }
    explicit REVENUESUPPLIER1LINEITEM1_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { L_ORDERKEY = c0; S_NATIONKEY = c1; SHIPPING_SUPP_NATION = c2; SHIPPING_CUST_NATION = c3; __av = c4; }
    REVENUESUPPLIER1LINEITEM1_entry(const REVENUESUPPLIER1LINEITEM1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), S_NATIONKEY( other.S_NATIONKEY ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER1LINEITEM1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { L_ORDERKEY = c0; S_NATIONKEY = c1; SHIPPING_SUPP_NATION = c2; SHIPPING_CUST_NATION = c3;  return *this; }
    FORCE_INLINE REVENUESUPPLIER1LINEITEM1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER1LINEITEM1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.S_NATIONKEY);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1LINEITEM1_entry& x, const REVENUESUPPLIER1LINEITEM1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.S_NATIONKEY == y.S_NATIONKEY && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION;
    }
  };
  
  struct REVENUESUPPLIER1LINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER1LINEITEM1_entry& x, const REVENUESUPPLIER1LINEITEM1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER1LINEITEM1_entry,long,
    HashIndex<REVENUESUPPLIER1LINEITEM1_entry,long,REVENUESUPPLIER1LINEITEM1_mapkey0123_idxfn,true>,
    HashIndex<REVENUESUPPLIER1LINEITEM1_entry,long,REVENUESUPPLIER1LINEITEM1_mapkey0_idxfn,false>
  > REVENUESUPPLIER1LINEITEM1_map;
  typedef HashIndex<REVENUESUPPLIER1LINEITEM1_entry,long,REVENUESUPPLIER1LINEITEM1_mapkey0123_idxfn,true> HashIndex_REVENUESUPPLIER1LINEITEM1_map_0123;
  typedef HashIndex<REVENUESUPPLIER1LINEITEM1_entry,long,REVENUESUPPLIER1LINEITEM1_mapkey0_idxfn,false> HashIndex_REVENUESUPPLIER1LINEITEM1_map_0;
  
  struct tuple3_SS_D {
    STRING_TYPE _1; STRING_TYPE _2; DOUBLE_TYPE __av;
    explicit tuple3_SS_D() { }
    explicit tuple3_SS_D(const STRING_TYPE& c1, const STRING_TYPE& c2, DOUBLE_TYPE c__av=0.0) { _1 = c1; _2 = c2; __av = c__av;}
    int operator==(const tuple3_SS_D &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2)); }
    FORCE_INLINE tuple3_SS_D& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, DOUBLE_TYPE c__av) { _1 = c0; _2 = c1; __av = c__av; return *this; }
    static bool equals(const tuple3_SS_D &x, const tuple3_SS_D &y) { return ((x._1==y._1) && (x._2==y._2)); }
    static long hash(const tuple3_SS_D &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
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
    data_t(): tlq_t(), agg1(16U) {
      c2 = Udate(STRING_TYPE("1996-12-31"));
      c4 = STRING_TYPE("FRANCE");
      c1 = Udate(STRING_TYPE("1995-1-1"));
      c3 = STRING_TYPE("GERMANY");
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
        REVENUELINEITEM1_DOMAIN1.clear();
        { 
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                long l_orderkey = DELTA_LINEITEM.orderkey[i];
                // long l_partkey = DELTA_LINEITEM.partkey[i];
                long s_suppkey = DELTA_LINEITEM.suppkey[i];
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
                long l1 = Uyear_part(l_shipdate);
                (/*if */(l_shipdate >= c1 && c2 >= l_shipdate) ? REVENUELINEITEM1_DELTA.addOrDelOnZero(se1.modify(l_orderkey,s_suppkey,l1),(v1 * (l_extendedprice * (1L + (-1L * l_discount))))) : (void)0);
                long v2 = 1L;
                (/*if */(l_shipdate >= c1 && c2 >= l_shipdate) ? REVENUELINEITEM1_DOMAIN1.addOrDelOnZero(se2.modify(l1),(v2 != 0 ? 1L : 0L)) : (void)0);
          }
        }

        {  // foreach
          const HashIndex_REVENUELINEITEM1_DOMAIN1_map_0* i3 = static_cast<HashIndex_REVENUELINEITEM1_DOMAIN1_map_0*>(REVENUELINEITEM1_DOMAIN1.index[0]);
          HashIndex_REVENUELINEITEM1_DOMAIN1_map_0::IdxNode* n3; 
          REVENUELINEITEM1_DOMAIN1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long shipping_l_year = e3->SHIPPING_L_YEAR;
                long v3 = e3->__av;
                agg1.clear();
                
                { //slice 
                  const HashIndex_REVENUELINEITEM1_DELTA_map_2* i4 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_2*>(REVENUELINEITEM1_DELTA.index[1]);
                  const HASH_RES_t h4 = REVENUELINEITEM1_DELTA_mapkey2_idxfn::hash(se7.modify2(shipping_l_year));
                  HashIndex_REVENUELINEITEM1_DELTA_map_2::IdxNode* n4 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_2::IdxNode*>(i4->slice(se7, h4));
                  REVENUELINEITEM1_DELTA_entry* e4;
                 
                  if (n4 && (e4 = n4->obj)) {
                    do {                
                      long l_orderkey = e4->L_ORDERKEY;
                      long s_suppkey = e4->S_SUPPKEY;
                      DOUBLE_TYPE v4 = e4->__av;
                      { //slice 
                        const HashIndex_REVENUELINEITEM1_T_2_map_1* i5 = static_cast<HashIndex_REVENUELINEITEM1_T_2_map_1*>(REVENUELINEITEM1_T_2.index[1]);
                        const HASH_RES_t h3 = REVENUELINEITEM1_T_2_mapkey1_idxfn::hash(se6.modify1(l_orderkey));
                        HashIndex_REVENUELINEITEM1_T_2_map_1::IdxNode* n5 = static_cast<HashIndex_REVENUELINEITEM1_T_2_map_1::IdxNode*>(i5->slice(se6, h3));
                        REVENUELINEITEM1_T_2_entry* e5;
                       
                        if (n5 && (e5 = n5->obj)) {
                          do {                
                            long c_nationkey = e5->C_NATIONKEY;
                            long v5 = e5->__av;
                            { //slice 
                              const HashIndex_REVENUELINEITEM1_T_3_map_0* i6 = static_cast<HashIndex_REVENUELINEITEM1_T_3_map_0*>(REVENUELINEITEM1_T_3.index[1]);
                              const HASH_RES_t h2 = REVENUELINEITEM1_T_3_mapkey0_idxfn::hash(se5.modify0(s_suppkey));
                              HashIndex_REVENUELINEITEM1_T_3_map_0::IdxNode* n6 = static_cast<HashIndex_REVENUELINEITEM1_T_3_map_0::IdxNode*>(i6->slice(se5, h2));
                              REVENUELINEITEM1_T_3_entry* e6;
                             
                              if (n6 && (e6 = n6->obj)) {
                                do {                
                                  long s_nationkey = e6->S_NATIONKEY;
                                  long v6 = e6->__av;
                                  { //slice 
                                    const HashIndex_REVENUELINEITEM1_T_1_map_01* i7 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_01*>(REVENUELINEITEM1_T_1.index[1]);
                                    const HASH_RES_t h1 = REVENUELINEITEM1_T_1_mapkey01_idxfn::hash(se4.modify01(c_nationkey, s_nationkey));
                                    HashIndex_REVENUELINEITEM1_T_1_map_01::IdxNode* n7 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_01::IdxNode*>(i7->slice(se4, h1));
                                    REVENUELINEITEM1_T_1_entry* e7;
                                   
                                    if (n7 && (e7 = n7->obj)) {
                                      do {                
                                        STRING_TYPE shipping_cust_nation = e7->SHIPPING_CUST_NATION;
                                        STRING_TYPE shipping_supp_nation = e7->SHIPPING_SUPP_NATION;
                                        long v7 = e7->__av;
                                        agg1.addOrDelOnZero(st1.modify(shipping_cust_nation,shipping_supp_nation,(v4 * (v5 * (v6 * v7)))), (v4 * (v5 * (v6 * v7))));
                                        n7 = n7->nxt;
                                      } while (n7 && (e7 = n7->obj) && h1 == n7->hash &&  REVENUELINEITEM1_T_1_mapkey01_idxfn::equals(se4, *e7)); 
                                    }
                                  }
                                  n6 = n6->nxt;
                                } while (n6 && (e6 = n6->obj) && h2 == n6->hash &&  REVENUELINEITEM1_T_3_mapkey0_idxfn::equals(se5, *e6)); 
                              }
                            }
                            n5 = n5->nxt;
                          } while (n5 && (e5 = n5->obj) && h3 == n5->hash &&  REVENUELINEITEM1_T_2_mapkey1_idxfn::equals(se6, *e5)); 
                        }
                      }
                      n4 = n4->nxt;
                    } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  REVENUELINEITEM1_DELTA_mapkey2_idxfn::equals(se7, *e4)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple3_SS_D, DOUBLE_TYPE>* i8 = static_cast<HashIndex<tuple3_SS_D, DOUBLE_TYPE>*>(agg1.index[0]);
                  HashIndex<tuple3_SS_D, DOUBLE_TYPE>::IdxNode* n8; 
                  tuple3_SS_D* e8;
                
                  for (size_t i = 0; i < i8->size_; i++)
                  {
                    n8 = i8->buckets_ + i;
                    while (n8 && (e8 = n8->obj))
                    {
                      STRING_TYPE shipping_cust_nation = e8->_1;
                      STRING_TYPE shipping_supp_nation = e8->_2;  
                      DOUBLE_TYPE v8 = e8->__av; 
                    REVENUE.addOrDelOnZero(se3.modify(shipping_supp_nation,shipping_cust_nation,shipping_l_year),((v3 != 0 ? 1L : 0L) * v8));      
                      n8 = n8->nxt;
                    }
                  }
                }
              n3 = n3->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_012* i9 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_012*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_012::IdxNode* n9; 
          REVENUELINEITEM1_DELTA_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long l_orderkey = e9->L_ORDERKEY;
                long s_suppkey = e9->S_SUPPKEY;
                long shipping_l_year = e9->SHIPPING_L_YEAR;
                DOUBLE_TYPE v9 = e9->__av;
                { //slice 
                  const HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_0* i10 = static_cast<HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_0*>(REVENUECUSTOMER1LINEITEM1_P_1.index[1]);
                  const HASH_RES_t h6 = REVENUECUSTOMER1LINEITEM1_P_1_mapkey0_idxfn::hash(se10.modify0(l_orderkey));
                  HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_0::IdxNode* n10 = static_cast<HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_0::IdxNode*>(i10->slice(se10, h6));
                  REVENUECUSTOMER1LINEITEM1_P_1_entry* e10;
                 
                  if (n10 && (e10 = n10->obj)) {
                    do {                
                      long o_custkey = e10->O_CUSTKEY;
                      long v10 = e10->__av;
                      { //slice 
                        const HashIndex_REVENUECUSTOMER1LINEITEM1_P_2_map_0* i11 = static_cast<HashIndex_REVENUECUSTOMER1LINEITEM1_P_2_map_0*>(REVENUECUSTOMER1LINEITEM1_P_2.index[1]);
                        const HASH_RES_t h5 = REVENUECUSTOMER1LINEITEM1_P_2_mapkey0_idxfn::hash(se9.modify0(s_suppkey));
                        HashIndex_REVENUECUSTOMER1LINEITEM1_P_2_map_0::IdxNode* n11 = static_cast<HashIndex_REVENUECUSTOMER1LINEITEM1_P_2_map_0::IdxNode*>(i11->slice(se9, h5));
                        REVENUECUSTOMER1LINEITEM1_P_2_entry* e11;
                       
                        if (n11 && (e11 = n11->obj)) {
                          do {                
                            long c_nationkey = e11->C_NATIONKEY;
                            STRING_TYPE shipping_supp_nation = e11->SHIPPING_SUPP_NATION;
                            STRING_TYPE shipping_cust_nation = e11->SHIPPING_CUST_NATION;
                            long v11 = e11->__av;
                            REVENUECUSTOMER1.addOrDelOnZero(se8.modify(o_custkey,c_nationkey,shipping_l_year,shipping_supp_nation,shipping_cust_nation),(v9 * (v10 * v11)));
                            n11 = n11->nxt;
                          } while (n11 && (e11 = n11->obj) && h5 == n11->hash &&  REVENUECUSTOMER1LINEITEM1_P_2_mapkey0_idxfn::equals(se9, *e11)); 
                        }
                      }
                      n10 = n10->nxt;
                    } while (n10 && (e10 = n10->obj) && h6 == n10->hash &&  REVENUECUSTOMER1LINEITEM1_P_1_mapkey0_idxfn::equals(se10, *e10)); 
                  }
                }
              n9 = n9->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_012* i12 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_012*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_012::IdxNode* n12; 
          REVENUELINEITEM1_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long l_orderkey = e12->L_ORDERKEY;
                long s_suppkey = e12->S_SUPPKEY;
                long shipping_l_year = e12->SHIPPING_L_YEAR;
                DOUBLE_TYPE v12 = e12->__av;
                { //slice 
                  const HashIndex_REVENUECUSTOMER1LINEITEM1_P_2_map_0* i13 = static_cast<HashIndex_REVENUECUSTOMER1LINEITEM1_P_2_map_0*>(REVENUECUSTOMER1LINEITEM1_P_2.index[1]);
                  const HASH_RES_t h7 = REVENUECUSTOMER1LINEITEM1_P_2_mapkey0_idxfn::hash(se12.modify0(s_suppkey));
                  HashIndex_REVENUECUSTOMER1LINEITEM1_P_2_map_0::IdxNode* n13 = static_cast<HashIndex_REVENUECUSTOMER1LINEITEM1_P_2_map_0::IdxNode*>(i13->slice(se12, h7));
                  REVENUECUSTOMER1LINEITEM1_P_2_entry* e13;
                 
                  if (n13 && (e13 = n13->obj)) {
                    do {                
                      long c_nationkey = e13->C_NATIONKEY;
                      STRING_TYPE shipping_supp_nation = e13->SHIPPING_SUPP_NATION;
                      STRING_TYPE shipping_cust_nation = e13->SHIPPING_CUST_NATION;
                      long v13 = e13->__av;
                      REVENUECUSTOMER1ORDERS1.addOrDelOnZero(se11.modify(l_orderkey,c_nationkey,shipping_l_year,shipping_supp_nation,shipping_cust_nation),(v12 * v13));
                      n13 = n13->nxt;
                    } while (n13 && (e13 = n13->obj) && h7 == n13->hash &&  REVENUECUSTOMER1LINEITEM1_P_2_mapkey0_idxfn::equals(se12, *e13)); 
                  }
                }
              n12 = n12->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_012* i14 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_012*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_012::IdxNode* n14; 
          REVENUELINEITEM1_DELTA_entry* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
                long l_orderkey = e14->L_ORDERKEY;
                long s_suppkey = e14->S_SUPPKEY;
                long shipping_l_year = e14->SHIPPING_L_YEAR;
                DOUBLE_TYPE v14 = e14->__av;
                REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2.addOrDelOnZero(se13.modify(l_orderkey,s_suppkey,shipping_l_year),v14);
              n14 = n14->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_012* i15 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_012*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_012::IdxNode* n15; 
          REVENUELINEITEM1_DELTA_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long l_orderkey = e15->L_ORDERKEY;
                long s_suppkey = e15->S_SUPPKEY;
                long shipping_l_year = e15->SHIPPING_L_YEAR;
                DOUBLE_TYPE v15 = e15->__av;
                { //slice 
                  const HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_0* i16 = static_cast<HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_0*>(REVENUECUSTOMER1LINEITEM1_P_1.index[1]);
                  const HASH_RES_t h8 = REVENUECUSTOMER1LINEITEM1_P_1_mapkey0_idxfn::hash(se15.modify0(l_orderkey));
                  HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_0::IdxNode* n16 = static_cast<HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_0::IdxNode*>(i16->slice(se15, h8));
                  REVENUECUSTOMER1LINEITEM1_P_1_entry* e16;
                 
                  if (n16 && (e16 = n16->obj)) {
                    do {                
                      long o_custkey = e16->O_CUSTKEY;
                      long v16 = e16->__av;
                      REVENUECUSTOMER1SUPPLIER1_P_2.addOrDelOnZero(se14.modify(s_suppkey,o_custkey,shipping_l_year),(v15 * v16));
                      n16 = n16->nxt;
                    } while (n16 && (e16 = n16->obj) && h8 == n16->hash &&  REVENUECUSTOMER1LINEITEM1_P_1_mapkey0_idxfn::equals(se15, *e16)); 
                  }
                }
              n15 = n15->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_012* i17 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_012*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_012::IdxNode* n17; 
          REVENUELINEITEM1_DELTA_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long l_orderkey = e17->L_ORDERKEY;
                long s_suppkey = e17->S_SUPPKEY;
                long shipping_l_year = e17->SHIPPING_L_YEAR;
                DOUBLE_TYPE v17 = e17->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_T_3_map_0* i18 = static_cast<HashIndex_REVENUELINEITEM1_T_3_map_0*>(REVENUELINEITEM1_T_3.index[1]);
                  const HASH_RES_t h9 = REVENUELINEITEM1_T_3_mapkey0_idxfn::hash(se17.modify0(s_suppkey));
                  HashIndex_REVENUELINEITEM1_T_3_map_0::IdxNode* n18 = static_cast<HashIndex_REVENUELINEITEM1_T_3_map_0::IdxNode*>(i18->slice(se17, h9));
                  REVENUELINEITEM1_T_3_entry* e18;
                 
                  if (n18 && (e18 = n18->obj)) {
                    do {                
                      long s_nationkey = e18->S_NATIONKEY;
                      long v18 = e18->__av;
                      REVENUEORDERS1_T_3.addOrDelOnZero(se16.modify(l_orderkey,s_nationkey,shipping_l_year),(v17 * v18));
                      n18 = n18->nxt;
                    } while (n18 && (e18 = n18->obj) && h9 == n18->hash &&  REVENUELINEITEM1_T_3_mapkey0_idxfn::equals(se17, *e18)); 
                  }
                }
              n17 = n17->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_012* i19 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_012*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_012::IdxNode* n19; 
          REVENUELINEITEM1_DELTA_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long l_orderkey = e19->L_ORDERKEY;
                long s_suppkey = e19->S_SUPPKEY;
                long shipping_l_year = e19->SHIPPING_L_YEAR;
                DOUBLE_TYPE v19 = e19->__av;
                { //slice 
                  const HashIndex_REVENUESUPPLIER1LINEITEM1_map_0* i20 = static_cast<HashIndex_REVENUESUPPLIER1LINEITEM1_map_0*>(REVENUESUPPLIER1LINEITEM1.index[1]);
                  const HASH_RES_t h10 = REVENUESUPPLIER1LINEITEM1_mapkey0_idxfn::hash(se19.modify0(l_orderkey));
                  HashIndex_REVENUESUPPLIER1LINEITEM1_map_0::IdxNode* n20 = static_cast<HashIndex_REVENUESUPPLIER1LINEITEM1_map_0::IdxNode*>(i20->slice(se19, h10));
                  REVENUESUPPLIER1LINEITEM1_entry* e20;
                 
                  if (n20 && (e20 = n20->obj)) {
                    do {                
                      long s_nationkey = e20->S_NATIONKEY;
                      STRING_TYPE shipping_supp_nation = e20->SHIPPING_SUPP_NATION;
                      STRING_TYPE shipping_cust_nation = e20->SHIPPING_CUST_NATION;
                      long v20 = e20->__av;
                      REVENUESUPPLIER1.addOrDelOnZero(se18.modify(s_suppkey,s_nationkey,shipping_l_year,shipping_supp_nation,shipping_cust_nation),(v19 * v20));
                      n20 = n20->nxt;
                    } while (n20 && (e20 = n20->obj) && h10 == n20->hash &&  REVENUESUPPLIER1LINEITEM1_mapkey0_idxfn::equals(se19, *e20)); 
                  }
                }
              n19 = n19->nxt;
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
                long l_orderkey = DELTA_ORDERS.orderkey[i];
                long o_custkey = DELTA_ORDERS.custkey[i];
                // STRING_TYPE o_orderstatus = DELTA_ORDERS.orderstatus[i];
                // DOUBLE_TYPE o_totalprice = DELTA_ORDERS.totalprice[i];
                // date o_orderdate = DELTA_ORDERS.orderdate[i];
                // STRING_TYPE o_orderpriority = DELTA_ORDERS.orderpriority[i];
                // STRING_TYPE o_clerk = DELTA_ORDERS.clerk[i];
                // long o_shippriority = DELTA_ORDERS.shippriority[i];
                // STRING_TYPE o_comment = DELTA_ORDERS.comment[i];
                long v21 = 1L;
                REVENUEORDERS1_DELTA.addOrDelOnZero(se20.modify(l_orderkey,o_custkey),v21);

          } 
        }
        {  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i22 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n22; 
          REVENUEORDERS1_DELTA_entry* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
                long l_orderkey = e22->L_ORDERKEY;
                long o_custkey = e22->O_CUSTKEY;
                long v22 = e22->__av;
                { //slice 
                  const HashIndex_REVENUEORDERS1_T_2_map_0* i23 = static_cast<HashIndex_REVENUEORDERS1_T_2_map_0*>(REVENUEORDERS1_T_2.index[1]);
                  const HASH_RES_t h13 = REVENUEORDERS1_T_2_mapkey0_idxfn::hash(se24.modify0(o_custkey));
                  HashIndex_REVENUEORDERS1_T_2_map_0::IdxNode* n23 = static_cast<HashIndex_REVENUEORDERS1_T_2_map_0::IdxNode*>(i23->slice(se24, h13));
                  REVENUEORDERS1_T_2_entry* e23;
                 
                  if (n23 && (e23 = n23->obj)) {
                    do {                
                      long c_nationkey = e23->C_NATIONKEY;
                      long v23 = e23->__av;
                      { //slice 
                        const HashIndex_REVENUEORDERS1_T_3_map_0* i24 = static_cast<HashIndex_REVENUEORDERS1_T_3_map_0*>(REVENUEORDERS1_T_3.index[1]);
                        const HASH_RES_t h12 = REVENUEORDERS1_T_3_mapkey0_idxfn::hash(se23.modify0(l_orderkey));
                        HashIndex_REVENUEORDERS1_T_3_map_0::IdxNode* n24 = static_cast<HashIndex_REVENUEORDERS1_T_3_map_0::IdxNode*>(i24->slice(se23, h12));
                        REVENUEORDERS1_T_3_entry* e24;
                       
                        if (n24 && (e24 = n24->obj)) {
                          do {                
                            long s_nationkey = e24->S_NATIONKEY;
                            long shipping_l_year = e24->SHIPPING_L_YEAR;
                            DOUBLE_TYPE v24 = e24->__av;
                            { //slice 
                              const HashIndex_REVENUELINEITEM1_T_1_map_01* i25 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_01*>(REVENUELINEITEM1_T_1.index[1]);
                              const HASH_RES_t h11 = REVENUELINEITEM1_T_1_mapkey01_idxfn::hash(se22.modify01(c_nationkey, s_nationkey));
                              HashIndex_REVENUELINEITEM1_T_1_map_01::IdxNode* n25 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_01::IdxNode*>(i25->slice(se22, h11));
                              REVENUELINEITEM1_T_1_entry* e25;
                             
                              if (n25 && (e25 = n25->obj)) {
                                do {                
                                  STRING_TYPE shipping_cust_nation = e25->SHIPPING_CUST_NATION;
                                  STRING_TYPE shipping_supp_nation = e25->SHIPPING_SUPP_NATION;
                                  long v25 = e25->__av;
                                  REVENUE.addOrDelOnZero(se21.modify(shipping_supp_nation,shipping_cust_nation,shipping_l_year),(v22 * (v23 * (v24 * v25))));
                                  n25 = n25->nxt;
                                } while (n25 && (e25 = n25->obj) && h11 == n25->hash &&  REVENUELINEITEM1_T_1_mapkey01_idxfn::equals(se22, *e25)); 
                              }
                            }
                            n24 = n24->nxt;
                          } while (n24 && (e24 = n24->obj) && h12 == n24->hash &&  REVENUEORDERS1_T_3_mapkey0_idxfn::equals(se23, *e24)); 
                        }
                      }
                      n23 = n23->nxt;
                    } while (n23 && (e23 = n23->obj) && h13 == n23->hash &&  REVENUEORDERS1_T_2_mapkey0_idxfn::equals(se24, *e23)); 
                  }
                }
              n22 = n22->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i26 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n26; 
          REVENUEORDERS1_DELTA_entry* e26;
        
          for (size_t i = 0; i < i26->size_; i++)
          {
            n26 = i26->buckets_ + i;
            while (n26 && (e26 = n26->obj))
            {
                long l_orderkey = e26->L_ORDERKEY;
                long o_custkey = e26->O_CUSTKEY;
                long v26 = e26->__av;
                { //slice 
                  const HashIndex_REVENUECUSTOMER1ORDERS1_map_0* i27 = static_cast<HashIndex_REVENUECUSTOMER1ORDERS1_map_0*>(REVENUECUSTOMER1ORDERS1.index[1]);
                  const HASH_RES_t h14 = REVENUECUSTOMER1ORDERS1_mapkey0_idxfn::hash(se26.modify0(l_orderkey));
                  HashIndex_REVENUECUSTOMER1ORDERS1_map_0::IdxNode* n27 = static_cast<HashIndex_REVENUECUSTOMER1ORDERS1_map_0::IdxNode*>(i27->slice(se26, h14));
                  REVENUECUSTOMER1ORDERS1_entry* e27;
                 
                  if (n27 && (e27 = n27->obj)) {
                    do {                
                      long c_nationkey = e27->C_NATIONKEY;
                      long shipping_l_year = e27->SHIPPING_L_YEAR;
                      STRING_TYPE shipping_supp_nation = e27->SHIPPING_SUPP_NATION;
                      STRING_TYPE shipping_cust_nation = e27->SHIPPING_CUST_NATION;
                      DOUBLE_TYPE v27 = e27->__av;
                      REVENUECUSTOMER1.addOrDelOnZero(se25.modify(o_custkey,c_nationkey,shipping_l_year,shipping_supp_nation,shipping_cust_nation),(v26 * v27));
                      n27 = n27->nxt;
                    } while (n27 && (e27 = n27->obj) && h14 == n27->hash &&  REVENUECUSTOMER1ORDERS1_mapkey0_idxfn::equals(se26, *e27)); 
                  }
                }
              n26 = n26->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i28 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n28; 
          REVENUEORDERS1_DELTA_entry* e28;
        
          for (size_t i = 0; i < i28->size_; i++)
          {
            n28 = i28->buckets_ + i;
            while (n28 && (e28 = n28->obj))
            {
                long l_orderkey = e28->L_ORDERKEY;
                long o_custkey = e28->O_CUSTKEY;
                long v28 = e28->__av;
                REVENUECUSTOMER1LINEITEM1_P_1.addOrDelOnZero(se27.modify(l_orderkey,o_custkey),v28);
              n28 = n28->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i29 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n29; 
          REVENUEORDERS1_DELTA_entry* e29;
        
          for (size_t i = 0; i < i29->size_; i++)
          {
            n29 = i29->buckets_ + i;
            while (n29 && (e29 = n29->obj))
            {
                long l_orderkey = e29->L_ORDERKEY;
                long o_custkey = e29->O_CUSTKEY;
                long v29 = e29->__av;
                { //slice 
                  const HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_0* i30 = static_cast<HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_0*>(REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2.index[1]);
                  const HASH_RES_t h15 = REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey0_idxfn::hash(se29.modify0(l_orderkey));
                  HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_0::IdxNode* n30 = static_cast<HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_0::IdxNode*>(i30->slice(se29, h15));
                  REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry* e30;
                 
                  if (n30 && (e30 = n30->obj)) {
                    do {                
                      long s_suppkey = e30->S_SUPPKEY;
                      long shipping_l_year = e30->SHIPPING_L_YEAR;
                      DOUBLE_TYPE v30 = e30->__av;
                      REVENUECUSTOMER1SUPPLIER1_P_2.addOrDelOnZero(se28.modify(s_suppkey,o_custkey,shipping_l_year),(v29 * v30));
                      n30 = n30->nxt;
                    } while (n30 && (e30 = n30->obj) && h15 == n30->hash &&  REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey0_idxfn::equals(se29, *e30)); 
                  }
                }
              n29 = n29->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i31 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n31; 
          REVENUEORDERS1_DELTA_entry* e31;
        
          for (size_t i = 0; i < i31->size_; i++)
          {
            n31 = i31->buckets_ + i;
            while (n31 && (e31 = n31->obj))
            {
                long l_orderkey = e31->L_ORDERKEY;
                long o_custkey = e31->O_CUSTKEY;
                long v31 = e31->__av;
                { //slice 
                  const HashIndex_REVENUEORDERS1_T_2_map_0* i32 = static_cast<HashIndex_REVENUEORDERS1_T_2_map_0*>(REVENUEORDERS1_T_2.index[1]);
                  const HASH_RES_t h16 = REVENUEORDERS1_T_2_mapkey0_idxfn::hash(se31.modify0(o_custkey));
                  HashIndex_REVENUEORDERS1_T_2_map_0::IdxNode* n32 = static_cast<HashIndex_REVENUEORDERS1_T_2_map_0::IdxNode*>(i32->slice(se31, h16));
                  REVENUEORDERS1_T_2_entry* e32;
                 
                  if (n32 && (e32 = n32->obj)) {
                    do {                
                      long c_nationkey = e32->C_NATIONKEY;
                      long v32 = e32->__av;
                      REVENUELINEITEM1_T_2.addOrDelOnZero(se30.modify(c_nationkey,l_orderkey),(v31 * v32));
                      n32 = n32->nxt;
                    } while (n32 && (e32 = n32->obj) && h16 == n32->hash &&  REVENUEORDERS1_T_2_mapkey0_idxfn::equals(se31, *e32)); 
                  }
                }
              n31 = n31->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i33 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n33; 
          REVENUEORDERS1_DELTA_entry* e33;
        
          for (size_t i = 0; i < i33->size_; i++)
          {
            n33 = i33->buckets_ + i;
            while (n33 && (e33 = n33->obj))
            {
                long l_orderkey = e33->L_ORDERKEY;
                long o_custkey = e33->O_CUSTKEY;
                long v33 = e33->__av;
                { //slice 
                  const HashIndex_REVENUESUPPLIER1ORDERS1_P_1_map_0* i34 = static_cast<HashIndex_REVENUESUPPLIER1ORDERS1_P_1_map_0*>(REVENUESUPPLIER1ORDERS1_P_1.index[1]);
                  const HASH_RES_t h18 = REVENUESUPPLIER1ORDERS1_P_1_mapkey0_idxfn::hash(se34.modify0(o_custkey));
                  HashIndex_REVENUESUPPLIER1ORDERS1_P_1_map_0::IdxNode* n34 = static_cast<HashIndex_REVENUESUPPLIER1ORDERS1_P_1_map_0::IdxNode*>(i34->slice(se34, h18));
                  REVENUESUPPLIER1ORDERS1_P_1_entry* e34;
                 
                  if (n34 && (e34 = n34->obj)) {
                    do {                
                      long s_nationkey = e34->S_NATIONKEY;
                      STRING_TYPE shipping_supp_nation = e34->SHIPPING_SUPP_NATION;
                      STRING_TYPE shipping_cust_nation = e34->SHIPPING_CUST_NATION;
                      long v34 = e34->__av;
                      { //slice 
                        const HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_0* i35 = static_cast<HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_0*>(REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2.index[1]);
                        const HASH_RES_t h17 = REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey0_idxfn::hash(se33.modify0(l_orderkey));
                        HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_0::IdxNode* n35 = static_cast<HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_0::IdxNode*>(i35->slice(se33, h17));
                        REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry* e35;
                       
                        if (n35 && (e35 = n35->obj)) {
                          do {                
                            long s_suppkey = e35->S_SUPPKEY;
                            long shipping_l_year = e35->SHIPPING_L_YEAR;
                            DOUBLE_TYPE v35 = e35->__av;
                            REVENUESUPPLIER1.addOrDelOnZero(se32.modify(s_suppkey,s_nationkey,shipping_l_year,shipping_supp_nation,shipping_cust_nation),(v33 * (v34 * v35)));
                            n35 = n35->nxt;
                          } while (n35 && (e35 = n35->obj) && h17 == n35->hash &&  REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey0_idxfn::equals(se33, *e35)); 
                        }
                      }
                      n34 = n34->nxt;
                    } while (n34 && (e34 = n34->obj) && h18 == n34->hash &&  REVENUESUPPLIER1ORDERS1_P_1_mapkey0_idxfn::equals(se34, *e34)); 
                  }
                }
              n33 = n33->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUEORDERS1_DELTA_map_01* i36 = static_cast<HashIndex_REVENUEORDERS1_DELTA_map_01*>(REVENUEORDERS1_DELTA.index[0]);
          HashIndex_REVENUEORDERS1_DELTA_map_01::IdxNode* n36; 
          REVENUEORDERS1_DELTA_entry* e36;
        
          for (size_t i = 0; i < i36->size_; i++)
          {
            n36 = i36->buckets_ + i;
            while (n36 && (e36 = n36->obj))
            {
                long l_orderkey = e36->L_ORDERKEY;
                long o_custkey = e36->O_CUSTKEY;
                long v36 = e36->__av;
                { //slice 
                  const HashIndex_REVENUESUPPLIER1ORDERS1_P_1_map_0* i37 = static_cast<HashIndex_REVENUESUPPLIER1ORDERS1_P_1_map_0*>(REVENUESUPPLIER1ORDERS1_P_1.index[1]);
                  const HASH_RES_t h19 = REVENUESUPPLIER1ORDERS1_P_1_mapkey0_idxfn::hash(se36.modify0(o_custkey));
                  HashIndex_REVENUESUPPLIER1ORDERS1_P_1_map_0::IdxNode* n37 = static_cast<HashIndex_REVENUESUPPLIER1ORDERS1_P_1_map_0::IdxNode*>(i37->slice(se36, h19));
                  REVENUESUPPLIER1ORDERS1_P_1_entry* e37;
                 
                  if (n37 && (e37 = n37->obj)) {
                    do {                
                      long s_nationkey = e37->S_NATIONKEY;
                      STRING_TYPE shipping_supp_nation = e37->SHIPPING_SUPP_NATION;
                      STRING_TYPE shipping_cust_nation = e37->SHIPPING_CUST_NATION;
                      long v37 = e37->__av;
                      REVENUESUPPLIER1LINEITEM1.addOrDelOnZero(se35.modify(l_orderkey,s_nationkey,shipping_supp_nation,shipping_cust_nation),(v36 * v37));
                      n37 = n37->nxt;
                    } while (n37 && (e37 = n37->obj) && h19 == n37->hash &&  REVENUESUPPLIER1ORDERS1_P_1_mapkey0_idxfn::equals(se36, *e37)); 
                  }
                }
              n36 = n36->nxt;
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
                long o_custkey = DELTA_CUSTOMER.custkey[i];
                // STRING_TYPE c_name = DELTA_CUSTOMER.name[i];
                // STRING_TYPE c_address = DELTA_CUSTOMER.address[i];
                long c_nationkey = DELTA_CUSTOMER.nationkey[i];
                // STRING_TYPE c_phone = DELTA_CUSTOMER.phone[i];
                // DOUBLE_TYPE c_acctbal = DELTA_CUSTOMER.acctbal[i];
                // STRING_TYPE c_mktsegment = DELTA_CUSTOMER.mktsegment[i];
                // STRING_TYPE c_comment = DELTA_CUSTOMER.comment[i];
                long v38 = 1L;
                REVENUECUSTOMER1_DELTA.addOrDelOnZero(se37.modify(o_custkey,c_nationkey),v38);            
          }
        }

        {  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_01* i39 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_01*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_01::IdxNode* n39; 
          REVENUECUSTOMER1_DELTA_entry* e39;
        
          for (size_t i = 0; i < i39->size_; i++)
          {
            n39 = i39->buckets_ + i;
            while (n39 && (e39 = n39->obj))
            {
                long o_custkey = e39->O_CUSTKEY;
                long c_nationkey = e39->C_NATIONKEY;
                long v39 = e39->__av;
                { //slice 
                  const HashIndex_REVENUECUSTOMER1_map_01* i40 = static_cast<HashIndex_REVENUECUSTOMER1_map_01*>(REVENUECUSTOMER1.index[1]);
                  const HASH_RES_t h20 = REVENUECUSTOMER1_mapkey01_idxfn::hash(se39.modify01(o_custkey, c_nationkey));
                  HashIndex_REVENUECUSTOMER1_map_01::IdxNode* n40 = static_cast<HashIndex_REVENUECUSTOMER1_map_01::IdxNode*>(i40->slice(se39, h20));
                  REVENUECUSTOMER1_entry* e40;
                 
                  if (n40 && (e40 = n40->obj)) {
                    do {                
                      long shipping_l_year = e40->SHIPPING_L_YEAR;
                      STRING_TYPE shipping_supp_nation = e40->SHIPPING_SUPP_NATION;
                      STRING_TYPE shipping_cust_nation = e40->SHIPPING_CUST_NATION;
                      DOUBLE_TYPE v40 = e40->__av;
                      REVENUE.addOrDelOnZero(se38.modify(shipping_supp_nation,shipping_cust_nation,shipping_l_year),(v39 * v40));
                      n40 = n40->nxt;
                    } while (n40 && (e40 = n40->obj) && h20 == n40->hash &&  REVENUECUSTOMER1_mapkey01_idxfn::equals(se39, *e40)); 
                  }
                }
              n39 = n39->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_01* i41 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_01*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_01::IdxNode* n41; 
          REVENUECUSTOMER1_DELTA_entry* e41;
        
          for (size_t i = 0; i < i41->size_; i++)
          {
            n41 = i41->buckets_ + i;
            while (n41 && (e41 = n41->obj))
            {
                long o_custkey = e41->O_CUSTKEY;
                long c_nationkey = e41->C_NATIONKEY;
                long v41 = e41->__av;
                REVENUEORDERS1_T_2.addOrDelOnZero(se40.modify(o_custkey,c_nationkey),v41);
              n41 = n41->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_01* i42 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_01*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_01::IdxNode* n42; 
          REVENUECUSTOMER1_DELTA_entry* e42;
        
          for (size_t i = 0; i < i42->size_; i++)
          {
            n42 = i42->buckets_ + i;
            while (n42 && (e42 = n42->obj))
            {
                long o_custkey = e42->O_CUSTKEY;
                long c_nationkey = e42->C_NATIONKEY;
                long v42 = e42->__av;
                { //slice 
                  const HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_1* i43 = static_cast<HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_1*>(REVENUECUSTOMER1LINEITEM1_P_1.index[2]);
                  const HASH_RES_t h21 = REVENUECUSTOMER1LINEITEM1_P_1_mapkey1_idxfn::hash(se42.modify1(o_custkey));
                  HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_1::IdxNode* n43 = static_cast<HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_1::IdxNode*>(i43->slice(se42, h21));
                  REVENUECUSTOMER1LINEITEM1_P_1_entry* e43;
                 
                  if (n43 && (e43 = n43->obj)) {
                    do {                
                      long l_orderkey = e43->L_ORDERKEY;
                      long v43 = e43->__av;
                      REVENUELINEITEM1_T_2.addOrDelOnZero(se41.modify(c_nationkey,l_orderkey),(v42 * v43));
                      n43 = n43->nxt;
                    } while (n43 && (e43 = n43->obj) && h21 == n43->hash &&  REVENUECUSTOMER1LINEITEM1_P_1_mapkey1_idxfn::equals(se42, *e43)); 
                  }
                }
              n42 = n42->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_01* i44 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_01*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_01::IdxNode* n44; 
          REVENUECUSTOMER1_DELTA_entry* e44;
        
          for (size_t i = 0; i < i44->size_; i++)
          {
            n44 = i44->buckets_ + i;
            while (n44 && (e44 = n44->obj))
            {
                long o_custkey = e44->O_CUSTKEY;
                long c_nationkey = e44->C_NATIONKEY;
                long v44 = e44->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_T_1_map_0* i45 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_0*>(REVENUELINEITEM1_T_1.index[2]);
                  const HASH_RES_t h23 = REVENUELINEITEM1_T_1_mapkey0_idxfn::hash(se45.modify0(c_nationkey));
                  HashIndex_REVENUELINEITEM1_T_1_map_0::IdxNode* n45 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_0::IdxNode*>(i45->slice(se45, h23));
                  REVENUELINEITEM1_T_1_entry* e45;
                 
                  if (n45 && (e45 = n45->obj)) {
                    do {                
                      long s_nationkey = e45->S_NATIONKEY;
                      STRING_TYPE shipping_cust_nation = e45->SHIPPING_CUST_NATION;
                      STRING_TYPE shipping_supp_nation = e45->SHIPPING_SUPP_NATION;
                      long v45 = e45->__av;
                      { //slice 
                        const HashIndex_REVENUECUSTOMER1SUPPLIER1_P_2_map_1* i46 = static_cast<HashIndex_REVENUECUSTOMER1SUPPLIER1_P_2_map_1*>(REVENUECUSTOMER1SUPPLIER1_P_2.index[1]);
                        const HASH_RES_t h22 = REVENUECUSTOMER1SUPPLIER1_P_2_mapkey1_idxfn::hash(se44.modify1(o_custkey));
                        HashIndex_REVENUECUSTOMER1SUPPLIER1_P_2_map_1::IdxNode* n46 = static_cast<HashIndex_REVENUECUSTOMER1SUPPLIER1_P_2_map_1::IdxNode*>(i46->slice(se44, h22));
                        REVENUECUSTOMER1SUPPLIER1_P_2_entry* e46;
                       
                        if (n46 && (e46 = n46->obj)) {
                          do {                
                            long s_suppkey = e46->S_SUPPKEY;
                            long shipping_l_year = e46->SHIPPING_L_YEAR;
                            DOUBLE_TYPE v46 = e46->__av;
                            REVENUESUPPLIER1.addOrDelOnZero(se43.modify(s_suppkey,s_nationkey,shipping_l_year,shipping_supp_nation,shipping_cust_nation),(v44 * (v45 * v46)));
                            n46 = n46->nxt;
                          } while (n46 && (e46 = n46->obj) && h22 == n46->hash &&  REVENUECUSTOMER1SUPPLIER1_P_2_mapkey1_idxfn::equals(se44, *e46)); 
                        }
                      }
                      n45 = n45->nxt;
                    } while (n45 && (e45 = n45->obj) && h23 == n45->hash &&  REVENUELINEITEM1_T_1_mapkey0_idxfn::equals(se45, *e45)); 
                  }
                }
              n44 = n44->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_01* i47 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_01*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_01::IdxNode* n47; 
          REVENUECUSTOMER1_DELTA_entry* e47;
        
          for (size_t i = 0; i < i47->size_; i++)
          {
            n47 = i47->buckets_ + i;
            while (n47 && (e47 = n47->obj))
            {
                long o_custkey = e47->O_CUSTKEY;
                long c_nationkey = e47->C_NATIONKEY;
                long v47 = e47->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_T_1_map_0* i48 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_0*>(REVENUELINEITEM1_T_1.index[2]);
                  const HASH_RES_t h24 = REVENUELINEITEM1_T_1_mapkey0_idxfn::hash(se47.modify0(c_nationkey));
                  HashIndex_REVENUELINEITEM1_T_1_map_0::IdxNode* n48 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_0::IdxNode*>(i48->slice(se47, h24));
                  REVENUELINEITEM1_T_1_entry* e48;
                 
                  if (n48 && (e48 = n48->obj)) {
                    do {                
                      long s_nationkey = e48->S_NATIONKEY;
                      STRING_TYPE shipping_cust_nation = e48->SHIPPING_CUST_NATION;
                      STRING_TYPE shipping_supp_nation = e48->SHIPPING_SUPP_NATION;
                      long v48 = e48->__av;
                      REVENUESUPPLIER1ORDERS1_P_1.addOrDelOnZero(se46.modify(o_custkey,s_nationkey,shipping_supp_nation,shipping_cust_nation),(v47 * v48));
                      n48 = n48->nxt;
                    } while (n48 && (e48 = n48->obj) && h24 == n48->hash &&  REVENUELINEITEM1_T_1_mapkey0_idxfn::equals(se47, *e48)); 
                  }
                }
              n47 = n47->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUECUSTOMER1_DELTA_map_01* i49 = static_cast<HashIndex_REVENUECUSTOMER1_DELTA_map_01*>(REVENUECUSTOMER1_DELTA.index[0]);
          HashIndex_REVENUECUSTOMER1_DELTA_map_01::IdxNode* n49; 
          REVENUECUSTOMER1_DELTA_entry* e49;
        
          for (size_t i = 0; i < i49->size_; i++)
          {
            n49 = i49->buckets_ + i;
            while (n49 && (e49 = n49->obj))
            {
                long o_custkey = e49->O_CUSTKEY;
                long c_nationkey = e49->C_NATIONKEY;
                long v49 = e49->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_T_1_map_0* i50 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_0*>(REVENUELINEITEM1_T_1.index[2]);
                  const HASH_RES_t h26 = REVENUELINEITEM1_T_1_mapkey0_idxfn::hash(se50.modify0(c_nationkey));
                  HashIndex_REVENUELINEITEM1_T_1_map_0::IdxNode* n50 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_0::IdxNode*>(i50->slice(se50, h26));
                  REVENUELINEITEM1_T_1_entry* e50;
                 
                  if (n50 && (e50 = n50->obj)) {
                    do {                
                      long s_nationkey = e50->S_NATIONKEY;
                      STRING_TYPE shipping_cust_nation = e50->SHIPPING_CUST_NATION;
                      STRING_TYPE shipping_supp_nation = e50->SHIPPING_SUPP_NATION;
                      long v50 = e50->__av;
                      { //slice 
                        const HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_1* i51 = static_cast<HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_1*>(REVENUECUSTOMER1LINEITEM1_P_1.index[2]);
                        const HASH_RES_t h25 = REVENUECUSTOMER1LINEITEM1_P_1_mapkey1_idxfn::hash(se49.modify1(o_custkey));
                        HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_1::IdxNode* n51 = static_cast<HashIndex_REVENUECUSTOMER1LINEITEM1_P_1_map_1::IdxNode*>(i51->slice(se49, h25));
                        REVENUECUSTOMER1LINEITEM1_P_1_entry* e51;
                       
                        if (n51 && (e51 = n51->obj)) {
                          do {                
                            long l_orderkey = e51->L_ORDERKEY;
                            long v51 = e51->__av;
                            REVENUESUPPLIER1LINEITEM1.addOrDelOnZero(se48.modify(l_orderkey,s_nationkey,shipping_supp_nation,shipping_cust_nation),(v49 * (v50 * v51)));
                            n51 = n51->nxt;
                          } while (n51 && (e51 = n51->obj) && h25 == n51->hash &&  REVENUECUSTOMER1LINEITEM1_P_1_mapkey1_idxfn::equals(se49, *e51)); 
                        }
                      }
                      n50 = n50->nxt;
                    } while (n50 && (e50 = n50->obj) && h26 == n50->hash &&  REVENUELINEITEM1_T_1_mapkey0_idxfn::equals(se50, *e50)); 
                  }
                }
              n49 = n49->nxt;
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
                long s_suppkey = DELTA_SUPPLIER.suppkey[i];
                // STRING_TYPE s_name = DELTA_SUPPLIER.name[i];
                // STRING_TYPE s_address = DELTA_SUPPLIER.address[i];
                long s_nationkey = DELTA_SUPPLIER.nationkey[i];
                // STRING_TYPE s_phone = DELTA_SUPPLIER.phone[i];
                // DOUBLE_TYPE s_acctbal = DELTA_SUPPLIER.acctbal[i];
                // STRING_TYPE s_comment = DELTA_SUPPLIER.comment[i];
                long v52 = 1L;
                REVENUESUPPLIER1_DELTA.addOrDelOnZero(se51.modify(s_suppkey,s_nationkey),v52);            
          }
        }
        {  // foreach
          const HashIndex_REVENUESUPPLIER1_DELTA_map_01* i53 = static_cast<HashIndex_REVENUESUPPLIER1_DELTA_map_01*>(REVENUESUPPLIER1_DELTA.index[0]);
          HashIndex_REVENUESUPPLIER1_DELTA_map_01::IdxNode* n53; 
          REVENUESUPPLIER1_DELTA_entry* e53;
        
          for (size_t i = 0; i < i53->size_; i++)
          {
            n53 = i53->buckets_ + i;
            while (n53 && (e53 = n53->obj))
            {
                long s_suppkey = e53->S_SUPPKEY;
                long s_nationkey = e53->S_NATIONKEY;
                long v53 = e53->__av;
                { //slice 
                  const HashIndex_REVENUESUPPLIER1_map_01* i54 = static_cast<HashIndex_REVENUESUPPLIER1_map_01*>(REVENUESUPPLIER1.index[1]);
                  const HASH_RES_t h27 = REVENUESUPPLIER1_mapkey01_idxfn::hash(se53.modify01(s_suppkey, s_nationkey));
                  HashIndex_REVENUESUPPLIER1_map_01::IdxNode* n54 = static_cast<HashIndex_REVENUESUPPLIER1_map_01::IdxNode*>(i54->slice(se53, h27));
                  REVENUESUPPLIER1_entry* e54;
                 
                  if (n54 && (e54 = n54->obj)) {
                    do {                
                      long shipping_l_year = e54->SHIPPING_L_YEAR;
                      STRING_TYPE shipping_supp_nation = e54->SHIPPING_SUPP_NATION;
                      STRING_TYPE shipping_cust_nation = e54->SHIPPING_CUST_NATION;
                      DOUBLE_TYPE v54 = e54->__av;
                      REVENUE.addOrDelOnZero(se52.modify(shipping_supp_nation,shipping_cust_nation,shipping_l_year),(v53 * v54));
                      n54 = n54->nxt;
                    } while (n54 && (e54 = n54->obj) && h27 == n54->hash &&  REVENUESUPPLIER1_mapkey01_idxfn::equals(se53, *e54)); 
                  }
                }
              n53 = n53->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUESUPPLIER1_DELTA_map_01* i55 = static_cast<HashIndex_REVENUESUPPLIER1_DELTA_map_01*>(REVENUESUPPLIER1_DELTA.index[0]);
          HashIndex_REVENUESUPPLIER1_DELTA_map_01::IdxNode* n55; 
          REVENUESUPPLIER1_DELTA_entry* e55;
        
          for (size_t i = 0; i < i55->size_; i++)
          {
            n55 = i55->buckets_ + i;
            while (n55 && (e55 = n55->obj))
            {
                long s_suppkey = e55->S_SUPPKEY;
                long s_nationkey = e55->S_NATIONKEY;
                long v55 = e55->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_T_1_map_1* i56 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_1*>(REVENUELINEITEM1_T_1.index[3]);
                  const HASH_RES_t h29 = REVENUELINEITEM1_T_1_mapkey1_idxfn::hash(se56.modify1(s_nationkey));
                  HashIndex_REVENUELINEITEM1_T_1_map_1::IdxNode* n56 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_1::IdxNode*>(i56->slice(se56, h29));
                  REVENUELINEITEM1_T_1_entry* e56;
                 
                  if (n56 && (e56 = n56->obj)) {
                    do {                
                      long c_nationkey = e56->C_NATIONKEY;
                      STRING_TYPE shipping_cust_nation = e56->SHIPPING_CUST_NATION;
                      STRING_TYPE shipping_supp_nation = e56->SHIPPING_SUPP_NATION;
                      long v56 = e56->__av;
                      { //slice 
                        const HashIndex_REVENUECUSTOMER1SUPPLIER1_P_2_map_0* i57 = static_cast<HashIndex_REVENUECUSTOMER1SUPPLIER1_P_2_map_0*>(REVENUECUSTOMER1SUPPLIER1_P_2.index[2]);
                        const HASH_RES_t h28 = REVENUECUSTOMER1SUPPLIER1_P_2_mapkey0_idxfn::hash(se55.modify0(s_suppkey));
                        HashIndex_REVENUECUSTOMER1SUPPLIER1_P_2_map_0::IdxNode* n57 = static_cast<HashIndex_REVENUECUSTOMER1SUPPLIER1_P_2_map_0::IdxNode*>(i57->slice(se55, h28));
                        REVENUECUSTOMER1SUPPLIER1_P_2_entry* e57;
                       
                        if (n57 && (e57 = n57->obj)) {
                          do {                
                            long o_custkey = e57->O_CUSTKEY;
                            long shipping_l_year = e57->SHIPPING_L_YEAR;
                            DOUBLE_TYPE v57 = e57->__av;
                            REVENUECUSTOMER1.addOrDelOnZero(se54.modify(o_custkey,c_nationkey,shipping_l_year,shipping_supp_nation,shipping_cust_nation),(v55 * (v56 * v57)));
                            n57 = n57->nxt;
                          } while (n57 && (e57 = n57->obj) && h28 == n57->hash &&  REVENUECUSTOMER1SUPPLIER1_P_2_mapkey0_idxfn::equals(se55, *e57)); 
                        }
                      }
                      n56 = n56->nxt;
                    } while (n56 && (e56 = n56->obj) && h29 == n56->hash &&  REVENUELINEITEM1_T_1_mapkey1_idxfn::equals(se56, *e56)); 
                  }
                }
              n55 = n55->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUESUPPLIER1_DELTA_map_01* i58 = static_cast<HashIndex_REVENUESUPPLIER1_DELTA_map_01*>(REVENUESUPPLIER1_DELTA.index[0]);
          HashIndex_REVENUESUPPLIER1_DELTA_map_01::IdxNode* n58; 
          REVENUESUPPLIER1_DELTA_entry* e58;
        
          for (size_t i = 0; i < i58->size_; i++)
          {
            n58 = i58->buckets_ + i;
            while (n58 && (e58 = n58->obj))
            {
                long s_suppkey = e58->S_SUPPKEY;
                long s_nationkey = e58->S_NATIONKEY;
                long v58 = e58->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_T_1_map_1* i59 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_1*>(REVENUELINEITEM1_T_1.index[3]);
                  const HASH_RES_t h31 = REVENUELINEITEM1_T_1_mapkey1_idxfn::hash(se59.modify1(s_nationkey));
                  HashIndex_REVENUELINEITEM1_T_1_map_1::IdxNode* n59 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_1::IdxNode*>(i59->slice(se59, h31));
                  REVENUELINEITEM1_T_1_entry* e59;
                 
                  if (n59 && (e59 = n59->obj)) {
                    do {                
                      long c_nationkey = e59->C_NATIONKEY;
                      STRING_TYPE shipping_cust_nation = e59->SHIPPING_CUST_NATION;
                      STRING_TYPE shipping_supp_nation = e59->SHIPPING_SUPP_NATION;
                      long v59 = e59->__av;
                      { //slice 
                        const HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_1* i60 = static_cast<HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_1*>(REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2.index[2]);
                        const HASH_RES_t h30 = REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey1_idxfn::hash(se58.modify1(s_suppkey));
                        HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_1::IdxNode* n60 = static_cast<HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_1::IdxNode*>(i60->slice(se58, h30));
                        REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry* e60;
                       
                        if (n60 && (e60 = n60->obj)) {
                          do {                
                            long l_orderkey = e60->L_ORDERKEY;
                            long shipping_l_year = e60->SHIPPING_L_YEAR;
                            DOUBLE_TYPE v60 = e60->__av;
                            REVENUECUSTOMER1ORDERS1.addOrDelOnZero(se57.modify(l_orderkey,c_nationkey,shipping_l_year,shipping_supp_nation,shipping_cust_nation),(v58 * (v59 * v60)));
                            n60 = n60->nxt;
                          } while (n60 && (e60 = n60->obj) && h30 == n60->hash &&  REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey1_idxfn::equals(se58, *e60)); 
                        }
                      }
                      n59 = n59->nxt;
                    } while (n59 && (e59 = n59->obj) && h31 == n59->hash &&  REVENUELINEITEM1_T_1_mapkey1_idxfn::equals(se59, *e59)); 
                  }
                }
              n58 = n58->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUESUPPLIER1_DELTA_map_01* i61 = static_cast<HashIndex_REVENUESUPPLIER1_DELTA_map_01*>(REVENUESUPPLIER1_DELTA.index[0]);
          HashIndex_REVENUESUPPLIER1_DELTA_map_01::IdxNode* n61; 
          REVENUESUPPLIER1_DELTA_entry* e61;
        
          for (size_t i = 0; i < i61->size_; i++)
          {
            n61 = i61->buckets_ + i;
            while (n61 && (e61 = n61->obj))
            {
                long s_suppkey = e61->S_SUPPKEY;
                long s_nationkey = e61->S_NATIONKEY;
                long v61 = e61->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_T_1_map_1* i62 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_1*>(REVENUELINEITEM1_T_1.index[3]);
                  const HASH_RES_t h32 = REVENUELINEITEM1_T_1_mapkey1_idxfn::hash(se61.modify1(s_nationkey));
                  HashIndex_REVENUELINEITEM1_T_1_map_1::IdxNode* n62 = static_cast<HashIndex_REVENUELINEITEM1_T_1_map_1::IdxNode*>(i62->slice(se61, h32));
                  REVENUELINEITEM1_T_1_entry* e62;
                 
                  if (n62 && (e62 = n62->obj)) {
                    do {                
                      long c_nationkey = e62->C_NATIONKEY;
                      STRING_TYPE shipping_cust_nation = e62->SHIPPING_CUST_NATION;
                      STRING_TYPE shipping_supp_nation = e62->SHIPPING_SUPP_NATION;
                      long v62 = e62->__av;
                      REVENUECUSTOMER1LINEITEM1_P_2.addOrDelOnZero(se60.modify(s_suppkey,c_nationkey,shipping_supp_nation,shipping_cust_nation),(v61 * v62));
                      n62 = n62->nxt;
                    } while (n62 && (e62 = n62->obj) && h32 == n62->hash &&  REVENUELINEITEM1_T_1_mapkey1_idxfn::equals(se61, *e62)); 
                  }
                }
              n61 = n61->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUESUPPLIER1_DELTA_map_01* i63 = static_cast<HashIndex_REVENUESUPPLIER1_DELTA_map_01*>(REVENUESUPPLIER1_DELTA.index[0]);
          HashIndex_REVENUESUPPLIER1_DELTA_map_01::IdxNode* n63; 
          REVENUESUPPLIER1_DELTA_entry* e63;
        
          for (size_t i = 0; i < i63->size_; i++)
          {
            n63 = i63->buckets_ + i;
            while (n63 && (e63 = n63->obj))
            {
                long s_suppkey = e63->S_SUPPKEY;
                long s_nationkey = e63->S_NATIONKEY;
                long v63 = e63->__av;
                { //slice 
                  const HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_1* i64 = static_cast<HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_1*>(REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2.index[2]);
                  const HASH_RES_t h33 = REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey1_idxfn::hash(se63.modify1(s_suppkey));
                  HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_1::IdxNode* n64 = static_cast<HashIndex_REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map_1::IdxNode*>(i64->slice(se63, h33));
                  REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry* e64;
                 
                  if (n64 && (e64 = n64->obj)) {
                    do {                
                      long l_orderkey = e64->L_ORDERKEY;
                      long shipping_l_year = e64->SHIPPING_L_YEAR;
                      DOUBLE_TYPE v64 = e64->__av;
                      REVENUEORDERS1_T_3.addOrDelOnZero(se62.modify(l_orderkey,s_nationkey,shipping_l_year),(v63 * v64));
                      n64 = n64->nxt;
                    } while (n64 && (e64 = n64->obj) && h33 == n64->hash &&  REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_mapkey1_idxfn::equals(se63, *e64)); 
                  }
                }
              n63 = n63->nxt;
            }
          }
        }{  // foreach
          const HashIndex_REVENUESUPPLIER1_DELTA_map_01* i65 = static_cast<HashIndex_REVENUESUPPLIER1_DELTA_map_01*>(REVENUESUPPLIER1_DELTA.index[0]);
          HashIndex_REVENUESUPPLIER1_DELTA_map_01::IdxNode* n65; 
          REVENUESUPPLIER1_DELTA_entry* e65;
        
          for (size_t i = 0; i < i65->size_; i++)
          {
            n65 = i65->buckets_ + i;
            while (n65 && (e65 = n65->obj))
            {
                long s_suppkey = e65->S_SUPPKEY;
                long s_nationkey = e65->S_NATIONKEY;
                long v65 = e65->__av;
                REVENUELINEITEM1_T_3.addOrDelOnZero(se64.modify(s_suppkey,s_nationkey),v65);
              n65 = n65->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        REVENUELINEITEM1_T_1.clear();
        {  // foreach
          const HashIndex_NATION_map_0123* i66 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n66; 
          NATION_entry* e66;
        
          for (size_t i = 0; i < i66->size_; i++)
          {
            n66 = i66->buckets_ + i;
            while (n66 && (e66 = n66->obj))
            {
                long c_nationkey = e66->NATION_NATIONKEY;
                STRING_TYPE n2_name = e66->NATION_NAME;
                long n2_regionkey = e66->NATION_REGIONKEY;
                STRING_TYPE n2_comment = e66->NATION_COMMENT;
                long v66 = e66->__av;
                {  // foreach
                  const HashIndex_NATION_map_0123* i67 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
                  HashIndex_NATION_map_0123::IdxNode* n67; 
                  NATION_entry* e67;
                
                  for (size_t i = 0; i < i67->size_; i++)
                  {
                    n67 = i67->buckets_ + i;
                    while (n67 && (e67 = n67->obj))
                    {
                        long s_nationkey = e67->NATION_NATIONKEY;
                        STRING_TYPE n1_name = e67->NATION_NAME;
                        long n1_regionkey = e67->NATION_REGIONKEY;
                        STRING_TYPE n1_comment = e67->NATION_COMMENT;
                        long v67 = e67->__av;
                        long l3 = ((/*if */(n2_name == c3 && n1_name == c4) ? 1L : 0L) + (/*if */(n2_name == c4 && n1_name == c3) ? 1L : 0L));
                        (/*if */(l3 > 0L) ? REVENUELINEITEM1_T_1.addOrDelOnZero(se65.modify(c_nationkey,s_nationkey,n2_name,n1_name),(v66 * v67)) : (void)0);
                      n67 = n67->nxt;
                    }
                  }
                }
              n66 = n66->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    REVENUELINEITEM1_DELTA_entry se1;
    REVENUELINEITEM1_DOMAIN1_entry se2;
    REVENUE_entry se3;
    tuple3_SS_D st1;
    REVENUELINEITEM1_T_1_entry se4;
    REVENUELINEITEM1_T_3_entry se5;
    REVENUELINEITEM1_T_2_entry se6;
    REVENUELINEITEM1_DELTA_entry se7;
    REVENUECUSTOMER1_entry se8;
    REVENUECUSTOMER1LINEITEM1_P_2_entry se9;
    REVENUECUSTOMER1LINEITEM1_P_1_entry se10;
    REVENUECUSTOMER1ORDERS1_entry se11;
    REVENUECUSTOMER1LINEITEM1_P_2_entry se12;
    REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry se13;
    REVENUECUSTOMER1SUPPLIER1_P_2_entry se14;
    REVENUECUSTOMER1LINEITEM1_P_1_entry se15;
    REVENUEORDERS1_T_3_entry se16;
    REVENUELINEITEM1_T_3_entry se17;
    REVENUESUPPLIER1_entry se18;
    REVENUESUPPLIER1LINEITEM1_entry se19;
    REVENUEORDERS1_DELTA_entry se20;
    REVENUE_entry se21;
    REVENUELINEITEM1_T_1_entry se22;
    REVENUEORDERS1_T_3_entry se23;
    REVENUEORDERS1_T_2_entry se24;
    REVENUECUSTOMER1_entry se25;
    REVENUECUSTOMER1ORDERS1_entry se26;
    REVENUECUSTOMER1LINEITEM1_P_1_entry se27;
    REVENUECUSTOMER1SUPPLIER1_P_2_entry se28;
    REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry se29;
    REVENUELINEITEM1_T_2_entry se30;
    REVENUEORDERS1_T_2_entry se31;
    REVENUESUPPLIER1_entry se32;
    REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry se33;
    REVENUESUPPLIER1ORDERS1_P_1_entry se34;
    REVENUESUPPLIER1LINEITEM1_entry se35;
    REVENUESUPPLIER1ORDERS1_P_1_entry se36;
    REVENUECUSTOMER1_DELTA_entry se37;
    REVENUE_entry se38;
    REVENUECUSTOMER1_entry se39;
    REVENUEORDERS1_T_2_entry se40;
    REVENUELINEITEM1_T_2_entry se41;
    REVENUECUSTOMER1LINEITEM1_P_1_entry se42;
    REVENUESUPPLIER1_entry se43;
    REVENUECUSTOMER1SUPPLIER1_P_2_entry se44;
    REVENUELINEITEM1_T_1_entry se45;
    REVENUESUPPLIER1ORDERS1_P_1_entry se46;
    REVENUELINEITEM1_T_1_entry se47;
    REVENUESUPPLIER1LINEITEM1_entry se48;
    REVENUECUSTOMER1LINEITEM1_P_1_entry se49;
    REVENUELINEITEM1_T_1_entry se50;
    REVENUESUPPLIER1_DELTA_entry se51;
    REVENUE_entry se52;
    REVENUESUPPLIER1_entry se53;
    REVENUECUSTOMER1_entry se54;
    REVENUECUSTOMER1SUPPLIER1_P_2_entry se55;
    REVENUELINEITEM1_T_1_entry se56;
    REVENUECUSTOMER1ORDERS1_entry se57;
    REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry se58;
    REVENUELINEITEM1_T_1_entry se59;
    REVENUECUSTOMER1LINEITEM1_P_2_entry se60;
    REVENUELINEITEM1_T_1_entry se61;
    REVENUEORDERS1_T_3_entry se62;
    REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_entry se63;
    REVENUELINEITEM1_T_3_entry se64;
    REVENUELINEITEM1_T_1_entry se65;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REVENUECUSTOMER1_DELTA_map REVENUECUSTOMER1_DELTA;
    REVENUECUSTOMER1_map REVENUECUSTOMER1;
    REVENUECUSTOMER1ORDERS1_map REVENUECUSTOMER1ORDERS1;
    REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2_map REVENUECUSTOMER1ORDERS1SUPPLIER1_P_2;
    REVENUECUSTOMER1LINEITEM1_P_1_map REVENUECUSTOMER1LINEITEM1_P_1;
    REVENUECUSTOMER1LINEITEM1_P_2_map REVENUECUSTOMER1LINEITEM1_P_2;
    REVENUECUSTOMER1SUPPLIER1_P_2_map REVENUECUSTOMER1SUPPLIER1_P_2;
    REVENUEORDERS1_DELTA_map REVENUEORDERS1_DELTA;
    REVENUEORDERS1_T_2_map REVENUEORDERS1_T_2;
    REVENUEORDERS1_T_3_map REVENUEORDERS1_T_3;
    REVENUELINEITEM1_DOMAIN1_map REVENUELINEITEM1_DOMAIN1;
    REVENUELINEITEM1_DELTA_map REVENUELINEITEM1_DELTA;
    REVENUELINEITEM1_T_1_map REVENUELINEITEM1_T_1;
    REVENUELINEITEM1_T_2_map REVENUELINEITEM1_T_2;
    REVENUELINEITEM1_T_3_map REVENUELINEITEM1_T_3;
    REVENUESUPPLIER1_DELTA_map REVENUESUPPLIER1_DELTA;
    REVENUESUPPLIER1_map REVENUESUPPLIER1;
    REVENUESUPPLIER1ORDERS1_P_1_map REVENUESUPPLIER1ORDERS1_P_1;
    REVENUESUPPLIER1LINEITEM1_map REVENUESUPPLIER1LINEITEM1;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_ORDERS_map DELTA_ORDERS;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    DELTA_SUPPLIER_map DELTA_SUPPLIER;
    MultiHashMap<tuple3_SS_D,DOUBLE_TYPE,HashIndex<tuple3_SS_D,DOUBLE_TYPE> > agg1;
    /*const static*/ long c2;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c3;
  
  };

}
