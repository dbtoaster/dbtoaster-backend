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
  
  struct NUMWAIT_entry {
    STRING_TYPE S_NAME; long __av; 
    explicit NUMWAIT_entry() { /*S_NAME = ""; __av = 0L; */ }
    explicit NUMWAIT_entry(const STRING_TYPE& c0, const long c1) { S_NAME = c0; __av = c1; }
    NUMWAIT_entry(const NUMWAIT_entry& other) : S_NAME( other.S_NAME ), __av( other.__av ) {}
    FORCE_INLINE NUMWAIT_entry& modify(const STRING_TYPE& c0) { S_NAME = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAIT_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_entry& x, const NUMWAIT_entry& y) {
      return x.S_NAME == y.S_NAME;
    }
  };
  
  typedef MultiHashMap<NUMWAIT_entry,long,
    HashIndex<NUMWAIT_entry,long,NUMWAIT_mapkey0_idxfn,true>
  > NUMWAIT_map;
  typedef HashIndex<NUMWAIT_entry,long,NUMWAIT_mapkey0_idxfn,true> HashIndex_NUMWAIT_map_0;
  
  struct NUMWAITORDERS1_DELTA_entry {
    long L1_ORDERKEY; long __av; 
    explicit NUMWAITORDERS1_DELTA_entry() { /*L1_ORDERKEY = 0L; __av = 0L; */ }
    explicit NUMWAITORDERS1_DELTA_entry(const long c0, const long c1) { L1_ORDERKEY = c0; __av = c1; }
    NUMWAITORDERS1_DELTA_entry(const NUMWAITORDERS1_DELTA_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITORDERS1_DELTA_entry& modify(const long c0) { L1_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITORDERS1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITORDERS1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITORDERS1_DELTA_entry& x, const NUMWAITORDERS1_DELTA_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITORDERS1_DELTA_entry,long,
    HashIndex<NUMWAITORDERS1_DELTA_entry,long,NUMWAITORDERS1_DELTA_mapkey0_idxfn,true>
  > NUMWAITORDERS1_DELTA_map;
  typedef HashIndex<NUMWAITORDERS1_DELTA_entry,long,NUMWAITORDERS1_DELTA_mapkey0_idxfn,true> HashIndex_NUMWAITORDERS1_DELTA_map_0;
  
  struct NUMWAITORDERS1_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; long L1_ORDERKEY; long __av; 
    explicit NUMWAITORDERS1_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; L1_ORDERKEY = 0L; __av = 0L; */ }
    explicit NUMWAITORDERS1_entry(const long c0, const STRING_TYPE& c1, const long c2, const long c3) { S_SUPPKEY = c0; S_NAME = c1; L1_ORDERKEY = c2; __av = c3; }
    NUMWAITORDERS1_entry(const NUMWAITORDERS1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), L1_ORDERKEY( other.L1_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITORDERS1_entry& modify(const long c0, const STRING_TYPE& c1, const long c2) { S_SUPPKEY = c0; S_NAME = c1; L1_ORDERKEY = c2;  return *this; }
    FORCE_INLINE NUMWAITORDERS1_entry& modify2(const long c2) { L1_ORDERKEY = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITORDERS1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.L1_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITORDERS1_entry& x, const NUMWAITORDERS1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.L1_ORDERKEY == y.L1_ORDERKEY;
    }
  };
  
  struct NUMWAITORDERS1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITORDERS1_entry& x, const NUMWAITORDERS1_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITORDERS1_entry,long,
    HashIndex<NUMWAITORDERS1_entry,long,NUMWAITORDERS1_mapkey012_idxfn,true>,
    HashIndex<NUMWAITORDERS1_entry,long,NUMWAITORDERS1_mapkey2_idxfn,false>
  > NUMWAITORDERS1_map;
  typedef HashIndex<NUMWAITORDERS1_entry,long,NUMWAITORDERS1_mapkey012_idxfn,true> HashIndex_NUMWAITORDERS1_map_012;
  typedef HashIndex<NUMWAITORDERS1_entry,long,NUMWAITORDERS1_mapkey2_idxfn,false> HashIndex_NUMWAITORDERS1_map_2;
  
  struct NUMWAITORDERS1LINEITEM1_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; long __av; 
    explicit NUMWAITORDERS1LINEITEM1_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; __av = 0L; */ }
    explicit NUMWAITORDERS1LINEITEM1_entry(const long c0, const STRING_TYPE& c1, const long c2) { S_SUPPKEY = c0; S_NAME = c1; __av = c2; }
    NUMWAITORDERS1LINEITEM1_entry(const NUMWAITORDERS1LINEITEM1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITORDERS1LINEITEM1_entry& modify(const long c0, const STRING_TYPE& c1) { S_SUPPKEY = c0; S_NAME = c1;  return *this; }
    FORCE_INLINE NUMWAITORDERS1LINEITEM1_entry& modify0(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITORDERS1LINEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITORDERS1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITORDERS1LINEITEM1_entry& x, const NUMWAITORDERS1LINEITEM1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME;
    }
  };
  
  struct NUMWAITORDERS1LINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITORDERS1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITORDERS1LINEITEM1_entry& x, const NUMWAITORDERS1LINEITEM1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITORDERS1LINEITEM1_entry,long,
    HashIndex<NUMWAITORDERS1LINEITEM1_entry,long,NUMWAITORDERS1LINEITEM1_mapkey01_idxfn,true>,
    HashIndex<NUMWAITORDERS1LINEITEM1_entry,long,NUMWAITORDERS1LINEITEM1_mapkey0_idxfn,false>
  > NUMWAITORDERS1LINEITEM1_map;
  typedef HashIndex<NUMWAITORDERS1LINEITEM1_entry,long,NUMWAITORDERS1LINEITEM1_mapkey01_idxfn,true> HashIndex_NUMWAITORDERS1LINEITEM1_map_01;
  typedef HashIndex<NUMWAITORDERS1LINEITEM1_entry,long,NUMWAITORDERS1LINEITEM1_mapkey0_idxfn,false> HashIndex_NUMWAITORDERS1LINEITEM1_map_0;
  
  struct NUMWAITLINEITEM1_DOMAIN1_P_3_entry {
    long L1_ORDERKEY; long __av; 
    explicit NUMWAITLINEITEM1_DOMAIN1_P_3_entry() { /*L1_ORDERKEY = 0L; __av = 0L; */ }
    explicit NUMWAITLINEITEM1_DOMAIN1_P_3_entry(const long c0, const long c1) { L1_ORDERKEY = c0; __av = c1; }
    NUMWAITLINEITEM1_DOMAIN1_P_3_entry(const NUMWAITLINEITEM1_DOMAIN1_P_3_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITLINEITEM1_DOMAIN1_P_3_entry& modify(const long c0) { L1_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITLINEITEM1_DOMAIN1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM1_DOMAIN1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM1_DOMAIN1_P_3_entry& x, const NUMWAITLINEITEM1_DOMAIN1_P_3_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITLINEITEM1_DOMAIN1_P_3_entry,long,
    HashIndex<NUMWAITLINEITEM1_DOMAIN1_P_3_entry,long,NUMWAITLINEITEM1_DOMAIN1_P_3_mapkey0_idxfn,true>
  > NUMWAITLINEITEM1_DOMAIN1_P_3_map;
  typedef HashIndex<NUMWAITLINEITEM1_DOMAIN1_P_3_entry,long,NUMWAITLINEITEM1_DOMAIN1_P_3_mapkey0_idxfn,true> HashIndex_NUMWAITLINEITEM1_DOMAIN1_P_3_map_0;
  
  struct NUMWAITLINEITEM1_P_3_entry {
    STRING_TYPE N_NAME; long L1_ORDERKEY; long S_SUPPKEY; STRING_TYPE S_NAME; long __av; 
    explicit NUMWAITLINEITEM1_P_3_entry() { /*N_NAME = ""; L1_ORDERKEY = 0L; S_SUPPKEY = 0L; S_NAME = ""; __av = 0L; */ }
    explicit NUMWAITLINEITEM1_P_3_entry(const STRING_TYPE& c0, const long c1, const long c2, const STRING_TYPE& c3, const long c4) { N_NAME = c0; L1_ORDERKEY = c1; S_SUPPKEY = c2; S_NAME = c3; __av = c4; }
    NUMWAITLINEITEM1_P_3_entry(const NUMWAITLINEITEM1_P_3_entry& other) : N_NAME( other.N_NAME ), L1_ORDERKEY( other.L1_ORDERKEY ), S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITLINEITEM1_P_3_entry& modify(const STRING_TYPE& c0, const long c1, const long c2, const STRING_TYPE& c3) { N_NAME = c0; L1_ORDERKEY = c1; S_SUPPKEY = c2; S_NAME = c3;  return *this; }
    FORCE_INLINE NUMWAITLINEITEM1_P_3_entry& modify01(const STRING_TYPE& c0, const long c1) { N_NAME = c0; L1_ORDERKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITLINEITEM1_P_3_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.N_NAME);
      hash_combine(h, e.L1_ORDERKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM1_P_3_entry& x, const NUMWAITLINEITEM1_P_3_entry& y) {
      return x.N_NAME == y.N_NAME && x.L1_ORDERKEY == y.L1_ORDERKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME;
    }
  };
  
  struct NUMWAITLINEITEM1_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.N_NAME);
      hash_combine(h, e.L1_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM1_P_3_entry& x, const NUMWAITLINEITEM1_P_3_entry& y) {
      return x.N_NAME == y.N_NAME && x.L1_ORDERKEY == y.L1_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITLINEITEM1_P_3_entry,long,
    HashIndex<NUMWAITLINEITEM1_P_3_entry,long,NUMWAITLINEITEM1_P_3_mapkey0123_idxfn,true>,
    HashIndex<NUMWAITLINEITEM1_P_3_entry,long,NUMWAITLINEITEM1_P_3_mapkey01_idxfn,false>
  > NUMWAITLINEITEM1_P_3_map;
  typedef HashIndex<NUMWAITLINEITEM1_P_3_entry,long,NUMWAITLINEITEM1_P_3_mapkey0123_idxfn,true> HashIndex_NUMWAITLINEITEM1_P_3_map_0123;
  typedef HashIndex<NUMWAITLINEITEM1_P_3_entry,long,NUMWAITLINEITEM1_P_3_mapkey01_idxfn,false> HashIndex_NUMWAITLINEITEM1_P_3_map_01;
  
  struct NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry {
    long S_NATIONKEY; STRING_TYPE N_NAME; long __av; 
    explicit NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry() { /*S_NATIONKEY = 0L; N_NAME = ""; __av = 0L; */ }
    explicit NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry(const long c0, const STRING_TYPE& c1, const long c2) { S_NATIONKEY = c0; N_NAME = c1; __av = c2; }
    NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry(const NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry& other) : S_NATIONKEY( other.S_NATIONKEY ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry& modify(const long c0, const STRING_TYPE& c1) { S_NATIONKEY = c0; N_NAME = c1;  return *this; }
    FORCE_INLINE NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry& modify0(const long c0) { S_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry& x, const NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  struct NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry& x, const NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry,long,
    HashIndex<NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry,long,NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_mapkey01_idxfn,true>,
    HashIndex<NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry,long,NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_mapkey0_idxfn,false>
  > NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_map;
  typedef HashIndex<NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry,long,NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_mapkey01_idxfn,true> HashIndex_NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_map_01;
  typedef HashIndex<NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry,long,NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_mapkey0_idxfn,false> HashIndex_NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_map_0;
  
  struct NUMWAITLINEITEM1_P_4_entry {
    long L1_ORDERKEY; STRING_TYPE O_ORDERSTATUS; long __av; 
    explicit NUMWAITLINEITEM1_P_4_entry() { /*L1_ORDERKEY = 0L; O_ORDERSTATUS = ""; __av = 0L; */ }
    explicit NUMWAITLINEITEM1_P_4_entry(const long c0, const STRING_TYPE& c1, const long c2) { L1_ORDERKEY = c0; O_ORDERSTATUS = c1; __av = c2; }
    NUMWAITLINEITEM1_P_4_entry(const NUMWAITLINEITEM1_P_4_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), O_ORDERSTATUS( other.O_ORDERSTATUS ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITLINEITEM1_P_4_entry& modify(const long c0, const STRING_TYPE& c1) { L1_ORDERKEY = c0; O_ORDERSTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERSTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITLINEITEM1_P_4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM1_P_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      hash_combine(h, e.O_ORDERSTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM1_P_4_entry& x, const NUMWAITLINEITEM1_P_4_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY && x.O_ORDERSTATUS == y.O_ORDERSTATUS;
    }
  };
  
  typedef MultiHashMap<NUMWAITLINEITEM1_P_4_entry,long,
    HashIndex<NUMWAITLINEITEM1_P_4_entry,long,NUMWAITLINEITEM1_P_4_mapkey01_idxfn,true>
  > NUMWAITLINEITEM1_P_4_map;
  typedef HashIndex<NUMWAITLINEITEM1_P_4_entry,long,NUMWAITLINEITEM1_P_4_mapkey01_idxfn,true> HashIndex_NUMWAITLINEITEM1_P_4_map_01;
  
  struct NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry {
    long L1_ORDERKEY; STRING_TYPE O_ORDERSTATUS; long __av; 
    explicit NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry() { /*L1_ORDERKEY = 0L; O_ORDERSTATUS = ""; __av = 0L; */ }
    explicit NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { L1_ORDERKEY = c0; O_ORDERSTATUS = c1; __av = c2; }
    NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry(const NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), O_ORDERSTATUS( other.O_ORDERSTATUS ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { L1_ORDERKEY = c0; O_ORDERSTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERSTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITLINEITEM1_P_4ORDERS1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      hash_combine(h, e.O_ORDERSTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry& x, const NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY && x.O_ORDERSTATUS == y.O_ORDERSTATUS;
    }
  };
  
  typedef MultiHashMap<NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry,long,
    HashIndex<NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry,long,NUMWAITLINEITEM1_P_4ORDERS1_DELTA_mapkey01_idxfn,true>
  > NUMWAITLINEITEM1_P_4ORDERS1_DELTA_map;
  typedef HashIndex<NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry,long,NUMWAITLINEITEM1_P_4ORDERS1_DELTA_mapkey01_idxfn,true> HashIndex_NUMWAITLINEITEM1_P_4ORDERS1_DELTA_map_01;
  
  struct NUMWAITLINEITEM3_L2_2_DELTA_entry {
    long L1_ORDERKEY; long L3_SUPPKEY; long __av; 
    explicit NUMWAITLINEITEM3_L2_2_DELTA_entry() { /*L1_ORDERKEY = 0L; L3_SUPPKEY = 0L; __av = 0L; */ }
    explicit NUMWAITLINEITEM3_L2_2_DELTA_entry(const long c0, const long c1, const long c2) { L1_ORDERKEY = c0; L3_SUPPKEY = c1; __av = c2; }
    NUMWAITLINEITEM3_L2_2_DELTA_entry(const NUMWAITLINEITEM3_L2_2_DELTA_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), L3_SUPPKEY( other.L3_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITLINEITEM3_L2_2_DELTA_entry& modify(const long c0, const long c1) { L1_ORDERKEY = c0; L3_SUPPKEY = c1;  return *this; }
    FORCE_INLINE NUMWAITLINEITEM3_L2_2_DELTA_entry& modify0(const long c0) { L1_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L3_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITLINEITEM3_L2_2_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM3_L2_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      hash_combine(h, e.L3_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM3_L2_2_DELTA_entry& x, const NUMWAITLINEITEM3_L2_2_DELTA_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY && x.L3_SUPPKEY == y.L3_SUPPKEY;
    }
  };
  
  struct NUMWAITLINEITEM3_L2_2_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM3_L2_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM3_L2_2_DELTA_entry& x, const NUMWAITLINEITEM3_L2_2_DELTA_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITLINEITEM3_L2_2_DELTA_entry,long,
    HashIndex<NUMWAITLINEITEM3_L2_2_DELTA_entry,long,NUMWAITLINEITEM3_L2_2_DELTA_mapkey01_idxfn,true>,
    HashIndex<NUMWAITLINEITEM3_L2_2_DELTA_entry,long,NUMWAITLINEITEM3_L2_2_DELTA_mapkey0_idxfn,false>
  > NUMWAITLINEITEM3_L2_2_DELTA_map;
  typedef HashIndex<NUMWAITLINEITEM3_L2_2_DELTA_entry,long,NUMWAITLINEITEM3_L2_2_DELTA_mapkey01_idxfn,true> HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01;
  typedef HashIndex<NUMWAITLINEITEM3_L2_2_DELTA_entry,long,NUMWAITLINEITEM3_L2_2_DELTA_mapkey0_idxfn,false> HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0;
  
  struct NUMWAITLINEITEM3_E3_2_DELTA_entry {
    long L1_ORDERKEY; long L2_SUPPKEY; long __av; 
    explicit NUMWAITLINEITEM3_E3_2_DELTA_entry() { /*L1_ORDERKEY = 0L; L2_SUPPKEY = 0L; __av = 0L; */ }
    explicit NUMWAITLINEITEM3_E3_2_DELTA_entry(const long c0, const long c1, const long c2) { L1_ORDERKEY = c0; L2_SUPPKEY = c1; __av = c2; }
    NUMWAITLINEITEM3_E3_2_DELTA_entry(const NUMWAITLINEITEM3_E3_2_DELTA_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), L2_SUPPKEY( other.L2_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITLINEITEM3_E3_2_DELTA_entry& modify(const long c0, const long c1) { L1_ORDERKEY = c0; L2_SUPPKEY = c1;  return *this; }
    FORCE_INLINE NUMWAITLINEITEM3_E3_2_DELTA_entry& modify0(const long c0) { L1_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITLINEITEM3_E3_2_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM3_E3_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      hash_combine(h, e.L2_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM3_E3_2_DELTA_entry& x, const NUMWAITLINEITEM3_E3_2_DELTA_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY && x.L2_SUPPKEY == y.L2_SUPPKEY;
    }
  };
  
  struct NUMWAITLINEITEM3_E3_2_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM3_E3_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM3_E3_2_DELTA_entry& x, const NUMWAITLINEITEM3_E3_2_DELTA_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITLINEITEM3_E3_2_DELTA_entry,long,
    HashIndex<NUMWAITLINEITEM3_E3_2_DELTA_entry,long,NUMWAITLINEITEM3_E3_2_DELTA_mapkey01_idxfn,true>,
    HashIndex<NUMWAITLINEITEM3_E3_2_DELTA_entry,long,NUMWAITLINEITEM3_E3_2_DELTA_mapkey0_idxfn,false>
  > NUMWAITLINEITEM3_E3_2_DELTA_map;
  typedef HashIndex<NUMWAITLINEITEM3_E3_2_DELTA_entry,long,NUMWAITLINEITEM3_E3_2_DELTA_mapkey01_idxfn,true> HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_01;
  typedef HashIndex<NUMWAITLINEITEM3_E3_2_DELTA_entry,long,NUMWAITLINEITEM3_E3_2_DELTA_mapkey0_idxfn,false> HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_0;
  
  struct NUMWAITLINEITEM4_P_3_entry {
    STRING_TYPE N_NAME; long S_SUPPKEY; STRING_TYPE S_NAME; long __av; 
    explicit NUMWAITLINEITEM4_P_3_entry() { /*N_NAME = ""; S_SUPPKEY = 0L; S_NAME = ""; __av = 0L; */ }
    explicit NUMWAITLINEITEM4_P_3_entry(const STRING_TYPE& c0, const long c1, const STRING_TYPE& c2, const long c3) { N_NAME = c0; S_SUPPKEY = c1; S_NAME = c2; __av = c3; }
    NUMWAITLINEITEM4_P_3_entry(const NUMWAITLINEITEM4_P_3_entry& other) : N_NAME( other.N_NAME ), S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITLINEITEM4_P_3_entry& modify(const STRING_TYPE& c0, const long c1, const STRING_TYPE& c2) { N_NAME = c0; S_SUPPKEY = c1; S_NAME = c2;  return *this; }
    FORCE_INLINE NUMWAITLINEITEM4_P_3_entry& modify01(const STRING_TYPE& c0, const long c1) { N_NAME = c0; S_SUPPKEY = c1;  return *this; }
    FORCE_INLINE NUMWAITLINEITEM4_P_3_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITLINEITEM4_P_3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM4_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.N_NAME);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM4_P_3_entry& x, const NUMWAITLINEITEM4_P_3_entry& y) {
      return x.N_NAME == y.N_NAME && x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME;
    }
  };
  
  struct NUMWAITLINEITEM4_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM4_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.N_NAME);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM4_P_3_entry& x, const NUMWAITLINEITEM4_P_3_entry& y) {
      return x.N_NAME == y.N_NAME && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  struct NUMWAITLINEITEM4_P_3_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM4_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM4_P_3_entry& x, const NUMWAITLINEITEM4_P_3_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITLINEITEM4_P_3_entry,long,
    HashIndex<NUMWAITLINEITEM4_P_3_entry,long,NUMWAITLINEITEM4_P_3_mapkey012_idxfn,true>,
    HashIndex<NUMWAITLINEITEM4_P_3_entry,long,NUMWAITLINEITEM4_P_3_mapkey01_idxfn,false>,
    HashIndex<NUMWAITLINEITEM4_P_3_entry,long,NUMWAITLINEITEM4_P_3_mapkey1_idxfn,false>
  > NUMWAITLINEITEM4_P_3_map;
  typedef HashIndex<NUMWAITLINEITEM4_P_3_entry,long,NUMWAITLINEITEM4_P_3_mapkey012_idxfn,true> HashIndex_NUMWAITLINEITEM4_P_3_map_012;
  typedef HashIndex<NUMWAITLINEITEM4_P_3_entry,long,NUMWAITLINEITEM4_P_3_mapkey01_idxfn,false> HashIndex_NUMWAITLINEITEM4_P_3_map_01;
  typedef HashIndex<NUMWAITLINEITEM4_P_3_entry,long,NUMWAITLINEITEM4_P_3_mapkey1_idxfn,false> HashIndex_NUMWAITLINEITEM4_P_3_map_1;
  
  struct NUMWAITSUPPLIER1_DELTA_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; long S_NATIONKEY; long __av; 
    explicit NUMWAITSUPPLIER1_DELTA_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; S_NATIONKEY = 0L; __av = 0L; */ }
    explicit NUMWAITSUPPLIER1_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2, const long c3) { S_SUPPKEY = c0; S_NAME = c1; S_NATIONKEY = c2; __av = c3; }
    NUMWAITSUPPLIER1_DELTA_entry(const NUMWAITSUPPLIER1_DELTA_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITSUPPLIER1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const long c2) { S_SUPPKEY = c0; S_NAME = c1; S_NATIONKEY = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITSUPPLIER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER1_DELTA_entry& x, const NUMWAITSUPPLIER1_DELTA_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITSUPPLIER1_DELTA_entry,long,
    HashIndex<NUMWAITSUPPLIER1_DELTA_entry,long,NUMWAITSUPPLIER1_DELTA_mapkey012_idxfn,true>
  > NUMWAITSUPPLIER1_DELTA_map;
  typedef HashIndex<NUMWAITSUPPLIER1_DELTA_entry,long,NUMWAITSUPPLIER1_DELTA_mapkey012_idxfn,true> HashIndex_NUMWAITSUPPLIER1_DELTA_map_012;
  
  struct NUMWAITSUPPLIER1_P_1_entry {
    long S_NATIONKEY; long __av; 
    explicit NUMWAITSUPPLIER1_P_1_entry() { /*S_NATIONKEY = 0L; __av = 0L; */ }
    explicit NUMWAITSUPPLIER1_P_1_entry(const long c0, const long c1) { S_NATIONKEY = c0; __av = c1; }
    NUMWAITSUPPLIER1_P_1_entry(const NUMWAITSUPPLIER1_P_1_entry& other) : S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITSUPPLIER1_P_1_entry& modify(const long c0) { S_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITSUPPLIER1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER1_P_1_entry& x, const NUMWAITSUPPLIER1_P_1_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITSUPPLIER1_P_1_entry,long,
    HashIndex<NUMWAITSUPPLIER1_P_1_entry,long,NUMWAITSUPPLIER1_P_1_mapkey0_idxfn,true>
  > NUMWAITSUPPLIER1_P_1_map;
  typedef HashIndex<NUMWAITSUPPLIER1_P_1_entry,long,NUMWAITSUPPLIER1_P_1_mapkey0_idxfn,true> HashIndex_NUMWAITSUPPLIER1_P_1_map_0;
  
  struct NUMWAITSUPPLIER1_P_2_entry {
    long L1_ORDERKEY; long S_SUPPKEY; long __av; 
    explicit NUMWAITSUPPLIER1_P_2_entry() { /*L1_ORDERKEY = 0L; S_SUPPKEY = 0L; __av = 0L; */ }
    explicit NUMWAITSUPPLIER1_P_2_entry(const long c0, const long c1, const long c2) { L1_ORDERKEY = c0; S_SUPPKEY = c1; __av = c2; }
    NUMWAITSUPPLIER1_P_2_entry(const NUMWAITSUPPLIER1_P_2_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITSUPPLIER1_P_2_entry& modify(const long c0, const long c1) { L1_ORDERKEY = c0; S_SUPPKEY = c1;  return *this; }
    FORCE_INLINE NUMWAITSUPPLIER1_P_2_entry& modify1(const long c1) { S_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITSUPPLIER1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER1_P_2_entry& x, const NUMWAITSUPPLIER1_P_2_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY && x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  struct NUMWAITSUPPLIER1_P_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER1_P_2_entry& x, const NUMWAITSUPPLIER1_P_2_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITSUPPLIER1_P_2_entry,long,
    HashIndex<NUMWAITSUPPLIER1_P_2_entry,long,NUMWAITSUPPLIER1_P_2_mapkey01_idxfn,true>,
    HashIndex<NUMWAITSUPPLIER1_P_2_entry,long,NUMWAITSUPPLIER1_P_2_mapkey1_idxfn,false>
  > NUMWAITSUPPLIER1_P_2_map;
  typedef HashIndex<NUMWAITSUPPLIER1_P_2_entry,long,NUMWAITSUPPLIER1_P_2_mapkey01_idxfn,true> HashIndex_NUMWAITSUPPLIER1_P_2_map_01;
  typedef HashIndex<NUMWAITSUPPLIER1_P_2_entry,long,NUMWAITSUPPLIER1_P_2_mapkey1_idxfn,false> HashIndex_NUMWAITSUPPLIER1_P_2_map_1;
  
  struct NUMWAITSUPPLIER1_P_2LINEITEM1_entry {
    long L1_ORDERKEY; long __av; 
    explicit NUMWAITSUPPLIER1_P_2LINEITEM1_entry() { /*L1_ORDERKEY = 0L; __av = 0L; */ }
    explicit NUMWAITSUPPLIER1_P_2LINEITEM1_entry(const long c0, const long c1) { L1_ORDERKEY = c0; __av = c1; }
    NUMWAITSUPPLIER1_P_2LINEITEM1_entry(const NUMWAITSUPPLIER1_P_2LINEITEM1_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITSUPPLIER1_P_2LINEITEM1_entry& modify(const long c0) { L1_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITSUPPLIER1_P_2LINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER1_P_2LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER1_P_2LINEITEM1_entry& x, const NUMWAITSUPPLIER1_P_2LINEITEM1_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITSUPPLIER1_P_2LINEITEM1_entry,long,
    HashIndex<NUMWAITSUPPLIER1_P_2LINEITEM1_entry,long,NUMWAITSUPPLIER1_P_2LINEITEM1_mapkey0_idxfn,true>
  > NUMWAITSUPPLIER1_P_2LINEITEM1_map;
  typedef HashIndex<NUMWAITSUPPLIER1_P_2LINEITEM1_entry,long,NUMWAITSUPPLIER1_P_2LINEITEM1_mapkey0_idxfn,true> HashIndex_NUMWAITSUPPLIER1_P_2LINEITEM1_map_0;
  
  struct NUMWAITSUPPLIER1_L2_1_entry {
    long L1_ORDERKEY; long L3_SUPPKEY; long __av; 
    explicit NUMWAITSUPPLIER1_L2_1_entry() { /*L1_ORDERKEY = 0L; L3_SUPPKEY = 0L; __av = 0L; */ }
    explicit NUMWAITSUPPLIER1_L2_1_entry(const long c0, const long c1, const long c2) { L1_ORDERKEY = c0; L3_SUPPKEY = c1; __av = c2; }
    NUMWAITSUPPLIER1_L2_1_entry(const NUMWAITSUPPLIER1_L2_1_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), L3_SUPPKEY( other.L3_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITSUPPLIER1_L2_1_entry& modify(const long c0, const long c1) { L1_ORDERKEY = c0; L3_SUPPKEY = c1;  return *this; }
    FORCE_INLINE NUMWAITSUPPLIER1_L2_1_entry& modify0(const long c0) { L1_ORDERKEY = c0;  return *this; }
    FORCE_INLINE NUMWAITSUPPLIER1_L2_1_entry& modify1(const long c1) { L3_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L3_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITSUPPLIER1_L2_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      hash_combine(h, e.L3_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER1_L2_1_entry& x, const NUMWAITSUPPLIER1_L2_1_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY && x.L3_SUPPKEY == y.L3_SUPPKEY;
    }
  };
  
  struct NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER1_L2_1_entry& x, const NUMWAITSUPPLIER1_L2_1_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY;
    }
  };
  
  struct NUMWAITSUPPLIER1_L2_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L3_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER1_L2_1_entry& x, const NUMWAITSUPPLIER1_L2_1_entry& y) {
      return x.L3_SUPPKEY == y.L3_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITSUPPLIER1_L2_1_entry,long,
    HashIndex<NUMWAITSUPPLIER1_L2_1_entry,long,NUMWAITSUPPLIER1_L2_1_mapkey01_idxfn,true>,
    HashIndex<NUMWAITSUPPLIER1_L2_1_entry,long,NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn,false>,
    HashIndex<NUMWAITSUPPLIER1_L2_1_entry,long,NUMWAITSUPPLIER1_L2_1_mapkey1_idxfn,false>
  > NUMWAITSUPPLIER1_L2_1_map;
  typedef HashIndex<NUMWAITSUPPLIER1_L2_1_entry,long,NUMWAITSUPPLIER1_L2_1_mapkey01_idxfn,true> HashIndex_NUMWAITSUPPLIER1_L2_1_map_01;
  typedef HashIndex<NUMWAITSUPPLIER1_L2_1_entry,long,NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn,false> HashIndex_NUMWAITSUPPLIER1_L2_1_map_0;
  typedef HashIndex<NUMWAITSUPPLIER1_L2_1_entry,long,NUMWAITSUPPLIER1_L2_1_mapkey1_idxfn,false> HashIndex_NUMWAITSUPPLIER1_L2_1_map_1;
  
  struct NUMWAITSUPPLIER1_E3_1_entry {
    long L1_ORDERKEY; long L2_SUPPKEY; long __av; 
    explicit NUMWAITSUPPLIER1_E3_1_entry() { /*L1_ORDERKEY = 0L; L2_SUPPKEY = 0L; __av = 0L; */ }
    explicit NUMWAITSUPPLIER1_E3_1_entry(const long c0, const long c1, const long c2) { L1_ORDERKEY = c0; L2_SUPPKEY = c1; __av = c2; }
    NUMWAITSUPPLIER1_E3_1_entry(const NUMWAITSUPPLIER1_E3_1_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), L2_SUPPKEY( other.L2_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITSUPPLIER1_E3_1_entry& modify(const long c0, const long c1) { L1_ORDERKEY = c0; L2_SUPPKEY = c1;  return *this; }
    FORCE_INLINE NUMWAITSUPPLIER1_E3_1_entry& modify0(const long c0) { L1_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITSUPPLIER1_E3_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER1_E3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      hash_combine(h, e.L2_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER1_E3_1_entry& x, const NUMWAITSUPPLIER1_E3_1_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY && x.L2_SUPPKEY == y.L2_SUPPKEY;
    }
  };
  
  struct NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER1_E3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER1_E3_1_entry& x, const NUMWAITSUPPLIER1_E3_1_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITSUPPLIER1_E3_1_entry,long,
    HashIndex<NUMWAITSUPPLIER1_E3_1_entry,long,NUMWAITSUPPLIER1_E3_1_mapkey01_idxfn,true>,
    HashIndex<NUMWAITSUPPLIER1_E3_1_entry,long,NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn,false>
  > NUMWAITSUPPLIER1_E3_1_map;
  typedef HashIndex<NUMWAITSUPPLIER1_E3_1_entry,long,NUMWAITSUPPLIER1_E3_1_mapkey01_idxfn,true> HashIndex_NUMWAITSUPPLIER1_E3_1_map_01;
  typedef HashIndex<NUMWAITSUPPLIER1_E3_1_entry,long,NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn,false> HashIndex_NUMWAITSUPPLIER1_E3_1_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const NUMWAIT_map& _NUMWAIT = get_NUMWAIT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(NUMWAIT), _NUMWAIT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const NUMWAIT_map& get_NUMWAIT() const {
      return NUMWAIT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    NUMWAIT_map NUMWAIT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c1 = STRING_TYPE("F");
      c2 = STRING_TYPE("SAUDI ARABIA");
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

        NUMWAITLINEITEM3_E3_2_DELTA.clear();
        NUMWAITLINEITEM3_L2_2_DELTA.clear();
        NUMWAITLINEITEM1_DOMAIN1_P_3.clear();
        { 
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                long l1_orderkey = DELTA_LINEITEM.orderkey[i];
                // long l2_partkey = DELTA_LINEITEM.partkey[i];
                long l2_suppkey = DELTA_LINEITEM.suppkey[i];
                // long l2_linenumber = DELTA_LINEITEM.linenumber[i];
                // DOUBLE_TYPE l2_quantity = DELTA_LINEITEM.quantity[i];
                // DOUBLE_TYPE l2_extendedprice = DELTA_LINEITEM.extendedprice[i];
                // DOUBLE_TYPE l2_discount = DELTA_LINEITEM.discount[i];
                // DOUBLE_TYPE l2_tax = DELTA_LINEITEM.tax[i];
                // STRING_TYPE l2_returnflag = DELTA_LINEITEM.returnflag[i];
                // STRING_TYPE l2_linestatus = DELTA_LINEITEM.linestatus[i];
                // date l2_shipdate = DELTA_LINEITEM.shipdate[i];
                date l2_commitdate = DELTA_LINEITEM.commitdate[i];
                date l2_receiptdate = DELTA_LINEITEM.receiptdate[i];
                // STRING_TYPE l2_shipinstruct = DELTA_LINEITEM.shipinstruct[i];
                // STRING_TYPE l2_shipmode = DELTA_LINEITEM.shipmode[i];
                // STRING_TYPE l2_comment = DELTA_LINEITEM.comment[i];
                long v1 = 1L;
                NUMWAITLINEITEM3_E3_2_DELTA.addOrDelOnZero(se1.modify(l1_orderkey,l2_suppkey),v1);
                long v2 = 1L;
                (/*if */(l2_receiptdate > l2_commitdate) ? NUMWAITLINEITEM3_L2_2_DELTA.addOrDelOnZero(se2.modify(l1_orderkey,l2_suppkey),v2) : (void)0);
                long v3 = 1L;
                NUMWAITLINEITEM1_DOMAIN1_P_3.addOrDelOnZero(se3.modify(l1_orderkey),(v3 != 0 ? 1L : 0L));
          }
        }
        
        STRING_TYPE l1 = c1;
        STRING_TYPE l2 = c2;
        long l3 = 0L;
        {  // foreach
          const HashIndex_NUMWAITLINEITEM1_DOMAIN1_P_3_map_0* i4 = static_cast<HashIndex_NUMWAITLINEITEM1_DOMAIN1_P_3_map_0*>(NUMWAITLINEITEM1_DOMAIN1_P_3.index[0]);
          HashIndex_NUMWAITLINEITEM1_DOMAIN1_P_3_map_0::IdxNode* n4; 
          NUMWAITLINEITEM1_DOMAIN1_P_3_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long l1_orderkey = e4->L1_ORDERKEY;
                long v4 = e4->__av;
                { //slice 
                  const HashIndex_NUMWAITLINEITEM1_P_3_map_01* i5 = static_cast<HashIndex_NUMWAITLINEITEM1_P_3_map_01*>(NUMWAITLINEITEM1_P_3.index[1]);
                  const HASH_RES_t h3 = NUMWAITLINEITEM1_P_3_mapkey01_idxfn::hash(se8.modify01(l2, l1_orderkey));
                  HashIndex_NUMWAITLINEITEM1_P_3_map_01::IdxNode* n5 = static_cast<HashIndex_NUMWAITLINEITEM1_P_3_map_01::IdxNode*>(i5->slice(se8, h3));
                  NUMWAITLINEITEM1_P_3_entry* e5;
                 
                  if (n5 && (e5 = n5->obj)) {
                    do {                
                      long s_suppkey = e5->S_SUPPKEY;
                      STRING_TYPE s_name = e5->S_NAME;
                      long v5 = e5->__av;
                      long agg1 = 0L;
                      { //slice 
                        const HashIndex_NUMWAITSUPPLIER1_L2_1_map_0* i6 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0*>(NUMWAITSUPPLIER1_L2_1.index[1]);
                        const HASH_RES_t h1 = NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::hash(se6.modify0(l1_orderkey));
                        HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode* n6 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode*>(i6->slice(se6, h1));
                        NUMWAITSUPPLIER1_L2_1_entry* e6;
                       
                        if (n6 && (e6 = n6->obj)) {
                          do {                
                            long l3_suppkey = e6->L3_SUPPKEY;
                            long v6 = e6->__av;
                            (/*if */(l3_suppkey != s_suppkey) ? agg1 += v6 : 0L);
                            n6 = n6->nxt;
                          } while (n6 && (e6 = n6->obj) && h1 == n6->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::equals(se6, *e6)); 
                        }
                      }long agg2 = 0L;
                      { //slice 
                        const HashIndex_NUMWAITSUPPLIER1_E3_1_map_0* i7 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0*>(NUMWAITSUPPLIER1_E3_1.index[1]);
                        const HASH_RES_t h2 = NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::hash(se7.modify0(l1_orderkey));
                        HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode* n7 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode*>(i7->slice(se7, h2));
                        NUMWAITSUPPLIER1_E3_1_entry* e7;
                       
                        if (n7 && (e7 = n7->obj)) {
                          do {                
                            long l2_suppkey = e7->L2_SUPPKEY;
                            long v7 = e7->__av;
                            (/*if */(l2_suppkey != s_suppkey) ? agg2 += v7 : 0L);
                            n7 = n7->nxt;
                          } while (n7 && (e7 = n7->obj) && h2 == n7->hash &&  NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::equals(se7, *e7)); 
                        }
                      }(/*if */(l3 == agg1) ? NUMWAIT.addOrDelOnZero(se4.modify(s_name),(((v4 != 0 ? 1L : 0L) * (NUMWAITLINEITEM1_P_4.getValueOrDefault(se5.modify(l1_orderkey,l1)) * (v5 * (agg2 != 0 ? 1L : 0L)))) * -1L)) : (void)0);
                      n5 = n5->nxt;
                    } while (n5 && (e5 = n5->obj) && h3 == n5->hash &&  NUMWAITLINEITEM1_P_3_mapkey01_idxfn::equals(se8, *e5)); 
                  }
                }
              n4 = n4->nxt;
            }
          }
        }STRING_TYPE l4 = c1;
        STRING_TYPE l5 = c2;
        long l6 = 0L;
        {  // foreach
          const HashIndex_NUMWAITLINEITEM1_DOMAIN1_P_3_map_0* i8 = static_cast<HashIndex_NUMWAITLINEITEM1_DOMAIN1_P_3_map_0*>(NUMWAITLINEITEM1_DOMAIN1_P_3.index[0]);
          HashIndex_NUMWAITLINEITEM1_DOMAIN1_P_3_map_0::IdxNode* n8; 
          NUMWAITLINEITEM1_DOMAIN1_P_3_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long l1_orderkey = e8->L1_ORDERKEY;
                long v8 = e8->__av;
                { //slice 
                  const HashIndex_NUMWAITLINEITEM1_P_3_map_01* i9 = static_cast<HashIndex_NUMWAITLINEITEM1_P_3_map_01*>(NUMWAITLINEITEM1_P_3.index[1]);
                  const HASH_RES_t h8 = NUMWAITLINEITEM1_P_3_mapkey01_idxfn::hash(se14.modify01(l5, l1_orderkey));
                  HashIndex_NUMWAITLINEITEM1_P_3_map_01::IdxNode* n9 = static_cast<HashIndex_NUMWAITLINEITEM1_P_3_map_01::IdxNode*>(i9->slice(se14, h8));
                  NUMWAITLINEITEM1_P_3_entry* e9;
                 
                  if (n9 && (e9 = n9->obj)) {
                    do {                
                      long s_suppkey = e9->S_SUPPKEY;
                      STRING_TYPE s_name = e9->S_NAME;
                      long v9 = e9->__av;
                      long agg3 = 0L;
                      { //slice 
                        const HashIndex_NUMWAITSUPPLIER1_L2_1_map_0* i10 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0*>(NUMWAITSUPPLIER1_L2_1.index[1]);
                        const HASH_RES_t h4 = NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::hash(se10.modify0(l1_orderkey));
                        HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode* n10 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode*>(i10->slice(se10, h4));
                        NUMWAITSUPPLIER1_L2_1_entry* e10;
                       
                        if (n10 && (e10 = n10->obj)) {
                          do {                
                            long l3_suppkey = e10->L3_SUPPKEY;
                            long v10 = e10->__av;
                            (/*if */(l3_suppkey != s_suppkey) ? agg3 += v10 : 0L);
                            n10 = n10->nxt;
                          } while (n10 && (e10 = n10->obj) && h4 == n10->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::equals(se10, *e10)); 
                        }
                      }long agg4 = 0L;
                      { //slice 
                        const HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0* i11 = static_cast<HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0*>(NUMWAITLINEITEM3_L2_2_DELTA.index[1]);
                        const HASH_RES_t h5 = NUMWAITLINEITEM3_L2_2_DELTA_mapkey0_idxfn::hash(se11.modify0(l1_orderkey));
                        HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0::IdxNode* n11 = static_cast<HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0::IdxNode*>(i11->slice(se11, h5));
                        NUMWAITLINEITEM3_L2_2_DELTA_entry* e11;
                       
                        if (n11 && (e11 = n11->obj)) {
                          do {                
                            long l3_suppkey = e11->L3_SUPPKEY;
                            long v11 = e11->__av;
                            (/*if */(l3_suppkey != s_suppkey) ? agg4 += v11 : 0L);
                            n11 = n11->nxt;
                          } while (n11 && (e11 = n11->obj) && h5 == n11->hash &&  NUMWAITLINEITEM3_L2_2_DELTA_mapkey0_idxfn::equals(se11, *e11)); 
                        }
                      }long agg5 = 0L;
                      { //slice 
                        const HashIndex_NUMWAITSUPPLIER1_E3_1_map_0* i12 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0*>(NUMWAITSUPPLIER1_E3_1.index[1]);
                        const HASH_RES_t h6 = NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::hash(se12.modify0(l1_orderkey));
                        HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode* n12 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode*>(i12->slice(se12, h6));
                        NUMWAITSUPPLIER1_E3_1_entry* e12;
                       
                        if (n12 && (e12 = n12->obj)) {
                          do {                
                            long l2_suppkey = e12->L2_SUPPKEY;
                            long v12 = e12->__av;
                            (/*if */(l2_suppkey != s_suppkey) ? agg5 += v12 : 0L);
                            n12 = n12->nxt;
                          } while (n12 && (e12 = n12->obj) && h6 == n12->hash &&  NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::equals(se12, *e12)); 
                        }
                      }long agg6 = 0L;
                      { //slice 
                        const HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_0* i13 = static_cast<HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_0*>(NUMWAITLINEITEM3_E3_2_DELTA.index[1]);
                        const HASH_RES_t h7 = NUMWAITLINEITEM3_E3_2_DELTA_mapkey0_idxfn::hash(se13.modify0(l1_orderkey));
                        HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_0::IdxNode* n13 = static_cast<HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_0::IdxNode*>(i13->slice(se13, h7));
                        NUMWAITLINEITEM3_E3_2_DELTA_entry* e13;
                       
                        if (n13 && (e13 = n13->obj)) {
                          do {                
                            long l2_suppkey = e13->L2_SUPPKEY;
                            long v13 = e13->__av;
                            (/*if */(l2_suppkey != s_suppkey) ? agg6 += v13 : 0L);
                            n13 = n13->nxt;
                          } while (n13 && (e13 = n13->obj) && h7 == n13->hash &&  NUMWAITLINEITEM3_E3_2_DELTA_mapkey0_idxfn::equals(se13, *e13)); 
                        }
                      }(/*if */(l6 == (agg3 + agg4)) ? NUMWAIT.addOrDelOnZero(se4.modify(s_name),((v8 != 0 ? 1L : 0L) * (NUMWAITLINEITEM1_P_4.getValueOrDefault(se9.modify(l1_orderkey,l4)) * (v9 * ((agg5 + agg6) != 0 ? 1L : 0L))))) : (void)0);
                      n9 = n9->nxt;
                    } while (n9 && (e9 = n9->obj) && h8 == n9->hash &&  NUMWAITLINEITEM1_P_3_mapkey01_idxfn::equals(se14, *e9)); 
                  }
                }
              n8 = n8->nxt;
            }
          }
        }STRING_TYPE l7 = c1;
        STRING_TYPE l8 = c2;
        long l9 = 0L;
        {  // foreach
          const HashIndex_NUMWAITLINEITEM1_DOMAIN1_P_3_map_0* i14 = static_cast<HashIndex_NUMWAITLINEITEM1_DOMAIN1_P_3_map_0*>(NUMWAITLINEITEM1_DOMAIN1_P_3.index[0]);
          HashIndex_NUMWAITLINEITEM1_DOMAIN1_P_3_map_0::IdxNode* n14; 
          NUMWAITLINEITEM1_DOMAIN1_P_3_entry* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
                long l1_orderkey = e14->L1_ORDERKEY;
                long v14 = e14->__av;
                { //slice 
                  const HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0* i15 = static_cast<HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0*>(NUMWAITLINEITEM3_L2_2_DELTA.index[1]);
                  const HASH_RES_t h14 = NUMWAITLINEITEM3_L2_2_DELTA_mapkey0_idxfn::hash(se21.modify0(l1_orderkey));
                  HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0::IdxNode* n15 = static_cast<HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0::IdxNode*>(i15->slice(se21, h14));
                  NUMWAITLINEITEM3_L2_2_DELTA_entry* e15;
                 
                  if (n15 && (e15 = n15->obj)) {
                    do {                
                      long s_suppkey = e15->L3_SUPPKEY;
                      long v15 = e15->__av;
                      long agg7 = 0L;
                      { //slice 
                        const HashIndex_NUMWAITSUPPLIER1_L2_1_map_0* i16 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0*>(NUMWAITSUPPLIER1_L2_1.index[1]);
                        const HASH_RES_t h9 = NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::hash(se15.modify0(l1_orderkey));
                        HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode* n16 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode*>(i16->slice(se15, h9));
                        NUMWAITSUPPLIER1_L2_1_entry* e16;
                       
                        if (n16 && (e16 = n16->obj)) {
                          do {                
                            long l3_suppkey = e16->L3_SUPPKEY;
                            long v16 = e16->__av;
                            (/*if */(l3_suppkey != s_suppkey) ? agg7 += v16 : 0L);
                            n16 = n16->nxt;
                          } while (n16 && (e16 = n16->obj) && h9 == n16->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::equals(se15, *e16)); 
                        }
                      }long agg8 = 0L;
                      { //slice 
                        const HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0* i17 = static_cast<HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0*>(NUMWAITLINEITEM3_L2_2_DELTA.index[1]);
                        const HASH_RES_t h10 = NUMWAITLINEITEM3_L2_2_DELTA_mapkey0_idxfn::hash(se16.modify0(l1_orderkey));
                        HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0::IdxNode* n17 = static_cast<HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_0::IdxNode*>(i17->slice(se16, h10));
                        NUMWAITLINEITEM3_L2_2_DELTA_entry* e17;
                       
                        if (n17 && (e17 = n17->obj)) {
                          do {                
                            long l3_suppkey = e17->L3_SUPPKEY;
                            long v17 = e17->__av;
                            (/*if */(l3_suppkey != s_suppkey) ? agg8 += v17 : 0L);
                            n17 = n17->nxt;
                          } while (n17 && (e17 = n17->obj) && h10 == n17->hash &&  NUMWAITLINEITEM3_L2_2_DELTA_mapkey0_idxfn::equals(se16, *e17)); 
                        }
                      }{ //slice 
                        const HashIndex_NUMWAITLINEITEM4_P_3_map_01* i18 = static_cast<HashIndex_NUMWAITLINEITEM4_P_3_map_01*>(NUMWAITLINEITEM4_P_3.index[1]);
                        const HASH_RES_t h13 = NUMWAITLINEITEM4_P_3_mapkey01_idxfn::hash(se20.modify01(l8, s_suppkey));
                        HashIndex_NUMWAITLINEITEM4_P_3_map_01::IdxNode* n18 = static_cast<HashIndex_NUMWAITLINEITEM4_P_3_map_01::IdxNode*>(i18->slice(se20, h13));
                        NUMWAITLINEITEM4_P_3_entry* e18;
                       
                        if (n18 && (e18 = n18->obj)) {
                          do {                
                            STRING_TYPE s_name = e18->S_NAME;
                            long v18 = e18->__av;
                            long agg9 = 0L;
                            { //slice 
                              const HashIndex_NUMWAITSUPPLIER1_E3_1_map_0* i19 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0*>(NUMWAITSUPPLIER1_E3_1.index[1]);
                              const HASH_RES_t h11 = NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::hash(se18.modify0(l1_orderkey));
                              HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode* n19 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode*>(i19->slice(se18, h11));
                              NUMWAITSUPPLIER1_E3_1_entry* e19;
                             
                              if (n19 && (e19 = n19->obj)) {
                                do {                
                                  long l2_suppkey = e19->L2_SUPPKEY;
                                  long v19 = e19->__av;
                                  (/*if */(l2_suppkey != s_suppkey) ? agg9 += v19 : 0L);
                                  n19 = n19->nxt;
                                } while (n19 && (e19 = n19->obj) && h11 == n19->hash &&  NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::equals(se18, *e19)); 
                              }
                            }long agg10 = 0L;
                            { //slice 
                              const HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_0* i20 = static_cast<HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_0*>(NUMWAITLINEITEM3_E3_2_DELTA.index[1]);
                              const HASH_RES_t h12 = NUMWAITLINEITEM3_E3_2_DELTA_mapkey0_idxfn::hash(se19.modify0(l1_orderkey));
                              HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_0::IdxNode* n20 = static_cast<HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_0::IdxNode*>(i20->slice(se19, h12));
                              NUMWAITLINEITEM3_E3_2_DELTA_entry* e20;
                             
                              if (n20 && (e20 = n20->obj)) {
                                do {                
                                  long l2_suppkey = e20->L2_SUPPKEY;
                                  long v20 = e20->__av;
                                  (/*if */(l2_suppkey != s_suppkey) ? agg10 += v20 : 0L);
                                  n20 = n20->nxt;
                                } while (n20 && (e20 = n20->obj) && h12 == n20->hash &&  NUMWAITLINEITEM3_E3_2_DELTA_mapkey0_idxfn::equals(se19, *e20)); 
                              }
                            }(/*if */(l9 == (agg7 + agg8)) ? NUMWAIT.addOrDelOnZero(se4.modify(s_name),((v14 != 0 ? 1L : 0L) * (v15 * (NUMWAITLINEITEM1_P_4.getValueOrDefault(se17.modify(l1_orderkey,l7)) * (v18 * ((agg9 + agg10) != 0 ? 1L : 0L)))))) : (void)0);
                            n18 = n18->nxt;
                          } while (n18 && (e18 = n18->obj) && h13 == n18->hash &&  NUMWAITLINEITEM4_P_3_mapkey01_idxfn::equals(se20, *e18)); 
                        }
                      }
                      n15 = n15->nxt;
                    } while (n15 && (e15 = n15->obj) && h14 == n15->hash &&  NUMWAITLINEITEM3_L2_2_DELTA_mapkey0_idxfn::equals(se21, *e15)); 
                  }
                }
              n14 = n14->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01* i21 = static_cast<HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01*>(NUMWAITLINEITEM3_L2_2_DELTA.index[0]);
          HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01::IdxNode* n21; 
          NUMWAITLINEITEM3_L2_2_DELTA_entry* e21;
        
          for (size_t i = 0; i < i21->size_; i++)
          {
            n21 = i21->buckets_ + i;
            while (n21 && (e21 = n21->obj))
            {
                long l1_orderkey = e21->L1_ORDERKEY;
                long s_suppkey = e21->L3_SUPPKEY;
                long v21 = e21->__av;
                { //slice 
                  const HashIndex_NUMWAITORDERS1LINEITEM1_map_0* i22 = static_cast<HashIndex_NUMWAITORDERS1LINEITEM1_map_0*>(NUMWAITORDERS1LINEITEM1.index[1]);
                  const HASH_RES_t h15 = NUMWAITORDERS1LINEITEM1_mapkey0_idxfn::hash(se23.modify0(s_suppkey));
                  HashIndex_NUMWAITORDERS1LINEITEM1_map_0::IdxNode* n22 = static_cast<HashIndex_NUMWAITORDERS1LINEITEM1_map_0::IdxNode*>(i22->slice(se23, h15));
                  NUMWAITORDERS1LINEITEM1_entry* e22;
                 
                  if (n22 && (e22 = n22->obj)) {
                    do {                
                      STRING_TYPE s_name = e22->S_NAME;
                      long v22 = e22->__av;
                      NUMWAITORDERS1.addOrDelOnZero(se22.modify(s_suppkey,s_name,l1_orderkey),(v21 * v22));
                      n22 = n22->nxt;
                    } while (n22 && (e22 = n22->obj) && h15 == n22->hash &&  NUMWAITORDERS1LINEITEM1_mapkey0_idxfn::equals(se23, *e22)); 
                  }
                }
              n21 = n21->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01* i23 = static_cast<HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01*>(NUMWAITLINEITEM3_L2_2_DELTA.index[0]);
          HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01::IdxNode* n23; 
          NUMWAITLINEITEM3_L2_2_DELTA_entry* e23;
        
          for (size_t i = 0; i < i23->size_; i++)
          {
            n23 = i23->buckets_ + i;
            while (n23 && (e23 = n23->obj))
            {
                long l1_orderkey = e23->L1_ORDERKEY;
                long s_suppkey = e23->L3_SUPPKEY;
                long v23 = e23->__av;
                { //slice 
                  const HashIndex_NUMWAITLINEITEM4_P_3_map_1* i24 = static_cast<HashIndex_NUMWAITLINEITEM4_P_3_map_1*>(NUMWAITLINEITEM4_P_3.index[2]);
                  const HASH_RES_t h16 = NUMWAITLINEITEM4_P_3_mapkey1_idxfn::hash(se25.modify1(s_suppkey));
                  HashIndex_NUMWAITLINEITEM4_P_3_map_1::IdxNode* n24 = static_cast<HashIndex_NUMWAITLINEITEM4_P_3_map_1::IdxNode*>(i24->slice(se25, h16));
                  NUMWAITLINEITEM4_P_3_entry* e24;
                 
                  if (n24 && (e24 = n24->obj)) {
                    do {                
                      STRING_TYPE n_name = e24->N_NAME;
                      STRING_TYPE s_name = e24->S_NAME;
                      long v24 = e24->__av;
                      NUMWAITLINEITEM1_P_3.addOrDelOnZero(se24.modify(n_name,l1_orderkey,s_suppkey,s_name),(v23 * v24));
                      n24 = n24->nxt;
                    } while (n24 && (e24 = n24->obj) && h16 == n24->hash &&  NUMWAITLINEITEM4_P_3_mapkey1_idxfn::equals(se25, *e24)); 
                  }
                }
              n23 = n23->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01* i25 = static_cast<HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01*>(NUMWAITLINEITEM3_L2_2_DELTA.index[0]);
          HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01::IdxNode* n25; 
          NUMWAITLINEITEM3_L2_2_DELTA_entry* e25;
        
          for (size_t i = 0; i < i25->size_; i++)
          {
            n25 = i25->buckets_ + i;
            while (n25 && (e25 = n25->obj))
            {
                long l1_orderkey = e25->L1_ORDERKEY;
                long s_suppkey = e25->L3_SUPPKEY;
                long v25 = e25->__av;
                NUMWAITSUPPLIER1_P_2.addOrDelOnZero(se26.modify(l1_orderkey,s_suppkey),(v25 * NUMWAITSUPPLIER1_P_2LINEITEM1.getValueOrDefault(se27.modify(l1_orderkey))));
              n25 = n25->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01* i26 = static_cast<HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01*>(NUMWAITLINEITEM3_L2_2_DELTA.index[0]);
          HashIndex_NUMWAITLINEITEM3_L2_2_DELTA_map_01::IdxNode* n26; 
          NUMWAITLINEITEM3_L2_2_DELTA_entry* e26;
        
          for (size_t i = 0; i < i26->size_; i++)
          {
            n26 = i26->buckets_ + i;
            while (n26 && (e26 = n26->obj))
            {
                long l1_orderkey = e26->L1_ORDERKEY;
                long l3_suppkey = e26->L3_SUPPKEY;
                long v26 = e26->__av;
                NUMWAITSUPPLIER1_L2_1.addOrDelOnZero(se28.modify(l1_orderkey,l3_suppkey),v26);
              n26 = n26->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_01* i27 = static_cast<HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_01*>(NUMWAITLINEITEM3_E3_2_DELTA.index[0]);
          HashIndex_NUMWAITLINEITEM3_E3_2_DELTA_map_01::IdxNode* n27; 
          NUMWAITLINEITEM3_E3_2_DELTA_entry* e27;
        
          for (size_t i = 0; i < i27->size_; i++)
          {
            n27 = i27->buckets_ + i;
            while (n27 && (e27 = n27->obj))
            {
                long l1_orderkey = e27->L1_ORDERKEY;
                long l2_suppkey = e27->L2_SUPPKEY;
                long v27 = e27->__av;
                NUMWAITSUPPLIER1_E3_1.addOrDelOnZero(se29.modify(l1_orderkey,l2_suppkey),v27);
              n27 = n27->nxt;
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

        NUMWAITORDERS1_DELTA.clear();
        NUMWAITLINEITEM1_P_4ORDERS1_DELTA.clear();
        { 
          for (size_t i = 0; i < DELTA_ORDERS.size; i++) 
          {
                long l1_orderkey = DELTA_ORDERS.orderkey[i];
                // long o_custkey = DELTA_ORDERS.custkey[i];
                STRING_TYPE o_orderstatus = DELTA_ORDERS.orderstatus[i];
                // DOUBLE_TYPE o_totalprice = DELTA_ORDERS.totalprice[i];
                // date o_orderdate = DELTA_ORDERS.orderdate[i];
                // STRING_TYPE o_orderpriority = DELTA_ORDERS.orderpriority[i];
                // STRING_TYPE o_clerk = DELTA_ORDERS.clerk[i];
                // long o_shippriority = DELTA_ORDERS.shippriority[i];
                // STRING_TYPE o_comment = DELTA_ORDERS.comment[i];
                long v28 = 1L;
                (/*if */(o_orderstatus == c1) ? NUMWAITORDERS1_DELTA.addOrDelOnZero(se30.modify(l1_orderkey),v28) : (void)0);
                long v29 = 1L;
                NUMWAITLINEITEM1_P_4ORDERS1_DELTA.addOrDelOnZero(se31.modify(l1_orderkey,o_orderstatus),v29);
          }
        }

        long l10 = 0L;
        {  // foreach
          const HashIndex_NUMWAITORDERS1_DELTA_map_0* i30 = static_cast<HashIndex_NUMWAITORDERS1_DELTA_map_0*>(NUMWAITORDERS1_DELTA.index[0]);
          HashIndex_NUMWAITORDERS1_DELTA_map_0::IdxNode* n30; 
          NUMWAITORDERS1_DELTA_entry* e30;
        
          for (size_t i = 0; i < i30->size_; i++)
          {
            n30 = i30->buckets_ + i;
            while (n30 && (e30 = n30->obj))
            {
                long l1_orderkey = e30->L1_ORDERKEY;
                long v30 = e30->__av;
                { //slice 
                  const HashIndex_NUMWAITORDERS1_map_2* i31 = static_cast<HashIndex_NUMWAITORDERS1_map_2*>(NUMWAITORDERS1.index[1]);
                  const HASH_RES_t h19 = NUMWAITORDERS1_mapkey2_idxfn::hash(se35.modify2(l1_orderkey));
                  HashIndex_NUMWAITORDERS1_map_2::IdxNode* n31 = static_cast<HashIndex_NUMWAITORDERS1_map_2::IdxNode*>(i31->slice(se35, h19));
                  NUMWAITORDERS1_entry* e31;
                 
                  if (n31 && (e31 = n31->obj)) {
                    do {                
                      long s_suppkey = e31->S_SUPPKEY;
                      STRING_TYPE s_name = e31->S_NAME;
                      long v31 = e31->__av;
                      long agg11 = 0L;
                      { //slice 
                        const HashIndex_NUMWAITSUPPLIER1_L2_1_map_0* i32 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0*>(NUMWAITSUPPLIER1_L2_1.index[1]);
                        const HASH_RES_t h17 = NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::hash(se33.modify0(l1_orderkey));
                        HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode* n32 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode*>(i32->slice(se33, h17));
                        NUMWAITSUPPLIER1_L2_1_entry* e32;
                       
                        if (n32 && (e32 = n32->obj)) {
                          do {                
                            long l3_suppkey = e32->L3_SUPPKEY;
                            long v32 = e32->__av;
                            (/*if */(l3_suppkey != s_suppkey) ? agg11 += v32 : 0L);
                            n32 = n32->nxt;
                          } while (n32 && (e32 = n32->obj) && h17 == n32->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::equals(se33, *e32)); 
                        }
                      }long agg12 = 0L;
                      { //slice 
                        const HashIndex_NUMWAITSUPPLIER1_E3_1_map_0* i33 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0*>(NUMWAITSUPPLIER1_E3_1.index[1]);
                        const HASH_RES_t h18 = NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::hash(se34.modify0(l1_orderkey));
                        HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode* n33 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode*>(i33->slice(se34, h18));
                        NUMWAITSUPPLIER1_E3_1_entry* e33;
                       
                        if (n33 && (e33 = n33->obj)) {
                          do {                
                            long l2_suppkey = e33->L2_SUPPKEY;
                            long v33 = e33->__av;
                            (/*if */(l2_suppkey != s_suppkey) ? agg12 += v33 : 0L);
                            n33 = n33->nxt;
                          } while (n33 && (e33 = n33->obj) && h18 == n33->hash &&  NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::equals(se34, *e33)); 
                        }
                      }(/*if */(l10 == agg11) ? NUMWAIT.addOrDelOnZero(se32.modify(s_name),(v30 * (v31 * (agg12 != 0 ? 1L : 0L)))) : (void)0);
                      n31 = n31->nxt;
                    } while (n31 && (e31 = n31->obj) && h19 == n31->hash &&  NUMWAITORDERS1_mapkey2_idxfn::equals(se35, *e31)); 
                  }
                }
              n30 = n30->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMWAITLINEITEM1_P_4ORDERS1_DELTA_map_01* i34 = static_cast<HashIndex_NUMWAITLINEITEM1_P_4ORDERS1_DELTA_map_01*>(NUMWAITLINEITEM1_P_4ORDERS1_DELTA.index[0]);
          HashIndex_NUMWAITLINEITEM1_P_4ORDERS1_DELTA_map_01::IdxNode* n34; 
          NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry* e34;
        
          for (size_t i = 0; i < i34->size_; i++)
          {
            n34 = i34->buckets_ + i;
            while (n34 && (e34 = n34->obj))
            {
                long l1_orderkey = e34->L1_ORDERKEY;
                STRING_TYPE o_orderstatus = e34->O_ORDERSTATUS;
                long v34 = e34->__av;
                NUMWAITLINEITEM1_P_4.addOrDelOnZero(se36.modify(l1_orderkey,o_orderstatus),v34);
              n34 = n34->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMWAITORDERS1_DELTA_map_0* i35 = static_cast<HashIndex_NUMWAITORDERS1_DELTA_map_0*>(NUMWAITORDERS1_DELTA.index[0]);
          HashIndex_NUMWAITORDERS1_DELTA_map_0::IdxNode* n35; 
          NUMWAITORDERS1_DELTA_entry* e35;
        
          for (size_t i = 0; i < i35->size_; i++)
          {
            n35 = i35->buckets_ + i;
            while (n35 && (e35 = n35->obj))
            {
                long l1_orderkey = e35->L1_ORDERKEY;
                long v35 = e35->__av;
                { //slice 
                  const HashIndex_NUMWAITSUPPLIER1_L2_1_map_0* i36 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0*>(NUMWAITSUPPLIER1_L2_1.index[1]);
                  const HASH_RES_t h20 = NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::hash(se38.modify0(l1_orderkey));
                  HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode* n36 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode*>(i36->slice(se38, h20));
                  NUMWAITSUPPLIER1_L2_1_entry* e36;
                 
                  if (n36 && (e36 = n36->obj)) {
                    do {                
                      long s_suppkey = e36->L3_SUPPKEY;
                      long v36 = e36->__av;
                      NUMWAITSUPPLIER1_P_2.addOrDelOnZero(se37.modify(l1_orderkey,s_suppkey),(v35 * v36));
                      n36 = n36->nxt;
                    } while (n36 && (e36 = n36->obj) && h20 == n36->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::equals(se38, *e36)); 
                  }
                }
              n35 = n35->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMWAITORDERS1_DELTA_map_0* i37 = static_cast<HashIndex_NUMWAITORDERS1_DELTA_map_0*>(NUMWAITORDERS1_DELTA.index[0]);
          HashIndex_NUMWAITORDERS1_DELTA_map_0::IdxNode* n37; 
          NUMWAITORDERS1_DELTA_entry* e37;
        
          for (size_t i = 0; i < i37->size_; i++)
          {
            n37 = i37->buckets_ + i;
            while (n37 && (e37 = n37->obj))
            {
                long l1_orderkey = e37->L1_ORDERKEY;
                long v37 = e37->__av;
                NUMWAITSUPPLIER1_P_2LINEITEM1.addOrDelOnZero(se39.modify(l1_orderkey),v37);
              n37 = n37->nxt;
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

        NUMWAITSUPPLIER1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_SUPPLIER.size; i++) 
          {
                long s_suppkey = DELTA_SUPPLIER.suppkey[i];
                STRING_TYPE s_name = DELTA_SUPPLIER.name[i];
                // STRING_TYPE s_address = DELTA_SUPPLIER.address[i];
                long s_nationkey = DELTA_SUPPLIER.nationkey[i];
                // STRING_TYPE s_phone = DELTA_SUPPLIER.phone[i];
                // DOUBLE_TYPE s_acctbal = DELTA_SUPPLIER.acctbal[i];
                // STRING_TYPE s_comment = DELTA_SUPPLIER.comment[i];
                long v38 = 1L;
                NUMWAITSUPPLIER1_DELTA.addOrDelOnZero(se40.modify(s_suppkey,s_name,s_nationkey),v38);            
          }
        }

        long l11 = 0L;
        {  // foreach
          const HashIndex_NUMWAITSUPPLIER1_DELTA_map_012* i39 = static_cast<HashIndex_NUMWAITSUPPLIER1_DELTA_map_012*>(NUMWAITSUPPLIER1_DELTA.index[0]);
          HashIndex_NUMWAITSUPPLIER1_DELTA_map_012::IdxNode* n39; 
          NUMWAITSUPPLIER1_DELTA_entry* e39;
        
          for (size_t i = 0; i < i39->size_; i++)
          {
            n39 = i39->buckets_ + i;
            while (n39 && (e39 = n39->obj))
            {
                long s_suppkey = e39->S_SUPPKEY;
                STRING_TYPE s_name = e39->S_NAME;
                long s_nationkey = e39->S_NATIONKEY;
                long v39 = e39->__av;
                { //slice 
                  const HashIndex_NUMWAITSUPPLIER1_P_2_map_1* i40 = static_cast<HashIndex_NUMWAITSUPPLIER1_P_2_map_1*>(NUMWAITSUPPLIER1_P_2.index[1]);
                  const HASH_RES_t h23 = NUMWAITSUPPLIER1_P_2_mapkey1_idxfn::hash(se45.modify1(s_suppkey));
                  HashIndex_NUMWAITSUPPLIER1_P_2_map_1::IdxNode* n40 = static_cast<HashIndex_NUMWAITSUPPLIER1_P_2_map_1::IdxNode*>(i40->slice(se45, h23));
                  NUMWAITSUPPLIER1_P_2_entry* e40;
                 
                  if (n40 && (e40 = n40->obj)) {
                    do {                
                      long l1_orderkey = e40->L1_ORDERKEY;
                      long v40 = e40->__av;
                      long agg13 = 0L;
                      { //slice 
                        const HashIndex_NUMWAITSUPPLIER1_L2_1_map_0* i41 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0*>(NUMWAITSUPPLIER1_L2_1.index[1]);
                        const HASH_RES_t h21 = NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::hash(se43.modify0(l1_orderkey));
                        HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode* n41 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode*>(i41->slice(se43, h21));
                        NUMWAITSUPPLIER1_L2_1_entry* e41;
                       
                        if (n41 && (e41 = n41->obj)) {
                          do {                
                            long l3_suppkey = e41->L3_SUPPKEY;
                            long v41 = e41->__av;
                            (/*if */(l3_suppkey != s_suppkey) ? agg13 += v41 : 0L);
                            n41 = n41->nxt;
                          } while (n41 && (e41 = n41->obj) && h21 == n41->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::equals(se43, *e41)); 
                        }
                      }long agg14 = 0L;
                      { //slice 
                        const HashIndex_NUMWAITSUPPLIER1_E3_1_map_0* i42 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0*>(NUMWAITSUPPLIER1_E3_1.index[1]);
                        const HASH_RES_t h22 = NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::hash(se44.modify0(l1_orderkey));
                        HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode* n42 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode*>(i42->slice(se44, h22));
                        NUMWAITSUPPLIER1_E3_1_entry* e42;
                       
                        if (n42 && (e42 = n42->obj)) {
                          do {                
                            long l2_suppkey = e42->L2_SUPPKEY;
                            long v42 = e42->__av;
                            (/*if */(l2_suppkey != s_suppkey) ? agg14 += v42 : 0L);
                            n42 = n42->nxt;
                          } while (n42 && (e42 = n42->obj) && h22 == n42->hash &&  NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::equals(se44, *e42)); 
                        }
                      }(/*if */(l11 == agg13) ? NUMWAIT.addOrDelOnZero(se41.modify(s_name),(v39 * (NUMWAITSUPPLIER1_P_1.getValueOrDefault(se42.modify(s_nationkey)) * (v40 * (agg14 != 0 ? 1L : 0L))))) : (void)0);
                      n40 = n40->nxt;
                    } while (n40 && (e40 = n40->obj) && h23 == n40->hash &&  NUMWAITSUPPLIER1_P_2_mapkey1_idxfn::equals(se45, *e40)); 
                  }
                }
              n39 = n39->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMWAITSUPPLIER1_DELTA_map_012* i43 = static_cast<HashIndex_NUMWAITSUPPLIER1_DELTA_map_012*>(NUMWAITSUPPLIER1_DELTA.index[0]);
          HashIndex_NUMWAITSUPPLIER1_DELTA_map_012::IdxNode* n43; 
          NUMWAITSUPPLIER1_DELTA_entry* e43;
        
          for (size_t i = 0; i < i43->size_; i++)
          {
            n43 = i43->buckets_ + i;
            while (n43 && (e43 = n43->obj))
            {
                long s_suppkey = e43->S_SUPPKEY;
                STRING_TYPE s_name = e43->S_NAME;
                long s_nationkey = e43->S_NATIONKEY;
                long v43 = e43->__av;
                { //slice 
                  const HashIndex_NUMWAITSUPPLIER1_L2_1_map_1* i44 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_1*>(NUMWAITSUPPLIER1_L2_1.index[2]);
                  const HASH_RES_t h24 = NUMWAITSUPPLIER1_L2_1_mapkey1_idxfn::hash(se48.modify1(s_suppkey));
                  HashIndex_NUMWAITSUPPLIER1_L2_1_map_1::IdxNode* n44 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_1::IdxNode*>(i44->slice(se48, h24));
                  NUMWAITSUPPLIER1_L2_1_entry* e44;
                 
                  if (n44 && (e44 = n44->obj)) {
                    do {                
                      long l1_orderkey = e44->L1_ORDERKEY;
                      long v44 = e44->__av;
                      NUMWAITORDERS1.addOrDelOnZero(se46.modify(s_suppkey,s_name,l1_orderkey),(v43 * (NUMWAITSUPPLIER1_P_1.getValueOrDefault(se47.modify(s_nationkey)) * v44)));
                      n44 = n44->nxt;
                    } while (n44 && (e44 = n44->obj) && h24 == n44->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey1_idxfn::equals(se48, *e44)); 
                  }
                }
              n43 = n43->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMWAITSUPPLIER1_DELTA_map_012* i45 = static_cast<HashIndex_NUMWAITSUPPLIER1_DELTA_map_012*>(NUMWAITSUPPLIER1_DELTA.index[0]);
          HashIndex_NUMWAITSUPPLIER1_DELTA_map_012::IdxNode* n45; 
          NUMWAITSUPPLIER1_DELTA_entry* e45;
        
          for (size_t i = 0; i < i45->size_; i++)
          {
            n45 = i45->buckets_ + i;
            while (n45 && (e45 = n45->obj))
            {
                long s_suppkey = e45->S_SUPPKEY;
                STRING_TYPE s_name = e45->S_NAME;
                long s_nationkey = e45->S_NATIONKEY;
                long v45 = e45->__av;
                NUMWAITORDERS1LINEITEM1.addOrDelOnZero(se49.modify(s_suppkey,s_name),(v45 * NUMWAITSUPPLIER1_P_1.getValueOrDefault(se50.modify(s_nationkey))));
              n45 = n45->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMWAITSUPPLIER1_DELTA_map_012* i46 = static_cast<HashIndex_NUMWAITSUPPLIER1_DELTA_map_012*>(NUMWAITSUPPLIER1_DELTA.index[0]);
          HashIndex_NUMWAITSUPPLIER1_DELTA_map_012::IdxNode* n46; 
          NUMWAITSUPPLIER1_DELTA_entry* e46;
        
          for (size_t i = 0; i < i46->size_; i++)
          {
            n46 = i46->buckets_ + i;
            while (n46 && (e46 = n46->obj))
            {
                long s_suppkey = e46->S_SUPPKEY;
                STRING_TYPE s_name = e46->S_NAME;
                long s_nationkey = e46->S_NATIONKEY;
                long v46 = e46->__av;
                { //slice 
                  const HashIndex_NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_map_0* i47 = static_cast<HashIndex_NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_map_0*>(NUMWAITLINEITEM1_P_3SUPPLIER1_P_1.index[1]);
                  const HASH_RES_t h26 = NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_mapkey0_idxfn::hash(se53.modify0(s_nationkey));
                  HashIndex_NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_map_0::IdxNode* n47 = static_cast<HashIndex_NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_map_0::IdxNode*>(i47->slice(se53, h26));
                  NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry* e47;
                 
                  if (n47 && (e47 = n47->obj)) {
                    do {                
                      STRING_TYPE n_name = e47->N_NAME;
                      long v47 = e47->__av;
                      { //slice 
                        const HashIndex_NUMWAITSUPPLIER1_L2_1_map_1* i48 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_1*>(NUMWAITSUPPLIER1_L2_1.index[2]);
                        const HASH_RES_t h25 = NUMWAITSUPPLIER1_L2_1_mapkey1_idxfn::hash(se52.modify1(s_suppkey));
                        HashIndex_NUMWAITSUPPLIER1_L2_1_map_1::IdxNode* n48 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_1::IdxNode*>(i48->slice(se52, h25));
                        NUMWAITSUPPLIER1_L2_1_entry* e48;
                       
                        if (n48 && (e48 = n48->obj)) {
                          do {                
                            long l1_orderkey = e48->L1_ORDERKEY;
                            long v48 = e48->__av;
                            NUMWAITLINEITEM1_P_3.addOrDelOnZero(se51.modify(n_name,l1_orderkey,s_suppkey,s_name),(v46 * (v47 * v48)));
                            n48 = n48->nxt;
                          } while (n48 && (e48 = n48->obj) && h25 == n48->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey1_idxfn::equals(se52, *e48)); 
                        }
                      }
                      n47 = n47->nxt;
                    } while (n47 && (e47 = n47->obj) && h26 == n47->hash &&  NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_mapkey0_idxfn::equals(se53, *e47)); 
                  }
                }
              n46 = n46->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMWAITSUPPLIER1_DELTA_map_012* i49 = static_cast<HashIndex_NUMWAITSUPPLIER1_DELTA_map_012*>(NUMWAITSUPPLIER1_DELTA.index[0]);
          HashIndex_NUMWAITSUPPLIER1_DELTA_map_012::IdxNode* n49; 
          NUMWAITSUPPLIER1_DELTA_entry* e49;
        
          for (size_t i = 0; i < i49->size_; i++)
          {
            n49 = i49->buckets_ + i;
            while (n49 && (e49 = n49->obj))
            {
                long s_suppkey = e49->S_SUPPKEY;
                STRING_TYPE s_name = e49->S_NAME;
                long s_nationkey = e49->S_NATIONKEY;
                long v49 = e49->__av;
                { //slice 
                  const HashIndex_NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_map_0* i50 = static_cast<HashIndex_NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_map_0*>(NUMWAITLINEITEM1_P_3SUPPLIER1_P_1.index[1]);
                  const HASH_RES_t h27 = NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_mapkey0_idxfn::hash(se55.modify0(s_nationkey));
                  HashIndex_NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_map_0::IdxNode* n50 = static_cast<HashIndex_NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_map_0::IdxNode*>(i50->slice(se55, h27));
                  NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry* e50;
                 
                  if (n50 && (e50 = n50->obj)) {
                    do {                
                      STRING_TYPE n_name = e50->N_NAME;
                      long v50 = e50->__av;
                      NUMWAITLINEITEM4_P_3.addOrDelOnZero(se54.modify(n_name,s_suppkey,s_name),(v49 * v50));
                      n50 = n50->nxt;
                    } while (n50 && (e50 = n50->obj) && h27 == n50->hash &&  NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_mapkey0_idxfn::equals(se55, *e50)); 
                  }
                }
              n49 = n49->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        NUMWAITLINEITEM1_P_3SUPPLIER1_P_1.clear();
        {  // foreach
          const HashIndex_NATION_map_0123* i51 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n51; 
          NATION_entry* e51;
        
          for (size_t i = 0; i < i51->size_; i++)
          {
            n51 = i51->buckets_ + i;
            while (n51 && (e51 = n51->obj))
            {
                long s_nationkey = e51->NATION_NATIONKEY;
                STRING_TYPE n_name = e51->NATION_NAME;
                long n_regionkey = e51->NATION_REGIONKEY;
                STRING_TYPE n_comment = e51->NATION_COMMENT;
                long v51 = e51->__av;
                NUMWAITLINEITEM1_P_3SUPPLIER1_P_1.addOrDelOnZero(se56.modify(s_nationkey,n_name),v51);
              n51 = n51->nxt;
            }
          }
        }NUMWAITSUPPLIER1_P_1.clear();
        STRING_TYPE l12 = c2;
        { //slice 
          const HashIndex_NATION_map_1* i52 = static_cast<HashIndex_NATION_map_1*>(NATION.index[1]);
          const HASH_RES_t h28 = NATION_mapkey1_idxfn::hash(se58.modify1(l12));
          HashIndex_NATION_map_1::IdxNode* n52 = static_cast<HashIndex_NATION_map_1::IdxNode*>(i52->slice(se58, h28));
          NATION_entry* e52;
         
          if (n52 && (e52 = n52->obj)) {
            do {                
              long s_nationkey = e52->NATION_NATIONKEY;
              long n_regionkey = e52->NATION_REGIONKEY;
              STRING_TYPE n_comment = e52->NATION_COMMENT;
              long v52 = e52->__av;
              NUMWAITSUPPLIER1_P_1.addOrDelOnZero(se57.modify(s_nationkey),v52);
              n52 = n52->nxt;
            } while (n52 && (e52 = n52->obj) && h28 == n52->hash &&  NATION_mapkey1_idxfn::equals(se58, *e52)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    NUMWAITLINEITEM3_E3_2_DELTA_entry se1;
    NUMWAITLINEITEM3_L2_2_DELTA_entry se2;
    NUMWAITLINEITEM1_DOMAIN1_P_3_entry se3;
    NUMWAIT_entry se4;
    NUMWAITLINEITEM1_P_4_entry se5;
    NUMWAITSUPPLIER1_L2_1_entry se6;
    NUMWAITSUPPLIER1_E3_1_entry se7;
    NUMWAITLINEITEM1_P_3_entry se8;
    NUMWAITLINEITEM1_P_4_entry se9;
    NUMWAITSUPPLIER1_L2_1_entry se10;
    NUMWAITLINEITEM3_L2_2_DELTA_entry se11;
    NUMWAITSUPPLIER1_E3_1_entry se12;
    NUMWAITLINEITEM3_E3_2_DELTA_entry se13;
    NUMWAITLINEITEM1_P_3_entry se14;
    NUMWAITSUPPLIER1_L2_1_entry se15;
    NUMWAITLINEITEM3_L2_2_DELTA_entry se16;
    NUMWAITLINEITEM1_P_4_entry se17;
    NUMWAITSUPPLIER1_E3_1_entry se18;
    NUMWAITLINEITEM3_E3_2_DELTA_entry se19;
    NUMWAITLINEITEM4_P_3_entry se20;
    NUMWAITLINEITEM3_L2_2_DELTA_entry se21;
    NUMWAITORDERS1_entry se22;
    NUMWAITORDERS1LINEITEM1_entry se23;
    NUMWAITLINEITEM1_P_3_entry se24;
    NUMWAITLINEITEM4_P_3_entry se25;
    NUMWAITSUPPLIER1_P_2_entry se26;
    NUMWAITSUPPLIER1_P_2LINEITEM1_entry se27;
    NUMWAITSUPPLIER1_L2_1_entry se28;
    NUMWAITSUPPLIER1_E3_1_entry se29;
    NUMWAITORDERS1_DELTA_entry se30;
    NUMWAITLINEITEM1_P_4ORDERS1_DELTA_entry se31;
    NUMWAIT_entry se32;
    NUMWAITSUPPLIER1_L2_1_entry se33;
    NUMWAITSUPPLIER1_E3_1_entry se34;
    NUMWAITORDERS1_entry se35;
    NUMWAITLINEITEM1_P_4_entry se36;
    NUMWAITSUPPLIER1_P_2_entry se37;
    NUMWAITSUPPLIER1_L2_1_entry se38;
    NUMWAITSUPPLIER1_P_2LINEITEM1_entry se39;
    NUMWAITSUPPLIER1_DELTA_entry se40;
    NUMWAIT_entry se41;
    NUMWAITSUPPLIER1_P_1_entry se42;
    NUMWAITSUPPLIER1_L2_1_entry se43;
    NUMWAITSUPPLIER1_E3_1_entry se44;
    NUMWAITSUPPLIER1_P_2_entry se45;
    NUMWAITORDERS1_entry se46;
    NUMWAITSUPPLIER1_P_1_entry se47;
    NUMWAITSUPPLIER1_L2_1_entry se48;
    NUMWAITORDERS1LINEITEM1_entry se49;
    NUMWAITSUPPLIER1_P_1_entry se50;
    NUMWAITLINEITEM1_P_3_entry se51;
    NUMWAITSUPPLIER1_L2_1_entry se52;
    NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry se53;
    NUMWAITLINEITEM4_P_3_entry se54;
    NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry se55;
    NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_entry se56;
    NUMWAITSUPPLIER1_P_1_entry se57;
    NATION_entry se58;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    NUMWAITORDERS1_DELTA_map NUMWAITORDERS1_DELTA;
    NUMWAITORDERS1_map NUMWAITORDERS1;
    NUMWAITORDERS1LINEITEM1_map NUMWAITORDERS1LINEITEM1;
    NUMWAITLINEITEM1_DOMAIN1_P_3_map NUMWAITLINEITEM1_DOMAIN1_P_3;
    NUMWAITLINEITEM1_P_3_map NUMWAITLINEITEM1_P_3;
    NUMWAITLINEITEM1_P_3SUPPLIER1_P_1_map NUMWAITLINEITEM1_P_3SUPPLIER1_P_1;
    NUMWAITLINEITEM1_P_4_map NUMWAITLINEITEM1_P_4;
    NUMWAITLINEITEM1_P_4ORDERS1_DELTA_map NUMWAITLINEITEM1_P_4ORDERS1_DELTA;
    NUMWAITLINEITEM3_L2_2_DELTA_map NUMWAITLINEITEM3_L2_2_DELTA;
    NUMWAITLINEITEM3_E3_2_DELTA_map NUMWAITLINEITEM3_E3_2_DELTA;
    NUMWAITLINEITEM4_P_3_map NUMWAITLINEITEM4_P_3;
    NUMWAITSUPPLIER1_DELTA_map NUMWAITSUPPLIER1_DELTA;
    NUMWAITSUPPLIER1_P_1_map NUMWAITSUPPLIER1_P_1;
    NUMWAITSUPPLIER1_P_2_map NUMWAITSUPPLIER1_P_2;
    NUMWAITSUPPLIER1_P_2LINEITEM1_map NUMWAITSUPPLIER1_P_2LINEITEM1;
    NUMWAITSUPPLIER1_L2_1_map NUMWAITSUPPLIER1_L2_1;
    NUMWAITSUPPLIER1_E3_1_map NUMWAITSUPPLIER1_E3_1;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_ORDERS_map DELTA_ORDERS;
    DELTA_SUPPLIER_map DELTA_SUPPLIER;
    
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c2;
  
  };

}
