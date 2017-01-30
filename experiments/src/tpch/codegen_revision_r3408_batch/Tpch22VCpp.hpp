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
    data_t(): tlq_t(), NUMCUSTCUSTOMER1_L2_1_L1_1(0L), NUMCUSTCUSTOMER1_L2_1_L1_1CUSTOMER1_DELTA(0L), NUMCUSTCUSTOMER1_L2_2(0.0), NUMCUSTCUSTOMER1_L2_2CUSTOMER1_DELTA(0.0) {
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
                // long o_orderkey = DELTA_ORDERS.orderkey[i];
                long c_custkey = DELTA_ORDERS.custkey[i];
                // STRING_TYPE o_orderstatus = DELTA_ORDERS.orderstatus[i];
                // DOUBLE_TYPE o_totalprice = DELTA_ORDERS.totalprice[i];
                // date o_orderdate = DELTA_ORDERS.orderdate[i];
                // STRING_TYPE o_orderpriority = DELTA_ORDERS.orderpriority[i];
                // STRING_TYPE o_clerk = DELTA_ORDERS.clerk[i];
                // long o_shippriority = DELTA_ORDERS.shippriority[i];
                // STRING_TYPE o_comment = DELTA_ORDERS.comment[i];
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
                long l3 = NUMCUSTCUSTOMER1_L2_1_L1_1;
                (/*if */(0L != l3) ? agg1 += Udiv(Ulistmax(1L, l3)) : 0.0);
                DOUBLE_TYPE l2 = (NUMCUSTCUSTOMER1_L2_2 * agg1);
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
                long l6 = NUMCUSTCUSTOMER1_L2_1_L1_1;
                (/*if */(0L != l6) ? agg2 += Udiv(Ulistmax(1L, l6)) : 0.0);
                DOUBLE_TYPE l5 = (NUMCUSTCUSTOMER1_L2_2 * agg2);
                { //slice 
                  const HashIndex_NUMCUSTCUSTOMER1_map_0* i6 = static_cast<HashIndex_NUMCUSTCUSTOMER1_map_0*>(NUMCUSTCUSTOMER1.index[1]);
                  const HASH_RES_t h2 = NUMCUSTCUSTOMER1_mapkey0_idxfn::hash(se8.modify0(c_custkey));
                  HashIndex_NUMCUSTCUSTOMER1_map_0::IdxNode* n6 = static_cast<HashIndex_NUMCUSTCUSTOMER1_map_0::IdxNode*>(i6->slice(se8, h2));
                  NUMCUSTCUSTOMER1_entry* e6;
                 
                  if (n6 && (e6 = n6->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e6->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e6->CUSTSALE_CNTRYCODE;
                      long v6 = e6->__av;
                      (/*if */(l4 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se7.modify(c_custkey)) && c_acctbal > l5) ? NUMCUST.addOrDelOnZero(se3.modify(custsale_cntrycode),(((v5 != 0 ? 1L : 0L) * v6) * -1L)) : (void)0);
                      n6 = n6->nxt;
                    } while (n6 && (e6 = n6->obj) && h2 == n6->hash &&  NUMCUSTCUSTOMER1_mapkey0_idxfn::equals(se8, *e6)); 
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
                long l9 = NUMCUSTCUSTOMER1_L2_1_L1_1;
                (/*if */(0L != l9) ? agg3 += Udiv(Ulistmax(1L, l9)) : 0.0);
                DOUBLE_TYPE l8 = (NUMCUSTCUSTOMER1_L2_2 * agg3);
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER1_map_0* i8 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_0*>(TOTALACCTBALCUSTOMER1.index[1]);
                  const HASH_RES_t h3 = TOTALACCTBALCUSTOMER1_mapkey0_idxfn::hash(se12.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER1_map_0::IdxNode* n8 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_0::IdxNode*>(i8->slice(se12, h3));
                  TOTALACCTBALCUSTOMER1_entry* e8;
                 
                  if (n8 && (e8 = n8->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e8->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e8->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v8 = e8->__av;
                      (/*if */(l7 == (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se10.modify(c_custkey)) + NUMCUSTORDERS1_L2_2_DELTA.getValueOrDefault(se11.modify(c_custkey))) && c_acctbal > l8) ? TOTALACCTBAL.addOrDelOnZero(se9.modify(custsale_cntrycode),((v7 != 0 ? 1L : 0L) * v8)) : (void)0);
                      n8 = n8->nxt;
                    } while (n8 && (e8 = n8->obj) && h3 == n8->hash &&  TOTALACCTBALCUSTOMER1_mapkey0_idxfn::equals(se12, *e8)); 
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
                long l12 = NUMCUSTCUSTOMER1_L2_1_L1_1;
                (/*if */(0L != l12) ? agg4 += Udiv(Ulistmax(1L, l12)) : 0.0);
                DOUBLE_TYPE l11 = (NUMCUSTCUSTOMER1_L2_2 * agg4);
                { //slice 
                  const HashIndex_TOTALACCTBALCUSTOMER1_map_0* i10 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_0*>(TOTALACCTBALCUSTOMER1.index[1]);
                  const HASH_RES_t h4 = TOTALACCTBALCUSTOMER1_mapkey0_idxfn::hash(se14.modify0(c_custkey));
                  HashIndex_TOTALACCTBALCUSTOMER1_map_0::IdxNode* n10 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_0::IdxNode*>(i10->slice(se14, h4));
                  TOTALACCTBALCUSTOMER1_entry* e10;
                 
                  if (n10 && (e10 = n10->obj)) {
                    do {                
                      DOUBLE_TYPE c_acctbal = e10->C_ACCTBAL;
                      STRING_TYPE custsale_cntrycode = e10->CUSTSALE_CNTRYCODE;
                      DOUBLE_TYPE v10 = e10->__av;
                      (/*if */(l10 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se13.modify(c_custkey)) && c_acctbal > l11) ? TOTALACCTBAL.addOrDelOnZero(se9.modify(custsale_cntrycode),(((v9 != 0 ? 1L : 0L) * v10) * -1L)) : (void)0);
                      n10 = n10->nxt;
                    } while (n10 && (e10 = n10->obj) && h4 == n10->hash &&  TOTALACCTBALCUSTOMER1_mapkey0_idxfn::equals(se14, *e10)); 
                  }
                }
              n9 = n9->nxt;
            }
          }
        }{  // foreach
          const HashIndex_NUMCUSTORDERS1_L2_2_DELTA_map_0* i11 = static_cast<HashIndex_NUMCUSTORDERS1_L2_2_DELTA_map_0*>(NUMCUSTORDERS1_L2_2_DELTA.index[0]);
          HashIndex_NUMCUSTORDERS1_L2_2_DELTA_map_0::IdxNode* n11; 
          NUMCUSTORDERS1_L2_2_DELTA_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long c_custkey = e11->C_CUSTKEY;
                long v11 = e11->__av;
                NUMCUSTCUSTOMER1_L3_1.addOrDelOnZero(se15.modify(c_custkey),v11);
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

        NUMCUSTCUSTOMER1CUSTOMER1_DELTA.clear();
        long agg5 = 0L;
        DOUBLE_TYPE agg6 = 0.0;
        TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA.clear();        
        { 
          for (size_t i = 0; i < DELTA_CUSTOMER.size; i++) 
          {
                long c_custkey = DELTA_CUSTOMER.custkey[i];
                // STRING_TYPE c_name = DELTA_CUSTOMER.name[i];
                // STRING_TYPE c_address = DELTA_CUSTOMER.address[i];
                // long c_nationkey = DELTA_CUSTOMER.nationkey[i];
                STRING_TYPE c_phone = DELTA_CUSTOMER.phone[i];
                DOUBLE_TYPE c_acctbal = DELTA_CUSTOMER.acctbal[i];
                // STRING_TYPE c_mktsegment = DELTA_CUSTOMER.mktsegment[i];
                // STRING_TYPE c_comment = DELTA_CUSTOMER.comment[i];
                long v12 = 1L;
                STRING_TYPE l13 = Usubstring(c_phone, 0L, 2L);
                (/*if */(((l13 == c1) || (l13 == c2) || (l13 == c3) || (l13 == c4) || (l13 == c5) || (l13 == c6) || (l13 == c7))) ? NUMCUSTCUSTOMER1CUSTOMER1_DELTA.addOrDelOnZero(se16.modify(c_custkey,c_acctbal,l13),v12) : (void)0);            
                long v13 = 1L;
                (/*if */(((l13 == c1) || (l13 == c2) || (l13 == c3) || (l13 == c4) || (l13 == c5) || (l13 == c6) || (l13 == c7)) && c_acctbal > 0.0) ? agg5 += v13 : 0L);                
                long v14 = 1L;
                (/*if */(((l13 == c1) || (l13 == c2) || (l13 == c3) || (l13 == c4) || (l13 == c5) || (l13 == c6) || (l13 == c7)) && c_acctbal > 0.0) ? agg6 += (v14 * c_acctbal) : 0.0);
                long v15 = 1L;
                (/*if */(((l13 == c1) || (l13 == c2) || (l13 == c3) || (l13 == c4) || (l13 == c5) || (l13 == c6) || (l13 == c7))) ? TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA.addOrDelOnZero(se19.modify(c_custkey,c_acctbal,l13),(v15 * c_acctbal)) : (void)0);
          }
        }
        NUMCUSTCUSTOMER1_L2_1_L1_1CUSTOMER1_DELTA = agg5;
        NUMCUSTCUSTOMER1_L2_2CUSTOMER1_DELTA = agg6;

        {  // foreach
          const HashIndex_NUMCUSTCUSTOMER1CUSTOMER1_DELTA_map_012* i16 = static_cast<HashIndex_NUMCUSTCUSTOMER1CUSTOMER1_DELTA_map_012*>(NUMCUSTCUSTOMER1CUSTOMER1_DELTA.index[0]);
          HashIndex_NUMCUSTCUSTOMER1CUSTOMER1_DELTA_map_012::IdxNode* n16; 
          NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long c_custkey = e16->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e16->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e16->CUSTSALE_CNTRYCODE;
                long v16 = e16->__av;
                NUMCUSTCUSTOMER1.addOrDelOnZero(se20.modify(c_custkey,c_acctbal,custsale_cntrycode),v16);
              n16 = n16->nxt;
            }
          }
        }NUMCUSTCUSTOMER1_L2_1_L1_1 += NUMCUSTCUSTOMER1_L2_1_L1_1CUSTOMER1_DELTA;
        NUMCUSTCUSTOMER1_L2_2 += NUMCUSTCUSTOMER1_L2_2CUSTOMER1_DELTA;
        {  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_map_012* i17 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_map_012*>(TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_map_012::IdxNode* n17; 
          TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long c_custkey = e17->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e17->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e17->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v17 = e17->__av;
                TOTALACCTBALCUSTOMER1.addOrDelOnZero(se23.modify(c_custkey,c_acctbal,custsale_cntrycode),v17);
              n17 = n17->nxt;
            }
          }
        }NUMCUST.clear();
        DOUBLE_TYPE agg7 = 0.0;
        long l16 = NUMCUSTCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l16) ? agg7 += Udiv(Ulistmax(1L, l16)) : 0.0);
        DOUBLE_TYPE l15 = (NUMCUSTCUSTOMER1_L2_2 * agg7);
        long l17 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTCUSTOMER1_map_012* i18 = static_cast<HashIndex_NUMCUSTCUSTOMER1_map_012*>(NUMCUSTCUSTOMER1.index[0]);
          HashIndex_NUMCUSTCUSTOMER1_map_012::IdxNode* n18; 
          NUMCUSTCUSTOMER1_entry* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
                long c_custkey = e18->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e18->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e18->CUSTSALE_CNTRYCODE;
                long v18 = e18->__av;
                (/*if */(c_acctbal > l15 && l17 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se25.modify(c_custkey))) ? NUMCUST.addOrDelOnZero(se24.modify(custsale_cntrycode),v18) : (void)0);
              n18 = n18->nxt;
            }
          }
        }TOTALACCTBAL.clear();
        DOUBLE_TYPE agg8 = 0.0;
        long l19 = NUMCUSTCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l19) ? agg8 += Udiv(Ulistmax(1L, l19)) : 0.0);
        DOUBLE_TYPE l18 = (NUMCUSTCUSTOMER1_L2_2 * agg8);
        long l20 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER1_map_012* i19 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_012*>(TOTALACCTBALCUSTOMER1.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER1_map_012::IdxNode* n19; 
          TOTALACCTBALCUSTOMER1_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long c_custkey = e19->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e19->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e19->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v19 = e19->__av;
                (/*if */(c_acctbal > l18 && l20 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se27.modify(c_custkey))) ? TOTALACCTBAL.addOrDelOnZero(se26.modify(custsale_cntrycode),v19) : (void)0);
              n19 = n19->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        NUMCUSTCUSTOMER1_L2_2 = 0.0;
        NUMCUSTCUSTOMER1_L2_2CUSTOMER1_DELTA = 0.0;
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
    NUMCUSTCUSTOMER1_entry se8;
    TOTALACCTBAL_entry se9;
    NUMCUSTCUSTOMER1_L3_1_entry se10;
    NUMCUSTORDERS1_L2_2_DELTA_entry se11;
    TOTALACCTBALCUSTOMER1_entry se12;
    NUMCUSTCUSTOMER1_L3_1_entry se13;
    TOTALACCTBALCUSTOMER1_entry se14;
    NUMCUSTCUSTOMER1_L3_1_entry se15;
    NUMCUSTCUSTOMER1CUSTOMER1_DELTA_entry se16;
    TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_entry se19;
    NUMCUSTCUSTOMER1_entry se20;
    TOTALACCTBALCUSTOMER1_entry se23;
    NUMCUST_entry se24;
    NUMCUSTCUSTOMER1_L3_1_entry se25;
    TOTALACCTBAL_entry se26;
    NUMCUSTCUSTOMER1_L3_1_entry se27;
  
    /* Data structures used for storing materialized views */
    NUMCUSTORDERS1_DOMAIN1_map NUMCUSTORDERS1_DOMAIN1;
    NUMCUSTORDERS1_L2_2_DELTA_map NUMCUSTORDERS1_L2_2_DELTA;
    NUMCUSTCUSTOMER1_map NUMCUSTCUSTOMER1;
    NUMCUSTCUSTOMER1CUSTOMER1_DELTA_map NUMCUSTCUSTOMER1CUSTOMER1_DELTA;
    long NUMCUSTCUSTOMER1_L2_1_L1_1;
    long NUMCUSTCUSTOMER1_L2_1_L1_1CUSTOMER1_DELTA;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_2;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_2CUSTOMER1_DELTA;
    NUMCUSTCUSTOMER1_L3_1_map NUMCUSTCUSTOMER1_L3_1;
    TOTALACCTBALCUSTOMER1_map TOTALACCTBALCUSTOMER1;
    TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA_map TOTALACCTBALCUSTOMER1CUSTOMER1_DELTA;
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
