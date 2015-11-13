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
  
  struct DELTA_PARTSUPP_entry {
    long partsupp_partkey; long partsupp_suppkey; long partsupp_availqty; DOUBLE_TYPE partsupp_supplycost; STRING_TYPE partsupp_comment; long __av; 
    explicit DELTA_PARTSUPP_entry() { /*partsupp_partkey = 0L; partsupp_suppkey = 0L; partsupp_availqty = 0L; partsupp_supplycost = 0.0; partsupp_comment = ""; __av = 0L; */ }
    explicit DELTA_PARTSUPP_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const long c5) { partsupp_partkey = c0; partsupp_suppkey = c1; partsupp_availqty = c2; partsupp_supplycost = c3; partsupp_comment = c4; __av = c5; }
    DELTA_PARTSUPP_entry(const DELTA_PARTSUPP_entry& other) : partsupp_partkey( other.partsupp_partkey ), partsupp_suppkey( other.partsupp_suppkey ), partsupp_availqty( other.partsupp_availqty ), partsupp_supplycost( other.partsupp_supplycost ), partsupp_comment( other.partsupp_comment ), __av( other.__av ) {}
    FORCE_INLINE DELTA_PARTSUPP_entry& modify(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4) { partsupp_partkey = c0; partsupp_suppkey = c1; partsupp_availqty = c2; partsupp_supplycost = c3; partsupp_comment = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partsupp_partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partsupp_suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partsupp_availqty);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partsupp_supplycost);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partsupp_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_PARTSUPP_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_PARTSUPP_entry& e) {
      size_t h = 0;
      hash_combine(h, e.partsupp_partkey);
      hash_combine(h, e.partsupp_suppkey);
      hash_combine(h, e.partsupp_availqty);
      hash_combine(h, e.partsupp_supplycost);
      hash_combine(h, e.partsupp_comment);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_PARTSUPP_entry& x, const DELTA_PARTSUPP_entry& y) {
      return x.partsupp_partkey == y.partsupp_partkey && x.partsupp_suppkey == y.partsupp_suppkey && x.partsupp_availqty == y.partsupp_availqty && x.partsupp_supplycost == y.partsupp_supplycost && x.partsupp_comment == y.partsupp_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_PARTSUPP_entry,long,
    HashIndex<DELTA_PARTSUPP_entry,long,DELTA_PARTSUPP_mapkey01234_idxfn,true>
  > DELTA_PARTSUPP_map;
  typedef HashIndex<DELTA_PARTSUPP_entry,long,DELTA_PARTSUPP_mapkey01234_idxfn,true> HashIndex_DELTA_PARTSUPP_map_01234;
  
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
  
  struct SUM_PROFIT_entry {
    STRING_TYPE PROFIT_NATION; long PROFIT_O_YEAR; DOUBLE_TYPE __av; 
    explicit SUM_PROFIT_entry() { /*PROFIT_NATION = ""; PROFIT_O_YEAR = 0L; __av = 0.0; */ }
    explicit SUM_PROFIT_entry(const STRING_TYPE& c0, const long c1, const DOUBLE_TYPE c2) { PROFIT_NATION = c0; PROFIT_O_YEAR = c1; __av = c2; }
    SUM_PROFIT_entry(const SUM_PROFIT_entry& other) : PROFIT_NATION( other.PROFIT_NATION ), PROFIT_O_YEAR( other.PROFIT_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFIT_entry& modify(const STRING_TYPE& c0, const long c1) { PROFIT_NATION = c0; PROFIT_O_YEAR = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFIT_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFIT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PROFIT_NATION);
      hash_combine(h, e.PROFIT_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFIT_entry& x, const SUM_PROFIT_entry& y) {
      return x.PROFIT_NATION == y.PROFIT_NATION && x.PROFIT_O_YEAR == y.PROFIT_O_YEAR;
    }
  };
  
  typedef MultiHashMap<SUM_PROFIT_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFIT_entry,DOUBLE_TYPE,SUM_PROFIT_mapkey01_idxfn,true>
  > SUM_PROFIT_map;
  typedef HashIndex<SUM_PROFIT_entry,DOUBLE_TYPE,SUM_PROFIT_mapkey01_idxfn,true> HashIndex_SUM_PROFIT_map_01;
  
  struct SUM_PROFITORDERS11_DOMAIN1_entry {
    long PROFIT_O_YEAR; long __av; 
    explicit SUM_PROFITORDERS11_DOMAIN1_entry() { /*PROFIT_O_YEAR = 0L; __av = 0L; */ }
    explicit SUM_PROFITORDERS11_DOMAIN1_entry(const long c0, const long c1) { PROFIT_O_YEAR = c0; __av = c1; }
    SUM_PROFITORDERS11_DOMAIN1_entry(const SUM_PROFITORDERS11_DOMAIN1_entry& other) : PROFIT_O_YEAR( other.PROFIT_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITORDERS11_DOMAIN1_entry& modify(const long c0) { PROFIT_O_YEAR = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITORDERS11_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PROFIT_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11_DOMAIN1_entry& x, const SUM_PROFITORDERS11_DOMAIN1_entry& y) {
      return x.PROFIT_O_YEAR == y.PROFIT_O_YEAR;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITORDERS11_DOMAIN1_entry,long,
    HashIndex<SUM_PROFITORDERS11_DOMAIN1_entry,long,SUM_PROFITORDERS11_DOMAIN1_mapkey0_idxfn,true>
  > SUM_PROFITORDERS11_DOMAIN1_map;
  typedef HashIndex<SUM_PROFITORDERS11_DOMAIN1_entry,long,SUM_PROFITORDERS11_DOMAIN1_mapkey0_idxfn,true> HashIndex_SUM_PROFITORDERS11_DOMAIN1_map_0;
  
  struct SUM_PROFITORDERS11_DELTA_entry {
    long L_ORDERKEY; long PROFIT_O_YEAR; long __av; 
    explicit SUM_PROFITORDERS11_DELTA_entry() { /*L_ORDERKEY = 0L; PROFIT_O_YEAR = 0L; __av = 0L; */ }
    explicit SUM_PROFITORDERS11_DELTA_entry(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; PROFIT_O_YEAR = c1; __av = c2; }
    SUM_PROFITORDERS11_DELTA_entry(const SUM_PROFITORDERS11_DELTA_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), PROFIT_O_YEAR( other.PROFIT_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITORDERS11_DELTA_entry& modify(const long c0, const long c1) { L_ORDERKEY = c0; PROFIT_O_YEAR = c1;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS11_DELTA_entry& modify1(const long c1) { PROFIT_O_YEAR = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITORDERS11_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.PROFIT_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11_DELTA_entry& x, const SUM_PROFITORDERS11_DELTA_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.PROFIT_O_YEAR == y.PROFIT_O_YEAR;
    }
  };
  
  struct SUM_PROFITORDERS11_DELTA_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PROFIT_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11_DELTA_entry& x, const SUM_PROFITORDERS11_DELTA_entry& y) {
      return x.PROFIT_O_YEAR == y.PROFIT_O_YEAR;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITORDERS11_DELTA_entry,long,
    HashIndex<SUM_PROFITORDERS11_DELTA_entry,long,SUM_PROFITORDERS11_DELTA_mapkey01_idxfn,true>,
    HashIndex<SUM_PROFITORDERS11_DELTA_entry,long,SUM_PROFITORDERS11_DELTA_mapkey1_idxfn,false>
  > SUM_PROFITORDERS11_DELTA_map;
  typedef HashIndex<SUM_PROFITORDERS11_DELTA_entry,long,SUM_PROFITORDERS11_DELTA_mapkey01_idxfn,true> HashIndex_SUM_PROFITORDERS11_DELTA_map_01;
  typedef HashIndex<SUM_PROFITORDERS11_DELTA_entry,long,SUM_PROFITORDERS11_DELTA_mapkey1_idxfn,false> HashIndex_SUM_PROFITORDERS11_DELTA_map_1;
  
  struct SUM_PROFITORDERS11_entry {
    long L_ORDERKEY; STRING_TYPE PROFIT_NATION; DOUBLE_TYPE __av; 
    explicit SUM_PROFITORDERS11_entry() { /*L_ORDERKEY = 0L; PROFIT_NATION = ""; __av = 0.0; */ }
    explicit SUM_PROFITORDERS11_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { L_ORDERKEY = c0; PROFIT_NATION = c1; __av = c2; }
    SUM_PROFITORDERS11_entry(const SUM_PROFITORDERS11_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), PROFIT_NATION( other.PROFIT_NATION ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITORDERS11_entry& modify(const long c0, const STRING_TYPE& c1) { L_ORDERKEY = c0; PROFIT_NATION = c1;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS11_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITORDERS11_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.PROFIT_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11_entry& x, const SUM_PROFITORDERS11_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.PROFIT_NATION == y.PROFIT_NATION;
    }
  };
  
  struct SUM_PROFITORDERS11_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11_entry& x, const SUM_PROFITORDERS11_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITORDERS11_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITORDERS11_entry,DOUBLE_TYPE,SUM_PROFITORDERS11_mapkey01_idxfn,true>,
    HashIndex<SUM_PROFITORDERS11_entry,DOUBLE_TYPE,SUM_PROFITORDERS11_mapkey0_idxfn,false>
  > SUM_PROFITORDERS11_map;
  typedef HashIndex<SUM_PROFITORDERS11_entry,DOUBLE_TYPE,SUM_PROFITORDERS11_mapkey01_idxfn,true> HashIndex_SUM_PROFITORDERS11_map_01;
  typedef HashIndex<SUM_PROFITORDERS11_entry,DOUBLE_TYPE,SUM_PROFITORDERS11_mapkey0_idxfn,false> HashIndex_SUM_PROFITORDERS11_map_0;
  
  struct SUM_PROFITORDERS11PARTSUPP1_P_3_entry {
    long L_ORDERKEY; long P_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit SUM_PROFITORDERS11PARTSUPP1_P_3_entry() { /*L_ORDERKEY = 0L; P_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit SUM_PROFITORDERS11PARTSUPP1_P_3_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2; __av = c3; }
    SUM_PROFITORDERS11PARTSUPP1_P_3_entry(const SUM_PROFITORDERS11PARTSUPP1_P_3_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITORDERS11PARTSUPP1_P_3_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS11PARTSUPP1_P_3_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS11PARTSUPP1_P_3_entry& modify12(const long c1, const long c2) { P_PARTKEY = c1; S_SUPPKEY = c2;  return *this; }
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
  struct SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11PARTSUPP1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11PARTSUPP1_P_3_entry& x, const SUM_PROFITORDERS11PARTSUPP1_P_3_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  struct SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11PARTSUPP1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11PARTSUPP1_P_3_entry& x, const SUM_PROFITORDERS11PARTSUPP1_P_3_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey12_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11PARTSUPP1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11PARTSUPP1_P_3_entry& x, const SUM_PROFITORDERS11PARTSUPP1_P_3_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITORDERS11PARTSUPP1_P_3_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITORDERS11PARTSUPP1_P_3_entry,DOUBLE_TYPE,SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey012_idxfn,true>,
    HashIndex<SUM_PROFITORDERS11PARTSUPP1_P_3_entry,DOUBLE_TYPE,SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey0_idxfn,false>,
    HashIndex<SUM_PROFITORDERS11PARTSUPP1_P_3_entry,DOUBLE_TYPE,SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey12_idxfn,false>
  > SUM_PROFITORDERS11PARTSUPP1_P_3_map;
  typedef HashIndex<SUM_PROFITORDERS11PARTSUPP1_P_3_entry,DOUBLE_TYPE,SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey012_idxfn,true> HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_012;
  typedef HashIndex<SUM_PROFITORDERS11PARTSUPP1_P_3_entry,DOUBLE_TYPE,SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey0_idxfn,false> HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_0;
  typedef HashIndex<SUM_PROFITORDERS11PARTSUPP1_P_3_entry,DOUBLE_TYPE,SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey12_idxfn,false> HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12;
  
  struct SUM_PROFITORDERS11SUPPLIER1_P_1_entry {
    long L_ORDERKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit SUM_PROFITORDERS11SUPPLIER1_P_1_entry() { /*L_ORDERKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit SUM_PROFITORDERS11SUPPLIER1_P_1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { L_ORDERKEY = c0; S_SUPPKEY = c1; __av = c2; }
    SUM_PROFITORDERS11SUPPLIER1_P_1_entry(const SUM_PROFITORDERS11SUPPLIER1_P_1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITORDERS11SUPPLIER1_P_1_entry& modify(const long c0, const long c1) { L_ORDERKEY = c0; S_SUPPKEY = c1;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS11SUPPLIER1_P_1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS11SUPPLIER1_P_1_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
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
  struct SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11SUPPLIER1_P_1_entry& x, const SUM_PROFITORDERS11SUPPLIER1_P_1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  struct SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11SUPPLIER1_P_1_entry& x, const SUM_PROFITORDERS11SUPPLIER1_P_1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11SUPPLIER1_P_1_entry& x, const SUM_PROFITORDERS11SUPPLIER1_P_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITORDERS11SUPPLIER1_P_1_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey01_idxfn,true>,
    HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey0_idxfn,false>,
    HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey1_idxfn,false>
  > SUM_PROFITORDERS11SUPPLIER1_P_1_map;
  typedef HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey01_idxfn,true> HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1_map_01;
  typedef HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey0_idxfn,false> HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1_map_0;
  typedef HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey1_idxfn,false> HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1_map_1;
  
  struct SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry {
    long L_ORDERKEY; long P_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry() { /*L_ORDERKEY = 0L; P_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2; __av = c3; }
    SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry(const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& modify1(const long c1) { P_PARTKEY = c1;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& modify2(const long c2) { S_SUPPKEY = c2;  return *this; }
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
  struct SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& x, const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  struct SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& x, const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& x, const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& x, const SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey012_idxfn,true>,
    HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey0_idxfn,false>,
    HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey1_idxfn,false>,
    HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey2_idxfn,false>
  > SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map;
  typedef HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey012_idxfn,true> HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_012;
  typedef HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey0_idxfn,false> HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_0;
  typedef HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey1_idxfn,false> HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_1;
  typedef HashIndex<SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey2_idxfn,false> HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_2;
  
  struct SUM_PROFITORDERS11PART1_entry {
    long L_ORDERKEY; long P_PARTKEY; STRING_TYPE PROFIT_NATION; DOUBLE_TYPE __av; 
    explicit SUM_PROFITORDERS11PART1_entry() { /*L_ORDERKEY = 0L; P_PARTKEY = 0L; PROFIT_NATION = ""; __av = 0.0; */ }
    explicit SUM_PROFITORDERS11PART1_entry(const long c0, const long c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; P_PARTKEY = c1; PROFIT_NATION = c2; __av = c3; }
    SUM_PROFITORDERS11PART1_entry(const SUM_PROFITORDERS11PART1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), P_PARTKEY( other.P_PARTKEY ), PROFIT_NATION( other.PROFIT_NATION ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITORDERS11PART1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2) { L_ORDERKEY = c0; P_PARTKEY = c1; PROFIT_NATION = c2;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS11PART1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS11PART1_entry& modify1(const long c1) { P_PARTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITORDERS11PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.PROFIT_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11PART1_entry& x, const SUM_PROFITORDERS11PART1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.P_PARTKEY == y.P_PARTKEY && x.PROFIT_NATION == y.PROFIT_NATION;
    }
  };
  
  struct SUM_PROFITORDERS11PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11PART1_entry& x, const SUM_PROFITORDERS11PART1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct SUM_PROFITORDERS11PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS11PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS11PART1_entry& x, const SUM_PROFITORDERS11PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITORDERS11PART1_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITORDERS11PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11PART1_mapkey012_idxfn,true>,
    HashIndex<SUM_PROFITORDERS11PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11PART1_mapkey0_idxfn,false>,
    HashIndex<SUM_PROFITORDERS11PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11PART1_mapkey1_idxfn,false>
  > SUM_PROFITORDERS11PART1_map;
  typedef HashIndex<SUM_PROFITORDERS11PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11PART1_mapkey012_idxfn,true> HashIndex_SUM_PROFITORDERS11PART1_map_012;
  typedef HashIndex<SUM_PROFITORDERS11PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11PART1_mapkey0_idxfn,false> HashIndex_SUM_PROFITORDERS11PART1_map_0;
  typedef HashIndex<SUM_PROFITORDERS11PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS11PART1_mapkey1_idxfn,false> HashIndex_SUM_PROFITORDERS11PART1_map_1;
  
  struct SUM_PROFITORDERS13_entry {
    long L_ORDERKEY; STRING_TYPE PROFIT_NATION; DOUBLE_TYPE __av; 
    explicit SUM_PROFITORDERS13_entry() { /*L_ORDERKEY = 0L; PROFIT_NATION = ""; __av = 0.0; */ }
    explicit SUM_PROFITORDERS13_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { L_ORDERKEY = c0; PROFIT_NATION = c1; __av = c2; }
    SUM_PROFITORDERS13_entry(const SUM_PROFITORDERS13_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), PROFIT_NATION( other.PROFIT_NATION ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITORDERS13_entry& modify(const long c0, const STRING_TYPE& c1) { L_ORDERKEY = c0; PROFIT_NATION = c1;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS13_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITORDERS13_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.PROFIT_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13_entry& x, const SUM_PROFITORDERS13_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.PROFIT_NATION == y.PROFIT_NATION;
    }
  };
  
  struct SUM_PROFITORDERS13_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13_entry& x, const SUM_PROFITORDERS13_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITORDERS13_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITORDERS13_entry,DOUBLE_TYPE,SUM_PROFITORDERS13_mapkey01_idxfn,true>,
    HashIndex<SUM_PROFITORDERS13_entry,DOUBLE_TYPE,SUM_PROFITORDERS13_mapkey0_idxfn,false>
  > SUM_PROFITORDERS13_map;
  typedef HashIndex<SUM_PROFITORDERS13_entry,DOUBLE_TYPE,SUM_PROFITORDERS13_mapkey01_idxfn,true> HashIndex_SUM_PROFITORDERS13_map_01;
  typedef HashIndex<SUM_PROFITORDERS13_entry,DOUBLE_TYPE,SUM_PROFITORDERS13_mapkey0_idxfn,false> HashIndex_SUM_PROFITORDERS13_map_0;
  
  struct SUM_PROFITORDERS13PARTSUPP1_P_3_entry {
    long L_ORDERKEY; long P_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit SUM_PROFITORDERS13PARTSUPP1_P_3_entry() { /*L_ORDERKEY = 0L; P_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit SUM_PROFITORDERS13PARTSUPP1_P_3_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2; __av = c3; }
    SUM_PROFITORDERS13PARTSUPP1_P_3_entry(const SUM_PROFITORDERS13PARTSUPP1_P_3_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITORDERS13PARTSUPP1_P_3_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS13PARTSUPP1_P_3_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS13PARTSUPP1_P_3_entry& modify12(const long c1, const long c2) { P_PARTKEY = c1; S_SUPPKEY = c2;  return *this; }
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
  struct SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13PARTSUPP1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13PARTSUPP1_P_3_entry& x, const SUM_PROFITORDERS13PARTSUPP1_P_3_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  struct SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13PARTSUPP1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13PARTSUPP1_P_3_entry& x, const SUM_PROFITORDERS13PARTSUPP1_P_3_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey12_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13PARTSUPP1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13PARTSUPP1_P_3_entry& x, const SUM_PROFITORDERS13PARTSUPP1_P_3_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITORDERS13PARTSUPP1_P_3_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITORDERS13PARTSUPP1_P_3_entry,DOUBLE_TYPE,SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey012_idxfn,true>,
    HashIndex<SUM_PROFITORDERS13PARTSUPP1_P_3_entry,DOUBLE_TYPE,SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey0_idxfn,false>,
    HashIndex<SUM_PROFITORDERS13PARTSUPP1_P_3_entry,DOUBLE_TYPE,SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey12_idxfn,false>
  > SUM_PROFITORDERS13PARTSUPP1_P_3_map;
  typedef HashIndex<SUM_PROFITORDERS13PARTSUPP1_P_3_entry,DOUBLE_TYPE,SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey012_idxfn,true> HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_012;
  typedef HashIndex<SUM_PROFITORDERS13PARTSUPP1_P_3_entry,DOUBLE_TYPE,SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey0_idxfn,false> HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_0;
  typedef HashIndex<SUM_PROFITORDERS13PARTSUPP1_P_3_entry,DOUBLE_TYPE,SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey12_idxfn,false> HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12;
  
  struct SUM_PROFITORDERS13SUPPLIER1_P_1_entry {
    long L_ORDERKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit SUM_PROFITORDERS13SUPPLIER1_P_1_entry() { /*L_ORDERKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit SUM_PROFITORDERS13SUPPLIER1_P_1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { L_ORDERKEY = c0; S_SUPPKEY = c1; __av = c2; }
    SUM_PROFITORDERS13SUPPLIER1_P_1_entry(const SUM_PROFITORDERS13SUPPLIER1_P_1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITORDERS13SUPPLIER1_P_1_entry& modify(const long c0, const long c1) { L_ORDERKEY = c0; S_SUPPKEY = c1;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS13SUPPLIER1_P_1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS13SUPPLIER1_P_1_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
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
  struct SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13SUPPLIER1_P_1_entry& x, const SUM_PROFITORDERS13SUPPLIER1_P_1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  struct SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13SUPPLIER1_P_1_entry& x, const SUM_PROFITORDERS13SUPPLIER1_P_1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13SUPPLIER1_P_1_entry& x, const SUM_PROFITORDERS13SUPPLIER1_P_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITORDERS13SUPPLIER1_P_1_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey01_idxfn,true>,
    HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey0_idxfn,false>,
    HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey1_idxfn,false>
  > SUM_PROFITORDERS13SUPPLIER1_P_1_map;
  typedef HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey01_idxfn,true> HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1_map_01;
  typedef HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey0_idxfn,false> HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1_map_0;
  typedef HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey1_idxfn,false> HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1_map_1;
  
  struct SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry {
    long L_ORDERKEY; long P_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry() { /*L_ORDERKEY = 0L; P_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2; __av = c3; }
    SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry(const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& modify1(const long c1) { P_PARTKEY = c1;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& modify2(const long c2) { S_SUPPKEY = c2;  return *this; }
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
  struct SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& x, const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  struct SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& x, const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& x, const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& x, const SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey012_idxfn,true>,
    HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey0_idxfn,false>,
    HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey1_idxfn,false>,
    HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey2_idxfn,false>
  > SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map;
  typedef HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey012_idxfn,true> HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_012;
  typedef HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey0_idxfn,false> HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_0;
  typedef HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey1_idxfn,false> HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_1;
  typedef HashIndex<SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey2_idxfn,false> HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_2;
  
  struct SUM_PROFITORDERS13PART1_entry {
    long L_ORDERKEY; long P_PARTKEY; STRING_TYPE PROFIT_NATION; DOUBLE_TYPE __av; 
    explicit SUM_PROFITORDERS13PART1_entry() { /*L_ORDERKEY = 0L; P_PARTKEY = 0L; PROFIT_NATION = ""; __av = 0.0; */ }
    explicit SUM_PROFITORDERS13PART1_entry(const long c0, const long c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; P_PARTKEY = c1; PROFIT_NATION = c2; __av = c3; }
    SUM_PROFITORDERS13PART1_entry(const SUM_PROFITORDERS13PART1_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), P_PARTKEY( other.P_PARTKEY ), PROFIT_NATION( other.PROFIT_NATION ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITORDERS13PART1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2) { L_ORDERKEY = c0; P_PARTKEY = c1; PROFIT_NATION = c2;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS13PART1_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    FORCE_INLINE SUM_PROFITORDERS13PART1_entry& modify1(const long c1) { P_PARTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITORDERS13PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.PROFIT_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13PART1_entry& x, const SUM_PROFITORDERS13PART1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.P_PARTKEY == y.P_PARTKEY && x.PROFIT_NATION == y.PROFIT_NATION;
    }
  };
  
  struct SUM_PROFITORDERS13PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13PART1_entry& x, const SUM_PROFITORDERS13PART1_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  struct SUM_PROFITORDERS13PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITORDERS13PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITORDERS13PART1_entry& x, const SUM_PROFITORDERS13PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITORDERS13PART1_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITORDERS13PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13PART1_mapkey012_idxfn,true>,
    HashIndex<SUM_PROFITORDERS13PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13PART1_mapkey0_idxfn,false>,
    HashIndex<SUM_PROFITORDERS13PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13PART1_mapkey1_idxfn,false>
  > SUM_PROFITORDERS13PART1_map;
  typedef HashIndex<SUM_PROFITORDERS13PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13PART1_mapkey012_idxfn,true> HashIndex_SUM_PROFITORDERS13PART1_map_012;
  typedef HashIndex<SUM_PROFITORDERS13PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13PART1_mapkey0_idxfn,false> HashIndex_SUM_PROFITORDERS13PART1_map_0;
  typedef HashIndex<SUM_PROFITORDERS13PART1_entry,DOUBLE_TYPE,SUM_PROFITORDERS13PART1_mapkey1_idxfn,false> HashIndex_SUM_PROFITORDERS13PART1_map_1;
  
  struct SUM_PROFITPARTSUPP11_DELTA_entry {
    long P_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit SUM_PROFITPARTSUPP11_DELTA_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit SUM_PROFITPARTSUPP11_DELTA_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { P_PARTKEY = c0; S_SUPPKEY = c1; __av = c2; }
    SUM_PROFITPARTSUPP11_DELTA_entry(const SUM_PROFITPARTSUPP11_DELTA_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITPARTSUPP11_DELTA_entry& modify(const long c0, const long c1) { P_PARTKEY = c0; S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITPARTSUPP11_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITPARTSUPP11_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITPARTSUPP11_DELTA_entry& x, const SUM_PROFITPARTSUPP11_DELTA_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITPARTSUPP11_DELTA_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITPARTSUPP11_DELTA_entry,DOUBLE_TYPE,SUM_PROFITPARTSUPP11_DELTA_mapkey01_idxfn,true>
  > SUM_PROFITPARTSUPP11_DELTA_map;
  typedef HashIndex<SUM_PROFITPARTSUPP11_DELTA_entry,DOUBLE_TYPE,SUM_PROFITPARTSUPP11_DELTA_mapkey01_idxfn,true> HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01;
  
  struct SUM_PROFITPARTSUPP11_P_3_entry {
    long P_PARTKEY; long S_SUPPKEY; long PROFIT_O_YEAR; DOUBLE_TYPE __av; 
    explicit SUM_PROFITPARTSUPP11_P_3_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; PROFIT_O_YEAR = 0L; __av = 0.0; */ }
    explicit SUM_PROFITPARTSUPP11_P_3_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { P_PARTKEY = c0; S_SUPPKEY = c1; PROFIT_O_YEAR = c2; __av = c3; }
    SUM_PROFITPARTSUPP11_P_3_entry(const SUM_PROFITPARTSUPP11_P_3_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), PROFIT_O_YEAR( other.PROFIT_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITPARTSUPP11_P_3_entry& modify(const long c0, const long c1, const long c2) { P_PARTKEY = c0; S_SUPPKEY = c1; PROFIT_O_YEAR = c2;  return *this; }
    FORCE_INLINE SUM_PROFITPARTSUPP11_P_3_entry& modify01(const long c0, const long c1) { P_PARTKEY = c0; S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITPARTSUPP11_P_3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITPARTSUPP11_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.PROFIT_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITPARTSUPP11_P_3_entry& x, const SUM_PROFITPARTSUPP11_P_3_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.PROFIT_O_YEAR == y.PROFIT_O_YEAR;
    }
  };
  
  struct SUM_PROFITPARTSUPP11_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITPARTSUPP11_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITPARTSUPP11_P_3_entry& x, const SUM_PROFITPARTSUPP11_P_3_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITPARTSUPP11_P_3_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITPARTSUPP11_P_3_entry,DOUBLE_TYPE,SUM_PROFITPARTSUPP11_P_3_mapkey012_idxfn,true>,
    HashIndex<SUM_PROFITPARTSUPP11_P_3_entry,DOUBLE_TYPE,SUM_PROFITPARTSUPP11_P_3_mapkey01_idxfn,false>
  > SUM_PROFITPARTSUPP11_P_3_map;
  typedef HashIndex<SUM_PROFITPARTSUPP11_P_3_entry,DOUBLE_TYPE,SUM_PROFITPARTSUPP11_P_3_mapkey012_idxfn,true> HashIndex_SUM_PROFITPARTSUPP11_P_3_map_012;
  typedef HashIndex<SUM_PROFITPARTSUPP11_P_3_entry,DOUBLE_TYPE,SUM_PROFITPARTSUPP11_P_3_mapkey01_idxfn,false> HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01;
  
  struct SUM_PROFITPARTSUPP13_DELTA_entry {
    long P_PARTKEY; long S_SUPPKEY; long __av; 
    explicit SUM_PROFITPARTSUPP13_DELTA_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUM_PROFITPARTSUPP13_DELTA_entry(const long c0, const long c1, const long c2) { P_PARTKEY = c0; S_SUPPKEY = c1; __av = c2; }
    SUM_PROFITPARTSUPP13_DELTA_entry(const SUM_PROFITPARTSUPP13_DELTA_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITPARTSUPP13_DELTA_entry& modify(const long c0, const long c1) { P_PARTKEY = c0; S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITPARTSUPP13_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITPARTSUPP13_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITPARTSUPP13_DELTA_entry& x, const SUM_PROFITPARTSUPP13_DELTA_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITPARTSUPP13_DELTA_entry,long,
    HashIndex<SUM_PROFITPARTSUPP13_DELTA_entry,long,SUM_PROFITPARTSUPP13_DELTA_mapkey01_idxfn,true>
  > SUM_PROFITPARTSUPP13_DELTA_map;
  typedef HashIndex<SUM_PROFITPARTSUPP13_DELTA_entry,long,SUM_PROFITPARTSUPP13_DELTA_mapkey01_idxfn,true> HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01;
  
  struct SUM_PROFITPARTSUPP13_P_3_entry {
    long P_PARTKEY; long S_SUPPKEY; long PROFIT_O_YEAR; DOUBLE_TYPE __av; 
    explicit SUM_PROFITPARTSUPP13_P_3_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; PROFIT_O_YEAR = 0L; __av = 0.0; */ }
    explicit SUM_PROFITPARTSUPP13_P_3_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { P_PARTKEY = c0; S_SUPPKEY = c1; PROFIT_O_YEAR = c2; __av = c3; }
    SUM_PROFITPARTSUPP13_P_3_entry(const SUM_PROFITPARTSUPP13_P_3_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), PROFIT_O_YEAR( other.PROFIT_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITPARTSUPP13_P_3_entry& modify(const long c0, const long c1, const long c2) { P_PARTKEY = c0; S_SUPPKEY = c1; PROFIT_O_YEAR = c2;  return *this; }
    FORCE_INLINE SUM_PROFITPARTSUPP13_P_3_entry& modify01(const long c0, const long c1) { P_PARTKEY = c0; S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITPARTSUPP13_P_3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITPARTSUPP13_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.PROFIT_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITPARTSUPP13_P_3_entry& x, const SUM_PROFITPARTSUPP13_P_3_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.PROFIT_O_YEAR == y.PROFIT_O_YEAR;
    }
  };
  
  struct SUM_PROFITPARTSUPP13_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITPARTSUPP13_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITPARTSUPP13_P_3_entry& x, const SUM_PROFITPARTSUPP13_P_3_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITPARTSUPP13_P_3_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITPARTSUPP13_P_3_entry,DOUBLE_TYPE,SUM_PROFITPARTSUPP13_P_3_mapkey012_idxfn,true>,
    HashIndex<SUM_PROFITPARTSUPP13_P_3_entry,DOUBLE_TYPE,SUM_PROFITPARTSUPP13_P_3_mapkey01_idxfn,false>
  > SUM_PROFITPARTSUPP13_P_3_map;
  typedef HashIndex<SUM_PROFITPARTSUPP13_P_3_entry,DOUBLE_TYPE,SUM_PROFITPARTSUPP13_P_3_mapkey012_idxfn,true> HashIndex_SUM_PROFITPARTSUPP13_P_3_map_012;
  typedef HashIndex<SUM_PROFITPARTSUPP13_P_3_entry,DOUBLE_TYPE,SUM_PROFITPARTSUPP13_P_3_mapkey01_idxfn,false> HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01;
  
  struct SUM_PROFITLINEITEM11_DELTA_entry {
    long L_ORDERKEY; long P_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit SUM_PROFITLINEITEM11_DELTA_entry() { /*L_ORDERKEY = 0L; P_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit SUM_PROFITLINEITEM11_DELTA_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2; __av = c3; }
    SUM_PROFITLINEITEM11_DELTA_entry(const SUM_PROFITLINEITEM11_DELTA_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITLINEITEM11_DELTA_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2;  return *this; }
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
  struct SUM_PROFITLINEITEM11_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITLINEITEM11_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITLINEITEM11_DELTA_entry& x, const SUM_PROFITLINEITEM11_DELTA_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITLINEITEM11_DELTA_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITLINEITEM11_DELTA_entry,DOUBLE_TYPE,SUM_PROFITLINEITEM11_DELTA_mapkey012_idxfn,true>
  > SUM_PROFITLINEITEM11_DELTA_map;
  typedef HashIndex<SUM_PROFITLINEITEM11_DELTA_entry,DOUBLE_TYPE,SUM_PROFITLINEITEM11_DELTA_mapkey012_idxfn,true> HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012;
  
  struct SUM_PROFITLINEITEM11_P_1_entry {
    long P_PARTKEY; long __av; 
    explicit SUM_PROFITLINEITEM11_P_1_entry() { /*P_PARTKEY = 0L; __av = 0L; */ }
    explicit SUM_PROFITLINEITEM11_P_1_entry(const long c0, const long c1) { P_PARTKEY = c0; __av = c1; }
    SUM_PROFITLINEITEM11_P_1_entry(const SUM_PROFITLINEITEM11_P_1_entry& other) : P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITLINEITEM11_P_1_entry& modify(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITLINEITEM11_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITLINEITEM11_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITLINEITEM11_P_1_entry& x, const SUM_PROFITLINEITEM11_P_1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITLINEITEM11_P_1_entry,long,
    HashIndex<SUM_PROFITLINEITEM11_P_1_entry,long,SUM_PROFITLINEITEM11_P_1_mapkey0_idxfn,true>
  > SUM_PROFITLINEITEM11_P_1_map;
  typedef HashIndex<SUM_PROFITLINEITEM11_P_1_entry,long,SUM_PROFITLINEITEM11_P_1_mapkey0_idxfn,true> HashIndex_SUM_PROFITLINEITEM11_P_1_map_0;
  
  struct SUM_PROFITLINEITEM11_P_2_entry {
    long S_SUPPKEY; STRING_TYPE PROFIT_NATION; long __av; 
    explicit SUM_PROFITLINEITEM11_P_2_entry() { /*S_SUPPKEY = 0L; PROFIT_NATION = ""; __av = 0L; */ }
    explicit SUM_PROFITLINEITEM11_P_2_entry(const long c0, const STRING_TYPE& c1, const long c2) { S_SUPPKEY = c0; PROFIT_NATION = c1; __av = c2; }
    SUM_PROFITLINEITEM11_P_2_entry(const SUM_PROFITLINEITEM11_P_2_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), PROFIT_NATION( other.PROFIT_NATION ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITLINEITEM11_P_2_entry& modify(const long c0, const STRING_TYPE& c1) { S_SUPPKEY = c0; PROFIT_NATION = c1;  return *this; }
    FORCE_INLINE SUM_PROFITLINEITEM11_P_2_entry& modify0(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITLINEITEM11_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITLINEITEM11_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.PROFIT_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITLINEITEM11_P_2_entry& x, const SUM_PROFITLINEITEM11_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.PROFIT_NATION == y.PROFIT_NATION;
    }
  };
  
  struct SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITLINEITEM11_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITLINEITEM11_P_2_entry& x, const SUM_PROFITLINEITEM11_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITLINEITEM11_P_2_entry,long,
    HashIndex<SUM_PROFITLINEITEM11_P_2_entry,long,SUM_PROFITLINEITEM11_P_2_mapkey01_idxfn,true>,
    HashIndex<SUM_PROFITLINEITEM11_P_2_entry,long,SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn,false>
  > SUM_PROFITLINEITEM11_P_2_map;
  typedef HashIndex<SUM_PROFITLINEITEM11_P_2_entry,long,SUM_PROFITLINEITEM11_P_2_mapkey01_idxfn,true> HashIndex_SUM_PROFITLINEITEM11_P_2_map_01;
  typedef HashIndex<SUM_PROFITLINEITEM11_P_2_entry,long,SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn,false> HashIndex_SUM_PROFITLINEITEM11_P_2_map_0;
  
  struct SUM_PROFITLINEITEM11_P_3_entry {
    long P_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit SUM_PROFITLINEITEM11_P_3_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit SUM_PROFITLINEITEM11_P_3_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { P_PARTKEY = c0; S_SUPPKEY = c1; __av = c2; }
    SUM_PROFITLINEITEM11_P_3_entry(const SUM_PROFITLINEITEM11_P_3_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITLINEITEM11_P_3_entry& modify(const long c0, const long c1) { P_PARTKEY = c0; S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITLINEITEM11_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITLINEITEM11_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITLINEITEM11_P_3_entry& x, const SUM_PROFITLINEITEM11_P_3_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITLINEITEM11_P_3_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITLINEITEM11_P_3_entry,DOUBLE_TYPE,SUM_PROFITLINEITEM11_P_3_mapkey01_idxfn,true>
  > SUM_PROFITLINEITEM11_P_3_map;
  typedef HashIndex<SUM_PROFITLINEITEM11_P_3_entry,DOUBLE_TYPE,SUM_PROFITLINEITEM11_P_3_mapkey01_idxfn,true> HashIndex_SUM_PROFITLINEITEM11_P_3_map_01;
  
  struct SUM_PROFITLINEITEM11_P_4_entry {
    long L_ORDERKEY; long PROFIT_O_YEAR; long __av; 
    explicit SUM_PROFITLINEITEM11_P_4_entry() { /*L_ORDERKEY = 0L; PROFIT_O_YEAR = 0L; __av = 0L; */ }
    explicit SUM_PROFITLINEITEM11_P_4_entry(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; PROFIT_O_YEAR = c1; __av = c2; }
    SUM_PROFITLINEITEM11_P_4_entry(const SUM_PROFITLINEITEM11_P_4_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), PROFIT_O_YEAR( other.PROFIT_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITLINEITEM11_P_4_entry& modify(const long c0, const long c1) { L_ORDERKEY = c0; PROFIT_O_YEAR = c1;  return *this; }
    FORCE_INLINE SUM_PROFITLINEITEM11_P_4_entry& modify0(const long c0) { L_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITLINEITEM11_P_4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITLINEITEM11_P_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.PROFIT_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITLINEITEM11_P_4_entry& x, const SUM_PROFITLINEITEM11_P_4_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.PROFIT_O_YEAR == y.PROFIT_O_YEAR;
    }
  };
  
  struct SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITLINEITEM11_P_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITLINEITEM11_P_4_entry& x, const SUM_PROFITLINEITEM11_P_4_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITLINEITEM11_P_4_entry,long,
    HashIndex<SUM_PROFITLINEITEM11_P_4_entry,long,SUM_PROFITLINEITEM11_P_4_mapkey01_idxfn,true>,
    HashIndex<SUM_PROFITLINEITEM11_P_4_entry,long,SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn,false>
  > SUM_PROFITLINEITEM11_P_4_map;
  typedef HashIndex<SUM_PROFITLINEITEM11_P_4_entry,long,SUM_PROFITLINEITEM11_P_4_mapkey01_idxfn,true> HashIndex_SUM_PROFITLINEITEM11_P_4_map_01;
  typedef HashIndex<SUM_PROFITLINEITEM11_P_4_entry,long,SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn,false> HashIndex_SUM_PROFITLINEITEM11_P_4_map_0;
  
  struct SUM_PROFITLINEITEM13_DELTA_entry {
    long L_ORDERKEY; long P_PARTKEY; long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit SUM_PROFITLINEITEM13_DELTA_entry() { /*L_ORDERKEY = 0L; P_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit SUM_PROFITLINEITEM13_DELTA_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2; __av = c3; }
    SUM_PROFITLINEITEM13_DELTA_entry(const SUM_PROFITLINEITEM13_DELTA_entry& other) : L_ORDERKEY( other.L_ORDERKEY ), P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITLINEITEM13_DELTA_entry& modify(const long c0, const long c1, const long c2) { L_ORDERKEY = c0; P_PARTKEY = c1; S_SUPPKEY = c2;  return *this; }
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
  struct SUM_PROFITLINEITEM13_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITLINEITEM13_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_ORDERKEY);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITLINEITEM13_DELTA_entry& x, const SUM_PROFITLINEITEM13_DELTA_entry& y) {
      return x.L_ORDERKEY == y.L_ORDERKEY && x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITLINEITEM13_DELTA_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITLINEITEM13_DELTA_entry,DOUBLE_TYPE,SUM_PROFITLINEITEM13_DELTA_mapkey012_idxfn,true>
  > SUM_PROFITLINEITEM13_DELTA_map;
  typedef HashIndex<SUM_PROFITLINEITEM13_DELTA_entry,DOUBLE_TYPE,SUM_PROFITLINEITEM13_DELTA_mapkey012_idxfn,true> HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012;
  
  struct SUM_PROFITLINEITEM13_P_3_entry {
    long P_PARTKEY; long S_SUPPKEY; long __av; 
    explicit SUM_PROFITLINEITEM13_P_3_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUM_PROFITLINEITEM13_P_3_entry(const long c0, const long c1, const long c2) { P_PARTKEY = c0; S_SUPPKEY = c1; __av = c2; }
    SUM_PROFITLINEITEM13_P_3_entry(const SUM_PROFITLINEITEM13_P_3_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITLINEITEM13_P_3_entry& modify(const long c0, const long c1) { P_PARTKEY = c0; S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITLINEITEM13_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITLINEITEM13_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITLINEITEM13_P_3_entry& x, const SUM_PROFITLINEITEM13_P_3_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITLINEITEM13_P_3_entry,long,
    HashIndex<SUM_PROFITLINEITEM13_P_3_entry,long,SUM_PROFITLINEITEM13_P_3_mapkey01_idxfn,true>
  > SUM_PROFITLINEITEM13_P_3_map;
  typedef HashIndex<SUM_PROFITLINEITEM13_P_3_entry,long,SUM_PROFITLINEITEM13_P_3_mapkey01_idxfn,true> HashIndex_SUM_PROFITLINEITEM13_P_3_map_01;
  
  struct SUM_PROFITSUPPLIER11_DELTA_entry {
    long S_SUPPKEY; long S_NATIONKEY; long __av; 
    explicit SUM_PROFITSUPPLIER11_DELTA_entry() { /*S_SUPPKEY = 0L; S_NATIONKEY = 0L; __av = 0L; */ }
    explicit SUM_PROFITSUPPLIER11_DELTA_entry(const long c0, const long c1, const long c2) { S_SUPPKEY = c0; S_NATIONKEY = c1; __av = c2; }
    SUM_PROFITSUPPLIER11_DELTA_entry(const SUM_PROFITSUPPLIER11_DELTA_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITSUPPLIER11_DELTA_entry& modify(const long c0, const long c1) { S_SUPPKEY = c0; S_NATIONKEY = c1;  return *this; }
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
  struct SUM_PROFITSUPPLIER11_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER11_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER11_DELTA_entry& x, const SUM_PROFITSUPPLIER11_DELTA_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITSUPPLIER11_DELTA_entry,long,
    HashIndex<SUM_PROFITSUPPLIER11_DELTA_entry,long,SUM_PROFITSUPPLIER11_DELTA_mapkey01_idxfn,true>
  > SUM_PROFITSUPPLIER11_DELTA_map;
  typedef HashIndex<SUM_PROFITSUPPLIER11_DELTA_entry,long,SUM_PROFITSUPPLIER11_DELTA_mapkey01_idxfn,true> HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01;
  
  struct SUM_PROFITSUPPLIER11_P_1_entry {
    long S_SUPPKEY; long PROFIT_O_YEAR; DOUBLE_TYPE __av; 
    explicit SUM_PROFITSUPPLIER11_P_1_entry() { /*S_SUPPKEY = 0L; PROFIT_O_YEAR = 0L; __av = 0.0; */ }
    explicit SUM_PROFITSUPPLIER11_P_1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { S_SUPPKEY = c0; PROFIT_O_YEAR = c1; __av = c2; }
    SUM_PROFITSUPPLIER11_P_1_entry(const SUM_PROFITSUPPLIER11_P_1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), PROFIT_O_YEAR( other.PROFIT_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITSUPPLIER11_P_1_entry& modify(const long c0, const long c1) { S_SUPPKEY = c0; PROFIT_O_YEAR = c1;  return *this; }
    FORCE_INLINE SUM_PROFITSUPPLIER11_P_1_entry& modify0(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITSUPPLIER11_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER11_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.PROFIT_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER11_P_1_entry& x, const SUM_PROFITSUPPLIER11_P_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.PROFIT_O_YEAR == y.PROFIT_O_YEAR;
    }
  };
  
  struct SUM_PROFITSUPPLIER11_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER11_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER11_P_1_entry& x, const SUM_PROFITSUPPLIER11_P_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITSUPPLIER11_P_1_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITSUPPLIER11_P_1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER11_P_1_mapkey01_idxfn,true>,
    HashIndex<SUM_PROFITSUPPLIER11_P_1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER11_P_1_mapkey0_idxfn,false>
  > SUM_PROFITSUPPLIER11_P_1_map;
  typedef HashIndex<SUM_PROFITSUPPLIER11_P_1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER11_P_1_mapkey01_idxfn,true> HashIndex_SUM_PROFITSUPPLIER11_P_1_map_01;
  typedef HashIndex<SUM_PROFITSUPPLIER11_P_1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER11_P_1_mapkey0_idxfn,false> HashIndex_SUM_PROFITSUPPLIER11_P_1_map_0;
  
  struct SUM_PROFITSUPPLIER11_P_1PART1_entry {
    long P_PARTKEY; long S_SUPPKEY; long PROFIT_O_YEAR; DOUBLE_TYPE __av; 
    explicit SUM_PROFITSUPPLIER11_P_1PART1_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; PROFIT_O_YEAR = 0L; __av = 0.0; */ }
    explicit SUM_PROFITSUPPLIER11_P_1PART1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { P_PARTKEY = c0; S_SUPPKEY = c1; PROFIT_O_YEAR = c2; __av = c3; }
    SUM_PROFITSUPPLIER11_P_1PART1_entry(const SUM_PROFITSUPPLIER11_P_1PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), PROFIT_O_YEAR( other.PROFIT_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITSUPPLIER11_P_1PART1_entry& modify(const long c0, const long c1, const long c2) { P_PARTKEY = c0; S_SUPPKEY = c1; PROFIT_O_YEAR = c2;  return *this; }
    FORCE_INLINE SUM_PROFITSUPPLIER11_P_1PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    FORCE_INLINE SUM_PROFITSUPPLIER11_P_1PART1_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITSUPPLIER11_P_1PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER11_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.PROFIT_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER11_P_1PART1_entry& x, const SUM_PROFITSUPPLIER11_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.PROFIT_O_YEAR == y.PROFIT_O_YEAR;
    }
  };
  
  struct SUM_PROFITSUPPLIER11_P_1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER11_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER11_P_1PART1_entry& x, const SUM_PROFITSUPPLIER11_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct SUM_PROFITSUPPLIER11_P_1PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER11_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER11_P_1PART1_entry& x, const SUM_PROFITSUPPLIER11_P_1PART1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITSUPPLIER11_P_1PART1_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITSUPPLIER11_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER11_P_1PART1_mapkey012_idxfn,true>,
    HashIndex<SUM_PROFITSUPPLIER11_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER11_P_1PART1_mapkey0_idxfn,false>,
    HashIndex<SUM_PROFITSUPPLIER11_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER11_P_1PART1_mapkey1_idxfn,false>
  > SUM_PROFITSUPPLIER11_P_1PART1_map;
  typedef HashIndex<SUM_PROFITSUPPLIER11_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER11_P_1PART1_mapkey012_idxfn,true> HashIndex_SUM_PROFITSUPPLIER11_P_1PART1_map_012;
  typedef HashIndex<SUM_PROFITSUPPLIER11_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER11_P_1PART1_mapkey0_idxfn,false> HashIndex_SUM_PROFITSUPPLIER11_P_1PART1_map_0;
  typedef HashIndex<SUM_PROFITSUPPLIER11_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER11_P_1PART1_mapkey1_idxfn,false> HashIndex_SUM_PROFITSUPPLIER11_P_1PART1_map_1;
  
  struct SUM_PROFITSUPPLIER11_P_2_entry {
    long S_NATIONKEY; STRING_TYPE PROFIT_NATION; long __av; 
    explicit SUM_PROFITSUPPLIER11_P_2_entry() { /*S_NATIONKEY = 0L; PROFIT_NATION = ""; __av = 0L; */ }
    explicit SUM_PROFITSUPPLIER11_P_2_entry(const long c0, const STRING_TYPE& c1, const long c2) { S_NATIONKEY = c0; PROFIT_NATION = c1; __av = c2; }
    SUM_PROFITSUPPLIER11_P_2_entry(const SUM_PROFITSUPPLIER11_P_2_entry& other) : S_NATIONKEY( other.S_NATIONKEY ), PROFIT_NATION( other.PROFIT_NATION ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITSUPPLIER11_P_2_entry& modify(const long c0, const STRING_TYPE& c1) { S_NATIONKEY = c0; PROFIT_NATION = c1;  return *this; }
    FORCE_INLINE SUM_PROFITSUPPLIER11_P_2_entry& modify0(const long c0) { S_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITSUPPLIER11_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER11_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      hash_combine(h, e.PROFIT_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER11_P_2_entry& x, const SUM_PROFITSUPPLIER11_P_2_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY && x.PROFIT_NATION == y.PROFIT_NATION;
    }
  };
  
  struct SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER11_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER11_P_2_entry& x, const SUM_PROFITSUPPLIER11_P_2_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITSUPPLIER11_P_2_entry,long,
    HashIndex<SUM_PROFITSUPPLIER11_P_2_entry,long,SUM_PROFITSUPPLIER11_P_2_mapkey01_idxfn,true>,
    HashIndex<SUM_PROFITSUPPLIER11_P_2_entry,long,SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn,false>
  > SUM_PROFITSUPPLIER11_P_2_map;
  typedef HashIndex<SUM_PROFITSUPPLIER11_P_2_entry,long,SUM_PROFITSUPPLIER11_P_2_mapkey01_idxfn,true> HashIndex_SUM_PROFITSUPPLIER11_P_2_map_01;
  typedef HashIndex<SUM_PROFITSUPPLIER11_P_2_entry,long,SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn,false> HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0;
  
  struct SUM_PROFITSUPPLIER13_P_1_entry {
    long S_SUPPKEY; long PROFIT_O_YEAR; DOUBLE_TYPE __av; 
    explicit SUM_PROFITSUPPLIER13_P_1_entry() { /*S_SUPPKEY = 0L; PROFIT_O_YEAR = 0L; __av = 0.0; */ }
    explicit SUM_PROFITSUPPLIER13_P_1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { S_SUPPKEY = c0; PROFIT_O_YEAR = c1; __av = c2; }
    SUM_PROFITSUPPLIER13_P_1_entry(const SUM_PROFITSUPPLIER13_P_1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), PROFIT_O_YEAR( other.PROFIT_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITSUPPLIER13_P_1_entry& modify(const long c0, const long c1) { S_SUPPKEY = c0; PROFIT_O_YEAR = c1;  return *this; }
    FORCE_INLINE SUM_PROFITSUPPLIER13_P_1_entry& modify0(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITSUPPLIER13_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER13_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.PROFIT_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER13_P_1_entry& x, const SUM_PROFITSUPPLIER13_P_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.PROFIT_O_YEAR == y.PROFIT_O_YEAR;
    }
  };
  
  struct SUM_PROFITSUPPLIER13_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER13_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER13_P_1_entry& x, const SUM_PROFITSUPPLIER13_P_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITSUPPLIER13_P_1_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITSUPPLIER13_P_1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER13_P_1_mapkey01_idxfn,true>,
    HashIndex<SUM_PROFITSUPPLIER13_P_1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER13_P_1_mapkey0_idxfn,false>
  > SUM_PROFITSUPPLIER13_P_1_map;
  typedef HashIndex<SUM_PROFITSUPPLIER13_P_1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER13_P_1_mapkey01_idxfn,true> HashIndex_SUM_PROFITSUPPLIER13_P_1_map_01;
  typedef HashIndex<SUM_PROFITSUPPLIER13_P_1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER13_P_1_mapkey0_idxfn,false> HashIndex_SUM_PROFITSUPPLIER13_P_1_map_0;
  
  struct SUM_PROFITSUPPLIER13_P_1PART1_entry {
    long P_PARTKEY; long S_SUPPKEY; long PROFIT_O_YEAR; DOUBLE_TYPE __av; 
    explicit SUM_PROFITSUPPLIER13_P_1PART1_entry() { /*P_PARTKEY = 0L; S_SUPPKEY = 0L; PROFIT_O_YEAR = 0L; __av = 0.0; */ }
    explicit SUM_PROFITSUPPLIER13_P_1PART1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { P_PARTKEY = c0; S_SUPPKEY = c1; PROFIT_O_YEAR = c2; __av = c3; }
    SUM_PROFITSUPPLIER13_P_1PART1_entry(const SUM_PROFITSUPPLIER13_P_1PART1_entry& other) : P_PARTKEY( other.P_PARTKEY ), S_SUPPKEY( other.S_SUPPKEY ), PROFIT_O_YEAR( other.PROFIT_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITSUPPLIER13_P_1PART1_entry& modify(const long c0, const long c1, const long c2) { P_PARTKEY = c0; S_SUPPKEY = c1; PROFIT_O_YEAR = c2;  return *this; }
    FORCE_INLINE SUM_PROFITSUPPLIER13_P_1PART1_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    FORCE_INLINE SUM_PROFITSUPPLIER13_P_1PART1_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITSUPPLIER13_P_1PART1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER13_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.PROFIT_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER13_P_1PART1_entry& x, const SUM_PROFITSUPPLIER13_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.PROFIT_O_YEAR == y.PROFIT_O_YEAR;
    }
  };
  
  struct SUM_PROFITSUPPLIER13_P_1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER13_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER13_P_1PART1_entry& x, const SUM_PROFITSUPPLIER13_P_1PART1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  struct SUM_PROFITSUPPLIER13_P_1PART1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITSUPPLIER13_P_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITSUPPLIER13_P_1PART1_entry& x, const SUM_PROFITSUPPLIER13_P_1PART1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITSUPPLIER13_P_1PART1_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITSUPPLIER13_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER13_P_1PART1_mapkey012_idxfn,true>,
    HashIndex<SUM_PROFITSUPPLIER13_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER13_P_1PART1_mapkey0_idxfn,false>,
    HashIndex<SUM_PROFITSUPPLIER13_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER13_P_1PART1_mapkey1_idxfn,false>
  > SUM_PROFITSUPPLIER13_P_1PART1_map;
  typedef HashIndex<SUM_PROFITSUPPLIER13_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER13_P_1PART1_mapkey012_idxfn,true> HashIndex_SUM_PROFITSUPPLIER13_P_1PART1_map_012;
  typedef HashIndex<SUM_PROFITSUPPLIER13_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER13_P_1PART1_mapkey0_idxfn,false> HashIndex_SUM_PROFITSUPPLIER13_P_1PART1_map_0;
  typedef HashIndex<SUM_PROFITSUPPLIER13_P_1PART1_entry,DOUBLE_TYPE,SUM_PROFITSUPPLIER13_P_1PART1_mapkey1_idxfn,false> HashIndex_SUM_PROFITSUPPLIER13_P_1PART1_map_1;
  
  struct SUM_PROFITPART11_DELTA_entry {
    long P_PARTKEY; long __av; 
    explicit SUM_PROFITPART11_DELTA_entry() { /*P_PARTKEY = 0L; __av = 0L; */ }
    explicit SUM_PROFITPART11_DELTA_entry(const long c0, const long c1) { P_PARTKEY = c0; __av = c1; }
    SUM_PROFITPART11_DELTA_entry(const SUM_PROFITPART11_DELTA_entry& other) : P_PARTKEY( other.P_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITPART11_DELTA_entry& modify(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITPART11_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITPART11_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITPART11_DELTA_entry& x, const SUM_PROFITPART11_DELTA_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITPART11_DELTA_entry,long,
    HashIndex<SUM_PROFITPART11_DELTA_entry,long,SUM_PROFITPART11_DELTA_mapkey0_idxfn,true>
  > SUM_PROFITPART11_DELTA_map;
  typedef HashIndex<SUM_PROFITPART11_DELTA_entry,long,SUM_PROFITPART11_DELTA_mapkey0_idxfn,true> HashIndex_SUM_PROFITPART11_DELTA_map_0;
  
  struct SUM_PROFITPART11_entry {
    long P_PARTKEY; long PROFIT_O_YEAR; STRING_TYPE PROFIT_NATION; DOUBLE_TYPE __av; 
    explicit SUM_PROFITPART11_entry() { /*P_PARTKEY = 0L; PROFIT_O_YEAR = 0L; PROFIT_NATION = ""; __av = 0.0; */ }
    explicit SUM_PROFITPART11_entry(const long c0, const long c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { P_PARTKEY = c0; PROFIT_O_YEAR = c1; PROFIT_NATION = c2; __av = c3; }
    SUM_PROFITPART11_entry(const SUM_PROFITPART11_entry& other) : P_PARTKEY( other.P_PARTKEY ), PROFIT_O_YEAR( other.PROFIT_O_YEAR ), PROFIT_NATION( other.PROFIT_NATION ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITPART11_entry& modify(const long c0, const long c1, const STRING_TYPE& c2) { P_PARTKEY = c0; PROFIT_O_YEAR = c1; PROFIT_NATION = c2;  return *this; }
    FORCE_INLINE SUM_PROFITPART11_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITPART11_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITPART11_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.PROFIT_O_YEAR);
      hash_combine(h, e.PROFIT_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITPART11_entry& x, const SUM_PROFITPART11_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.PROFIT_O_YEAR == y.PROFIT_O_YEAR && x.PROFIT_NATION == y.PROFIT_NATION;
    }
  };
  
  struct SUM_PROFITPART11_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITPART11_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITPART11_entry& x, const SUM_PROFITPART11_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITPART11_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITPART11_entry,DOUBLE_TYPE,SUM_PROFITPART11_mapkey012_idxfn,true>,
    HashIndex<SUM_PROFITPART11_entry,DOUBLE_TYPE,SUM_PROFITPART11_mapkey0_idxfn,false>
  > SUM_PROFITPART11_map;
  typedef HashIndex<SUM_PROFITPART11_entry,DOUBLE_TYPE,SUM_PROFITPART11_mapkey012_idxfn,true> HashIndex_SUM_PROFITPART11_map_012;
  typedef HashIndex<SUM_PROFITPART11_entry,DOUBLE_TYPE,SUM_PROFITPART11_mapkey0_idxfn,false> HashIndex_SUM_PROFITPART11_map_0;
  
  struct SUM_PROFITPART13_entry {
    long P_PARTKEY; long PROFIT_O_YEAR; STRING_TYPE PROFIT_NATION; DOUBLE_TYPE __av; 
    explicit SUM_PROFITPART13_entry() { /*P_PARTKEY = 0L; PROFIT_O_YEAR = 0L; PROFIT_NATION = ""; __av = 0.0; */ }
    explicit SUM_PROFITPART13_entry(const long c0, const long c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { P_PARTKEY = c0; PROFIT_O_YEAR = c1; PROFIT_NATION = c2; __av = c3; }
    SUM_PROFITPART13_entry(const SUM_PROFITPART13_entry& other) : P_PARTKEY( other.P_PARTKEY ), PROFIT_O_YEAR( other.PROFIT_O_YEAR ), PROFIT_NATION( other.PROFIT_NATION ), __av( other.__av ) {}
    FORCE_INLINE SUM_PROFITPART13_entry& modify(const long c0, const long c1, const STRING_TYPE& c2) { P_PARTKEY = c0; PROFIT_O_YEAR = c1; PROFIT_NATION = c2;  return *this; }
    FORCE_INLINE SUM_PROFITPART13_entry& modify0(const long c0) { P_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROFIT_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_PROFITPART13_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITPART13_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.PROFIT_O_YEAR);
      hash_combine(h, e.PROFIT_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITPART13_entry& x, const SUM_PROFITPART13_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.PROFIT_O_YEAR == y.PROFIT_O_YEAR && x.PROFIT_NATION == y.PROFIT_NATION;
    }
  };
  
  struct SUM_PROFITPART13_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_PROFITPART13_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_PROFITPART13_entry& x, const SUM_PROFITPART13_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUM_PROFITPART13_entry,DOUBLE_TYPE,
    HashIndex<SUM_PROFITPART13_entry,DOUBLE_TYPE,SUM_PROFITPART13_mapkey012_idxfn,true>,
    HashIndex<SUM_PROFITPART13_entry,DOUBLE_TYPE,SUM_PROFITPART13_mapkey0_idxfn,false>
  > SUM_PROFITPART13_map;
  typedef HashIndex<SUM_PROFITPART13_entry,DOUBLE_TYPE,SUM_PROFITPART13_mapkey012_idxfn,true> HashIndex_SUM_PROFITPART13_map_012;
  typedef HashIndex<SUM_PROFITPART13_entry,DOUBLE_TYPE,SUM_PROFITPART13_mapkey0_idxfn,false> HashIndex_SUM_PROFITPART13_map_0;
  
  struct tuple2_S_D {
    STRING_TYPE _1; DOUBLE_TYPE __av;
    explicit tuple2_S_D() { }
    explicit tuple2_S_D(const STRING_TYPE& c1, DOUBLE_TYPE c__av=0.0) { _1 = c1; __av = c__av;}
    int operator==(const tuple2_S_D &rhs) const { return ((this->_1==rhs._1)); }
    FORCE_INLINE tuple2_S_D& modify(const STRING_TYPE& c0, DOUBLE_TYPE c__av) { _1 = c0; __av = c__av; return *this; }
    static bool equals(const tuple2_S_D &x, const tuple2_S_D &y) { return ((x._1==y._1)); }
    static long hash(const tuple2_S_D &e) {
      size_t h = 0;
      hash_combine(h, e._1);
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
      const SUM_PROFIT_map& _SUM_PROFIT = get_SUM_PROFIT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(SUM_PROFIT), _SUM_PROFIT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const SUM_PROFIT_map& get_SUM_PROFIT() const {
      return SUM_PROFIT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    SUM_PROFIT_map SUM_PROFIT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), _c1(16U) {
      
      /* regex_t init */
      if(regcomp(&preg1, "^.*green.*$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^.*green.*$/" << endl;
        exit(-1);
      }
    }
  
    ~data_t() {
      regfree(&preg1);
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

        SUM_PROFITLINEITEM13_DELTA.clear();
        SUM_PROFITLINEITEM11_DELTA.clear();        
        {  
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                long l_orderkey = DELTA_LINEITEM.orderkey[i];
                long p_partkey = DELTA_LINEITEM.partkey[i];
                long s_suppkey = DELTA_LINEITEM.suppkey[i];
                long l_linenumber = DELTA_LINEITEM.linenumber[i];
                DOUBLE_TYPE l_quantity = DELTA_LINEITEM.quantity[i];
                DOUBLE_TYPE l_extendedprice = DELTA_LINEITEM.extendedprice[i];
                DOUBLE_TYPE l_discount = DELTA_LINEITEM.discount[i];
                DOUBLE_TYPE l_tax = DELTA_LINEITEM.tax[i];
                STRING_TYPE l_returnflag = DELTA_LINEITEM.returnflag[i];
                STRING_TYPE l_linestatus = DELTA_LINEITEM.linestatus[i];
                date l_shipdate = DELTA_LINEITEM.shipdate[i];
                date l_commitdate = DELTA_LINEITEM.commitdate[i];
                date l_receiptdate = DELTA_LINEITEM.receiptdate[i];
                STRING_TYPE l_shipinstruct = DELTA_LINEITEM.shipinstruct[i];
                STRING_TYPE l_shipmode = DELTA_LINEITEM.shipmode[i];
                STRING_TYPE l_comment = DELTA_LINEITEM.comment[i];
                long v1 = 1L;
                SUM_PROFITLINEITEM13_DELTA.addOrDelOnZero(se1.modify(l_orderkey,p_partkey,s_suppkey),(v1 * (l_extendedprice * (1L + (-1L * l_discount)))));
                long v2 = 1L;
                SUM_PROFITLINEITEM11_DELTA.addOrDelOnZero(se2.modify(l_orderkey,p_partkey,s_suppkey),(v2 * l_quantity));
          }
        }
        {  // foreach
          const HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012* i3 = static_cast<HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012*>(SUM_PROFITLINEITEM11_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012::IdxNode* n3; 
          SUM_PROFITLINEITEM11_DELTA_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long l_orderkey = e3->L_ORDERKEY;
                long p_partkey = e3->P_PARTKEY;
                long s_suppkey = e3->S_SUPPKEY;
                DOUBLE_TYPE v3 = e3->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i4 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h2 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se7.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n4 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i4->slice(se7, h2));
                  SUM_PROFITLINEITEM11_P_2_entry* e4;
                 
                  if (n4 && (e4 = n4->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e4->PROFIT_NATION;
                      long v4 = e4->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITLINEITEM11_P_4_map_0* i5 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0*>(SUM_PROFITLINEITEM11_P_4.index[1]);
                        const HASH_RES_t h1 = SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::hash(se6.modify0(l_orderkey));
                        HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode* n5 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode*>(i5->slice(se6, h1));
                        SUM_PROFITLINEITEM11_P_4_entry* e5;
                       
                        if (n5 && (e5 = n5->obj)) {
                          do {                
                            long profit_o_year = e5->PROFIT_O_YEAR;
                            long v5 = e5->__av;
                            SUM_PROFIT.addOrDelOnZero(se3.modify(profit_nation,profit_o_year),((v3 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se4.modify(p_partkey)) * (v4 * (SUM_PROFITLINEITEM11_P_3.getValueOrDefault(se5.modify(p_partkey,s_suppkey)) * v5)))) * -1L));
                            n5 = n5->nxt;
                          } while (n5 && (e5 = n5->obj) && h1 == n5->hash &&  SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::equals(se6, *e5)); 
                        }
                      }
                      n4 = n4->nxt;
                    } while (n4 && (e4 = n4->obj) && h2 == n4->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se7, *e4)); 
                  }
                }
              n3 = n3->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012* i6 = static_cast<HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012*>(SUM_PROFITLINEITEM13_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012::IdxNode* n6; 
          SUM_PROFITLINEITEM13_DELTA_entry* e6;
        
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
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i7 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h4 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se11.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n7 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i7->slice(se11, h4));
                  SUM_PROFITLINEITEM11_P_2_entry* e7;
                 
                  if (n7 && (e7 = n7->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e7->PROFIT_NATION;
                      long v7 = e7->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITLINEITEM11_P_4_map_0* i8 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0*>(SUM_PROFITLINEITEM11_P_4.index[1]);
                        const HASH_RES_t h3 = SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::hash(se10.modify0(l_orderkey));
                        HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode* n8 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode*>(i8->slice(se10, h3));
                        SUM_PROFITLINEITEM11_P_4_entry* e8;
                       
                        if (n8 && (e8 = n8->obj)) {
                          do {                
                            long profit_o_year = e8->PROFIT_O_YEAR;
                            long v8 = e8->__av;
                            SUM_PROFIT.addOrDelOnZero(se3.modify(profit_nation,profit_o_year),(v6 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se8.modify(p_partkey)) * (v7 * (SUM_PROFITLINEITEM13_P_3.getValueOrDefault(se9.modify(p_partkey,s_suppkey)) * v8)))));
                            n8 = n8->nxt;
                          } while (n8 && (e8 = n8->obj) && h3 == n8->hash &&  SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::equals(se10, *e8)); 
                        }
                      }
                      n7 = n7->nxt;
                    } while (n7 && (e7 = n7->obj) && h4 == n7->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se11, *e7)); 
                  }
                }
              n6 = n6->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012* i9 = static_cast<HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012*>(SUM_PROFITLINEITEM11_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012::IdxNode* n9; 
          SUM_PROFITLINEITEM11_DELTA_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long l_orderkey = e9->L_ORDERKEY;
                long p_partkey = e9->P_PARTKEY;
                long s_suppkey = e9->S_SUPPKEY;
                DOUBLE_TYPE v9 = e9->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i10 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h5 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se15.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n10 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i10->slice(se15, h5));
                  SUM_PROFITLINEITEM11_P_2_entry* e10;
                 
                  if (n10 && (e10 = n10->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e10->PROFIT_NATION;
                      long v10 = e10->__av;
                      SUM_PROFITORDERS11.addOrDelOnZero(se12.modify(l_orderkey,profit_nation),(v9 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se13.modify(p_partkey)) * (v10 * SUM_PROFITLINEITEM11_P_3.getValueOrDefault(se14.modify(p_partkey,s_suppkey))))));
                      n10 = n10->nxt;
                    } while (n10 && (e10 = n10->obj) && h5 == n10->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se15, *e10)); 
                  }
                }
              n9 = n9->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012* i11 = static_cast<HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012*>(SUM_PROFITLINEITEM11_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012::IdxNode* n11; 
          SUM_PROFITLINEITEM11_DELTA_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long l_orderkey = e11->L_ORDERKEY;
                long p_partkey = e11->P_PARTKEY;
                long s_suppkey = e11->S_SUPPKEY;
                DOUBLE_TYPE v11 = e11->__av;
                SUM_PROFITORDERS11PARTSUPP1_P_3.addOrDelOnZero(se16.modify(l_orderkey,p_partkey,s_suppkey),v11);
              n11 = n11->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012* i12 = static_cast<HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012*>(SUM_PROFITLINEITEM11_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012::IdxNode* n12; 
          SUM_PROFITLINEITEM11_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long l_orderkey = e12->L_ORDERKEY;
                long p_partkey = e12->P_PARTKEY;
                long s_suppkey = e12->S_SUPPKEY;
                DOUBLE_TYPE v12 = e12->__av;
                SUM_PROFITORDERS11SUPPLIER1_P_1.addOrDelOnZero(se17.modify(l_orderkey,s_suppkey),(v12 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se18.modify(p_partkey)) * SUM_PROFITLINEITEM11_P_3.getValueOrDefault(se19.modify(p_partkey,s_suppkey)))));
              n12 = n12->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012* i13 = static_cast<HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012*>(SUM_PROFITLINEITEM11_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012::IdxNode* n13; 
          SUM_PROFITLINEITEM11_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long l_orderkey = e13->L_ORDERKEY;
                long p_partkey = e13->P_PARTKEY;
                long s_suppkey = e13->S_SUPPKEY;
                DOUBLE_TYPE v13 = e13->__av;
                SUM_PROFITORDERS11SUPPLIER1_P_1PART1.addOrDelOnZero(se20.modify(l_orderkey,p_partkey,s_suppkey),(v13 * SUM_PROFITLINEITEM11_P_3.getValueOrDefault(se21.modify(p_partkey,s_suppkey))));
              n13 = n13->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012* i14 = static_cast<HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012*>(SUM_PROFITLINEITEM11_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012::IdxNode* n14; 
          SUM_PROFITLINEITEM11_DELTA_entry* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
                long l_orderkey = e14->L_ORDERKEY;
                long p_partkey = e14->P_PARTKEY;
                long s_suppkey = e14->S_SUPPKEY;
                DOUBLE_TYPE v14 = e14->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i15 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h6 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se24.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n15 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i15->slice(se24, h6));
                  SUM_PROFITLINEITEM11_P_2_entry* e15;
                 
                  if (n15 && (e15 = n15->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e15->PROFIT_NATION;
                      long v15 = e15->__av;
                      SUM_PROFITORDERS11PART1.addOrDelOnZero(se22.modify(l_orderkey,p_partkey,profit_nation),(v14 * (v15 * SUM_PROFITLINEITEM11_P_3.getValueOrDefault(se23.modify(p_partkey,s_suppkey)))));
                      n15 = n15->nxt;
                    } while (n15 && (e15 = n15->obj) && h6 == n15->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se24, *e15)); 
                  }
                }
              n14 = n14->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012* i16 = static_cast<HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012*>(SUM_PROFITLINEITEM13_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012::IdxNode* n16; 
          SUM_PROFITLINEITEM13_DELTA_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long l_orderkey = e16->L_ORDERKEY;
                long p_partkey = e16->P_PARTKEY;
                long s_suppkey = e16->S_SUPPKEY;
                DOUBLE_TYPE v16 = e16->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i17 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h7 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se28.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n17 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i17->slice(se28, h7));
                  SUM_PROFITLINEITEM11_P_2_entry* e17;
                 
                  if (n17 && (e17 = n17->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e17->PROFIT_NATION;
                      long v17 = e17->__av;
                      SUM_PROFITORDERS13.addOrDelOnZero(se25.modify(l_orderkey,profit_nation),(v16 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se26.modify(p_partkey)) * (v17 * SUM_PROFITLINEITEM13_P_3.getValueOrDefault(se27.modify(p_partkey,s_suppkey))))));
                      n17 = n17->nxt;
                    } while (n17 && (e17 = n17->obj) && h7 == n17->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se28, *e17)); 
                  }
                }
              n16 = n16->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012* i18 = static_cast<HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012*>(SUM_PROFITLINEITEM13_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012::IdxNode* n18; 
          SUM_PROFITLINEITEM13_DELTA_entry* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
                long l_orderkey = e18->L_ORDERKEY;
                long p_partkey = e18->P_PARTKEY;
                long s_suppkey = e18->S_SUPPKEY;
                DOUBLE_TYPE v18 = e18->__av;
                SUM_PROFITORDERS13PARTSUPP1_P_3.addOrDelOnZero(se29.modify(l_orderkey,p_partkey,s_suppkey),v18);
              n18 = n18->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012* i19 = static_cast<HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012*>(SUM_PROFITLINEITEM13_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012::IdxNode* n19; 
          SUM_PROFITLINEITEM13_DELTA_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long l_orderkey = e19->L_ORDERKEY;
                long p_partkey = e19->P_PARTKEY;
                long s_suppkey = e19->S_SUPPKEY;
                DOUBLE_TYPE v19 = e19->__av;
                SUM_PROFITORDERS13SUPPLIER1_P_1.addOrDelOnZero(se30.modify(l_orderkey,s_suppkey),(v19 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se31.modify(p_partkey)) * SUM_PROFITLINEITEM13_P_3.getValueOrDefault(se32.modify(p_partkey,s_suppkey)))));
              n19 = n19->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012* i20 = static_cast<HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012*>(SUM_PROFITLINEITEM13_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012::IdxNode* n20; 
          SUM_PROFITLINEITEM13_DELTA_entry* e20;
        
          for (size_t i = 0; i < i20->size_; i++)
          {
            n20 = i20->buckets_ + i;
            while (n20 && (e20 = n20->obj))
            {
                long l_orderkey = e20->L_ORDERKEY;
                long p_partkey = e20->P_PARTKEY;
                long s_suppkey = e20->S_SUPPKEY;
                DOUBLE_TYPE v20 = e20->__av;
                SUM_PROFITORDERS13SUPPLIER1_P_1PART1.addOrDelOnZero(se33.modify(l_orderkey,p_partkey,s_suppkey),(v20 * SUM_PROFITLINEITEM13_P_3.getValueOrDefault(se34.modify(p_partkey,s_suppkey))));
              n20 = n20->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012* i21 = static_cast<HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012*>(SUM_PROFITLINEITEM13_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012::IdxNode* n21; 
          SUM_PROFITLINEITEM13_DELTA_entry* e21;
        
          for (size_t i = 0; i < i21->size_; i++)
          {
            n21 = i21->buckets_ + i;
            while (n21 && (e21 = n21->obj))
            {
                long l_orderkey = e21->L_ORDERKEY;
                long p_partkey = e21->P_PARTKEY;
                long s_suppkey = e21->S_SUPPKEY;
                DOUBLE_TYPE v21 = e21->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i22 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h8 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se37.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n22 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i22->slice(se37, h8));
                  SUM_PROFITLINEITEM11_P_2_entry* e22;
                 
                  if (n22 && (e22 = n22->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e22->PROFIT_NATION;
                      long v22 = e22->__av;
                      SUM_PROFITORDERS13PART1.addOrDelOnZero(se35.modify(l_orderkey,p_partkey,profit_nation),(v21 * (v22 * SUM_PROFITLINEITEM13_P_3.getValueOrDefault(se36.modify(p_partkey,s_suppkey)))));
                      n22 = n22->nxt;
                    } while (n22 && (e22 = n22->obj) && h8 == n22->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se37, *e22)); 
                  }
                }
              n21 = n21->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012* i23 = static_cast<HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012*>(SUM_PROFITLINEITEM11_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012::IdxNode* n23; 
          SUM_PROFITLINEITEM11_DELTA_entry* e23;
        
          for (size_t i = 0; i < i23->size_; i++)
          {
            n23 = i23->buckets_ + i;
            while (n23 && (e23 = n23->obj))
            {
                long l_orderkey = e23->L_ORDERKEY;
                long p_partkey = e23->P_PARTKEY;
                long s_suppkey = e23->S_SUPPKEY;
                DOUBLE_TYPE v23 = e23->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_4_map_0* i24 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0*>(SUM_PROFITLINEITEM11_P_4.index[1]);
                  const HASH_RES_t h9 = SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::hash(se39.modify0(l_orderkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode* n24 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode*>(i24->slice(se39, h9));
                  SUM_PROFITLINEITEM11_P_4_entry* e24;
                 
                  if (n24 && (e24 = n24->obj)) {
                    do {                
                      long profit_o_year = e24->PROFIT_O_YEAR;
                      long v24 = e24->__av;
                      SUM_PROFITPARTSUPP11_P_3.addOrDelOnZero(se38.modify(p_partkey,s_suppkey,profit_o_year),(v23 * v24));
                      n24 = n24->nxt;
                    } while (n24 && (e24 = n24->obj) && h9 == n24->hash &&  SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::equals(se39, *e24)); 
                  }
                }
              n23 = n23->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012* i25 = static_cast<HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012*>(SUM_PROFITLINEITEM13_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012::IdxNode* n25; 
          SUM_PROFITLINEITEM13_DELTA_entry* e25;
        
          for (size_t i = 0; i < i25->size_; i++)
          {
            n25 = i25->buckets_ + i;
            while (n25 && (e25 = n25->obj))
            {
                long l_orderkey = e25->L_ORDERKEY;
                long p_partkey = e25->P_PARTKEY;
                long s_suppkey = e25->S_SUPPKEY;
                DOUBLE_TYPE v25 = e25->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_4_map_0* i26 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0*>(SUM_PROFITLINEITEM11_P_4.index[1]);
                  const HASH_RES_t h10 = SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::hash(se41.modify0(l_orderkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode* n26 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode*>(i26->slice(se41, h10));
                  SUM_PROFITLINEITEM11_P_4_entry* e26;
                 
                  if (n26 && (e26 = n26->obj)) {
                    do {                
                      long profit_o_year = e26->PROFIT_O_YEAR;
                      long v26 = e26->__av;
                      SUM_PROFITPARTSUPP13_P_3.addOrDelOnZero(se40.modify(p_partkey,s_suppkey,profit_o_year),(v25 * v26));
                      n26 = n26->nxt;
                    } while (n26 && (e26 = n26->obj) && h10 == n26->hash &&  SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::equals(se41, *e26)); 
                  }
                }
              n25 = n25->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012* i27 = static_cast<HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012*>(SUM_PROFITLINEITEM11_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012::IdxNode* n27; 
          SUM_PROFITLINEITEM11_DELTA_entry* e27;
        
          for (size_t i = 0; i < i27->size_; i++)
          {
            n27 = i27->buckets_ + i;
            while (n27 && (e27 = n27->obj))
            {
                long l_orderkey = e27->L_ORDERKEY;
                long p_partkey = e27->P_PARTKEY;
                long s_suppkey = e27->S_SUPPKEY;
                DOUBLE_TYPE v27 = e27->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_4_map_0* i28 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0*>(SUM_PROFITLINEITEM11_P_4.index[1]);
                  const HASH_RES_t h11 = SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::hash(se45.modify0(l_orderkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode* n28 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode*>(i28->slice(se45, h11));
                  SUM_PROFITLINEITEM11_P_4_entry* e28;
                 
                  if (n28 && (e28 = n28->obj)) {
                    do {                
                      long profit_o_year = e28->PROFIT_O_YEAR;
                      long v28 = e28->__av;
                      SUM_PROFITSUPPLIER11_P_1.addOrDelOnZero(se42.modify(s_suppkey,profit_o_year),(v27 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se43.modify(p_partkey)) * (SUM_PROFITLINEITEM11_P_3.getValueOrDefault(se44.modify(p_partkey,s_suppkey)) * v28))));
                      n28 = n28->nxt;
                    } while (n28 && (e28 = n28->obj) && h11 == n28->hash &&  SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::equals(se45, *e28)); 
                  }
                }
              n27 = n27->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012* i29 = static_cast<HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012*>(SUM_PROFITLINEITEM11_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012::IdxNode* n29; 
          SUM_PROFITLINEITEM11_DELTA_entry* e29;
        
          for (size_t i = 0; i < i29->size_; i++)
          {
            n29 = i29->buckets_ + i;
            while (n29 && (e29 = n29->obj))
            {
                long l_orderkey = e29->L_ORDERKEY;
                long p_partkey = e29->P_PARTKEY;
                long s_suppkey = e29->S_SUPPKEY;
                DOUBLE_TYPE v29 = e29->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_4_map_0* i30 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0*>(SUM_PROFITLINEITEM11_P_4.index[1]);
                  const HASH_RES_t h12 = SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::hash(se48.modify0(l_orderkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode* n30 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode*>(i30->slice(se48, h12));
                  SUM_PROFITLINEITEM11_P_4_entry* e30;
                 
                  if (n30 && (e30 = n30->obj)) {
                    do {                
                      long profit_o_year = e30->PROFIT_O_YEAR;
                      long v30 = e30->__av;
                      SUM_PROFITSUPPLIER11_P_1PART1.addOrDelOnZero(se46.modify(p_partkey,s_suppkey,profit_o_year),(v29 * (SUM_PROFITLINEITEM11_P_3.getValueOrDefault(se47.modify(p_partkey,s_suppkey)) * v30)));
                      n30 = n30->nxt;
                    } while (n30 && (e30 = n30->obj) && h12 == n30->hash &&  SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::equals(se48, *e30)); 
                  }
                }
              n29 = n29->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012* i31 = static_cast<HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012*>(SUM_PROFITLINEITEM13_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012::IdxNode* n31; 
          SUM_PROFITLINEITEM13_DELTA_entry* e31;
        
          for (size_t i = 0; i < i31->size_; i++)
          {
            n31 = i31->buckets_ + i;
            while (n31 && (e31 = n31->obj))
            {
                long l_orderkey = e31->L_ORDERKEY;
                long p_partkey = e31->P_PARTKEY;
                long s_suppkey = e31->S_SUPPKEY;
                DOUBLE_TYPE v31 = e31->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_4_map_0* i32 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0*>(SUM_PROFITLINEITEM11_P_4.index[1]);
                  const HASH_RES_t h13 = SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::hash(se52.modify0(l_orderkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode* n32 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode*>(i32->slice(se52, h13));
                  SUM_PROFITLINEITEM11_P_4_entry* e32;
                 
                  if (n32 && (e32 = n32->obj)) {
                    do {                
                      long profit_o_year = e32->PROFIT_O_YEAR;
                      long v32 = e32->__av;
                      SUM_PROFITSUPPLIER13_P_1.addOrDelOnZero(se49.modify(s_suppkey,profit_o_year),(v31 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se50.modify(p_partkey)) * (SUM_PROFITLINEITEM13_P_3.getValueOrDefault(se51.modify(p_partkey,s_suppkey)) * v32))));
                      n32 = n32->nxt;
                    } while (n32 && (e32 = n32->obj) && h13 == n32->hash &&  SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::equals(se52, *e32)); 
                  }
                }
              n31 = n31->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012* i33 = static_cast<HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012*>(SUM_PROFITLINEITEM13_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012::IdxNode* n33; 
          SUM_PROFITLINEITEM13_DELTA_entry* e33;
        
          for (size_t i = 0; i < i33->size_; i++)
          {
            n33 = i33->buckets_ + i;
            while (n33 && (e33 = n33->obj))
            {
                long l_orderkey = e33->L_ORDERKEY;
                long p_partkey = e33->P_PARTKEY;
                long s_suppkey = e33->S_SUPPKEY;
                DOUBLE_TYPE v33 = e33->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_4_map_0* i34 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0*>(SUM_PROFITLINEITEM11_P_4.index[1]);
                  const HASH_RES_t h14 = SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::hash(se55.modify0(l_orderkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode* n34 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode*>(i34->slice(se55, h14));
                  SUM_PROFITLINEITEM11_P_4_entry* e34;
                 
                  if (n34 && (e34 = n34->obj)) {
                    do {                
                      long profit_o_year = e34->PROFIT_O_YEAR;
                      long v34 = e34->__av;
                      SUM_PROFITSUPPLIER13_P_1PART1.addOrDelOnZero(se53.modify(p_partkey,s_suppkey,profit_o_year),(v33 * (SUM_PROFITLINEITEM13_P_3.getValueOrDefault(se54.modify(p_partkey,s_suppkey)) * v34)));
                      n34 = n34->nxt;
                    } while (n34 && (e34 = n34->obj) && h14 == n34->hash &&  SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::equals(se55, *e34)); 
                  }
                }
              n33 = n33->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012* i35 = static_cast<HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012*>(SUM_PROFITLINEITEM11_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM11_DELTA_map_012::IdxNode* n35; 
          SUM_PROFITLINEITEM11_DELTA_entry* e35;
        
          for (size_t i = 0; i < i35->size_; i++)
          {
            n35 = i35->buckets_ + i;
            while (n35 && (e35 = n35->obj))
            {
                long l_orderkey = e35->L_ORDERKEY;
                long p_partkey = e35->P_PARTKEY;
                long s_suppkey = e35->S_SUPPKEY;
                DOUBLE_TYPE v35 = e35->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i36 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h16 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se59.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n36 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i36->slice(se59, h16));
                  SUM_PROFITLINEITEM11_P_2_entry* e36;
                 
                  if (n36 && (e36 = n36->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e36->PROFIT_NATION;
                      long v36 = e36->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITLINEITEM11_P_4_map_0* i37 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0*>(SUM_PROFITLINEITEM11_P_4.index[1]);
                        const HASH_RES_t h15 = SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::hash(se58.modify0(l_orderkey));
                        HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode* n37 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode*>(i37->slice(se58, h15));
                        SUM_PROFITLINEITEM11_P_4_entry* e37;
                       
                        if (n37 && (e37 = n37->obj)) {
                          do {                
                            long profit_o_year = e37->PROFIT_O_YEAR;
                            long v37 = e37->__av;
                            SUM_PROFITPART11.addOrDelOnZero(se56.modify(p_partkey,profit_o_year,profit_nation),(v35 * (v36 * (SUM_PROFITLINEITEM11_P_3.getValueOrDefault(se57.modify(p_partkey,s_suppkey)) * v37))));
                            n37 = n37->nxt;
                          } while (n37 && (e37 = n37->obj) && h15 == n37->hash &&  SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::equals(se58, *e37)); 
                        }
                      }
                      n36 = n36->nxt;
                    } while (n36 && (e36 = n36->obj) && h16 == n36->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se59, *e36)); 
                  }
                }
              n35 = n35->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012* i38 = static_cast<HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012*>(SUM_PROFITLINEITEM13_DELTA.index[0]);
          HashIndex_SUM_PROFITLINEITEM13_DELTA_map_012::IdxNode* n38; 
          SUM_PROFITLINEITEM13_DELTA_entry* e38;
        
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
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i39 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h18 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se63.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n39 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i39->slice(se63, h18));
                  SUM_PROFITLINEITEM11_P_2_entry* e39;
                 
                  if (n39 && (e39 = n39->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e39->PROFIT_NATION;
                      long v39 = e39->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITLINEITEM11_P_4_map_0* i40 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0*>(SUM_PROFITLINEITEM11_P_4.index[1]);
                        const HASH_RES_t h17 = SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::hash(se62.modify0(l_orderkey));
                        HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode* n40 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_4_map_0::IdxNode*>(i40->slice(se62, h17));
                        SUM_PROFITLINEITEM11_P_4_entry* e40;
                       
                        if (n40 && (e40 = n40->obj)) {
                          do {                
                            long profit_o_year = e40->PROFIT_O_YEAR;
                            long v40 = e40->__av;
                            SUM_PROFITPART13.addOrDelOnZero(se60.modify(p_partkey,profit_o_year,profit_nation),(v38 * (v39 * (SUM_PROFITLINEITEM13_P_3.getValueOrDefault(se61.modify(p_partkey,s_suppkey)) * v40))));
                            n40 = n40->nxt;
                          } while (n40 && (e40 = n40->obj) && h17 == n40->hash &&  SUM_PROFITLINEITEM11_P_4_mapkey0_idxfn::equals(se62, *e40)); 
                        }
                      }
                      n39 = n39->nxt;
                    } while (n39 && (e39 = n39->obj) && h18 == n39->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se63, *e39)); 
                  }
                }
              n38 = n38->nxt;
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

        SUM_PROFITORDERS11_DELTA.clear();
        SUM_PROFITORDERS11_DOMAIN1.clear();
        {  
          for (size_t i = 0; i < DELTA_ORDERS.size; i++)
          {
                long l_orderkey = DELTA_ORDERS.orderkey[i];
                long o_custkey = DELTA_ORDERS.custkey[i];
                STRING_TYPE o_orderstatus = DELTA_ORDERS.orderstatus[i];
                DOUBLE_TYPE o_totalprice = DELTA_ORDERS.totalprice[i];
                date o_orderdate = DELTA_ORDERS.orderdate[i];
                STRING_TYPE o_orderpriority = DELTA_ORDERS.orderpriority[i];
                STRING_TYPE o_clerk = DELTA_ORDERS.clerk[i];
                long o_shippriority = DELTA_ORDERS.shippriority[i];
                STRING_TYPE o_comment = DELTA_ORDERS.comment[i];
                long v41 = 1L;
                long l1 = Uyear_part(o_orderdate);
                SUM_PROFITORDERS11_DELTA.addOrDelOnZero(se64.modify(l_orderkey,l1),v41);
                long v42 = 1L;
                long l2 = l1;
                SUM_PROFITORDERS11_DOMAIN1.addOrDelOnZero(se65.modify(l2),(v42 != 0 ? 1L : 0L));
          }
        }        
        {  // foreach
          const HashIndex_SUM_PROFITORDERS11_DOMAIN1_map_0* i43 = static_cast<HashIndex_SUM_PROFITORDERS11_DOMAIN1_map_0*>(SUM_PROFITORDERS11_DOMAIN1.index[0]);
          HashIndex_SUM_PROFITORDERS11_DOMAIN1_map_0::IdxNode* n43; 
          SUM_PROFITORDERS11_DOMAIN1_entry* e43;
        
          for (size_t i = 0; i < i43->size_; i++)
          {
            n43 = i43->buckets_ + i;
            while (n43 && (e43 = n43->obj))
            {
                long profit_o_year = e43->PROFIT_O_YEAR;
                long v43 = e43->__av;
                _c1.clear();
                { //slice 
                  const HashIndex_SUM_PROFITORDERS11_DELTA_map_1* i44 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_1*>(SUM_PROFITORDERS11_DELTA.index[1]);
                  const HASH_RES_t h20 = SUM_PROFITORDERS11_DELTA_mapkey1_idxfn::hash(se68.modify1(profit_o_year));
                  HashIndex_SUM_PROFITORDERS11_DELTA_map_1::IdxNode* n44 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_1::IdxNode*>(i44->slice(se68, h20));
                  SUM_PROFITORDERS11_DELTA_entry* e44;
                 
                  if (n44 && (e44 = n44->obj)) {
                    do {                
                      long l_orderkey = e44->L_ORDERKEY;
                      long v45 = e44->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITORDERS11_map_0* i45 = static_cast<HashIndex_SUM_PROFITORDERS11_map_0*>(SUM_PROFITORDERS11.index[1]);
                        const HASH_RES_t h19 = SUM_PROFITORDERS11_mapkey0_idxfn::hash(se67.modify0(l_orderkey));
                        HashIndex_SUM_PROFITORDERS11_map_0::IdxNode* n45 = static_cast<HashIndex_SUM_PROFITORDERS11_map_0::IdxNode*>(i45->slice(se67, h19));
                        SUM_PROFITORDERS11_entry* e45;
                       
                        if (n45 && (e45 = n45->obj)) {
                          do {                
                            STRING_TYPE profit_nation = e45->PROFIT_NATION;
                            DOUBLE_TYPE v46 = e45->__av;
                            _c1.addOrDelOnZero(st1.modify(profit_nation,((v45 * v46) * -1L)), ((v45 * v46) * -1L));
                            n45 = n45->nxt;
                          } while (n45 && (e45 = n45->obj) && h19 == n45->hash &&  SUM_PROFITORDERS11_mapkey0_idxfn::equals(se67, *e45)); 
                        }
                      }
                      n44 = n44->nxt;
                    } while (n44 && (e44 = n44->obj) && h20 == n44->hash &&  SUM_PROFITORDERS11_DELTA_mapkey1_idxfn::equals(se68, *e44)); 
                  }
                }{ //slice 
                  const HashIndex_SUM_PROFITORDERS11_DELTA_map_1* i46 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_1*>(SUM_PROFITORDERS11_DELTA.index[1]);
                  const HASH_RES_t h22 = SUM_PROFITORDERS11_DELTA_mapkey1_idxfn::hash(se70.modify1(profit_o_year));
                  HashIndex_SUM_PROFITORDERS11_DELTA_map_1::IdxNode* n46 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_1::IdxNode*>(i46->slice(se70, h22));
                  SUM_PROFITORDERS11_DELTA_entry* e46;
                 
                  if (n46 && (e46 = n46->obj)) {
                    do {                
                      long l_orderkey = e46->L_ORDERKEY;
                      long v47 = e46->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITORDERS13_map_0* i47 = static_cast<HashIndex_SUM_PROFITORDERS13_map_0*>(SUM_PROFITORDERS13.index[1]);
                        const HASH_RES_t h21 = SUM_PROFITORDERS13_mapkey0_idxfn::hash(se69.modify0(l_orderkey));
                        HashIndex_SUM_PROFITORDERS13_map_0::IdxNode* n47 = static_cast<HashIndex_SUM_PROFITORDERS13_map_0::IdxNode*>(i47->slice(se69, h21));
                        SUM_PROFITORDERS13_entry* e47;
                       
                        if (n47 && (e47 = n47->obj)) {
                          do {                
                            STRING_TYPE profit_nation = e47->PROFIT_NATION;
                            DOUBLE_TYPE v48 = e47->__av;
                            _c1.addOrDelOnZero(st2.modify(profit_nation,(v47 * v48)), (v47 * v48));
                            n47 = n47->nxt;
                          } while (n47 && (e47 = n47->obj) && h21 == n47->hash &&  SUM_PROFITORDERS13_mapkey0_idxfn::equals(se69, *e47)); 
                        }
                      }
                      n46 = n46->nxt;
                    } while (n46 && (e46 = n46->obj) && h22 == n46->hash &&  SUM_PROFITORDERS11_DELTA_mapkey1_idxfn::equals(se70, *e46)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i48 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c1.index[0]);
                  HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n48; 
                  tuple2_S_D* e48;
                
                  for (size_t i = 0; i < i48->size_; i++)
                  {
                    n48 = i48->buckets_ + i;
                    while (n48 && (e48 = n48->obj))
                    {
                      STRING_TYPE profit_nation = e48->_1;  
                      DOUBLE_TYPE v49 = e48->__av; 
                    SUM_PROFIT.addOrDelOnZero(se66.modify(profit_nation,profit_o_year),((v43 != 0 ? 1L : 0L) * v49));      
                      n48 = n48->nxt;
                    }
                  }
                }
              n43 = n43->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITORDERS11_DELTA_map_01* i49 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_01*>(SUM_PROFITORDERS11_DELTA.index[0]);
          HashIndex_SUM_PROFITORDERS11_DELTA_map_01::IdxNode* n49; 
          SUM_PROFITORDERS11_DELTA_entry* e49;
        
          for (size_t i = 0; i < i49->size_; i++)
          {
            n49 = i49->buckets_ + i;
            while (n49 && (e49 = n49->obj))
            {
                long l_orderkey = e49->L_ORDERKEY;
                long profit_o_year = e49->PROFIT_O_YEAR;
                long v50 = e49->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_0* i50 = static_cast<HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_0*>(SUM_PROFITORDERS11PARTSUPP1_P_3.index[1]);
                  const HASH_RES_t h23 = SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey0_idxfn::hash(se72.modify0(l_orderkey));
                  HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_0::IdxNode* n50 = static_cast<HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_0::IdxNode*>(i50->slice(se72, h23));
                  SUM_PROFITORDERS11PARTSUPP1_P_3_entry* e50;
                 
                  if (n50 && (e50 = n50->obj)) {
                    do {                
                      long p_partkey = e50->P_PARTKEY;
                      long s_suppkey = e50->S_SUPPKEY;
                      DOUBLE_TYPE v51 = e50->__av;
                      SUM_PROFITPARTSUPP11_P_3.addOrDelOnZero(se71.modify(p_partkey,s_suppkey,profit_o_year),(v50 * v51));
                      n50 = n50->nxt;
                    } while (n50 && (e50 = n50->obj) && h23 == n50->hash &&  SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey0_idxfn::equals(se72, *e50)); 
                  }
                }
              n49 = n49->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITORDERS11_DELTA_map_01* i51 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_01*>(SUM_PROFITORDERS11_DELTA.index[0]);
          HashIndex_SUM_PROFITORDERS11_DELTA_map_01::IdxNode* n51; 
          SUM_PROFITORDERS11_DELTA_entry* e51;
        
          for (size_t i = 0; i < i51->size_; i++)
          {
            n51 = i51->buckets_ + i;
            while (n51 && (e51 = n51->obj))
            {
                long l_orderkey = e51->L_ORDERKEY;
                long profit_o_year = e51->PROFIT_O_YEAR;
                long v52 = e51->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_0* i52 = static_cast<HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_0*>(SUM_PROFITORDERS13PARTSUPP1_P_3.index[1]);
                  const HASH_RES_t h24 = SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey0_idxfn::hash(se74.modify0(l_orderkey));
                  HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_0::IdxNode* n52 = static_cast<HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_0::IdxNode*>(i52->slice(se74, h24));
                  SUM_PROFITORDERS13PARTSUPP1_P_3_entry* e52;
                 
                  if (n52 && (e52 = n52->obj)) {
                    do {                
                      long p_partkey = e52->P_PARTKEY;
                      long s_suppkey = e52->S_SUPPKEY;
                      DOUBLE_TYPE v53 = e52->__av;
                      SUM_PROFITPARTSUPP13_P_3.addOrDelOnZero(se73.modify(p_partkey,s_suppkey,profit_o_year),(v52 * v53));
                      n52 = n52->nxt;
                    } while (n52 && (e52 = n52->obj) && h24 == n52->hash &&  SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey0_idxfn::equals(se74, *e52)); 
                  }
                }
              n51 = n51->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITORDERS11_DELTA_map_01* i53 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_01*>(SUM_PROFITORDERS11_DELTA.index[0]);
          HashIndex_SUM_PROFITORDERS11_DELTA_map_01::IdxNode* n53; 
          SUM_PROFITORDERS11_DELTA_entry* e53;
        
          for (size_t i = 0; i < i53->size_; i++)
          {
            n53 = i53->buckets_ + i;
            while (n53 && (e53 = n53->obj))
            {
                long l_orderkey = e53->L_ORDERKEY;
                long profit_o_year = e53->PROFIT_O_YEAR;
                long v54 = e53->__av;
                SUM_PROFITLINEITEM11_P_4.addOrDelOnZero(se75.modify(l_orderkey,profit_o_year),v54);
              n53 = n53->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITORDERS11_DELTA_map_01* i54 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_01*>(SUM_PROFITORDERS11_DELTA.index[0]);
          HashIndex_SUM_PROFITORDERS11_DELTA_map_01::IdxNode* n54; 
          SUM_PROFITORDERS11_DELTA_entry* e54;
        
          for (size_t i = 0; i < i54->size_; i++)
          {
            n54 = i54->buckets_ + i;
            while (n54 && (e54 = n54->obj))
            {
                long l_orderkey = e54->L_ORDERKEY;
                long profit_o_year = e54->PROFIT_O_YEAR;
                long v55 = e54->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1_map_0* i55 = static_cast<HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1_map_0*>(SUM_PROFITORDERS11SUPPLIER1_P_1.index[1]);
                  const HASH_RES_t h25 = SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey0_idxfn::hash(se77.modify0(l_orderkey));
                  HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1_map_0::IdxNode* n55 = static_cast<HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1_map_0::IdxNode*>(i55->slice(se77, h25));
                  SUM_PROFITORDERS11SUPPLIER1_P_1_entry* e55;
                 
                  if (n55 && (e55 = n55->obj)) {
                    do {                
                      long s_suppkey = e55->S_SUPPKEY;
                      DOUBLE_TYPE v56 = e55->__av;
                      SUM_PROFITSUPPLIER11_P_1.addOrDelOnZero(se76.modify(s_suppkey,profit_o_year),(v55 * v56));
                      n55 = n55->nxt;
                    } while (n55 && (e55 = n55->obj) && h25 == n55->hash &&  SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey0_idxfn::equals(se77, *e55)); 
                  }
                }
              n54 = n54->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITORDERS11_DELTA_map_01* i56 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_01*>(SUM_PROFITORDERS11_DELTA.index[0]);
          HashIndex_SUM_PROFITORDERS11_DELTA_map_01::IdxNode* n56; 
          SUM_PROFITORDERS11_DELTA_entry* e56;
        
          for (size_t i = 0; i < i56->size_; i++)
          {
            n56 = i56->buckets_ + i;
            while (n56 && (e56 = n56->obj))
            {
                long l_orderkey = e56->L_ORDERKEY;
                long profit_o_year = e56->PROFIT_O_YEAR;
                long v57 = e56->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_0* i57 = static_cast<HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_0*>(SUM_PROFITORDERS11SUPPLIER1_P_1PART1.index[1]);
                  const HASH_RES_t h26 = SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey0_idxfn::hash(se79.modify0(l_orderkey));
                  HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_0::IdxNode* n57 = static_cast<HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_0::IdxNode*>(i57->slice(se79, h26));
                  SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry* e57;
                 
                  if (n57 && (e57 = n57->obj)) {
                    do {                
                      long p_partkey = e57->P_PARTKEY;
                      long s_suppkey = e57->S_SUPPKEY;
                      DOUBLE_TYPE v58 = e57->__av;
                      SUM_PROFITSUPPLIER11_P_1PART1.addOrDelOnZero(se78.modify(p_partkey,s_suppkey,profit_o_year),(v57 * v58));
                      n57 = n57->nxt;
                    } while (n57 && (e57 = n57->obj) && h26 == n57->hash &&  SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey0_idxfn::equals(se79, *e57)); 
                  }
                }
              n56 = n56->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITORDERS11_DELTA_map_01* i58 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_01*>(SUM_PROFITORDERS11_DELTA.index[0]);
          HashIndex_SUM_PROFITORDERS11_DELTA_map_01::IdxNode* n58; 
          SUM_PROFITORDERS11_DELTA_entry* e58;
        
          for (size_t i = 0; i < i58->size_; i++)
          {
            n58 = i58->buckets_ + i;
            while (n58 && (e58 = n58->obj))
            {
                long l_orderkey = e58->L_ORDERKEY;
                long profit_o_year = e58->PROFIT_O_YEAR;
                long v59 = e58->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1_map_0* i59 = static_cast<HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1_map_0*>(SUM_PROFITORDERS13SUPPLIER1_P_1.index[1]);
                  const HASH_RES_t h27 = SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey0_idxfn::hash(se81.modify0(l_orderkey));
                  HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1_map_0::IdxNode* n59 = static_cast<HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1_map_0::IdxNode*>(i59->slice(se81, h27));
                  SUM_PROFITORDERS13SUPPLIER1_P_1_entry* e59;
                 
                  if (n59 && (e59 = n59->obj)) {
                    do {                
                      long s_suppkey = e59->S_SUPPKEY;
                      DOUBLE_TYPE v60 = e59->__av;
                      SUM_PROFITSUPPLIER13_P_1.addOrDelOnZero(se80.modify(s_suppkey,profit_o_year),(v59 * v60));
                      n59 = n59->nxt;
                    } while (n59 && (e59 = n59->obj) && h27 == n59->hash &&  SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey0_idxfn::equals(se81, *e59)); 
                  }
                }
              n58 = n58->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITORDERS11_DELTA_map_01* i60 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_01*>(SUM_PROFITORDERS11_DELTA.index[0]);
          HashIndex_SUM_PROFITORDERS11_DELTA_map_01::IdxNode* n60; 
          SUM_PROFITORDERS11_DELTA_entry* e60;
        
          for (size_t i = 0; i < i60->size_; i++)
          {
            n60 = i60->buckets_ + i;
            while (n60 && (e60 = n60->obj))
            {
                long l_orderkey = e60->L_ORDERKEY;
                long profit_o_year = e60->PROFIT_O_YEAR;
                long v61 = e60->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_0* i61 = static_cast<HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_0*>(SUM_PROFITORDERS13SUPPLIER1_P_1PART1.index[1]);
                  const HASH_RES_t h28 = SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey0_idxfn::hash(se83.modify0(l_orderkey));
                  HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_0::IdxNode* n61 = static_cast<HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_0::IdxNode*>(i61->slice(se83, h28));
                  SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry* e61;
                 
                  if (n61 && (e61 = n61->obj)) {
                    do {                
                      long p_partkey = e61->P_PARTKEY;
                      long s_suppkey = e61->S_SUPPKEY;
                      DOUBLE_TYPE v62 = e61->__av;
                      SUM_PROFITSUPPLIER13_P_1PART1.addOrDelOnZero(se82.modify(p_partkey,s_suppkey,profit_o_year),(v61 * v62));
                      n61 = n61->nxt;
                    } while (n61 && (e61 = n61->obj) && h28 == n61->hash &&  SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey0_idxfn::equals(se83, *e61)); 
                  }
                }
              n60 = n60->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITORDERS11_DELTA_map_01* i62 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_01*>(SUM_PROFITORDERS11_DELTA.index[0]);
          HashIndex_SUM_PROFITORDERS11_DELTA_map_01::IdxNode* n62; 
          SUM_PROFITORDERS11_DELTA_entry* e62;
        
          for (size_t i = 0; i < i62->size_; i++)
          {
            n62 = i62->buckets_ + i;
            while (n62 && (e62 = n62->obj))
            {
                long l_orderkey = e62->L_ORDERKEY;
                long profit_o_year = e62->PROFIT_O_YEAR;
                long v63 = e62->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS11PART1_map_0* i63 = static_cast<HashIndex_SUM_PROFITORDERS11PART1_map_0*>(SUM_PROFITORDERS11PART1.index[1]);
                  const HASH_RES_t h29 = SUM_PROFITORDERS11PART1_mapkey0_idxfn::hash(se85.modify0(l_orderkey));
                  HashIndex_SUM_PROFITORDERS11PART1_map_0::IdxNode* n63 = static_cast<HashIndex_SUM_PROFITORDERS11PART1_map_0::IdxNode*>(i63->slice(se85, h29));
                  SUM_PROFITORDERS11PART1_entry* e63;
                 
                  if (n63 && (e63 = n63->obj)) {
                    do {                
                      long p_partkey = e63->P_PARTKEY;
                      STRING_TYPE profit_nation = e63->PROFIT_NATION;
                      DOUBLE_TYPE v64 = e63->__av;
                      SUM_PROFITPART11.addOrDelOnZero(se84.modify(p_partkey,profit_o_year,profit_nation),(v63 * v64));
                      n63 = n63->nxt;
                    } while (n63 && (e63 = n63->obj) && h29 == n63->hash &&  SUM_PROFITORDERS11PART1_mapkey0_idxfn::equals(se85, *e63)); 
                  }
                }
              n62 = n62->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITORDERS11_DELTA_map_01* i64 = static_cast<HashIndex_SUM_PROFITORDERS11_DELTA_map_01*>(SUM_PROFITORDERS11_DELTA.index[0]);
          HashIndex_SUM_PROFITORDERS11_DELTA_map_01::IdxNode* n64; 
          SUM_PROFITORDERS11_DELTA_entry* e64;
        
          for (size_t i = 0; i < i64->size_; i++)
          {
            n64 = i64->buckets_ + i;
            while (n64 && (e64 = n64->obj))
            {
                long l_orderkey = e64->L_ORDERKEY;
                long profit_o_year = e64->PROFIT_O_YEAR;
                long v65 = e64->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS13PART1_map_0* i65 = static_cast<HashIndex_SUM_PROFITORDERS13PART1_map_0*>(SUM_PROFITORDERS13PART1.index[1]);
                  const HASH_RES_t h30 = SUM_PROFITORDERS13PART1_mapkey0_idxfn::hash(se87.modify0(l_orderkey));
                  HashIndex_SUM_PROFITORDERS13PART1_map_0::IdxNode* n65 = static_cast<HashIndex_SUM_PROFITORDERS13PART1_map_0::IdxNode*>(i65->slice(se87, h30));
                  SUM_PROFITORDERS13PART1_entry* e65;
                 
                  if (n65 && (e65 = n65->obj)) {
                    do {                
                      long p_partkey = e65->P_PARTKEY;
                      STRING_TYPE profit_nation = e65->PROFIT_NATION;
                      DOUBLE_TYPE v66 = e65->__av;
                      SUM_PROFITPART13.addOrDelOnZero(se86.modify(p_partkey,profit_o_year,profit_nation),(v65 * v66));
                      n65 = n65->nxt;
                    } while (n65 && (e65 = n65->obj) && h30 == n65->hash &&  SUM_PROFITORDERS13PART1_mapkey0_idxfn::equals(se87, *e65)); 
                  }
                }
              n64 = n64->nxt;
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

        SUM_PROFITPART11_DELTA.clear();
        { 
          for (size_t i = 0; i < DELTA_PART.size; i++)
          {
                long p_partkey = DELTA_PART.partkey[i];
                STRING_TYPE p_name = DELTA_PART.name[i];
                STRING_TYPE p_mfgr = DELTA_PART.mfgr[i];
                STRING_TYPE p_brand = DELTA_PART.brand[i];
                STRING_TYPE p_type = DELTA_PART.type[i];
                long p_size = DELTA_PART.psize[i];
                STRING_TYPE p_container = DELTA_PART.container[i];
                DOUBLE_TYPE p_retailprice = DELTA_PART.retailprice[i];
                STRING_TYPE p_comment = DELTA_PART.comment[i];
                long v67 = 1L;
                (/*if */(0L != Upreg_match(preg1,p_name)) ? SUM_PROFITPART11_DELTA.addOrDelOnZero(se88.modify(p_partkey),v67) : (void)0);
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPART11_DELTA_map_0* i67 = static_cast<HashIndex_SUM_PROFITPART11_DELTA_map_0*>(SUM_PROFITPART11_DELTA.index[0]);
          HashIndex_SUM_PROFITPART11_DELTA_map_0::IdxNode* n67; 
          SUM_PROFITPART11_DELTA_entry* e67;
        
          for (size_t i = 0; i < i67->size_; i++)
          {
            n67 = i67->buckets_ + i;
            while (n67 && (e67 = n67->obj))
            {
                long p_partkey = e67->P_PARTKEY;
                long v68 = e67->__av;
                { //slice 
                  const HashIndex_SUM_PROFITPART11_map_0* i68 = static_cast<HashIndex_SUM_PROFITPART11_map_0*>(SUM_PROFITPART11.index[1]);
                  const HASH_RES_t h31 = SUM_PROFITPART11_mapkey0_idxfn::hash(se90.modify0(p_partkey));
                  HashIndex_SUM_PROFITPART11_map_0::IdxNode* n68 = static_cast<HashIndex_SUM_PROFITPART11_map_0::IdxNode*>(i68->slice(se90, h31));
                  SUM_PROFITPART11_entry* e68;
                 
                  if (n68 && (e68 = n68->obj)) {
                    do {                
                      long profit_o_year = e68->PROFIT_O_YEAR;
                      STRING_TYPE profit_nation = e68->PROFIT_NATION;
                      DOUBLE_TYPE v69 = e68->__av;
                      SUM_PROFIT.addOrDelOnZero(se89.modify(profit_nation,profit_o_year),((v68 * v69) * -1L));
                      n68 = n68->nxt;
                    } while (n68 && (e68 = n68->obj) && h31 == n68->hash &&  SUM_PROFITPART11_mapkey0_idxfn::equals(se90, *e68)); 
                  }
                }
              n67 = n67->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPART11_DELTA_map_0* i69 = static_cast<HashIndex_SUM_PROFITPART11_DELTA_map_0*>(SUM_PROFITPART11_DELTA.index[0]);
          HashIndex_SUM_PROFITPART11_DELTA_map_0::IdxNode* n69; 
          SUM_PROFITPART11_DELTA_entry* e69;
        
          for (size_t i = 0; i < i69->size_; i++)
          {
            n69 = i69->buckets_ + i;
            while (n69 && (e69 = n69->obj))
            {
                long p_partkey = e69->P_PARTKEY;
                long v70 = e69->__av;
                { //slice 
                  const HashIndex_SUM_PROFITPART13_map_0* i70 = static_cast<HashIndex_SUM_PROFITPART13_map_0*>(SUM_PROFITPART13.index[1]);
                  const HASH_RES_t h32 = SUM_PROFITPART13_mapkey0_idxfn::hash(se91.modify0(p_partkey));
                  HashIndex_SUM_PROFITPART13_map_0::IdxNode* n70 = static_cast<HashIndex_SUM_PROFITPART13_map_0::IdxNode*>(i70->slice(se91, h32));
                  SUM_PROFITPART13_entry* e70;
                 
                  if (n70 && (e70 = n70->obj)) {
                    do {                
                      long profit_o_year = e70->PROFIT_O_YEAR;
                      STRING_TYPE profit_nation = e70->PROFIT_NATION;
                      DOUBLE_TYPE v71 = e70->__av;
                      SUM_PROFIT.addOrDelOnZero(se89.modify(profit_nation,profit_o_year),(v70 * v71));
                      n70 = n70->nxt;
                    } while (n70 && (e70 = n70->obj) && h32 == n70->hash &&  SUM_PROFITPART13_mapkey0_idxfn::equals(se91, *e70)); 
                  }
                }
              n69 = n69->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPART11_DELTA_map_0* i71 = static_cast<HashIndex_SUM_PROFITPART11_DELTA_map_0*>(SUM_PROFITPART11_DELTA.index[0]);
          HashIndex_SUM_PROFITPART11_DELTA_map_0::IdxNode* n71; 
          SUM_PROFITPART11_DELTA_entry* e71;
        
          for (size_t i = 0; i < i71->size_; i++)
          {
            n71 = i71->buckets_ + i;
            while (n71 && (e71 = n71->obj))
            {
                long p_partkey = e71->P_PARTKEY;
                long v72 = e71->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS11PART1_map_1* i72 = static_cast<HashIndex_SUM_PROFITORDERS11PART1_map_1*>(SUM_PROFITORDERS11PART1.index[2]);
                  const HASH_RES_t h33 = SUM_PROFITORDERS11PART1_mapkey1_idxfn::hash(se93.modify1(p_partkey));
                  HashIndex_SUM_PROFITORDERS11PART1_map_1::IdxNode* n72 = static_cast<HashIndex_SUM_PROFITORDERS11PART1_map_1::IdxNode*>(i72->slice(se93, h33));
                  SUM_PROFITORDERS11PART1_entry* e72;
                 
                  if (n72 && (e72 = n72->obj)) {
                    do {                
                      long l_orderkey = e72->L_ORDERKEY;
                      STRING_TYPE profit_nation = e72->PROFIT_NATION;
                      DOUBLE_TYPE v73 = e72->__av;
                      SUM_PROFITORDERS11.addOrDelOnZero(se92.modify(l_orderkey,profit_nation),(v72 * v73));
                      n72 = n72->nxt;
                    } while (n72 && (e72 = n72->obj) && h33 == n72->hash &&  SUM_PROFITORDERS11PART1_mapkey1_idxfn::equals(se93, *e72)); 
                  }
                }
              n71 = n71->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPART11_DELTA_map_0* i73 = static_cast<HashIndex_SUM_PROFITPART11_DELTA_map_0*>(SUM_PROFITPART11_DELTA.index[0]);
          HashIndex_SUM_PROFITPART11_DELTA_map_0::IdxNode* n73; 
          SUM_PROFITPART11_DELTA_entry* e73;
        
          for (size_t i = 0; i < i73->size_; i++)
          {
            n73 = i73->buckets_ + i;
            while (n73 && (e73 = n73->obj))
            {
                long p_partkey = e73->P_PARTKEY;
                long v74 = e73->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_1* i74 = static_cast<HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_1*>(SUM_PROFITORDERS11SUPPLIER1_P_1PART1.index[2]);
                  const HASH_RES_t h34 = SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey1_idxfn::hash(se95.modify1(p_partkey));
                  HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_1::IdxNode* n74 = static_cast<HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_1::IdxNode*>(i74->slice(se95, h34));
                  SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry* e74;
                 
                  if (n74 && (e74 = n74->obj)) {
                    do {                
                      long l_orderkey = e74->L_ORDERKEY;
                      long s_suppkey = e74->S_SUPPKEY;
                      DOUBLE_TYPE v75 = e74->__av;
                      SUM_PROFITORDERS11SUPPLIER1_P_1.addOrDelOnZero(se94.modify(l_orderkey,s_suppkey),(v74 * v75));
                      n74 = n74->nxt;
                    } while (n74 && (e74 = n74->obj) && h34 == n74->hash &&  SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey1_idxfn::equals(se95, *e74)); 
                  }
                }
              n73 = n73->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPART11_DELTA_map_0* i75 = static_cast<HashIndex_SUM_PROFITPART11_DELTA_map_0*>(SUM_PROFITPART11_DELTA.index[0]);
          HashIndex_SUM_PROFITPART11_DELTA_map_0::IdxNode* n75; 
          SUM_PROFITPART11_DELTA_entry* e75;
        
          for (size_t i = 0; i < i75->size_; i++)
          {
            n75 = i75->buckets_ + i;
            while (n75 && (e75 = n75->obj))
            {
                long p_partkey = e75->P_PARTKEY;
                long v76 = e75->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS13PART1_map_1* i76 = static_cast<HashIndex_SUM_PROFITORDERS13PART1_map_1*>(SUM_PROFITORDERS13PART1.index[2]);
                  const HASH_RES_t h35 = SUM_PROFITORDERS13PART1_mapkey1_idxfn::hash(se97.modify1(p_partkey));
                  HashIndex_SUM_PROFITORDERS13PART1_map_1::IdxNode* n76 = static_cast<HashIndex_SUM_PROFITORDERS13PART1_map_1::IdxNode*>(i76->slice(se97, h35));
                  SUM_PROFITORDERS13PART1_entry* e76;
                 
                  if (n76 && (e76 = n76->obj)) {
                    do {                
                      long l_orderkey = e76->L_ORDERKEY;
                      STRING_TYPE profit_nation = e76->PROFIT_NATION;
                      DOUBLE_TYPE v77 = e76->__av;
                      SUM_PROFITORDERS13.addOrDelOnZero(se96.modify(l_orderkey,profit_nation),(v76 * v77));
                      n76 = n76->nxt;
                    } while (n76 && (e76 = n76->obj) && h35 == n76->hash &&  SUM_PROFITORDERS13PART1_mapkey1_idxfn::equals(se97, *e76)); 
                  }
                }
              n75 = n75->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPART11_DELTA_map_0* i77 = static_cast<HashIndex_SUM_PROFITPART11_DELTA_map_0*>(SUM_PROFITPART11_DELTA.index[0]);
          HashIndex_SUM_PROFITPART11_DELTA_map_0::IdxNode* n77; 
          SUM_PROFITPART11_DELTA_entry* e77;
        
          for (size_t i = 0; i < i77->size_; i++)
          {
            n77 = i77->buckets_ + i;
            while (n77 && (e77 = n77->obj))
            {
                long p_partkey = e77->P_PARTKEY;
                long v78 = e77->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_1* i78 = static_cast<HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_1*>(SUM_PROFITORDERS13SUPPLIER1_P_1PART1.index[2]);
                  const HASH_RES_t h36 = SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey1_idxfn::hash(se99.modify1(p_partkey));
                  HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_1::IdxNode* n78 = static_cast<HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_1::IdxNode*>(i78->slice(se99, h36));
                  SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry* e78;
                 
                  if (n78 && (e78 = n78->obj)) {
                    do {                
                      long l_orderkey = e78->L_ORDERKEY;
                      long s_suppkey = e78->S_SUPPKEY;
                      DOUBLE_TYPE v79 = e78->__av;
                      SUM_PROFITORDERS13SUPPLIER1_P_1.addOrDelOnZero(se98.modify(l_orderkey,s_suppkey),(v78 * v79));
                      n78 = n78->nxt;
                    } while (n78 && (e78 = n78->obj) && h36 == n78->hash &&  SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey1_idxfn::equals(se99, *e78)); 
                  }
                }
              n77 = n77->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPART11_DELTA_map_0* i79 = static_cast<HashIndex_SUM_PROFITPART11_DELTA_map_0*>(SUM_PROFITPART11_DELTA.index[0]);
          HashIndex_SUM_PROFITPART11_DELTA_map_0::IdxNode* n79; 
          SUM_PROFITPART11_DELTA_entry* e79;
        
          for (size_t i = 0; i < i79->size_; i++)
          {
            n79 = i79->buckets_ + i;
            while (n79 && (e79 = n79->obj))
            {
                long p_partkey = e79->P_PARTKEY;
                long v80 = e79->__av;
                SUM_PROFITLINEITEM11_P_1.addOrDelOnZero(se100.modify(p_partkey),v80);
              n79 = n79->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPART11_DELTA_map_0* i80 = static_cast<HashIndex_SUM_PROFITPART11_DELTA_map_0*>(SUM_PROFITPART11_DELTA.index[0]);
          HashIndex_SUM_PROFITPART11_DELTA_map_0::IdxNode* n80; 
          SUM_PROFITPART11_DELTA_entry* e80;
        
          for (size_t i = 0; i < i80->size_; i++)
          {
            n80 = i80->buckets_ + i;
            while (n80 && (e80 = n80->obj))
            {
                long p_partkey = e80->P_PARTKEY;
                long v81 = e80->__av;
                { //slice 
                  const HashIndex_SUM_PROFITSUPPLIER11_P_1PART1_map_0* i81 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_1PART1_map_0*>(SUM_PROFITSUPPLIER11_P_1PART1.index[1]);
                  const HASH_RES_t h37 = SUM_PROFITSUPPLIER11_P_1PART1_mapkey0_idxfn::hash(se102.modify0(p_partkey));
                  HashIndex_SUM_PROFITSUPPLIER11_P_1PART1_map_0::IdxNode* n81 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_1PART1_map_0::IdxNode*>(i81->slice(se102, h37));
                  SUM_PROFITSUPPLIER11_P_1PART1_entry* e81;
                 
                  if (n81 && (e81 = n81->obj)) {
                    do {                
                      long s_suppkey = e81->S_SUPPKEY;
                      long profit_o_year = e81->PROFIT_O_YEAR;
                      DOUBLE_TYPE v82 = e81->__av;
                      SUM_PROFITSUPPLIER11_P_1.addOrDelOnZero(se101.modify(s_suppkey,profit_o_year),(v81 * v82));
                      n81 = n81->nxt;
                    } while (n81 && (e81 = n81->obj) && h37 == n81->hash &&  SUM_PROFITSUPPLIER11_P_1PART1_mapkey0_idxfn::equals(se102, *e81)); 
                  }
                }
              n80 = n80->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPART11_DELTA_map_0* i82 = static_cast<HashIndex_SUM_PROFITPART11_DELTA_map_0*>(SUM_PROFITPART11_DELTA.index[0]);
          HashIndex_SUM_PROFITPART11_DELTA_map_0::IdxNode* n82; 
          SUM_PROFITPART11_DELTA_entry* e82;
        
          for (size_t i = 0; i < i82->size_; i++)
          {
            n82 = i82->buckets_ + i;
            while (n82 && (e82 = n82->obj))
            {
                long p_partkey = e82->P_PARTKEY;
                long v83 = e82->__av;
                { //slice 
                  const HashIndex_SUM_PROFITSUPPLIER13_P_1PART1_map_0* i83 = static_cast<HashIndex_SUM_PROFITSUPPLIER13_P_1PART1_map_0*>(SUM_PROFITSUPPLIER13_P_1PART1.index[1]);
                  const HASH_RES_t h38 = SUM_PROFITSUPPLIER13_P_1PART1_mapkey0_idxfn::hash(se104.modify0(p_partkey));
                  HashIndex_SUM_PROFITSUPPLIER13_P_1PART1_map_0::IdxNode* n83 = static_cast<HashIndex_SUM_PROFITSUPPLIER13_P_1PART1_map_0::IdxNode*>(i83->slice(se104, h38));
                  SUM_PROFITSUPPLIER13_P_1PART1_entry* e83;
                 
                  if (n83 && (e83 = n83->obj)) {
                    do {                
                      long s_suppkey = e83->S_SUPPKEY;
                      long profit_o_year = e83->PROFIT_O_YEAR;
                      DOUBLE_TYPE v84 = e83->__av;
                      SUM_PROFITSUPPLIER13_P_1.addOrDelOnZero(se103.modify(s_suppkey,profit_o_year),(v83 * v84));
                      n83 = n83->nxt;
                    } while (n83 && (e83 = n83->obj) && h38 == n83->hash &&  SUM_PROFITSUPPLIER13_P_1PART1_mapkey0_idxfn::equals(se104, *e83)); 
                  }
                }
              n82 = n82->nxt;
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

        SUM_PROFITSUPPLIER11_DELTA.clear();
        { 
          for (size_t i = 0; i < DELTA_SUPPLIER.size; i++) 
          {
                long s_suppkey = DELTA_SUPPLIER.suppkey[i];
                STRING_TYPE s_name = DELTA_SUPPLIER.name[i];
                STRING_TYPE s_address = DELTA_SUPPLIER.address[i];
                long s_nationkey = DELTA_SUPPLIER.nationkey[i];
                STRING_TYPE s_phone = DELTA_SUPPLIER.phone[i];
                DOUBLE_TYPE s_acctbal = DELTA_SUPPLIER.acctbal[i];
                STRING_TYPE s_comment = DELTA_SUPPLIER.comment[i];
                long v85 = 1L;
                SUM_PROFITSUPPLIER11_DELTA.addOrDelOnZero(se105.modify(s_suppkey,s_nationkey),v85);
          }
        }{  // foreach
          const HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01* i85 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01*>(SUM_PROFITSUPPLIER11_DELTA.index[0]);
          HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01::IdxNode* n85; 
          SUM_PROFITSUPPLIER11_DELTA_entry* e85;
        
          for (size_t i = 0; i < i85->size_; i++)
          {
            n85 = i85->buckets_ + i;
            while (n85 && (e85 = n85->obj))
            {
                long s_suppkey = e85->S_SUPPKEY;
                long s_nationkey = e85->S_NATIONKEY;
                long v86 = e85->__av;
                { //slice 
                  const HashIndex_SUM_PROFITSUPPLIER11_P_1_map_0* i86 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_1_map_0*>(SUM_PROFITSUPPLIER11_P_1.index[1]);
                  const HASH_RES_t h40 = SUM_PROFITSUPPLIER11_P_1_mapkey0_idxfn::hash(se108.modify0(s_suppkey));
                  HashIndex_SUM_PROFITSUPPLIER11_P_1_map_0::IdxNode* n86 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_1_map_0::IdxNode*>(i86->slice(se108, h40));
                  SUM_PROFITSUPPLIER11_P_1_entry* e86;
                 
                  if (n86 && (e86 = n86->obj)) {
                    do {                
                      long profit_o_year = e86->PROFIT_O_YEAR;
                      DOUBLE_TYPE v87 = e86->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0* i87 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0*>(SUM_PROFITSUPPLIER11_P_2.index[1]);
                        const HASH_RES_t h39 = SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::hash(se107.modify0(s_nationkey));
                        HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode* n87 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode*>(i87->slice(se107, h39));
                        SUM_PROFITSUPPLIER11_P_2_entry* e87;
                       
                        if (n87 && (e87 = n87->obj)) {
                          do {                
                            STRING_TYPE profit_nation = e87->PROFIT_NATION;
                            long v88 = e87->__av;
                            SUM_PROFIT.addOrDelOnZero(se106.modify(profit_nation,profit_o_year),((v86 * (v87 * v88)) * -1L));
                            n87 = n87->nxt;
                          } while (n87 && (e87 = n87->obj) && h39 == n87->hash &&  SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::equals(se107, *e87)); 
                        }
                      }
                      n86 = n86->nxt;
                    } while (n86 && (e86 = n86->obj) && h40 == n86->hash &&  SUM_PROFITSUPPLIER11_P_1_mapkey0_idxfn::equals(se108, *e86)); 
                  }
                }
              n85 = n85->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01* i88 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01*>(SUM_PROFITSUPPLIER11_DELTA.index[0]);
          HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01::IdxNode* n88; 
          SUM_PROFITSUPPLIER11_DELTA_entry* e88;
        
          for (size_t i = 0; i < i88->size_; i++)
          {
            n88 = i88->buckets_ + i;
            while (n88 && (e88 = n88->obj))
            {
                long s_suppkey = e88->S_SUPPKEY;
                long s_nationkey = e88->S_NATIONKEY;
                long v89 = e88->__av;
                { //slice 
                  const HashIndex_SUM_PROFITSUPPLIER13_P_1_map_0* i89 = static_cast<HashIndex_SUM_PROFITSUPPLIER13_P_1_map_0*>(SUM_PROFITSUPPLIER13_P_1.index[1]);
                  const HASH_RES_t h42 = SUM_PROFITSUPPLIER13_P_1_mapkey0_idxfn::hash(se110.modify0(s_suppkey));
                  HashIndex_SUM_PROFITSUPPLIER13_P_1_map_0::IdxNode* n89 = static_cast<HashIndex_SUM_PROFITSUPPLIER13_P_1_map_0::IdxNode*>(i89->slice(se110, h42));
                  SUM_PROFITSUPPLIER13_P_1_entry* e89;
                 
                  if (n89 && (e89 = n89->obj)) {
                    do {                
                      long profit_o_year = e89->PROFIT_O_YEAR;
                      DOUBLE_TYPE v90 = e89->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0* i90 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0*>(SUM_PROFITSUPPLIER11_P_2.index[1]);
                        const HASH_RES_t h41 = SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::hash(se109.modify0(s_nationkey));
                        HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode* n90 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode*>(i90->slice(se109, h41));
                        SUM_PROFITSUPPLIER11_P_2_entry* e90;
                       
                        if (n90 && (e90 = n90->obj)) {
                          do {                
                            STRING_TYPE profit_nation = e90->PROFIT_NATION;
                            long v91 = e90->__av;
                            SUM_PROFIT.addOrDelOnZero(se106.modify(profit_nation,profit_o_year),(v89 * (v90 * v91)));
                            n90 = n90->nxt;
                          } while (n90 && (e90 = n90->obj) && h41 == n90->hash &&  SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::equals(se109, *e90)); 
                        }
                      }
                      n89 = n89->nxt;
                    } while (n89 && (e89 = n89->obj) && h42 == n89->hash &&  SUM_PROFITSUPPLIER13_P_1_mapkey0_idxfn::equals(se110, *e89)); 
                  }
                }
              n88 = n88->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01* i91 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01*>(SUM_PROFITSUPPLIER11_DELTA.index[0]);
          HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01::IdxNode* n91; 
          SUM_PROFITSUPPLIER11_DELTA_entry* e91;
        
          for (size_t i = 0; i < i91->size_; i++)
          {
            n91 = i91->buckets_ + i;
            while (n91 && (e91 = n91->obj))
            {
                long s_suppkey = e91->S_SUPPKEY;
                long s_nationkey = e91->S_NATIONKEY;
                long v92 = e91->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1_map_1* i92 = static_cast<HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1_map_1*>(SUM_PROFITORDERS11SUPPLIER1_P_1.index[2]);
                  const HASH_RES_t h44 = SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey1_idxfn::hash(se113.modify1(s_suppkey));
                  HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1_map_1::IdxNode* n92 = static_cast<HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1_map_1::IdxNode*>(i92->slice(se113, h44));
                  SUM_PROFITORDERS11SUPPLIER1_P_1_entry* e92;
                 
                  if (n92 && (e92 = n92->obj)) {
                    do {                
                      long l_orderkey = e92->L_ORDERKEY;
                      DOUBLE_TYPE v93 = e92->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0* i93 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0*>(SUM_PROFITSUPPLIER11_P_2.index[1]);
                        const HASH_RES_t h43 = SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::hash(se112.modify0(s_nationkey));
                        HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode* n93 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode*>(i93->slice(se112, h43));
                        SUM_PROFITSUPPLIER11_P_2_entry* e93;
                       
                        if (n93 && (e93 = n93->obj)) {
                          do {                
                            STRING_TYPE profit_nation = e93->PROFIT_NATION;
                            long v94 = e93->__av;
                            SUM_PROFITORDERS11.addOrDelOnZero(se111.modify(l_orderkey,profit_nation),(v92 * (v93 * v94)));
                            n93 = n93->nxt;
                          } while (n93 && (e93 = n93->obj) && h43 == n93->hash &&  SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::equals(se112, *e93)); 
                        }
                      }
                      n92 = n92->nxt;
                    } while (n92 && (e92 = n92->obj) && h44 == n92->hash &&  SUM_PROFITORDERS11SUPPLIER1_P_1_mapkey1_idxfn::equals(se113, *e92)); 
                  }
                }
              n91 = n91->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01* i94 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01*>(SUM_PROFITSUPPLIER11_DELTA.index[0]);
          HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01::IdxNode* n94; 
          SUM_PROFITSUPPLIER11_DELTA_entry* e94;
        
          for (size_t i = 0; i < i94->size_; i++)
          {
            n94 = i94->buckets_ + i;
            while (n94 && (e94 = n94->obj))
            {
                long s_suppkey = e94->S_SUPPKEY;
                long s_nationkey = e94->S_NATIONKEY;
                long v95 = e94->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_2* i95 = static_cast<HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_2*>(SUM_PROFITORDERS11SUPPLIER1_P_1PART1.index[3]);
                  const HASH_RES_t h46 = SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey2_idxfn::hash(se116.modify2(s_suppkey));
                  HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_2::IdxNode* n95 = static_cast<HashIndex_SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map_2::IdxNode*>(i95->slice(se116, h46));
                  SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry* e95;
                 
                  if (n95 && (e95 = n95->obj)) {
                    do {                
                      long l_orderkey = e95->L_ORDERKEY;
                      long p_partkey = e95->P_PARTKEY;
                      DOUBLE_TYPE v96 = e95->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0* i96 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0*>(SUM_PROFITSUPPLIER11_P_2.index[1]);
                        const HASH_RES_t h45 = SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::hash(se115.modify0(s_nationkey));
                        HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode* n96 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode*>(i96->slice(se115, h45));
                        SUM_PROFITSUPPLIER11_P_2_entry* e96;
                       
                        if (n96 && (e96 = n96->obj)) {
                          do {                
                            STRING_TYPE profit_nation = e96->PROFIT_NATION;
                            long v97 = e96->__av;
                            SUM_PROFITORDERS11PART1.addOrDelOnZero(se114.modify(l_orderkey,p_partkey,profit_nation),(v95 * (v96 * v97)));
                            n96 = n96->nxt;
                          } while (n96 && (e96 = n96->obj) && h45 == n96->hash &&  SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::equals(se115, *e96)); 
                        }
                      }
                      n95 = n95->nxt;
                    } while (n95 && (e95 = n95->obj) && h46 == n95->hash &&  SUM_PROFITORDERS11SUPPLIER1_P_1PART1_mapkey2_idxfn::equals(se116, *e95)); 
                  }
                }
              n94 = n94->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01* i97 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01*>(SUM_PROFITSUPPLIER11_DELTA.index[0]);
          HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01::IdxNode* n97; 
          SUM_PROFITSUPPLIER11_DELTA_entry* e97;
        
          for (size_t i = 0; i < i97->size_; i++)
          {
            n97 = i97->buckets_ + i;
            while (n97 && (e97 = n97->obj))
            {
                long s_suppkey = e97->S_SUPPKEY;
                long s_nationkey = e97->S_NATIONKEY;
                long v98 = e97->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1_map_1* i98 = static_cast<HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1_map_1*>(SUM_PROFITORDERS13SUPPLIER1_P_1.index[2]);
                  const HASH_RES_t h48 = SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey1_idxfn::hash(se119.modify1(s_suppkey));
                  HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1_map_1::IdxNode* n98 = static_cast<HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1_map_1::IdxNode*>(i98->slice(se119, h48));
                  SUM_PROFITORDERS13SUPPLIER1_P_1_entry* e98;
                 
                  if (n98 && (e98 = n98->obj)) {
                    do {                
                      long l_orderkey = e98->L_ORDERKEY;
                      DOUBLE_TYPE v99 = e98->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0* i99 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0*>(SUM_PROFITSUPPLIER11_P_2.index[1]);
                        const HASH_RES_t h47 = SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::hash(se118.modify0(s_nationkey));
                        HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode* n99 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode*>(i99->slice(se118, h47));
                        SUM_PROFITSUPPLIER11_P_2_entry* e99;
                       
                        if (n99 && (e99 = n99->obj)) {
                          do {                
                            STRING_TYPE profit_nation = e99->PROFIT_NATION;
                            long v100 = e99->__av;
                            SUM_PROFITORDERS13.addOrDelOnZero(se117.modify(l_orderkey,profit_nation),(v98 * (v99 * v100)));
                            n99 = n99->nxt;
                          } while (n99 && (e99 = n99->obj) && h47 == n99->hash &&  SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::equals(se118, *e99)); 
                        }
                      }
                      n98 = n98->nxt;
                    } while (n98 && (e98 = n98->obj) && h48 == n98->hash &&  SUM_PROFITORDERS13SUPPLIER1_P_1_mapkey1_idxfn::equals(se119, *e98)); 
                  }
                }
              n97 = n97->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01* i100 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01*>(SUM_PROFITSUPPLIER11_DELTA.index[0]);
          HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01::IdxNode* n100; 
          SUM_PROFITSUPPLIER11_DELTA_entry* e100;
        
          for (size_t i = 0; i < i100->size_; i++)
          {
            n100 = i100->buckets_ + i;
            while (n100 && (e100 = n100->obj))
            {
                long s_suppkey = e100->S_SUPPKEY;
                long s_nationkey = e100->S_NATIONKEY;
                long v101 = e100->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_2* i101 = static_cast<HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_2*>(SUM_PROFITORDERS13SUPPLIER1_P_1PART1.index[3]);
                  const HASH_RES_t h50 = SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey2_idxfn::hash(se122.modify2(s_suppkey));
                  HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_2::IdxNode* n101 = static_cast<HashIndex_SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map_2::IdxNode*>(i101->slice(se122, h50));
                  SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry* e101;
                 
                  if (n101 && (e101 = n101->obj)) {
                    do {                
                      long l_orderkey = e101->L_ORDERKEY;
                      long p_partkey = e101->P_PARTKEY;
                      DOUBLE_TYPE v102 = e101->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0* i102 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0*>(SUM_PROFITSUPPLIER11_P_2.index[1]);
                        const HASH_RES_t h49 = SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::hash(se121.modify0(s_nationkey));
                        HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode* n102 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode*>(i102->slice(se121, h49));
                        SUM_PROFITSUPPLIER11_P_2_entry* e102;
                       
                        if (n102 && (e102 = n102->obj)) {
                          do {                
                            STRING_TYPE profit_nation = e102->PROFIT_NATION;
                            long v103 = e102->__av;
                            SUM_PROFITORDERS13PART1.addOrDelOnZero(se120.modify(l_orderkey,p_partkey,profit_nation),(v101 * (v102 * v103)));
                            n102 = n102->nxt;
                          } while (n102 && (e102 = n102->obj) && h49 == n102->hash &&  SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::equals(se121, *e102)); 
                        }
                      }
                      n101 = n101->nxt;
                    } while (n101 && (e101 = n101->obj) && h50 == n101->hash &&  SUM_PROFITORDERS13SUPPLIER1_P_1PART1_mapkey2_idxfn::equals(se122, *e101)); 
                  }
                }
              n100 = n100->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01* i103 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01*>(SUM_PROFITSUPPLIER11_DELTA.index[0]);
          HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01::IdxNode* n103; 
          SUM_PROFITSUPPLIER11_DELTA_entry* e103;
        
          for (size_t i = 0; i < i103->size_; i++)
          {
            n103 = i103->buckets_ + i;
            while (n103 && (e103 = n103->obj))
            {
                long s_suppkey = e103->S_SUPPKEY;
                long s_nationkey = e103->S_NATIONKEY;
                long v104 = e103->__av;
                { //slice 
                  const HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0* i104 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0*>(SUM_PROFITSUPPLIER11_P_2.index[1]);
                  const HASH_RES_t h51 = SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::hash(se124.modify0(s_nationkey));
                  HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode* n104 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode*>(i104->slice(se124, h51));
                  SUM_PROFITSUPPLIER11_P_2_entry* e104;
                 
                  if (n104 && (e104 = n104->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e104->PROFIT_NATION;
                      long v105 = e104->__av;
                      SUM_PROFITLINEITEM11_P_2.addOrDelOnZero(se123.modify(s_suppkey,profit_nation),(v104 * v105));
                      n104 = n104->nxt;
                    } while (n104 && (e104 = n104->obj) && h51 == n104->hash &&  SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::equals(se124, *e104)); 
                  }
                }
              n103 = n103->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01* i105 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01*>(SUM_PROFITSUPPLIER11_DELTA.index[0]);
          HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01::IdxNode* n105; 
          SUM_PROFITSUPPLIER11_DELTA_entry* e105;
        
          for (size_t i = 0; i < i105->size_; i++)
          {
            n105 = i105->buckets_ + i;
            while (n105 && (e105 = n105->obj))
            {
                long s_suppkey = e105->S_SUPPKEY;
                long s_nationkey = e105->S_NATIONKEY;
                long v106 = e105->__av;
                { //slice 
                  const HashIndex_SUM_PROFITSUPPLIER11_P_1PART1_map_1* i106 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_1PART1_map_1*>(SUM_PROFITSUPPLIER11_P_1PART1.index[2]);
                  const HASH_RES_t h53 = SUM_PROFITSUPPLIER11_P_1PART1_mapkey1_idxfn::hash(se127.modify1(s_suppkey));
                  HashIndex_SUM_PROFITSUPPLIER11_P_1PART1_map_1::IdxNode* n106 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_1PART1_map_1::IdxNode*>(i106->slice(se127, h53));
                  SUM_PROFITSUPPLIER11_P_1PART1_entry* e106;
                 
                  if (n106 && (e106 = n106->obj)) {
                    do {                
                      long p_partkey = e106->P_PARTKEY;
                      long profit_o_year = e106->PROFIT_O_YEAR;
                      DOUBLE_TYPE v107 = e106->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0* i107 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0*>(SUM_PROFITSUPPLIER11_P_2.index[1]);
                        const HASH_RES_t h52 = SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::hash(se126.modify0(s_nationkey));
                        HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode* n107 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode*>(i107->slice(se126, h52));
                        SUM_PROFITSUPPLIER11_P_2_entry* e107;
                       
                        if (n107 && (e107 = n107->obj)) {
                          do {                
                            STRING_TYPE profit_nation = e107->PROFIT_NATION;
                            long v108 = e107->__av;
                            SUM_PROFITPART11.addOrDelOnZero(se125.modify(p_partkey,profit_o_year,profit_nation),(v106 * (v107 * v108)));
                            n107 = n107->nxt;
                          } while (n107 && (e107 = n107->obj) && h52 == n107->hash &&  SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::equals(se126, *e107)); 
                        }
                      }
                      n106 = n106->nxt;
                    } while (n106 && (e106 = n106->obj) && h53 == n106->hash &&  SUM_PROFITSUPPLIER11_P_1PART1_mapkey1_idxfn::equals(se127, *e106)); 
                  }
                }
              n105 = n105->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01* i108 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01*>(SUM_PROFITSUPPLIER11_DELTA.index[0]);
          HashIndex_SUM_PROFITSUPPLIER11_DELTA_map_01::IdxNode* n108; 
          SUM_PROFITSUPPLIER11_DELTA_entry* e108;
        
          for (size_t i = 0; i < i108->size_; i++)
          {
            n108 = i108->buckets_ + i;
            while (n108 && (e108 = n108->obj))
            {
                long s_suppkey = e108->S_SUPPKEY;
                long s_nationkey = e108->S_NATIONKEY;
                long v109 = e108->__av;
                { //slice 
                  const HashIndex_SUM_PROFITSUPPLIER13_P_1PART1_map_1* i109 = static_cast<HashIndex_SUM_PROFITSUPPLIER13_P_1PART1_map_1*>(SUM_PROFITSUPPLIER13_P_1PART1.index[2]);
                  const HASH_RES_t h55 = SUM_PROFITSUPPLIER13_P_1PART1_mapkey1_idxfn::hash(se130.modify1(s_suppkey));
                  HashIndex_SUM_PROFITSUPPLIER13_P_1PART1_map_1::IdxNode* n109 = static_cast<HashIndex_SUM_PROFITSUPPLIER13_P_1PART1_map_1::IdxNode*>(i109->slice(se130, h55));
                  SUM_PROFITSUPPLIER13_P_1PART1_entry* e109;
                 
                  if (n109 && (e109 = n109->obj)) {
                    do {                
                      long p_partkey = e109->P_PARTKEY;
                      long profit_o_year = e109->PROFIT_O_YEAR;
                      DOUBLE_TYPE v110 = e109->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0* i110 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0*>(SUM_PROFITSUPPLIER11_P_2.index[1]);
                        const HASH_RES_t h54 = SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::hash(se129.modify0(s_nationkey));
                        HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode* n110 = static_cast<HashIndex_SUM_PROFITSUPPLIER11_P_2_map_0::IdxNode*>(i110->slice(se129, h54));
                        SUM_PROFITSUPPLIER11_P_2_entry* e110;
                       
                        if (n110 && (e110 = n110->obj)) {
                          do {                
                            STRING_TYPE profit_nation = e110->PROFIT_NATION;
                            long v111 = e110->__av;
                            SUM_PROFITPART13.addOrDelOnZero(se128.modify(p_partkey,profit_o_year,profit_nation),(v109 * (v110 * v111)));
                            n110 = n110->nxt;
                          } while (n110 && (e110 = n110->obj) && h54 == n110->hash &&  SUM_PROFITSUPPLIER11_P_2_mapkey0_idxfn::equals(se129, *e110)); 
                        }
                      }
                      n109 = n109->nxt;
                    } while (n109 && (e109 = n109->obj) && h55 == n109->hash &&  SUM_PROFITSUPPLIER13_P_1PART1_mapkey1_idxfn::equals(se130, *e109)); 
                  }
                }
              n108 = n108->nxt;
            }
          }
        }
      }
    }
    void on_batch_update_PARTSUPP(TPCHPartSuppBatch& DELTA_PARTSUPP) {
      {  
        if (tS > 0) { tS += DELTA_PARTSUPP.size; return; }         
        tLastN += DELTA_PARTSUPP.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_PARTSUPP.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_PARTSUPP.size;

        SUM_PROFITPARTSUPP13_DELTA.clear();
        SUM_PROFITPARTSUPP11_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_PARTSUPP.size; i++)
          {
                long p_partkey = DELTA_PARTSUPP.partkey[i];
                long s_suppkey = DELTA_PARTSUPP.suppkey[i];
                long ps_availqty = DELTA_PARTSUPP.availqty[i];
                DOUBLE_TYPE ps_supplycost = DELTA_PARTSUPP.supplycost[i];
                STRING_TYPE ps_comment = DELTA_PARTSUPP.comment[i];
                long v112 = 1L;
                SUM_PROFITPARTSUPP13_DELTA.addOrDelOnZero(se131.modify(p_partkey,s_suppkey),v112);
                long v113 = 1L;
                SUM_PROFITPARTSUPP11_DELTA.addOrDelOnZero(se132.modify(p_partkey,s_suppkey),(v113 * ps_supplycost));
          }
        }
        {  // foreach
          const HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01* i113 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01*>(SUM_PROFITPARTSUPP11_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01::IdxNode* n113; 
          SUM_PROFITPARTSUPP11_DELTA_entry* e113;
        
          for (size_t i = 0; i < i113->size_; i++)
          {
            n113 = i113->buckets_ + i;
            while (n113 && (e113 = n113->obj))
            {
                long p_partkey = e113->P_PARTKEY;
                long s_suppkey = e113->S_SUPPKEY;
                DOUBLE_TYPE v114 = e113->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i114 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h57 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se136.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n114 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i114->slice(se136, h57));
                  SUM_PROFITLINEITEM11_P_2_entry* e114;
                 
                  if (n114 && (e114 = n114->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e114->PROFIT_NATION;
                      long v115 = e114->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01* i115 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01*>(SUM_PROFITPARTSUPP11_P_3.index[1]);
                        const HASH_RES_t h56 = SUM_PROFITPARTSUPP11_P_3_mapkey01_idxfn::hash(se135.modify01(p_partkey, s_suppkey));
                        HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01::IdxNode* n115 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01::IdxNode*>(i115->slice(se135, h56));
                        SUM_PROFITPARTSUPP11_P_3_entry* e115;
                       
                        if (n115 && (e115 = n115->obj)) {
                          do {                
                            long profit_o_year = e115->PROFIT_O_YEAR;
                            DOUBLE_TYPE v116 = e115->__av;
                            SUM_PROFIT.addOrDelOnZero(se133.modify(profit_nation,profit_o_year),((v114 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se134.modify(p_partkey)) * (v115 * v116))) * -1L));
                            n115 = n115->nxt;
                          } while (n115 && (e115 = n115->obj) && h56 == n115->hash &&  SUM_PROFITPARTSUPP11_P_3_mapkey01_idxfn::equals(se135, *e115)); 
                        }
                      }
                      n114 = n114->nxt;
                    } while (n114 && (e114 = n114->obj) && h57 == n114->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se136, *e114)); 
                  }
                }
              n113 = n113->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01* i116 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01*>(SUM_PROFITPARTSUPP13_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01::IdxNode* n116; 
          SUM_PROFITPARTSUPP13_DELTA_entry* e116;
        
          for (size_t i = 0; i < i116->size_; i++)
          {
            n116 = i116->buckets_ + i;
            while (n116 && (e116 = n116->obj))
            {
                long p_partkey = e116->P_PARTKEY;
                long s_suppkey = e116->S_SUPPKEY;
                long v117 = e116->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i117 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h59 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se139.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n117 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i117->slice(se139, h59));
                  SUM_PROFITLINEITEM11_P_2_entry* e117;
                 
                  if (n117 && (e117 = n117->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e117->PROFIT_NATION;
                      long v118 = e117->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01* i118 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01*>(SUM_PROFITPARTSUPP13_P_3.index[1]);
                        const HASH_RES_t h58 = SUM_PROFITPARTSUPP13_P_3_mapkey01_idxfn::hash(se138.modify01(p_partkey, s_suppkey));
                        HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01::IdxNode* n118 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01::IdxNode*>(i118->slice(se138, h58));
                        SUM_PROFITPARTSUPP13_P_3_entry* e118;
                       
                        if (n118 && (e118 = n118->obj)) {
                          do {                
                            long profit_o_year = e118->PROFIT_O_YEAR;
                            DOUBLE_TYPE v119 = e118->__av;
                            SUM_PROFIT.addOrDelOnZero(se133.modify(profit_nation,profit_o_year),(v117 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se137.modify(p_partkey)) * (v118 * v119))));
                            n118 = n118->nxt;
                          } while (n118 && (e118 = n118->obj) && h58 == n118->hash &&  SUM_PROFITPARTSUPP13_P_3_mapkey01_idxfn::equals(se138, *e118)); 
                        }
                      }
                      n117 = n117->nxt;
                    } while (n117 && (e117 = n117->obj) && h59 == n117->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se139, *e117)); 
                  }
                }
              n116 = n116->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01* i119 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01*>(SUM_PROFITPARTSUPP11_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01::IdxNode* n119; 
          SUM_PROFITPARTSUPP11_DELTA_entry* e119;
        
          for (size_t i = 0; i < i119->size_; i++)
          {
            n119 = i119->buckets_ + i;
            while (n119 && (e119 = n119->obj))
            {
                long p_partkey = e119->P_PARTKEY;
                long s_suppkey = e119->S_SUPPKEY;
                DOUBLE_TYPE v120 = e119->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i120 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h61 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se143.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n120 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i120->slice(se143, h61));
                  SUM_PROFITLINEITEM11_P_2_entry* e120;
                 
                  if (n120 && (e120 = n120->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e120->PROFIT_NATION;
                      long v121 = e120->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12* i121 = static_cast<HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12*>(SUM_PROFITORDERS11PARTSUPP1_P_3.index[2]);
                        const HASH_RES_t h60 = SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey12_idxfn::hash(se142.modify12(p_partkey, s_suppkey));
                        HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12::IdxNode* n121 = static_cast<HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12::IdxNode*>(i121->slice(se142, h60));
                        SUM_PROFITORDERS11PARTSUPP1_P_3_entry* e121;
                       
                        if (n121 && (e121 = n121->obj)) {
                          do {                
                            long l_orderkey = e121->L_ORDERKEY;
                            DOUBLE_TYPE v122 = e121->__av;
                            SUM_PROFITORDERS11.addOrDelOnZero(se140.modify(l_orderkey,profit_nation),(v120 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se141.modify(p_partkey)) * (v121 * v122))));
                            n121 = n121->nxt;
                          } while (n121 && (e121 = n121->obj) && h60 == n121->hash &&  SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey12_idxfn::equals(se142, *e121)); 
                        }
                      }
                      n120 = n120->nxt;
                    } while (n120 && (e120 = n120->obj) && h61 == n120->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se143, *e120)); 
                  }
                }
              n119 = n119->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01* i122 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01*>(SUM_PROFITPARTSUPP11_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01::IdxNode* n122; 
          SUM_PROFITPARTSUPP11_DELTA_entry* e122;
        
          for (size_t i = 0; i < i122->size_; i++)
          {
            n122 = i122->buckets_ + i;
            while (n122 && (e122 = n122->obj))
            {
                long p_partkey = e122->P_PARTKEY;
                long s_suppkey = e122->S_SUPPKEY;
                DOUBLE_TYPE v123 = e122->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12* i123 = static_cast<HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12*>(SUM_PROFITORDERS11PARTSUPP1_P_3.index[2]);
                  const HASH_RES_t h62 = SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey12_idxfn::hash(se146.modify12(p_partkey, s_suppkey));
                  HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12::IdxNode* n123 = static_cast<HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12::IdxNode*>(i123->slice(se146, h62));
                  SUM_PROFITORDERS11PARTSUPP1_P_3_entry* e123;
                 
                  if (n123 && (e123 = n123->obj)) {
                    do {                
                      long l_orderkey = e123->L_ORDERKEY;
                      DOUBLE_TYPE v124 = e123->__av;
                      SUM_PROFITORDERS11SUPPLIER1_P_1.addOrDelOnZero(se144.modify(l_orderkey,s_suppkey),(v123 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se145.modify(p_partkey)) * v124)));
                      n123 = n123->nxt;
                    } while (n123 && (e123 = n123->obj) && h62 == n123->hash &&  SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey12_idxfn::equals(se146, *e123)); 
                  }
                }
              n122 = n122->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01* i124 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01*>(SUM_PROFITPARTSUPP11_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01::IdxNode* n124; 
          SUM_PROFITPARTSUPP11_DELTA_entry* e124;
        
          for (size_t i = 0; i < i124->size_; i++)
          {
            n124 = i124->buckets_ + i;
            while (n124 && (e124 = n124->obj))
            {
                long p_partkey = e124->P_PARTKEY;
                long s_suppkey = e124->S_SUPPKEY;
                DOUBLE_TYPE v125 = e124->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12* i125 = static_cast<HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12*>(SUM_PROFITORDERS11PARTSUPP1_P_3.index[2]);
                  const HASH_RES_t h63 = SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey12_idxfn::hash(se148.modify12(p_partkey, s_suppkey));
                  HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12::IdxNode* n125 = static_cast<HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12::IdxNode*>(i125->slice(se148, h63));
                  SUM_PROFITORDERS11PARTSUPP1_P_3_entry* e125;
                 
                  if (n125 && (e125 = n125->obj)) {
                    do {                
                      long l_orderkey = e125->L_ORDERKEY;
                      DOUBLE_TYPE v126 = e125->__av;
                      SUM_PROFITORDERS11SUPPLIER1_P_1PART1.addOrDelOnZero(se147.modify(l_orderkey,p_partkey,s_suppkey),(v125 * v126));
                      n125 = n125->nxt;
                    } while (n125 && (e125 = n125->obj) && h63 == n125->hash &&  SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey12_idxfn::equals(se148, *e125)); 
                  }
                }
              n124 = n124->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01* i126 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01*>(SUM_PROFITPARTSUPP11_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01::IdxNode* n126; 
          SUM_PROFITPARTSUPP11_DELTA_entry* e126;
        
          for (size_t i = 0; i < i126->size_; i++)
          {
            n126 = i126->buckets_ + i;
            while (n126 && (e126 = n126->obj))
            {
                long p_partkey = e126->P_PARTKEY;
                long s_suppkey = e126->S_SUPPKEY;
                DOUBLE_TYPE v127 = e126->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i127 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h65 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se151.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n127 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i127->slice(se151, h65));
                  SUM_PROFITLINEITEM11_P_2_entry* e127;
                 
                  if (n127 && (e127 = n127->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e127->PROFIT_NATION;
                      long v128 = e127->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12* i128 = static_cast<HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12*>(SUM_PROFITORDERS11PARTSUPP1_P_3.index[2]);
                        const HASH_RES_t h64 = SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey12_idxfn::hash(se150.modify12(p_partkey, s_suppkey));
                        HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12::IdxNode* n128 = static_cast<HashIndex_SUM_PROFITORDERS11PARTSUPP1_P_3_map_12::IdxNode*>(i128->slice(se150, h64));
                        SUM_PROFITORDERS11PARTSUPP1_P_3_entry* e128;
                       
                        if (n128 && (e128 = n128->obj)) {
                          do {                
                            long l_orderkey = e128->L_ORDERKEY;
                            DOUBLE_TYPE v129 = e128->__av;
                            SUM_PROFITORDERS11PART1.addOrDelOnZero(se149.modify(l_orderkey,p_partkey,profit_nation),(v127 * (v128 * v129)));
                            n128 = n128->nxt;
                          } while (n128 && (e128 = n128->obj) && h64 == n128->hash &&  SUM_PROFITORDERS11PARTSUPP1_P_3_mapkey12_idxfn::equals(se150, *e128)); 
                        }
                      }
                      n127 = n127->nxt;
                    } while (n127 && (e127 = n127->obj) && h65 == n127->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se151, *e127)); 
                  }
                }
              n126 = n126->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01* i129 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01*>(SUM_PROFITPARTSUPP13_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01::IdxNode* n129; 
          SUM_PROFITPARTSUPP13_DELTA_entry* e129;
        
          for (size_t i = 0; i < i129->size_; i++)
          {
            n129 = i129->buckets_ + i;
            while (n129 && (e129 = n129->obj))
            {
                long p_partkey = e129->P_PARTKEY;
                long s_suppkey = e129->S_SUPPKEY;
                long v130 = e129->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i130 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h67 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se155.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n130 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i130->slice(se155, h67));
                  SUM_PROFITLINEITEM11_P_2_entry* e130;
                 
                  if (n130 && (e130 = n130->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e130->PROFIT_NATION;
                      long v131 = e130->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12* i131 = static_cast<HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12*>(SUM_PROFITORDERS13PARTSUPP1_P_3.index[2]);
                        const HASH_RES_t h66 = SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey12_idxfn::hash(se154.modify12(p_partkey, s_suppkey));
                        HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12::IdxNode* n131 = static_cast<HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12::IdxNode*>(i131->slice(se154, h66));
                        SUM_PROFITORDERS13PARTSUPP1_P_3_entry* e131;
                       
                        if (n131 && (e131 = n131->obj)) {
                          do {                
                            long l_orderkey = e131->L_ORDERKEY;
                            DOUBLE_TYPE v132 = e131->__av;
                            SUM_PROFITORDERS13.addOrDelOnZero(se152.modify(l_orderkey,profit_nation),(v130 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se153.modify(p_partkey)) * (v131 * v132))));
                            n131 = n131->nxt;
                          } while (n131 && (e131 = n131->obj) && h66 == n131->hash &&  SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey12_idxfn::equals(se154, *e131)); 
                        }
                      }
                      n130 = n130->nxt;
                    } while (n130 && (e130 = n130->obj) && h67 == n130->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se155, *e130)); 
                  }
                }
              n129 = n129->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01* i132 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01*>(SUM_PROFITPARTSUPP13_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01::IdxNode* n132; 
          SUM_PROFITPARTSUPP13_DELTA_entry* e132;
        
          for (size_t i = 0; i < i132->size_; i++)
          {
            n132 = i132->buckets_ + i;
            while (n132 && (e132 = n132->obj))
            {
                long p_partkey = e132->P_PARTKEY;
                long s_suppkey = e132->S_SUPPKEY;
                long v133 = e132->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12* i133 = static_cast<HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12*>(SUM_PROFITORDERS13PARTSUPP1_P_3.index[2]);
                  const HASH_RES_t h68 = SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey12_idxfn::hash(se158.modify12(p_partkey, s_suppkey));
                  HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12::IdxNode* n133 = static_cast<HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12::IdxNode*>(i133->slice(se158, h68));
                  SUM_PROFITORDERS13PARTSUPP1_P_3_entry* e133;
                 
                  if (n133 && (e133 = n133->obj)) {
                    do {                
                      long l_orderkey = e133->L_ORDERKEY;
                      DOUBLE_TYPE v134 = e133->__av;
                      SUM_PROFITORDERS13SUPPLIER1_P_1.addOrDelOnZero(se156.modify(l_orderkey,s_suppkey),(v133 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se157.modify(p_partkey)) * v134)));
                      n133 = n133->nxt;
                    } while (n133 && (e133 = n133->obj) && h68 == n133->hash &&  SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey12_idxfn::equals(se158, *e133)); 
                  }
                }
              n132 = n132->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01* i134 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01*>(SUM_PROFITPARTSUPP13_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01::IdxNode* n134; 
          SUM_PROFITPARTSUPP13_DELTA_entry* e134;
        
          for (size_t i = 0; i < i134->size_; i++)
          {
            n134 = i134->buckets_ + i;
            while (n134 && (e134 = n134->obj))
            {
                long p_partkey = e134->P_PARTKEY;
                long s_suppkey = e134->S_SUPPKEY;
                long v135 = e134->__av;
                { //slice 
                  const HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12* i135 = static_cast<HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12*>(SUM_PROFITORDERS13PARTSUPP1_P_3.index[2]);
                  const HASH_RES_t h69 = SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey12_idxfn::hash(se160.modify12(p_partkey, s_suppkey));
                  HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12::IdxNode* n135 = static_cast<HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12::IdxNode*>(i135->slice(se160, h69));
                  SUM_PROFITORDERS13PARTSUPP1_P_3_entry* e135;
                 
                  if (n135 && (e135 = n135->obj)) {
                    do {                
                      long l_orderkey = e135->L_ORDERKEY;
                      DOUBLE_TYPE v136 = e135->__av;
                      SUM_PROFITORDERS13SUPPLIER1_P_1PART1.addOrDelOnZero(se159.modify(l_orderkey,p_partkey,s_suppkey),(v135 * v136));
                      n135 = n135->nxt;
                    } while (n135 && (e135 = n135->obj) && h69 == n135->hash &&  SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey12_idxfn::equals(se160, *e135)); 
                  }
                }
              n134 = n134->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01* i136 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01*>(SUM_PROFITPARTSUPP13_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01::IdxNode* n136; 
          SUM_PROFITPARTSUPP13_DELTA_entry* e136;
        
          for (size_t i = 0; i < i136->size_; i++)
          {
            n136 = i136->buckets_ + i;
            while (n136 && (e136 = n136->obj))
            {
                long p_partkey = e136->P_PARTKEY;
                long s_suppkey = e136->S_SUPPKEY;
                long v137 = e136->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i137 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h71 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se163.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n137 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i137->slice(se163, h71));
                  SUM_PROFITLINEITEM11_P_2_entry* e137;
                 
                  if (n137 && (e137 = n137->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e137->PROFIT_NATION;
                      long v138 = e137->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12* i138 = static_cast<HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12*>(SUM_PROFITORDERS13PARTSUPP1_P_3.index[2]);
                        const HASH_RES_t h70 = SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey12_idxfn::hash(se162.modify12(p_partkey, s_suppkey));
                        HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12::IdxNode* n138 = static_cast<HashIndex_SUM_PROFITORDERS13PARTSUPP1_P_3_map_12::IdxNode*>(i138->slice(se162, h70));
                        SUM_PROFITORDERS13PARTSUPP1_P_3_entry* e138;
                       
                        if (n138 && (e138 = n138->obj)) {
                          do {                
                            long l_orderkey = e138->L_ORDERKEY;
                            DOUBLE_TYPE v139 = e138->__av;
                            SUM_PROFITORDERS13PART1.addOrDelOnZero(se161.modify(l_orderkey,p_partkey,profit_nation),(v137 * (v138 * v139)));
                            n138 = n138->nxt;
                          } while (n138 && (e138 = n138->obj) && h70 == n138->hash &&  SUM_PROFITORDERS13PARTSUPP1_P_3_mapkey12_idxfn::equals(se162, *e138)); 
                        }
                      }
                      n137 = n137->nxt;
                    } while (n137 && (e137 = n137->obj) && h71 == n137->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se163, *e137)); 
                  }
                }
              n136 = n136->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01* i139 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01*>(SUM_PROFITPARTSUPP11_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01::IdxNode* n139; 
          SUM_PROFITPARTSUPP11_DELTA_entry* e139;
        
          for (size_t i = 0; i < i139->size_; i++)
          {
            n139 = i139->buckets_ + i;
            while (n139 && (e139 = n139->obj))
            {
                long p_partkey = e139->P_PARTKEY;
                long s_suppkey = e139->S_SUPPKEY;
                DOUBLE_TYPE v140 = e139->__av;
                SUM_PROFITLINEITEM11_P_3.addOrDelOnZero(se164.modify(p_partkey,s_suppkey),v140);
              n139 = n139->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01* i140 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01*>(SUM_PROFITPARTSUPP13_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01::IdxNode* n140; 
          SUM_PROFITPARTSUPP13_DELTA_entry* e140;
        
          for (size_t i = 0; i < i140->size_; i++)
          {
            n140 = i140->buckets_ + i;
            while (n140 && (e140 = n140->obj))
            {
                long p_partkey = e140->P_PARTKEY;
                long s_suppkey = e140->S_SUPPKEY;
                long v141 = e140->__av;
                SUM_PROFITLINEITEM13_P_3.addOrDelOnZero(se165.modify(p_partkey,s_suppkey),v141);
              n140 = n140->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01* i141 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01*>(SUM_PROFITPARTSUPP11_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01::IdxNode* n141; 
          SUM_PROFITPARTSUPP11_DELTA_entry* e141;
        
          for (size_t i = 0; i < i141->size_; i++)
          {
            n141 = i141->buckets_ + i;
            while (n141 && (e141 = n141->obj))
            {
                long p_partkey = e141->P_PARTKEY;
                long s_suppkey = e141->S_SUPPKEY;
                DOUBLE_TYPE v142 = e141->__av;
                { //slice 
                  const HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01* i142 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01*>(SUM_PROFITPARTSUPP11_P_3.index[1]);
                  const HASH_RES_t h72 = SUM_PROFITPARTSUPP11_P_3_mapkey01_idxfn::hash(se168.modify01(p_partkey, s_suppkey));
                  HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01::IdxNode* n142 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01::IdxNode*>(i142->slice(se168, h72));
                  SUM_PROFITPARTSUPP11_P_3_entry* e142;
                 
                  if (n142 && (e142 = n142->obj)) {
                    do {                
                      long profit_o_year = e142->PROFIT_O_YEAR;
                      DOUBLE_TYPE v143 = e142->__av;
                      SUM_PROFITSUPPLIER11_P_1.addOrDelOnZero(se166.modify(s_suppkey,profit_o_year),(v142 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se167.modify(p_partkey)) * v143)));
                      n142 = n142->nxt;
                    } while (n142 && (e142 = n142->obj) && h72 == n142->hash &&  SUM_PROFITPARTSUPP11_P_3_mapkey01_idxfn::equals(se168, *e142)); 
                  }
                }
              n141 = n141->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01* i143 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01*>(SUM_PROFITPARTSUPP11_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01::IdxNode* n143; 
          SUM_PROFITPARTSUPP11_DELTA_entry* e143;
        
          for (size_t i = 0; i < i143->size_; i++)
          {
            n143 = i143->buckets_ + i;
            while (n143 && (e143 = n143->obj))
            {
                long p_partkey = e143->P_PARTKEY;
                long s_suppkey = e143->S_SUPPKEY;
                DOUBLE_TYPE v144 = e143->__av;
                { //slice 
                  const HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01* i144 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01*>(SUM_PROFITPARTSUPP11_P_3.index[1]);
                  const HASH_RES_t h73 = SUM_PROFITPARTSUPP11_P_3_mapkey01_idxfn::hash(se170.modify01(p_partkey, s_suppkey));
                  HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01::IdxNode* n144 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01::IdxNode*>(i144->slice(se170, h73));
                  SUM_PROFITPARTSUPP11_P_3_entry* e144;
                 
                  if (n144 && (e144 = n144->obj)) {
                    do {                
                      long profit_o_year = e144->PROFIT_O_YEAR;
                      DOUBLE_TYPE v145 = e144->__av;
                      SUM_PROFITSUPPLIER11_P_1PART1.addOrDelOnZero(se169.modify(p_partkey,s_suppkey,profit_o_year),(v144 * v145));
                      n144 = n144->nxt;
                    } while (n144 && (e144 = n144->obj) && h73 == n144->hash &&  SUM_PROFITPARTSUPP11_P_3_mapkey01_idxfn::equals(se170, *e144)); 
                  }
                }
              n143 = n143->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01* i145 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01*>(SUM_PROFITPARTSUPP13_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01::IdxNode* n145; 
          SUM_PROFITPARTSUPP13_DELTA_entry* e145;
        
          for (size_t i = 0; i < i145->size_; i++)
          {
            n145 = i145->buckets_ + i;
            while (n145 && (e145 = n145->obj))
            {
                long p_partkey = e145->P_PARTKEY;
                long s_suppkey = e145->S_SUPPKEY;
                long v146 = e145->__av;
                { //slice 
                  const HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01* i146 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01*>(SUM_PROFITPARTSUPP13_P_3.index[1]);
                  const HASH_RES_t h74 = SUM_PROFITPARTSUPP13_P_3_mapkey01_idxfn::hash(se173.modify01(p_partkey, s_suppkey));
                  HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01::IdxNode* n146 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01::IdxNode*>(i146->slice(se173, h74));
                  SUM_PROFITPARTSUPP13_P_3_entry* e146;
                 
                  if (n146 && (e146 = n146->obj)) {
                    do {                
                      long profit_o_year = e146->PROFIT_O_YEAR;
                      DOUBLE_TYPE v147 = e146->__av;
                      SUM_PROFITSUPPLIER13_P_1.addOrDelOnZero(se171.modify(s_suppkey,profit_o_year),(v146 * (SUM_PROFITLINEITEM11_P_1.getValueOrDefault(se172.modify(p_partkey)) * v147)));
                      n146 = n146->nxt;
                    } while (n146 && (e146 = n146->obj) && h74 == n146->hash &&  SUM_PROFITPARTSUPP13_P_3_mapkey01_idxfn::equals(se173, *e146)); 
                  }
                }
              n145 = n145->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01* i147 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01*>(SUM_PROFITPARTSUPP13_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01::IdxNode* n147; 
          SUM_PROFITPARTSUPP13_DELTA_entry* e147;
        
          for (size_t i = 0; i < i147->size_; i++)
          {
            n147 = i147->buckets_ + i;
            while (n147 && (e147 = n147->obj))
            {
                long p_partkey = e147->P_PARTKEY;
                long s_suppkey = e147->S_SUPPKEY;
                long v148 = e147->__av;
                { //slice 
                  const HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01* i148 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01*>(SUM_PROFITPARTSUPP13_P_3.index[1]);
                  const HASH_RES_t h75 = SUM_PROFITPARTSUPP13_P_3_mapkey01_idxfn::hash(se175.modify01(p_partkey, s_suppkey));
                  HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01::IdxNode* n148 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01::IdxNode*>(i148->slice(se175, h75));
                  SUM_PROFITPARTSUPP13_P_3_entry* e148;
                 
                  if (n148 && (e148 = n148->obj)) {
                    do {                
                      long profit_o_year = e148->PROFIT_O_YEAR;
                      DOUBLE_TYPE v149 = e148->__av;
                      SUM_PROFITSUPPLIER13_P_1PART1.addOrDelOnZero(se174.modify(p_partkey,s_suppkey,profit_o_year),(v148 * v149));
                      n148 = n148->nxt;
                    } while (n148 && (e148 = n148->obj) && h75 == n148->hash &&  SUM_PROFITPARTSUPP13_P_3_mapkey01_idxfn::equals(se175, *e148)); 
                  }
                }
              n147 = n147->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01* i149 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01*>(SUM_PROFITPARTSUPP11_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP11_DELTA_map_01::IdxNode* n149; 
          SUM_PROFITPARTSUPP11_DELTA_entry* e149;
        
          for (size_t i = 0; i < i149->size_; i++)
          {
            n149 = i149->buckets_ + i;
            while (n149 && (e149 = n149->obj))
            {
                long p_partkey = e149->P_PARTKEY;
                long s_suppkey = e149->S_SUPPKEY;
                DOUBLE_TYPE v150 = e149->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i150 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h77 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se178.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n150 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i150->slice(se178, h77));
                  SUM_PROFITLINEITEM11_P_2_entry* e150;
                 
                  if (n150 && (e150 = n150->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e150->PROFIT_NATION;
                      long v151 = e150->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01* i151 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01*>(SUM_PROFITPARTSUPP11_P_3.index[1]);
                        const HASH_RES_t h76 = SUM_PROFITPARTSUPP11_P_3_mapkey01_idxfn::hash(se177.modify01(p_partkey, s_suppkey));
                        HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01::IdxNode* n151 = static_cast<HashIndex_SUM_PROFITPARTSUPP11_P_3_map_01::IdxNode*>(i151->slice(se177, h76));
                        SUM_PROFITPARTSUPP11_P_3_entry* e151;
                       
                        if (n151 && (e151 = n151->obj)) {
                          do {                
                            long profit_o_year = e151->PROFIT_O_YEAR;
                            DOUBLE_TYPE v152 = e151->__av;
                            SUM_PROFITPART11.addOrDelOnZero(se176.modify(p_partkey,profit_o_year,profit_nation),(v150 * (v151 * v152)));
                            n151 = n151->nxt;
                          } while (n151 && (e151 = n151->obj) && h76 == n151->hash &&  SUM_PROFITPARTSUPP11_P_3_mapkey01_idxfn::equals(se177, *e151)); 
                        }
                      }
                      n150 = n150->nxt;
                    } while (n150 && (e150 = n150->obj) && h77 == n150->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se178, *e150)); 
                  }
                }
              n149 = n149->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01* i152 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01*>(SUM_PROFITPARTSUPP13_DELTA.index[0]);
          HashIndex_SUM_PROFITPARTSUPP13_DELTA_map_01::IdxNode* n152; 
          SUM_PROFITPARTSUPP13_DELTA_entry* e152;
        
          for (size_t i = 0; i < i152->size_; i++)
          {
            n152 = i152->buckets_ + i;
            while (n152 && (e152 = n152->obj))
            {
                long p_partkey = e152->P_PARTKEY;
                long s_suppkey = e152->S_SUPPKEY;
                long v153 = e152->__av;
                { //slice 
                  const HashIndex_SUM_PROFITLINEITEM11_P_2_map_0* i153 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0*>(SUM_PROFITLINEITEM11_P_2.index[1]);
                  const HASH_RES_t h79 = SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::hash(se181.modify0(s_suppkey));
                  HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode* n153 = static_cast<HashIndex_SUM_PROFITLINEITEM11_P_2_map_0::IdxNode*>(i153->slice(se181, h79));
                  SUM_PROFITLINEITEM11_P_2_entry* e153;
                 
                  if (n153 && (e153 = n153->obj)) {
                    do {                
                      STRING_TYPE profit_nation = e153->PROFIT_NATION;
                      long v154 = e153->__av;
                      { //slice 
                        const HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01* i154 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01*>(SUM_PROFITPARTSUPP13_P_3.index[1]);
                        const HASH_RES_t h78 = SUM_PROFITPARTSUPP13_P_3_mapkey01_idxfn::hash(se180.modify01(p_partkey, s_suppkey));
                        HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01::IdxNode* n154 = static_cast<HashIndex_SUM_PROFITPARTSUPP13_P_3_map_01::IdxNode*>(i154->slice(se180, h78));
                        SUM_PROFITPARTSUPP13_P_3_entry* e154;
                       
                        if (n154 && (e154 = n154->obj)) {
                          do {                
                            long profit_o_year = e154->PROFIT_O_YEAR;
                            DOUBLE_TYPE v155 = e154->__av;
                            SUM_PROFITPART13.addOrDelOnZero(se179.modify(p_partkey,profit_o_year,profit_nation),(v153 * (v154 * v155)));
                            n154 = n154->nxt;
                          } while (n154 && (e154 = n154->obj) && h78 == n154->hash &&  SUM_PROFITPARTSUPP13_P_3_mapkey01_idxfn::equals(se180, *e154)); 
                        }
                      }
                      n153 = n153->nxt;
                    } while (n153 && (e153 = n153->obj) && h79 == n153->hash &&  SUM_PROFITLINEITEM11_P_2_mapkey0_idxfn::equals(se181, *e153)); 
                  }
                }
              n152 = n152->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        SUM_PROFITSUPPLIER11_P_2.clear();
        {  // foreach
          const HashIndex_NATION_map_0123* i155 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n155; 
          NATION_entry* e155;
        
          for (size_t i = 0; i < i155->size_; i++)
          {
            n155 = i155->buckets_ + i;
            while (n155 && (e155 = n155->obj))
            {
                long s_nationkey = e155->NATION_NATIONKEY;
                STRING_TYPE n_name = e155->NATION_NAME;
                long n_regionkey = e155->NATION_REGIONKEY;
                STRING_TYPE n_comment = e155->NATION_COMMENT;
                long v156 = e155->__av;
                SUM_PROFITSUPPLIER11_P_2.addOrDelOnZero(se182.modify(s_nationkey,n_name),v156);
              n155 = n155->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    SUM_PROFITLINEITEM13_DELTA_entry se1;
    SUM_PROFITLINEITEM11_DELTA_entry se2;
    SUM_PROFIT_entry se3;
    SUM_PROFITLINEITEM11_P_1_entry se4;
    SUM_PROFITLINEITEM11_P_3_entry se5;
    SUM_PROFITLINEITEM11_P_4_entry se6;
    SUM_PROFITLINEITEM11_P_2_entry se7;
    SUM_PROFITLINEITEM11_P_1_entry se8;
    SUM_PROFITLINEITEM13_P_3_entry se9;
    SUM_PROFITLINEITEM11_P_4_entry se10;
    SUM_PROFITLINEITEM11_P_2_entry se11;
    SUM_PROFITORDERS11_entry se12;
    SUM_PROFITLINEITEM11_P_1_entry se13;
    SUM_PROFITLINEITEM11_P_3_entry se14;
    SUM_PROFITLINEITEM11_P_2_entry se15;
    SUM_PROFITORDERS11PARTSUPP1_P_3_entry se16;
    SUM_PROFITORDERS11SUPPLIER1_P_1_entry se17;
    SUM_PROFITLINEITEM11_P_1_entry se18;
    SUM_PROFITLINEITEM11_P_3_entry se19;
    SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry se20;
    SUM_PROFITLINEITEM11_P_3_entry se21;
    SUM_PROFITORDERS11PART1_entry se22;
    SUM_PROFITLINEITEM11_P_3_entry se23;
    SUM_PROFITLINEITEM11_P_2_entry se24;
    SUM_PROFITORDERS13_entry se25;
    SUM_PROFITLINEITEM11_P_1_entry se26;
    SUM_PROFITLINEITEM13_P_3_entry se27;
    SUM_PROFITLINEITEM11_P_2_entry se28;
    SUM_PROFITORDERS13PARTSUPP1_P_3_entry se29;
    SUM_PROFITORDERS13SUPPLIER1_P_1_entry se30;
    SUM_PROFITLINEITEM11_P_1_entry se31;
    SUM_PROFITLINEITEM13_P_3_entry se32;
    SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry se33;
    SUM_PROFITLINEITEM13_P_3_entry se34;
    SUM_PROFITORDERS13PART1_entry se35;
    SUM_PROFITLINEITEM13_P_3_entry se36;
    SUM_PROFITLINEITEM11_P_2_entry se37;
    SUM_PROFITPARTSUPP11_P_3_entry se38;
    SUM_PROFITLINEITEM11_P_4_entry se39;
    SUM_PROFITPARTSUPP13_P_3_entry se40;
    SUM_PROFITLINEITEM11_P_4_entry se41;
    SUM_PROFITSUPPLIER11_P_1_entry se42;
    SUM_PROFITLINEITEM11_P_1_entry se43;
    SUM_PROFITLINEITEM11_P_3_entry se44;
    SUM_PROFITLINEITEM11_P_4_entry se45;
    SUM_PROFITSUPPLIER11_P_1PART1_entry se46;
    SUM_PROFITLINEITEM11_P_3_entry se47;
    SUM_PROFITLINEITEM11_P_4_entry se48;
    SUM_PROFITSUPPLIER13_P_1_entry se49;
    SUM_PROFITLINEITEM11_P_1_entry se50;
    SUM_PROFITLINEITEM13_P_3_entry se51;
    SUM_PROFITLINEITEM11_P_4_entry se52;
    SUM_PROFITSUPPLIER13_P_1PART1_entry se53;
    SUM_PROFITLINEITEM13_P_3_entry se54;
    SUM_PROFITLINEITEM11_P_4_entry se55;
    SUM_PROFITPART11_entry se56;
    SUM_PROFITLINEITEM11_P_3_entry se57;
    SUM_PROFITLINEITEM11_P_4_entry se58;
    SUM_PROFITLINEITEM11_P_2_entry se59;
    SUM_PROFITPART13_entry se60;
    SUM_PROFITLINEITEM13_P_3_entry se61;
    SUM_PROFITLINEITEM11_P_4_entry se62;
    SUM_PROFITLINEITEM11_P_2_entry se63;
    SUM_PROFITORDERS11_DELTA_entry se64;
    SUM_PROFITORDERS11_DOMAIN1_entry se65;
    SUM_PROFIT_entry se66;
    tuple2_S_D st1;
    SUM_PROFITORDERS11_entry se67;
    SUM_PROFITORDERS11_DELTA_entry se68;
    tuple2_S_D st2;
    SUM_PROFITORDERS13_entry se69;
    SUM_PROFITORDERS11_DELTA_entry se70;
    SUM_PROFITPARTSUPP11_P_3_entry se71;
    SUM_PROFITORDERS11PARTSUPP1_P_3_entry se72;
    SUM_PROFITPARTSUPP13_P_3_entry se73;
    SUM_PROFITORDERS13PARTSUPP1_P_3_entry se74;
    SUM_PROFITLINEITEM11_P_4_entry se75;
    SUM_PROFITSUPPLIER11_P_1_entry se76;
    SUM_PROFITORDERS11SUPPLIER1_P_1_entry se77;
    SUM_PROFITSUPPLIER11_P_1PART1_entry se78;
    SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry se79;
    SUM_PROFITSUPPLIER13_P_1_entry se80;
    SUM_PROFITORDERS13SUPPLIER1_P_1_entry se81;
    SUM_PROFITSUPPLIER13_P_1PART1_entry se82;
    SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry se83;
    SUM_PROFITPART11_entry se84;
    SUM_PROFITORDERS11PART1_entry se85;
    SUM_PROFITPART13_entry se86;
    SUM_PROFITORDERS13PART1_entry se87;
    SUM_PROFITPART11_DELTA_entry se88;
    SUM_PROFIT_entry se89;
    SUM_PROFITPART11_entry se90;
    SUM_PROFITPART13_entry se91;
    SUM_PROFITORDERS11_entry se92;
    SUM_PROFITORDERS11PART1_entry se93;
    SUM_PROFITORDERS11SUPPLIER1_P_1_entry se94;
    SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry se95;
    SUM_PROFITORDERS13_entry se96;
    SUM_PROFITORDERS13PART1_entry se97;
    SUM_PROFITORDERS13SUPPLIER1_P_1_entry se98;
    SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry se99;
    SUM_PROFITLINEITEM11_P_1_entry se100;
    SUM_PROFITSUPPLIER11_P_1_entry se101;
    SUM_PROFITSUPPLIER11_P_1PART1_entry se102;
    SUM_PROFITSUPPLIER13_P_1_entry se103;
    SUM_PROFITSUPPLIER13_P_1PART1_entry se104;
    SUM_PROFITSUPPLIER11_DELTA_entry se105;
    SUM_PROFIT_entry se106;
    SUM_PROFITSUPPLIER11_P_2_entry se107;
    SUM_PROFITSUPPLIER11_P_1_entry se108;
    SUM_PROFITSUPPLIER11_P_2_entry se109;
    SUM_PROFITSUPPLIER13_P_1_entry se110;
    SUM_PROFITORDERS11_entry se111;
    SUM_PROFITSUPPLIER11_P_2_entry se112;
    SUM_PROFITORDERS11SUPPLIER1_P_1_entry se113;
    SUM_PROFITORDERS11PART1_entry se114;
    SUM_PROFITSUPPLIER11_P_2_entry se115;
    SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry se116;
    SUM_PROFITORDERS13_entry se117;
    SUM_PROFITSUPPLIER11_P_2_entry se118;
    SUM_PROFITORDERS13SUPPLIER1_P_1_entry se119;
    SUM_PROFITORDERS13PART1_entry se120;
    SUM_PROFITSUPPLIER11_P_2_entry se121;
    SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry se122;
    SUM_PROFITLINEITEM11_P_2_entry se123;
    SUM_PROFITSUPPLIER11_P_2_entry se124;
    SUM_PROFITPART11_entry se125;
    SUM_PROFITSUPPLIER11_P_2_entry se126;
    SUM_PROFITSUPPLIER11_P_1PART1_entry se127;
    SUM_PROFITPART13_entry se128;
    SUM_PROFITSUPPLIER11_P_2_entry se129;
    SUM_PROFITSUPPLIER13_P_1PART1_entry se130;
    SUM_PROFITPARTSUPP13_DELTA_entry se131;
    SUM_PROFITPARTSUPP11_DELTA_entry se132;
    SUM_PROFIT_entry se133;
    SUM_PROFITLINEITEM11_P_1_entry se134;
    SUM_PROFITPARTSUPP11_P_3_entry se135;
    SUM_PROFITLINEITEM11_P_2_entry se136;
    SUM_PROFITLINEITEM11_P_1_entry se137;
    SUM_PROFITPARTSUPP13_P_3_entry se138;
    SUM_PROFITLINEITEM11_P_2_entry se139;
    SUM_PROFITORDERS11_entry se140;
    SUM_PROFITLINEITEM11_P_1_entry se141;
    SUM_PROFITORDERS11PARTSUPP1_P_3_entry se142;
    SUM_PROFITLINEITEM11_P_2_entry se143;
    SUM_PROFITORDERS11SUPPLIER1_P_1_entry se144;
    SUM_PROFITLINEITEM11_P_1_entry se145;
    SUM_PROFITORDERS11PARTSUPP1_P_3_entry se146;
    SUM_PROFITORDERS11SUPPLIER1_P_1PART1_entry se147;
    SUM_PROFITORDERS11PARTSUPP1_P_3_entry se148;
    SUM_PROFITORDERS11PART1_entry se149;
    SUM_PROFITORDERS11PARTSUPP1_P_3_entry se150;
    SUM_PROFITLINEITEM11_P_2_entry se151;
    SUM_PROFITORDERS13_entry se152;
    SUM_PROFITLINEITEM11_P_1_entry se153;
    SUM_PROFITORDERS13PARTSUPP1_P_3_entry se154;
    SUM_PROFITLINEITEM11_P_2_entry se155;
    SUM_PROFITORDERS13SUPPLIER1_P_1_entry se156;
    SUM_PROFITLINEITEM11_P_1_entry se157;
    SUM_PROFITORDERS13PARTSUPP1_P_3_entry se158;
    SUM_PROFITORDERS13SUPPLIER1_P_1PART1_entry se159;
    SUM_PROFITORDERS13PARTSUPP1_P_3_entry se160;
    SUM_PROFITORDERS13PART1_entry se161;
    SUM_PROFITORDERS13PARTSUPP1_P_3_entry se162;
    SUM_PROFITLINEITEM11_P_2_entry se163;
    SUM_PROFITLINEITEM11_P_3_entry se164;
    SUM_PROFITLINEITEM13_P_3_entry se165;
    SUM_PROFITSUPPLIER11_P_1_entry se166;
    SUM_PROFITLINEITEM11_P_1_entry se167;
    SUM_PROFITPARTSUPP11_P_3_entry se168;
    SUM_PROFITSUPPLIER11_P_1PART1_entry se169;
    SUM_PROFITPARTSUPP11_P_3_entry se170;
    SUM_PROFITSUPPLIER13_P_1_entry se171;
    SUM_PROFITLINEITEM11_P_1_entry se172;
    SUM_PROFITPARTSUPP13_P_3_entry se173;
    SUM_PROFITSUPPLIER13_P_1PART1_entry se174;
    SUM_PROFITPARTSUPP13_P_3_entry se175;
    SUM_PROFITPART11_entry se176;
    SUM_PROFITPARTSUPP11_P_3_entry se177;
    SUM_PROFITLINEITEM11_P_2_entry se178;
    SUM_PROFITPART13_entry se179;
    SUM_PROFITPARTSUPP13_P_3_entry se180;
    SUM_PROFITLINEITEM11_P_2_entry se181;
    SUM_PROFITSUPPLIER11_P_2_entry se182;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    SUM_PROFITORDERS11_DOMAIN1_map SUM_PROFITORDERS11_DOMAIN1;
    SUM_PROFITORDERS11_DELTA_map SUM_PROFITORDERS11_DELTA;
    SUM_PROFITORDERS11_map SUM_PROFITORDERS11;
    SUM_PROFITORDERS11PARTSUPP1_P_3_map SUM_PROFITORDERS11PARTSUPP1_P_3;
    SUM_PROFITORDERS11SUPPLIER1_P_1_map SUM_PROFITORDERS11SUPPLIER1_P_1;
    SUM_PROFITORDERS11SUPPLIER1_P_1PART1_map SUM_PROFITORDERS11SUPPLIER1_P_1PART1;
    SUM_PROFITORDERS11PART1_map SUM_PROFITORDERS11PART1;
    SUM_PROFITORDERS13_map SUM_PROFITORDERS13;
    SUM_PROFITORDERS13PARTSUPP1_P_3_map SUM_PROFITORDERS13PARTSUPP1_P_3;
    SUM_PROFITORDERS13SUPPLIER1_P_1_map SUM_PROFITORDERS13SUPPLIER1_P_1;
    SUM_PROFITORDERS13SUPPLIER1_P_1PART1_map SUM_PROFITORDERS13SUPPLIER1_P_1PART1;
    SUM_PROFITORDERS13PART1_map SUM_PROFITORDERS13PART1;
    SUM_PROFITPARTSUPP11_DELTA_map SUM_PROFITPARTSUPP11_DELTA;
    SUM_PROFITPARTSUPP11_P_3_map SUM_PROFITPARTSUPP11_P_3;
    SUM_PROFITPARTSUPP13_DELTA_map SUM_PROFITPARTSUPP13_DELTA;
    SUM_PROFITPARTSUPP13_P_3_map SUM_PROFITPARTSUPP13_P_3;
    SUM_PROFITLINEITEM11_DELTA_map SUM_PROFITLINEITEM11_DELTA;
    SUM_PROFITLINEITEM11_P_1_map SUM_PROFITLINEITEM11_P_1;
    SUM_PROFITLINEITEM11_P_2_map SUM_PROFITLINEITEM11_P_2;
    SUM_PROFITLINEITEM11_P_3_map SUM_PROFITLINEITEM11_P_3;
    SUM_PROFITLINEITEM11_P_4_map SUM_PROFITLINEITEM11_P_4;
    SUM_PROFITLINEITEM13_DELTA_map SUM_PROFITLINEITEM13_DELTA;
    SUM_PROFITLINEITEM13_P_3_map SUM_PROFITLINEITEM13_P_3;
    SUM_PROFITSUPPLIER11_DELTA_map SUM_PROFITSUPPLIER11_DELTA;
    SUM_PROFITSUPPLIER11_P_1_map SUM_PROFITSUPPLIER11_P_1;
    SUM_PROFITSUPPLIER11_P_1PART1_map SUM_PROFITSUPPLIER11_P_1PART1;
    SUM_PROFITSUPPLIER11_P_2_map SUM_PROFITSUPPLIER11_P_2;
    SUM_PROFITSUPPLIER13_P_1_map SUM_PROFITSUPPLIER13_P_1;
    SUM_PROFITSUPPLIER13_P_1PART1_map SUM_PROFITSUPPLIER13_P_1PART1;
    SUM_PROFITPART11_DELTA_map SUM_PROFITPART11_DELTA;
    SUM_PROFITPART11_map SUM_PROFITPART11;
    SUM_PROFITPART13_map SUM_PROFITPART13;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_ORDERS_map DELTA_ORDERS;
    DELTA_PART_map DELTA_PART;
    DELTA_SUPPLIER_map DELTA_SUPPLIER;
    DELTA_PARTSUPP_map DELTA_PARTSUPP;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c1;
    
  
  };

}
