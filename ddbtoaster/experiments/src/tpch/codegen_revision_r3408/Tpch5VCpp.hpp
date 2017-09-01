#include <sys/time.h>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "hashmap.hpp"
#include "serialization.hpp"

#define ELEM_SEPARATOR "\n\t\t\t"

namespace dbtoaster {
  
  /* Definitions of auxiliary maps for storing materialized views. */
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
  
  struct REVENUESUPPLIER2_entry {
    long REVENUESUPPLIERSUPPLIER_NATIONKEY; long REVENUESUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit REVENUESUPPLIER2_entry() { /*REVENUESUPPLIERSUPPLIER_NATIONKEY = 0L; REVENUESUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit REVENUESUPPLIER2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { REVENUESUPPLIERSUPPLIER_NATIONKEY = c0; REVENUESUPPLIERSUPPLIER_SUPPKEY = c1; __av = c2; }
    REVENUESUPPLIER2_entry(const REVENUESUPPLIER2_entry& other) : REVENUESUPPLIERSUPPLIER_NATIONKEY( other.REVENUESUPPLIERSUPPLIER_NATIONKEY ), REVENUESUPPLIERSUPPLIER_SUPPKEY( other.REVENUESUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER2_entry& modify(const long c0, const long c1) { REVENUESUPPLIERSUPPLIER_NATIONKEY = c0; REVENUESUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUESUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUESUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUESUPPLIERSUPPLIER_NATIONKEY);
      hash_combine(h, e.REVENUESUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER2_entry& x, const REVENUESUPPLIER2_entry& y) {
      return x.REVENUESUPPLIERSUPPLIER_NATIONKEY == y.REVENUESUPPLIERSUPPLIER_NATIONKEY && x.REVENUESUPPLIERSUPPLIER_SUPPKEY == y.REVENUESUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER2_entry,DOUBLE_TYPE,
    HashIndex<REVENUESUPPLIER2_entry,DOUBLE_TYPE,REVENUESUPPLIER2_mapkey01_idxfn,true>
  > REVENUESUPPLIER2_map;
  typedef HashIndex<REVENUESUPPLIER2_entry,DOUBLE_TYPE,REVENUESUPPLIER2_mapkey01_idxfn,true> HashIndex_REVENUESUPPLIER2_map_01;
  
  struct REVENUESUPPLIER2ORDERS4_entry {
    long REVENUESUPPLIER2ORDERSORDERS_ORDERKEY; long REVENUESUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit REVENUESUPPLIER2ORDERS4_entry() { /*REVENUESUPPLIER2ORDERSORDERS_ORDERKEY = 0L; REVENUESUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit REVENUESUPPLIER2ORDERS4_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { REVENUESUPPLIER2ORDERSORDERS_ORDERKEY = c0; REVENUESUPPLIERSUPPLIER_SUPPKEY = c1; __av = c2; }
    REVENUESUPPLIER2ORDERS4_entry(const REVENUESUPPLIER2ORDERS4_entry& other) : REVENUESUPPLIER2ORDERSORDERS_ORDERKEY( other.REVENUESUPPLIER2ORDERSORDERS_ORDERKEY ), REVENUESUPPLIERSUPPLIER_SUPPKEY( other.REVENUESUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER2ORDERS4_entry& modify(const long c0, const long c1) { REVENUESUPPLIER2ORDERSORDERS_ORDERKEY = c0; REVENUESUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    FORCE_INLINE REVENUESUPPLIER2ORDERS4_entry& modify0(const long c0) { REVENUESUPPLIER2ORDERSORDERS_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUESUPPLIER2ORDERS4_entry& modify1(const long c1) { REVENUESUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUESUPPLIER2ORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUESUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER2ORDERS4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER2ORDERS4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUESUPPLIER2ORDERSORDERS_ORDERKEY);
      hash_combine(h, e.REVENUESUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER2ORDERS4_entry& x, const REVENUESUPPLIER2ORDERS4_entry& y) {
      return x.REVENUESUPPLIER2ORDERSORDERS_ORDERKEY == y.REVENUESUPPLIER2ORDERSORDERS_ORDERKEY && x.REVENUESUPPLIERSUPPLIER_SUPPKEY == y.REVENUESUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  struct REVENUESUPPLIER2ORDERS4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER2ORDERS4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUESUPPLIER2ORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER2ORDERS4_entry& x, const REVENUESUPPLIER2ORDERS4_entry& y) {
      return x.REVENUESUPPLIER2ORDERSORDERS_ORDERKEY == y.REVENUESUPPLIER2ORDERSORDERS_ORDERKEY;
    }
  };
  
  struct REVENUESUPPLIER2ORDERS4_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER2ORDERS4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUESUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER2ORDERS4_entry& x, const REVENUESUPPLIER2ORDERS4_entry& y) {
      return x.REVENUESUPPLIERSUPPLIER_SUPPKEY == y.REVENUESUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER2ORDERS4_entry,DOUBLE_TYPE,
    HashIndex<REVENUESUPPLIER2ORDERS4_entry,DOUBLE_TYPE,REVENUESUPPLIER2ORDERS4_mapkey01_idxfn,true>,
    HashIndex<REVENUESUPPLIER2ORDERS4_entry,DOUBLE_TYPE,REVENUESUPPLIER2ORDERS4_mapkey0_idxfn,false>,
    HashIndex<REVENUESUPPLIER2ORDERS4_entry,DOUBLE_TYPE,REVENUESUPPLIER2ORDERS4_mapkey1_idxfn,false>
  > REVENUESUPPLIER2ORDERS4_map;
  typedef HashIndex<REVENUESUPPLIER2ORDERS4_entry,DOUBLE_TYPE,REVENUESUPPLIER2ORDERS4_mapkey01_idxfn,true> HashIndex_REVENUESUPPLIER2ORDERS4_map_01;
  typedef HashIndex<REVENUESUPPLIER2ORDERS4_entry,DOUBLE_TYPE,REVENUESUPPLIER2ORDERS4_mapkey0_idxfn,false> HashIndex_REVENUESUPPLIER2ORDERS4_map_0;
  typedef HashIndex<REVENUESUPPLIER2ORDERS4_entry,DOUBLE_TYPE,REVENUESUPPLIER2ORDERS4_mapkey1_idxfn,false> HashIndex_REVENUESUPPLIER2ORDERS4_map_1;
  
  struct REVENUESUPPLIER2CUSTOMER1_entry {
    long REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY; long REVENUESUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit REVENUESUPPLIER2CUSTOMER1_entry() { /*REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY = 0L; REVENUESUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit REVENUESUPPLIER2CUSTOMER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY = c0; REVENUESUPPLIERSUPPLIER_SUPPKEY = c1; __av = c2; }
    REVENUESUPPLIER2CUSTOMER1_entry(const REVENUESUPPLIER2CUSTOMER1_entry& other) : REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY( other.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY ), REVENUESUPPLIERSUPPLIER_SUPPKEY( other.REVENUESUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER2CUSTOMER1_entry& modify(const long c0, const long c1) { REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY = c0; REVENUESUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    FORCE_INLINE REVENUESUPPLIER2CUSTOMER1_entry& modify0(const long c0) { REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY = c0;  return *this; }
    FORCE_INLINE REVENUESUPPLIER2CUSTOMER1_entry& modify1(const long c1) { REVENUESUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUESUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER2CUSTOMER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER2CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.REVENUESUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER2CUSTOMER1_entry& x, const REVENUESUPPLIER2CUSTOMER1_entry& y) {
      return x.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY == y.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY && x.REVENUESUPPLIERSUPPLIER_SUPPKEY == y.REVENUESUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  struct REVENUESUPPLIER2CUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER2CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER2CUSTOMER1_entry& x, const REVENUESUPPLIER2CUSTOMER1_entry& y) {
      return x.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY == y.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct REVENUESUPPLIER2CUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER2CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUESUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER2CUSTOMER1_entry& x, const REVENUESUPPLIER2CUSTOMER1_entry& y) {
      return x.REVENUESUPPLIERSUPPLIER_SUPPKEY == y.REVENUESUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER2CUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<REVENUESUPPLIER2CUSTOMER1_entry,DOUBLE_TYPE,REVENUESUPPLIER2CUSTOMER1_mapkey01_idxfn,true>,
    HashIndex<REVENUESUPPLIER2CUSTOMER1_entry,DOUBLE_TYPE,REVENUESUPPLIER2CUSTOMER1_mapkey0_idxfn,false>,
    HashIndex<REVENUESUPPLIER2CUSTOMER1_entry,DOUBLE_TYPE,REVENUESUPPLIER2CUSTOMER1_mapkey1_idxfn,false>
  > REVENUESUPPLIER2CUSTOMER1_map;
  typedef HashIndex<REVENUESUPPLIER2CUSTOMER1_entry,DOUBLE_TYPE,REVENUESUPPLIER2CUSTOMER1_mapkey01_idxfn,true> HashIndex_REVENUESUPPLIER2CUSTOMER1_map_01;
  typedef HashIndex<REVENUESUPPLIER2CUSTOMER1_entry,DOUBLE_TYPE,REVENUESUPPLIER2CUSTOMER1_mapkey0_idxfn,false> HashIndex_REVENUESUPPLIER2CUSTOMER1_map_0;
  typedef HashIndex<REVENUESUPPLIER2CUSTOMER1_entry,DOUBLE_TYPE,REVENUESUPPLIER2CUSTOMER1_mapkey1_idxfn,false> HashIndex_REVENUESUPPLIER2CUSTOMER1_map_1;
  
  struct REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry {
    long REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY; long REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY; long __av; 
    explicit REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry() { /*REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY = 0L; REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY = 0L; __av = 0L; */ }
    explicit REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry(const long c0, const long c1, const long c2) { REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY = c0; REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY = c1; __av = c2; }
    REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry(const REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& other) : REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY( other.REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY ), REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY( other.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& modify(const long c0, const long c1) { REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY = c0; REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    FORCE_INLINE REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& modify0(const long c0) { REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& modify1(const long c1) { REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& x, const REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& y) {
      return x.REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY == y.REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY && x.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY == y.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& x, const REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& y) {
      return x.REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY == y.REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& x, const REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry& y) {
      return x.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY == y.REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry,long,
    HashIndex<REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry,long,REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey01_idxfn,true>,
    HashIndex<REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry,long,REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey0_idxfn,false>,
    HashIndex<REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry,long,REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey1_idxfn,false>
  > REVENUESUPPLIER2CUSTOMER1LINEITEM1_map;
  typedef HashIndex<REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry,long,REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey01_idxfn,true> HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_01;
  typedef HashIndex<REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry,long,REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey0_idxfn,false> HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_0;
  typedef HashIndex<REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry,long,REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey1_idxfn,false> HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_1;
  
  struct REVENUELINEITEM1_T_2_entry {
    long C_NATIONKEY; long REVENUELINEITEMLINEITEM_ORDERKEY; long __av; 
    explicit REVENUELINEITEM1_T_2_entry() { /*C_NATIONKEY = 0L; REVENUELINEITEMLINEITEM_ORDERKEY = 0L; __av = 0L; */ }
    explicit REVENUELINEITEM1_T_2_entry(const long c0, const long c1, const long c2) { C_NATIONKEY = c0; REVENUELINEITEMLINEITEM_ORDERKEY = c1; __av = c2; }
    REVENUELINEITEM1_T_2_entry(const REVENUELINEITEM1_T_2_entry& other) : C_NATIONKEY( other.C_NATIONKEY ), REVENUELINEITEMLINEITEM_ORDERKEY( other.REVENUELINEITEMLINEITEM_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_T_2_entry& modify(const long c0, const long c1) { C_NATIONKEY = c0; REVENUELINEITEMLINEITEM_ORDERKEY = c1;  return *this; }
    FORCE_INLINE REVENUELINEITEM1_T_2_entry& modify1(const long c1) { REVENUELINEITEMLINEITEM_ORDERKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUELINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_T_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.REVENUELINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_2_entry& x, const REVENUELINEITEM1_T_2_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.REVENUELINEITEMLINEITEM_ORDERKEY == y.REVENUELINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct REVENUELINEITEM1_T_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUELINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_2_entry& x, const REVENUELINEITEM1_T_2_entry& y) {
      return x.REVENUELINEITEMLINEITEM_ORDERKEY == y.REVENUELINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_T_2_entry,long,
    HashIndex<REVENUELINEITEM1_T_2_entry,long,REVENUELINEITEM1_T_2_mapkey01_idxfn,true>,
    HashIndex<REVENUELINEITEM1_T_2_entry,long,REVENUELINEITEM1_T_2_mapkey1_idxfn,false>
  > REVENUELINEITEM1_T_2_map;
  typedef HashIndex<REVENUELINEITEM1_T_2_entry,long,REVENUELINEITEM1_T_2_mapkey01_idxfn,true> HashIndex_REVENUELINEITEM1_T_2_map_01;
  typedef HashIndex<REVENUELINEITEM1_T_2_entry,long,REVENUELINEITEM1_T_2_mapkey1_idxfn,false> HashIndex_REVENUELINEITEM1_T_2_map_1;
  
  struct REVENUELINEITEM1_T_3_entry {
    long REVENUELINEITEMLINEITEM_SUPPKEY; long C_NATIONKEY; long __av; 
    explicit REVENUELINEITEM1_T_3_entry() { /*REVENUELINEITEMLINEITEM_SUPPKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUELINEITEM1_T_3_entry(const long c0, const long c1, const long c2) { REVENUELINEITEMLINEITEM_SUPPKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUELINEITEM1_T_3_entry(const REVENUELINEITEM1_T_3_entry& other) : REVENUELINEITEMLINEITEM_SUPPKEY( other.REVENUELINEITEMLINEITEM_SUPPKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_T_3_entry& modify(const long c0, const long c1) { REVENUELINEITEMLINEITEM_SUPPKEY = c0; C_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUELINEITEM1_T_3_entry& modify0(const long c0) { REVENUELINEITEMLINEITEM_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUELINEITEMLINEITEM_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_T_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUELINEITEMLINEITEM_SUPPKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_3_entry& x, const REVENUELINEITEM1_T_3_entry& y) {
      return x.REVENUELINEITEMLINEITEM_SUPPKEY == y.REVENUELINEITEMLINEITEM_SUPPKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  struct REVENUELINEITEM1_T_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUELINEITEMLINEITEM_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_T_3_entry& x, const REVENUELINEITEM1_T_3_entry& y) {
      return x.REVENUELINEITEMLINEITEM_SUPPKEY == y.REVENUELINEITEMLINEITEM_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_T_3_entry,long,
    HashIndex<REVENUELINEITEM1_T_3_entry,long,REVENUELINEITEM1_T_3_mapkey01_idxfn,true>,
    HashIndex<REVENUELINEITEM1_T_3_entry,long,REVENUELINEITEM1_T_3_mapkey0_idxfn,false>
  > REVENUELINEITEM1_T_3_map;
  typedef HashIndex<REVENUELINEITEM1_T_3_entry,long,REVENUELINEITEM1_T_3_mapkey01_idxfn,true> HashIndex_REVENUELINEITEM1_T_3_map_01;
  typedef HashIndex<REVENUELINEITEM1_T_3_entry,long,REVENUELINEITEM1_T_3_mapkey0_idxfn,false> HashIndex_REVENUELINEITEM1_T_3_map_0;
  
  struct REVENUEORDERS3_T_2_entry {
    long C_NATIONKEY; long REVENUEORDERSORDERS_ORDERKEY; DOUBLE_TYPE __av; 
    explicit REVENUEORDERS3_T_2_entry() { /*C_NATIONKEY = 0L; REVENUEORDERSORDERS_ORDERKEY = 0L; __av = 0.0; */ }
    explicit REVENUEORDERS3_T_2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { C_NATIONKEY = c0; REVENUEORDERSORDERS_ORDERKEY = c1; __av = c2; }
    REVENUEORDERS3_T_2_entry(const REVENUEORDERS3_T_2_entry& other) : C_NATIONKEY( other.C_NATIONKEY ), REVENUEORDERSORDERS_ORDERKEY( other.REVENUEORDERSORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUEORDERS3_T_2_entry& modify(const long c0, const long c1) { C_NATIONKEY = c0; REVENUEORDERSORDERS_ORDERKEY = c1;  return *this; }
    FORCE_INLINE REVENUEORDERS3_T_2_entry& modify1(const long c1) { REVENUEORDERSORDERS_ORDERKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUEORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEORDERS3_T_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS3_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.REVENUEORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS3_T_2_entry& x, const REVENUEORDERS3_T_2_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.REVENUEORDERSORDERS_ORDERKEY == y.REVENUEORDERSORDERS_ORDERKEY;
    }
  };
  
  struct REVENUEORDERS3_T_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS3_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUEORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS3_T_2_entry& x, const REVENUEORDERS3_T_2_entry& y) {
      return x.REVENUEORDERSORDERS_ORDERKEY == y.REVENUEORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEORDERS3_T_2_entry,DOUBLE_TYPE,
    HashIndex<REVENUEORDERS3_T_2_entry,DOUBLE_TYPE,REVENUEORDERS3_T_2_mapkey01_idxfn,true>,
    HashIndex<REVENUEORDERS3_T_2_entry,DOUBLE_TYPE,REVENUEORDERS3_T_2_mapkey1_idxfn,false>
  > REVENUEORDERS3_T_2_map;
  typedef HashIndex<REVENUEORDERS3_T_2_entry,DOUBLE_TYPE,REVENUEORDERS3_T_2_mapkey01_idxfn,true> HashIndex_REVENUEORDERS3_T_2_map_01;
  typedef HashIndex<REVENUEORDERS3_T_2_entry,DOUBLE_TYPE,REVENUEORDERS3_T_2_mapkey1_idxfn,false> HashIndex_REVENUEORDERS3_T_2_map_1;
  
  struct REVENUEORDERS3_T_3_entry {
    long REVENUEORDERSORDERS_CUSTKEY; long C_NATIONKEY; long __av; 
    explicit REVENUEORDERS3_T_3_entry() { /*REVENUEORDERSORDERS_CUSTKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUEORDERS3_T_3_entry(const long c0, const long c1, const long c2) { REVENUEORDERSORDERS_CUSTKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUEORDERS3_T_3_entry(const REVENUEORDERS3_T_3_entry& other) : REVENUEORDERSORDERS_CUSTKEY( other.REVENUEORDERSORDERS_CUSTKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUEORDERS3_T_3_entry& modify(const long c0, const long c1) { REVENUEORDERSORDERS_CUSTKEY = c0; C_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUEORDERS3_T_3_entry& modify0(const long c0) { REVENUEORDERSORDERS_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUEORDERSORDERS_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEORDERS3_T_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS3_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUEORDERSORDERS_CUSTKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS3_T_3_entry& x, const REVENUEORDERS3_T_3_entry& y) {
      return x.REVENUEORDERSORDERS_CUSTKEY == y.REVENUEORDERSORDERS_CUSTKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  struct REVENUEORDERS3_T_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS3_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUEORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS3_T_3_entry& x, const REVENUEORDERS3_T_3_entry& y) {
      return x.REVENUEORDERSORDERS_CUSTKEY == y.REVENUEORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEORDERS3_T_3_entry,long,
    HashIndex<REVENUEORDERS3_T_3_entry,long,REVENUEORDERS3_T_3_mapkey01_idxfn,true>,
    HashIndex<REVENUEORDERS3_T_3_entry,long,REVENUEORDERS3_T_3_mapkey0_idxfn,false>
  > REVENUEORDERS3_T_3_map;
  typedef HashIndex<REVENUEORDERS3_T_3_entry,long,REVENUEORDERS3_T_3_mapkey01_idxfn,true> HashIndex_REVENUEORDERS3_T_3_map_01;
  typedef HashIndex<REVENUEORDERS3_T_3_entry,long,REVENUEORDERS3_T_3_mapkey0_idxfn,false> HashIndex_REVENUEORDERS3_T_3_map_0;
  
  struct REVENUECUSTOMER1_entry {
    long REVENUECUSTOMERCUSTOMER_NATIONKEY; STRING_TYPE N_NAME; long __av; 
    explicit REVENUECUSTOMER1_entry() { /*REVENUECUSTOMERCUSTOMER_NATIONKEY = 0L; N_NAME = ""; __av = 0L; */ }
    explicit REVENUECUSTOMER1_entry(const long c0, const STRING_TYPE& c1, const long c2) { REVENUECUSTOMERCUSTOMER_NATIONKEY = c0; N_NAME = c1; __av = c2; }
    REVENUECUSTOMER1_entry(const REVENUECUSTOMER1_entry& other) : REVENUECUSTOMERCUSTOMER_NATIONKEY( other.REVENUECUSTOMERCUSTOMER_NATIONKEY ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1_entry& modify(const long c0, const STRING_TYPE& c1) { REVENUECUSTOMERCUSTOMER_NATIONKEY = c0; N_NAME = c1;  return *this; }
    FORCE_INLINE REVENUECUSTOMER1_entry& modify0(const long c0) { REVENUECUSTOMERCUSTOMER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUECUSTOMERCUSTOMER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUECUSTOMERCUSTOMER_NATIONKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_entry& x, const REVENUECUSTOMER1_entry& y) {
      return x.REVENUECUSTOMERCUSTOMER_NATIONKEY == y.REVENUECUSTOMERCUSTOMER_NATIONKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  struct REVENUECUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUECUSTOMERCUSTOMER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_entry& x, const REVENUECUSTOMER1_entry& y) {
      return x.REVENUECUSTOMERCUSTOMER_NATIONKEY == y.REVENUECUSTOMERCUSTOMER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1_entry,long,
    HashIndex<REVENUECUSTOMER1_entry,long,REVENUECUSTOMER1_mapkey01_idxfn,true>,
    HashIndex<REVENUECUSTOMER1_entry,long,REVENUECUSTOMER1_mapkey0_idxfn,false>
  > REVENUECUSTOMER1_map;
  typedef HashIndex<REVENUECUSTOMER1_entry,long,REVENUECUSTOMER1_mapkey01_idxfn,true> HashIndex_REVENUECUSTOMER1_map_01;
  typedef HashIndex<REVENUECUSTOMER1_entry,long,REVENUECUSTOMER1_mapkey0_idxfn,false> HashIndex_REVENUECUSTOMER1_map_0;
  
  struct REVENUECUSTOMER2_entry {
    long REVENUECUSTOMERCUSTOMER_CUSTKEY; long REVENUECUSTOMERCUSTOMER_NATIONKEY; DOUBLE_TYPE __av; 
    explicit REVENUECUSTOMER2_entry() { /*REVENUECUSTOMERCUSTOMER_CUSTKEY = 0L; REVENUECUSTOMERCUSTOMER_NATIONKEY = 0L; __av = 0.0; */ }
    explicit REVENUECUSTOMER2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { REVENUECUSTOMERCUSTOMER_CUSTKEY = c0; REVENUECUSTOMERCUSTOMER_NATIONKEY = c1; __av = c2; }
    REVENUECUSTOMER2_entry(const REVENUECUSTOMER2_entry& other) : REVENUECUSTOMERCUSTOMER_CUSTKEY( other.REVENUECUSTOMERCUSTOMER_CUSTKEY ), REVENUECUSTOMERCUSTOMER_NATIONKEY( other.REVENUECUSTOMERCUSTOMER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER2_entry& modify(const long c0, const long c1) { REVENUECUSTOMERCUSTOMER_CUSTKEY = c0; REVENUECUSTOMERCUSTOMER_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUECUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUECUSTOMERCUSTOMER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUECUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.REVENUECUSTOMERCUSTOMER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER2_entry& x, const REVENUECUSTOMER2_entry& y) {
      return x.REVENUECUSTOMERCUSTOMER_CUSTKEY == y.REVENUECUSTOMERCUSTOMER_CUSTKEY && x.REVENUECUSTOMERCUSTOMER_NATIONKEY == y.REVENUECUSTOMERCUSTOMER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER2_entry,DOUBLE_TYPE,
    HashIndex<REVENUECUSTOMER2_entry,DOUBLE_TYPE,REVENUECUSTOMER2_mapkey01_idxfn,true>
  > REVENUECUSTOMER2_map;
  typedef HashIndex<REVENUECUSTOMER2_entry,DOUBLE_TYPE,REVENUECUSTOMER2_mapkey01_idxfn,true> HashIndex_REVENUECUSTOMER2_map_01;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
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
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_REVENUELINEITEM1_T_2_map_1* i1 = static_cast<HashIndex_REVENUELINEITEM1_T_2_map_1*>(REVENUELINEITEM1_T_2.index[1]);
          const HASH_RES_t h2 = REVENUELINEITEM1_T_2_mapkey1_idxfn::hash(se4.modify1(lineitem_orderkey));
          HashIndex_REVENUELINEITEM1_T_2_map_1::IdxNode* n1 = static_cast<HashIndex_REVENUELINEITEM1_T_2_map_1::IdxNode*>(i1->slice(se4, h2));
          REVENUELINEITEM1_T_2_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long c_nationkey = e1->C_NATIONKEY;
              long v1 = e1->__av;
              { //slice 
                const HashIndex_REVENUECUSTOMER1_map_0* i2 = static_cast<HashIndex_REVENUECUSTOMER1_map_0*>(REVENUECUSTOMER1.index[1]);
                const HASH_RES_t h1 = REVENUECUSTOMER1_mapkey0_idxfn::hash(se3.modify0(c_nationkey));
                HashIndex_REVENUECUSTOMER1_map_0::IdxNode* n2 = static_cast<HashIndex_REVENUECUSTOMER1_map_0::IdxNode*>(i2->slice(se3, h1));
                REVENUECUSTOMER1_entry* e2;
               
                if (n2 && (e2 = n2->obj)) {
                  do {                
                    STRING_TYPE n_name = e2->N_NAME;
                    long v2 = e2->__av;
                    REVENUE.addOrDelOnZero(se1.modify(n_name),((v1 * (REVENUELINEITEM1_T_3.getValueOrDefault(se2.modify(lineitem_suppkey,c_nationkey)) * v2)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
                    n2 = n2->nxt;
                  } while (n2 && (e2 = n2->obj) && h1 == n2->hash &&  REVENUECUSTOMER1_mapkey0_idxfn::equals(se3, *e2)); 
                }
              }
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h2 == n1->hash &&  REVENUELINEITEM1_T_2_mapkey1_idxfn::equals(se4, *e1)); 
          }
        }{ //slice 
          const HashIndex_REVENUELINEITEM1_T_2_map_1* i3 = static_cast<HashIndex_REVENUELINEITEM1_T_2_map_1*>(REVENUELINEITEM1_T_2.index[1]);
          const HASH_RES_t h3 = REVENUELINEITEM1_T_2_mapkey1_idxfn::hash(se6.modify1(lineitem_orderkey));
          HashIndex_REVENUELINEITEM1_T_2_map_1::IdxNode* n3 = static_cast<HashIndex_REVENUELINEITEM1_T_2_map_1::IdxNode*>(i3->slice(se6, h3));
          REVENUELINEITEM1_T_2_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              long revenuesuppliersupplier_nationkey = e3->C_NATIONKEY;
              long v3 = e3->__av;
              REVENUESUPPLIER2.addOrDelOnZero(se5.modify(revenuesuppliersupplier_nationkey,lineitem_suppkey),(v3 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  REVENUELINEITEM1_T_2_mapkey1_idxfn::equals(se6, *e3)); 
          }
        }REVENUESUPPLIER2ORDERS4.addOrDelOnZero(se7.modify(lineitem_orderkey,lineitem_suppkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount))));
        { //slice 
          const HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_0* i4 = static_cast<HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_0*>(REVENUESUPPLIER2CUSTOMER1LINEITEM1.index[1]);
          const HASH_RES_t h4 = REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey0_idxfn::hash(se9.modify0(lineitem_orderkey));
          HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_0::IdxNode* n4 = static_cast<HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_0::IdxNode*>(i4->slice(se9, h4));
          REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long revenuesupplier2customercustomer_custkey = e4->REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY;
              long v4 = e4->__av;
              REVENUESUPPLIER2CUSTOMER1.addOrDelOnZero(se8.modify(revenuesupplier2customercustomer_custkey,lineitem_suppkey),(v4 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey0_idxfn::equals(se9, *e4)); 
          }
        }{ //slice 
          const HashIndex_REVENUELINEITEM1_T_3_map_0* i5 = static_cast<HashIndex_REVENUELINEITEM1_T_3_map_0*>(REVENUELINEITEM1_T_3.index[1]);
          const HASH_RES_t h5 = REVENUELINEITEM1_T_3_mapkey0_idxfn::hash(se11.modify0(lineitem_suppkey));
          HashIndex_REVENUELINEITEM1_T_3_map_0::IdxNode* n5 = static_cast<HashIndex_REVENUELINEITEM1_T_3_map_0::IdxNode*>(i5->slice(se11, h5));
          REVENUELINEITEM1_T_3_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long c_nationkey = e5->C_NATIONKEY;
              long v5 = e5->__av;
              REVENUEORDERS3_T_2.addOrDelOnZero(se10.modify(c_nationkey,lineitem_orderkey),(v5 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  REVENUELINEITEM1_T_3_mapkey0_idxfn::equals(se11, *e5)); 
          }
        }{ //slice 
          const HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_0* i6 = static_cast<HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_0*>(REVENUESUPPLIER2CUSTOMER1LINEITEM1.index[1]);
          const HASH_RES_t h7 = REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey0_idxfn::hash(se14.modify0(lineitem_orderkey));
          HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_0::IdxNode* n6 = static_cast<HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_0::IdxNode*>(i6->slice(se14, h7));
          REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              long revenuecustomercustomer_custkey = e6->REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY;
              long v6 = e6->__av;
              { //slice 
                const HashIndex_REVENUELINEITEM1_T_3_map_0* i7 = static_cast<HashIndex_REVENUELINEITEM1_T_3_map_0*>(REVENUELINEITEM1_T_3.index[1]);
                const HASH_RES_t h6 = REVENUELINEITEM1_T_3_mapkey0_idxfn::hash(se13.modify0(lineitem_suppkey));
                HashIndex_REVENUELINEITEM1_T_3_map_0::IdxNode* n7 = static_cast<HashIndex_REVENUELINEITEM1_T_3_map_0::IdxNode*>(i7->slice(se13, h6));
                REVENUELINEITEM1_T_3_entry* e7;
               
                if (n7 && (e7 = n7->obj)) {
                  do {                
                    long revenuecustomercustomer_nationkey = e7->C_NATIONKEY;
                    long v7 = e7->__av;
                    REVENUECUSTOMER2.addOrDelOnZero(se12.modify(revenuecustomercustomer_custkey,revenuecustomercustomer_nationkey),(v6 * (v7 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
                    n7 = n7->nxt;
                  } while (n7 && (e7 = n7->obj) && h6 == n7->hash &&  REVENUELINEITEM1_T_3_mapkey0_idxfn::equals(se13, *e7)); 
                }
              }
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h7 == n6->hash &&  REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey0_idxfn::equals(se14, *e6)); 
          }
        }
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_REVENUEORDERS3_T_3_map_0* i8 = static_cast<HashIndex_REVENUEORDERS3_T_3_map_0*>(REVENUEORDERS3_T_3.index[1]);
          const HASH_RES_t h9 = REVENUEORDERS3_T_3_mapkey0_idxfn::hash(se18.modify0(orders_custkey));
          HashIndex_REVENUEORDERS3_T_3_map_0::IdxNode* n8 = static_cast<HashIndex_REVENUEORDERS3_T_3_map_0::IdxNode*>(i8->slice(se18, h9));
          REVENUEORDERS3_T_3_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              long c_nationkey = e8->C_NATIONKEY;
              long v8 = e8->__av;
              { //slice 
                const HashIndex_REVENUECUSTOMER1_map_0* i9 = static_cast<HashIndex_REVENUECUSTOMER1_map_0*>(REVENUECUSTOMER1.index[1]);
                const HASH_RES_t h8 = REVENUECUSTOMER1_mapkey0_idxfn::hash(se17.modify0(c_nationkey));
                HashIndex_REVENUECUSTOMER1_map_0::IdxNode* n9 = static_cast<HashIndex_REVENUECUSTOMER1_map_0::IdxNode*>(i9->slice(se17, h8));
                REVENUECUSTOMER1_entry* e9;
               
                if (n9 && (e9 = n9->obj)) {
                  do {                
                    STRING_TYPE n_name = e9->N_NAME;
                    long v9 = e9->__av;
                    (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUE.addOrDelOnZero(se15.modify(n_name),(v8 * (REVENUEORDERS3_T_2.getValueOrDefault(se16.modify(c_nationkey,orders_orderkey)) * v9))) : (void)0);
                    n9 = n9->nxt;
                  } while (n9 && (e9 = n9->obj) && h8 == n9->hash &&  REVENUECUSTOMER1_mapkey0_idxfn::equals(se17, *e9)); 
                }
              }
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h9 == n8->hash &&  REVENUEORDERS3_T_3_mapkey0_idxfn::equals(se18, *e8)); 
          }
        }{ //slice 
          const HashIndex_REVENUEORDERS3_T_3_map_0* i10 = static_cast<HashIndex_REVENUEORDERS3_T_3_map_0*>(REVENUEORDERS3_T_3.index[1]);
          const HASH_RES_t h11 = REVENUEORDERS3_T_3_mapkey0_idxfn::hash(se21.modify0(orders_custkey));
          HashIndex_REVENUEORDERS3_T_3_map_0::IdxNode* n10 = static_cast<HashIndex_REVENUEORDERS3_T_3_map_0::IdxNode*>(i10->slice(se21, h11));
          REVENUEORDERS3_T_3_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              long revenuesuppliersupplier_nationkey = e10->C_NATIONKEY;
              long v10 = e10->__av;
              { //slice 
                const HashIndex_REVENUESUPPLIER2ORDERS4_map_0* i11 = static_cast<HashIndex_REVENUESUPPLIER2ORDERS4_map_0*>(REVENUESUPPLIER2ORDERS4.index[1]);
                const HASH_RES_t h10 = REVENUESUPPLIER2ORDERS4_mapkey0_idxfn::hash(se20.modify0(orders_orderkey));
                HashIndex_REVENUESUPPLIER2ORDERS4_map_0::IdxNode* n11 = static_cast<HashIndex_REVENUESUPPLIER2ORDERS4_map_0::IdxNode*>(i11->slice(se20, h10));
                REVENUESUPPLIER2ORDERS4_entry* e11;
               
                if (n11 && (e11 = n11->obj)) {
                  do {                
                    long revenuesuppliersupplier_suppkey = e11->REVENUESUPPLIERSUPPLIER_SUPPKEY;
                    DOUBLE_TYPE v11 = e11->__av;
                    (/*if */(c2 > orders_orderdate && orders_orderdate >= c1) ? REVENUESUPPLIER2.addOrDelOnZero(se19.modify(revenuesuppliersupplier_nationkey,revenuesuppliersupplier_suppkey),(v10 * v11)) : (void)0);
                    n11 = n11->nxt;
                  } while (n11 && (e11 = n11->obj) && h10 == n11->hash &&  REVENUESUPPLIER2ORDERS4_mapkey0_idxfn::equals(se20, *e11)); 
                }
              }
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h11 == n10->hash &&  REVENUEORDERS3_T_3_mapkey0_idxfn::equals(se21, *e10)); 
          }
        }{ //slice 
          const HashIndex_REVENUESUPPLIER2ORDERS4_map_0* i12 = static_cast<HashIndex_REVENUESUPPLIER2ORDERS4_map_0*>(REVENUESUPPLIER2ORDERS4.index[1]);
          const HASH_RES_t h12 = REVENUESUPPLIER2ORDERS4_mapkey0_idxfn::hash(se23.modify0(orders_orderkey));
          HashIndex_REVENUESUPPLIER2ORDERS4_map_0::IdxNode* n12 = static_cast<HashIndex_REVENUESUPPLIER2ORDERS4_map_0::IdxNode*>(i12->slice(se23, h12));
          REVENUESUPPLIER2ORDERS4_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              long revenuesuppliersupplier_suppkey = e12->REVENUESUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v12 = e12->__av;
              (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUESUPPLIER2CUSTOMER1.addOrDelOnZero(se22.modify(orders_custkey,revenuesuppliersupplier_suppkey),v12) : (void)0);
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h12 == n12->hash &&  REVENUESUPPLIER2ORDERS4_mapkey0_idxfn::equals(se23, *e12)); 
          }
        }(/*if */(c2 > orders_orderdate && orders_orderdate >= c1) ? REVENUESUPPLIER2CUSTOMER1LINEITEM1.addOrDelOnZero(se24.modify(orders_orderkey,orders_custkey),1L) : (void)0);
        { //slice 
          const HashIndex_REVENUEORDERS3_T_3_map_0* i13 = static_cast<HashIndex_REVENUEORDERS3_T_3_map_0*>(REVENUEORDERS3_T_3.index[1]);
          const HASH_RES_t h13 = REVENUEORDERS3_T_3_mapkey0_idxfn::hash(se26.modify0(orders_custkey));
          HashIndex_REVENUEORDERS3_T_3_map_0::IdxNode* n13 = static_cast<HashIndex_REVENUEORDERS3_T_3_map_0::IdxNode*>(i13->slice(se26, h13));
          REVENUEORDERS3_T_3_entry* e13;
         
          if (n13 && (e13 = n13->obj)) {
            do {                
              long c_nationkey = e13->C_NATIONKEY;
              long v13 = e13->__av;
              (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUELINEITEM1_T_2.addOrDelOnZero(se25.modify(c_nationkey,orders_orderkey),v13) : (void)0);
              n13 = n13->nxt;
            } while (n13 && (e13 = n13->obj) && h13 == n13->hash &&  REVENUEORDERS3_T_3_mapkey0_idxfn::equals(se26, *e13)); 
          }
        }{ //slice 
          const HashIndex_REVENUEORDERS3_T_2_map_1* i14 = static_cast<HashIndex_REVENUEORDERS3_T_2_map_1*>(REVENUEORDERS3_T_2.index[1]);
          const HASH_RES_t h14 = REVENUEORDERS3_T_2_mapkey1_idxfn::hash(se28.modify1(orders_orderkey));
          HashIndex_REVENUEORDERS3_T_2_map_1::IdxNode* n14 = static_cast<HashIndex_REVENUEORDERS3_T_2_map_1::IdxNode*>(i14->slice(se28, h14));
          REVENUEORDERS3_T_2_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              long revenuecustomercustomer_nationkey = e14->C_NATIONKEY;
              DOUBLE_TYPE v14 = e14->__av;
              (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? REVENUECUSTOMER2.addOrDelOnZero(se27.modify(orders_custkey,revenuecustomercustomer_nationkey),v14) : (void)0);
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h14 == n14->hash &&  REVENUEORDERS3_T_2_mapkey1_idxfn::equals(se28, *e14)); 
          }
        }
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_REVENUECUSTOMER1_map_0* i15 = static_cast<HashIndex_REVENUECUSTOMER1_map_0*>(REVENUECUSTOMER1.index[1]);
          const HASH_RES_t h15 = REVENUECUSTOMER1_mapkey0_idxfn::hash(se31.modify0(customer_nationkey));
          HashIndex_REVENUECUSTOMER1_map_0::IdxNode* n15 = static_cast<HashIndex_REVENUECUSTOMER1_map_0::IdxNode*>(i15->slice(se31, h15));
          REVENUECUSTOMER1_entry* e15;
         
          if (n15 && (e15 = n15->obj)) {
            do {                
              STRING_TYPE n_name = e15->N_NAME;
              long v15 = e15->__av;
              REVENUE.addOrDelOnZero(se29.modify(n_name),(REVENUECUSTOMER2.getValueOrDefault(se30.modify(customer_custkey,customer_nationkey)) * v15));
              n15 = n15->nxt;
            } while (n15 && (e15 = n15->obj) && h15 == n15->hash &&  REVENUECUSTOMER1_mapkey0_idxfn::equals(se31, *e15)); 
          }
        }{ //slice 
          const HashIndex_REVENUESUPPLIER2CUSTOMER1_map_0* i16 = static_cast<HashIndex_REVENUESUPPLIER2CUSTOMER1_map_0*>(REVENUESUPPLIER2CUSTOMER1.index[1]);
          const HASH_RES_t h16 = REVENUESUPPLIER2CUSTOMER1_mapkey0_idxfn::hash(se33.modify0(customer_custkey));
          HashIndex_REVENUESUPPLIER2CUSTOMER1_map_0::IdxNode* n16 = static_cast<HashIndex_REVENUESUPPLIER2CUSTOMER1_map_0::IdxNode*>(i16->slice(se33, h16));
          REVENUESUPPLIER2CUSTOMER1_entry* e16;
         
          if (n16 && (e16 = n16->obj)) {
            do {                
              long revenuesuppliersupplier_suppkey = e16->REVENUESUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v16 = e16->__av;
              REVENUESUPPLIER2.addOrDelOnZero(se32.modify(customer_nationkey,revenuesuppliersupplier_suppkey),v16);
              n16 = n16->nxt;
            } while (n16 && (e16 = n16->obj) && h16 == n16->hash &&  REVENUESUPPLIER2CUSTOMER1_mapkey0_idxfn::equals(se33, *e16)); 
          }
        }{ //slice 
          const HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_1* i17 = static_cast<HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_1*>(REVENUESUPPLIER2CUSTOMER1LINEITEM1.index[2]);
          const HASH_RES_t h17 = REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey1_idxfn::hash(se35.modify1(customer_custkey));
          HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_1::IdxNode* n17 = static_cast<HashIndex_REVENUESUPPLIER2CUSTOMER1LINEITEM1_map_1::IdxNode*>(i17->slice(se35, h17));
          REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry* e17;
         
          if (n17 && (e17 = n17->obj)) {
            do {                
              long revenuelineitemlineitem_orderkey = e17->REVENUESUPPLIER2CUSTOMER1LINEITEMLINEITEM_ORDERKEY;
              long v17 = e17->__av;
              REVENUELINEITEM1_T_2.addOrDelOnZero(se34.modify(customer_nationkey,revenuelineitemlineitem_orderkey),v17);
              n17 = n17->nxt;
            } while (n17 && (e17 = n17->obj) && h17 == n17->hash &&  REVENUESUPPLIER2CUSTOMER1LINEITEM1_mapkey1_idxfn::equals(se35, *e17)); 
          }
        }REVENUEORDERS3_T_3.addOrDelOnZero(se36.modify(customer_custkey,customer_nationkey),1L);
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_REVENUECUSTOMER1_map_0* i18 = static_cast<HashIndex_REVENUECUSTOMER1_map_0*>(REVENUECUSTOMER1.index[1]);
          const HASH_RES_t h18 = REVENUECUSTOMER1_mapkey0_idxfn::hash(se39.modify0(supplier_nationkey));
          HashIndex_REVENUECUSTOMER1_map_0::IdxNode* n18 = static_cast<HashIndex_REVENUECUSTOMER1_map_0::IdxNode*>(i18->slice(se39, h18));
          REVENUECUSTOMER1_entry* e18;
         
          if (n18 && (e18 = n18->obj)) {
            do {                
              STRING_TYPE n_name = e18->N_NAME;
              long v18 = e18->__av;
              REVENUE.addOrDelOnZero(se37.modify(n_name),(REVENUESUPPLIER2.getValueOrDefault(se38.modify(supplier_nationkey,supplier_suppkey)) * v18));
              n18 = n18->nxt;
            } while (n18 && (e18 = n18->obj) && h18 == n18->hash &&  REVENUECUSTOMER1_mapkey0_idxfn::equals(se39, *e18)); 
          }
        }REVENUELINEITEM1_T_3.addOrDelOnZero(se40.modify(supplier_suppkey,supplier_nationkey),1L);
        { //slice 
          const HashIndex_REVENUESUPPLIER2ORDERS4_map_1* i19 = static_cast<HashIndex_REVENUESUPPLIER2ORDERS4_map_1*>(REVENUESUPPLIER2ORDERS4.index[2]);
          const HASH_RES_t h19 = REVENUESUPPLIER2ORDERS4_mapkey1_idxfn::hash(se42.modify1(supplier_suppkey));
          HashIndex_REVENUESUPPLIER2ORDERS4_map_1::IdxNode* n19 = static_cast<HashIndex_REVENUESUPPLIER2ORDERS4_map_1::IdxNode*>(i19->slice(se42, h19));
          REVENUESUPPLIER2ORDERS4_entry* e19;
         
          if (n19 && (e19 = n19->obj)) {
            do {                
              long revenueordersorders_orderkey = e19->REVENUESUPPLIER2ORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v19 = e19->__av;
              REVENUEORDERS3_T_2.addOrDelOnZero(se41.modify(supplier_nationkey,revenueordersorders_orderkey),v19);
              n19 = n19->nxt;
            } while (n19 && (e19 = n19->obj) && h19 == n19->hash &&  REVENUESUPPLIER2ORDERS4_mapkey1_idxfn::equals(se42, *e19)); 
          }
        }{ //slice 
          const HashIndex_REVENUESUPPLIER2CUSTOMER1_map_1* i20 = static_cast<HashIndex_REVENUESUPPLIER2CUSTOMER1_map_1*>(REVENUESUPPLIER2CUSTOMER1.index[2]);
          const HASH_RES_t h20 = REVENUESUPPLIER2CUSTOMER1_mapkey1_idxfn::hash(se44.modify1(supplier_suppkey));
          HashIndex_REVENUESUPPLIER2CUSTOMER1_map_1::IdxNode* n20 = static_cast<HashIndex_REVENUESUPPLIER2CUSTOMER1_map_1::IdxNode*>(i20->slice(se44, h20));
          REVENUESUPPLIER2CUSTOMER1_entry* e20;
         
          if (n20 && (e20 = n20->obj)) {
            do {                
              long revenuecustomercustomer_custkey = e20->REVENUESUPPLIER2CUSTOMERCUSTOMER_CUSTKEY;
              DOUBLE_TYPE v20 = e20->__av;
              REVENUECUSTOMER2.addOrDelOnZero(se43.modify(revenuecustomercustomer_custkey,supplier_nationkey),v20);
              n20 = n20->nxt;
            } while (n20 && (e20 = n20->obj) && h20 == n20->hash &&  REVENUESUPPLIER2CUSTOMER1_mapkey1_idxfn::equals(se44, *e20)); 
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        REVENUECUSTOMER1.clear();
        STRING_TYPE l1 = c3;
        {  // foreach
          const HashIndex_NATION_map_0123* i21 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n21; 
          NATION_entry* e21;
        
          for (size_t i = 0; i < i21->size_; i++)
          {
            n21 = i21->buckets_ + i;
            while (n21 && (e21 = n21->obj))
            {
                long revenuecustomercustomer_nationkey = e21->NATION_NATIONKEY;
                STRING_TYPE n_name = e21->NATION_NAME;
                long n_regionkey = e21->NATION_REGIONKEY;
                STRING_TYPE n_comment = e21->NATION_COMMENT;
                long v21 = e21->__av;
                { //slice 
                  const HashIndex_REGION_map_01* i22 = static_cast<HashIndex_REGION_map_01*>(REGION.index[1]);
                  const HASH_RES_t h21 = REGION_mapkey01_idxfn::hash(se46.modify01(n_regionkey, l1));
                  HashIndex_REGION_map_01::IdxNode* n22 = static_cast<HashIndex_REGION_map_01::IdxNode*>(i22->slice(se46, h21));
                  REGION_entry* e22;
                 
                  if (n22 && (e22 = n22->obj)) {
                    do {                
                      STRING_TYPE r_comment = e22->REGION_COMMENT;
                      long v22 = e22->__av;
                      REVENUECUSTOMER1.addOrDelOnZero(se45.modify(revenuecustomercustomer_nationkey,n_name),(v21 * v22));
                      n22 = n22->nxt;
                    } while (n22 && (e22 = n22->obj) && h21 == n22->hash &&  REGION_mapkey01_idxfn::equals(se46, *e22)); 
                  }
                }
              n21 = n21->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    REVENUE_entry se1;
    REVENUELINEITEM1_T_3_entry se2;
    REVENUECUSTOMER1_entry se3;
    REVENUELINEITEM1_T_2_entry se4;
    REVENUESUPPLIER2_entry se5;
    REVENUELINEITEM1_T_2_entry se6;
    REVENUESUPPLIER2ORDERS4_entry se7;
    REVENUESUPPLIER2CUSTOMER1_entry se8;
    REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry se9;
    REVENUEORDERS3_T_2_entry se10;
    REVENUELINEITEM1_T_3_entry se11;
    REVENUECUSTOMER2_entry se12;
    REVENUELINEITEM1_T_3_entry se13;
    REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry se14;
    REVENUE_entry se15;
    REVENUEORDERS3_T_2_entry se16;
    REVENUECUSTOMER1_entry se17;
    REVENUEORDERS3_T_3_entry se18;
    REVENUESUPPLIER2_entry se19;
    REVENUESUPPLIER2ORDERS4_entry se20;
    REVENUEORDERS3_T_3_entry se21;
    REVENUESUPPLIER2CUSTOMER1_entry se22;
    REVENUESUPPLIER2ORDERS4_entry se23;
    REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry se24;
    REVENUELINEITEM1_T_2_entry se25;
    REVENUEORDERS3_T_3_entry se26;
    REVENUECUSTOMER2_entry se27;
    REVENUEORDERS3_T_2_entry se28;
    REVENUE_entry se29;
    REVENUECUSTOMER2_entry se30;
    REVENUECUSTOMER1_entry se31;
    REVENUESUPPLIER2_entry se32;
    REVENUESUPPLIER2CUSTOMER1_entry se33;
    REVENUELINEITEM1_T_2_entry se34;
    REVENUESUPPLIER2CUSTOMER1LINEITEM1_entry se35;
    REVENUEORDERS3_T_3_entry se36;
    REVENUE_entry se37;
    REVENUESUPPLIER2_entry se38;
    REVENUECUSTOMER1_entry se39;
    REVENUELINEITEM1_T_3_entry se40;
    REVENUEORDERS3_T_2_entry se41;
    REVENUESUPPLIER2ORDERS4_entry se42;
    REVENUECUSTOMER2_entry se43;
    REVENUESUPPLIER2CUSTOMER1_entry se44;
    REVENUECUSTOMER1_entry se45;
    REGION_entry se46;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REGION_map REGION;
    REVENUESUPPLIER2_map REVENUESUPPLIER2;
    REVENUESUPPLIER2ORDERS4_map REVENUESUPPLIER2ORDERS4;
    REVENUESUPPLIER2CUSTOMER1_map REVENUESUPPLIER2CUSTOMER1;
    REVENUESUPPLIER2CUSTOMER1LINEITEM1_map REVENUESUPPLIER2CUSTOMER1LINEITEM1;
    REVENUELINEITEM1_T_2_map REVENUELINEITEM1_T_2;
    REVENUELINEITEM1_T_3_map REVENUELINEITEM1_T_3;
    REVENUEORDERS3_T_2_map REVENUEORDERS3_T_2;
    REVENUEORDERS3_T_3_map REVENUEORDERS3_T_3;
    REVENUECUSTOMER1_map REVENUECUSTOMER1;
    REVENUECUSTOMER2_map REVENUECUSTOMER2;
    
    /*const static*/ long c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
  
  };

}
