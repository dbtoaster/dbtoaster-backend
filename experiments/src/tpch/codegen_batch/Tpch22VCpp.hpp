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
  
  struct NUMCUST_entry {
    STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUST_entry() { /*CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUST_entry(const STRING_TYPE& c0, const long c1) { CUSTSALE_CNTRYCODE = c0; __av = c1; }
    NUMCUST_entry(const NUMCUST_entry& other) : CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUST_entry& modify(const STRING_TYPE& c0) { CUSTSALE_CNTRYCODE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUST_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_entry& x, const NUMCUST_entry& y) {
      return x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<NUMCUST_entry,long,
    HashIndex<NUMCUST_entry,long,NUMCUST_mapkey0_idxfn,true>
  > NUMCUST_map;
  typedef HashIndex<NUMCUST_entry,long,NUMCUST_mapkey0_idxfn,true> HashIndex_NUMCUST_map_0;
  
  struct NUMCUSTORDERS1_DOMAIN1_entry {
    long C_CUSTKEY; long __av; 
    explicit NUMCUSTORDERS1_DOMAIN1_entry() { /*C_CUSTKEY = 0L; __av = 0L; */ }
    explicit NUMCUSTORDERS1_DOMAIN1_entry(const long c0, const long c1) { C_CUSTKEY = c0; __av = c1; }
    NUMCUSTORDERS1_DOMAIN1_entry(const NUMCUSTORDERS1_DOMAIN1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTORDERS1_DOMAIN1_entry& modify(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTORDERS1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTORDERS1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTORDERS1_DOMAIN1_entry& x, const NUMCUSTORDERS1_DOMAIN1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUSTORDERS1_DOMAIN1_entry,long,
    HashIndex<NUMCUSTORDERS1_DOMAIN1_entry,long,NUMCUSTORDERS1_DOMAIN1_mapkey0_idxfn,true>
  > NUMCUSTORDERS1_DOMAIN1_map;
  typedef HashIndex<NUMCUSTORDERS1_DOMAIN1_entry,long,NUMCUSTORDERS1_DOMAIN1_mapkey0_idxfn,true> HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0;
  
  struct NUMCUSTORDERS1_L2_2_DELTA_entry {
    long C_CUSTKEY; long __av; 
    explicit NUMCUSTORDERS1_L2_2_DELTA_entry() { /*C_CUSTKEY = 0L; __av = 0L; */ }
    explicit NUMCUSTORDERS1_L2_2_DELTA_entry(const long c0, const long c1) { C_CUSTKEY = c0; __av = c1; }
    NUMCUSTORDERS1_L2_2_DELTA_entry(const NUMCUSTORDERS1_L2_2_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTORDERS1_L2_2_DELTA_entry& modify(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTORDERS1_L2_2_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTORDERS1_L2_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTORDERS1_L2_2_DELTA_entry& x, const NUMCUSTORDERS1_L2_2_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUSTORDERS1_L2_2_DELTA_entry,long,
    HashIndex<NUMCUSTORDERS1_L2_2_DELTA_entry,long,NUMCUSTORDERS1_L2_2_DELTA_mapkey0_idxfn,true>
  > NUMCUSTORDERS1_L2_2_DELTA_map;
  typedef HashIndex<NUMCUSTORDERS1_L2_2_DELTA_entry,long,NUMCUSTORDERS1_L2_2_DELTA_mapkey0_idxfn,true> HashIndex_NUMCUSTORDERS1_L2_2_DELTA_map_0;
  
  struct NUMCUSTCUSTOMER1_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER1_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER1_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER1_entry(const NUMCUSTCUSTOMER1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER1_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUSTCUSTOMER1_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER1_entry& x, const NUMCUSTCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUSTCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER1_entry& x, const NUMCUSTCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER1_entry,long,
    HashIndex<NUMCUSTCUSTOMER1_entry,long,NUMCUSTCUSTOMER1_mapkey012_idxfn,true>,
    HashIndex<NUMCUSTCUSTOMER1_entry,long,NUMCUSTCUSTOMER1_mapkey0_idxfn,false>
  > NUMCUSTCUSTOMER1_map;
  typedef HashIndex<NUMCUSTCUSTOMER1_entry,long,NUMCUSTCUSTOMER1_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER1_map_012;
  typedef HashIndex<NUMCUSTCUSTOMER1_entry,long,NUMCUSTCUSTOMER1_mapkey0_idxfn,false> HashIndex_NUMCUSTCUSTOMER1_map_0;
  
  struct NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry(const NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER1CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry& x, const NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry,long,
    HashIndex<NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER1CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > NUMCUSTCUSTOMER1CUSTOMER1_DELTA_map;
  typedef HashIndex<NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER1CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER1CUSTOMER1_DELTA_map_012;
  
  struct NUMCUSTCUSTOMER1_L3_1_entry {
    long C_CUSTKEY; long __av; 
    explicit NUMCUSTCUSTOMER1_L3_1_entry() { /*C_CUSTKEY = 0L; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER1_L3_1_entry(const long c0, const long c1) { C_CUSTKEY = c0; __av = c1; }
    NUMCUSTCUSTOMER1_L3_1_entry(const NUMCUSTCUSTOMER1_L3_1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER1_L3_1_entry& modify(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER1_L3_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER1_L3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER1_L3_1_entry& x, const NUMCUSTCUSTOMER1_L3_1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER1_L3_1_entry,long,
    HashIndex<NUMCUSTCUSTOMER1_L3_1_entry,long,NUMCUSTCUSTOMER1_L3_1_mapkey0_idxfn,true>
  > NUMCUSTCUSTOMER1_L3_1_map;
  typedef HashIndex<NUMCUSTCUSTOMER1_L3_1_entry,long,NUMCUSTCUSTOMER1_L3_1_mapkey0_idxfn,true> HashIndex_NUMCUSTCUSTOMER1_L3_1_map_0;
  
  struct NUMCUSTCUSTOMER2_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER2_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER2_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER2_entry(const NUMCUSTCUSTOMER2_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER2_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUSTCUSTOMER2_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER2_entry& x, const NUMCUSTCUSTOMER2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUSTCUSTOMER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER2_entry& x, const NUMCUSTCUSTOMER2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER2_entry,long,
    HashIndex<NUMCUSTCUSTOMER2_entry,long,NUMCUSTCUSTOMER2_mapkey012_idxfn,true>,
    HashIndex<NUMCUSTCUSTOMER2_entry,long,NUMCUSTCUSTOMER2_mapkey0_idxfn,false>
  > NUMCUSTCUSTOMER2_map;
  typedef HashIndex<NUMCUSTCUSTOMER2_entry,long,NUMCUSTCUSTOMER2_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER2_map_012;
  typedef HashIndex<NUMCUSTCUSTOMER2_entry,long,NUMCUSTCUSTOMER2_mapkey0_idxfn,false> HashIndex_NUMCUSTCUSTOMER2_map_0;
  
  struct NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry(const NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER2CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry& x, const NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry,long,
    HashIndex<NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER2CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > NUMCUSTCUSTOMER2CUSTOMER1_DELTA_map;
  typedef HashIndex<NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER2CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER2CUSTOMER1_DELTA_map_012;
  
  struct NUMCUSTCUSTOMER3_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER3_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER3_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER3_entry(const NUMCUSTCUSTOMER3_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER3_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUSTCUSTOMER3_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER3_entry& x, const NUMCUSTCUSTOMER3_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUSTCUSTOMER3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER3_entry& x, const NUMCUSTCUSTOMER3_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER3_entry,long,
    HashIndex<NUMCUSTCUSTOMER3_entry,long,NUMCUSTCUSTOMER3_mapkey012_idxfn,true>,
    HashIndex<NUMCUSTCUSTOMER3_entry,long,NUMCUSTCUSTOMER3_mapkey0_idxfn,false>
  > NUMCUSTCUSTOMER3_map;
  typedef HashIndex<NUMCUSTCUSTOMER3_entry,long,NUMCUSTCUSTOMER3_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER3_map_012;
  typedef HashIndex<NUMCUSTCUSTOMER3_entry,long,NUMCUSTCUSTOMER3_mapkey0_idxfn,false> HashIndex_NUMCUSTCUSTOMER3_map_0;
  
  struct NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry(const NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER3CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry& x, const NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry,long,
    HashIndex<NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER3CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > NUMCUSTCUSTOMER3CUSTOMER1_DELTA_map;
  typedef HashIndex<NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER3CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER3CUSTOMER1_DELTA_map_012;
  
  struct NUMCUSTCUSTOMER4_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER4_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER4_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER4_entry(const NUMCUSTCUSTOMER4_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER4_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUSTCUSTOMER4_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER4_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER4_entry& x, const NUMCUSTCUSTOMER4_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUSTCUSTOMER4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER4_entry& x, const NUMCUSTCUSTOMER4_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER4_entry,long,
    HashIndex<NUMCUSTCUSTOMER4_entry,long,NUMCUSTCUSTOMER4_mapkey012_idxfn,true>,
    HashIndex<NUMCUSTCUSTOMER4_entry,long,NUMCUSTCUSTOMER4_mapkey0_idxfn,false>
  > NUMCUSTCUSTOMER4_map;
  typedef HashIndex<NUMCUSTCUSTOMER4_entry,long,NUMCUSTCUSTOMER4_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER4_map_012;
  typedef HashIndex<NUMCUSTCUSTOMER4_entry,long,NUMCUSTCUSTOMER4_mapkey0_idxfn,false> HashIndex_NUMCUSTCUSTOMER4_map_0;
  
  struct NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry(const NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER4CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry& x, const NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry,long,
    HashIndex<NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER4CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > NUMCUSTCUSTOMER4CUSTOMER1_DELTA_map;
  typedef HashIndex<NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER4CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER4CUSTOMER1_DELTA_map_012;
  
  struct NUMCUSTCUSTOMER5_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER5_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER5_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER5_entry(const NUMCUSTCUSTOMER5_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER5_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUSTCUSTOMER5_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER5_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER5_entry& x, const NUMCUSTCUSTOMER5_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUSTCUSTOMER5_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER5_entry& x, const NUMCUSTCUSTOMER5_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER5_entry,long,
    HashIndex<NUMCUSTCUSTOMER5_entry,long,NUMCUSTCUSTOMER5_mapkey012_idxfn,true>,
    HashIndex<NUMCUSTCUSTOMER5_entry,long,NUMCUSTCUSTOMER5_mapkey0_idxfn,false>
  > NUMCUSTCUSTOMER5_map;
  typedef HashIndex<NUMCUSTCUSTOMER5_entry,long,NUMCUSTCUSTOMER5_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER5_map_012;
  typedef HashIndex<NUMCUSTCUSTOMER5_entry,long,NUMCUSTCUSTOMER5_mapkey0_idxfn,false> HashIndex_NUMCUSTCUSTOMER5_map_0;
  
  struct NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry(const NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER5CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry& x, const NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry,long,
    HashIndex<NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER5CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > NUMCUSTCUSTOMER5CUSTOMER1_DELTA_map;
  typedef HashIndex<NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER5CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER5CUSTOMER1_DELTA_map_012;
  
  struct NUMCUSTCUSTOMER6_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER6_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER6_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER6_entry(const NUMCUSTCUSTOMER6_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER6_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUSTCUSTOMER6_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER6_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER6_entry& x, const NUMCUSTCUSTOMER6_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUSTCUSTOMER6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER6_entry& x, const NUMCUSTCUSTOMER6_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER6_entry,long,
    HashIndex<NUMCUSTCUSTOMER6_entry,long,NUMCUSTCUSTOMER6_mapkey012_idxfn,true>,
    HashIndex<NUMCUSTCUSTOMER6_entry,long,NUMCUSTCUSTOMER6_mapkey0_idxfn,false>
  > NUMCUSTCUSTOMER6_map;
  typedef HashIndex<NUMCUSTCUSTOMER6_entry,long,NUMCUSTCUSTOMER6_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER6_map_012;
  typedef HashIndex<NUMCUSTCUSTOMER6_entry,long,NUMCUSTCUSTOMER6_mapkey0_idxfn,false> HashIndex_NUMCUSTCUSTOMER6_map_0;
  
  struct NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry(const NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER6CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry& x, const NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry,long,
    HashIndex<NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER6CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > NUMCUSTCUSTOMER6CUSTOMER1_DELTA_map;
  typedef HashIndex<NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER6CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER6CUSTOMER1_DELTA_map_012;
  
  struct NUMCUSTCUSTOMER7_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER7_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER7_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER7_entry(const NUMCUSTCUSTOMER7_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER7_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUSTCUSTOMER7_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER7_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER7_entry& x, const NUMCUSTCUSTOMER7_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUSTCUSTOMER7_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER7_entry& x, const NUMCUSTCUSTOMER7_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER7_entry,long,
    HashIndex<NUMCUSTCUSTOMER7_entry,long,NUMCUSTCUSTOMER7_mapkey012_idxfn,true>,
    HashIndex<NUMCUSTCUSTOMER7_entry,long,NUMCUSTCUSTOMER7_mapkey0_idxfn,false>
  > NUMCUSTCUSTOMER7_map;
  typedef HashIndex<NUMCUSTCUSTOMER7_entry,long,NUMCUSTCUSTOMER7_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER7_map_012;
  typedef HashIndex<NUMCUSTCUSTOMER7_entry,long,NUMCUSTCUSTOMER7_mapkey0_idxfn,false> HashIndex_NUMCUSTCUSTOMER7_map_0;
  
  struct NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry(const NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER7CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry& x, const NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry,long,
    HashIndex<NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER7CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > NUMCUSTCUSTOMER7CUSTOMER1_DELTA_map;
  typedef HashIndex<NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry,long,NUMCUSTCUSTOMER7CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER7CUSTOMER1_DELTA_map_012;
  
  struct TOTALACCTBAL_entry {
    STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBAL_entry() { /*CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBAL_entry(const STRING_TYPE& c0, const DOUBLE_TYPE c1) { CUSTSALE_CNTRYCODE = c0; __av = c1; }
    TOTALACCTBAL_entry(const TOTALACCTBAL_entry& other) : CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBAL_entry& modify(const STRING_TYPE& c0) { CUSTSALE_CNTRYCODE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBAL_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_entry& x, const TOTALACCTBAL_entry& y) {
      return x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBAL_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBAL_entry,DOUBLE_TYPE,TOTALACCTBAL_mapkey0_idxfn,true>
  > TOTALACCTBAL_map;
  typedef HashIndex<TOTALACCTBAL_entry,DOUBLE_TYPE,TOTALACCTBAL_mapkey0_idxfn,true> HashIndex_TOTALACCTBAL_map_0;
  
  struct TOTALACCTBALCUSTOMER1_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER1_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER1_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER1_entry(const TOTALACCTBALCUSTOMER1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER1_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBALCUSTOMER1_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER1_entry& x, const TOTALACCTBALCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBALCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER1_entry& x, const TOTALACCTBALCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER1_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBALCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER1_mapkey0_idxfn,false>
  > TOTALACCTBALCUSTOMER1_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER1_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER1_map_012;
  typedef HashIndex<TOTALACCTBALCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER1_mapkey0_idxfn,false> HashIndex_TOTALACCTBALCUSTOMER1_map_0;
  
  struct TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry(const TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry& x, const TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_map_012;
  
  struct TOTALACCTBALCUSTOMER2_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER2_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER2_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER2_entry(const TOTALACCTBALCUSTOMER2_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER2_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBALCUSTOMER2_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER2_entry& x, const TOTALACCTBALCUSTOMER2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBALCUSTOMER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER2_entry& x, const TOTALACCTBALCUSTOMER2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER2_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER2_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER2_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBALCUSTOMER2_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER2_mapkey0_idxfn,false>
  > TOTALACCTBALCUSTOMER2_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER2_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER2_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER2_map_012;
  typedef HashIndex<TOTALACCTBALCUSTOMER2_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER2_mapkey0_idxfn,false> HashIndex_TOTALACCTBALCUSTOMER2_map_0;
  
  struct TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry(const TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry& x, const TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_map_012;
  
  struct TOTALACCTBALCUSTOMER3_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER3_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER3_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER3_entry(const TOTALACCTBALCUSTOMER3_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER3_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBALCUSTOMER3_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER3_entry& x, const TOTALACCTBALCUSTOMER3_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBALCUSTOMER3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER3_entry& x, const TOTALACCTBALCUSTOMER3_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER3_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER3_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER3_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBALCUSTOMER3_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER3_mapkey0_idxfn,false>
  > TOTALACCTBALCUSTOMER3_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER3_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER3_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER3_map_012;
  typedef HashIndex<TOTALACCTBALCUSTOMER3_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER3_mapkey0_idxfn,false> HashIndex_TOTALACCTBALCUSTOMER3_map_0;
  
  struct TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry(const TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry& x, const TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_map_012;
  
  struct TOTALACCTBALCUSTOMER4_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER4_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER4_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER4_entry(const TOTALACCTBALCUSTOMER4_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER4_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBALCUSTOMER4_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER4_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER4_entry& x, const TOTALACCTBALCUSTOMER4_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBALCUSTOMER4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER4_entry& x, const TOTALACCTBALCUSTOMER4_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER4_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER4_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER4_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBALCUSTOMER4_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER4_mapkey0_idxfn,false>
  > TOTALACCTBALCUSTOMER4_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER4_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER4_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER4_map_012;
  typedef HashIndex<TOTALACCTBALCUSTOMER4_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER4_mapkey0_idxfn,false> HashIndex_TOTALACCTBALCUSTOMER4_map_0;
  
  struct TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry(const TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry& x, const TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_map_012;
  
  struct TOTALACCTBALCUSTOMER5_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER5_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER5_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER5_entry(const TOTALACCTBALCUSTOMER5_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER5_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBALCUSTOMER5_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER5_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER5_entry& x, const TOTALACCTBALCUSTOMER5_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBALCUSTOMER5_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER5_entry& x, const TOTALACCTBALCUSTOMER5_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER5_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER5_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER5_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBALCUSTOMER5_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER5_mapkey0_idxfn,false>
  > TOTALACCTBALCUSTOMER5_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER5_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER5_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER5_map_012;
  typedef HashIndex<TOTALACCTBALCUSTOMER5_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER5_mapkey0_idxfn,false> HashIndex_TOTALACCTBALCUSTOMER5_map_0;
  
  struct TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry(const TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry& x, const TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_map_012;
  
  struct TOTALACCTBALCUSTOMER6_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER6_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER6_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER6_entry(const TOTALACCTBALCUSTOMER6_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER6_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBALCUSTOMER6_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER6_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER6_entry& x, const TOTALACCTBALCUSTOMER6_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBALCUSTOMER6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER6_entry& x, const TOTALACCTBALCUSTOMER6_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER6_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER6_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER6_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBALCUSTOMER6_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER6_mapkey0_idxfn,false>
  > TOTALACCTBALCUSTOMER6_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER6_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER6_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER6_map_012;
  typedef HashIndex<TOTALACCTBALCUSTOMER6_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER6_mapkey0_idxfn,false> HashIndex_TOTALACCTBALCUSTOMER6_map_0;
  
  struct TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry(const TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry& x, const TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_map_012;
  
  struct TOTALACCTBALCUSTOMER7_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER7_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER7_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER7_entry(const TOTALACCTBALCUSTOMER7_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER7_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBALCUSTOMER7_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER7_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER7_entry& x, const TOTALACCTBALCUSTOMER7_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBALCUSTOMER7_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER7_entry& x, const TOTALACCTBALCUSTOMER7_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER7_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER7_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER7_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBALCUSTOMER7_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER7_mapkey0_idxfn,false>
  > TOTALACCTBALCUSTOMER7_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER7_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER7_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER7_map_012;
  typedef HashIndex<TOTALACCTBALCUSTOMER7_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER7_mapkey0_idxfn,false> HashIndex_TOTALACCTBALCUSTOMER7_map_0;
  
  struct TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry(const TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry& x, const TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_mapkey012_idxfn,true>
  > TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_map_012;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const NUMCUST_map& _NUMCUST = get_NUMCUST();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(NUMCUST), _NUMCUST, "\t");
      ar << "\n";
      const TOTALACCTBAL_map& _TOTALACCTBAL = get_TOTALACCTBAL();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(TOTALACCTBAL), _TOTALACCTBAL, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const NUMCUST_map& get_NUMCUST() const {
      return NUMCUST;
    
    }
    const TOTALACCTBAL_map& get_TOTALACCTBAL() const {
      return TOTALACCTBAL;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    NUMCUST_map NUMCUST;
    TOTALACCTBAL_map TOTALACCTBAL;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), NUMCUSTCUSTOMER1_L2_1_L1_1(0L), NUMCUSTCUSTOMER1_L2_1_L1_1CUSTOMER1_DELTA(0L), NUMCUSTCUSTOMER1_L2_1_L1_2(0L), NUMCUSTCUSTOMER1_L2_1_L1_2CUSTOMER1_DELTA(0L), NUMCUSTCUSTOMER1_L2_1_L1_3(0L), NUMCUSTCUSTOMER1_L2_1_L1_3CUSTOMER1_DELTA(0L), NUMCUSTCUSTOMER1_L2_1_L1_4(0L), NUMCUSTCUSTOMER1_L2_1_L1_4CUSTOMER1_DELTA(0L), NUMCUSTCUSTOMER1_L2_1_L1_5(0L), NUMCUSTCUSTOMER1_L2_1_L1_5CUSTOMER1_DELTA(0L), NUMCUSTCUSTOMER1_L2_1_L1_6(0L), NUMCUSTCUSTOMER1_L2_1_L1_6CUSTOMER1_DELTA(0L), NUMCUSTCUSTOMER1_L2_1_L1_7(0L), NUMCUSTCUSTOMER1_L2_1_L1_7CUSTOMER1_DELTA(0L), NUMCUSTCUSTOMER1_L2_2(0.0), NUMCUSTCUSTOMER1_L2_2CUSTOMER1_DELTA(0.0), NUMCUSTCUSTOMER1_L2_4(0.0), NUMCUSTCUSTOMER1_L2_4CUSTOMER1_DELTA(0.0), NUMCUSTCUSTOMER1_L2_6(0.0), NUMCUSTCUSTOMER1_L2_6CUSTOMER1_DELTA(0.0), NUMCUSTCUSTOMER1_L2_8(0.0), NUMCUSTCUSTOMER1_L2_8CUSTOMER1_DELTA(0.0), NUMCUSTCUSTOMER1_L2_10(0.0), NUMCUSTCUSTOMER1_L2_10CUSTOMER1_DELTA(0.0), NUMCUSTCUSTOMER1_L2_12(0.0), NUMCUSTCUSTOMER1_L2_12CUSTOMER1_DELTA(0.0), NUMCUSTCUSTOMER1_L2_14(0.0), NUMCUSTCUSTOMER1_L2_14CUSTOMER1_DELTA(0.0) {
      c7 = STRING_TYPE("17");
      c2 = STRING_TYPE("31");
      c1 = STRING_TYPE("13");
      c3 = STRING_TYPE("23");
      c6 = STRING_TYPE("18");
      c4 = STRING_TYPE("29");
      c5 = STRING_TYPE("30");
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


        NUMCUSTORDERS1_L2_2_DELTA.clear();
        NUMCUSTORDERS1_DOMAIN1.clear();
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
                long v1 = 1L;
                NUMCUSTORDERS1_L2_2_DELTA.addOrDelOnZero(se1.modify(c_custkey),v1);
                long v2 = 1L;
                NUMCUSTORDERS1_DOMAIN1.addOrDelOnZero(se2.modify(c_custkey),(v2 != 0 ? 1L : 0L));                
          }
        }
        
        long l1 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i3 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n3; 
          NUMCUSTORDERS1_DOMAIN1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long c_custkey = e3->C_CUSTKEY;
                long v3 = e3->__av;
                DOUBLE_TYPE agg1 = 0.0;
                long l3 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l3) ? agg1 += Udiv(Ulistmax(1L, l3)) : 0.0);
                DOUBLE_TYPE l2 = (agg1 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER1_map_0* i4 = static_cast<HashIndex_NUMCUSTCUSTOMER1_map_0*>(NUMCUSTCUSTOMER1.index[1]);
                  const HASH_RES_t h1 = NUMCUSTCUSTOMER1_mapkey0_idxfn::hash(se6.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER1_map_0::IdxNode* n4 = static_cast<HashIndex_NUMCUSTCUSTOMER1_map_0::IdxNode*>(i4->slice(se6, h1));
                  NUMCUSTCUSTOMER1_entry* e4;
                 
                  if (n4 && (e4 = n4->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e4->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e4->CUSTSALE_CNTRYCODE;
                      long v4 = e4->__av;
                      (/*if */(l1 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se4.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se5.modify(c_custkey))) && c_acctbal > l2) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),((v3 != 0 ? 1L : 0L) * v4)) : (void)0);
                      n4 = n4->nxt;
                    } while (n4 && (e4 = n4->obj) && h1 == n4->hash &&  NUMCUSTCUSTOMER1_mapkey0_idxfn::equals(se6, *e4)); 
                  }
                }
              n3 = n3->nxt;
            }
          }
        }long l4 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i5 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n5; 
          NUMCUSTORDERS1_DOMAIN1_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long c_custkey = e5->C_CUSTKEY;
                long v5 = e5->__av;
                DOUBLE_TYPE agg2 = 0.0;
                long l6 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l6) ? agg2 += Udiv(Ulistmax(1L, l6)) : 0.0);
                DOUBLE_TYPE l5 = (agg2 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER2_map_0* i6 = static_cast<HashIndex_NUMCUSTCUSTOMER2_map_0*>(NUMCUSTCUSTOMER2.index[1]);
                  const HASH_RES_t h2 = NUMCUSTCUSTOMER2_mapkey0_idxfn::hash(se9.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER2_map_0::IdxNode* n6 = static_cast<HashIndex_NUMCUSTCUSTOMER2_map_0::IdxNode*>(i6->slice(se9, h2));
                  NUMCUSTCUSTOMER2_entry* e6;
                 
                  if (n6 && (e6 = n6->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e6->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e6->CUSTSALE_CNTRYCODE;
                      long v6 = e6->__av;
                      (/*if */(l4 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se7.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se8.modify(c_custkey))) && c_acctbal > l5) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),((v5 != 0 ? 1L : 0L) * v6)) : (void)0);
                      n6 = n6->nxt;
                    } while (n6 && (e6 = n6->obj) && h2 == n6->hash &&  NUMCUSTCUSTOMER2_mapkey0_idxfn::equals(se9, *e6)); 
                  }
                }
              n5 = n5->nxt;
            }
          }
        }long l7 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i7 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n7; 
          NUMCUSTORDERS1_DOMAIN1_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long c_custkey = e7->C_CUSTKEY;
                long v7 = e7->__av;
                DOUBLE_TYPE agg3 = 0.0;
                long l9 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l9) ? agg3 += Udiv(Ulistmax(1L, l9)) : 0.0);
                DOUBLE_TYPE l8 = (agg3 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER3_map_0* i8 = static_cast<HashIndex_NUMCUSTCUSTOMER3_map_0*>(NUMCUSTCUSTOMER3.index[1]);
                  const HASH_RES_t h3 = NUMCUSTCUSTOMER3_mapkey0_idxfn::hash(se12.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER3_map_0::IdxNode* n8 = static_cast<HashIndex_NUMCUSTCUSTOMER3_map_0::IdxNode*>(i8->slice(se12, h3));
                  NUMCUSTCUSTOMER3_entry* e8;
                 
                  if (n8 && (e8 = n8->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e8->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e8->CUSTSALE_CNTRYCODE;
                      long v8 = e8->__av;
                      (/*if */(l7 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se10.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se11.modify(c_custkey))) && c_acctbal > l8) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),((v7 != 0 ? 1L : 0L) * v8)) : (void)0);
                      n8 = n8->nxt;
                    } while (n8 && (e8 = n8->obj) && h3 == n8->hash &&  NUMCUSTCUSTOMER3_mapkey0_idxfn::equals(se12, *e8)); 
                  }
                }
              n7 = n7->nxt;
            }
          }
        }long l10 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i9 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n9; 
          NUMCUSTORDERS1_DOMAIN1_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long c_custkey = e9->C_CUSTKEY;
                long v9 = e9->__av;
                DOUBLE_TYPE agg4 = 0.0;
                long l12 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l12) ? agg4 += Udiv(Ulistmax(1L, l12)) : 0.0);
                DOUBLE_TYPE l11 = (agg4 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER4_map_0* i10 = static_cast<HashIndex_NUMCUSTCUSTOMER4_map_0*>(NUMCUSTCUSTOMER4.index[1]);
                  const HASH_RES_t h4 = NUMCUSTCUSTOMER4_mapkey0_idxfn::hash(se15.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER4_map_0::IdxNode* n10 = static_cast<HashIndex_NUMCUSTCUSTOMER4_map_0::IdxNode*>(i10->slice(se15, h4));
                  NUMCUSTCUSTOMER4_entry* e10;
                 
                  if (n10 && (e10 = n10->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e10->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e10->CUSTSALE_CNTRYCODE;
                      long v10 = e10->__av;
                      (/*if */(l10 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se13.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se14.modify(c_custkey))) && c_acctbal > l11) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),((v9 != 0 ? 1L : 0L) * v10)) : (void)0);
                      n10 = n10->nxt;
                    } while (n10 && (e10 = n10->obj) && h4 == n10->hash &&  NUMCUSTCUSTOMER4_mapkey0_idxfn::equals(se15, *e10)); 
                  }
                }
              n9 = n9->nxt;
            }
          }
        }long l13 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i11 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n11; 
          NUMCUSTORDERS1_DOMAIN1_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long c_custkey = e11->C_CUSTKEY;
                long v11 = e11->__av;
                DOUBLE_TYPE agg5 = 0.0;
                long l15 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l15) ? agg5 += Udiv(Ulistmax(1L, l15)) : 0.0);
                DOUBLE_TYPE l14 = (agg5 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER5_map_0* i12 = static_cast<HashIndex_NUMCUSTCUSTOMER5_map_0*>(NUMCUSTCUSTOMER5.index[1]);
                  const HASH_RES_t h5 = NUMCUSTCUSTOMER5_mapkey0_idxfn::hash(se18.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER5_map_0::IdxNode* n12 = static_cast<HashIndex_NUMCUSTCUSTOMER5_map_0::IdxNode*>(i12->slice(se18, h5));
                  NUMCUSTCUSTOMER5_entry* e12;
                 
                  if (n12 && (e12 = n12->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e12->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e12->CUSTSALE_CNTRYCODE;
                      long v12 = e12->__av;
                      (/*if */(l13 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se16.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se17.modify(c_custkey))) && c_acctbal > l14) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),((v11 != 0 ? 1L : 0L) * v12)) : (void)0);
                      n12 = n12->nxt;
                    } while (n12 && (e12 = n12->obj) && h5 == n12->hash &&  NUMCUSTCUSTOMER5_mapkey0_idxfn::equals(se18, *e12)); 
                  }
                }
              n11 = n11->nxt;
            }
          }
        }long l16 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i13 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n13; 
          NUMCUSTORDERS1_DOMAIN1_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long c_custkey = e13->C_CUSTKEY;
                long v13 = e13->__av;
                DOUBLE_TYPE agg6 = 0.0;
                long l18 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l18) ? agg6 += Udiv(Ulistmax(1L, l18)) : 0.0);
                DOUBLE_TYPE l17 = (agg6 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER6_map_0* i14 = static_cast<HashIndex_NUMCUSTCUSTOMER6_map_0*>(NUMCUSTCUSTOMER6.index[1]);
                  const HASH_RES_t h6 = NUMCUSTCUSTOMER6_mapkey0_idxfn::hash(se21.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER6_map_0::IdxNode* n14 = static_cast<HashIndex_NUMCUSTCUSTOMER6_map_0::IdxNode*>(i14->slice(se21, h6));
                  NUMCUSTCUSTOMER6_entry* e14;
                 
                  if (n14 && (e14 = n14->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e14->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e14->CUSTSALE_CNTRYCODE;
                      long v14 = e14->__av;
                      (/*if */(l16 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se19.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se20.modify(c_custkey))) && c_acctbal > l17) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),((v13 != 0 ? 1L : 0L) * v14)) : (void)0);
                      n14 = n14->nxt;
                    } while (n14 && (e14 = n14->obj) && h6 == n14->hash &&  NUMCUSTCUSTOMER6_mapkey0_idxfn::equals(se21, *e14)); 
                  }
                }
              n13 = n13->nxt;
            }
          }
        }long l19 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i15 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n15; 
          NUMCUSTORDERS1_DOMAIN1_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long c_custkey = e15->C_CUSTKEY;
                long v15 = e15->__av;
                DOUBLE_TYPE agg7 = 0.0;
                long l21 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l21) ? agg7 += Udiv(Ulistmax(1L, l21)) : 0.0);
                DOUBLE_TYPE l20 = (agg7 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER7_map_0* i16 = static_cast<HashIndex_NUMCUSTCUSTOMER7_map_0*>(NUMCUSTCUSTOMER7.index[1]);
                  const HASH_RES_t h7 = NUMCUSTCUSTOMER7_mapkey0_idxfn::hash(se24.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER7_map_0::IdxNode* n16 = static_cast<HashIndex_NUMCUSTCUSTOMER7_map_0::IdxNode*>(i16->slice(se24, h7));
                  NUMCUSTCUSTOMER7_entry* e16;
                 
                  if (n16 && (e16 = n16->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e16->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e16->CUSTSALE_CNTRYCODE;
                      long v16 = e16->__av;
                      (/*if */(l19 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se22.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se23.modify(c_custkey))) && c_acctbal > l20) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),((v15 != 0 ? 1L : 0L) * v16)) : (void)0);
                      n16 = n16->nxt;
                    } while (n16 && (e16 = n16->obj) && h7 == n16->hash &&  NUMCUSTCUSTOMER7_mapkey0_idxfn::equals(se24, *e16)); 
                  }
                }
              n15 = n15->nxt;
            }
          }
        }long l22 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i17 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n17; 
          NUMCUSTORDERS1_DOMAIN1_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long c_custkey = e17->C_CUSTKEY;
                long v17 = e17->__av;
                DOUBLE_TYPE agg8 = 0.0;
                long l24 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l24) ? agg8 += Udiv(Ulistmax(1L, l24)) : 0.0);
                DOUBLE_TYPE l23 = (agg8 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER1_map_0* i18 = static_cast<HashIndex_NUMCUSTCUSTOMER1_map_0*>(NUMCUSTCUSTOMER1.index[1]);
                  const HASH_RES_t h8 = NUMCUSTCUSTOMER1_mapkey0_idxfn::hash(se26.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER1_map_0::IdxNode* n18 = static_cast<HashIndex_NUMCUSTCUSTOMER1_map_0::IdxNode*>(i18->slice(se26, h8));
                  NUMCUSTCUSTOMER1_entry* e18;
                 
                  if (n18 && (e18 = n18->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e18->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e18->CUSTSALE_CNTRYCODE;
                      long v18 = e18->__av;
                      (/*if */(l22 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se25.modify(c_custkey)) && c_acctbal > l23) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),(((v17 != 0 ? 1L : 0L) * v18) * -1L)) : (void)0);
                      n18 = n18->nxt;
                    } while (n18 && (e18 = n18->obj) && h8 == n18->hash &&  NUMCUSTCUSTOMER1_mapkey0_idxfn::equals(se26, *e18)); 
                  }
                }
              n17 = n17->nxt;
            }
          }
        }long l25 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i19 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n19; 
          NUMCUSTORDERS1_DOMAIN1_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long c_custkey = e19->C_CUSTKEY;
                long v19 = e19->__av;
                DOUBLE_TYPE agg9 = 0.0;
                long l27 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l27) ? agg9 += Udiv(Ulistmax(1L, l27)) : 0.0);
                DOUBLE_TYPE l26 = (agg9 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER2_map_0* i20 = static_cast<HashIndex_NUMCUSTCUSTOMER2_map_0*>(NUMCUSTCUSTOMER2.index[1]);
                  const HASH_RES_t h9 = NUMCUSTCUSTOMER2_mapkey0_idxfn::hash(se28.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER2_map_0::IdxNode* n20 = static_cast<HashIndex_NUMCUSTCUSTOMER2_map_0::IdxNode*>(i20->slice(se28, h9));
                  NUMCUSTCUSTOMER2_entry* e20;
                 
                  if (n20 && (e20 = n20->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e20->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e20->CUSTSALE_CNTRYCODE;
                      long v20 = e20->__av;
                      (/*if */(l25 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se27.modify(c_custkey)) && c_acctbal > l26) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),(((v19 != 0 ? 1L : 0L) * v20) * -1L)) : (void)0);
                      n20 = n20->nxt;
                    } while (n20 && (e20 = n20->obj) && h9 == n20->hash &&  NUMCUSTCUSTOMER2_mapkey0_idxfn::equals(se28, *e20)); 
                  }
                }
              n19 = n19->nxt;
            }
          }
        }long l28 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i21 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n21; 
          NUMCUSTORDERS1_DOMAIN1_entry* e21;
        
          for (size_t i = 0; i < i21->size_; i++)
          {
            n21 = i21->buckets_ + i;
            while (n21 && (e21 = n21->obj))
            {
                long c_custkey = e21->C_CUSTKEY;
                long v21 = e21->__av;
                DOUBLE_TYPE agg10 = 0.0;
                long l30 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l30) ? agg10 += Udiv(Ulistmax(1L, l30)) : 0.0);
                DOUBLE_TYPE l29 = (agg10 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER3_map_0* i22 = static_cast<HashIndex_NUMCUSTCUSTOMER3_map_0*>(NUMCUSTCUSTOMER3.index[1]);
                  const HASH_RES_t h10 = NUMCUSTCUSTOMER3_mapkey0_idxfn::hash(se30.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER3_map_0::IdxNode* n22 = static_cast<HashIndex_NUMCUSTCUSTOMER3_map_0::IdxNode*>(i22->slice(se30, h10));
                  NUMCUSTCUSTOMER3_entry* e22;
                 
                  if (n22 && (e22 = n22->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e22->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e22->CUSTSALE_CNTRYCODE;
                      long v22 = e22->__av;
                      (/*if */(l28 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se29.modify(c_custkey)) && c_acctbal > l29) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),(((v21 != 0 ? 1L : 0L) * v22) * -1L)) : (void)0);
                      n22 = n22->nxt;
                    } while (n22 && (e22 = n22->obj) && h10 == n22->hash &&  NUMCUSTCUSTOMER3_mapkey0_idxfn::equals(se30, *e22)); 
                  }
                }
              n21 = n21->nxt;
            }
          }
        }long l31 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i23 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n23; 
          NUMCUSTORDERS1_DOMAIN1_entry* e23;
        
          for (size_t i = 0; i < i23->size_; i++)
          {
            n23 = i23->buckets_ + i;
            while (n23 && (e23 = n23->obj))
            {
                long c_custkey = e23->C_CUSTKEY;
                long v23 = e23->__av;
                DOUBLE_TYPE agg11 = 0.0;
                long l33 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l33) ? agg11 += Udiv(Ulistmax(1L, l33)) : 0.0);
                DOUBLE_TYPE l32 = (agg11 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER4_map_0* i24 = static_cast<HashIndex_NUMCUSTCUSTOMER4_map_0*>(NUMCUSTCUSTOMER4.index[1]);
                  const HASH_RES_t h11 = NUMCUSTCUSTOMER4_mapkey0_idxfn::hash(se32.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER4_map_0::IdxNode* n24 = static_cast<HashIndex_NUMCUSTCUSTOMER4_map_0::IdxNode*>(i24->slice(se32, h11));
                  NUMCUSTCUSTOMER4_entry* e24;
                 
                  if (n24 && (e24 = n24->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e24->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e24->CUSTSALE_CNTRYCODE;
                      long v24 = e24->__av;
                      (/*if */(l31 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se31.modify(c_custkey)) && c_acctbal > l32) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),(((v23 != 0 ? 1L : 0L) * v24) * -1L)) : (void)0);
                      n24 = n24->nxt;
                    } while (n24 && (e24 = n24->obj) && h11 == n24->hash &&  NUMCUSTCUSTOMER4_mapkey0_idxfn::equals(se32, *e24)); 
                  }
                }
              n23 = n23->nxt;
            }
          }
        }long l34 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i25 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n25; 
          NUMCUSTORDERS1_DOMAIN1_entry* e25;
        
          for (size_t i = 0; i < i25->size_; i++)
          {
            n25 = i25->buckets_ + i;
            while (n25 && (e25 = n25->obj))
            {
                long c_custkey = e25->C_CUSTKEY;
                long v25 = e25->__av;
                DOUBLE_TYPE agg12 = 0.0;
                long l36 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l36) ? agg12 += Udiv(Ulistmax(1L, l36)) : 0.0);
                DOUBLE_TYPE l35 = (agg12 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER5_map_0* i26 = static_cast<HashIndex_NUMCUSTCUSTOMER5_map_0*>(NUMCUSTCUSTOMER5.index[1]);
                  const HASH_RES_t h12 = NUMCUSTCUSTOMER5_mapkey0_idxfn::hash(se34.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER5_map_0::IdxNode* n26 = static_cast<HashIndex_NUMCUSTCUSTOMER5_map_0::IdxNode*>(i26->slice(se34, h12));
                  NUMCUSTCUSTOMER5_entry* e26;
                 
                  if (n26 && (e26 = n26->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e26->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e26->CUSTSALE_CNTRYCODE;
                      long v26 = e26->__av;
                      (/*if */(l34 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se33.modify(c_custkey)) && c_acctbal > l35) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),(((v25 != 0 ? 1L : 0L) * v26) * -1L)) : (void)0);
                      n26 = n26->nxt;
                    } while (n26 && (e26 = n26->obj) && h12 == n26->hash &&  NUMCUSTCUSTOMER5_mapkey0_idxfn::equals(se34, *e26)); 
                  }
                }
              n25 = n25->nxt;
            }
          }
        }long l37 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i27 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n27; 
          NUMCUSTORDERS1_DOMAIN1_entry* e27;
        
          for (size_t i = 0; i < i27->size_; i++)
          {
            n27 = i27->buckets_ + i;
            while (n27 && (e27 = n27->obj))
            {
                long c_custkey = e27->C_CUSTKEY;
                long v27 = e27->__av;
                DOUBLE_TYPE agg13 = 0.0;
                long l39 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l39) ? agg13 += Udiv(Ulistmax(1L, l39)) : 0.0);
                DOUBLE_TYPE l38 = (agg13 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER6_map_0* i28 = static_cast<HashIndex_NUMCUSTCUSTOMER6_map_0*>(NUMCUSTCUSTOMER6.index[1]);
                  const HASH_RES_t h13 = NUMCUSTCUSTOMER6_mapkey0_idxfn::hash(se36.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER6_map_0::IdxNode* n28 = static_cast<HashIndex_NUMCUSTCUSTOMER6_map_0::IdxNode*>(i28->slice(se36, h13));
                  NUMCUSTCUSTOMER6_entry* e28;
                 
                  if (n28 && (e28 = n28->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e28->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e28->CUSTSALE_CNTRYCODE;
                      long v28 = e28->__av;
                      (/*if */(l37 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se35.modify(c_custkey)) && c_acctbal > l38) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),(((v27 != 0 ? 1L : 0L) * v28) * -1L)) : (void)0);
                      n28 = n28->nxt;
                    } while (n28 && (e28 = n28->obj) && h13 == n28->hash &&  NUMCUSTCUSTOMER6_mapkey0_idxfn::equals(se36, *e28)); 
                  }
                }
              n27 = n27->nxt;
            }
          }
        }long l40 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i29 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n29; 
          NUMCUSTORDERS1_DOMAIN1_entry* e29;
        
          for (size_t i = 0; i < i29->size_; i++)
          {
            n29 = i29->buckets_ + i;
            while (n29 && (e29 = n29->obj))
            {
                long c_custkey = e29->C_CUSTKEY;
                long v29 = e29->__av;
                DOUBLE_TYPE agg14 = 0.0;
                long l42 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l42) ? agg14 += Udiv(Ulistmax(1L, l42)) : 0.0);
                DOUBLE_TYPE l41 = (agg14 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER7_map_0* i30 = static_cast<HashIndex_NUMCUSTCUSTOMER7_map_0*>(NUMCUSTCUSTOMER7.index[1]);
                  const HASH_RES_t h14 = NUMCUSTCUSTOMER7_mapkey0_idxfn::hash(se38.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER7_map_0::IdxNode* n30 = static_cast<HashIndex_NUMCUSTCUSTOMER7_map_0::IdxNode*>(i30->slice(se38, h14));
                  NUMCUSTCUSTOMER7_entry* e30;
                 
                  if (n30 && (e30 = n30->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e30->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e30->CUSTSALE_CNTRYCODE;
                      long v30 = e30->__av;
                      (/*if */(l40 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se37.modify(c_custkey)) && c_acctbal > l41) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),(((v29 != 0 ? 1L : 0L) * v30) * -1L)) : (void)0);
                      n30 = n30->nxt;
                    } while (n30 && (e30 = n30->obj) && h14 == n30->hash &&  NUMCUSTCUSTOMER7_mapkey0_idxfn::equals(se38, *e30)); 
                  }
                }
              n29 = n29->nxt;
            }
          }
        }long l43 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i31 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n31; 
          NUMCUSTORDERS1_DOMAIN1_entry* e31;
        
          for (size_t i = 0; i < i31->size_; i++)
          {
            n31 = i31->buckets_ + i;
            while (n31 && (e31 = n31->obj))
            {
                long c_custkey = e31->C_CUSTKEY;
                long v31 = e31->__av;
                DOUBLE_TYPE agg15 = 0.0;
                long l45 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l45) ? agg15 += Udiv(Ulistmax(1L, l45)) : 0.0);
                DOUBLE_TYPE l44 = (agg15 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER1_map_0* i32 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_0*>(TOTALACCTBALCUSTOMER1.index[1]);
                  const HASH_RES_t h15 = TOTALACCTBALCUSTOMER1_mapkey0_idxfn::hash(se42.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER1_map_0::IdxNode* n32 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_0::IdxNode*>(i32->slice(se42, h15));
                  TOTALACCTBALCUSTOMER1_entry* e32;
                 
                  if (n32 && (e32 = n32->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e32->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e32->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v32 = e32->__av;
                      (/*if */(l43 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se40.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se41.modify(c_custkey))) && c_acctbal > l44) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),((v31 != 0 ? 1L : 0L) * v32)) : (void)0);
                      n32 = n32->nxt;
                    } while (n32 && (e32 = n32->obj) && h15 == n32->hash &&  TOTALACCTBALCUSTOMER1_mapkey0_idxfn::equals(se42, *e32)); 
                  }
                }
              n31 = n31->nxt;
            }
          }
        }long l46 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i33 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n33; 
          NUMCUSTORDERS1_DOMAIN1_entry* e33;
        
          for (size_t i = 0; i < i33->size_; i++)
          {
            n33 = i33->buckets_ + i;
            while (n33 && (e33 = n33->obj))
            {
                long c_custkey = e33->C_CUSTKEY;
                long v33 = e33->__av;
                DOUBLE_TYPE agg16 = 0.0;
                long l48 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l48) ? agg16 += Udiv(Ulistmax(1L, l48)) : 0.0);
                DOUBLE_TYPE l47 = (agg16 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER2_map_0* i34 = static_cast<HashIndex_TOTALACCTBALCUSTOMER2_map_0*>(TOTALACCTBALCUSTOMER2.index[1]);
                  const HASH_RES_t h16 = TOTALACCTBALCUSTOMER2_mapkey0_idxfn::hash(se45.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER2_map_0::IdxNode* n34 = static_cast<HashIndex_TOTALACCTBALCUSTOMER2_map_0::IdxNode*>(i34->slice(se45, h16));
                  TOTALACCTBALCUSTOMER2_entry* e34;
                 
                  if (n34 && (e34 = n34->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e34->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e34->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v34 = e34->__av;
                      (/*if */(l46 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se43.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se44.modify(c_custkey))) && c_acctbal > l47) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),((v33 != 0 ? 1L : 0L) * v34)) : (void)0);
                      n34 = n34->nxt;
                    } while (n34 && (e34 = n34->obj) && h16 == n34->hash &&  TOTALACCTBALCUSTOMER2_mapkey0_idxfn::equals(se45, *e34)); 
                  }
                }
              n33 = n33->nxt;
            }
          }
        }long l49 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i35 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n35; 
          NUMCUSTORDERS1_DOMAIN1_entry* e35;
        
          for (size_t i = 0; i < i35->size_; i++)
          {
            n35 = i35->buckets_ + i;
            while (n35 && (e35 = n35->obj))
            {
                long c_custkey = e35->C_CUSTKEY;
                long v35 = e35->__av;
                DOUBLE_TYPE agg17 = 0.0;
                long l51 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l51) ? agg17 += Udiv(Ulistmax(1L, l51)) : 0.0);
                DOUBLE_TYPE l50 = (agg17 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER3_map_0* i36 = static_cast<HashIndex_TOTALACCTBALCUSTOMER3_map_0*>(TOTALACCTBALCUSTOMER3.index[1]);
                  const HASH_RES_t h17 = TOTALACCTBALCUSTOMER3_mapkey0_idxfn::hash(se48.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER3_map_0::IdxNode* n36 = static_cast<HashIndex_TOTALACCTBALCUSTOMER3_map_0::IdxNode*>(i36->slice(se48, h17));
                  TOTALACCTBALCUSTOMER3_entry* e36;
                 
                  if (n36 && (e36 = n36->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e36->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e36->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v36 = e36->__av;
                      (/*if */(l49 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se46.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se47.modify(c_custkey))) && c_acctbal > l50) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),((v35 != 0 ? 1L : 0L) * v36)) : (void)0);
                      n36 = n36->nxt;
                    } while (n36 && (e36 = n36->obj) && h17 == n36->hash &&  TOTALACCTBALCUSTOMER3_mapkey0_idxfn::equals(se48, *e36)); 
                  }
                }
              n35 = n35->nxt;
            }
          }
        }long l52 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i37 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n37; 
          NUMCUSTORDERS1_DOMAIN1_entry* e37;
        
          for (size_t i = 0; i < i37->size_; i++)
          {
            n37 = i37->buckets_ + i;
            while (n37 && (e37 = n37->obj))
            {
                long c_custkey = e37->C_CUSTKEY;
                long v37 = e37->__av;
                DOUBLE_TYPE agg18 = 0.0;
                long l54 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l54) ? agg18 += Udiv(Ulistmax(1L, l54)) : 0.0);
                DOUBLE_TYPE l53 = (agg18 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER4_map_0* i38 = static_cast<HashIndex_TOTALACCTBALCUSTOMER4_map_0*>(TOTALACCTBALCUSTOMER4.index[1]);
                  const HASH_RES_t h18 = TOTALACCTBALCUSTOMER4_mapkey0_idxfn::hash(se51.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER4_map_0::IdxNode* n38 = static_cast<HashIndex_TOTALACCTBALCUSTOMER4_map_0::IdxNode*>(i38->slice(se51, h18));
                  TOTALACCTBALCUSTOMER4_entry* e38;
                 
                  if (n38 && (e38 = n38->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e38->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e38->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v38 = e38->__av;
                      (/*if */(l52 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se49.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se50.modify(c_custkey))) && c_acctbal > l53) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),((v37 != 0 ? 1L : 0L) * v38)) : (void)0);
                      n38 = n38->nxt;
                    } while (n38 && (e38 = n38->obj) && h18 == n38->hash &&  TOTALACCTBALCUSTOMER4_mapkey0_idxfn::equals(se51, *e38)); 
                  }
                }
              n37 = n37->nxt;
            }
          }
        }long l55 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i39 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n39; 
          NUMCUSTORDERS1_DOMAIN1_entry* e39;
        
          for (size_t i = 0; i < i39->size_; i++)
          {
            n39 = i39->buckets_ + i;
            while (n39 && (e39 = n39->obj))
            {
                long c_custkey = e39->C_CUSTKEY;
                long v39 = e39->__av;
                DOUBLE_TYPE agg19 = 0.0;
                long l57 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l57) ? agg19 += Udiv(Ulistmax(1L, l57)) : 0.0);
                DOUBLE_TYPE l56 = (agg19 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER5_map_0* i40 = static_cast<HashIndex_TOTALACCTBALCUSTOMER5_map_0*>(TOTALACCTBALCUSTOMER5.index[1]);
                  const HASH_RES_t h19 = TOTALACCTBALCUSTOMER5_mapkey0_idxfn::hash(se54.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER5_map_0::IdxNode* n40 = static_cast<HashIndex_TOTALACCTBALCUSTOMER5_map_0::IdxNode*>(i40->slice(se54, h19));
                  TOTALACCTBALCUSTOMER5_entry* e40;
                 
                  if (n40 && (e40 = n40->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e40->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e40->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v40 = e40->__av;
                      (/*if */(l55 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se52.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se53.modify(c_custkey))) && c_acctbal > l56) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),((v39 != 0 ? 1L : 0L) * v40)) : (void)0);
                      n40 = n40->nxt;
                    } while (n40 && (e40 = n40->obj) && h19 == n40->hash &&  TOTALACCTBALCUSTOMER5_mapkey0_idxfn::equals(se54, *e40)); 
                  }
                }
              n39 = n39->nxt;
            }
          }
        }long l58 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i41 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n41; 
          NUMCUSTORDERS1_DOMAIN1_entry* e41;
        
          for (size_t i = 0; i < i41->size_; i++)
          {
            n41 = i41->buckets_ + i;
            while (n41 && (e41 = n41->obj))
            {
                long c_custkey = e41->C_CUSTKEY;
                long v41 = e41->__av;
                DOUBLE_TYPE agg20 = 0.0;
                long l60 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l60) ? agg20 += Udiv(Ulistmax(1L, l60)) : 0.0);
                DOUBLE_TYPE l59 = (agg20 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER6_map_0* i42 = static_cast<HashIndex_TOTALACCTBALCUSTOMER6_map_0*>(TOTALACCTBALCUSTOMER6.index[1]);
                  const HASH_RES_t h20 = TOTALACCTBALCUSTOMER6_mapkey0_idxfn::hash(se57.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER6_map_0::IdxNode* n42 = static_cast<HashIndex_TOTALACCTBALCUSTOMER6_map_0::IdxNode*>(i42->slice(se57, h20));
                  TOTALACCTBALCUSTOMER6_entry* e42;
                 
                  if (n42 && (e42 = n42->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e42->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e42->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v42 = e42->__av;
                      (/*if */(l58 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se55.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se56.modify(c_custkey))) && c_acctbal > l59) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),((v41 != 0 ? 1L : 0L) * v42)) : (void)0);
                      n42 = n42->nxt;
                    } while (n42 && (e42 = n42->obj) && h20 == n42->hash &&  TOTALACCTBALCUSTOMER6_mapkey0_idxfn::equals(se57, *e42)); 
                  }
                }
              n41 = n41->nxt;
            }
          }
        }long l61 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i43 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n43; 
          NUMCUSTORDERS1_DOMAIN1_entry* e43;
        
          for (size_t i = 0; i < i43->size_; i++)
          {
            n43 = i43->buckets_ + i;
            while (n43 && (e43 = n43->obj))
            {
                long c_custkey = e43->C_CUSTKEY;
                long v43 = e43->__av;
                DOUBLE_TYPE agg21 = 0.0;
                long l63 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l63) ? agg21 += Udiv(Ulistmax(1L, l63)) : 0.0);
                DOUBLE_TYPE l62 = (agg21 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER7_map_0* i44 = static_cast<HashIndex_TOTALACCTBALCUSTOMER7_map_0*>(TOTALACCTBALCUSTOMER7.index[1]);
                  const HASH_RES_t h21 = TOTALACCTBALCUSTOMER7_mapkey0_idxfn::hash(se60.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER7_map_0::IdxNode* n44 = static_cast<HashIndex_TOTALACCTBALCUSTOMER7_map_0::IdxNode*>(i44->slice(se60, h21));
                  TOTALACCTBALCUSTOMER7_entry* e44;
                 
                  if (n44 && (e44 = n44->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e44->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e44->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v44 = e44->__av;
                      (/*if */(l61 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se58.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se59.modify(c_custkey))) && c_acctbal > l62) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),((v43 != 0 ? 1L : 0L) * v44)) : (void)0);
                      n44 = n44->nxt;
                    } while (n44 && (e44 = n44->obj) && h21 == n44->hash &&  TOTALACCTBALCUSTOMER7_mapkey0_idxfn::equals(se60, *e44)); 
                  }
                }
              n43 = n43->nxt;
            }
          }
        }long l64 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i45 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n45; 
          NUMCUSTORDERS1_DOMAIN1_entry* e45;
        
          for (size_t i = 0; i < i45->size_; i++)
          {
            n45 = i45->buckets_ + i;
            while (n45 && (e45 = n45->obj))
            {
                long c_custkey = e45->C_CUSTKEY;
                long v45 = e45->__av;
                DOUBLE_TYPE agg22 = 0.0;
                long l66 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l66) ? agg22 += Udiv(Ulistmax(1L, l66)) : 0.0);
                DOUBLE_TYPE l65 = (agg22 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER1_map_0* i46 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_0*>(TOTALACCTBALCUSTOMER1.index[1]);
                  const HASH_RES_t h22 = TOTALACCTBALCUSTOMER1_mapkey0_idxfn::hash(se62.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER1_map_0::IdxNode* n46 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_0::IdxNode*>(i46->slice(se62, h22));
                  TOTALACCTBALCUSTOMER1_entry* e46;
                 
                  if (n46 && (e46 = n46->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e46->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e46->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v46 = e46->__av;
                      (/*if */(l64 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se61.modify(c_custkey)) && c_acctbal > l65) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),(((v45 != 0 ? 1L : 0L) * v46) * -1L)) : (void)0);
                      n46 = n46->nxt;
                    } while (n46 && (e46 = n46->obj) && h22 == n46->hash &&  TOTALACCTBALCUSTOMER1_mapkey0_idxfn::equals(se62, *e46)); 
                  }
                }
              n45 = n45->nxt;
            }
          }
        }long l67 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i47 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n47; 
          NUMCUSTORDERS1_DOMAIN1_entry* e47;
        
          for (size_t i = 0; i < i47->size_; i++)
          {
            n47 = i47->buckets_ + i;
            while (n47 && (e47 = n47->obj))
            {
                long c_custkey = e47->C_CUSTKEY;
                long v47 = e47->__av;
                DOUBLE_TYPE agg23 = 0.0;
                long l69 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l69) ? agg23 += Udiv(Ulistmax(1L, l69)) : 0.0);
                DOUBLE_TYPE l68 = (agg23 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER2_map_0* i48 = static_cast<HashIndex_TOTALACCTBALCUSTOMER2_map_0*>(TOTALACCTBALCUSTOMER2.index[1]);
                  const HASH_RES_t h23 = TOTALACCTBALCUSTOMER2_mapkey0_idxfn::hash(se64.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER2_map_0::IdxNode* n48 = static_cast<HashIndex_TOTALACCTBALCUSTOMER2_map_0::IdxNode*>(i48->slice(se64, h23));
                  TOTALACCTBALCUSTOMER2_entry* e48;
                 
                  if (n48 && (e48 = n48->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e48->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e48->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v48 = e48->__av;
                      (/*if */(l67 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se63.modify(c_custkey)) && c_acctbal > l68) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),(((v47 != 0 ? 1L : 0L) * v48) * -1L)) : (void)0);
                      n48 = n48->nxt;
                    } while (n48 && (e48 = n48->obj) && h23 == n48->hash &&  TOTALACCTBALCUSTOMER2_mapkey0_idxfn::equals(se64, *e48)); 
                  }
                }
              n47 = n47->nxt;
            }
          }
        }long l70 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i49 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n49; 
          NUMCUSTORDERS1_DOMAIN1_entry* e49;
        
          for (size_t i = 0; i < i49->size_; i++)
          {
            n49 = i49->buckets_ + i;
            while (n49 && (e49 = n49->obj))
            {
                long c_custkey = e49->C_CUSTKEY;
                long v49 = e49->__av;
                DOUBLE_TYPE agg24 = 0.0;
                long l72 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l72) ? agg24 += Udiv(Ulistmax(1L, l72)) : 0.0);
                DOUBLE_TYPE l71 = (agg24 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER3_map_0* i50 = static_cast<HashIndex_TOTALACCTBALCUSTOMER3_map_0*>(TOTALACCTBALCUSTOMER3.index[1]);
                  const HASH_RES_t h24 = TOTALACCTBALCUSTOMER3_mapkey0_idxfn::hash(se66.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER3_map_0::IdxNode* n50 = static_cast<HashIndex_TOTALACCTBALCUSTOMER3_map_0::IdxNode*>(i50->slice(se66, h24));
                  TOTALACCTBALCUSTOMER3_entry* e50;
                 
                  if (n50 && (e50 = n50->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e50->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e50->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v50 = e50->__av;
                      (/*if */(l70 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se65.modify(c_custkey)) && c_acctbal > l71) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),(((v49 != 0 ? 1L : 0L) * v50) * -1L)) : (void)0);
                      n50 = n50->nxt;
                    } while (n50 && (e50 = n50->obj) && h24 == n50->hash &&  TOTALACCTBALCUSTOMER3_mapkey0_idxfn::equals(se66, *e50)); 
                  }
                }
              n49 = n49->nxt;
            }
          }
        }long l73 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i51 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n51; 
          NUMCUSTORDERS1_DOMAIN1_entry* e51;
        
          for (size_t i = 0; i < i51->size_; i++)
          {
            n51 = i51->buckets_ + i;
            while (n51 && (e51 = n51->obj))
            {
                long c_custkey = e51->C_CUSTKEY;
                long v51 = e51->__av;
                DOUBLE_TYPE agg25 = 0.0;
                long l75 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l75) ? agg25 += Udiv(Ulistmax(1L, l75)) : 0.0);
                DOUBLE_TYPE l74 = (agg25 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER4_map_0* i52 = static_cast<HashIndex_TOTALACCTBALCUSTOMER4_map_0*>(TOTALACCTBALCUSTOMER4.index[1]);
                  const HASH_RES_t h25 = TOTALACCTBALCUSTOMER4_mapkey0_idxfn::hash(se68.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER4_map_0::IdxNode* n52 = static_cast<HashIndex_TOTALACCTBALCUSTOMER4_map_0::IdxNode*>(i52->slice(se68, h25));
                  TOTALACCTBALCUSTOMER4_entry* e52;
                 
                  if (n52 && (e52 = n52->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e52->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e52->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v52 = e52->__av;
                      (/*if */(l73 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se67.modify(c_custkey)) && c_acctbal > l74) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),(((v51 != 0 ? 1L : 0L) * v52) * -1L)) : (void)0);
                      n52 = n52->nxt;
                    } while (n52 && (e52 = n52->obj) && h25 == n52->hash &&  TOTALACCTBALCUSTOMER4_mapkey0_idxfn::equals(se68, *e52)); 
                  }
                }
              n51 = n51->nxt;
            }
          }
        }long l76 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i53 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n53; 
          NUMCUSTORDERS1_DOMAIN1_entry* e53;
        
          for (size_t i = 0; i < i53->size_; i++)
          {
            n53 = i53->buckets_ + i;
            while (n53 && (e53 = n53->obj))
            {
                long c_custkey = e53->C_CUSTKEY;
                long v53 = e53->__av;
                DOUBLE_TYPE agg26 = 0.0;
                long l78 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l78) ? agg26 += Udiv(Ulistmax(1L, l78)) : 0.0);
                DOUBLE_TYPE l77 = (agg26 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER5_map_0* i54 = static_cast<HashIndex_TOTALACCTBALCUSTOMER5_map_0*>(TOTALACCTBALCUSTOMER5.index[1]);
                  const HASH_RES_t h26 = TOTALACCTBALCUSTOMER5_mapkey0_idxfn::hash(se70.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER5_map_0::IdxNode* n54 = static_cast<HashIndex_TOTALACCTBALCUSTOMER5_map_0::IdxNode*>(i54->slice(se70, h26));
                  TOTALACCTBALCUSTOMER5_entry* e54;
                 
                  if (n54 && (e54 = n54->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e54->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e54->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v54 = e54->__av;
                      (/*if */(l76 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se69.modify(c_custkey)) && c_acctbal > l77) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),(((v53 != 0 ? 1L : 0L) * v54) * -1L)) : (void)0);
                      n54 = n54->nxt;
                    } while (n54 && (e54 = n54->obj) && h26 == n54->hash &&  TOTALACCTBALCUSTOMER5_mapkey0_idxfn::equals(se70, *e54)); 
                  }
                }
              n53 = n53->nxt;
            }
          }
        }long l79 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i55 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n55; 
          NUMCUSTORDERS1_DOMAIN1_entry* e55;
        
          for (size_t i = 0; i < i55->size_; i++)
          {
            n55 = i55->buckets_ + i;
            while (n55 && (e55 = n55->obj))
            {
                long c_custkey = e55->C_CUSTKEY;
                long v55 = e55->__av;
                DOUBLE_TYPE agg27 = 0.0;
                long l81 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l81) ? agg27 += Udiv(Ulistmax(1L, l81)) : 0.0);
                DOUBLE_TYPE l80 = (agg27 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER6_map_0* i56 = static_cast<HashIndex_TOTALACCTBALCUSTOMER6_map_0*>(TOTALACCTBALCUSTOMER6.index[1]);
                  const HASH_RES_t h27 = TOTALACCTBALCUSTOMER6_mapkey0_idxfn::hash(se72.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER6_map_0::IdxNode* n56 = static_cast<HashIndex_TOTALACCTBALCUSTOMER6_map_0::IdxNode*>(i56->slice(se72, h27));
                  TOTALACCTBALCUSTOMER6_entry* e56;
                 
                  if (n56 && (e56 = n56->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e56->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e56->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v56 = e56->__av;
                      (/*if */(l79 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se71.modify(c_custkey)) && c_acctbal > l80) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),(((v55 != 0 ? 1L : 0L) * v56) * -1L)) : (void)0);
                      n56 = n56->nxt;
                    } while (n56 && (e56 = n56->obj) && h27 == n56->hash &&  TOTALACCTBALCUSTOMER6_mapkey0_idxfn::equals(se72, *e56)); 
                  }
                }
              n55 = n55->nxt;
            }
          }
        }long l82 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0* i57 = static_cast<HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0*>(NUMCUSTORDERS1_DOMAIN1.index[0]);
          HashIndex_NUMCUSTORDERS1_DOMAIN1_map_0::IdxNode* n57; 
          NUMCUSTORDERS1_DOMAIN1_entry* e57;
        
          for (size_t i = 0; i < i57->size_; i++)
          {
            n57 = i57->buckets_ + i;
            while (n57 && (e57 = n57->obj))
            {
                long c_custkey = e57->C_CUSTKEY;
                long v57 = e57->__av;
                DOUBLE_TYPE agg28 = 0.0;
                long l84 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
                (/*if */(0L != l84) ? agg28 += Udiv(Ulistmax(1L, l84)) : 0.0);
                DOUBLE_TYPE l83 = (agg28 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER7_map_0* i58 = static_cast<HashIndex_TOTALACCTBALCUSTOMER7_map_0*>(TOTALACCTBALCUSTOMER7.index[1]);
                  const HASH_RES_t h28 = TOTALACCTBALCUSTOMER7_mapkey0_idxfn::hash(se74.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER7_map_0::IdxNode* n58 = static_cast<HashIndex_TOTALACCTBALCUSTOMER7_map_0::IdxNode*>(i58->slice(se74, h28));
                  TOTALACCTBALCUSTOMER7_entry* e58;
                 
                  if (n58 && (e58 = n58->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e58->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e58->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v58 = e58->__av;
                      (/*if */(l82 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se73.modify(c_custkey)) && c_acctbal > l83) ? TOTALACCTBAL.addOrDelOnZero(se39.modify(custsale_cntrycode),(((v57 != 0 ? 1L : 0L) * v58) * -1L)) : (void)0);
                      n58 = n58->nxt;
                    } while (n58 && (e58 = n58->obj) && h28 == n58->hash &&  TOTALACCTBALCUSTOMER7_mapkey0_idxfn::equals(se74, *e58)); 
                  }
                }
              n57 = n57->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMCUSTORDERS1_L2_2_DELTA_map_0* i59 = static_cast<HashIndex_NUMCUSTORDERS1_L2_2_DELTA_map_0*>(NUMCUSTORDERS1_L2_2_DELTA.index[0]);
          HashIndex_NUMCUSTORDERS1_L2_2_DELTA_map_0::IdxNode* n59; 
          NUMCUSTORDERS1_L2_2_DELTA_entry* e59;
        
          for (size_t i = 0; i < i59->size_; i++)
          {
            n59 = i59->buckets_ + i;
            while (n59 && (e59 = n59->obj))
            {
                long c_custkey = e59->C_CUSTKEY;
                long v59 = e59->__av;
                NUMCUSTCUSTOMER1_L3_1.addOrDelOnZero(se75.modify(c_custkey),v59);
              n59 = n59->nxt;
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


        NUMCUSTCUSTOMER1CUSTOMER1_DELTA.clear();
        long agg29 = 0L;
        long agg30 = 0L;
        long agg31 = 0L;
        long agg32 = 0L;
        long agg33 = 0L;
        long agg34 = 0L;
        long agg35 = 0L;
        DOUBLE_TYPE agg36 = 0.0;
        DOUBLE_TYPE agg37 = 0.0;
        DOUBLE_TYPE agg38 = 0.0;
        DOUBLE_TYPE agg39 = 0.0;
        DOUBLE_TYPE agg40 = 0.0;                
        DOUBLE_TYPE agg41 = 0.0;
        DOUBLE_TYPE agg42 = 0.0;
        NUMCUSTCUSTOMER2CUSTOMER1_DELTA.clear();    
        NUMCUSTCUSTOMER3CUSTOMER1_DELTA.clear();
        NUMCUSTCUSTOMER4CUSTOMER1_DELTA.clear();
        NUMCUSTCUSTOMER5CUSTOMER1_DELTA.clear();
        NUMCUSTCUSTOMER6CUSTOMER1_DELTA.clear();
        NUMCUSTCUSTOMER7CUSTOMER1_DELTA.clear();
        TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA.clear();
        TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA.clear();
        TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA.clear();
        TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA.clear();
        TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA.clear();
        TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA.clear();
        TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA.clear();

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
                long v60 = 1L;
                STRING_TYPE l85 = Usubstring(c_phone, 0L, 2L);
                (/*if */(c1 == l85) ? NUMCUSTCUSTOMER1CUSTOMER1_DELTA.addOrDelOnZero(se76.modify(c_custkey,c_acctbal,l85),v60) : (void)0);            
                long v61 = 1L;
                (/*if */(c_acctbal > 0.0 && c1 == l85) ? agg29 += v61 : 0L);
                long v62 = 1L;
                (/*if */(c_acctbal > 0.0 && c2 == l85) ? agg30 += v62 : 0L);
                long v63 = 1L;
                (/*if */(c_acctbal > 0.0 && c3 == l85) ? agg31 += v63 : 0L);
                long v64 = 1L;
                (/*if */(c_acctbal > 0.0 && c4 == l85) ? agg32 += v64 : 0L);
                long v65 = 1L;
                (/*if */(c_acctbal > 0.0 && c5 == l85) ? agg33 += v65 : 0L);
                long v66 = 1L;
                (/*if */(c_acctbal > 0.0 && c6 == l85) ? agg34 += v66 : 0L);
                long v67 = 1L;
                (/*if */(c_acctbal > 0.0 && c7 == l85) ? agg35 += v67 : 0L);
                long v68 = 1L;
                (/*if */(c_acctbal > 0.0 && c1 == l85) ? agg36 += (v68 * c_acctbal) : 0.0);
                long v69 = 1L;
                (/*if */(c_acctbal > 0.0 && c2 == l85) ? agg37 += (v69 * c_acctbal) : 0.0);
                long v70 = 1L;
                (/*if */(c_acctbal > 0.0 && c3 == l85) ? agg38 += (v70 * c_acctbal) : 0.0);
                long v71 = 1L;
                (/*if */(c_acctbal > 0.0 && c4 == l85) ? agg39 += (v71 * c_acctbal) : 0.0);
                long v72 = 1L;
                (/*if */(c_acctbal > 0.0 && c5 == l85) ? agg40 += (v72 * c_acctbal) : 0.0);
                long v73 = 1L;
                (/*if */(c_acctbal > 0.0 && c6 == l85) ? agg41 += (v73 * c_acctbal) : 0.0);
                long v74 = 1L;
                (/*if */(c_acctbal > 0.0 && c7 == l85) ? agg42 += (v74 * c_acctbal) : 0.0);
                long v75 = 1L;
                (/*if */(c2 == l85) ? NUMCUSTCUSTOMER2CUSTOMER1_DELTA.addOrDelOnZero(se91.modify(c_custkey,c_acctbal,l85),v75) : (void)0);
                long v76 = 1L;
                (/*if */(c3 == l85) ? NUMCUSTCUSTOMER3CUSTOMER1_DELTA.addOrDelOnZero(se92.modify(c_custkey,c_acctbal,l85),v76) : (void)0);
                long v77 = 1L;
                (/*if */(c4 == l85) ? NUMCUSTCUSTOMER4CUSTOMER1_DELTA.addOrDelOnZero(se93.modify(c_custkey,c_acctbal,l85),v77) : (void)0);
                long v78 = 1L;
                (/*if */(c5 == l85) ? NUMCUSTCUSTOMER5CUSTOMER1_DELTA.addOrDelOnZero(se94.modify(c_custkey,c_acctbal,l85),v78) : (void)0);
                long v79 = 1L;
                (/*if */(c6 == l85) ? NUMCUSTCUSTOMER6CUSTOMER1_DELTA.addOrDelOnZero(se95.modify(c_custkey,c_acctbal,l85),v79) : (void)0);
                long v80 = 1L;
                (/*if */(c7 == l85) ? NUMCUSTCUSTOMER7CUSTOMER1_DELTA.addOrDelOnZero(se96.modify(c_custkey,c_acctbal,l85),v80) : (void)0);
                long v81 = 1L;
                (/*if */(c1 == l85) ? TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA.addOrDelOnZero(se97.modify(c_custkey,c_acctbal,l85),(v81 * c_acctbal)) : (void)0);
                long v82 = 1L;
                (/*if */(c2 == l85) ? TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA.addOrDelOnZero(se98.modify(c_custkey,c_acctbal,l85),(v82 * c_acctbal)) : (void)0);
                long v83 = 1L;
                (/*if */(c3 == l85) ? TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA.addOrDelOnZero(se99.modify(c_custkey,c_acctbal,l85),(v83 * c_acctbal)) : (void)0);
                long v84 = 1L;
                (/*if */(c4 == l85) ? TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA.addOrDelOnZero(se100.modify(c_custkey,c_acctbal,l85),(v84 * c_acctbal)) : (void)0);
                long v85 = 1L;
                (/*if */(c5 == l85) ? TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA.addOrDelOnZero(se101.modify(c_custkey,c_acctbal,l85),(v85 * c_acctbal)) : (void)0);
                long v86 = 1L;
                (/*if */(c6 == l85) ? TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA.addOrDelOnZero(se102.modify(c_custkey,c_acctbal,l85),(v86 * c_acctbal)) : (void)0);
                long v87 = 1L;
                (/*if */(c7 == l85) ? TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA.addOrDelOnZero(se103.modify(c_custkey,c_acctbal,l85),(v87 * c_acctbal)) : (void)0);
          }
        }
        
        NUMCUSTCUSTOMER1_L2_1_L1_1CUSTOMER1_DELTA = agg29;
        NUMCUSTCUSTOMER1_L2_1_L1_2CUSTOMER1_DELTA = agg30;
        NUMCUSTCUSTOMER1_L2_1_L1_3CUSTOMER1_DELTA = agg31;
        NUMCUSTCUSTOMER1_L2_1_L1_4CUSTOMER1_DELTA = agg32;
        NUMCUSTCUSTOMER1_L2_1_L1_5CUSTOMER1_DELTA = agg33;
        NUMCUSTCUSTOMER1_L2_1_L1_6CUSTOMER1_DELTA = agg34;
        NUMCUSTCUSTOMER1_L2_1_L1_7CUSTOMER1_DELTA = agg35;
        NUMCUSTCUSTOMER1_L2_2CUSTOMER1_DELTA = agg36;
        NUMCUSTCUSTOMER1_L2_4CUSTOMER1_DELTA = agg37;
        NUMCUSTCUSTOMER1_L2_6CUSTOMER1_DELTA = agg38;
        NUMCUSTCUSTOMER1_L2_8CUSTOMER1_DELTA = agg39;
        NUMCUSTCUSTOMER1_L2_10CUSTOMER1_DELTA = agg40;
        NUMCUSTCUSTOMER1_L2_12CUSTOMER1_DELTA = agg41;
        NUMCUSTCUSTOMER1_L2_14CUSTOMER1_DELTA = agg42;

        {  // foreach
          const HashIndex_NUMCUSTCUSTOMER1CUSTOMER1_DELTA_map_012* i88 = static_cast<HashIndex_NUMCUSTCUSTOMER1CUSTOMER1_DELTA_map_012*>(NUMCUSTCUSTOMER1CUSTOMER1_DELTA.index[0]);
          HashIndex_NUMCUSTCUSTOMER1CUSTOMER1_DELTA_map_012::IdxNode* n88; 
          NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry* e88;
        
          for (size_t i = 0; i < i88->size_; i++)
          {
            n88 = i88->buckets_ + i;
            while (n88 && (e88 = n88->obj))
            {
                long c_custkey = e88->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e88->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e88->CUSTSALE_CNTRYCODE;
                long v88 = e88->__av;
                NUMCUSTCUSTOMER1.addOrDelOnZero(se104.modify(c_custkey,c_acctbal,custsale_cntrycode),v88);
              n88 = n88->nxt;
            }
          }
        }NUMCUSTCUSTOMER1_L2_1_L1_1 += NUMCUSTCUSTOMER1_L2_1_L1_1CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_1_L1_2 += NUMCUSTCUSTOMER1_L2_1_L1_2CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_1_L1_3 += NUMCUSTCUSTOMER1_L2_1_L1_3CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_1_L1_4 += NUMCUSTCUSTOMER1_L2_1_L1_4CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_1_L1_5 += NUMCUSTCUSTOMER1_L2_1_L1_5CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_1_L1_6 += NUMCUSTCUSTOMER1_L2_1_L1_6CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_1_L1_7 += NUMCUSTCUSTOMER1_L2_1_L1_7CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_2 += NUMCUSTCUSTOMER1_L2_2CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_4 += NUMCUSTCUSTOMER1_L2_4CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_6 += NUMCUSTCUSTOMER1_L2_6CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_8 += NUMCUSTCUSTOMER1_L2_8CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_10 += NUMCUSTCUSTOMER1_L2_10CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_12 += NUMCUSTCUSTOMER1_L2_12CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_14 += NUMCUSTCUSTOMER1_L2_14CUSTOMER1_DELTA;
        {  // foreach
          const HashIndex_NUMCUSTCUSTOMER2CUSTOMER1_DELTA_map_012* i89 = static_cast<HashIndex_NUMCUSTCUSTOMER2CUSTOMER1_DELTA_map_012*>(NUMCUSTCUSTOMER2CUSTOMER1_DELTA.index[0]);
          HashIndex_NUMCUSTCUSTOMER2CUSTOMER1_DELTA_map_012::IdxNode* n89; 
          NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry* e89;
        
          for (size_t i = 0; i < i89->size_; i++)
          {
            n89 = i89->buckets_ + i;
            while (n89 && (e89 = n89->obj))
            {
                long c_custkey = e89->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e89->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e89->CUSTSALE_CNTRYCODE;
                long v89 = e89->__av;
                NUMCUSTCUSTOMER2.addOrDelOnZero(se119.modify(c_custkey,c_acctbal,custsale_cntrycode),v89);
              n89 = n89->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMCUSTCUSTOMER3CUSTOMER1_DELTA_map_012* i90 = static_cast<HashIndex_NUMCUSTCUSTOMER3CUSTOMER1_DELTA_map_012*>(NUMCUSTCUSTOMER3CUSTOMER1_DELTA.index[0]);
          HashIndex_NUMCUSTCUSTOMER3CUSTOMER1_DELTA_map_012::IdxNode* n90; 
          NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry* e90;
        
          for (size_t i = 0; i < i90->size_; i++)
          {
            n90 = i90->buckets_ + i;
            while (n90 && (e90 = n90->obj))
            {
                long c_custkey = e90->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e90->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e90->CUSTSALE_CNTRYCODE;
                long v90 = e90->__av;
                NUMCUSTCUSTOMER3.addOrDelOnZero(se120.modify(c_custkey,c_acctbal,custsale_cntrycode),v90);
              n90 = n90->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMCUSTCUSTOMER4CUSTOMER1_DELTA_map_012* i91 = static_cast<HashIndex_NUMCUSTCUSTOMER4CUSTOMER1_DELTA_map_012*>(NUMCUSTCUSTOMER4CUSTOMER1_DELTA.index[0]);
          HashIndex_NUMCUSTCUSTOMER4CUSTOMER1_DELTA_map_012::IdxNode* n91; 
          NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry* e91;
        
          for (size_t i = 0; i < i91->size_; i++)
          {
            n91 = i91->buckets_ + i;
            while (n91 && (e91 = n91->obj))
            {
                long c_custkey = e91->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e91->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e91->CUSTSALE_CNTRYCODE;
                long v91 = e91->__av;
                NUMCUSTCUSTOMER4.addOrDelOnZero(se121.modify(c_custkey,c_acctbal,custsale_cntrycode),v91);
              n91 = n91->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMCUSTCUSTOMER5CUSTOMER1_DELTA_map_012* i92 = static_cast<HashIndex_NUMCUSTCUSTOMER5CUSTOMER1_DELTA_map_012*>(NUMCUSTCUSTOMER5CUSTOMER1_DELTA.index[0]);
          HashIndex_NUMCUSTCUSTOMER5CUSTOMER1_DELTA_map_012::IdxNode* n92; 
          NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry* e92;
        
          for (size_t i = 0; i < i92->size_; i++)
          {
            n92 = i92->buckets_ + i;
            while (n92 && (e92 = n92->obj))
            {
                long c_custkey = e92->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e92->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e92->CUSTSALE_CNTRYCODE;
                long v92 = e92->__av;
                NUMCUSTCUSTOMER5.addOrDelOnZero(se122.modify(c_custkey,c_acctbal,custsale_cntrycode),v92);
              n92 = n92->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMCUSTCUSTOMER6CUSTOMER1_DELTA_map_012* i93 = static_cast<HashIndex_NUMCUSTCUSTOMER6CUSTOMER1_DELTA_map_012*>(NUMCUSTCUSTOMER6CUSTOMER1_DELTA.index[0]);
          HashIndex_NUMCUSTCUSTOMER6CUSTOMER1_DELTA_map_012::IdxNode* n93; 
          NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry* e93;
        
          for (size_t i = 0; i < i93->size_; i++)
          {
            n93 = i93->buckets_ + i;
            while (n93 && (e93 = n93->obj))
            {
                long c_custkey = e93->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e93->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e93->CUSTSALE_CNTRYCODE;
                long v93 = e93->__av;
                NUMCUSTCUSTOMER6.addOrDelOnZero(se123.modify(c_custkey,c_acctbal,custsale_cntrycode),v93);
              n93 = n93->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMCUSTCUSTOMER7CUSTOMER1_DELTA_map_012* i94 = static_cast<HashIndex_NUMCUSTCUSTOMER7CUSTOMER1_DELTA_map_012*>(NUMCUSTCUSTOMER7CUSTOMER1_DELTA.index[0]);
          HashIndex_NUMCUSTCUSTOMER7CUSTOMER1_DELTA_map_012::IdxNode* n94; 
          NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry* e94;
        
          for (size_t i = 0; i < i94->size_; i++)
          {
            n94 = i94->buckets_ + i;
            while (n94 && (e94 = n94->obj))
            {
                long c_custkey = e94->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e94->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e94->CUSTSALE_CNTRYCODE;
                long v94 = e94->__av;
                NUMCUSTCUSTOMER7.addOrDelOnZero(se124.modify(c_custkey,c_acctbal,custsale_cntrycode),v94);
              n94 = n94->nxt;
            }
          }
        }{  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_map_012* i95 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_map_012*>(TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_map_012::IdxNode* n95; 
          TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry* e95;
        
          for (size_t i = 0; i < i95->size_; i++)
          {
            n95 = i95->buckets_ + i;
            while (n95 && (e95 = n95->obj))
            {
                long c_custkey = e95->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e95->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e95->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v95 = e95->__av;
                TOTALACCTBALCUSTOMER1.addOrDelOnZero(se125.modify(c_custkey,c_acctbal,custsale_cntrycode),v95);
              n95 = n95->nxt;
            }
          }
        }{  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_map_012* i96 = static_cast<HashIndex_TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_map_012*>(TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_map_012::IdxNode* n96; 
          TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry* e96;
        
          for (size_t i = 0; i < i96->size_; i++)
          {
            n96 = i96->buckets_ + i;
            while (n96 && (e96 = n96->obj))
            {
                long c_custkey = e96->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e96->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e96->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v96 = e96->__av;
                TOTALACCTBALCUSTOMER2.addOrDelOnZero(se126.modify(c_custkey,c_acctbal,custsale_cntrycode),v96);
              n96 = n96->nxt;
            }
          }
        }{  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_map_012* i97 = static_cast<HashIndex_TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_map_012*>(TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_map_012::IdxNode* n97; 
          TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry* e97;
        
          for (size_t i = 0; i < i97->size_; i++)
          {
            n97 = i97->buckets_ + i;
            while (n97 && (e97 = n97->obj))
            {
                long c_custkey = e97->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e97->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e97->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v97 = e97->__av;
                TOTALACCTBALCUSTOMER3.addOrDelOnZero(se127.modify(c_custkey,c_acctbal,custsale_cntrycode),v97);
              n97 = n97->nxt;
            }
          }
        }{  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_map_012* i98 = static_cast<HashIndex_TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_map_012*>(TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_map_012::IdxNode* n98; 
          TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry* e98;
        
          for (size_t i = 0; i < i98->size_; i++)
          {
            n98 = i98->buckets_ + i;
            while (n98 && (e98 = n98->obj))
            {
                long c_custkey = e98->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e98->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e98->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v98 = e98->__av;
                TOTALACCTBALCUSTOMER4.addOrDelOnZero(se128.modify(c_custkey,c_acctbal,custsale_cntrycode),v98);
              n98 = n98->nxt;
            }
          }
        }{  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_map_012* i99 = static_cast<HashIndex_TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_map_012*>(TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_map_012::IdxNode* n99; 
          TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry* e99;
        
          for (size_t i = 0; i < i99->size_; i++)
          {
            n99 = i99->buckets_ + i;
            while (n99 && (e99 = n99->obj))
            {
                long c_custkey = e99->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e99->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e99->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v99 = e99->__av;
                TOTALACCTBALCUSTOMER5.addOrDelOnZero(se129.modify(c_custkey,c_acctbal,custsale_cntrycode),v99);
              n99 = n99->nxt;
            }
          }
        }{  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_map_012* i100 = static_cast<HashIndex_TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_map_012*>(TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_map_012::IdxNode* n100; 
          TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry* e100;
        
          for (size_t i = 0; i < i100->size_; i++)
          {
            n100 = i100->buckets_ + i;
            while (n100 && (e100 = n100->obj))
            {
                long c_custkey = e100->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e100->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e100->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v100 = e100->__av;
                TOTALACCTBALCUSTOMER6.addOrDelOnZero(se130.modify(c_custkey,c_acctbal,custsale_cntrycode),v100);
              n100 = n100->nxt;
            }
          }
        }{  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_map_012* i101 = static_cast<HashIndex_TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_map_012*>(TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_map_012::IdxNode* n101; 
          TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry* e101;
        
          for (size_t i = 0; i < i101->size_; i++)
          {
            n101 = i101->buckets_ + i;
            while (n101 && (e101 = n101->obj))
            {
                long c_custkey = e101->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e101->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e101->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v101 = e101->__av;
                TOTALACCTBALCUSTOMER7.addOrDelOnZero(se131.modify(c_custkey,c_acctbal,custsale_cntrycode),v101);
              n101 = n101->nxt;
            }
          }
        }NUMCUST.clear();
        DOUBLE_TYPE agg43 = 0.0;
        long l100 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l100) ? agg43 += Udiv(Ulistmax(1L, l100)) : 0.0);
        DOUBLE_TYPE l99 = (agg43 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l101 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTCUSTOMER1_map_012* i102 = static_cast<HashIndex_NUMCUSTCUSTOMER1_map_012*>(NUMCUSTCUSTOMER1.index[0]);
          HashIndex_NUMCUSTCUSTOMER1_map_012::IdxNode* n102; 
          NUMCUSTCUSTOMER1_entry* e102;
        
          for (size_t i = 0; i < i102->size_; i++)
          {
            n102 = i102->buckets_ + i;
            while (n102 && (e102 = n102->obj))
            {
                long c_custkey = e102->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e102->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e102->CUSTSALE_CNTRYCODE;
                long v102 = e102->__av;
                (/*if */(l101 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se133.modify(c_custkey)) && c_acctbal > l99) ? NUMCUST.addOrDelOnZero(se132.modify(custsale_cntrycode),v102) : (void)0);
              n102 = n102->nxt;
            }
          }
        }DOUBLE_TYPE agg44 = 0.0;
        long l103 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l103) ? agg44 += Udiv(Ulistmax(1L, l103)) : 0.0);
        DOUBLE_TYPE l102 = (agg44 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l104 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTCUSTOMER2_map_012* i103 = static_cast<HashIndex_NUMCUSTCUSTOMER2_map_012*>(NUMCUSTCUSTOMER2.index[0]);
          HashIndex_NUMCUSTCUSTOMER2_map_012::IdxNode* n103; 
          NUMCUSTCUSTOMER2_entry* e103;
        
          for (size_t i = 0; i < i103->size_; i++)
          {
            n103 = i103->buckets_ + i;
            while (n103 && (e103 = n103->obj))
            {
                long c_custkey = e103->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e103->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e103->CUSTSALE_CNTRYCODE;
                long v103 = e103->__av;
                (/*if */(l104 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se134.modify(c_custkey)) && c_acctbal > l102) ? NUMCUST.addOrDelOnZero(se132.modify(custsale_cntrycode),v103) : (void)0);
              n103 = n103->nxt;
            }
          }
        }DOUBLE_TYPE agg45 = 0.0;
        long l106 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l106) ? agg45 += Udiv(Ulistmax(1L, l106)) : 0.0);
        DOUBLE_TYPE l105 = (agg45 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l107 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTCUSTOMER3_map_012* i104 = static_cast<HashIndex_NUMCUSTCUSTOMER3_map_012*>(NUMCUSTCUSTOMER3.index[0]);
          HashIndex_NUMCUSTCUSTOMER3_map_012::IdxNode* n104; 
          NUMCUSTCUSTOMER3_entry* e104;
        
          for (size_t i = 0; i < i104->size_; i++)
          {
            n104 = i104->buckets_ + i;
            while (n104 && (e104 = n104->obj))
            {
                long c_custkey = e104->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e104->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e104->CUSTSALE_CNTRYCODE;
                long v104 = e104->__av;
                (/*if */(l107 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se135.modify(c_custkey)) && c_acctbal > l105) ? NUMCUST.addOrDelOnZero(se132.modify(custsale_cntrycode),v104) : (void)0);
              n104 = n104->nxt;
            }
          }
        }DOUBLE_TYPE agg46 = 0.0;
        long l109 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l109) ? agg46 += Udiv(Ulistmax(1L, l109)) : 0.0);
        DOUBLE_TYPE l108 = (agg46 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l110 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTCUSTOMER4_map_012* i105 = static_cast<HashIndex_NUMCUSTCUSTOMER4_map_012*>(NUMCUSTCUSTOMER4.index[0]);
          HashIndex_NUMCUSTCUSTOMER4_map_012::IdxNode* n105; 
          NUMCUSTCUSTOMER4_entry* e105;
        
          for (size_t i = 0; i < i105->size_; i++)
          {
            n105 = i105->buckets_ + i;
            while (n105 && (e105 = n105->obj))
            {
                long c_custkey = e105->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e105->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e105->CUSTSALE_CNTRYCODE;
                long v105 = e105->__av;
                (/*if */(l110 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se136.modify(c_custkey)) && c_acctbal > l108) ? NUMCUST.addOrDelOnZero(se132.modify(custsale_cntrycode),v105) : (void)0);
              n105 = n105->nxt;
            }
          }
        }DOUBLE_TYPE agg47 = 0.0;
        long l112 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l112) ? agg47 += Udiv(Ulistmax(1L, l112)) : 0.0);
        DOUBLE_TYPE l111 = (agg47 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l113 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTCUSTOMER5_map_012* i106 = static_cast<HashIndex_NUMCUSTCUSTOMER5_map_012*>(NUMCUSTCUSTOMER5.index[0]);
          HashIndex_NUMCUSTCUSTOMER5_map_012::IdxNode* n106; 
          NUMCUSTCUSTOMER5_entry* e106;
        
          for (size_t i = 0; i < i106->size_; i++)
          {
            n106 = i106->buckets_ + i;
            while (n106 && (e106 = n106->obj))
            {
                long c_custkey = e106->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e106->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e106->CUSTSALE_CNTRYCODE;
                long v106 = e106->__av;
                (/*if */(l113 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se137.modify(c_custkey)) && c_acctbal > l111) ? NUMCUST.addOrDelOnZero(se132.modify(custsale_cntrycode),v106) : (void)0);
              n106 = n106->nxt;
            }
          }
        }DOUBLE_TYPE agg48 = 0.0;
        long l115 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l115) ? agg48 += Udiv(Ulistmax(1L, l115)) : 0.0);
        DOUBLE_TYPE l114 = (agg48 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l116 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTCUSTOMER6_map_012* i107 = static_cast<HashIndex_NUMCUSTCUSTOMER6_map_012*>(NUMCUSTCUSTOMER6.index[0]);
          HashIndex_NUMCUSTCUSTOMER6_map_012::IdxNode* n107; 
          NUMCUSTCUSTOMER6_entry* e107;
        
          for (size_t i = 0; i < i107->size_; i++)
          {
            n107 = i107->buckets_ + i;
            while (n107 && (e107 = n107->obj))
            {
                long c_custkey = e107->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e107->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e107->CUSTSALE_CNTRYCODE;
                long v107 = e107->__av;
                (/*if */(l116 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se138.modify(c_custkey)) && c_acctbal > l114) ? NUMCUST.addOrDelOnZero(se132.modify(custsale_cntrycode),v107) : (void)0);
              n107 = n107->nxt;
            }
          }
        }DOUBLE_TYPE agg49 = 0.0;
        long l118 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l118) ? agg49 += Udiv(Ulistmax(1L, l118)) : 0.0);
        DOUBLE_TYPE l117 = (agg49 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l119 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTCUSTOMER7_map_012* i108 = static_cast<HashIndex_NUMCUSTCUSTOMER7_map_012*>(NUMCUSTCUSTOMER7.index[0]);
          HashIndex_NUMCUSTCUSTOMER7_map_012::IdxNode* n108; 
          NUMCUSTCUSTOMER7_entry* e108;
        
          for (size_t i = 0; i < i108->size_; i++)
          {
            n108 = i108->buckets_ + i;
            while (n108 && (e108 = n108->obj))
            {
                long c_custkey = e108->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e108->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e108->CUSTSALE_CNTRYCODE;
                long v108 = e108->__av;
                (/*if */(l119 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se139.modify(c_custkey)) && c_acctbal > l117) ? NUMCUST.addOrDelOnZero(se132.modify(custsale_cntrycode),v108) : (void)0);
              n108 = n108->nxt;
            }
          }
        }TOTALACCTBAL.clear();
        DOUBLE_TYPE agg50 = 0.0;
        long l121 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l121) ? agg50 += Udiv(Ulistmax(1L, l121)) : 0.0);
        DOUBLE_TYPE l120 = (agg50 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l122 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER1_map_012* i109 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_012*>(TOTALACCTBALCUSTOMER1.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER1_map_012::IdxNode* n109; 
          TOTALACCTBALCUSTOMER1_entry* e109;
        
          for (size_t i = 0; i < i109->size_; i++)
          {
            n109 = i109->buckets_ + i;
            while (n109 && (e109 = n109->obj))
            {
                long c_custkey = e109->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e109->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e109->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v109 = e109->__av;
                (/*if */(l122 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se141.modify(c_custkey)) && c_acctbal > l120) ? TOTALACCTBAL.addOrDelOnZero(se140.modify(custsale_cntrycode),v109) : (void)0);
              n109 = n109->nxt;
            }
          }
        }DOUBLE_TYPE agg51 = 0.0;
        long l124 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l124) ? agg51 += Udiv(Ulistmax(1L, l124)) : 0.0);
        DOUBLE_TYPE l123 = (agg51 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l125 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER2_map_012* i110 = static_cast<HashIndex_TOTALACCTBALCUSTOMER2_map_012*>(TOTALACCTBALCUSTOMER2.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER2_map_012::IdxNode* n110; 
          TOTALACCTBALCUSTOMER2_entry* e110;
        
          for (size_t i = 0; i < i110->size_; i++)
          {
            n110 = i110->buckets_ + i;
            while (n110 && (e110 = n110->obj))
            {
                long c_custkey = e110->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e110->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e110->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v110 = e110->__av;
                (/*if */(l125 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se142.modify(c_custkey)) && c_acctbal > l123) ? TOTALACCTBAL.addOrDelOnZero(se140.modify(custsale_cntrycode),v110) : (void)0);
              n110 = n110->nxt;
            }
          }
        }DOUBLE_TYPE agg52 = 0.0;
        long l127 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l127) ? agg52 += Udiv(Ulistmax(1L, l127)) : 0.0);
        DOUBLE_TYPE l126 = (agg52 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l128 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER3_map_012* i111 = static_cast<HashIndex_TOTALACCTBALCUSTOMER3_map_012*>(TOTALACCTBALCUSTOMER3.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER3_map_012::IdxNode* n111; 
          TOTALACCTBALCUSTOMER3_entry* e111;
        
          for (size_t i = 0; i < i111->size_; i++)
          {
            n111 = i111->buckets_ + i;
            while (n111 && (e111 = n111->obj))
            {
                long c_custkey = e111->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e111->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e111->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v111 = e111->__av;
                (/*if */(l128 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se143.modify(c_custkey)) && c_acctbal > l126) ? TOTALACCTBAL.addOrDelOnZero(se140.modify(custsale_cntrycode),v111) : (void)0);
              n111 = n111->nxt;
            }
          }
        }DOUBLE_TYPE agg53 = 0.0;
        long l130 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l130) ? agg53 += Udiv(Ulistmax(1L, l130)) : 0.0);
        DOUBLE_TYPE l129 = (agg53 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l131 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER4_map_012* i112 = static_cast<HashIndex_TOTALACCTBALCUSTOMER4_map_012*>(TOTALACCTBALCUSTOMER4.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER4_map_012::IdxNode* n112; 
          TOTALACCTBALCUSTOMER4_entry* e112;
        
          for (size_t i = 0; i < i112->size_; i++)
          {
            n112 = i112->buckets_ + i;
            while (n112 && (e112 = n112->obj))
            {
                long c_custkey = e112->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e112->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e112->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v112 = e112->__av;
                (/*if */(l131 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se144.modify(c_custkey)) && c_acctbal > l129) ? TOTALACCTBAL.addOrDelOnZero(se140.modify(custsale_cntrycode),v112) : (void)0);
              n112 = n112->nxt;
            }
          }
        }DOUBLE_TYPE agg54 = 0.0;
        long l133 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l133) ? agg54 += Udiv(Ulistmax(1L, l133)) : 0.0);
        DOUBLE_TYPE l132 = (agg54 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l134 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER5_map_012* i113 = static_cast<HashIndex_TOTALACCTBALCUSTOMER5_map_012*>(TOTALACCTBALCUSTOMER5.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER5_map_012::IdxNode* n113; 
          TOTALACCTBALCUSTOMER5_entry* e113;
        
          for (size_t i = 0; i < i113->size_; i++)
          {
            n113 = i113->buckets_ + i;
            while (n113 && (e113 = n113->obj))
            {
                long c_custkey = e113->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e113->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e113->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v113 = e113->__av;
                (/*if */(l134 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se145.modify(c_custkey)) && c_acctbal > l132) ? TOTALACCTBAL.addOrDelOnZero(se140.modify(custsale_cntrycode),v113) : (void)0);
              n113 = n113->nxt;
            }
          }
        }DOUBLE_TYPE agg55 = 0.0;
        long l136 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l136) ? agg55 += Udiv(Ulistmax(1L, l136)) : 0.0);
        DOUBLE_TYPE l135 = (agg55 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l137 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER6_map_012* i114 = static_cast<HashIndex_TOTALACCTBALCUSTOMER6_map_012*>(TOTALACCTBALCUSTOMER6.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER6_map_012::IdxNode* n114; 
          TOTALACCTBALCUSTOMER6_entry* e114;
        
          for (size_t i = 0; i < i114->size_; i++)
          {
            n114 = i114->buckets_ + i;
            while (n114 && (e114 = n114->obj))
            {
                long c_custkey = e114->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e114->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e114->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v114 = e114->__av;
                (/*if */(l137 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se146.modify(c_custkey)) && c_acctbal > l135) ? TOTALACCTBAL.addOrDelOnZero(se140.modify(custsale_cntrycode),v114) : (void)0);
              n114 = n114->nxt;
            }
          }
        }DOUBLE_TYPE agg56 = 0.0;
        long l139 = (NUMCUSTCUSTOMER1_L2_1_L1_1 + (NUMCUSTCUSTOMER1_L2_1_L1_2 + (NUMCUSTCUSTOMER1_L2_1_L1_3 + (NUMCUSTCUSTOMER1_L2_1_L1_4 + (NUMCUSTCUSTOMER1_L2_1_L1_5 + (NUMCUSTCUSTOMER1_L2_1_L1_6 + NUMCUSTCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l139) ? agg56 += Udiv(Ulistmax(1L, l139)) : 0.0);
        DOUBLE_TYPE l138 = (agg56 * (NUMCUSTCUSTOMER1_L2_2 + (NUMCUSTCUSTOMER1_L2_4 + (NUMCUSTCUSTOMER1_L2_6 + (NUMCUSTCUSTOMER1_L2_8 + (NUMCUSTCUSTOMER1_L2_10 + (NUMCUSTCUSTOMER1_L2_12 + NUMCUSTCUSTOMER1_L2_14)))))));
        long l140 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER7_map_012* i115 = static_cast<HashIndex_TOTALACCTBALCUSTOMER7_map_012*>(TOTALACCTBALCUSTOMER7.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER7_map_012::IdxNode* n115; 
          TOTALACCTBALCUSTOMER7_entry* e115;
        
          for (size_t i = 0; i < i115->size_; i++)
          {
            n115 = i115->buckets_ + i;
            while (n115 && (e115 = n115->obj))
            {
                long c_custkey = e115->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e115->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e115->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v115 = e115->__av;
                (/*if */(l140 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se147.modify(c_custkey)) && c_acctbal > l138) ? TOTALACCTBAL.addOrDelOnZero(se140.modify(custsale_cntrycode),v115) : (void)0);
              n115 = n115->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        NUMCUSTCUSTOMER1_L2_2 = 0.0;
        NUMCUSTCUSTOMER1_L2_2CUSTOMER1_DELTA = 0.0;
        NUMCUSTCUSTOMER1_L2_4 = 0.0;
        NUMCUSTCUSTOMER1_L2_4CUSTOMER1_DELTA = 0.0;
        NUMCUSTCUSTOMER1_L2_6 = 0.0;
        NUMCUSTCUSTOMER1_L2_6CUSTOMER1_DELTA = 0.0;
        NUMCUSTCUSTOMER1_L2_8 = 0.0;
        NUMCUSTCUSTOMER1_L2_8CUSTOMER1_DELTA = 0.0;
        NUMCUSTCUSTOMER1_L2_10 = 0.0;
        NUMCUSTCUSTOMER1_L2_10CUSTOMER1_DELTA = 0.0;
        NUMCUSTCUSTOMER1_L2_12 = 0.0;
        NUMCUSTCUSTOMER1_L2_12CUSTOMER1_DELTA = 0.0;
        NUMCUSTCUSTOMER1_L2_14 = 0.0;
        NUMCUSTCUSTOMER1_L2_14CUSTOMER1_DELTA = 0.0;
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    NUMCUSTORDERS1_L2_2_DELTA_entry se1;
    NUMCUSTORDERS1_DOMAIN1_entry se2;
    NUMCUST_entry se3;
    NUMCUSTCUSTOMER1_L3_1_entry se4;
    NUMCUSTORDERS1_L2_2_DELTA_entry se5;
    NUMCUSTCUSTOMER1_entry se6;
    NUMCUSTCUSTOMER1_L3_1_entry se7;
    NUMCUSTORDERS1_L2_2_DELTA_entry se8;
    NUMCUSTCUSTOMER2_entry se9;
    NUMCUSTCUSTOMER1_L3_1_entry se10;
    NUMCUSTORDERS1_L2_2_DELTA_entry se11;
    NUMCUSTCUSTOMER3_entry se12;
    NUMCUSTCUSTOMER1_L3_1_entry se13;
    NUMCUSTORDERS1_L2_2_DELTA_entry se14;
    NUMCUSTCUSTOMER4_entry se15;
    NUMCUSTCUSTOMER1_L3_1_entry se16;
    NUMCUSTORDERS1_L2_2_DELTA_entry se17;
    NUMCUSTCUSTOMER5_entry se18;
    NUMCUSTCUSTOMER1_L3_1_entry se19;
    NUMCUSTORDERS1_L2_2_DELTA_entry se20;
    NUMCUSTCUSTOMER6_entry se21;
    NUMCUSTCUSTOMER1_L3_1_entry se22;
    NUMCUSTORDERS1_L2_2_DELTA_entry se23;
    NUMCUSTCUSTOMER7_entry se24;
    NUMCUSTCUSTOMER1_L3_1_entry se25;
    NUMCUSTCUSTOMER1_entry se26;
    NUMCUSTCUSTOMER1_L3_1_entry se27;
    NUMCUSTCUSTOMER2_entry se28;
    NUMCUSTCUSTOMER1_L3_1_entry se29;
    NUMCUSTCUSTOMER3_entry se30;
    NUMCUSTCUSTOMER1_L3_1_entry se31;
    NUMCUSTCUSTOMER4_entry se32;
    NUMCUSTCUSTOMER1_L3_1_entry se33;
    NUMCUSTCUSTOMER5_entry se34;
    NUMCUSTCUSTOMER1_L3_1_entry se35;
    NUMCUSTCUSTOMER6_entry se36;
    NUMCUSTCUSTOMER1_L3_1_entry se37;
    NUMCUSTCUSTOMER7_entry se38;
    TOTALACCTBAL_entry se39;
    NUMCUSTCUSTOMER1_L3_1_entry se40;
    NUMCUSTORDERS1_L2_2_DELTA_entry se41;
    TOTALACCTBALCUSTOMER1_entry se42;
    NUMCUSTCUSTOMER1_L3_1_entry se43;
    NUMCUSTORDERS1_L2_2_DELTA_entry se44;
    TOTALACCTBALCUSTOMER2_entry se45;
    NUMCUSTCUSTOMER1_L3_1_entry se46;
    NUMCUSTORDERS1_L2_2_DELTA_entry se47;
    TOTALACCTBALCUSTOMER3_entry se48;
    NUMCUSTCUSTOMER1_L3_1_entry se49;
    NUMCUSTORDERS1_L2_2_DELTA_entry se50;
    TOTALACCTBALCUSTOMER4_entry se51;
    NUMCUSTCUSTOMER1_L3_1_entry se52;
    NUMCUSTORDERS1_L2_2_DELTA_entry se53;
    TOTALACCTBALCUSTOMER5_entry se54;
    NUMCUSTCUSTOMER1_L3_1_entry se55;
    NUMCUSTORDERS1_L2_2_DELTA_entry se56;
    TOTALACCTBALCUSTOMER6_entry se57;
    NUMCUSTCUSTOMER1_L3_1_entry se58;
    NUMCUSTORDERS1_L2_2_DELTA_entry se59;
    TOTALACCTBALCUSTOMER7_entry se60;
    NUMCUSTCUSTOMER1_L3_1_entry se61;
    TOTALACCTBALCUSTOMER1_entry se62;
    NUMCUSTCUSTOMER1_L3_1_entry se63;
    TOTALACCTBALCUSTOMER2_entry se64;
    NUMCUSTCUSTOMER1_L3_1_entry se65;
    TOTALACCTBALCUSTOMER3_entry se66;
    NUMCUSTCUSTOMER1_L3_1_entry se67;
    TOTALACCTBALCUSTOMER4_entry se68;
    NUMCUSTCUSTOMER1_L3_1_entry se69;
    TOTALACCTBALCUSTOMER5_entry se70;
    NUMCUSTCUSTOMER1_L3_1_entry se71;
    TOTALACCTBALCUSTOMER6_entry se72;
    NUMCUSTCUSTOMER1_L3_1_entry se73;
    TOTALACCTBALCUSTOMER7_entry se74;
    NUMCUSTCUSTOMER1_L3_1_entry se75;
    NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry se76;
    NUMCUSTCUSTOMER2CUSTOMER1_DELTA_entry se91;
    NUMCUSTCUSTOMER3CUSTOMER1_DELTA_entry se92;
    NUMCUSTCUSTOMER4CUSTOMER1_DELTA_entry se93;
    NUMCUSTCUSTOMER5CUSTOMER1_DELTA_entry se94;
    NUMCUSTCUSTOMER6CUSTOMER1_DELTA_entry se95;
    NUMCUSTCUSTOMER7CUSTOMER1_DELTA_entry se96;
    TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry se97;
    TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_entry se98;
    TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_entry se99;
    TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_entry se100;
    TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_entry se101;
    TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_entry se102;
    TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_entry se103;
    NUMCUSTCUSTOMER1_entry se104;
    NUMCUSTCUSTOMER2_entry se119;
    NUMCUSTCUSTOMER3_entry se120;
    NUMCUSTCUSTOMER4_entry se121;
    NUMCUSTCUSTOMER5_entry se122;
    NUMCUSTCUSTOMER6_entry se123;
    NUMCUSTCUSTOMER7_entry se124;
    TOTALACCTBALCUSTOMER1_entry se125;
    TOTALACCTBALCUSTOMER2_entry se126;
    TOTALACCTBALCUSTOMER3_entry se127;
    TOTALACCTBALCUSTOMER4_entry se128;
    TOTALACCTBALCUSTOMER5_entry se129;
    TOTALACCTBALCUSTOMER6_entry se130;
    TOTALACCTBALCUSTOMER7_entry se131;
    NUMCUST_entry se132;
    NUMCUSTCUSTOMER1_L3_1_entry se133;
    NUMCUSTCUSTOMER1_L3_1_entry se134;
    NUMCUSTCUSTOMER1_L3_1_entry se135;
    NUMCUSTCUSTOMER1_L3_1_entry se136;
    NUMCUSTCUSTOMER1_L3_1_entry se137;
    NUMCUSTCUSTOMER1_L3_1_entry se138;
    NUMCUSTCUSTOMER1_L3_1_entry se139;
    TOTALACCTBAL_entry se140;
    NUMCUSTCUSTOMER1_L3_1_entry se141;
    NUMCUSTCUSTOMER1_L3_1_entry se142;
    NUMCUSTCUSTOMER1_L3_1_entry se143;
    NUMCUSTCUSTOMER1_L3_1_entry se144;
    NUMCUSTCUSTOMER1_L3_1_entry se145;
    NUMCUSTCUSTOMER1_L3_1_entry se146;
    NUMCUSTCUSTOMER1_L3_1_entry se147;
  
    /* Data structures used for storing materialized views */
    NUMCUSTORDERS1_DOMAIN1_map NUMCUSTORDERS1_DOMAIN1;
    NUMCUSTORDERS1_L2_2_DELTA_map NUMCUSTORDERS1_L2_2_DELTA;
    NUMCUSTCUSTOMER1_map NUMCUSTCUSTOMER1;
    NUMCUSTCUSTOMER1CUSTOMER1_DELTA_map NUMCUSTCUSTOMER1CUSTOMER1_DELTA;
    long NUMCUSTCUSTOMER1_L2_1_L1_1;
    long NUMCUSTCUSTOMER1_L2_1_L1_1CUSTOMER1_DELTA;
    long NUMCUSTCUSTOMER1_L2_1_L1_2;
    long NUMCUSTCUSTOMER1_L2_1_L1_2CUSTOMER1_DELTA;
    long NUMCUSTCUSTOMER1_L2_1_L1_3;
    long NUMCUSTCUSTOMER1_L2_1_L1_3CUSTOMER1_DELTA;
    long NUMCUSTCUSTOMER1_L2_1_L1_4;
    long NUMCUSTCUSTOMER1_L2_1_L1_4CUSTOMER1_DELTA;
    long NUMCUSTCUSTOMER1_L2_1_L1_5;
    long NUMCUSTCUSTOMER1_L2_1_L1_5CUSTOMER1_DELTA;
    long NUMCUSTCUSTOMER1_L2_1_L1_6;
    long NUMCUSTCUSTOMER1_L2_1_L1_6CUSTOMER1_DELTA;
    long NUMCUSTCUSTOMER1_L2_1_L1_7;
    long NUMCUSTCUSTOMER1_L2_1_L1_7CUSTOMER1_DELTA;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_2;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_2CUSTOMER1_DELTA;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_4;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_4CUSTOMER1_DELTA;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_6;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_6CUSTOMER1_DELTA;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_8;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_8CUSTOMER1_DELTA;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_10;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_10CUSTOMER1_DELTA;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_12;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_12CUSTOMER1_DELTA;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_14;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_14CUSTOMER1_DELTA;
    NUMCUSTCUSTOMER1_L3_1_map NUMCUSTCUSTOMER1_L3_1;
    NUMCUSTCUSTOMER2_map NUMCUSTCUSTOMER2;
    NUMCUSTCUSTOMER2CUSTOMER1_DELTA_map NUMCUSTCUSTOMER2CUSTOMER1_DELTA;
    NUMCUSTCUSTOMER3_map NUMCUSTCUSTOMER3;
    NUMCUSTCUSTOMER3CUSTOMER1_DELTA_map NUMCUSTCUSTOMER3CUSTOMER1_DELTA;
    NUMCUSTCUSTOMER4_map NUMCUSTCUSTOMER4;
    NUMCUSTCUSTOMER4CUSTOMER1_DELTA_map NUMCUSTCUSTOMER4CUSTOMER1_DELTA;
    NUMCUSTCUSTOMER5_map NUMCUSTCUSTOMER5;
    NUMCUSTCUSTOMER5CUSTOMER1_DELTA_map NUMCUSTCUSTOMER5CUSTOMER1_DELTA;
    NUMCUSTCUSTOMER6_map NUMCUSTCUSTOMER6;
    NUMCUSTCUSTOMER6CUSTOMER1_DELTA_map NUMCUSTCUSTOMER6CUSTOMER1_DELTA;
    NUMCUSTCUSTOMER7_map NUMCUSTCUSTOMER7;
    NUMCUSTCUSTOMER7CUSTOMER1_DELTA_map NUMCUSTCUSTOMER7CUSTOMER1_DELTA;
    TOTALACCTBALCUSTOMER1_map TOTALACCTBALCUSTOMER1;
    TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_map TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA;
    TOTALACCTBALCUSTOMER2_map TOTALACCTBALCUSTOMER2;
    TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA_map TOTALACCTBALCUSTOMER2CUSTOMER1_DELTA;
    TOTALACCTBALCUSTOMER3_map TOTALACCTBALCUSTOMER3;
    TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA_map TOTALACCTBALCUSTOMER3CUSTOMER1_DELTA;
    TOTALACCTBALCUSTOMER4_map TOTALACCTBALCUSTOMER4;
    TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA_map TOTALACCTBALCUSTOMER4CUSTOMER1_DELTA;
    TOTALACCTBALCUSTOMER5_map TOTALACCTBALCUSTOMER5;
    TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA_map TOTALACCTBALCUSTOMER5CUSTOMER1_DELTA;
    TOTALACCTBALCUSTOMER6_map TOTALACCTBALCUSTOMER6;
    TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA_map TOTALACCTBALCUSTOMER6CUSTOMER1_DELTA;
    TOTALACCTBALCUSTOMER7_map TOTALACCTBALCUSTOMER7;
    TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA_map TOTALACCTBALCUSTOMER7CUSTOMER1_DELTA;
    DELTA_ORDERS_map DELTA_ORDERS;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c5;
  
  };

}
