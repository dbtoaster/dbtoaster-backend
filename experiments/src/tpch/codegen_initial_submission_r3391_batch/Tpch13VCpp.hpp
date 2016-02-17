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
  
  struct CUSTDIST_entry {
    long C_ORDERS_C_COUNT; long __av; 
    explicit CUSTDIST_entry() { /*C_ORDERS_C_COUNT = 0L; __av = 0L; */ }
    explicit CUSTDIST_entry(const long c0, const long c1) { C_ORDERS_C_COUNT = c0; __av = c1; }
    CUSTDIST_entry(const CUSTDIST_entry& other) : C_ORDERS_C_COUNT( other.C_ORDERS_C_COUNT ), __av( other.__av ) {}
    FORCE_INLINE CUSTDIST_entry& modify(const long c0) { C_ORDERS_C_COUNT = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ORDERS_C_COUNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDIST_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDIST_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_ORDERS_C_COUNT);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDIST_entry& x, const CUSTDIST_entry& y) {
      return x.C_ORDERS_C_COUNT == y.C_ORDERS_C_COUNT;
    }
  };
  
  typedef MultiHashMap<CUSTDIST_entry,long,
    HashIndex<CUSTDIST_entry,long,CUSTDIST_mapkey0_idxfn,true>
  > CUSTDIST_map;
  typedef HashIndex<CUSTDIST_entry,long,CUSTDIST_mapkey0_idxfn,true> HashIndex_CUSTDIST_map_0;
  
  struct CUSTDISTORDERS1_DOMAIN1_entry {
    long C_ORDERS_C_CUSTKEY; long __av; 
    explicit CUSTDISTORDERS1_DOMAIN1_entry() { /*C_ORDERS_C_CUSTKEY = 0L; __av = 0L; */ }
    explicit CUSTDISTORDERS1_DOMAIN1_entry(const long c0, const long c1) { C_ORDERS_C_CUSTKEY = c0; __av = c1; }
    CUSTDISTORDERS1_DOMAIN1_entry(const CUSTDISTORDERS1_DOMAIN1_entry& other) : C_ORDERS_C_CUSTKEY( other.C_ORDERS_C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE CUSTDISTORDERS1_DOMAIN1_entry& modify(const long c0) { C_ORDERS_C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ORDERS_C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDISTORDERS1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDISTORDERS1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_ORDERS_C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDISTORDERS1_DOMAIN1_entry& x, const CUSTDISTORDERS1_DOMAIN1_entry& y) {
      return x.C_ORDERS_C_CUSTKEY == y.C_ORDERS_C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<CUSTDISTORDERS1_DOMAIN1_entry,long,
    HashIndex<CUSTDISTORDERS1_DOMAIN1_entry,long,CUSTDISTORDERS1_DOMAIN1_mapkey0_idxfn,true>
  > CUSTDISTORDERS1_DOMAIN1_map;
  typedef HashIndex<CUSTDISTORDERS1_DOMAIN1_entry,long,CUSTDISTORDERS1_DOMAIN1_mapkey0_idxfn,true> HashIndex_CUSTDISTORDERS1_DOMAIN1_map_0;
  
  struct CUSTDISTORDERS3_L1_2_DELTA_entry {
    long C_CUSTKEY; long C_ORDERS_C_CUSTKEY; long __av; 
    explicit CUSTDISTORDERS3_L1_2_DELTA_entry() { /*C_CUSTKEY = 0L; C_ORDERS_C_CUSTKEY = 0L; __av = 0L; */ }
    explicit CUSTDISTORDERS3_L1_2_DELTA_entry(const long c0, const long c1, const long c2) { C_CUSTKEY = c0; C_ORDERS_C_CUSTKEY = c1; __av = c2; }
    CUSTDISTORDERS3_L1_2_DELTA_entry(const CUSTDISTORDERS3_L1_2_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ORDERS_C_CUSTKEY( other.C_ORDERS_C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE CUSTDISTORDERS3_L1_2_DELTA_entry& modify(const long c0, const long c1) { C_CUSTKEY = c0; C_ORDERS_C_CUSTKEY = c1;  return *this; }
    FORCE_INLINE CUSTDISTORDERS3_L1_2_DELTA_entry& modify1(const long c1) { C_ORDERS_C_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ORDERS_C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDISTORDERS3_L1_2_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDISTORDERS3_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ORDERS_C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDISTORDERS3_L1_2_DELTA_entry& x, const CUSTDISTORDERS3_L1_2_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ORDERS_C_CUSTKEY == y.C_ORDERS_C_CUSTKEY;
    }
  };
  
  struct CUSTDISTORDERS3_L1_2_DELTA_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDISTORDERS3_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_ORDERS_C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDISTORDERS3_L1_2_DELTA_entry& x, const CUSTDISTORDERS3_L1_2_DELTA_entry& y) {
      return x.C_ORDERS_C_CUSTKEY == y.C_ORDERS_C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<CUSTDISTORDERS3_L1_2_DELTA_entry,long,
    HashIndex<CUSTDISTORDERS3_L1_2_DELTA_entry,long,CUSTDISTORDERS3_L1_2_DELTA_mapkey01_idxfn,true>,
    HashIndex<CUSTDISTORDERS3_L1_2_DELTA_entry,long,CUSTDISTORDERS3_L1_2_DELTA_mapkey1_idxfn,false>
  > CUSTDISTORDERS3_L1_2_DELTA_map;
  typedef HashIndex<CUSTDISTORDERS3_L1_2_DELTA_entry,long,CUSTDISTORDERS3_L1_2_DELTA_mapkey01_idxfn,true> HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_01;
  typedef HashIndex<CUSTDISTORDERS3_L1_2_DELTA_entry,long,CUSTDISTORDERS3_L1_2_DELTA_mapkey1_idxfn,false> HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_1;
  
  struct CUSTDISTORDERS3_L1_2_entry {
    long C_CUSTKEY; long __av; 
    explicit CUSTDISTORDERS3_L1_2_entry() { /*C_CUSTKEY = 0L; __av = 0L; */ }
    explicit CUSTDISTORDERS3_L1_2_entry(const long c0, const long c1) { C_CUSTKEY = c0; __av = c1; }
    CUSTDISTORDERS3_L1_2_entry(const CUSTDISTORDERS3_L1_2_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE CUSTDISTORDERS3_L1_2_entry& modify(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDISTORDERS3_L1_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDISTORDERS3_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDISTORDERS3_L1_2_entry& x, const CUSTDISTORDERS3_L1_2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<CUSTDISTORDERS3_L1_2_entry,long,
    HashIndex<CUSTDISTORDERS3_L1_2_entry,long,CUSTDISTORDERS3_L1_2_mapkey0_idxfn,true>
  > CUSTDISTORDERS3_L1_2_map;
  typedef HashIndex<CUSTDISTORDERS3_L1_2_entry,long,CUSTDISTORDERS3_L1_2_mapkey0_idxfn,true> HashIndex_CUSTDISTORDERS3_L1_2_map_0;
  
  struct CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; long __av; 
    explicit CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; __av = 0L; */ }
    explicit CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry(const long c0, const long c1) { C_CUSTKEY = c0; __av = c1; }
    CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry(const CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry& modify(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry& x, const CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry,long,
    HashIndex<CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry,long,CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_mapkey0_idxfn,true>
  > CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_map;
  typedef HashIndex<CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry,long,CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_mapkey0_idxfn,true> HashIndex_CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_map_0;
  
  struct CUSTDISTCUSTOMER1_DOMAIN1_entry {
    long C_ORDERS_C_CUSTKEY; long __av; 
    explicit CUSTDISTCUSTOMER1_DOMAIN1_entry() { /*C_ORDERS_C_CUSTKEY = 0L; __av = 0L; */ }
    explicit CUSTDISTCUSTOMER1_DOMAIN1_entry(const long c0, const long c1) { C_ORDERS_C_CUSTKEY = c0; __av = c1; }
    CUSTDISTCUSTOMER1_DOMAIN1_entry(const CUSTDISTCUSTOMER1_DOMAIN1_entry& other) : C_ORDERS_C_CUSTKEY( other.C_ORDERS_C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE CUSTDISTCUSTOMER1_DOMAIN1_entry& modify(const long c0) { C_ORDERS_C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ORDERS_C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDISTCUSTOMER1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDISTCUSTOMER1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_ORDERS_C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDISTCUSTOMER1_DOMAIN1_entry& x, const CUSTDISTCUSTOMER1_DOMAIN1_entry& y) {
      return x.C_ORDERS_C_CUSTKEY == y.C_ORDERS_C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<CUSTDISTCUSTOMER1_DOMAIN1_entry,long,
    HashIndex<CUSTDISTCUSTOMER1_DOMAIN1_entry,long,CUSTDISTCUSTOMER1_DOMAIN1_mapkey0_idxfn,true>
  > CUSTDISTCUSTOMER1_DOMAIN1_map;
  typedef HashIndex<CUSTDISTCUSTOMER1_DOMAIN1_entry,long,CUSTDISTCUSTOMER1_DOMAIN1_mapkey0_idxfn,true> HashIndex_CUSTDISTCUSTOMER1_DOMAIN1_map_0;
  
  struct CUSTDISTCUSTOMER1_L1_1_entry {
    long C_ORDERS_C_CUSTKEY; long __av; 
    explicit CUSTDISTCUSTOMER1_L1_1_entry() { /*C_ORDERS_C_CUSTKEY = 0L; __av = 0L; */ }
    explicit CUSTDISTCUSTOMER1_L1_1_entry(const long c0, const long c1) { C_ORDERS_C_CUSTKEY = c0; __av = c1; }
    CUSTDISTCUSTOMER1_L1_1_entry(const CUSTDISTCUSTOMER1_L1_1_entry& other) : C_ORDERS_C_CUSTKEY( other.C_ORDERS_C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE CUSTDISTCUSTOMER1_L1_1_entry& modify(const long c0) { C_ORDERS_C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ORDERS_C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDISTCUSTOMER1_L1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDISTCUSTOMER1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_ORDERS_C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDISTCUSTOMER1_L1_1_entry& x, const CUSTDISTCUSTOMER1_L1_1_entry& y) {
      return x.C_ORDERS_C_CUSTKEY == y.C_ORDERS_C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<CUSTDISTCUSTOMER1_L1_1_entry,long,
    HashIndex<CUSTDISTCUSTOMER1_L1_1_entry,long,CUSTDISTCUSTOMER1_L1_1_mapkey0_idxfn,true>
  > CUSTDISTCUSTOMER1_L1_1_map;
  typedef HashIndex<CUSTDISTCUSTOMER1_L1_1_entry,long,CUSTDISTCUSTOMER1_L1_1_mapkey0_idxfn,true> HashIndex_CUSTDISTCUSTOMER1_L1_1_map_0;
  
  struct CUSTDISTCUSTOMER3_L1_2_DELTA_entry {
    long C_CUSTKEY; long C_ORDERS_C_CUSTKEY; long __av; 
    explicit CUSTDISTCUSTOMER3_L1_2_DELTA_entry() { /*C_CUSTKEY = 0L; C_ORDERS_C_CUSTKEY = 0L; __av = 0L; */ }
    explicit CUSTDISTCUSTOMER3_L1_2_DELTA_entry(const long c0, const long c1, const long c2) { C_CUSTKEY = c0; C_ORDERS_C_CUSTKEY = c1; __av = c2; }
    CUSTDISTCUSTOMER3_L1_2_DELTA_entry(const CUSTDISTCUSTOMER3_L1_2_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ORDERS_C_CUSTKEY( other.C_ORDERS_C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE CUSTDISTCUSTOMER3_L1_2_DELTA_entry& modify(const long c0, const long c1) { C_CUSTKEY = c0; C_ORDERS_C_CUSTKEY = c1;  return *this; }
    FORCE_INLINE CUSTDISTCUSTOMER3_L1_2_DELTA_entry& modify1(const long c1) { C_ORDERS_C_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ORDERS_C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDISTCUSTOMER3_L1_2_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDISTCUSTOMER3_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ORDERS_C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDISTCUSTOMER3_L1_2_DELTA_entry& x, const CUSTDISTCUSTOMER3_L1_2_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ORDERS_C_CUSTKEY == y.C_ORDERS_C_CUSTKEY;
    }
  };
  
  struct CUSTDISTCUSTOMER3_L1_2_DELTA_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDISTCUSTOMER3_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_ORDERS_C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDISTCUSTOMER3_L1_2_DELTA_entry& x, const CUSTDISTCUSTOMER3_L1_2_DELTA_entry& y) {
      return x.C_ORDERS_C_CUSTKEY == y.C_ORDERS_C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<CUSTDISTCUSTOMER3_L1_2_DELTA_entry,long,
    HashIndex<CUSTDISTCUSTOMER3_L1_2_DELTA_entry,long,CUSTDISTCUSTOMER3_L1_2_DELTA_mapkey01_idxfn,true>,
    HashIndex<CUSTDISTCUSTOMER3_L1_2_DELTA_entry,long,CUSTDISTCUSTOMER3_L1_2_DELTA_mapkey1_idxfn,false>
  > CUSTDISTCUSTOMER3_L1_2_DELTA_map;
  typedef HashIndex<CUSTDISTCUSTOMER3_L1_2_DELTA_entry,long,CUSTDISTCUSTOMER3_L1_2_DELTA_mapkey01_idxfn,true> HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_01;
  typedef HashIndex<CUSTDISTCUSTOMER3_L1_2_DELTA_entry,long,CUSTDISTCUSTOMER3_L1_2_DELTA_mapkey1_idxfn,false> HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_1;
  
  struct CUSTDISTCUSTOMER3_L1_2_entry {
    long C_CUSTKEY; long __av; 
    explicit CUSTDISTCUSTOMER3_L1_2_entry() { /*C_CUSTKEY = 0L; __av = 0L; */ }
    explicit CUSTDISTCUSTOMER3_L1_2_entry(const long c0, const long c1) { C_CUSTKEY = c0; __av = c1; }
    CUSTDISTCUSTOMER3_L1_2_entry(const CUSTDISTCUSTOMER3_L1_2_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE CUSTDISTCUSTOMER3_L1_2_entry& modify(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDISTCUSTOMER3_L1_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDISTCUSTOMER3_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDISTCUSTOMER3_L1_2_entry& x, const CUSTDISTCUSTOMER3_L1_2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<CUSTDISTCUSTOMER3_L1_2_entry,long,
    HashIndex<CUSTDISTCUSTOMER3_L1_2_entry,long,CUSTDISTCUSTOMER3_L1_2_mapkey0_idxfn,true>
  > CUSTDISTCUSTOMER3_L1_2_map;
  typedef HashIndex<CUSTDISTCUSTOMER3_L1_2_entry,long,CUSTDISTCUSTOMER3_L1_2_mapkey0_idxfn,true> HashIndex_CUSTDISTCUSTOMER3_L1_2_map_0;
  
  struct CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry {
    long C_CUSTKEY; long __av; 
    explicit CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry() { /*C_CUSTKEY = 0L; __av = 0L; */ }
    explicit CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry(const long c0, const long c1) { C_CUSTKEY = c0; __av = c1; }
    CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry(const CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry& modify(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry& x, const CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry,long,
    HashIndex<CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry,long,CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_mapkey0_idxfn,true>
  > CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_map;
  typedef HashIndex<CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry,long,CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_mapkey0_idxfn,true> HashIndex_CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_map_0;
  
  struct tuple2_L_L {
    long _1; long __av;
    explicit tuple2_L_L() { }
    explicit tuple2_L_L(const long c1, long c__av=0L) { _1 = c1; __av = c__av;}
    int operator==(const tuple2_L_L &rhs) const { return ((this->_1==rhs._1)); }
    FORCE_INLINE tuple2_L_L& modify(const long c0, long c__av) { _1 = c0; __av = c__av; return *this; }
    static bool equals(const tuple2_L_L &x, const tuple2_L_L &y) { return ((x._1==y._1)); }
    static long hash(const tuple2_L_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      return h;
    }
  };
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0),tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const CUSTDIST_map& _CUSTDIST = get_CUSTDIST();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(CUSTDIST), _CUSTDIST, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const CUSTDIST_map& get_CUSTDIST() const {
      return CUSTDIST;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    CUSTDIST_map CUSTDIST;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), agg4(16U), agg1(16U) {
      
      /* regex_t init */
      if(regcomp(&preg1, "^.*special.*requests.*$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^.*special.*requests.*$/" << endl;
        exit(-1);
      }
    }
  
    ~data_t() {
      regfree(&preg1);
    }
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
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


        CUSTDISTORDERS3_L1_2_DELTA.clear();
        CUSTDISTORDERS1_DOMAIN1.clear();
        CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_ORDERS.size; i++)
          {
                // long o_orderkey = DELTA_ORDERS.orderkey[i];
                long c_custkey = DELTA_ORDERS.custkey[i];
                // STRING_TYPE o_orderstatus = DELTA_ORDERS.orderstatus[i];
                // DOUBLE_TYPE o_totalprice = DELTA_ORDERS.totalprice[i];
                // date o_orderdate = DELTA_ORDERS.orderdate[i];
                // STRING_TYPE o_orderpriority = DELTA_ORDERS.orderpriority[i];
                // STRING_TYPE o_clerk = DELTA_ORDERS.clerk[i];
                // long o_shippriority = DELTA_ORDERS.shippriority[i];
                STRING_TYPE o_comment = DELTA_ORDERS.comment[i];
                long v1 = 1L;
                long preg1_match = Upreg_match(preg1,o_comment);
                (/*if */(0L == preg1_match) ? CUSTDISTORDERS3_L1_2_DELTA.addOrDelOnZero(se1.modify(c_custkey,c_custkey),v1) : (void)0);
                long v2 = 1L;
                (/*if */(0L == preg1_match) ? CUSTDISTORDERS1_DOMAIN1.addOrDelOnZero(se2.modify(c_custkey),(v2 != 0 ? 1L : 0L)) : (void)0);
                long v3 = 1L;
                (/*if */(0L == preg1_match) ? CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA.addOrDelOnZero(se3.modify(c_custkey),v3) : (void)0);
          }
        }
        
        agg1.clear();        
        {  // foreach
          const HashIndex_CUSTDISTCUSTOMER1_L1_1_map_0* i4 = static_cast<HashIndex_CUSTDISTCUSTOMER1_L1_1_map_0*>(CUSTDISTCUSTOMER1_L1_1.index[0]);
          HashIndex_CUSTDISTCUSTOMER1_L1_1_map_0::IdxNode* n4; 
          CUSTDISTCUSTOMER1_L1_1_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long c_orders_c_custkey = e4->C_ORDERS_C_CUSTKEY;
                long v4 = e4->__av;
                long l1 = CUSTDISTCUSTOMER1_L1_1.getValueOrDefault(se5.modify(c_orders_c_custkey));
                agg1.addOrDelOnZero(st1.modify(l1,(v4 != 0 ? 1L : 0L)), (v4 != 0 ? 1L : 0L));
              n4 = n4->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i5 = static_cast<HashIndex<tuple2_L_L, long>*>(agg1.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n5; 
          tuple2_L_L* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
              long c_orders_c_count = e5->_1;  
              long v5 = e5->__av; 
            if (CUSTDIST.getValueOrDefault(se4.modify(c_orders_c_count))==0) CUSTDIST.setOrDelOnZero(se4, v5);      
              n5 = n5->nxt;
            }
          }
        }{  // foreach
          const HashIndex_CUSTDISTORDERS1_DOMAIN1_map_0* i6 = static_cast<HashIndex_CUSTDISTORDERS1_DOMAIN1_map_0*>(CUSTDISTORDERS1_DOMAIN1.index[0]);
          HashIndex_CUSTDISTORDERS1_DOMAIN1_map_0::IdxNode* n6; 
          CUSTDISTORDERS1_DOMAIN1_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long c_orders_c_custkey = e6->C_ORDERS_C_CUSTKEY;
                long v6 = e6->__av;
                long l2 = CUSTDISTCUSTOMER1_L1_1.getValueOrDefault(se6.modify(c_orders_c_custkey));
                CUSTDIST.addOrDelOnZero(se4.modify(l2),(((v6 != 0 ? 1L : 0L) * (CUSTDISTCUSTOMER1_L1_1.getValueOrDefault(se7.modify(c_orders_c_custkey)) != 0 ? 1L : 0L)) * -1L));
              n6 = n6->nxt;
            }
          }
        }{  // foreach
          const HashIndex_CUSTDISTORDERS1_DOMAIN1_map_0* i7 = static_cast<HashIndex_CUSTDISTORDERS1_DOMAIN1_map_0*>(CUSTDISTORDERS1_DOMAIN1.index[0]);
          HashIndex_CUSTDISTORDERS1_DOMAIN1_map_0::IdxNode* n7; 
          CUSTDISTORDERS1_DOMAIN1_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long c_orders_c_custkey = e7->C_ORDERS_C_CUSTKEY;
                long v7 = e7->__av;
                long agg2 = 0L;
                { //slice 
                  const HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_1* i8 = static_cast<HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_1*>(CUSTDISTORDERS3_L1_2_DELTA.index[1]);
                  const HASH_RES_t h1 = CUSTDISTORDERS3_L1_2_DELTA_mapkey1_idxfn::hash(se10.modify1(c_orders_c_custkey));
                  HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_1::IdxNode* n8 = static_cast<HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_1::IdxNode*>(i8->slice(se10, h1));
                  CUSTDISTORDERS3_L1_2_DELTA_entry* e8;
                 
                  if (n8 && (e8 = n8->obj)) {
                    do {                
                      long c_custkey = e8->C_CUSTKEY;
                      long v8 = e8->__av;
                      agg2 += (v8 * CUSTDISTORDERS3_L1_2.getValueOrDefault(se9.modify(c_custkey)));
                      n8 = n8->nxt;
                    } while (n8 && (e8 = n8->obj) && h1 == n8->hash &&  CUSTDISTORDERS3_L1_2_DELTA_mapkey1_idxfn::equals(se10, *e8)); 
                  }
                }long l3 = (CUSTDISTCUSTOMER1_L1_1.getValueOrDefault(se8.modify(c_orders_c_custkey)) + agg2);
                long agg3 = 0L;
                { //slice 
                  const HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_1* i9 = static_cast<HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_1*>(CUSTDISTORDERS3_L1_2_DELTA.index[1]);
                  const HASH_RES_t h2 = CUSTDISTORDERS3_L1_2_DELTA_mapkey1_idxfn::hash(se13.modify1(c_orders_c_custkey));
                  HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_1::IdxNode* n9 = static_cast<HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_1::IdxNode*>(i9->slice(se13, h2));
                  CUSTDISTORDERS3_L1_2_DELTA_entry* e9;
                 
                  if (n9 && (e9 = n9->obj)) {
                    do {                
                      long c_custkey = e9->C_CUSTKEY;
                      long v9 = e9->__av;
                      agg3 += (v9 * CUSTDISTORDERS3_L1_2.getValueOrDefault(se12.modify(c_custkey)));
                      n9 = n9->nxt;
                    } while (n9 && (e9 = n9->obj) && h2 == n9->hash &&  CUSTDISTORDERS3_L1_2_DELTA_mapkey1_idxfn::equals(se13, *e9)); 
                  }
                }CUSTDIST.addOrDelOnZero(se4.modify(l3),((v7 != 0 ? 1L : 0L) * ((CUSTDISTCUSTOMER1_L1_1.getValueOrDefault(se11.modify(c_orders_c_custkey)) + agg3) != 0 ? 1L : 0L)));
              n7 = n7->nxt;
            }
          }
        }{  // foreach
          const HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_01* i10 = static_cast<HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_01*>(CUSTDISTORDERS3_L1_2_DELTA.index[0]);
          HashIndex_CUSTDISTORDERS3_L1_2_DELTA_map_01::IdxNode* n10; 
          CUSTDISTORDERS3_L1_2_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long c_custkey = e10->C_CUSTKEY;
                long c_orders_c_custkey = e10->C_ORDERS_C_CUSTKEY;
                long v10 = e10->__av;
                CUSTDISTCUSTOMER1_L1_1.addOrDelOnZero(se14.modify(c_orders_c_custkey),(v10 * CUSTDISTORDERS3_L1_2.getValueOrDefault(se15.modify(c_custkey))));
              n10 = n10->nxt;
            }
          }
        }{  // foreach
          const HashIndex_CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_map_0* i11 = static_cast<HashIndex_CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_map_0*>(CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA.index[0]);
          HashIndex_CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_map_0::IdxNode* n11; 
          CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long c_custkey = e11->C_CUSTKEY;
                long v11 = e11->__av;
                CUSTDISTCUSTOMER3_L1_2.addOrDelOnZero(se16.modify(c_custkey),v11);
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

        CUSTDISTCUSTOMER3_L1_2_DELTA.clear();
        CUSTDISTCUSTOMER1_DOMAIN1.clear();
        CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_CUSTOMER.size; i++)
          {
                long c_custkey = DELTA_CUSTOMER.custkey[i];
                // STRING_TYPE c_name = DELTA_CUSTOMER.name[i];
                // STRING_TYPE c_address = DELTA_CUSTOMER.address[i];
                // long c_nationkey = DELTA_CUSTOMER.nationkey[i];
                // STRING_TYPE c_phone = DELTA_CUSTOMER.phone[i];
                // DOUBLE_TYPE c_acctbal = DELTA_CUSTOMER.acctbal[i];
                // STRING_TYPE c_mktsegment = DELTA_CUSTOMER.mktsegment[i];
                // STRING_TYPE c_comment = DELTA_CUSTOMER.comment[i];
                long v12 = 1L;
                CUSTDISTCUSTOMER3_L1_2_DELTA.addOrDelOnZero(se17.modify(c_custkey,c_custkey),v12);
                long v13 = 1L;
                CUSTDISTCUSTOMER1_DOMAIN1.addOrDelOnZero(se18.modify(c_custkey),(v13 != 0 ? 1L : 0L));
                long v14 = 1L;
                CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA.addOrDelOnZero(se19.modify(c_custkey),v14);
          }
        }
        
        agg4.clear();
        
        {  // foreach
          const HashIndex_CUSTDISTCUSTOMER1_L1_1_map_0* i15 = static_cast<HashIndex_CUSTDISTCUSTOMER1_L1_1_map_0*>(CUSTDISTCUSTOMER1_L1_1.index[0]);
          HashIndex_CUSTDISTCUSTOMER1_L1_1_map_0::IdxNode* n15; 
          CUSTDISTCUSTOMER1_L1_1_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long c_orders_c_custkey = e15->C_ORDERS_C_CUSTKEY;
                long v15 = e15->__av;
                long l4 = CUSTDISTCUSTOMER1_L1_1.getValueOrDefault(se21.modify(c_orders_c_custkey));
                agg4.addOrDelOnZero(st2.modify(l4,(v15 != 0 ? 1L : 0L)), (v15 != 0 ? 1L : 0L));
              n15 = n15->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i16 = static_cast<HashIndex<tuple2_L_L, long>*>(agg4.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n16; 
          tuple2_L_L* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
              long c_orders_c_count = e16->_1;  
              long v16 = e16->__av; 
            if (CUSTDIST.getValueOrDefault(se20.modify(c_orders_c_count))==0) CUSTDIST.setOrDelOnZero(se20, v16);      
              n16 = n16->nxt;
            }
          }
        }{  // foreach
          const HashIndex_CUSTDISTCUSTOMER1_DOMAIN1_map_0* i17 = static_cast<HashIndex_CUSTDISTCUSTOMER1_DOMAIN1_map_0*>(CUSTDISTCUSTOMER1_DOMAIN1.index[0]);
          HashIndex_CUSTDISTCUSTOMER1_DOMAIN1_map_0::IdxNode* n17; 
          CUSTDISTCUSTOMER1_DOMAIN1_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long c_orders_c_custkey = e17->C_ORDERS_C_CUSTKEY;
                long v17 = e17->__av;
                long l5 = CUSTDISTCUSTOMER1_L1_1.getValueOrDefault(se22.modify(c_orders_c_custkey));
                CUSTDIST.addOrDelOnZero(se20.modify(l5),(((v17 != 0 ? 1L : 0L) * (CUSTDISTCUSTOMER1_L1_1.getValueOrDefault(se23.modify(c_orders_c_custkey)) != 0 ? 1L : 0L)) * -1L));
              n17 = n17->nxt;
            }
          }
        }{  // foreach
          const HashIndex_CUSTDISTCUSTOMER1_DOMAIN1_map_0* i18 = static_cast<HashIndex_CUSTDISTCUSTOMER1_DOMAIN1_map_0*>(CUSTDISTCUSTOMER1_DOMAIN1.index[0]);
          HashIndex_CUSTDISTCUSTOMER1_DOMAIN1_map_0::IdxNode* n18; 
          CUSTDISTCUSTOMER1_DOMAIN1_entry* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
                long c_orders_c_custkey = e18->C_ORDERS_C_CUSTKEY;
                long v18 = e18->__av;
                long agg5 = 0L;
                { //slice 
                  const HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_1* i19 = static_cast<HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_1*>(CUSTDISTCUSTOMER3_L1_2_DELTA.index[1]);
                  const HASH_RES_t h3 = CUSTDISTCUSTOMER3_L1_2_DELTA_mapkey1_idxfn::hash(se26.modify1(c_orders_c_custkey));
                  HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_1::IdxNode* n19 = static_cast<HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_1::IdxNode*>(i19->slice(se26, h3));
                  CUSTDISTCUSTOMER3_L1_2_DELTA_entry* e19;
                 
                  if (n19 && (e19 = n19->obj)) {
                    do {                
                      long c_custkey = e19->C_CUSTKEY;
                      long v19 = e19->__av;
                      agg5 += (v19 * CUSTDISTCUSTOMER3_L1_2.getValueOrDefault(se25.modify(c_custkey)));
                      n19 = n19->nxt;
                    } while (n19 && (e19 = n19->obj) && h3 == n19->hash &&  CUSTDISTCUSTOMER3_L1_2_DELTA_mapkey1_idxfn::equals(se26, *e19)); 
                  }
                }long l6 = (CUSTDISTCUSTOMER1_L1_1.getValueOrDefault(se24.modify(c_orders_c_custkey)) + agg5);
                long agg6 = 0L;
                { //slice 
                  const HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_1* i20 = static_cast<HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_1*>(CUSTDISTCUSTOMER3_L1_2_DELTA.index[1]);
                  const HASH_RES_t h4 = CUSTDISTCUSTOMER3_L1_2_DELTA_mapkey1_idxfn::hash(se29.modify1(c_orders_c_custkey));
                  HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_1::IdxNode* n20 = static_cast<HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_1::IdxNode*>(i20->slice(se29, h4));
                  CUSTDISTCUSTOMER3_L1_2_DELTA_entry* e20;
                 
                  if (n20 && (e20 = n20->obj)) {
                    do {                
                      long c_custkey = e20->C_CUSTKEY;
                      long v20 = e20->__av;
                      agg6 += (v20 * CUSTDISTCUSTOMER3_L1_2.getValueOrDefault(se28.modify(c_custkey)));
                      n20 = n20->nxt;
                    } while (n20 && (e20 = n20->obj) && h4 == n20->hash &&  CUSTDISTCUSTOMER3_L1_2_DELTA_mapkey1_idxfn::equals(se29, *e20)); 
                  }
                }CUSTDIST.addOrDelOnZero(se20.modify(l6),((v18 != 0 ? 1L : 0L) * ((CUSTDISTCUSTOMER1_L1_1.getValueOrDefault(se27.modify(c_orders_c_custkey)) + agg6) != 0 ? 1L : 0L)));
              n18 = n18->nxt;
            }
          }
        }{  // foreach
          const HashIndex_CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_map_0* i21 = static_cast<HashIndex_CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_map_0*>(CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA.index[0]);
          HashIndex_CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_map_0::IdxNode* n21; 
          CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry* e21;
        
          for (size_t i = 0; i < i21->size_; i++)
          {
            n21 = i21->buckets_ + i;
            while (n21 && (e21 = n21->obj))
            {
                long c_custkey = e21->C_CUSTKEY;
                long v21 = e21->__av;
                CUSTDISTORDERS3_L1_2.addOrDelOnZero(se30.modify(c_custkey),v21);
              n21 = n21->nxt;
            }
          }
        }{  // foreach
          const HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_01* i22 = static_cast<HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_01*>(CUSTDISTCUSTOMER3_L1_2_DELTA.index[0]);
          HashIndex_CUSTDISTCUSTOMER3_L1_2_DELTA_map_01::IdxNode* n22; 
          CUSTDISTCUSTOMER3_L1_2_DELTA_entry* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
                long c_custkey = e22->C_CUSTKEY;
                long c_orders_c_custkey = e22->C_ORDERS_C_CUSTKEY;
                long v22 = e22->__av;
                CUSTDISTCUSTOMER1_L1_1.addOrDelOnZero(se31.modify(c_orders_c_custkey),(v22 * CUSTDISTCUSTOMER3_L1_2.getValueOrDefault(se32.modify(c_custkey))));
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
    CUSTDISTORDERS3_L1_2_DELTA_entry se1;
    CUSTDISTORDERS1_DOMAIN1_entry se2;
    CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_entry se3;
    CUSTDIST_entry se4;
    CUSTDISTCUSTOMER1_L1_1_entry se5;
    tuple2_L_L st1;
    CUSTDISTCUSTOMER1_L1_1_entry se6;
    CUSTDISTCUSTOMER1_L1_1_entry se7;
    CUSTDISTCUSTOMER1_L1_1_entry se8;
    CUSTDISTORDERS3_L1_2_entry se9;
    CUSTDISTORDERS3_L1_2_DELTA_entry se10;
    CUSTDISTCUSTOMER1_L1_1_entry se11;
    CUSTDISTORDERS3_L1_2_entry se12;
    CUSTDISTORDERS3_L1_2_DELTA_entry se13;
    CUSTDISTCUSTOMER1_L1_1_entry se14;
    CUSTDISTORDERS3_L1_2_entry se15;
    CUSTDISTCUSTOMER3_L1_2_entry se16;
    CUSTDISTCUSTOMER3_L1_2_DELTA_entry se17;
    CUSTDISTCUSTOMER1_DOMAIN1_entry se18;
    CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_entry se19;
    CUSTDIST_entry se20;
    CUSTDISTCUSTOMER1_L1_1_entry se21;
    tuple2_L_L st2;
    CUSTDISTCUSTOMER1_L1_1_entry se22;
    CUSTDISTCUSTOMER1_L1_1_entry se23;
    CUSTDISTCUSTOMER1_L1_1_entry se24;
    CUSTDISTCUSTOMER3_L1_2_entry se25;
    CUSTDISTCUSTOMER3_L1_2_DELTA_entry se26;
    CUSTDISTCUSTOMER1_L1_1_entry se27;
    CUSTDISTCUSTOMER3_L1_2_entry se28;
    CUSTDISTCUSTOMER3_L1_2_DELTA_entry se29;
    CUSTDISTORDERS3_L1_2_entry se30;
    CUSTDISTCUSTOMER1_L1_1_entry se31;
    CUSTDISTCUSTOMER3_L1_2_entry se32;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    CUSTDISTORDERS1_DOMAIN1_map CUSTDISTORDERS1_DOMAIN1;
    CUSTDISTORDERS3_L1_2_DELTA_map CUSTDISTORDERS3_L1_2_DELTA;
    CUSTDISTORDERS3_L1_2_map CUSTDISTORDERS3_L1_2;
    CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA_map CUSTDISTORDERS3_L1_2CUSTOMER1_DELTA;
    CUSTDISTCUSTOMER1_DOMAIN1_map CUSTDISTCUSTOMER1_DOMAIN1;
    CUSTDISTCUSTOMER1_L1_1_map CUSTDISTCUSTOMER1_L1_1;
    CUSTDISTCUSTOMER3_L1_2_DELTA_map CUSTDISTCUSTOMER3_L1_2_DELTA;
    CUSTDISTCUSTOMER3_L1_2_map CUSTDISTCUSTOMER3_L1_2;
    CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA_map CUSTDISTCUSTOMER3_L1_2ORDERS1_DELTA;
    DELTA_ORDERS_map DELTA_ORDERS;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg4;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg1;
    
  
  };

}
