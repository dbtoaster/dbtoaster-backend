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
  
  struct MKT_SHARE_entry {
    long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_entry() { /*TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_entry(const long c0, const DOUBLE_TYPE c1) { TOTAL_O_YEAR = c0; __av = c1; }
    MKT_SHARE_entry(const MKT_SHARE_entry& other) : TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_entry& modify(const long c0) { TOTAL_O_YEAR = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_entry& x, const MKT_SHARE_entry& y) {
      return x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_entry,DOUBLE_TYPE,MKT_SHARE_mapkey0_idxfn,true>
  > MKT_SHARE_map;
  typedef HashIndex<MKT_SHARE_entry,DOUBLE_TYPE,MKT_SHARE_mapkey0_idxfn,true> HashIndex_MKT_SHARE_map_0;
  
  struct MKT_SHAREORDERS1_DOMAIN1_entry {
    long TOTAL_O_YEAR; long __av; 
    explicit MKT_SHAREORDERS1_DOMAIN1_entry() { /*TOTAL_O_YEAR = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1_DOMAIN1_entry(const long c0, const long c1) { TOTAL_O_YEAR = c0; __av = c1; }
    MKT_SHAREORDERS1_DOMAIN1_entry(const MKT_SHAREORDERS1_DOMAIN1_entry& other) : TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_DOMAIN1_entry& modify(const long c0) { TOTAL_O_YEAR = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_DOMAIN1_entry& x, const MKT_SHAREORDERS1_DOMAIN1_entry& y) {
      return x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_DOMAIN1_entry,long,
    HashIndex<MKT_SHAREORDERS1_DOMAIN1_entry,long,MKT_SHAREORDERS1_DOMAIN1_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1_DOMAIN1_map;
  typedef HashIndex<MKT_SHAREORDERS1_DOMAIN1_entry,long,MKT_SHAREORDERS1_DOMAIN1_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1_DOMAIN1_map_0;
  
  struct MKT_SHAREORDERS1_entry {
    long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1_entry() { /*TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1_entry(const long c0, const DOUBLE_TYPE c1) { TOTAL_O_YEAR = c0; __av = c1; }
    MKT_SHAREORDERS1_entry(const MKT_SHAREORDERS1_entry& other) : TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_entry& modify(const long c0) { TOTAL_O_YEAR = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_entry& x, const MKT_SHAREORDERS1_entry& y) {
      return x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1_map;
  typedef HashIndex<MKT_SHAREORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1_map_0;
  
  struct MKT_SHAREORDERS1CUSTOMER1_DELTA_entry {
    long O_CUSTKEY; long C_NATIONKEY; long __av; 
    explicit MKT_SHAREORDERS1CUSTOMER1_DELTA_entry() { /*O_CUSTKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1CUSTOMER1_DELTA_entry(const long c0, const long c1, const long c2) { O_CUSTKEY = c0; C_NATIONKEY = c1; __av = c2; }
    MKT_SHAREORDERS1CUSTOMER1_DELTA_entry(const MKT_SHAREORDERS1CUSTOMER1_DELTA_entry& other) : O_CUSTKEY( other.O_CUSTKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_DELTA_entry& modify(const long c0, const long c1) { O_CUSTKEY = c0; C_NATIONKEY = c1;  return *this; }
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
  struct MKT_SHAREORDERS1CUSTOMER1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_DELTA_entry& x, const MKT_SHAREORDERS1CUSTOMER1_DELTA_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1CUSTOMER1_DELTA_entry,long,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_DELTA_entry,long,MKT_SHAREORDERS1CUSTOMER1_DELTA_mapkey01_idxfn,true>
  > MKT_SHAREORDERS1CUSTOMER1_DELTA_map;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_DELTA_entry,long,MKT_SHAREORDERS1CUSTOMER1_DELTA_mapkey01_idxfn,true> HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01;
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1_entry {
    long O_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1_entry() { /*O_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { O_CUSTKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHAREORDERS1CUSTOMER1_P_1_entry(const MKT_SHAREORDERS1CUSTOMER1_P_1_entry& other) : O_CUSTKEY( other.O_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1_entry& modify(const long c0, const long c1) { O_CUSTKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1_entry& modify0(const long c0) { O_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1CUSTOMER1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1CUSTOMER1_P_1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1_mapkey0_idxfn,false>
  > MKT_SHAREORDERS1CUSTOMER1_P_1_map;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1_mapkey01_idxfn,true> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1_map_01;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1_map_0;
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry {
    long L_ORDERKEY; long O_CUSTKEY; long TOTAL_O_YEAR; long __av; 
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry() { /*L_ORDERKEY = 0L; O_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry(const long c0, const long c1, const long c2, const long c3) { L_ORDERKEY = c0; O_CUSTKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry(const MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), O_CUSTKEY( other.O_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; O_CUSTKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& modify1(const long c1) { O_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.O_CUSTKEY == y.O_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry,long,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry,long,MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry,long,MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry,long,MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey1_idxfn,false>
  > MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry,long,MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey012_idxfn,true> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_012;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry,long,MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry,long,MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_1;
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry {
    long S_SUPPKEY; long O_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry() { /*S_SUPPKEY = 0L; O_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { S_SUPPKEY = c0; O_CUSTKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), O_CUSTKEY( other.O_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& modify(const long c0, const long c1, const long c2) { S_SUPPKEY = c0; O_CUSTKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& modify1(const long c1) { O_CUSTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& modify0(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.O_CUSTKEY == y.O_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey1_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey0_idxfn,false>
  > MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey012_idxfn,true> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_012;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_1;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_0;
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry {
    long L_ORDERKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry() { /*L_ORDERKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { L_ORDERKEY = c0; S_SUPPKEY = c1; __av = c2; }
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& modify(const long c0, const long c1) { L_ORDERKEY = c0; S_SUPPKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey1_idxfn,false>
  > MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey01_idxfn,true> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_01;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_1;
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry {
    long L_ORDERKEY; long P_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry() { /*L_ORDERKEY = 0L; P_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2; __av = c3; }
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& modify1(const long c1) { P_PARTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& modify2(const long c2) { S_SUPPKEY = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey1_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey2_idxfn,false>
  > MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey012_idxfn,true> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_012;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_1;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey2_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_2;
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry {
    long P_PARTKEY; long S_SUPPKEY; long O_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; O_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { P_PARTKEY = c0; S_SUPPKEY = c1; O_CUSTKEY = c2; TOTAL_O_YEAR = c3; __av = c4; }
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), O_CUSTKEY( other.O_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& modify(const long c0, const long c1, const long c2, const long c3) { P_PARTKEY = c0; S_SUPPKEY = c1; O_CUSTKEY = c2; TOTAL_O_YEAR = c3;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& modify2(const long c2) { O_CUSTKEY = c2;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.O_CUSTKEY == y.O_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey0123_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey2_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey1_idxfn,false>
  > MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey0123_idxfn,true> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_0123;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_0;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey2_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_2;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_1;
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry {
    long P_PARTKEY; long O_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry() { /*P_PARTKEY = 0L; O_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { P_PARTKEY = c0; O_CUSTKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), O_CUSTKEY( other.O_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& modify(const long c0, const long c1, const long c2) { P_PARTKEY = c0; O_CUSTKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& modify1(const long c1) { O_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.O_CUSTKEY == y.O_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey1_idxfn,false>
  > MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey012_idxfn,true> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map_012;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map_0;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map_1;
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry {
    long L_ORDERKEY; long P_PARTKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry() { /*L_ORDERKEY = 0L; P_PARTKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { L_ORDERKEY = c0; P_PARTKEY = c1; __av = c2; }
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& modify(const long c0, const long c1) { L_ORDERKEY = c0; P_PARTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& modify1(const long c1) { P_PARTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey1_idxfn,false>
  > MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey01_idxfn,true> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_01;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_1;
  
  struct MKT_SHAREORDERS1CUSTOMER1_P_2_entry {
    long C_NATIONKEY; long __av; 
    explicit MKT_SHAREORDERS1CUSTOMER1_P_2_entry() { /*C_NATIONKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1CUSTOMER1_P_2_entry(const long c0, const long c1) { C_NATIONKEY = c0; __av = c1; }
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry(const MKT_SHAREORDERS1CUSTOMER1_P_2_entry& other) : C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1CUSTOMER1_P_2_entry& modify(const long c0) { C_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1CUSTOMER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1CUSTOMER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1CUSTOMER1_P_2_entry& x, const MKT_SHAREORDERS1CUSTOMER1_P_2_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1CUSTOMER1_P_2_entry,long,
    HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_2_entry,long,MKT_SHAREORDERS1CUSTOMER1_P_2_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1CUSTOMER1_P_2_map;
  typedef HashIndex<MKT_SHAREORDERS1CUSTOMER1_P_2_entry,long,MKT_SHAREORDERS1CUSTOMER1_P_2_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_2_map_0;
  
  struct MKT_SHAREORDERS1LINEITEM1_DELTA_entry {
    long L_ORDERKEY; long P_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1LINEITEM1_DELTA_entry() { /*L_ORDERKEY = 0L; P_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1LINEITEM1_DELTA_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2; __av = c3; }
    MKT_SHAREORDERS1LINEITEM1_DELTA_entry(const MKT_SHAREORDERS1LINEITEM1_DELTA_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1LINEITEM1_DELTA_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1LINEITEM1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1LINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1LINEITEM1_DELTA_entry& x, const MKT_SHAREORDERS1LINEITEM1_DELTA_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1LINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1LINEITEM1_DELTA_entry,DOUBLE_TYPE,MKT_SHAREORDERS1LINEITEM1_DELTA_mapkey012_idxfn,true>
  > MKT_SHAREORDERS1LINEITEM1_DELTA_map;
  typedef HashIndex<MKT_SHAREORDERS1LINEITEM1_DELTA_entry,DOUBLE_TYPE,MKT_SHAREORDERS1LINEITEM1_DELTA_mapkey012_idxfn,true> HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012;
  
  struct MKT_SHAREORDERS1LINEITEM1_P_1_entry {
    long P_PARTKEY; long __av; 
    explicit MKT_SHAREORDERS1LINEITEM1_P_1_entry() { /*P_PARTKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1LINEITEM1_P_1_entry(const long c0, const long c1) { P_PARTKEY = c0; __av = c1; }
    MKT_SHAREORDERS1LINEITEM1_P_1_entry(const MKT_SHAREORDERS1LINEITEM1_P_1_entry& other) : P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1LINEITEM1_P_1_entry& modify(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1LINEITEM1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1LINEITEM1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1LINEITEM1_P_1_entry& x, const MKT_SHAREORDERS1LINEITEM1_P_1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1LINEITEM1_P_1_entry,long,
    HashIndex<MKT_SHAREORDERS1LINEITEM1_P_1_entry,long,MKT_SHAREORDERS1LINEITEM1_P_1_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1LINEITEM1_P_1_map;
  typedef HashIndex<MKT_SHAREORDERS1LINEITEM1_P_1_entry,long,MKT_SHAREORDERS1LINEITEM1_P_1_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1LINEITEM1_P_1_map_0;
  
  struct MKT_SHAREORDERS1LINEITEM1_P_2_entry {
    long L_ORDERKEY; long TOTAL_O_YEAR; long __av; 
    explicit MKT_SHAREORDERS1LINEITEM1_P_2_entry() { /*L_ORDERKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1LINEITEM1_P_2_entry(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHAREORDERS1LINEITEM1_P_2_entry(const MKT_SHAREORDERS1LINEITEM1_P_2_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1LINEITEM1_P_2_entry& modify(const long c0, const long c1) { L_ORDERKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1LINEITEM1_P_2_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1LINEITEM1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1LINEITEM1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1LINEITEM1_P_2_entry& x, const MKT_SHAREORDERS1LINEITEM1_P_2_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1LINEITEM1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1LINEITEM1_P_2_entry& x, const MKT_SHAREORDERS1LINEITEM1_P_2_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1LINEITEM1_P_2_entry,long,
    HashIndex<MKT_SHAREORDERS1LINEITEM1_P_2_entry,long,MKT_SHAREORDERS1LINEITEM1_P_2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1LINEITEM1_P_2_entry,long,MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn,false>
  > MKT_SHAREORDERS1LINEITEM1_P_2_map;
  typedef HashIndex<MKT_SHAREORDERS1LINEITEM1_P_2_entry,long,MKT_SHAREORDERS1LINEITEM1_P_2_mapkey01_idxfn,true> HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_01;
  typedef HashIndex<MKT_SHAREORDERS1LINEITEM1_P_2_entry,long,MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0;
  
  struct MKT_SHAREORDERS1LINEITEM1_P_3_entry {
    long S_SUPPKEY; long __av; 
    explicit MKT_SHAREORDERS1LINEITEM1_P_3_entry() { /*S_SUPPKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1LINEITEM1_P_3_entry(const long c0, const long c1) { S_SUPPKEY = c0; __av = c1; }
    MKT_SHAREORDERS1LINEITEM1_P_3_entry(const MKT_SHAREORDERS1LINEITEM1_P_3_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1LINEITEM1_P_3_entry& modify(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1LINEITEM1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1LINEITEM1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1LINEITEM1_P_3_entry& x, const MKT_SHAREORDERS1LINEITEM1_P_3_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1LINEITEM1_P_3_entry,long,
    HashIndex<MKT_SHAREORDERS1LINEITEM1_P_3_entry,long,MKT_SHAREORDERS1LINEITEM1_P_3_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1LINEITEM1_P_3_map;
  typedef HashIndex<MKT_SHAREORDERS1LINEITEM1_P_3_entry,long,MKT_SHAREORDERS1LINEITEM1_P_3_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1LINEITEM1_P_3_map_0;
  
  struct MKT_SHAREORDERS1SUPPLIER1_DELTA_entry {
    long S_SUPPKEY; long S_NATIONKEY; long __av; 
    explicit MKT_SHAREORDERS1SUPPLIER1_DELTA_entry() { /*S_SUPPKEY = 0L; S_NATIONKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1SUPPLIER1_DELTA_entry(const long c0, const long c1, const long c2) { S_SUPPKEY = c0; S_NATIONKEY = c1; __av = c2; }
    MKT_SHAREORDERS1SUPPLIER1_DELTA_entry(const MKT_SHAREORDERS1SUPPLIER1_DELTA_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1SUPPLIER1_DELTA_entry& modify(const long c0, const long c1) { S_SUPPKEY = c0; S_NATIONKEY = c1;  return *this; }
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
  struct MKT_SHAREORDERS1SUPPLIER1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1SUPPLIER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1SUPPLIER1_DELTA_entry& x, const MKT_SHAREORDERS1SUPPLIER1_DELTA_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1SUPPLIER1_DELTA_entry,long,
    HashIndex<MKT_SHAREORDERS1SUPPLIER1_DELTA_entry,long,MKT_SHAREORDERS1SUPPLIER1_DELTA_mapkey01_idxfn,true>
  > MKT_SHAREORDERS1SUPPLIER1_DELTA_map;
  typedef HashIndex<MKT_SHAREORDERS1SUPPLIER1_DELTA_entry,long,MKT_SHAREORDERS1SUPPLIER1_DELTA_mapkey01_idxfn,true> HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01;
  
  struct MKT_SHAREORDERS1SUPPLIER1_P_1_entry {
    long S_SUPPKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1SUPPLIER1_P_1_entry() { /*S_SUPPKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1SUPPLIER1_P_1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { S_SUPPKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHAREORDERS1SUPPLIER1_P_1_entry(const MKT_SHAREORDERS1SUPPLIER1_P_1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1SUPPLIER1_P_1_entry& modify(const long c0, const long c1) { S_SUPPKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1SUPPLIER1_P_1_entry& modify0(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1SUPPLIER1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1SUPPLIER1_P_1_entry& x, const MKT_SHAREORDERS1SUPPLIER1_P_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREORDERS1SUPPLIER1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1SUPPLIER1_P_1_entry& x, const MKT_SHAREORDERS1SUPPLIER1_P_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1SUPPLIER1_P_1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1SUPPLIER1_P_1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1SUPPLIER1_P_1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1SUPPLIER1_P_1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1SUPPLIER1_P_1_mapkey0_idxfn,false>
  > MKT_SHAREORDERS1SUPPLIER1_P_1_map;
  typedef HashIndex<MKT_SHAREORDERS1SUPPLIER1_P_1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1SUPPLIER1_P_1_mapkey01_idxfn,true> HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1_map_01;
  typedef HashIndex<MKT_SHAREORDERS1SUPPLIER1_P_1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1SUPPLIER1_P_1_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1_map_0;
  
  struct MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry {
    long P_PARTKEY; long S_SUPPKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { P_PARTKEY = c0; S_SUPPKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry(const MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& modify(const long c0, const long c1, const long c2) { P_PARTKEY = c0; S_SUPPKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& x, const MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& x, const MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& x, const MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey1_idxfn,false>
  > MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map;
  typedef HashIndex<MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey012_idxfn,true> HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_012;
  typedef HashIndex<MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_0;
  typedef HashIndex<MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_1;
  
  struct MKT_SHAREORDERS1SUPPLIER1_P_2_entry {
    long S_NATIONKEY; long __av; 
    explicit MKT_SHAREORDERS1SUPPLIER1_P_2_entry() { /*S_NATIONKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1SUPPLIER1_P_2_entry(const long c0, const long c1) { S_NATIONKEY = c0; __av = c1; }
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry(const MKT_SHAREORDERS1SUPPLIER1_P_2_entry& other) : S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1SUPPLIER1_P_2_entry& modify(const long c0) { S_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1SUPPLIER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1SUPPLIER1_P_2_entry& x, const MKT_SHAREORDERS1SUPPLIER1_P_2_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1SUPPLIER1_P_2_entry,long,
    HashIndex<MKT_SHAREORDERS1SUPPLIER1_P_2_entry,long,MKT_SHAREORDERS1SUPPLIER1_P_2_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1SUPPLIER1_P_2_map;
  typedef HashIndex<MKT_SHAREORDERS1SUPPLIER1_P_2_entry,long,MKT_SHAREORDERS1SUPPLIER1_P_2_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_2_map_0;
  
  struct MKT_SHAREORDERS1PART1_DELTA_entry {
    long P_PARTKEY; long __av; 
    explicit MKT_SHAREORDERS1PART1_DELTA_entry() { /*P_PARTKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1PART1_DELTA_entry(const long c0, const long c1) { P_PARTKEY = c0; __av = c1; }
    MKT_SHAREORDERS1PART1_DELTA_entry(const MKT_SHAREORDERS1PART1_DELTA_entry& other) : P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1PART1_DELTA_entry& modify(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1PART1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1PART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1PART1_DELTA_entry& x, const MKT_SHAREORDERS1PART1_DELTA_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1PART1_DELTA_entry,long,
    HashIndex<MKT_SHAREORDERS1PART1_DELTA_entry,long,MKT_SHAREORDERS1PART1_DELTA_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1PART1_DELTA_map;
  typedef HashIndex<MKT_SHAREORDERS1PART1_DELTA_entry,long,MKT_SHAREORDERS1PART1_DELTA_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0;
  
  struct MKT_SHAREORDERS1PART1_entry {
    long P_PARTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1PART1_entry() { /*P_PARTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1PART1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { P_PARTKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHAREORDERS1PART1_entry(const MKT_SHAREORDERS1PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1PART1_entry& modify(const long c0, const long c1) { P_PARTKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1PART1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1PART1_entry& x, const MKT_SHAREORDERS1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREORDERS1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1PART1_entry& x, const MKT_SHAREORDERS1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1PART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1PART1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1PART1_mapkey0_idxfn,false>
  > MKT_SHAREORDERS1PART1_map;
  typedef HashIndex<MKT_SHAREORDERS1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1PART1_mapkey01_idxfn,true> HashIndex_MKT_SHAREORDERS1PART1_map_01;
  typedef HashIndex<MKT_SHAREORDERS1PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1PART1_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1PART1_map_0;
  
  struct MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry {
    long L_ORDERKEY; long O_CUSTKEY; long TOTAL_O_YEAR; long __av; 
    explicit MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry() { /*L_ORDERKEY = 0L; O_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry(const long c0, const long c1, const long c2, const long c3) { L_ORDERKEY = c0; O_CUSTKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry(const MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), O_CUSTKEY( other.O_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; O_CUSTKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry& modify2(const long c2) { TOTAL_O_YEAR = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L1_1_L1_2_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry& x, const MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.O_CUSTKEY == y.O_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREORDERS1_L1_1_L1_2_DELTA_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry& x, const MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry& y) {
      return x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry,long,
    HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry,long,MKT_SHAREORDERS1_L1_1_L1_2_DELTA_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry,long,MKT_SHAREORDERS1_L1_1_L1_2_DELTA_mapkey2_idxfn,false>
  > MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map;
  typedef HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry,long,MKT_SHAREORDERS1_L1_1_L1_2_DELTA_mapkey012_idxfn,true> HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012;
  typedef HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry,long,MKT_SHAREORDERS1_L1_1_L1_2_DELTA_mapkey2_idxfn,false> HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_2;
  
  struct MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry {
    long O_CUSTKEY; long __av; 
    explicit MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry() { /*O_CUSTKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry(const long c0, const long c1) { O_CUSTKEY = c0; __av = c1; }
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry(const MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry& other) : O_CUSTKEY( other.O_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry& modify(const long c0) { O_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L1_1_L1_2_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry& x, const MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry,long,
    HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry,long,MKT_SHAREORDERS1_L1_1_L1_2_P_1_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1_L1_1_L1_2_P_1_map;
  typedef HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry,long,MKT_SHAREORDERS1_L1_1_L1_2_P_1_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_1_map_0;
  
  struct MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry {
    long L_ORDERKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry() { /*L_ORDERKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry(const long c0, const DOUBLE_TYPE c1) { L_ORDERKEY = c0; __av = c1; }
    MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry(const MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry& modify(const long c0) { L_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L1_1_L1_2_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry& x, const MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L1_1_L1_2_P_2_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1_L1_1_L1_2_P_2_map;
  typedef HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L1_1_L1_2_P_2_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2_map_0;
  
  struct MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry {
    long S_SUPPKEY; long __av; 
    explicit MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry() { /*S_SUPPKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry(const long c0, const long c1) { S_SUPPKEY = c0; __av = c1; }
    MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry(const MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry& modify(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry& x, const MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry,long,
    HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry,long,MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_map;
  typedef HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry,long,MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_map_0;
  
  struct MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry {
    long S_NATIONKEY; long __av; 
    explicit MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry() { /*S_NATIONKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry(const long c0, const long c1) { S_NATIONKEY = c0; __av = c1; }
    MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry(const MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry& other) : S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry& modify(const long c0) { S_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry& x, const MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry,long,
    HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry,long,MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_map;
  typedef HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry,long,MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_map_0;
  
  struct MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry {
    long L_ORDERKEY; long P_PARTKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry() { /*L_ORDERKEY = 0L; P_PARTKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { L_ORDERKEY = c0; P_PARTKEY = c1; __av = c2; }
    MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry(const MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& modify(const long c0, const long c1) { L_ORDERKEY = c0; P_PARTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& modify1(const long c1) { P_PARTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& x, const MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& x, const MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& x, const MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey1_idxfn,false>
  > MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map;
  typedef HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey01_idxfn,true> HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_01;
  typedef HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_0;
  typedef HashIndex<MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_1;
  
  struct MKT_SHAREORDERS4_DELTA_entry {
    long L_ORDERKEY; long O_CUSTKEY; date O_ORDERDATE; long __av; 
    explicit MKT_SHAREORDERS4_DELTA_entry() { /*L_ORDERKEY = 0L; O_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit MKT_SHAREORDERS4_DELTA_entry(const long c0, const long c1, const date c2, const long c3) { L_ORDERKEY = c0; O_CUSTKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHAREORDERS4_DELTA_entry(const MKT_SHAREORDERS4_DELTA_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), O_CUSTKEY( other.O_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS4_DELTA_entry& modify(const long c0, const long c1, const date c2) { L_ORDERKEY = c0; O_CUSTKEY = c1; O_ORDERDATE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS4_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS4_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS4_DELTA_entry& x, const MKT_SHAREORDERS4_DELTA_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.O_CUSTKEY == y.O_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS4_DELTA_entry,long,
    HashIndex<MKT_SHAREORDERS4_DELTA_entry,long,MKT_SHAREORDERS4_DELTA_mapkey012_idxfn,true>
  > MKT_SHAREORDERS4_DELTA_map;
  typedef HashIndex<MKT_SHAREORDERS4_DELTA_entry,long,MKT_SHAREORDERS4_DELTA_mapkey012_idxfn,true> HashIndex_MKT_SHAREORDERS4_DELTA_map_012;
  
  struct MKT_SHAREORDERS4_P_1_entry {
    long L_ORDERKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS4_P_1_entry() { /*L_ORDERKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS4_P_1_entry(const long c0, const DOUBLE_TYPE c1) { L_ORDERKEY = c0; __av = c1; }
    MKT_SHAREORDERS4_P_1_entry(const MKT_SHAREORDERS4_P_1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS4_P_1_entry& modify(const long c0) { L_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS4_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS4_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS4_P_1_entry& x, const MKT_SHAREORDERS4_P_1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS4_P_1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS4_P_1_entry,DOUBLE_TYPE,MKT_SHAREORDERS4_P_1_mapkey0_idxfn,true>
  > MKT_SHAREORDERS4_P_1_map;
  typedef HashIndex<MKT_SHAREORDERS4_P_1_entry,DOUBLE_TYPE,MKT_SHAREORDERS4_P_1_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS4_P_1_map_0;
  
  struct MKT_SHAREPART1_entry {
    date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1_entry() { /*O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1_entry(const date c0, const DOUBLE_TYPE c1) { O_ORDERDATE = c0; __av = c1; }
    MKT_SHAREPART1_entry(const MKT_SHAREPART1_entry& other) : O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_entry& modify(const date c0) { O_ORDERDATE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_entry& x, const MKT_SHAREPART1_entry& y) {
      return x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1_entry,DOUBLE_TYPE,MKT_SHAREPART1_mapkey0_idxfn,true>
  > MKT_SHAREPART1_map;
  typedef HashIndex<MKT_SHAREPART1_entry,DOUBLE_TYPE,MKT_SHAREPART1_mapkey0_idxfn,true> HashIndex_MKT_SHAREPART1_map_0;
  
  struct MKT_SHAREPART1CUSTOMER1_P_2_entry {
    long O_CUSTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1CUSTOMER1_P_2_entry() { /*O_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1CUSTOMER1_P_2_entry(const long c0, const date c1, const DOUBLE_TYPE c2) { O_CUSTKEY = c0; O_ORDERDATE = c1; __av = c2; }
    MKT_SHAREPART1CUSTOMER1_P_2_entry(const MKT_SHAREPART1CUSTOMER1_P_2_entry& other) : O_CUSTKEY( other.O_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2_entry& modify(const long c0, const date c1) { O_CUSTKEY = c0; O_ORDERDATE = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2_entry& modify0(const long c0) { O_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1CUSTOMER1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1CUSTOMER1_P_2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2_mapkey0_idxfn,false>
  > MKT_SHAREPART1CUSTOMER1_P_2_map;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2_map_01;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2_map_0;
  
  struct MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry {
    long L_ORDERKEY; long O_CUSTKEY; date O_ORDERDATE; long __av; 
    explicit MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry() { /*L_ORDERKEY = 0L; O_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry(const long c0, const long c1, const date c2, const long c3) { L_ORDERKEY = c0; O_CUSTKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry(const MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), O_CUSTKEY( other.O_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& modify(const long c0, const long c1, const date c2) { L_ORDERKEY = c0; O_CUSTKEY = c1; O_ORDERDATE = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& modify1(const long c1) { O_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.O_CUSTKEY == y.O_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry,long,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry,long,MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry,long,MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry,long,MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey1_idxfn,false>
  > MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry,long,MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_012;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry,long,MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry,long,MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_1;
  
  struct MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry {
    long S_SUPPKEY; long O_CUSTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry() { /*S_SUPPKEY = 0L; O_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry(const long c0, const long c1, const date c2, const DOUBLE_TYPE c3) { S_SUPPKEY = c0; O_CUSTKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), O_CUSTKEY( other.O_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& modify(const long c0, const long c1, const date c2) { S_SUPPKEY = c0; O_CUSTKEY = c1; O_ORDERDATE = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& modify1(const long c1) { O_CUSTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& modify0(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.O_CUSTKEY == y.O_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey1_idxfn,false>,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey0_idxfn,false>
  > MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map_012;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map_1;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map_0;
  
  struct MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry {
    long P_PARTKEY; long S_SUPPKEY; long O_CUSTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; O_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry(const long c0, const long c1, const long c2, const date c3, const DOUBLE_TYPE c4) { P_PARTKEY = c0; S_SUPPKEY = c1; O_CUSTKEY = c2; O_ORDERDATE = c3; __av = c4; }
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), O_CUSTKEY( other.O_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& modify(const long c0, const long c1, const long c2, const date c3) { P_PARTKEY = c0; S_SUPPKEY = c1; O_CUSTKEY = c2; O_ORDERDATE = c3;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& modify2(const long c2) { O_CUSTKEY = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.O_CUSTKEY == y.O_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey0123_idxfn,true>,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey2_idxfn,false>,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey1_idxfn,false>
  > MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey0123_idxfn,true> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_0123;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_0;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey2_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_2;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_1;
  
  struct MKT_SHAREPART1CUSTOMER1_P_2PART1_entry {
    long P_PARTKEY; long O_CUSTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1CUSTOMER1_P_2PART1_entry() { /*P_PARTKEY = 0L; O_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1CUSTOMER1_P_2PART1_entry(const long c0, const long c1, const date c2, const DOUBLE_TYPE c3) { P_PARTKEY = c0; O_CUSTKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHAREPART1CUSTOMER1_P_2PART1_entry(const MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), O_CUSTKEY( other.O_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& modify(const long c0, const long c1, const date c2) { P_PARTKEY = c0; O_CUSTKEY = c1; O_ORDERDATE = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& modify1(const long c1) { O_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.O_CUSTKEY == y.O_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& x, const MKT_SHAREPART1CUSTOMER1_P_2PART1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey1_idxfn,false>
  > MKT_SHAREPART1CUSTOMER1_P_2PART1_map;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2PART1_map_012;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2PART1_map_0;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER1_P_2PART1_map_1;
  
  struct MKT_SHAREPART1LINEITEM1_P_1_entry {
    long L_ORDERKEY; date O_ORDERDATE; long __av; 
    explicit MKT_SHAREPART1LINEITEM1_P_1_entry() { /*L_ORDERKEY = 0L; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit MKT_SHAREPART1LINEITEM1_P_1_entry(const long c0, const date c1, const long c2) { L_ORDERKEY = c0; O_ORDERDATE = c1; __av = c2; }
    MKT_SHAREPART1LINEITEM1_P_1_entry(const MKT_SHAREPART1LINEITEM1_P_1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1LINEITEM1_P_1_entry& modify(const long c0, const date c1) { L_ORDERKEY = c0; O_ORDERDATE = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1LINEITEM1_P_1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1LINEITEM1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1LINEITEM1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1LINEITEM1_P_1_entry& x, const MKT_SHAREPART1LINEITEM1_P_1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1LINEITEM1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1LINEITEM1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1LINEITEM1_P_1_entry& x, const MKT_SHAREPART1LINEITEM1_P_1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1LINEITEM1_P_1_entry,long,
    HashIndex<MKT_SHAREPART1LINEITEM1_P_1_entry,long,MKT_SHAREPART1LINEITEM1_P_1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1LINEITEM1_P_1_entry,long,MKT_SHAREPART1LINEITEM1_P_1_mapkey0_idxfn,false>
  > MKT_SHAREPART1LINEITEM1_P_1_map;
  typedef HashIndex<MKT_SHAREPART1LINEITEM1_P_1_entry,long,MKT_SHAREPART1LINEITEM1_P_1_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_01;
  typedef HashIndex<MKT_SHAREPART1LINEITEM1_P_1_entry,long,MKT_SHAREPART1LINEITEM1_P_1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0;
  
  struct MKT_SHAREPART1SUPPLIER1_P_1_entry {
    long S_SUPPKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1SUPPLIER1_P_1_entry() { /*S_SUPPKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1SUPPLIER1_P_1_entry(const long c0, const date c1, const DOUBLE_TYPE c2) { S_SUPPKEY = c0; O_ORDERDATE = c1; __av = c2; }
    MKT_SHAREPART1SUPPLIER1_P_1_entry(const MKT_SHAREPART1SUPPLIER1_P_1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1SUPPLIER1_P_1_entry& modify(const long c0, const date c1) { S_SUPPKEY = c0; O_ORDERDATE = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1SUPPLIER1_P_1_entry& modify0(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1SUPPLIER1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1SUPPLIER1_P_1_entry& x, const MKT_SHAREPART1SUPPLIER1_P_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1SUPPLIER1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1SUPPLIER1_P_1_entry& x, const MKT_SHAREPART1SUPPLIER1_P_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1SUPPLIER1_P_1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1SUPPLIER1_P_1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_P_1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1SUPPLIER1_P_1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_P_1_mapkey0_idxfn,false>
  > MKT_SHAREPART1SUPPLIER1_P_1_map;
  typedef HashIndex<MKT_SHAREPART1SUPPLIER1_P_1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_P_1_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1SUPPLIER1_P_1_map_01;
  typedef HashIndex<MKT_SHAREPART1SUPPLIER1_P_1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_P_1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1SUPPLIER1_P_1_map_0;
  
  struct MKT_SHAREPART1SUPPLIER1_P_1PART1_entry {
    long P_PARTKEY; long S_SUPPKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1SUPPLIER1_P_1PART1_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1SUPPLIER1_P_1PART1_entry(const long c0, const long c1, const date c2, const DOUBLE_TYPE c3) { P_PARTKEY = c0; S_SUPPKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHAREPART1SUPPLIER1_P_1PART1_entry(const MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& modify(const long c0, const long c1, const date c2) { P_PARTKEY = c0; S_SUPPKEY = c1; O_ORDERDATE = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& x, const MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& x, const MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& x, const MKT_SHAREPART1SUPPLIER1_P_1PART1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey1_idxfn,false>
  > MKT_SHAREPART1SUPPLIER1_P_1PART1_map;
  typedef HashIndex<MKT_SHAREPART1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1SUPPLIER1_P_1PART1_map_012;
  typedef HashIndex<MKT_SHAREPART1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1SUPPLIER1_P_1PART1_map_0;
  typedef HashIndex<MKT_SHAREPART1SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1SUPPLIER1_P_1PART1_map_1;
  
  struct MKT_SHAREPART1PART1_entry {
    long P_PARTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1PART1_entry() { /*P_PARTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1PART1_entry(const long c0, const date c1, const DOUBLE_TYPE c2) { P_PARTKEY = c0; O_ORDERDATE = c1; __av = c2; }
    MKT_SHAREPART1PART1_entry(const MKT_SHAREPART1PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1PART1_entry& modify(const long c0, const date c1) { P_PARTKEY = c0; O_ORDERDATE = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1PART1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1PART1_entry& x, const MKT_SHAREPART1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1PART1_entry& x, const MKT_SHAREPART1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1PART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1PART1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1PART1_mapkey0_idxfn,false>
  > MKT_SHAREPART1PART1_map;
  typedef HashIndex<MKT_SHAREPART1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1PART1_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1PART1_map_01;
  typedef HashIndex<MKT_SHAREPART1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1PART1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1PART1_map_0;
  
  struct MKT_SHAREPART1_L2_1_L1_1_entry {
    long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1_entry() { /*TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1_entry(const long c0, const DOUBLE_TYPE c1) { TOTAL_O_YEAR = c0; __av = c1; }
    MKT_SHAREPART1_L2_1_L1_1_entry(const MKT_SHAREPART1_L2_1_L1_1_entry& other) : TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1_entry& modify(const long c0) { TOTAL_O_YEAR = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1_entry& x, const MKT_SHAREPART1_L2_1_L1_1_entry& y) {
      return x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1_mapkey0_idxfn,true>
  > MKT_SHAREPART1_L2_1_L1_1_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1_mapkey0_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1_map_0;
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry {
    long O_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry() { /*O_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { O_CUSTKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry& other) : O_CUSTKEY( other.O_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry& modify(const long c0, const long c1) { O_CUSTKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry& modify0(const long c0) { O_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_mapkey0_idxfn,false>
  > MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_map_01;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_map_0;
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry {
    long P_PARTKEY; long O_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry() { /*P_PARTKEY = 0L; O_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { P_PARTKEY = c0; O_CUSTKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), O_CUSTKEY( other.O_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& modify(const long c0, const long c1, const long c2) { P_PARTKEY = c0; O_CUSTKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& modify1(const long c1) { O_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.O_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.O_CUSTKEY == y.O_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry& y) {
      return x.O_CUSTKEY == y.O_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey1_idxfn,false>
  > MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map_012;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map_0;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map_1;
  
  struct MKT_SHAREPART1_L2_1_L1_1PART1_entry {
    long P_PARTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1PART1_entry() { /*P_PARTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1PART1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { P_PARTKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHAREPART1_L2_1_L1_1PART1_entry(const MKT_SHAREPART1_L2_1_L1_1PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1PART1_entry& modify(const long c0, const long c1) { P_PARTKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1PART1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1PART1_entry& x, const MKT_SHAREPART1_L2_1_L1_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1PART1_entry& x, const MKT_SHAREPART1_L2_1_L1_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1PART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1PART1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1PART1_mapkey0_idxfn,false>
  > MKT_SHAREPART1_L2_1_L1_1PART1_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1PART1_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1PART1_map_01;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1PART1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1PART1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1PART1_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const MKT_SHARE_map& _MKT_SHARE = get_MKT_SHARE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(MKT_SHARE), _MKT_SHARE, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const MKT_SHARE_map& get_MKT_SHARE() const {
      return MKT_SHARE;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    MKT_SHARE_map MKT_SHARE;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c2 = Udate(STRING_TYPE("1996-12-31"));
      c3 = STRING_TYPE("ECONOMY ANODIZED STEEL");
      c4 = STRING_TYPE("AMERICA");
      c1 = Udate(STRING_TYPE("1995-1-1"));
      c5 = STRING_TYPE("BRAZIL");
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

        MKT_SHAREORDERS1LINEITEM1_DELTA.clear();
        {  

          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                long l_orderkey = DELTA_LINEITEM.orderkey[i];
                long p_partkey = DELTA_LINEITEM.partkey[i];
                long s_suppkey = DELTA_LINEITEM.suppkey[i];
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
                MKT_SHAREORDERS1LINEITEM1_DELTA.addOrDelOnZero(se1.modify(l_orderkey,p_partkey,s_suppkey),(v1 * (l_extendedprice * (1L + (-1L * l_discount)))));

          }
        }
        {  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i2 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n2; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
                long l_orderkey = e2->L_ORDERKEY;
                long p_partkey = e2->P_PARTKEY;
                long s_suppkey = e2->S_SUPPKEY;
                DOUBLE_TYPE v2 = e2->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0* i3 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0*>(MKT_SHAREORDERS1LINEITEM1_P_2.index[1]);
                  const HASH_RES_t h1 = MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn::hash(se5.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0::IdxNode* n3 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0::IdxNode*>(i3->slice(se5, h1));
                  MKT_SHAREORDERS1LINEITEM1_P_2_entry* e3;
                 
                  if (n3 && (e3 = n3->obj)) {
                    do {                
                      long total_o_year = e3->TOTAL_O_YEAR;
                      long v3 = e3->__av;
                      MKT_SHAREORDERS1.addOrDelOnZero(se2.modify(total_o_year),(v2 * (MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se3.modify(p_partkey)) * (v3 * MKT_SHAREORDERS1LINEITEM1_P_3.getValueOrDefault(se4.modify(s_suppkey))))));
                      n3 = n3->nxt;
                    } while (n3 && (e3 = n3->obj) && h1 == n3->hash &&  MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn::equals(se5, *e3)); 
                  }
                }
              n2 = n2->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i4 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n4; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long l_orderkey = e4->L_ORDERKEY;
                long p_partkey = e4->P_PARTKEY;
                long s_suppkey = e4->S_SUPPKEY;
                DOUBLE_TYPE v4 = e4->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0* i5 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3.index[1]);
                  const HASH_RES_t h2 = MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn::hash(se9.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0::IdxNode* n5 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0::IdxNode*>(i5->slice(se9, h2));
                  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry* e5;
                 
                  if (n5 && (e5 = n5->obj)) {
                    do {                
                      long o_custkey = e5->O_CUSTKEY;
                      long total_o_year = e5->TOTAL_O_YEAR;
                      long v5 = e5->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1.addOrDelOnZero(se6.modify(o_custkey,total_o_year),(v4 * (MKT_SHAREORDERS1LINEITEM1_P_3.getValueOrDefault(se7.modify(s_suppkey)) * (MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se8.modify(p_partkey)) * v5))));
                      n5 = n5->nxt;
                    } while (n5 && (e5 = n5->obj) && h2 == n5->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn::equals(se9, *e5)); 
                  }
                }
              n4 = n4->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i6 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n6; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long l_orderkey = e6->L_ORDERKEY;
                long p_partkey = e6->P_PARTKEY;
                long s_suppkey = e6->S_SUPPKEY;
                DOUBLE_TYPE v6 = e6->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0* i7 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3.index[1]);
                  const HASH_RES_t h3 = MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn::hash(se12.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0::IdxNode* n7 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0::IdxNode*>(i7->slice(se12, h3));
                  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry* e7;
                 
                  if (n7 && (e7 = n7->obj)) {
                    do {                
                      long o_custkey = e7->O_CUSTKEY;
                      long total_o_year = e7->TOTAL_O_YEAR;
                      long v7 = e7->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2.addOrDelOnZero(se10.modify(s_suppkey,o_custkey,total_o_year),(v6 * (MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se11.modify(p_partkey)) * v7)));
                      n7 = n7->nxt;
                    } while (n7 && (e7 = n7->obj) && h3 == n7->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn::equals(se12, *e7)); 
                  }
                }
              n6 = n6->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i8 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n8; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long l_orderkey = e8->L_ORDERKEY;
                long p_partkey = e8->P_PARTKEY;
                long s_suppkey = e8->S_SUPPKEY;
                DOUBLE_TYPE v8 = e8->__av;
                MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1.addOrDelOnZero(se13.modify(l_orderkey,s_suppkey),(v8 * MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se14.modify(p_partkey))));
              n8 = n8->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i9 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n9; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long l_orderkey = e9->L_ORDERKEY;
                long p_partkey = e9->P_PARTKEY;
                long s_suppkey = e9->S_SUPPKEY;
                DOUBLE_TYPE v9 = e9->__av;
                MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1.addOrDelOnZero(se15.modify(l_orderkey,p_partkey,s_suppkey),v9);
              n9 = n9->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i10 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n10; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long l_orderkey = e10->L_ORDERKEY;
                long p_partkey = e10->P_PARTKEY;
                long s_suppkey = e10->S_SUPPKEY;
                DOUBLE_TYPE v10 = e10->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0* i11 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3.index[1]);
                  const HASH_RES_t h4 = MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn::hash(se17.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0::IdxNode* n11 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0::IdxNode*>(i11->slice(se17, h4));
                  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry* e11;
                 
                  if (n11 && (e11 = n11->obj)) {
                    do {                
                      long o_custkey = e11->O_CUSTKEY;
                      long total_o_year = e11->TOTAL_O_YEAR;
                      long v11 = e11->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1.addOrDelOnZero(se16.modify(p_partkey,s_suppkey,o_custkey,total_o_year),(v10 * v11));
                      n11 = n11->nxt;
                    } while (n11 && (e11 = n11->obj) && h4 == n11->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn::equals(se17, *e11)); 
                  }
                }
              n10 = n10->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i12 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n12; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long l_orderkey = e12->L_ORDERKEY;
                long p_partkey = e12->P_PARTKEY;
                long s_suppkey = e12->S_SUPPKEY;
                DOUBLE_TYPE v12 = e12->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0* i13 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3.index[1]);
                  const HASH_RES_t h5 = MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn::hash(se20.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0::IdxNode* n13 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0::IdxNode*>(i13->slice(se20, h5));
                  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry* e13;
                 
                  if (n13 && (e13 = n13->obj)) {
                    do {                
                      long o_custkey = e13->O_CUSTKEY;
                      long total_o_year = e13->TOTAL_O_YEAR;
                      long v13 = e13->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1PART1.addOrDelOnZero(se18.modify(p_partkey,o_custkey,total_o_year),(v12 * (MKT_SHAREORDERS1LINEITEM1_P_3.getValueOrDefault(se19.modify(s_suppkey)) * v13)));
                      n13 = n13->nxt;
                    } while (n13 && (e13 = n13->obj) && h5 == n13->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn::equals(se20, *e13)); 
                  }
                }
              n12 = n12->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i14 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n14; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
                long l_orderkey = e14->L_ORDERKEY;
                long p_partkey = e14->P_PARTKEY;
                long s_suppkey = e14->S_SUPPKEY;
                DOUBLE_TYPE v14 = e14->__av;
                MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1.addOrDelOnZero(se21.modify(l_orderkey,p_partkey),(v14 * MKT_SHAREORDERS1LINEITEM1_P_3.getValueOrDefault(se22.modify(s_suppkey))));
              n14 = n14->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i15 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n15; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long l_orderkey = e15->L_ORDERKEY;
                long p_partkey = e15->P_PARTKEY;
                long s_suppkey = e15->S_SUPPKEY;
                DOUBLE_TYPE v15 = e15->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0* i16 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0*>(MKT_SHAREORDERS1LINEITEM1_P_2.index[1]);
                  const HASH_RES_t h6 = MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn::hash(se25.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0::IdxNode* n16 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0::IdxNode*>(i16->slice(se25, h6));
                  MKT_SHAREORDERS1LINEITEM1_P_2_entry* e16;
                 
                  if (n16 && (e16 = n16->obj)) {
                    do {                
                      long total_o_year = e16->TOTAL_O_YEAR;
                      long v16 = e16->__av;
                      MKT_SHAREORDERS1SUPPLIER1_P_1.addOrDelOnZero(se23.modify(s_suppkey,total_o_year),(v15 * (v16 * MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se24.modify(p_partkey)))));
                      n16 = n16->nxt;
                    } while (n16 && (e16 = n16->obj) && h6 == n16->hash &&  MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn::equals(se25, *e16)); 
                  }
                }
              n15 = n15->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i17 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n17; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long l_orderkey = e17->L_ORDERKEY;
                long p_partkey = e17->P_PARTKEY;
                long s_suppkey = e17->S_SUPPKEY;
                DOUBLE_TYPE v17 = e17->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0* i18 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0*>(MKT_SHAREORDERS1LINEITEM1_P_2.index[1]);
                  const HASH_RES_t h7 = MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn::hash(se27.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0::IdxNode* n18 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0::IdxNode*>(i18->slice(se27, h7));
                  MKT_SHAREORDERS1LINEITEM1_P_2_entry* e18;
                 
                  if (n18 && (e18 = n18->obj)) {
                    do {                
                      long total_o_year = e18->TOTAL_O_YEAR;
                      long v18 = e18->__av;
                      MKT_SHAREORDERS1SUPPLIER1_P_1PART1.addOrDelOnZero(se26.modify(p_partkey,s_suppkey,total_o_year),(v17 * v18));
                      n18 = n18->nxt;
                    } while (n18 && (e18 = n18->obj) && h7 == n18->hash &&  MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn::equals(se27, *e18)); 
                  }
                }
              n17 = n17->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i19 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n19; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long l_orderkey = e19->L_ORDERKEY;
                long p_partkey = e19->P_PARTKEY;
                long s_suppkey = e19->S_SUPPKEY;
                DOUBLE_TYPE v19 = e19->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0* i20 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0*>(MKT_SHAREORDERS1LINEITEM1_P_2.index[1]);
                  const HASH_RES_t h8 = MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn::hash(se30.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0::IdxNode* n20 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0::IdxNode*>(i20->slice(se30, h8));
                  MKT_SHAREORDERS1LINEITEM1_P_2_entry* e20;
                 
                  if (n20 && (e20 = n20->obj)) {
                    do {                
                      long total_o_year = e20->TOTAL_O_YEAR;
                      long v20 = e20->__av;
                      MKT_SHAREORDERS1PART1.addOrDelOnZero(se28.modify(p_partkey,total_o_year),(v19 * (MKT_SHAREORDERS1LINEITEM1_P_3.getValueOrDefault(se29.modify(s_suppkey)) * v20)));
                      n20 = n20->nxt;
                    } while (n20 && (e20 = n20->obj) && h8 == n20->hash &&  MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn::equals(se30, *e20)); 
                  }
                }
              n19 = n19->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i21 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n21; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e21;
        
          for (size_t i = 0; i < i21->size_; i++)
          {
            n21 = i21->buckets_ + i;
            while (n21 && (e21 = n21->obj))
            {
                long l_orderkey = e21->L_ORDERKEY;
                long p_partkey = e21->P_PARTKEY;
                long s_suppkey = e21->S_SUPPKEY;
                DOUBLE_TYPE v21 = e21->__av;
                MKT_SHAREORDERS1_L1_1_L1_2_P_2.addOrDelOnZero(se31.modify(l_orderkey),(v21 * (MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se32.modify(p_partkey)) * MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2.getValueOrDefault(se33.modify(s_suppkey)))));
              n21 = n21->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i22 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n22; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
                long l_orderkey = e22->L_ORDERKEY;
                long p_partkey = e22->P_PARTKEY;
                long s_suppkey = e22->S_SUPPKEY;
                DOUBLE_TYPE v22 = e22->__av;
                MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1.addOrDelOnZero(se34.modify(l_orderkey,p_partkey),(v22 * MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2.getValueOrDefault(se35.modify(s_suppkey))));
              n22 = n22->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i23 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n23; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e23;
        
          for (size_t i = 0; i < i23->size_; i++)
          {
            n23 = i23->buckets_ + i;
            while (n23 && (e23 = n23->obj))
            {
                long l_orderkey = e23->L_ORDERKEY;
                long p_partkey = e23->P_PARTKEY;
                long s_suppkey = e23->S_SUPPKEY;
                DOUBLE_TYPE v23 = e23->__av;
                MKT_SHAREORDERS4_P_1.addOrDelOnZero(se36.modify(l_orderkey),(v23 * (MKT_SHAREORDERS1LINEITEM1_P_3.getValueOrDefault(se37.modify(s_suppkey)) * MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se38.modify(p_partkey)))));
              n23 = n23->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i24 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n24; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e24;
        
          for (size_t i = 0; i < i24->size_; i++)
          {
            n24 = i24->buckets_ + i;
            while (n24 && (e24 = n24->obj))
            {
                long l_orderkey = e24->L_ORDERKEY;
                long p_partkey = e24->P_PARTKEY;
                long s_suppkey = e24->S_SUPPKEY;
                DOUBLE_TYPE v24 = e24->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0* i25 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0*>(MKT_SHAREPART1LINEITEM1_P_1.index[1]);
                  const HASH_RES_t h9 = MKT_SHAREPART1LINEITEM1_P_1_mapkey0_idxfn::hash(se42.modify0(l_orderkey));
                  HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0::IdxNode* n25 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0::IdxNode*>(i25->slice(se42, h9));
                  MKT_SHAREPART1LINEITEM1_P_1_entry* e25;
                 
                  if (n25 && (e25 = n25->obj)) {
                    do {                
                      date o_orderdate = e25->O_ORDERDATE;
                      long v25 = e25->__av;
                      MKT_SHAREPART1.addOrDelOnZero(se39.modify(o_orderdate),(v24 * (v25 * (MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se40.modify(p_partkey)) * MKT_SHAREORDERS1LINEITEM1_P_3.getValueOrDefault(se41.modify(s_suppkey))))));
                      n25 = n25->nxt;
                    } while (n25 && (e25 = n25->obj) && h9 == n25->hash &&  MKT_SHAREPART1LINEITEM1_P_1_mapkey0_idxfn::equals(se42, *e25)); 
                  }
                }
              n24 = n24->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i26 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n26; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e26;
        
          for (size_t i = 0; i < i26->size_; i++)
          {
            n26 = i26->buckets_ + i;
            while (n26 && (e26 = n26->obj))
            {
                long l_orderkey = e26->L_ORDERKEY;
                long p_partkey = e26->P_PARTKEY;
                long s_suppkey = e26->S_SUPPKEY;
                DOUBLE_TYPE v26 = e26->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0* i27 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0*>(MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3.index[1]);
                  const HASH_RES_t h10 = MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey0_idxfn::hash(se46.modify0(l_orderkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0::IdxNode* n27 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0::IdxNode*>(i27->slice(se46, h10));
                  MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry* e27;
                 
                  if (n27 && (e27 = n27->obj)) {
                    do {                
                      long o_custkey = e27->O_CUSTKEY;
                      date o_orderdate = e27->O_ORDERDATE;
                      long v27 = e27->__av;
                      MKT_SHAREPART1CUSTOMER1_P_2.addOrDelOnZero(se43.modify(o_custkey,o_orderdate),(v26 * (MKT_SHAREORDERS1LINEITEM1_P_3.getValueOrDefault(se44.modify(s_suppkey)) * (MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se45.modify(p_partkey)) * v27))));
                      n27 = n27->nxt;
                    } while (n27 && (e27 = n27->obj) && h10 == n27->hash &&  MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey0_idxfn::equals(se46, *e27)); 
                  }
                }
              n26 = n26->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i28 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n28; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e28;
        
          for (size_t i = 0; i < i28->size_; i++)
          {
            n28 = i28->buckets_ + i;
            while (n28 && (e28 = n28->obj))
            {
                long l_orderkey = e28->L_ORDERKEY;
                long p_partkey = e28->P_PARTKEY;
                long s_suppkey = e28->S_SUPPKEY;
                DOUBLE_TYPE v28 = e28->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0* i29 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0*>(MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3.index[1]);
                  const HASH_RES_t h11 = MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey0_idxfn::hash(se49.modify0(l_orderkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0::IdxNode* n29 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0::IdxNode*>(i29->slice(se49, h11));
                  MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry* e29;
                 
                  if (n29 && (e29 = n29->obj)) {
                    do {                
                      long o_custkey = e29->O_CUSTKEY;
                      date o_orderdate = e29->O_ORDERDATE;
                      long v29 = e29->__av;
                      MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2.addOrDelOnZero(se47.modify(s_suppkey,o_custkey,o_orderdate),(v28 * (MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se48.modify(p_partkey)) * v29)));
                      n29 = n29->nxt;
                    } while (n29 && (e29 = n29->obj) && h11 == n29->hash &&  MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey0_idxfn::equals(se49, *e29)); 
                  }
                }
              n28 = n28->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i30 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n30; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e30;
        
          for (size_t i = 0; i < i30->size_; i++)
          {
            n30 = i30->buckets_ + i;
            while (n30 && (e30 = n30->obj))
            {
                long l_orderkey = e30->L_ORDERKEY;
                long p_partkey = e30->P_PARTKEY;
                long s_suppkey = e30->S_SUPPKEY;
                DOUBLE_TYPE v30 = e30->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0* i31 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0*>(MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3.index[1]);
                  const HASH_RES_t h12 = MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey0_idxfn::hash(se51.modify0(l_orderkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0::IdxNode* n31 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0::IdxNode*>(i31->slice(se51, h12));
                  MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry* e31;
                 
                  if (n31 && (e31 = n31->obj)) {
                    do {                
                      long o_custkey = e31->O_CUSTKEY;
                      date o_orderdate = e31->O_ORDERDATE;
                      long v31 = e31->__av;
                      MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1.addOrDelOnZero(se50.modify(p_partkey,s_suppkey,o_custkey,o_orderdate),(v30 * v31));
                      n31 = n31->nxt;
                    } while (n31 && (e31 = n31->obj) && h12 == n31->hash &&  MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey0_idxfn::equals(se51, *e31)); 
                  }
                }
              n30 = n30->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i32 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n32; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e32;
        
          for (size_t i = 0; i < i32->size_; i++)
          {
            n32 = i32->buckets_ + i;
            while (n32 && (e32 = n32->obj))
            {
                long l_orderkey = e32->L_ORDERKEY;
                long p_partkey = e32->P_PARTKEY;
                long s_suppkey = e32->S_SUPPKEY;
                DOUBLE_TYPE v32 = e32->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0* i33 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0*>(MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3.index[1]);
                  const HASH_RES_t h13 = MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey0_idxfn::hash(se54.modify0(l_orderkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0::IdxNode* n33 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_0::IdxNode*>(i33->slice(se54, h13));
                  MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry* e33;
                 
                  if (n33 && (e33 = n33->obj)) {
                    do {                
                      long o_custkey = e33->O_CUSTKEY;
                      date o_orderdate = e33->O_ORDERDATE;
                      long v33 = e33->__av;
                      MKT_SHAREPART1CUSTOMER1_P_2PART1.addOrDelOnZero(se52.modify(p_partkey,o_custkey,o_orderdate),(v32 * (MKT_SHAREORDERS1LINEITEM1_P_3.getValueOrDefault(se53.modify(s_suppkey)) * v33)));
                      n33 = n33->nxt;
                    } while (n33 && (e33 = n33->obj) && h13 == n33->hash &&  MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey0_idxfn::equals(se54, *e33)); 
                  }
                }
              n32 = n32->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i34 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n34; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e34;
        
          for (size_t i = 0; i < i34->size_; i++)
          {
            n34 = i34->buckets_ + i;
            while (n34 && (e34 = n34->obj))
            {
                long l_orderkey = e34->L_ORDERKEY;
                long p_partkey = e34->P_PARTKEY;
                long s_suppkey = e34->S_SUPPKEY;
                DOUBLE_TYPE v34 = e34->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0* i35 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0*>(MKT_SHAREPART1LINEITEM1_P_1.index[1]);
                  const HASH_RES_t h14 = MKT_SHAREPART1LINEITEM1_P_1_mapkey0_idxfn::hash(se57.modify0(l_orderkey));
                  HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0::IdxNode* n35 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0::IdxNode*>(i35->slice(se57, h14));
                  MKT_SHAREPART1LINEITEM1_P_1_entry* e35;
                 
                  if (n35 && (e35 = n35->obj)) {
                    do {                
                      date o_orderdate = e35->O_ORDERDATE;
                      long v35 = e35->__av;
                      MKT_SHAREPART1SUPPLIER1_P_1.addOrDelOnZero(se55.modify(s_suppkey,o_orderdate),(v34 * (MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se56.modify(p_partkey)) * v35)));
                      n35 = n35->nxt;
                    } while (n35 && (e35 = n35->obj) && h14 == n35->hash &&  MKT_SHAREPART1LINEITEM1_P_1_mapkey0_idxfn::equals(se57, *e35)); 
                  }
                }
              n34 = n34->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i36 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n36; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e36;
        
          for (size_t i = 0; i < i36->size_; i++)
          {
            n36 = i36->buckets_ + i;
            while (n36 && (e36 = n36->obj))
            {
                long l_orderkey = e36->L_ORDERKEY;
                long p_partkey = e36->P_PARTKEY;
                long s_suppkey = e36->S_SUPPKEY;
                DOUBLE_TYPE v36 = e36->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0* i37 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0*>(MKT_SHAREPART1LINEITEM1_P_1.index[1]);
                  const HASH_RES_t h15 = MKT_SHAREPART1LINEITEM1_P_1_mapkey0_idxfn::hash(se59.modify0(l_orderkey));
                  HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0::IdxNode* n37 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0::IdxNode*>(i37->slice(se59, h15));
                  MKT_SHAREPART1LINEITEM1_P_1_entry* e37;
                 
                  if (n37 && (e37 = n37->obj)) {
                    do {                
                      date o_orderdate = e37->O_ORDERDATE;
                      long v37 = e37->__av;
                      MKT_SHAREPART1SUPPLIER1_P_1PART1.addOrDelOnZero(se58.modify(p_partkey,s_suppkey,o_orderdate),(v36 * v37));
                      n37 = n37->nxt;
                    } while (n37 && (e37 = n37->obj) && h15 == n37->hash &&  MKT_SHAREPART1LINEITEM1_P_1_mapkey0_idxfn::equals(se59, *e37)); 
                  }
                }
              n36 = n36->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i38 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n38; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e38;
        
          for (size_t i = 0; i < i38->size_; i++)
          {
            n38 = i38->buckets_ + i;
            while (n38 && (e38 = n38->obj))
            {
                long l_orderkey = e38->L_ORDERKEY;
                long p_partkey = e38->P_PARTKEY;
                long s_suppkey = e38->S_SUPPKEY;
                DOUBLE_TYPE v38 = e38->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0* i39 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0*>(MKT_SHAREPART1LINEITEM1_P_1.index[1]);
                  const HASH_RES_t h16 = MKT_SHAREPART1LINEITEM1_P_1_mapkey0_idxfn::hash(se62.modify0(l_orderkey));
                  HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0::IdxNode* n39 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_P_1_map_0::IdxNode*>(i39->slice(se62, h16));
                  MKT_SHAREPART1LINEITEM1_P_1_entry* e39;
                 
                  if (n39 && (e39 = n39->obj)) {
                    do {                
                      date o_orderdate = e39->O_ORDERDATE;
                      long v39 = e39->__av;
                      MKT_SHAREPART1PART1.addOrDelOnZero(se60.modify(p_partkey,o_orderdate),(v38 * (MKT_SHAREORDERS1LINEITEM1_P_3.getValueOrDefault(se61.modify(s_suppkey)) * v39)));
                      n39 = n39->nxt;
                    } while (n39 && (e39 = n39->obj) && h16 == n39->hash &&  MKT_SHAREPART1LINEITEM1_P_1_mapkey0_idxfn::equals(se62, *e39)); 
                  }
                }
              n38 = n38->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i40 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n40; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e40;
        
          for (size_t i = 0; i < i40->size_; i++)
          {
            n40 = i40->buckets_ + i;
            while (n40 && (e40 = n40->obj))
            {
                long l_orderkey = e40->L_ORDERKEY;
                long p_partkey = e40->P_PARTKEY;
                long s_suppkey = e40->S_SUPPKEY;
                DOUBLE_TYPE v40 = e40->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0* i41 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0*>(MKT_SHAREORDERS1LINEITEM1_P_2.index[1]);
                  const HASH_RES_t h17 = MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn::hash(se66.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0::IdxNode* n41 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0::IdxNode*>(i41->slice(se66, h17));
                  MKT_SHAREORDERS1LINEITEM1_P_2_entry* e41;
                 
                  if (n41 && (e41 = n41->obj)) {
                    do {                
                      long total_o_year = e41->TOTAL_O_YEAR;
                      long v41 = e41->__av;
                      MKT_SHAREPART1_L2_1_L1_1.addOrDelOnZero(se63.modify(total_o_year),(v40 * (v41 * (MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se64.modify(p_partkey)) * MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2.getValueOrDefault(se65.modify(s_suppkey))))));
                      n41 = n41->nxt;
                    } while (n41 && (e41 = n41->obj) && h17 == n41->hash &&  MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn::equals(se66, *e41)); 
                  }
                }
              n40 = n40->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i42 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n42; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e42;
        
          for (size_t i = 0; i < i42->size_; i++)
          {
            n42 = i42->buckets_ + i;
            while (n42 && (e42 = n42->obj))
            {
                long l_orderkey = e42->L_ORDERKEY;
                long p_partkey = e42->P_PARTKEY;
                long s_suppkey = e42->S_SUPPKEY;
                DOUBLE_TYPE v42 = e42->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0* i43 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3.index[1]);
                  const HASH_RES_t h18 = MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn::hash(se70.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0::IdxNode* n43 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0::IdxNode*>(i43->slice(se70, h18));
                  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry* e43;
                 
                  if (n43 && (e43 = n43->obj)) {
                    do {                
                      long o_custkey = e43->O_CUSTKEY;
                      long total_o_year = e43->TOTAL_O_YEAR;
                      long v43 = e43->__av;
                      MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2.addOrDelOnZero(se67.modify(o_custkey,total_o_year),(v42 * (MKT_SHAREORDERS1LINEITEM1_P_1.getValueOrDefault(se68.modify(p_partkey)) * (MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2.getValueOrDefault(se69.modify(s_suppkey)) * v43))));
                      n43 = n43->nxt;
                    } while (n43 && (e43 = n43->obj) && h18 == n43->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn::equals(se70, *e43)); 
                  }
                }
              n42 = n42->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i44 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n44; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e44;
        
          for (size_t i = 0; i < i44->size_; i++)
          {
            n44 = i44->buckets_ + i;
            while (n44 && (e44 = n44->obj))
            {
                long l_orderkey = e44->L_ORDERKEY;
                long p_partkey = e44->P_PARTKEY;
                long s_suppkey = e44->S_SUPPKEY;
                DOUBLE_TYPE v44 = e44->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0* i45 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3.index[1]);
                  const HASH_RES_t h19 = MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn::hash(se73.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0::IdxNode* n45 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_0::IdxNode*>(i45->slice(se73, h19));
                  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry* e45;
                 
                  if (n45 && (e45 = n45->obj)) {
                    do {                
                      long o_custkey = e45->O_CUSTKEY;
                      long total_o_year = e45->TOTAL_O_YEAR;
                      long v45 = e45->__av;
                      MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1.addOrDelOnZero(se71.modify(p_partkey,o_custkey,total_o_year),(v44 * (MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2.getValueOrDefault(se72.modify(s_suppkey)) * v45)));
                      n45 = n45->nxt;
                    } while (n45 && (e45 = n45->obj) && h19 == n45->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey0_idxfn::equals(se73, *e45)); 
                  }
                }
              n44 = n44->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012* i46 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012*>(MKT_SHAREORDERS1LINEITEM1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1LINEITEM1_DELTA_map_012::IdxNode* n46; 
          MKT_SHAREORDERS1LINEITEM1_DELTA_entry* e46;
        
          for (size_t i = 0; i < i46->size_; i++)
          {
            n46 = i46->buckets_ + i;
            while (n46 && (e46 = n46->obj))
            {
                long l_orderkey = e46->L_ORDERKEY;
                long p_partkey = e46->P_PARTKEY;
                long s_suppkey = e46->S_SUPPKEY;
                DOUBLE_TYPE v46 = e46->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0* i47 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0*>(MKT_SHAREORDERS1LINEITEM1_P_2.index[1]);
                  const HASH_RES_t h20 = MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn::hash(se76.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0::IdxNode* n47 = static_cast<HashIndex_MKT_SHAREORDERS1LINEITEM1_P_2_map_0::IdxNode*>(i47->slice(se76, h20));
                  MKT_SHAREORDERS1LINEITEM1_P_2_entry* e47;
                 
                  if (n47 && (e47 = n47->obj)) {
                    do {                
                      long total_o_year = e47->TOTAL_O_YEAR;
                      long v47 = e47->__av;
                      MKT_SHAREPART1_L2_1_L1_1PART1.addOrDelOnZero(se74.modify(p_partkey,total_o_year),(v46 * (v47 * MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2.getValueOrDefault(se75.modify(s_suppkey)))));
                      n47 = n47->nxt;
                    } while (n47 && (e47 = n47->obj) && h20 == n47->hash &&  MKT_SHAREORDERS1LINEITEM1_P_2_mapkey0_idxfn::equals(se76, *e47)); 
                  }
                }
              n46 = n46->nxt;
            }
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHAREPART1_map_0* i48 = static_cast<HashIndex_MKT_SHAREPART1_map_0*>(MKT_SHAREPART1.index[0]);
          HashIndex_MKT_SHAREPART1_map_0::IdxNode* n48; 
          MKT_SHAREPART1_entry* e48;
        
          for (size_t i = 0; i < i48->size_; i++)
          {
            n48 = i48->buckets_ + i;
            while (n48 && (e48 = n48->obj))
            {
                date o_orderdate = e48->O_ORDERDATE;
                DOUBLE_TYPE v48 = e48->__av;
                long l1 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg1 = 0.0;
                DOUBLE_TYPE l3 = MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se78.modify(l1));
                agg1 += Ulistmax(1L, l3);
                DOUBLE_TYPE l2 = agg1;
                MKT_SHARE.addOrDelOnZero(se77.modify(l1),(v48 * Udiv(l2)));
              n48 = n48->nxt;
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

        MKT_SHAREORDERS4_DELTA.clear();
        MKT_SHAREORDERS1_L1_1_L1_2_DELTA.clear();
        MKT_SHAREORDERS1_DOMAIN1.clear();
        {  
          for (size_t i = 0; i < DELTA_ORDERS.size; i++)
          {
                long l_orderkey = DELTA_ORDERS.orderkey[i];
                long o_custkey = DELTA_ORDERS.custkey[i];
                // STRING_TYPE o_orderstatus = DELTA_ORDERS.orderstatus[i];
                // DOUBLE_TYPE o_totalprice = DELTA_ORDERS.totalprice[i];
                date o_orderdate = DELTA_ORDERS.orderdate[i];
                // STRING_TYPE o_orderpriority = DELTA_ORDERS.orderpriority[i];
                // STRING_TYPE o_clerk = DELTA_ORDERS.clerk[i];
                // long o_shippriority = DELTA_ORDERS.shippriority[i];
                // STRING_TYPE o_comment = DELTA_ORDERS.comment[i];
                long v49 = 1L;
                (/*if */(o_orderdate >= c1 && c2 >= o_orderdate) ? MKT_SHAREORDERS4_DELTA.addOrDelOnZero(se79.modify(l_orderkey,o_custkey,o_orderdate),v49) : (void)0);
                long v50 = 1L;
                long l4 = Uyear_part(o_orderdate);
                (/*if */(o_orderdate >= c1 && c2 >= o_orderdate) ? MKT_SHAREORDERS1_L1_1_L1_2_DELTA.addOrDelOnZero(se80.modify(l_orderkey,o_custkey,l4),v50) : (void)0);
                long v51 = 1L;
                long l5 = l4;
                (/*if */(o_orderdate >= c1 && c2 >= o_orderdate) ? MKT_SHAREORDERS1_DOMAIN1.addOrDelOnZero(se81.modify(l5),(v51 != 0 ? 1L : 0L)) : (void)0);
          }
        } 
        {  // foreach
          const HashIndex_MKT_SHAREORDERS1_DOMAIN1_map_0* i52 = static_cast<HashIndex_MKT_SHAREORDERS1_DOMAIN1_map_0*>(MKT_SHAREORDERS1_DOMAIN1.index[0]);
          HashIndex_MKT_SHAREORDERS1_DOMAIN1_map_0::IdxNode* n52; 
          MKT_SHAREORDERS1_DOMAIN1_entry* e52;
        
          for (size_t i = 0; i < i52->size_; i++)
          {
            n52 = i52->buckets_ + i;
            while (n52 && (e52 = n52->obj))
            {
                long total_o_year = e52->TOTAL_O_YEAR;
                long v52 = e52->__av;
                DOUBLE_TYPE agg2 = 0.0;
                DOUBLE_TYPE agg3 = 0.0;
                DOUBLE_TYPE agg4 = 0.0;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_2* i53 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_2*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[1]);
                  const HASH_RES_t h21 = MKT_SHAREORDERS1_L1_1_L1_2_DELTA_mapkey2_idxfn::hash(se87.modify2(total_o_year));
                  HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_2::IdxNode* n53 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_2::IdxNode*>(i53->slice(se87, h21));
                  MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e53;
                 
                  if (n53 && (e53 = n53->obj)) {
                    do {                
                      long l_orderkey = e53->L_ORDERKEY;
                      long o_custkey = e53->O_CUSTKEY;
                      long v53 = e53->__av;
                      agg4 += (v53 * (MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se85.modify(o_custkey)) * MKT_SHAREORDERS1_L1_1_L1_2_P_2.getValueOrDefault(se86.modify(l_orderkey))));
                      n53 = n53->nxt;
                    } while (n53 && (e53 = n53->obj) && h21 == n53->hash &&  MKT_SHAREORDERS1_L1_1_L1_2_DELTA_mapkey2_idxfn::equals(se87, *e53)); 
                  }
                }DOUBLE_TYPE l7 = (MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se84.modify(total_o_year)) + agg4);
                agg3 += Ulistmax(1L, l7);
                DOUBLE_TYPE l6 = agg3;
                agg2 += Udiv(l6);
                DOUBLE_TYPE agg5 = 0.0;
                DOUBLE_TYPE agg6 = 0.0;
                DOUBLE_TYPE l9 = MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se88.modify(total_o_year));
                agg6 += Ulistmax(1L, l9);
                DOUBLE_TYPE l8 = agg6;
                agg5 += Udiv(l8);
                DOUBLE_TYPE agg7 = 0.0;
                {  // foreach
                  const HashIndex_MKT_SHAREORDERS4_DELTA_map_012* i54 = static_cast<HashIndex_MKT_SHAREORDERS4_DELTA_map_012*>(MKT_SHAREORDERS4_DELTA.index[0]);
                  HashIndex_MKT_SHAREORDERS4_DELTA_map_012::IdxNode* n54; 
                  MKT_SHAREORDERS4_DELTA_entry* e54;
                
                  for (size_t i = 0; i < i54->size_; i++)
                  {
                    n54 = i54->buckets_ + i;
                    while (n54 && (e54 = n54->obj))
                    {
                        long l_orderkey = e54->L_ORDERKEY;
                        long o_custkey = e54->O_CUSTKEY;
                        date o_orderdate = e54->O_ORDERDATE;
                        long v54 = e54->__av;
                        long l10 = Uyear_part(o_orderdate);
                        DOUBLE_TYPE agg8 = 0.0;
                        DOUBLE_TYPE agg9 = 0.0;
                        agg9 += (MKT_SHAREORDERS1_L1_1_L1_2_DELTA.getValueOrDefault(se90.modify(l_orderkey,o_custkey,l10)) * (MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se91.modify(o_custkey)) * MKT_SHAREORDERS1_L1_1_L1_2_P_2.getValueOrDefault(se92.modify(l_orderkey))));
                        DOUBLE_TYPE l12 = (MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se89.modify(l10)) + agg9);
                        agg8 += Ulistmax(1L, l12);
                        DOUBLE_TYPE l11 = agg8;
                        agg7 += (v54 * (MKT_SHAREORDERS4_P_1.getValueOrDefault(se93.modify(l_orderkey)) * (MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se94.modify(o_custkey)) * Udiv(l11))));
                      n54 = n54->nxt;
                    }
                  }
                }MKT_SHARE.addOrDelOnZero(se82.modify(total_o_year),((v52 != 0 ? 1L : 0L) * ((MKT_SHAREORDERS1.getValueOrDefault(se83.modify(total_o_year)) * (agg2 + (agg5 * -1L))) + agg7)));
              n52 = n52->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i55 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n55; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e55;
        
          for (size_t i = 0; i < i55->size_; i++)
          {
            n55 = i55->buckets_ + i;
            while (n55 && (e55 = n55->obj))
            {
                long l_orderkey = e55->L_ORDERKEY;
                long o_custkey = e55->O_CUSTKEY;
                long total_o_year = e55->TOTAL_O_YEAR;
                long v55 = e55->__av;
                MKT_SHAREORDERS1.addOrDelOnZero(se95.modify(total_o_year),(v55 * (MKT_SHAREORDERS4_P_1.getValueOrDefault(se96.modify(l_orderkey)) * MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se97.modify(o_custkey)))));
              n55 = n55->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i56 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n56; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e56;
        
          for (size_t i = 0; i < i56->size_; i++)
          {
            n56 = i56->buckets_ + i;
            while (n56 && (e56 = n56->obj))
            {
                long l_orderkey = e56->L_ORDERKEY;
                long o_custkey = e56->O_CUSTKEY;
                long total_o_year = e56->TOTAL_O_YEAR;
                long v56 = e56->__av;
                MKT_SHAREORDERS1CUSTOMER1_P_1.addOrDelOnZero(se98.modify(o_custkey,total_o_year),(v56 * MKT_SHAREORDERS4_P_1.getValueOrDefault(se99.modify(l_orderkey))));
              n56 = n56->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i57 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n57; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e57;
        
          for (size_t i = 0; i < i57->size_; i++)
          {
            n57 = i57->buckets_ + i;
            while (n57 && (e57 = n57->obj))
            {
                long l_orderkey = e57->L_ORDERKEY;
                long o_custkey = e57->O_CUSTKEY;
                long total_o_year = e57->TOTAL_O_YEAR;
                long v57 = e57->__av;
                MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3.addOrDelOnZero(se100.modify(l_orderkey,o_custkey,total_o_year),v57);
              n57 = n57->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i58 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n58; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e58;
        
          for (size_t i = 0; i < i58->size_; i++)
          {
            n58 = i58->buckets_ + i;
            while (n58 && (e58 = n58->obj))
            {
                long l_orderkey = e58->L_ORDERKEY;
                long o_custkey = e58->O_CUSTKEY;
                long total_o_year = e58->TOTAL_O_YEAR;
                long v58 = e58->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0* i59 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1.index[1]);
                  const HASH_RES_t h22 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey0_idxfn::hash(se102.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0::IdxNode* n59 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0::IdxNode*>(i59->slice(se102, h22));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry* e59;
                 
                  if (n59 && (e59 = n59->obj)) {
                    do {                
                      long s_suppkey = e59->S_SUPPKEY;
                      DOUBLE_TYPE v59 = e59->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2.addOrDelOnZero(se101.modify(s_suppkey,o_custkey,total_o_year),(v58 * v59));
                      n59 = n59->nxt;
                    } while (n59 && (e59 = n59->obj) && h22 == n59->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey0_idxfn::equals(se102, *e59)); 
                  }
                }
              n58 = n58->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i60 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n60; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e60;
        
          for (size_t i = 0; i < i60->size_; i++)
          {
            n60 = i60->buckets_ + i;
            while (n60 && (e60 = n60->obj))
            {
                long l_orderkey = e60->L_ORDERKEY;
                long o_custkey = e60->O_CUSTKEY;
                long total_o_year = e60->TOTAL_O_YEAR;
                long v60 = e60->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0* i61 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1.index[1]);
                  const HASH_RES_t h23 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey0_idxfn::hash(se104.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0::IdxNode* n61 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0::IdxNode*>(i61->slice(se104, h23));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry* e61;
                 
                  if (n61 && (e61 = n61->obj)) {
                    do {                
                      long p_partkey = e61->P_PARTKEY;
                      long s_suppkey = e61->S_SUPPKEY;
                      DOUBLE_TYPE v61 = e61->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1.addOrDelOnZero(se103.modify(p_partkey,s_suppkey,o_custkey,total_o_year),(v60 * v61));
                      n61 = n61->nxt;
                    } while (n61 && (e61 = n61->obj) && h23 == n61->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey0_idxfn::equals(se104, *e61)); 
                  }
                }
              n60 = n60->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i62 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n62; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e62;
        
          for (size_t i = 0; i < i62->size_; i++)
          {
            n62 = i62->buckets_ + i;
            while (n62 && (e62 = n62->obj))
            {
                long l_orderkey = e62->L_ORDERKEY;
                long o_custkey = e62->O_CUSTKEY;
                long total_o_year = e62->TOTAL_O_YEAR;
                long v62 = e62->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0* i63 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1.index[1]);
                  const HASH_RES_t h24 = MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey0_idxfn::hash(se106.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0::IdxNode* n63 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0::IdxNode*>(i63->slice(se106, h24));
                  MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry* e63;
                 
                  if (n63 && (e63 = n63->obj)) {
                    do {                
                      long p_partkey = e63->P_PARTKEY;
                      DOUBLE_TYPE v63 = e63->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1PART1.addOrDelOnZero(se105.modify(p_partkey,o_custkey,total_o_year),(v62 * v63));
                      n63 = n63->nxt;
                    } while (n63 && (e63 = n63->obj) && h24 == n63->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey0_idxfn::equals(se106, *e63)); 
                  }
                }
              n62 = n62->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i64 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n64; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e64;
        
          for (size_t i = 0; i < i64->size_; i++)
          {
            n64 = i64->buckets_ + i;
            while (n64 && (e64 = n64->obj))
            {
                long l_orderkey = e64->L_ORDERKEY;
                long o_custkey = e64->O_CUSTKEY;
                long total_o_year = e64->TOTAL_O_YEAR;
                long v64 = e64->__av;
                MKT_SHAREORDERS1LINEITEM1_P_2.addOrDelOnZero(se107.modify(l_orderkey,total_o_year),(v64 * MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se108.modify(o_custkey))));
              n64 = n64->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i65 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n65; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e65;
        
          for (size_t i = 0; i < i65->size_; i++)
          {
            n65 = i65->buckets_ + i;
            while (n65 && (e65 = n65->obj))
            {
                long l_orderkey = e65->L_ORDERKEY;
                long o_custkey = e65->O_CUSTKEY;
                long total_o_year = e65->TOTAL_O_YEAR;
                long v65 = e65->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0* i66 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1.index[1]);
                  const HASH_RES_t h25 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey0_idxfn::hash(se111.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0::IdxNode* n66 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0::IdxNode*>(i66->slice(se111, h25));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry* e66;
                 
                  if (n66 && (e66 = n66->obj)) {
                    do {                
                      long s_suppkey = e66->S_SUPPKEY;
                      DOUBLE_TYPE v66 = e66->__av;
                      MKT_SHAREORDERS1SUPPLIER1_P_1.addOrDelOnZero(se109.modify(s_suppkey,total_o_year),(v65 * (v66 * MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se110.modify(o_custkey)))));
                      n66 = n66->nxt;
                    } while (n66 && (e66 = n66->obj) && h25 == n66->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey0_idxfn::equals(se111, *e66)); 
                  }
                }
              n65 = n65->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i67 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n67; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e67;
        
          for (size_t i = 0; i < i67->size_; i++)
          {
            n67 = i67->buckets_ + i;
            while (n67 && (e67 = n67->obj))
            {
                long l_orderkey = e67->L_ORDERKEY;
                long o_custkey = e67->O_CUSTKEY;
                long total_o_year = e67->TOTAL_O_YEAR;
                long v67 = e67->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0* i68 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1.index[1]);
                  const HASH_RES_t h26 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey0_idxfn::hash(se114.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0::IdxNode* n68 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0::IdxNode*>(i68->slice(se114, h26));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry* e68;
                 
                  if (n68 && (e68 = n68->obj)) {
                    do {                
                      long p_partkey = e68->P_PARTKEY;
                      long s_suppkey = e68->S_SUPPKEY;
                      DOUBLE_TYPE v68 = e68->__av;
                      MKT_SHAREORDERS1SUPPLIER1_P_1PART1.addOrDelOnZero(se112.modify(p_partkey,s_suppkey,total_o_year),(v67 * (MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se113.modify(o_custkey)) * v68)));
                      n68 = n68->nxt;
                    } while (n68 && (e68 = n68->obj) && h26 == n68->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey0_idxfn::equals(se114, *e68)); 
                  }
                }
              n67 = n67->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i69 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n69; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e69;
        
          for (size_t i = 0; i < i69->size_; i++)
          {
            n69 = i69->buckets_ + i;
            while (n69 && (e69 = n69->obj))
            {
                long l_orderkey = e69->L_ORDERKEY;
                long o_custkey = e69->O_CUSTKEY;
                long total_o_year = e69->TOTAL_O_YEAR;
                long v69 = e69->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0* i70 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1.index[1]);
                  const HASH_RES_t h27 = MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey0_idxfn::hash(se117.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0::IdxNode* n70 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0::IdxNode*>(i70->slice(se117, h27));
                  MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry* e70;
                 
                  if (n70 && (e70 = n70->obj)) {
                    do {                
                      long p_partkey = e70->P_PARTKEY;
                      DOUBLE_TYPE v70 = e70->__av;
                      MKT_SHAREORDERS1PART1.addOrDelOnZero(se115.modify(p_partkey,total_o_year),(v69 * (MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se116.modify(o_custkey)) * v70)));
                      n70 = n70->nxt;
                    } while (n70 && (e70 = n70->obj) && h27 == n70->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey0_idxfn::equals(se117, *e70)); 
                  }
                }
              n69 = n69->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS4_DELTA_map_012* i71 = static_cast<HashIndex_MKT_SHAREORDERS4_DELTA_map_012*>(MKT_SHAREORDERS4_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS4_DELTA_map_012::IdxNode* n71; 
          MKT_SHAREORDERS4_DELTA_entry* e71;
        
          for (size_t i = 0; i < i71->size_; i++)
          {
            n71 = i71->buckets_ + i;
            while (n71 && (e71 = n71->obj))
            {
                long l_orderkey = e71->L_ORDERKEY;
                long o_custkey = e71->O_CUSTKEY;
                date o_orderdate = e71->O_ORDERDATE;
                long v71 = e71->__av;
                MKT_SHAREPART1.addOrDelOnZero(se118.modify(o_orderdate),(v71 * (MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se119.modify(o_custkey)) * MKT_SHAREORDERS4_P_1.getValueOrDefault(se120.modify(l_orderkey)))));
              n71 = n71->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS4_DELTA_map_012* i72 = static_cast<HashIndex_MKT_SHAREORDERS4_DELTA_map_012*>(MKT_SHAREORDERS4_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS4_DELTA_map_012::IdxNode* n72; 
          MKT_SHAREORDERS4_DELTA_entry* e72;
        
          for (size_t i = 0; i < i72->size_; i++)
          {
            n72 = i72->buckets_ + i;
            while (n72 && (e72 = n72->obj))
            {
                long l_orderkey = e72->L_ORDERKEY;
                long o_custkey = e72->O_CUSTKEY;
                date o_orderdate = e72->O_ORDERDATE;
                long v72 = e72->__av;
                MKT_SHAREPART1CUSTOMER1_P_2.addOrDelOnZero(se121.modify(o_custkey,o_orderdate),(v72 * MKT_SHAREORDERS4_P_1.getValueOrDefault(se122.modify(l_orderkey))));
              n72 = n72->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS4_DELTA_map_012* i73 = static_cast<HashIndex_MKT_SHAREORDERS4_DELTA_map_012*>(MKT_SHAREORDERS4_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS4_DELTA_map_012::IdxNode* n73; 
          MKT_SHAREORDERS4_DELTA_entry* e73;
        
          for (size_t i = 0; i < i73->size_; i++)
          {
            n73 = i73->buckets_ + i;
            while (n73 && (e73 = n73->obj))
            {
                long l_orderkey = e73->L_ORDERKEY;
                long o_custkey = e73->O_CUSTKEY;
                date o_orderdate = e73->O_ORDERDATE;
                long v73 = e73->__av;
                MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3.addOrDelOnZero(se123.modify(l_orderkey,o_custkey,o_orderdate),v73);
              n73 = n73->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS4_DELTA_map_012* i74 = static_cast<HashIndex_MKT_SHAREORDERS4_DELTA_map_012*>(MKT_SHAREORDERS4_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS4_DELTA_map_012::IdxNode* n74; 
          MKT_SHAREORDERS4_DELTA_entry* e74;
        
          for (size_t i = 0; i < i74->size_; i++)
          {
            n74 = i74->buckets_ + i;
            while (n74 && (e74 = n74->obj))
            {
                long l_orderkey = e74->L_ORDERKEY;
                long o_custkey = e74->O_CUSTKEY;
                date o_orderdate = e74->O_ORDERDATE;
                long v74 = e74->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0* i75 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1.index[1]);
                  const HASH_RES_t h28 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey0_idxfn::hash(se125.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0::IdxNode* n75 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0::IdxNode*>(i75->slice(se125, h28));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry* e75;
                 
                  if (n75 && (e75 = n75->obj)) {
                    do {                
                      long s_suppkey = e75->S_SUPPKEY;
                      DOUBLE_TYPE v75 = e75->__av;
                      MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2.addOrDelOnZero(se124.modify(s_suppkey,o_custkey,o_orderdate),(v74 * v75));
                      n75 = n75->nxt;
                    } while (n75 && (e75 = n75->obj) && h28 == n75->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey0_idxfn::equals(se125, *e75)); 
                  }
                }
              n74 = n74->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS4_DELTA_map_012* i76 = static_cast<HashIndex_MKT_SHAREORDERS4_DELTA_map_012*>(MKT_SHAREORDERS4_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS4_DELTA_map_012::IdxNode* n76; 
          MKT_SHAREORDERS4_DELTA_entry* e76;
        
          for (size_t i = 0; i < i76->size_; i++)
          {
            n76 = i76->buckets_ + i;
            while (n76 && (e76 = n76->obj))
            {
                long l_orderkey = e76->L_ORDERKEY;
                long o_custkey = e76->O_CUSTKEY;
                date o_orderdate = e76->O_ORDERDATE;
                long v76 = e76->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0* i77 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1.index[1]);
                  const HASH_RES_t h29 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey0_idxfn::hash(se127.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0::IdxNode* n77 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0::IdxNode*>(i77->slice(se127, h29));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry* e77;
                 
                  if (n77 && (e77 = n77->obj)) {
                    do {                
                      long p_partkey = e77->P_PARTKEY;
                      long s_suppkey = e77->S_SUPPKEY;
                      DOUBLE_TYPE v77 = e77->__av;
                      MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1.addOrDelOnZero(se126.modify(p_partkey,s_suppkey,o_custkey,o_orderdate),(v76 * v77));
                      n77 = n77->nxt;
                    } while (n77 && (e77 = n77->obj) && h29 == n77->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey0_idxfn::equals(se127, *e77)); 
                  }
                }
              n76 = n76->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS4_DELTA_map_012* i78 = static_cast<HashIndex_MKT_SHAREORDERS4_DELTA_map_012*>(MKT_SHAREORDERS4_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS4_DELTA_map_012::IdxNode* n78; 
          MKT_SHAREORDERS4_DELTA_entry* e78;
        
          for (size_t i = 0; i < i78->size_; i++)
          {
            n78 = i78->buckets_ + i;
            while (n78 && (e78 = n78->obj))
            {
                long l_orderkey = e78->L_ORDERKEY;
                long o_custkey = e78->O_CUSTKEY;
                date o_orderdate = e78->O_ORDERDATE;
                long v78 = e78->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0* i79 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1.index[1]);
                  const HASH_RES_t h30 = MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey0_idxfn::hash(se129.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0::IdxNode* n79 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0::IdxNode*>(i79->slice(se129, h30));
                  MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry* e79;
                 
                  if (n79 && (e79 = n79->obj)) {
                    do {                
                      long p_partkey = e79->P_PARTKEY;
                      DOUBLE_TYPE v79 = e79->__av;
                      MKT_SHAREPART1CUSTOMER1_P_2PART1.addOrDelOnZero(se128.modify(p_partkey,o_custkey,o_orderdate),(v78 * v79));
                      n79 = n79->nxt;
                    } while (n79 && (e79 = n79->obj) && h30 == n79->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey0_idxfn::equals(se129, *e79)); 
                  }
                }
              n78 = n78->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS4_DELTA_map_012* i80 = static_cast<HashIndex_MKT_SHAREORDERS4_DELTA_map_012*>(MKT_SHAREORDERS4_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS4_DELTA_map_012::IdxNode* n80; 
          MKT_SHAREORDERS4_DELTA_entry* e80;
        
          for (size_t i = 0; i < i80->size_; i++)
          {
            n80 = i80->buckets_ + i;
            while (n80 && (e80 = n80->obj))
            {
                long l_orderkey = e80->L_ORDERKEY;
                long o_custkey = e80->O_CUSTKEY;
                date o_orderdate = e80->O_ORDERDATE;
                long v80 = e80->__av;
                MKT_SHAREPART1LINEITEM1_P_1.addOrDelOnZero(se130.modify(l_orderkey,o_orderdate),(v80 * MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se131.modify(o_custkey))));
              n80 = n80->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS4_DELTA_map_012* i81 = static_cast<HashIndex_MKT_SHAREORDERS4_DELTA_map_012*>(MKT_SHAREORDERS4_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS4_DELTA_map_012::IdxNode* n81; 
          MKT_SHAREORDERS4_DELTA_entry* e81;
        
          for (size_t i = 0; i < i81->size_; i++)
          {
            n81 = i81->buckets_ + i;
            while (n81 && (e81 = n81->obj))
            {
                long l_orderkey = e81->L_ORDERKEY;
                long o_custkey = e81->O_CUSTKEY;
                date o_orderdate = e81->O_ORDERDATE;
                long v81 = e81->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0* i82 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1.index[1]);
                  const HASH_RES_t h31 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey0_idxfn::hash(se134.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0::IdxNode* n82 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_0::IdxNode*>(i82->slice(se134, h31));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry* e82;
                 
                  if (n82 && (e82 = n82->obj)) {
                    do {                
                      long s_suppkey = e82->S_SUPPKEY;
                      DOUBLE_TYPE v82 = e82->__av;
                      MKT_SHAREPART1SUPPLIER1_P_1.addOrDelOnZero(se132.modify(s_suppkey,o_orderdate),(v81 * (MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se133.modify(o_custkey)) * v82)));
                      n82 = n82->nxt;
                    } while (n82 && (e82 = n82->obj) && h31 == n82->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey0_idxfn::equals(se134, *e82)); 
                  }
                }
              n81 = n81->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS4_DELTA_map_012* i83 = static_cast<HashIndex_MKT_SHAREORDERS4_DELTA_map_012*>(MKT_SHAREORDERS4_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS4_DELTA_map_012::IdxNode* n83; 
          MKT_SHAREORDERS4_DELTA_entry* e83;
        
          for (size_t i = 0; i < i83->size_; i++)
          {
            n83 = i83->buckets_ + i;
            while (n83 && (e83 = n83->obj))
            {
                long l_orderkey = e83->L_ORDERKEY;
                long o_custkey = e83->O_CUSTKEY;
                date o_orderdate = e83->O_ORDERDATE;
                long v83 = e83->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0* i84 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1.index[1]);
                  const HASH_RES_t h32 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey0_idxfn::hash(se137.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0::IdxNode* n84 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_0::IdxNode*>(i84->slice(se137, h32));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry* e84;
                 
                  if (n84 && (e84 = n84->obj)) {
                    do {                
                      long p_partkey = e84->P_PARTKEY;
                      long s_suppkey = e84->S_SUPPKEY;
                      DOUBLE_TYPE v84 = e84->__av;
                      MKT_SHAREPART1SUPPLIER1_P_1PART1.addOrDelOnZero(se135.modify(p_partkey,s_suppkey,o_orderdate),(v83 * (MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se136.modify(o_custkey)) * v84)));
                      n84 = n84->nxt;
                    } while (n84 && (e84 = n84->obj) && h32 == n84->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey0_idxfn::equals(se137, *e84)); 
                  }
                }
              n83 = n83->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS4_DELTA_map_012* i85 = static_cast<HashIndex_MKT_SHAREORDERS4_DELTA_map_012*>(MKT_SHAREORDERS4_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS4_DELTA_map_012::IdxNode* n85; 
          MKT_SHAREORDERS4_DELTA_entry* e85;
        
          for (size_t i = 0; i < i85->size_; i++)
          {
            n85 = i85->buckets_ + i;
            while (n85 && (e85 = n85->obj))
            {
                long l_orderkey = e85->L_ORDERKEY;
                long o_custkey = e85->O_CUSTKEY;
                date o_orderdate = e85->O_ORDERDATE;
                long v85 = e85->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0* i86 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1.index[1]);
                  const HASH_RES_t h33 = MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey0_idxfn::hash(se140.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0::IdxNode* n86 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_0::IdxNode*>(i86->slice(se140, h33));
                  MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry* e86;
                 
                  if (n86 && (e86 = n86->obj)) {
                    do {                
                      long p_partkey = e86->P_PARTKEY;
                      DOUBLE_TYPE v86 = e86->__av;
                      MKT_SHAREPART1PART1.addOrDelOnZero(se138.modify(p_partkey,o_orderdate),(v85 * (MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se139.modify(o_custkey)) * v86)));
                      n86 = n86->nxt;
                    } while (n86 && (e86 = n86->obj) && h33 == n86->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey0_idxfn::equals(se140, *e86)); 
                  }
                }
              n85 = n85->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i87 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n87; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e87;
        
          for (size_t i = 0; i < i87->size_; i++)
          {
            n87 = i87->buckets_ + i;
            while (n87 && (e87 = n87->obj))
            {
                long l_orderkey = e87->L_ORDERKEY;
                long o_custkey = e87->O_CUSTKEY;
                long total_o_year = e87->TOTAL_O_YEAR;
                long v87 = e87->__av;
                MKT_SHAREPART1_L2_1_L1_1.addOrDelOnZero(se141.modify(total_o_year),(v87 * (MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se142.modify(o_custkey)) * MKT_SHAREORDERS1_L1_1_L1_2_P_2.getValueOrDefault(se143.modify(l_orderkey)))));
              n87 = n87->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i88 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n88; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e88;
        
          for (size_t i = 0; i < i88->size_; i++)
          {
            n88 = i88->buckets_ + i;
            while (n88 && (e88 = n88->obj))
            {
                long l_orderkey = e88->L_ORDERKEY;
                long o_custkey = e88->O_CUSTKEY;
                long total_o_year = e88->TOTAL_O_YEAR;
                long v88 = e88->__av;
                MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2.addOrDelOnZero(se144.modify(o_custkey,total_o_year),(v88 * MKT_SHAREORDERS1_L1_1_L1_2_P_2.getValueOrDefault(se145.modify(l_orderkey))));
              n88 = n88->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i89 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n89; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e89;
        
          for (size_t i = 0; i < i89->size_; i++)
          {
            n89 = i89->buckets_ + i;
            while (n89 && (e89 = n89->obj))
            {
                long l_orderkey = e89->L_ORDERKEY;
                long o_custkey = e89->O_CUSTKEY;
                long total_o_year = e89->TOTAL_O_YEAR;
                long v89 = e89->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_0* i90 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_0*>(MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1.index[1]);
                  const HASH_RES_t h34 = MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey0_idxfn::hash(se147.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_0::IdxNode* n90 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_0::IdxNode*>(i90->slice(se147, h34));
                  MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry* e90;
                 
                  if (n90 && (e90 = n90->obj)) {
                    do {                
                      long p_partkey = e90->P_PARTKEY;
                      DOUBLE_TYPE v90 = e90->__av;
                      MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1.addOrDelOnZero(se146.modify(p_partkey,o_custkey,total_o_year),(v89 * v90));
                      n90 = n90->nxt;
                    } while (n90 && (e90 = n90->obj) && h34 == n90->hash &&  MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey0_idxfn::equals(se147, *e90)); 
                  }
                }
              n89 = n89->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012* i91 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012*>(MKT_SHAREORDERS1_L1_1_L1_2_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map_012::IdxNode* n91; 
          MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry* e91;
        
          for (size_t i = 0; i < i91->size_; i++)
          {
            n91 = i91->buckets_ + i;
            while (n91 && (e91 = n91->obj))
            {
                long l_orderkey = e91->L_ORDERKEY;
                long o_custkey = e91->O_CUSTKEY;
                long total_o_year = e91->TOTAL_O_YEAR;
                long v91 = e91->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_0* i92 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_0*>(MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1.index[1]);
                  const HASH_RES_t h35 = MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey0_idxfn::hash(se150.modify0(l_orderkey));
                  HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_0::IdxNode* n92 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_0::IdxNode*>(i92->slice(se150, h35));
                  MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry* e92;
                 
                  if (n92 && (e92 = n92->obj)) {
                    do {                
                      long p_partkey = e92->P_PARTKEY;
                      DOUBLE_TYPE v92 = e92->__av;
                      MKT_SHAREPART1_L2_1_L1_1PART1.addOrDelOnZero(se148.modify(p_partkey,total_o_year),(v91 * (MKT_SHAREORDERS1_L1_1_L1_2_P_1.getValueOrDefault(se149.modify(o_custkey)) * v92)));
                      n92 = n92->nxt;
                    } while (n92 && (e92 = n92->obj) && h35 == n92->hash &&  MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey0_idxfn::equals(se150, *e92)); 
                  }
                }
              n91 = n91->nxt;
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

        MKT_SHAREORDERS1PART1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_PART.size; i++)
          {
                long p_partkey = DELTA_PART.partkey[i];
                // STRING_TYPE p_name = DELTA_PART.name[i];
                // STRING_TYPE p_mfgr = DELTA_PART.mfgr[i];
                // STRING_TYPE p_brand = DELTA_PART.brand[i];
                STRING_TYPE lift7 = DELTA_PART.type[i];
                // long p_size = DELTA_PART.psize[i];
                // STRING_TYPE p_container = DELTA_PART.container[i];
                // DOUBLE_TYPE p_retailprice = DELTA_PART.retailprice[i];
                // STRING_TYPE p_comment = DELTA_PART.comment[i];
                long v93 = 1L;
                (/*if */(lift7 == c3) ? MKT_SHAREORDERS1PART1_DELTA.addOrDelOnZero(se151.modify(p_partkey),v93) : (void)0);
          }
        }
        {  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i94 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n94; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e94;
        
          for (size_t i = 0; i < i94->size_; i++)
          {
            n94 = i94->buckets_ + i;
            while (n94 && (e94 = n94->obj))
            {
                long p_partkey = e94->P_PARTKEY;
                long v94 = e94->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1PART1_map_0* i95 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_map_0*>(MKT_SHAREORDERS1PART1.index[1]);
                  const HASH_RES_t h36 = MKT_SHAREORDERS1PART1_mapkey0_idxfn::hash(se153.modify0(p_partkey));
                  HashIndex_MKT_SHAREORDERS1PART1_map_0::IdxNode* n95 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_map_0::IdxNode*>(i95->slice(se153, h36));
                  MKT_SHAREORDERS1PART1_entry* e95;
                 
                  if (n95 && (e95 = n95->obj)) {
                    do {                
                      long total_o_year = e95->TOTAL_O_YEAR;
                      DOUBLE_TYPE v95 = e95->__av;
                      MKT_SHAREORDERS1.addOrDelOnZero(se152.modify(total_o_year),(v94 * v95));
                      n95 = n95->nxt;
                    } while (n95 && (e95 = n95->obj) && h36 == n95->hash &&  MKT_SHAREORDERS1PART1_mapkey0_idxfn::equals(se153, *e95)); 
                  }
                }
              n94 = n94->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i96 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n96; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e96;
        
          for (size_t i = 0; i < i96->size_; i++)
          {
            n96 = i96->buckets_ + i;
            while (n96 && (e96 = n96->obj))
            {
                long p_partkey = e96->P_PARTKEY;
                long v96 = e96->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map_0* i97 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1PART1.index[1]);
                  const HASH_RES_t h37 = MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey0_idxfn::hash(se155.modify0(p_partkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map_0::IdxNode* n97 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map_0::IdxNode*>(i97->slice(se155, h37));
                  MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry* e97;
                 
                  if (n97 && (e97 = n97->obj)) {
                    do {                
                      long o_custkey = e97->O_CUSTKEY;
                      long total_o_year = e97->TOTAL_O_YEAR;
                      DOUBLE_TYPE v97 = e97->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1.addOrDelOnZero(se154.modify(o_custkey,total_o_year),(v96 * v97));
                      n97 = n97->nxt;
                    } while (n97 && (e97 = n97->obj) && h37 == n97->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey0_idxfn::equals(se155, *e97)); 
                  }
                }
              n96 = n96->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i98 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n98; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e98;
        
          for (size_t i = 0; i < i98->size_; i++)
          {
            n98 = i98->buckets_ + i;
            while (n98 && (e98 = n98->obj))
            {
                long p_partkey = e98->P_PARTKEY;
                long v98 = e98->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_0* i99 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1.index[1]);
                  const HASH_RES_t h38 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey0_idxfn::hash(se157.modify0(p_partkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_0::IdxNode* n99 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_0::IdxNode*>(i99->slice(se157, h38));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry* e99;
                 
                  if (n99 && (e99 = n99->obj)) {
                    do {                
                      long s_suppkey = e99->S_SUPPKEY;
                      long o_custkey = e99->O_CUSTKEY;
                      long total_o_year = e99->TOTAL_O_YEAR;
                      DOUBLE_TYPE v99 = e99->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2.addOrDelOnZero(se156.modify(s_suppkey,o_custkey,total_o_year),(v98 * v99));
                      n99 = n99->nxt;
                    } while (n99 && (e99 = n99->obj) && h38 == n99->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey0_idxfn::equals(se157, *e99)); 
                  }
                }
              n98 = n98->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i100 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n100; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e100;
        
          for (size_t i = 0; i < i100->size_; i++)
          {
            n100 = i100->buckets_ + i;
            while (n100 && (e100 = n100->obj))
            {
                long p_partkey = e100->P_PARTKEY;
                long v100 = e100->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_1* i101 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_1*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1.index[2]);
                  const HASH_RES_t h39 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey1_idxfn::hash(se159.modify1(p_partkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_1::IdxNode* n101 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_1::IdxNode*>(i101->slice(se159, h39));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry* e101;
                 
                  if (n101 && (e101 = n101->obj)) {
                    do {                
                      long l_orderkey = e101->L_ORDERKEY;
                      long s_suppkey = e101->S_SUPPKEY;
                      DOUBLE_TYPE v101 = e101->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1.addOrDelOnZero(se158.modify(l_orderkey,s_suppkey),(v100 * v101));
                      n101 = n101->nxt;
                    } while (n101 && (e101 = n101->obj) && h39 == n101->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey1_idxfn::equals(se159, *e101)); 
                  }
                }
              n100 = n100->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i102 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n102; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e102;
        
          for (size_t i = 0; i < i102->size_; i++)
          {
            n102 = i102->buckets_ + i;
            while (n102 && (e102 = n102->obj))
            {
                long p_partkey = e102->P_PARTKEY;
                long v102 = e102->__av;
                MKT_SHAREORDERS1LINEITEM1_P_1.addOrDelOnZero(se160.modify(p_partkey),v102);
              n102 = n102->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i103 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n103; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e103;
        
          for (size_t i = 0; i < i103->size_; i++)
          {
            n103 = i103->buckets_ + i;
            while (n103 && (e103 = n103->obj))
            {
                long p_partkey = e103->P_PARTKEY;
                long v103 = e103->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_0* i104 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_0*>(MKT_SHAREORDERS1SUPPLIER1_P_1PART1.index[1]);
                  const HASH_RES_t h40 = MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey0_idxfn::hash(se162.modify0(p_partkey));
                  HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_0::IdxNode* n104 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_0::IdxNode*>(i104->slice(se162, h40));
                  MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry* e104;
                 
                  if (n104 && (e104 = n104->obj)) {
                    do {                
                      long s_suppkey = e104->S_SUPPKEY;
                      long total_o_year = e104->TOTAL_O_YEAR;
                      DOUBLE_TYPE v104 = e104->__av;
                      MKT_SHAREORDERS1SUPPLIER1_P_1.addOrDelOnZero(se161.modify(s_suppkey,total_o_year),(v103 * v104));
                      n104 = n104->nxt;
                    } while (n104 && (e104 = n104->obj) && h40 == n104->hash &&  MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey0_idxfn::equals(se162, *e104)); 
                  }
                }
              n103 = n103->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i105 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n105; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e105;
        
          for (size_t i = 0; i < i105->size_; i++)
          {
            n105 = i105->buckets_ + i;
            while (n105 && (e105 = n105->obj))
            {
                long p_partkey = e105->P_PARTKEY;
                long v105 = e105->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_1* i106 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_1*>(MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1.index[2]);
                  const HASH_RES_t h41 = MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey1_idxfn::hash(se164.modify1(p_partkey));
                  HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_1::IdxNode* n106 = static_cast<HashIndex_MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map_1::IdxNode*>(i106->slice(se164, h41));
                  MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry* e106;
                 
                  if (n106 && (e106 = n106->obj)) {
                    do {                
                      long l_orderkey = e106->L_ORDERKEY;
                      DOUBLE_TYPE v106 = e106->__av;
                      MKT_SHAREORDERS1_L1_1_L1_2_P_2.addOrDelOnZero(se163.modify(l_orderkey),(v105 * v106));
                      n106 = n106->nxt;
                    } while (n106 && (e106 = n106->obj) && h41 == n106->hash &&  MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_mapkey1_idxfn::equals(se164, *e106)); 
                  }
                }
              n105 = n105->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i107 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n107; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e107;
        
          for (size_t i = 0; i < i107->size_; i++)
          {
            n107 = i107->buckets_ + i;
            while (n107 && (e107 = n107->obj))
            {
                long p_partkey = e107->P_PARTKEY;
                long v107 = e107->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_1* i108 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_1*>(MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1.index[2]);
                  const HASH_RES_t h42 = MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey1_idxfn::hash(se166.modify1(p_partkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_1::IdxNode* n108 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map_1::IdxNode*>(i108->slice(se166, h42));
                  MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry* e108;
                 
                  if (n108 && (e108 = n108->obj)) {
                    do {                
                      long l_orderkey = e108->L_ORDERKEY;
                      DOUBLE_TYPE v108 = e108->__av;
                      MKT_SHAREORDERS4_P_1.addOrDelOnZero(se165.modify(l_orderkey),(v107 * v108));
                      n108 = n108->nxt;
                    } while (n108 && (e108 = n108->obj) && h42 == n108->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_mapkey1_idxfn::equals(se166, *e108)); 
                  }
                }
              n107 = n107->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i109 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n109; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e109;
        
          for (size_t i = 0; i < i109->size_; i++)
          {
            n109 = i109->buckets_ + i;
            while (n109 && (e109 = n109->obj))
            {
                long p_partkey = e109->P_PARTKEY;
                long v109 = e109->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1PART1_map_0* i110 = static_cast<HashIndex_MKT_SHAREPART1PART1_map_0*>(MKT_SHAREPART1PART1.index[1]);
                  const HASH_RES_t h43 = MKT_SHAREPART1PART1_mapkey0_idxfn::hash(se168.modify0(p_partkey));
                  HashIndex_MKT_SHAREPART1PART1_map_0::IdxNode* n110 = static_cast<HashIndex_MKT_SHAREPART1PART1_map_0::IdxNode*>(i110->slice(se168, h43));
                  MKT_SHAREPART1PART1_entry* e110;
                 
                  if (n110 && (e110 = n110->obj)) {
                    do {                
                      date o_orderdate = e110->O_ORDERDATE;
                      DOUBLE_TYPE v110 = e110->__av;
                      MKT_SHAREPART1.addOrDelOnZero(se167.modify(o_orderdate),(v109 * v110));
                      n110 = n110->nxt;
                    } while (n110 && (e110 = n110->obj) && h43 == n110->hash &&  MKT_SHAREPART1PART1_mapkey0_idxfn::equals(se168, *e110)); 
                  }
                }
              n109 = n109->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i111 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n111; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e111;
        
          for (size_t i = 0; i < i111->size_; i++)
          {
            n111 = i111->buckets_ + i;
            while (n111 && (e111 = n111->obj))
            {
                long p_partkey = e111->P_PARTKEY;
                long v111 = e111->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2PART1_map_0* i112 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2PART1_map_0*>(MKT_SHAREPART1CUSTOMER1_P_2PART1.index[1]);
                  const HASH_RES_t h44 = MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey0_idxfn::hash(se170.modify0(p_partkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2PART1_map_0::IdxNode* n112 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2PART1_map_0::IdxNode*>(i112->slice(se170, h44));
                  MKT_SHAREPART1CUSTOMER1_P_2PART1_entry* e112;
                 
                  if (n112 && (e112 = n112->obj)) {
                    do {                
                      long o_custkey = e112->O_CUSTKEY;
                      date o_orderdate = e112->O_ORDERDATE;
                      DOUBLE_TYPE v112 = e112->__av;
                      MKT_SHAREPART1CUSTOMER1_P_2.addOrDelOnZero(se169.modify(o_custkey,o_orderdate),(v111 * v112));
                      n112 = n112->nxt;
                    } while (n112 && (e112 = n112->obj) && h44 == n112->hash &&  MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey0_idxfn::equals(se170, *e112)); 
                  }
                }
              n111 = n111->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i113 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n113; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e113;
        
          for (size_t i = 0; i < i113->size_; i++)
          {
            n113 = i113->buckets_ + i;
            while (n113 && (e113 = n113->obj))
            {
                long p_partkey = e113->P_PARTKEY;
                long v113 = e113->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_0* i114 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_0*>(MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1.index[1]);
                  const HASH_RES_t h45 = MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey0_idxfn::hash(se172.modify0(p_partkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_0::IdxNode* n114 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_0::IdxNode*>(i114->slice(se172, h45));
                  MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry* e114;
                 
                  if (n114 && (e114 = n114->obj)) {
                    do {                
                      long s_suppkey = e114->S_SUPPKEY;
                      long o_custkey = e114->O_CUSTKEY;
                      date o_orderdate = e114->O_ORDERDATE;
                      DOUBLE_TYPE v114 = e114->__av;
                      MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2.addOrDelOnZero(se171.modify(s_suppkey,o_custkey,o_orderdate),(v113 * v114));
                      n114 = n114->nxt;
                    } while (n114 && (e114 = n114->obj) && h45 == n114->hash &&  MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey0_idxfn::equals(se172, *e114)); 
                  }
                }
              n113 = n113->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i115 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n115; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e115;
        
          for (size_t i = 0; i < i115->size_; i++)
          {
            n115 = i115->buckets_ + i;
            while (n115 && (e115 = n115->obj))
            {
                long p_partkey = e115->P_PARTKEY;
                long v115 = e115->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1SUPPLIER1_P_1PART1_map_0* i116 = static_cast<HashIndex_MKT_SHAREPART1SUPPLIER1_P_1PART1_map_0*>(MKT_SHAREPART1SUPPLIER1_P_1PART1.index[1]);
                  const HASH_RES_t h46 = MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey0_idxfn::hash(se174.modify0(p_partkey));
                  HashIndex_MKT_SHAREPART1SUPPLIER1_P_1PART1_map_0::IdxNode* n116 = static_cast<HashIndex_MKT_SHAREPART1SUPPLIER1_P_1PART1_map_0::IdxNode*>(i116->slice(se174, h46));
                  MKT_SHAREPART1SUPPLIER1_P_1PART1_entry* e116;
                 
                  if (n116 && (e116 = n116->obj)) {
                    do {                
                      long s_suppkey = e116->S_SUPPKEY;
                      date o_orderdate = e116->O_ORDERDATE;
                      DOUBLE_TYPE v116 = e116->__av;
                      MKT_SHAREPART1SUPPLIER1_P_1.addOrDelOnZero(se173.modify(s_suppkey,o_orderdate),(v115 * v116));
                      n116 = n116->nxt;
                    } while (n116 && (e116 = n116->obj) && h46 == n116->hash &&  MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey0_idxfn::equals(se174, *e116)); 
                  }
                }
              n115 = n115->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i117 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n117; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e117;
        
          for (size_t i = 0; i < i117->size_; i++)
          {
            n117 = i117->buckets_ + i;
            while (n117 && (e117 = n117->obj))
            {
                long p_partkey = e117->P_PARTKEY;
                long v117 = e117->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1_L2_1_L1_1PART1_map_0* i118 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1PART1_map_0*>(MKT_SHAREPART1_L2_1_L1_1PART1.index[1]);
                  const HASH_RES_t h47 = MKT_SHAREPART1_L2_1_L1_1PART1_mapkey0_idxfn::hash(se176.modify0(p_partkey));
                  HashIndex_MKT_SHAREPART1_L2_1_L1_1PART1_map_0::IdxNode* n118 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1PART1_map_0::IdxNode*>(i118->slice(se176, h47));
                  MKT_SHAREPART1_L2_1_L1_1PART1_entry* e118;
                 
                  if (n118 && (e118 = n118->obj)) {
                    do {                
                      long total_o_year = e118->TOTAL_O_YEAR;
                      DOUBLE_TYPE v118 = e118->__av;
                      MKT_SHAREPART1_L2_1_L1_1.addOrDelOnZero(se175.modify(total_o_year),(v117 * v118));
                      n118 = n118->nxt;
                    } while (n118 && (e118 = n118->obj) && h47 == n118->hash &&  MKT_SHAREPART1_L2_1_L1_1PART1_mapkey0_idxfn::equals(se176, *e118)); 
                  }
                }
              n117 = n117->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0* i119 = static_cast<HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0*>(MKT_SHAREORDERS1PART1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1PART1_DELTA_map_0::IdxNode* n119; 
          MKT_SHAREORDERS1PART1_DELTA_entry* e119;
        
          for (size_t i = 0; i < i119->size_; i++)
          {
            n119 = i119->buckets_ + i;
            while (n119 && (e119 = n119->obj))
            {
                long p_partkey = e119->P_PARTKEY;
                long v119 = e119->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map_0* i120 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map_0*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1.index[1]);
                  const HASH_RES_t h48 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey0_idxfn::hash(se178.modify0(p_partkey));
                  HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map_0::IdxNode* n120 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map_0::IdxNode*>(i120->slice(se178, h48));
                  MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry* e120;
                 
                  if (n120 && (e120 = n120->obj)) {
                    do {                
                      long o_custkey = e120->O_CUSTKEY;
                      long total_o_year = e120->TOTAL_O_YEAR;
                      DOUBLE_TYPE v120 = e120->__av;
                      MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2.addOrDelOnZero(se177.modify(o_custkey,total_o_year),(v119 * v120));
                      n120 = n120->nxt;
                    } while (n120 && (e120 = n120->obj) && h48 == n120->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey0_idxfn::equals(se178, *e120)); 
                  }
                }
              n119 = n119->nxt;
            }
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHAREPART1_map_0* i121 = static_cast<HashIndex_MKT_SHAREPART1_map_0*>(MKT_SHAREPART1.index[0]);
          HashIndex_MKT_SHAREPART1_map_0::IdxNode* n121; 
          MKT_SHAREPART1_entry* e121;
        
          for (size_t i = 0; i < i121->size_; i++)
          {
            n121 = i121->buckets_ + i;
            while (n121 && (e121 = n121->obj))
            {
                date o_orderdate = e121->O_ORDERDATE;
                DOUBLE_TYPE v121 = e121->__av;
                long l13 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg10 = 0.0;
                DOUBLE_TYPE l15 = MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se180.modify(l13));
                agg10 += Ulistmax(1L, l15);
                DOUBLE_TYPE l14 = agg10;
                MKT_SHARE.addOrDelOnZero(se179.modify(l13),(v121 * Udiv(l14)));
              n121 = n121->nxt;
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

        MKT_SHAREORDERS1CUSTOMER1_DELTA.clear();
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
                long v122 = 1L;
                MKT_SHAREORDERS1CUSTOMER1_DELTA.addOrDelOnZero(se181.modify(o_custkey,c_nationkey),v122);
          }        
        }
        {  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i123 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n123; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e123;
        
          for (size_t i = 0; i < i123->size_; i++)
          {
            n123 = i123->buckets_ + i;
            while (n123 && (e123 = n123->obj))
            {
                long o_custkey = e123->O_CUSTKEY;
                long c_nationkey = e123->C_NATIONKEY;
                long v123 = e123->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1_map_0* i124 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1.index[1]);
                  const HASH_RES_t h49 = MKT_SHAREORDERS1CUSTOMER1_P_1_mapkey0_idxfn::hash(se184.modify0(o_custkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1_map_0::IdxNode* n124 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1_map_0::IdxNode*>(i124->slice(se184, h49));
                  MKT_SHAREORDERS1CUSTOMER1_P_1_entry* e124;
                 
                  if (n124 && (e124 = n124->obj)) {
                    do {                
                      long total_o_year = e124->TOTAL_O_YEAR;
                      DOUBLE_TYPE v124 = e124->__av;
                      MKT_SHAREORDERS1.addOrDelOnZero(se182.modify(total_o_year),(v123 * (v124 * MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se183.modify(c_nationkey)))));
                      n124 = n124->nxt;
                    } while (n124 && (e124 = n124->obj) && h49 == n124->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1_mapkey0_idxfn::equals(se184, *e124)); 
                  }
                }
              n123 = n123->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i125 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n125; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e125;
        
          for (size_t i = 0; i < i125->size_; i++)
          {
            n125 = i125->buckets_ + i;
            while (n125 && (e125 = n125->obj))
            {
                long o_custkey = e125->O_CUSTKEY;
                long c_nationkey = e125->C_NATIONKEY;
                long v125 = e125->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_1* i126 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_1*>(MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3.index[2]);
                  const HASH_RES_t h50 = MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey1_idxfn::hash(se187.modify1(o_custkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_1::IdxNode* n126 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map_1::IdxNode*>(i126->slice(se187, h50));
                  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry* e126;
                 
                  if (n126 && (e126 = n126->obj)) {
                    do {                
                      long l_orderkey = e126->L_ORDERKEY;
                      long total_o_year = e126->TOTAL_O_YEAR;
                      long v126 = e126->__av;
                      MKT_SHAREORDERS1LINEITEM1_P_2.addOrDelOnZero(se185.modify(l_orderkey,total_o_year),(v125 * (MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se186.modify(c_nationkey)) * v126)));
                      n126 = n126->nxt;
                    } while (n126 && (e126 = n126->obj) && h50 == n126->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_mapkey1_idxfn::equals(se187, *e126)); 
                  }
                }
              n125 = n125->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i127 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n127; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e127;
        
          for (size_t i = 0; i < i127->size_; i++)
          {
            n127 = i127->buckets_ + i;
            while (n127 && (e127 = n127->obj))
            {
                long o_custkey = e127->O_CUSTKEY;
                long c_nationkey = e127->C_NATIONKEY;
                long v127 = e127->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_1* i128 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_1*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2.index[1]);
                  const HASH_RES_t h51 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey1_idxfn::hash(se190.modify1(o_custkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_1::IdxNode* n128 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_1::IdxNode*>(i128->slice(se190, h51));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry* e128;
                 
                  if (n128 && (e128 = n128->obj)) {
                    do {                
                      long s_suppkey = e128->S_SUPPKEY;
                      long total_o_year = e128->TOTAL_O_YEAR;
                      DOUBLE_TYPE v128 = e128->__av;
                      MKT_SHAREORDERS1SUPPLIER1_P_1.addOrDelOnZero(se188.modify(s_suppkey,total_o_year),(v127 * (MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se189.modify(c_nationkey)) * v128)));
                      n128 = n128->nxt;
                    } while (n128 && (e128 = n128->obj) && h51 == n128->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey1_idxfn::equals(se190, *e128)); 
                  }
                }
              n127 = n127->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i129 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n129; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e129;
        
          for (size_t i = 0; i < i129->size_; i++)
          {
            n129 = i129->buckets_ + i;
            while (n129 && (e129 = n129->obj))
            {
                long o_custkey = e129->O_CUSTKEY;
                long c_nationkey = e129->C_NATIONKEY;
                long v129 = e129->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_2* i130 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_2*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1.index[2]);
                  const HASH_RES_t h52 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey2_idxfn::hash(se193.modify2(o_custkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_2::IdxNode* n130 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_2::IdxNode*>(i130->slice(se193, h52));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry* e130;
                 
                  if (n130 && (e130 = n130->obj)) {
                    do {                
                      long p_partkey = e130->P_PARTKEY;
                      long s_suppkey = e130->S_SUPPKEY;
                      long total_o_year = e130->TOTAL_O_YEAR;
                      DOUBLE_TYPE v130 = e130->__av;
                      MKT_SHAREORDERS1SUPPLIER1_P_1PART1.addOrDelOnZero(se191.modify(p_partkey,s_suppkey,total_o_year),(v129 * (MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se192.modify(c_nationkey)) * v130)));
                      n130 = n130->nxt;
                    } while (n130 && (e130 = n130->obj) && h52 == n130->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey2_idxfn::equals(se193, *e130)); 
                  }
                }
              n129 = n129->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i131 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n131; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e131;
        
          for (size_t i = 0; i < i131->size_; i++)
          {
            n131 = i131->buckets_ + i;
            while (n131 && (e131 = n131->obj))
            {
                long o_custkey = e131->O_CUSTKEY;
                long c_nationkey = e131->C_NATIONKEY;
                long v131 = e131->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map_1* i132 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map_1*>(MKT_SHAREORDERS1CUSTOMER1_P_1PART1.index[2]);
                  const HASH_RES_t h53 = MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey1_idxfn::hash(se196.modify1(o_custkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map_1::IdxNode* n132 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map_1::IdxNode*>(i132->slice(se196, h53));
                  MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry* e132;
                 
                  if (n132 && (e132 = n132->obj)) {
                    do {                
                      long p_partkey = e132->P_PARTKEY;
                      long total_o_year = e132->TOTAL_O_YEAR;
                      DOUBLE_TYPE v132 = e132->__av;
                      MKT_SHAREORDERS1PART1.addOrDelOnZero(se194.modify(p_partkey,total_o_year),(v131 * (v132 * MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se195.modify(c_nationkey)))));
                      n132 = n132->nxt;
                    } while (n132 && (e132 = n132->obj) && h53 == n132->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1PART1_mapkey1_idxfn::equals(se196, *e132)); 
                  }
                }
              n131 = n131->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i133 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n133; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e133;
        
          for (size_t i = 0; i < i133->size_; i++)
          {
            n133 = i133->buckets_ + i;
            while (n133 && (e133 = n133->obj))
            {
                long o_custkey = e133->O_CUSTKEY;
                long c_nationkey = e133->C_NATIONKEY;
                long v133 = e133->__av;
                MKT_SHAREORDERS1_L1_1_L1_2_P_1.addOrDelOnZero(se197.modify(o_custkey),(v133 * MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se198.modify(c_nationkey))));
              n133 = n133->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i134 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n134; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e134;
        
          for (size_t i = 0; i < i134->size_; i++)
          {
            n134 = i134->buckets_ + i;
            while (n134 && (e134 = n134->obj))
            {
                long o_custkey = e134->O_CUSTKEY;
                long c_nationkey = e134->C_NATIONKEY;
                long v134 = e134->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2_map_0* i135 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2_map_0*>(MKT_SHAREPART1CUSTOMER1_P_2.index[1]);
                  const HASH_RES_t h54 = MKT_SHAREPART1CUSTOMER1_P_2_mapkey0_idxfn::hash(se201.modify0(o_custkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2_map_0::IdxNode* n135 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2_map_0::IdxNode*>(i135->slice(se201, h54));
                  MKT_SHAREPART1CUSTOMER1_P_2_entry* e135;
                 
                  if (n135 && (e135 = n135->obj)) {
                    do {                
                      date o_orderdate = e135->O_ORDERDATE;
                      DOUBLE_TYPE v135 = e135->__av;
                      MKT_SHAREPART1.addOrDelOnZero(se199.modify(o_orderdate),(v134 * (MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se200.modify(c_nationkey)) * v135)));
                      n135 = n135->nxt;
                    } while (n135 && (e135 = n135->obj) && h54 == n135->hash &&  MKT_SHAREPART1CUSTOMER1_P_2_mapkey0_idxfn::equals(se201, *e135)); 
                  }
                }
              n134 = n134->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i136 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n136; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e136;
        
          for (size_t i = 0; i < i136->size_; i++)
          {
            n136 = i136->buckets_ + i;
            while (n136 && (e136 = n136->obj))
            {
                long o_custkey = e136->O_CUSTKEY;
                long c_nationkey = e136->C_NATIONKEY;
                long v136 = e136->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_1* i137 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_1*>(MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3.index[2]);
                  const HASH_RES_t h55 = MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey1_idxfn::hash(se204.modify1(o_custkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_1::IdxNode* n137 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map_1::IdxNode*>(i137->slice(se204, h55));
                  MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry* e137;
                 
                  if (n137 && (e137 = n137->obj)) {
                    do {                
                      long l_orderkey = e137->L_ORDERKEY;
                      date o_orderdate = e137->O_ORDERDATE;
                      long v137 = e137->__av;
                      MKT_SHAREPART1LINEITEM1_P_1.addOrDelOnZero(se202.modify(l_orderkey,o_orderdate),(v136 * (MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se203.modify(c_nationkey)) * v137)));
                      n137 = n137->nxt;
                    } while (n137 && (e137 = n137->obj) && h55 == n137->hash &&  MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_mapkey1_idxfn::equals(se204, *e137)); 
                  }
                }
              n136 = n136->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i138 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n138; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e138;
        
          for (size_t i = 0; i < i138->size_; i++)
          {
            n138 = i138->buckets_ + i;
            while (n138 && (e138 = n138->obj))
            {
                long o_custkey = e138->O_CUSTKEY;
                long c_nationkey = e138->C_NATIONKEY;
                long v138 = e138->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map_1* i139 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map_1*>(MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2.index[1]);
                  const HASH_RES_t h56 = MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey1_idxfn::hash(se207.modify1(o_custkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map_1::IdxNode* n139 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map_1::IdxNode*>(i139->slice(se207, h56));
                  MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry* e139;
                 
                  if (n139 && (e139 = n139->obj)) {
                    do {                
                      long s_suppkey = e139->S_SUPPKEY;
                      date o_orderdate = e139->O_ORDERDATE;
                      DOUBLE_TYPE v139 = e139->__av;
                      MKT_SHAREPART1SUPPLIER1_P_1.addOrDelOnZero(se205.modify(s_suppkey,o_orderdate),(v138 * (v139 * MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se206.modify(c_nationkey)))));
                      n139 = n139->nxt;
                    } while (n139 && (e139 = n139->obj) && h56 == n139->hash &&  MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey1_idxfn::equals(se207, *e139)); 
                  }
                }
              n138 = n138->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i140 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n140; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e140;
        
          for (size_t i = 0; i < i140->size_; i++)
          {
            n140 = i140->buckets_ + i;
            while (n140 && (e140 = n140->obj))
            {
                long o_custkey = e140->O_CUSTKEY;
                long c_nationkey = e140->C_NATIONKEY;
                long v140 = e140->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_2* i141 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_2*>(MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1.index[2]);
                  const HASH_RES_t h57 = MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey2_idxfn::hash(se210.modify2(o_custkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_2::IdxNode* n141 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_2::IdxNode*>(i141->slice(se210, h57));
                  MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry* e141;
                 
                  if (n141 && (e141 = n141->obj)) {
                    do {                
                      long p_partkey = e141->P_PARTKEY;
                      long s_suppkey = e141->S_SUPPKEY;
                      date o_orderdate = e141->O_ORDERDATE;
                      DOUBLE_TYPE v141 = e141->__av;
                      MKT_SHAREPART1SUPPLIER1_P_1PART1.addOrDelOnZero(se208.modify(p_partkey,s_suppkey,o_orderdate),(v140 * (MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se209.modify(c_nationkey)) * v141)));
                      n141 = n141->nxt;
                    } while (n141 && (e141 = n141->obj) && h57 == n141->hash &&  MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey2_idxfn::equals(se210, *e141)); 
                  }
                }
              n140 = n140->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i142 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n142; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e142;
        
          for (size_t i = 0; i < i142->size_; i++)
          {
            n142 = i142->buckets_ + i;
            while (n142 && (e142 = n142->obj))
            {
                long o_custkey = e142->O_CUSTKEY;
                long c_nationkey = e142->C_NATIONKEY;
                long v142 = e142->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2PART1_map_1* i143 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2PART1_map_1*>(MKT_SHAREPART1CUSTOMER1_P_2PART1.index[2]);
                  const HASH_RES_t h58 = MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey1_idxfn::hash(se213.modify1(o_custkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2PART1_map_1::IdxNode* n143 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2PART1_map_1::IdxNode*>(i143->slice(se213, h58));
                  MKT_SHAREPART1CUSTOMER1_P_2PART1_entry* e143;
                 
                  if (n143 && (e143 = n143->obj)) {
                    do {                
                      long p_partkey = e143->P_PARTKEY;
                      date o_orderdate = e143->O_ORDERDATE;
                      DOUBLE_TYPE v143 = e143->__av;
                      MKT_SHAREPART1PART1.addOrDelOnZero(se211.modify(p_partkey,o_orderdate),(v142 * (v143 * MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se212.modify(c_nationkey)))));
                      n143 = n143->nxt;
                    } while (n143 && (e143 = n143->obj) && h58 == n143->hash &&  MKT_SHAREPART1CUSTOMER1_P_2PART1_mapkey1_idxfn::equals(se213, *e143)); 
                  }
                }
              n142 = n142->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i144 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n144; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e144;
        
          for (size_t i = 0; i < i144->size_; i++)
          {
            n144 = i144->buckets_ + i;
            while (n144 && (e144 = n144->obj))
            {
                long o_custkey = e144->O_CUSTKEY;
                long c_nationkey = e144->C_NATIONKEY;
                long v144 = e144->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_map_0* i145 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_map_0*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2.index[1]);
                  const HASH_RES_t h59 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_mapkey0_idxfn::hash(se216.modify0(o_custkey));
                  HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_map_0::IdxNode* n145 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_map_0::IdxNode*>(i145->slice(se216, h59));
                  MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry* e145;
                 
                  if (n145 && (e145 = n145->obj)) {
                    do {                
                      long total_o_year = e145->TOTAL_O_YEAR;
                      DOUBLE_TYPE v145 = e145->__av;
                      MKT_SHAREPART1_L2_1_L1_1.addOrDelOnZero(se214.modify(total_o_year),(v144 * (MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se215.modify(c_nationkey)) * v145)));
                      n145 = n145->nxt;
                    } while (n145 && (e145 = n145->obj) && h59 == n145->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_mapkey0_idxfn::equals(se216, *e145)); 
                  }
                }
              n144 = n144->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01* i146 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01*>(MKT_SHAREORDERS1CUSTOMER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1CUSTOMER1_DELTA_map_01::IdxNode* n146; 
          MKT_SHAREORDERS1CUSTOMER1_DELTA_entry* e146;
        
          for (size_t i = 0; i < i146->size_; i++)
          {
            n146 = i146->buckets_ + i;
            while (n146 && (e146 = n146->obj))
            {
                long o_custkey = e146->O_CUSTKEY;
                long c_nationkey = e146->C_NATIONKEY;
                long v146 = e146->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map_1* i147 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map_1*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1.index[2]);
                  const HASH_RES_t h60 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey1_idxfn::hash(se219.modify1(o_custkey));
                  HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map_1::IdxNode* n147 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map_1::IdxNode*>(i147->slice(se219, h60));
                  MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry* e147;
                 
                  if (n147 && (e147 = n147->obj)) {
                    do {                
                      long p_partkey = e147->P_PARTKEY;
                      long total_o_year = e147->TOTAL_O_YEAR;
                      DOUBLE_TYPE v147 = e147->__av;
                      MKT_SHAREPART1_L2_1_L1_1PART1.addOrDelOnZero(se217.modify(p_partkey,total_o_year),(v146 * (MKT_SHAREORDERS1CUSTOMER1_P_2.getValueOrDefault(se218.modify(c_nationkey)) * v147)));
                      n147 = n147->nxt;
                    } while (n147 && (e147 = n147->obj) && h60 == n147->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_mapkey1_idxfn::equals(se219, *e147)); 
                  }
                }
              n146 = n146->nxt;
            }
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHAREPART1_map_0* i148 = static_cast<HashIndex_MKT_SHAREPART1_map_0*>(MKT_SHAREPART1.index[0]);
          HashIndex_MKT_SHAREPART1_map_0::IdxNode* n148; 
          MKT_SHAREPART1_entry* e148;
        
          for (size_t i = 0; i < i148->size_; i++)
          {
            n148 = i148->buckets_ + i;
            while (n148 && (e148 = n148->obj))
            {
                date o_orderdate = e148->O_ORDERDATE;
                DOUBLE_TYPE v148 = e148->__av;
                long l16 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg11 = 0.0;
                DOUBLE_TYPE l18 = MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se221.modify(l16));
                agg11 += Ulistmax(1L, l18);
                DOUBLE_TYPE l17 = agg11;
                MKT_SHARE.addOrDelOnZero(se220.modify(l16),(v148 * Udiv(l17)));
              n148 = n148->nxt;
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


        MKT_SHAREORDERS1SUPPLIER1_DELTA.clear();
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
                long v149 = 1L;
                MKT_SHAREORDERS1SUPPLIER1_DELTA.addOrDelOnZero(se222.modify(s_suppkey,s_nationkey),v149);
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i150 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n150; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e150;
        
          for (size_t i = 0; i < i150->size_; i++)
          {
            n150 = i150->buckets_ + i;
            while (n150 && (e150 = n150->obj))
            {
                long s_suppkey = e150->S_SUPPKEY;
                long s_nationkey = e150->S_NATIONKEY;
                long v150 = e150->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1_map_0* i151 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1_map_0*>(MKT_SHAREORDERS1SUPPLIER1_P_1.index[1]);
                  const HASH_RES_t h61 = MKT_SHAREORDERS1SUPPLIER1_P_1_mapkey0_idxfn::hash(se225.modify0(s_suppkey));
                  HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1_map_0::IdxNode* n151 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1_map_0::IdxNode*>(i151->slice(se225, h61));
                  MKT_SHAREORDERS1SUPPLIER1_P_1_entry* e151;
                 
                  if (n151 && (e151 = n151->obj)) {
                    do {                
                      long total_o_year = e151->TOTAL_O_YEAR;
                      DOUBLE_TYPE v151 = e151->__av;
                      MKT_SHAREORDERS1.addOrDelOnZero(se223.modify(total_o_year),(v150 * (v151 * MKT_SHAREORDERS1SUPPLIER1_P_2.getValueOrDefault(se224.modify(s_nationkey)))));
                      n151 = n151->nxt;
                    } while (n151 && (e151 = n151->obj) && h61 == n151->hash &&  MKT_SHAREORDERS1SUPPLIER1_P_1_mapkey0_idxfn::equals(se225, *e151)); 
                  }
                }
              n150 = n150->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i152 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n152; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e152;
        
          for (size_t i = 0; i < i152->size_; i++)
          {
            n152 = i152->buckets_ + i;
            while (n152 && (e152 = n152->obj))
            {
                long s_suppkey = e152->S_SUPPKEY;
                long s_nationkey = e152->S_NATIONKEY;
                long v152 = e152->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_0* i153 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2.index[2]);
                  const HASH_RES_t h62 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey0_idxfn::hash(se228.modify0(s_suppkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_0::IdxNode* n153 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_0::IdxNode*>(i153->slice(se228, h62));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry* e153;
                 
                  if (n153 && (e153 = n153->obj)) {
                    do {                
                      long o_custkey = e153->O_CUSTKEY;
                      long total_o_year = e153->TOTAL_O_YEAR;
                      DOUBLE_TYPE v153 = e153->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1.addOrDelOnZero(se226.modify(o_custkey,total_o_year),(v152 * (MKT_SHAREORDERS1SUPPLIER1_P_2.getValueOrDefault(se227.modify(s_nationkey)) * v153)));
                      n153 = n153->nxt;
                    } while (n153 && (e153 = n153->obj) && h62 == n153->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey0_idxfn::equals(se228, *e153)); 
                  }
                }
              n152 = n152->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i154 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n154; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e154;
        
          for (size_t i = 0; i < i154->size_; i++)
          {
            n154 = i154->buckets_ + i;
            while (n154 && (e154 = n154->obj))
            {
                long s_suppkey = e154->S_SUPPKEY;
                long s_nationkey = e154->S_NATIONKEY;
                long v154 = e154->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_1* i155 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_1*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1.index[3]);
                  const HASH_RES_t h63 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey1_idxfn::hash(se231.modify1(s_suppkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_1::IdxNode* n155 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_1::IdxNode*>(i155->slice(se231, h63));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry* e155;
                 
                  if (n155 && (e155 = n155->obj)) {
                    do {                
                      long p_partkey = e155->P_PARTKEY;
                      long o_custkey = e155->O_CUSTKEY;
                      long total_o_year = e155->TOTAL_O_YEAR;
                      DOUBLE_TYPE v155 = e155->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1PART1.addOrDelOnZero(se229.modify(p_partkey,o_custkey,total_o_year),(v154 * (MKT_SHAREORDERS1SUPPLIER1_P_2.getValueOrDefault(se230.modify(s_nationkey)) * v155)));
                      n155 = n155->nxt;
                    } while (n155 && (e155 = n155->obj) && h63 == n155->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey1_idxfn::equals(se231, *e155)); 
                  }
                }
              n154 = n154->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i156 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n156; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e156;
        
          for (size_t i = 0; i < i156->size_; i++)
          {
            n156 = i156->buckets_ + i;
            while (n156 && (e156 = n156->obj))
            {
                long s_suppkey = e156->S_SUPPKEY;
                long s_nationkey = e156->S_NATIONKEY;
                long v156 = e156->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_2* i157 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_2*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1.index[3]);
                  const HASH_RES_t h64 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey2_idxfn::hash(se234.modify2(s_suppkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_2::IdxNode* n157 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_2::IdxNode*>(i157->slice(se234, h64));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry* e157;
                 
                  if (n157 && (e157 = n157->obj)) {
                    do {                
                      long l_orderkey = e157->L_ORDERKEY;
                      long p_partkey = e157->P_PARTKEY;
                      DOUBLE_TYPE v157 = e157->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1.addOrDelOnZero(se232.modify(l_orderkey,p_partkey),(v156 * (MKT_SHAREORDERS1SUPPLIER1_P_2.getValueOrDefault(se233.modify(s_nationkey)) * v157)));
                      n157 = n157->nxt;
                    } while (n157 && (e157 = n157->obj) && h64 == n157->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey2_idxfn::equals(se234, *e157)); 
                  }
                }
              n156 = n156->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i158 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n158; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e158;
        
          for (size_t i = 0; i < i158->size_; i++)
          {
            n158 = i158->buckets_ + i;
            while (n158 && (e158 = n158->obj))
            {
                long s_suppkey = e158->S_SUPPKEY;
                long s_nationkey = e158->S_NATIONKEY;
                long v158 = e158->__av;
                MKT_SHAREORDERS1LINEITEM1_P_3.addOrDelOnZero(se235.modify(s_suppkey),(v158 * MKT_SHAREORDERS1SUPPLIER1_P_2.getValueOrDefault(se236.modify(s_nationkey))));
              n158 = n158->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i159 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n159; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e159;
        
          for (size_t i = 0; i < i159->size_; i++)
          {
            n159 = i159->buckets_ + i;
            while (n159 && (e159 = n159->obj))
            {
                long s_suppkey = e159->S_SUPPKEY;
                long s_nationkey = e159->S_NATIONKEY;
                long v159 = e159->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_1* i160 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_1*>(MKT_SHAREORDERS1SUPPLIER1_P_1PART1.index[2]);
                  const HASH_RES_t h65 = MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey1_idxfn::hash(se239.modify1(s_suppkey));
                  HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_1::IdxNode* n160 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_1::IdxNode*>(i160->slice(se239, h65));
                  MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry* e160;
                 
                  if (n160 && (e160 = n160->obj)) {
                    do {                
                      long p_partkey = e160->P_PARTKEY;
                      long total_o_year = e160->TOTAL_O_YEAR;
                      DOUBLE_TYPE v160 = e160->__av;
                      MKT_SHAREORDERS1PART1.addOrDelOnZero(se237.modify(p_partkey,total_o_year),(v159 * (v160 * MKT_SHAREORDERS1SUPPLIER1_P_2.getValueOrDefault(se238.modify(s_nationkey)))));
                      n160 = n160->nxt;
                    } while (n160 && (e160 = n160->obj) && h65 == n160->hash &&  MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey1_idxfn::equals(se239, *e160)); 
                  }
                }
              n159 = n159->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i161 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n161; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e161;
        
          for (size_t i = 0; i < i161->size_; i++)
          {
            n161 = i161->buckets_ + i;
            while (n161 && (e161 = n161->obj))
            {
                long s_suppkey = e161->S_SUPPKEY;
                long s_nationkey = e161->S_NATIONKEY;
                long v161 = e161->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_1* i162 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_1*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1.index[2]);
                  const HASH_RES_t h66 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey1_idxfn::hash(se242.modify1(s_suppkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_1::IdxNode* n162 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_1::IdxNode*>(i162->slice(se242, h66));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry* e162;
                 
                  if (n162 && (e162 = n162->obj)) {
                    do {                
                      long l_orderkey = e162->L_ORDERKEY;
                      DOUBLE_TYPE v162 = e162->__av;
                      MKT_SHAREORDERS1_L1_1_L1_2_P_2.addOrDelOnZero(se240.modify(l_orderkey),(v161 * (v162 * MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2.getValueOrDefault(se241.modify(s_nationkey)))));
                      n162 = n162->nxt;
                    } while (n162 && (e162 = n162->obj) && h66 == n162->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey1_idxfn::equals(se242, *e162)); 
                  }
                }
              n161 = n161->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i163 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n163; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e163;
        
          for (size_t i = 0; i < i163->size_; i++)
          {
            n163 = i163->buckets_ + i;
            while (n163 && (e163 = n163->obj))
            {
                long s_suppkey = e163->S_SUPPKEY;
                long s_nationkey = e163->S_NATIONKEY;
                long v163 = e163->__av;
                MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2.addOrDelOnZero(se243.modify(s_suppkey),(v163 * MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2.getValueOrDefault(se244.modify(s_nationkey))));
              n163 = n163->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i164 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n164; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e164;
        
          for (size_t i = 0; i < i164->size_; i++)
          {
            n164 = i164->buckets_ + i;
            while (n164 && (e164 = n164->obj))
            {
                long s_suppkey = e164->S_SUPPKEY;
                long s_nationkey = e164->S_NATIONKEY;
                long v164 = e164->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_2* i165 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_2*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1.index[3]);
                  const HASH_RES_t h67 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey2_idxfn::hash(se247.modify2(s_suppkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_2::IdxNode* n165 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map_2::IdxNode*>(i165->slice(se247, h67));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry* e165;
                 
                  if (n165 && (e165 = n165->obj)) {
                    do {                
                      long l_orderkey = e165->L_ORDERKEY;
                      long p_partkey = e165->P_PARTKEY;
                      DOUBLE_TYPE v165 = e165->__av;
                      MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1.addOrDelOnZero(se245.modify(l_orderkey,p_partkey),(v164 * (v165 * MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2.getValueOrDefault(se246.modify(s_nationkey)))));
                      n165 = n165->nxt;
                    } while (n165 && (e165 = n165->obj) && h67 == n165->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_mapkey2_idxfn::equals(se247, *e165)); 
                  }
                }
              n164 = n164->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i166 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n166; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e166;
        
          for (size_t i = 0; i < i166->size_; i++)
          {
            n166 = i166->buckets_ + i;
            while (n166 && (e166 = n166->obj))
            {
                long s_suppkey = e166->S_SUPPKEY;
                long s_nationkey = e166->S_NATIONKEY;
                long v166 = e166->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_1* i167 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_1*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1.index[2]);
                  const HASH_RES_t h68 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey1_idxfn::hash(se250.modify1(s_suppkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_1::IdxNode* n167 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map_1::IdxNode*>(i167->slice(se250, h68));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry* e167;
                 
                  if (n167 && (e167 = n167->obj)) {
                    do {                
                      long l_orderkey = e167->L_ORDERKEY;
                      DOUBLE_TYPE v167 = e167->__av;
                      MKT_SHAREORDERS4_P_1.addOrDelOnZero(se248.modify(l_orderkey),(v166 * (MKT_SHAREORDERS1SUPPLIER1_P_2.getValueOrDefault(se249.modify(s_nationkey)) * v167)));
                      n167 = n167->nxt;
                    } while (n167 && (e167 = n167->obj) && h68 == n167->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_mapkey1_idxfn::equals(se250, *e167)); 
                  }
                }
              n166 = n166->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i168 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n168; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e168;
        
          for (size_t i = 0; i < i168->size_; i++)
          {
            n168 = i168->buckets_ + i;
            while (n168 && (e168 = n168->obj))
            {
                long s_suppkey = e168->S_SUPPKEY;
                long s_nationkey = e168->S_NATIONKEY;
                long v168 = e168->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1SUPPLIER1_P_1_map_0* i169 = static_cast<HashIndex_MKT_SHAREPART1SUPPLIER1_P_1_map_0*>(MKT_SHAREPART1SUPPLIER1_P_1.index[1]);
                  const HASH_RES_t h69 = MKT_SHAREPART1SUPPLIER1_P_1_mapkey0_idxfn::hash(se253.modify0(s_suppkey));
                  HashIndex_MKT_SHAREPART1SUPPLIER1_P_1_map_0::IdxNode* n169 = static_cast<HashIndex_MKT_SHAREPART1SUPPLIER1_P_1_map_0::IdxNode*>(i169->slice(se253, h69));
                  MKT_SHAREPART1SUPPLIER1_P_1_entry* e169;
                 
                  if (n169 && (e169 = n169->obj)) {
                    do {                
                      date o_orderdate = e169->O_ORDERDATE;
                      DOUBLE_TYPE v169 = e169->__av;
                      MKT_SHAREPART1.addOrDelOnZero(se251.modify(o_orderdate),(v168 * (v169 * MKT_SHAREORDERS1SUPPLIER1_P_2.getValueOrDefault(se252.modify(s_nationkey)))));
                      n169 = n169->nxt;
                    } while (n169 && (e169 = n169->obj) && h69 == n169->hash &&  MKT_SHAREPART1SUPPLIER1_P_1_mapkey0_idxfn::equals(se253, *e169)); 
                  }
                }
              n168 = n168->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i170 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n170; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e170;
        
          for (size_t i = 0; i < i170->size_; i++)
          {
            n170 = i170->buckets_ + i;
            while (n170 && (e170 = n170->obj))
            {
                long s_suppkey = e170->S_SUPPKEY;
                long s_nationkey = e170->S_NATIONKEY;
                long v170 = e170->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map_0* i171 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map_0*>(MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2.index[2]);
                  const HASH_RES_t h70 = MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey0_idxfn::hash(se256.modify0(s_suppkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map_0::IdxNode* n171 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map_0::IdxNode*>(i171->slice(se256, h70));
                  MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry* e171;
                 
                  if (n171 && (e171 = n171->obj)) {
                    do {                
                      long o_custkey = e171->O_CUSTKEY;
                      date o_orderdate = e171->O_ORDERDATE;
                      DOUBLE_TYPE v171 = e171->__av;
                      MKT_SHAREPART1CUSTOMER1_P_2.addOrDelOnZero(se254.modify(o_custkey,o_orderdate),(v170 * (MKT_SHAREORDERS1SUPPLIER1_P_2.getValueOrDefault(se255.modify(s_nationkey)) * v171)));
                      n171 = n171->nxt;
                    } while (n171 && (e171 = n171->obj) && h70 == n171->hash &&  MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_mapkey0_idxfn::equals(se256, *e171)); 
                  }
                }
              n170 = n170->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i172 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n172; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e172;
        
          for (size_t i = 0; i < i172->size_; i++)
          {
            n172 = i172->buckets_ + i;
            while (n172 && (e172 = n172->obj))
            {
                long s_suppkey = e172->S_SUPPKEY;
                long s_nationkey = e172->S_NATIONKEY;
                long v172 = e172->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_1* i173 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_1*>(MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1.index[3]);
                  const HASH_RES_t h71 = MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey1_idxfn::hash(se259.modify1(s_suppkey));
                  HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_1::IdxNode* n173 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map_1::IdxNode*>(i173->slice(se259, h71));
                  MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry* e173;
                 
                  if (n173 && (e173 = n173->obj)) {
                    do {                
                      long p_partkey = e173->P_PARTKEY;
                      long o_custkey = e173->O_CUSTKEY;
                      date o_orderdate = e173->O_ORDERDATE;
                      DOUBLE_TYPE v173 = e173->__av;
                      MKT_SHAREPART1CUSTOMER1_P_2PART1.addOrDelOnZero(se257.modify(p_partkey,o_custkey,o_orderdate),(v172 * (MKT_SHAREORDERS1SUPPLIER1_P_2.getValueOrDefault(se258.modify(s_nationkey)) * v173)));
                      n173 = n173->nxt;
                    } while (n173 && (e173 = n173->obj) && h71 == n173->hash &&  MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_mapkey1_idxfn::equals(se259, *e173)); 
                  }
                }
              n172 = n172->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i174 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n174; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e174;
        
          for (size_t i = 0; i < i174->size_; i++)
          {
            n174 = i174->buckets_ + i;
            while (n174 && (e174 = n174->obj))
            {
                long s_suppkey = e174->S_SUPPKEY;
                long s_nationkey = e174->S_NATIONKEY;
                long v174 = e174->__av;
                { //slice 
                  const HashIndex_MKT_SHAREPART1SUPPLIER1_P_1PART1_map_1* i175 = static_cast<HashIndex_MKT_SHAREPART1SUPPLIER1_P_1PART1_map_1*>(MKT_SHAREPART1SUPPLIER1_P_1PART1.index[2]);
                  const HASH_RES_t h72 = MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey1_idxfn::hash(se262.modify1(s_suppkey));
                  HashIndex_MKT_SHAREPART1SUPPLIER1_P_1PART1_map_1::IdxNode* n175 = static_cast<HashIndex_MKT_SHAREPART1SUPPLIER1_P_1PART1_map_1::IdxNode*>(i175->slice(se262, h72));
                  MKT_SHAREPART1SUPPLIER1_P_1PART1_entry* e175;
                 
                  if (n175 && (e175 = n175->obj)) {
                    do {                
                      long p_partkey = e175->P_PARTKEY;
                      date o_orderdate = e175->O_ORDERDATE;
                      DOUBLE_TYPE v175 = e175->__av;
                      MKT_SHAREPART1PART1.addOrDelOnZero(se260.modify(p_partkey,o_orderdate),(v174 * (v175 * MKT_SHAREORDERS1SUPPLIER1_P_2.getValueOrDefault(se261.modify(s_nationkey)))));
                      n175 = n175->nxt;
                    } while (n175 && (e175 = n175->obj) && h72 == n175->hash &&  MKT_SHAREPART1SUPPLIER1_P_1PART1_mapkey1_idxfn::equals(se262, *e175)); 
                  }
                }
              n174 = n174->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i176 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n176; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e176;
        
          for (size_t i = 0; i < i176->size_; i++)
          {
            n176 = i176->buckets_ + i;
            while (n176 && (e176 = n176->obj))
            {
                long s_suppkey = e176->S_SUPPKEY;
                long s_nationkey = e176->S_NATIONKEY;
                long v176 = e176->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1_map_0* i177 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1_map_0*>(MKT_SHAREORDERS1SUPPLIER1_P_1.index[1]);
                  const HASH_RES_t h73 = MKT_SHAREORDERS1SUPPLIER1_P_1_mapkey0_idxfn::hash(se265.modify0(s_suppkey));
                  HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1_map_0::IdxNode* n177 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1_map_0::IdxNode*>(i177->slice(se265, h73));
                  MKT_SHAREORDERS1SUPPLIER1_P_1_entry* e177;
                 
                  if (n177 && (e177 = n177->obj)) {
                    do {                
                      long total_o_year = e177->TOTAL_O_YEAR;
                      DOUBLE_TYPE v177 = e177->__av;
                      MKT_SHAREPART1_L2_1_L1_1.addOrDelOnZero(se263.modify(total_o_year),(v176 * (v177 * MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2.getValueOrDefault(se264.modify(s_nationkey)))));
                      n177 = n177->nxt;
                    } while (n177 && (e177 = n177->obj) && h73 == n177->hash &&  MKT_SHAREORDERS1SUPPLIER1_P_1_mapkey0_idxfn::equals(se265, *e177)); 
                  }
                }
              n176 = n176->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i178 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n178; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e178;
        
          for (size_t i = 0; i < i178->size_; i++)
          {
            n178 = i178->buckets_ + i;
            while (n178 && (e178 = n178->obj))
            {
                long s_suppkey = e178->S_SUPPKEY;
                long s_nationkey = e178->S_NATIONKEY;
                long v178 = e178->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_0* i179 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_0*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2.index[2]);
                  const HASH_RES_t h74 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey0_idxfn::hash(se268.modify0(s_suppkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_0::IdxNode* n179 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map_0::IdxNode*>(i179->slice(se268, h74));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry* e179;
                 
                  if (n179 && (e179 = n179->obj)) {
                    do {                
                      long o_custkey = e179->O_CUSTKEY;
                      long total_o_year = e179->TOTAL_O_YEAR;
                      DOUBLE_TYPE v179 = e179->__av;
                      MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2.addOrDelOnZero(se266.modify(o_custkey,total_o_year),(v178 * (v179 * MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2.getValueOrDefault(se267.modify(s_nationkey)))));
                      n179 = n179->nxt;
                    } while (n179 && (e179 = n179->obj) && h74 == n179->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_mapkey0_idxfn::equals(se268, *e179)); 
                  }
                }
              n178 = n178->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i180 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n180; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e180;
        
          for (size_t i = 0; i < i180->size_; i++)
          {
            n180 = i180->buckets_ + i;
            while (n180 && (e180 = n180->obj))
            {
                long s_suppkey = e180->S_SUPPKEY;
                long s_nationkey = e180->S_NATIONKEY;
                long v180 = e180->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_1* i181 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_1*>(MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1.index[3]);
                  const HASH_RES_t h75 = MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey1_idxfn::hash(se271.modify1(s_suppkey));
                  HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_1::IdxNode* n181 = static_cast<HashIndex_MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map_1::IdxNode*>(i181->slice(se271, h75));
                  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry* e181;
                 
                  if (n181 && (e181 = n181->obj)) {
                    do {                
                      long p_partkey = e181->P_PARTKEY;
                      long o_custkey = e181->O_CUSTKEY;
                      long total_o_year = e181->TOTAL_O_YEAR;
                      DOUBLE_TYPE v181 = e181->__av;
                      MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1.addOrDelOnZero(se269.modify(p_partkey,o_custkey,total_o_year),(v180 * (v181 * MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2.getValueOrDefault(se270.modify(s_nationkey)))));
                      n181 = n181->nxt;
                    } while (n181 && (e181 = n181->obj) && h75 == n181->hash &&  MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_mapkey1_idxfn::equals(se271, *e181)); 
                  }
                }
              n180 = n180->nxt;
            }
          }
        }{  // foreach
          const HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01* i182 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01*>(MKT_SHAREORDERS1SUPPLIER1_DELTA.index[0]);
          HashIndex_MKT_SHAREORDERS1SUPPLIER1_DELTA_map_01::IdxNode* n182; 
          MKT_SHAREORDERS1SUPPLIER1_DELTA_entry* e182;
        
          for (size_t i = 0; i < i182->size_; i++)
          {
            n182 = i182->buckets_ + i;
            while (n182 && (e182 = n182->obj))
            {
                long s_suppkey = e182->S_SUPPKEY;
                long s_nationkey = e182->S_NATIONKEY;
                long v182 = e182->__av;
                { //slice 
                  const HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_1* i183 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_1*>(MKT_SHAREORDERS1SUPPLIER1_P_1PART1.index[2]);
                  const HASH_RES_t h76 = MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey1_idxfn::hash(se274.modify1(s_suppkey));
                  HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_1::IdxNode* n183 = static_cast<HashIndex_MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map_1::IdxNode*>(i183->slice(se274, h76));
                  MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry* e183;
                 
                  if (n183 && (e183 = n183->obj)) {
                    do {                
                      long p_partkey = e183->P_PARTKEY;
                      long total_o_year = e183->TOTAL_O_YEAR;
                      DOUBLE_TYPE v183 = e183->__av;
                      MKT_SHAREPART1_L2_1_L1_1PART1.addOrDelOnZero(se272.modify(p_partkey,total_o_year),(v182 * (v183 * MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2.getValueOrDefault(se273.modify(s_nationkey)))));
                      n183 = n183->nxt;
                    } while (n183 && (e183 = n183->obj) && h76 == n183->hash &&  MKT_SHAREORDERS1SUPPLIER1_P_1PART1_mapkey1_idxfn::equals(se274, *e183)); 
                  }
                }
              n182 = n182->nxt;
            }
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHAREPART1_map_0* i184 = static_cast<HashIndex_MKT_SHAREPART1_map_0*>(MKT_SHAREPART1.index[0]);
          HashIndex_MKT_SHAREPART1_map_0::IdxNode* n184; 
          MKT_SHAREPART1_entry* e184;
        
          for (size_t i = 0; i < i184->size_; i++)
          {
            n184 = i184->buckets_ + i;
            while (n184 && (e184 = n184->obj))
            {
                date o_orderdate = e184->O_ORDERDATE;
                DOUBLE_TYPE v184 = e184->__av;
                long l19 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg12 = 0.0;
                DOUBLE_TYPE l21 = MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se276.modify(l19));
                agg12 += Ulistmax(1L, l21);
                DOUBLE_TYPE l20 = agg12;
                MKT_SHARE.addOrDelOnZero(se275.modify(l19),(v184 * Udiv(l20)));
              n184 = n184->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        MKT_SHAREORDERS1CUSTOMER1_P_2.clear();
        STRING_TYPE l22 = c4;
        {  // foreach
          const HashIndex_NATION_map_0123* i185 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n185; 
          NATION_entry* e185;
        
          for (size_t i = 0; i < i185->size_; i++)
          {
            n185 = i185->buckets_ + i;
            while (n185 && (e185 = n185->obj))
            {
                long c_nationkey = e185->NATION_NATIONKEY;
                STRING_TYPE n1_name = e185->NATION_NAME;
                long n1_regionkey = e185->NATION_REGIONKEY;
                STRING_TYPE n1_comment = e185->NATION_COMMENT;
                long v185 = e185->__av;
                { //slice 
                  const HashIndex_REGION_map_01* i186 = static_cast<HashIndex_REGION_map_01*>(REGION.index[1]);
                  const HASH_RES_t h77 = REGION_mapkey01_idxfn::hash(se278.modify01(n1_regionkey, l22));
                  HashIndex_REGION_map_01::IdxNode* n186 = static_cast<HashIndex_REGION_map_01::IdxNode*>(i186->slice(se278, h77));
                  REGION_entry* e186;
                 
                  if (n186 && (e186 = n186->obj)) {
                    do {                
                      STRING_TYPE r_comment = e186->REGION_COMMENT;
                      long v186 = e186->__av;
                      MKT_SHAREORDERS1CUSTOMER1_P_2.addOrDelOnZero(se277.modify(c_nationkey),(v185 * v186));
                      n186 = n186->nxt;
                    } while (n186 && (e186 = n186->obj) && h77 == n186->hash &&  REGION_mapkey01_idxfn::equals(se278, *e186)); 
                  }
                }
              n185 = n185->nxt;
            }
          }
        }MKT_SHAREORDERS1SUPPLIER1_P_2.clear();
        STRING_TYPE l23 = c5;
        { //slice 
          const HashIndex_NATION_map_1* i187 = static_cast<HashIndex_NATION_map_1*>(NATION.index[1]);
          const HASH_RES_t h78 = NATION_mapkey1_idxfn::hash(se280.modify1(l23));
          HashIndex_NATION_map_1::IdxNode* n187 = static_cast<HashIndex_NATION_map_1::IdxNode*>(i187->slice(se280, h78));
          NATION_entry* e187;
         
          if (n187 && (e187 = n187->obj)) {
            do {                
              long s_nationkey = e187->NATION_NATIONKEY;
              long n2_regionkey = e187->NATION_REGIONKEY;
              STRING_TYPE n2_comment = e187->NATION_COMMENT;
              long v187 = e187->__av;
              MKT_SHAREORDERS1SUPPLIER1_P_2.addOrDelOnZero(se279.modify(s_nationkey),v187);
              n187 = n187->nxt;
            } while (n187 && (e187 = n187->obj) && h78 == n187->hash &&  NATION_mapkey1_idxfn::equals(se280, *e187)); 
          }
        }MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2.clear();
        {  // foreach
          const HashIndex_NATION_map_0123* i188 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n188; 
          NATION_entry* e188;
        
          for (size_t i = 0; i < i188->size_; i++)
          {
            n188 = i188->buckets_ + i;
            while (n188 && (e188 = n188->obj))
            {
                long s_nationkey = e188->NATION_NATIONKEY;
                STRING_TYPE n2_name = e188->NATION_NAME;
                long n2_regionkey = e188->NATION_REGIONKEY;
                STRING_TYPE n2_comment = e188->NATION_COMMENT;
                long v188 = e188->__av;
                MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2.addOrDelOnZero(se281.modify(s_nationkey),v188);
              n188 = n188->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    MKT_SHAREORDERS1LINEITEM1_DELTA_entry se1;
    MKT_SHAREORDERS1_entry se2;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se3;
    MKT_SHAREORDERS1LINEITEM1_P_3_entry se4;
    MKT_SHAREORDERS1LINEITEM1_P_2_entry se5;
    MKT_SHAREORDERS1CUSTOMER1_P_1_entry se6;
    MKT_SHAREORDERS1LINEITEM1_P_3_entry se7;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se8;
    MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry se9;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry se10;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se11;
    MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry se12;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry se13;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se14;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry se15;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry se16;
    MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry se17;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry se18;
    MKT_SHAREORDERS1LINEITEM1_P_3_entry se19;
    MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry se20;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry se21;
    MKT_SHAREORDERS1LINEITEM1_P_3_entry se22;
    MKT_SHAREORDERS1SUPPLIER1_P_1_entry se23;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se24;
    MKT_SHAREORDERS1LINEITEM1_P_2_entry se25;
    MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry se26;
    MKT_SHAREORDERS1LINEITEM1_P_2_entry se27;
    MKT_SHAREORDERS1PART1_entry se28;
    MKT_SHAREORDERS1LINEITEM1_P_3_entry se29;
    MKT_SHAREORDERS1LINEITEM1_P_2_entry se30;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry se31;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se32;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry se33;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry se34;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry se35;
    MKT_SHAREORDERS4_P_1_entry se36;
    MKT_SHAREORDERS1LINEITEM1_P_3_entry se37;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se38;
    MKT_SHAREPART1_entry se39;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se40;
    MKT_SHAREORDERS1LINEITEM1_P_3_entry se41;
    MKT_SHAREPART1LINEITEM1_P_1_entry se42;
    MKT_SHAREPART1CUSTOMER1_P_2_entry se43;
    MKT_SHAREORDERS1LINEITEM1_P_3_entry se44;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se45;
    MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry se46;
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry se47;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se48;
    MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry se49;
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry se50;
    MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry se51;
    MKT_SHAREPART1CUSTOMER1_P_2PART1_entry se52;
    MKT_SHAREORDERS1LINEITEM1_P_3_entry se53;
    MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry se54;
    MKT_SHAREPART1SUPPLIER1_P_1_entry se55;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se56;
    MKT_SHAREPART1LINEITEM1_P_1_entry se57;
    MKT_SHAREPART1SUPPLIER1_P_1PART1_entry se58;
    MKT_SHAREPART1LINEITEM1_P_1_entry se59;
    MKT_SHAREPART1PART1_entry se60;
    MKT_SHAREORDERS1LINEITEM1_P_3_entry se61;
    MKT_SHAREPART1LINEITEM1_P_1_entry se62;
    MKT_SHAREPART1_L2_1_L1_1_entry se63;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se64;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry se65;
    MKT_SHAREORDERS1LINEITEM1_P_2_entry se66;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry se67;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se68;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry se69;
    MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry se70;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry se71;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry se72;
    MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry se73;
    MKT_SHAREPART1_L2_1_L1_1PART1_entry se74;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry se75;
    MKT_SHAREORDERS1LINEITEM1_P_2_entry se76;
    MKT_SHARE_entry se77;
    MKT_SHAREPART1_L2_1_L1_1_entry se78;
    MKT_SHAREORDERS4_DELTA_entry se79;
    MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry se80;
    MKT_SHAREORDERS1_DOMAIN1_entry se81;
    MKT_SHARE_entry se82;
    MKT_SHAREORDERS1_entry se83;
    MKT_SHAREPART1_L2_1_L1_1_entry se84;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se85;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry se86;
    MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry se87;
    MKT_SHAREPART1_L2_1_L1_1_entry se88;
    MKT_SHAREPART1_L2_1_L1_1_entry se89;
    MKT_SHAREORDERS1_L1_1_L1_2_DELTA_entry se90;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se91;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry se92;
    MKT_SHAREORDERS4_P_1_entry se93;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se94;
    MKT_SHAREORDERS1_entry se95;
    MKT_SHAREORDERS4_P_1_entry se96;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se97;
    MKT_SHAREORDERS1CUSTOMER1_P_1_entry se98;
    MKT_SHAREORDERS4_P_1_entry se99;
    MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry se100;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry se101;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry se102;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry se103;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry se104;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry se105;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry se106;
    MKT_SHAREORDERS1LINEITEM1_P_2_entry se107;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se108;
    MKT_SHAREORDERS1SUPPLIER1_P_1_entry se109;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se110;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry se111;
    MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry se112;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se113;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry se114;
    MKT_SHAREORDERS1PART1_entry se115;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se116;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry se117;
    MKT_SHAREPART1_entry se118;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se119;
    MKT_SHAREORDERS4_P_1_entry se120;
    MKT_SHAREPART1CUSTOMER1_P_2_entry se121;
    MKT_SHAREORDERS4_P_1_entry se122;
    MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry se123;
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry se124;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry se125;
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry se126;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry se127;
    MKT_SHAREPART1CUSTOMER1_P_2PART1_entry se128;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry se129;
    MKT_SHAREPART1LINEITEM1_P_1_entry se130;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se131;
    MKT_SHAREPART1SUPPLIER1_P_1_entry se132;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se133;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry se134;
    MKT_SHAREPART1SUPPLIER1_P_1PART1_entry se135;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se136;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry se137;
    MKT_SHAREPART1PART1_entry se138;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se139;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry se140;
    MKT_SHAREPART1_L2_1_L1_1_entry se141;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se142;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry se143;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry se144;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry se145;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry se146;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry se147;
    MKT_SHAREPART1_L2_1_L1_1PART1_entry se148;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se149;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry se150;
    MKT_SHAREORDERS1PART1_DELTA_entry se151;
    MKT_SHAREORDERS1_entry se152;
    MKT_SHAREORDERS1PART1_entry se153;
    MKT_SHAREORDERS1CUSTOMER1_P_1_entry se154;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry se155;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry se156;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry se157;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry se158;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry se159;
    MKT_SHAREORDERS1LINEITEM1_P_1_entry se160;
    MKT_SHAREORDERS1SUPPLIER1_P_1_entry se161;
    MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry se162;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry se163;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry se164;
    MKT_SHAREORDERS4_P_1_entry se165;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry se166;
    MKT_SHAREPART1_entry se167;
    MKT_SHAREPART1PART1_entry se168;
    MKT_SHAREPART1CUSTOMER1_P_2_entry se169;
    MKT_SHAREPART1CUSTOMER1_P_2PART1_entry se170;
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry se171;
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry se172;
    MKT_SHAREPART1SUPPLIER1_P_1_entry se173;
    MKT_SHAREPART1SUPPLIER1_P_1PART1_entry se174;
    MKT_SHAREPART1_L2_1_L1_1_entry se175;
    MKT_SHAREPART1_L2_1_L1_1PART1_entry se176;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry se177;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry se178;
    MKT_SHARE_entry se179;
    MKT_SHAREPART1_L2_1_L1_1_entry se180;
    MKT_SHAREORDERS1CUSTOMER1_DELTA_entry se181;
    MKT_SHAREORDERS1_entry se182;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se183;
    MKT_SHAREORDERS1CUSTOMER1_P_1_entry se184;
    MKT_SHAREORDERS1LINEITEM1_P_2_entry se185;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se186;
    MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_entry se187;
    MKT_SHAREORDERS1SUPPLIER1_P_1_entry se188;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se189;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry se190;
    MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry se191;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se192;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry se193;
    MKT_SHAREORDERS1PART1_entry se194;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se195;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry se196;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_entry se197;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se198;
    MKT_SHAREPART1_entry se199;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se200;
    MKT_SHAREPART1CUSTOMER1_P_2_entry se201;
    MKT_SHAREPART1LINEITEM1_P_1_entry se202;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se203;
    MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_entry se204;
    MKT_SHAREPART1SUPPLIER1_P_1_entry se205;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se206;
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry se207;
    MKT_SHAREPART1SUPPLIER1_P_1PART1_entry se208;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se209;
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry se210;
    MKT_SHAREPART1PART1_entry se211;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se212;
    MKT_SHAREPART1CUSTOMER1_P_2PART1_entry se213;
    MKT_SHAREPART1_L2_1_L1_1_entry se214;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se215;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry se216;
    MKT_SHAREPART1_L2_1_L1_1PART1_entry se217;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se218;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry se219;
    MKT_SHARE_entry se220;
    MKT_SHAREPART1_L2_1_L1_1_entry se221;
    MKT_SHAREORDERS1SUPPLIER1_DELTA_entry se222;
    MKT_SHAREORDERS1_entry se223;
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry se224;
    MKT_SHAREORDERS1SUPPLIER1_P_1_entry se225;
    MKT_SHAREORDERS1CUSTOMER1_P_1_entry se226;
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry se227;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry se228;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1_entry se229;
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry se230;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry se231;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_entry se232;
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry se233;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry se234;
    MKT_SHAREORDERS1LINEITEM1_P_3_entry se235;
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry se236;
    MKT_SHAREORDERS1PART1_entry se237;
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry se238;
    MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry se239;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2_entry se240;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry se241;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry se242;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_entry se243;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry se244;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_entry se245;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry se246;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_entry se247;
    MKT_SHAREORDERS4_P_1_entry se248;
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry se249;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_entry se250;
    MKT_SHAREPART1_entry se251;
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry se252;
    MKT_SHAREPART1SUPPLIER1_P_1_entry se253;
    MKT_SHAREPART1CUSTOMER1_P_2_entry se254;
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry se255;
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_entry se256;
    MKT_SHAREPART1CUSTOMER1_P_2PART1_entry se257;
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry se258;
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_entry se259;
    MKT_SHAREPART1PART1_entry se260;
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry se261;
    MKT_SHAREPART1SUPPLIER1_P_1PART1_entry se262;
    MKT_SHAREPART1_L2_1_L1_1_entry se263;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry se264;
    MKT_SHAREORDERS1SUPPLIER1_P_1_entry se265;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_entry se266;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry se267;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_entry se268;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_entry se269;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry se270;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_entry se271;
    MKT_SHAREPART1_L2_1_L1_1PART1_entry se272;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry se273;
    MKT_SHAREORDERS1SUPPLIER1_P_1PART1_entry se274;
    MKT_SHARE_entry se275;
    MKT_SHAREPART1_L2_1_L1_1_entry se276;
    MKT_SHAREORDERS1CUSTOMER1_P_2_entry se277;
    REGION_entry se278;
    MKT_SHAREORDERS1SUPPLIER1_P_2_entry se279;
    NATION_entry se280;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_entry se281;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REGION_map REGION;
    MKT_SHAREORDERS1_DOMAIN1_map MKT_SHAREORDERS1_DOMAIN1;
    MKT_SHAREORDERS1_map MKT_SHAREORDERS1;
    MKT_SHAREORDERS1CUSTOMER1_DELTA_map MKT_SHAREORDERS1CUSTOMER1_DELTA;
    MKT_SHAREORDERS1CUSTOMER1_P_1_map MKT_SHAREORDERS1CUSTOMER1_P_1;
    MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3_map MKT_SHAREORDERS1CUSTOMER1_P_1LINEITEM1_P_3;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2_map MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1_map MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1_map MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2ORDERS1PART1;
    MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1_map MKT_SHAREORDERS1CUSTOMER1_P_1SUPPLIER1_P_2PART1;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1_map MKT_SHAREORDERS1CUSTOMER1_P_1PART1;
    MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1_map MKT_SHAREORDERS1CUSTOMER1_P_1PART1ORDERS1;
    MKT_SHAREORDERS1CUSTOMER1_P_2_map MKT_SHAREORDERS1CUSTOMER1_P_2;
    MKT_SHAREORDERS1LINEITEM1_DELTA_map MKT_SHAREORDERS1LINEITEM1_DELTA;
    MKT_SHAREORDERS1LINEITEM1_P_1_map MKT_SHAREORDERS1LINEITEM1_P_1;
    MKT_SHAREORDERS1LINEITEM1_P_2_map MKT_SHAREORDERS1LINEITEM1_P_2;
    MKT_SHAREORDERS1LINEITEM1_P_3_map MKT_SHAREORDERS1LINEITEM1_P_3;
    MKT_SHAREORDERS1SUPPLIER1_DELTA_map MKT_SHAREORDERS1SUPPLIER1_DELTA;
    MKT_SHAREORDERS1SUPPLIER1_P_1_map MKT_SHAREORDERS1SUPPLIER1_P_1;
    MKT_SHAREORDERS1SUPPLIER1_P_1PART1_map MKT_SHAREORDERS1SUPPLIER1_P_1PART1;
    MKT_SHAREORDERS1SUPPLIER1_P_2_map MKT_SHAREORDERS1SUPPLIER1_P_2;
    MKT_SHAREORDERS1PART1_DELTA_map MKT_SHAREORDERS1PART1_DELTA;
    MKT_SHAREORDERS1PART1_map MKT_SHAREORDERS1PART1;
    MKT_SHAREORDERS1_L1_1_L1_2_DELTA_map MKT_SHAREORDERS1_L1_1_L1_2_DELTA;
    MKT_SHAREORDERS1_L1_1_L1_2_P_1_map MKT_SHAREORDERS1_L1_1_L1_2_P_1;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2_map MKT_SHAREORDERS1_L1_1_L1_2_P_2;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2_map MKT_SHAREORDERS1_L1_1_L1_2_P_2LINEITEM1_P_2;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2_map MKT_SHAREORDERS1_L1_1_L1_2_P_2SUPPLIER1_P_2;
    MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1_map MKT_SHAREORDERS1_L1_1_L1_2_P_2PART1;
    MKT_SHAREORDERS4_DELTA_map MKT_SHAREORDERS4_DELTA;
    MKT_SHAREORDERS4_P_1_map MKT_SHAREORDERS4_P_1;
    MKT_SHAREPART1_map MKT_SHAREPART1;
    MKT_SHAREPART1CUSTOMER1_P_2_map MKT_SHAREPART1CUSTOMER1_P_2;
    MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3_map MKT_SHAREPART1CUSTOMER1_P_2LINEITEM1_P_3;
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2_map MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2;
    MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1_map MKT_SHAREPART1CUSTOMER1_P_2SUPPLIER1_P_2PART1;
    MKT_SHAREPART1CUSTOMER1_P_2PART1_map MKT_SHAREPART1CUSTOMER1_P_2PART1;
    MKT_SHAREPART1LINEITEM1_P_1_map MKT_SHAREPART1LINEITEM1_P_1;
    MKT_SHAREPART1SUPPLIER1_P_1_map MKT_SHAREPART1SUPPLIER1_P_1;
    MKT_SHAREPART1SUPPLIER1_P_1PART1_map MKT_SHAREPART1SUPPLIER1_P_1PART1;
    MKT_SHAREPART1PART1_map MKT_SHAREPART1PART1;
    MKT_SHAREPART1_L2_1_L1_1_map MKT_SHAREPART1_L2_1_L1_1;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2_map MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1_map MKT_SHAREPART1_L2_1_L1_1CUSTOMER1_P_2PART1;
    MKT_SHAREPART1_L2_1_L1_1PART1_map MKT_SHAREPART1_L2_1_L1_1PART1;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_ORDERS_map DELTA_ORDERS;
    DELTA_PART_map DELTA_PART;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    DELTA_SUPPLIER_map DELTA_SUPPLIER;
    
    /*const static*/ long c2;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c5;
  
  };

}
