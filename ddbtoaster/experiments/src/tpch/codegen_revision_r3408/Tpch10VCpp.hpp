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
  
  struct REVENUELINEITEM2_entry {
    long REVENUELINEITEMLINEITEM_ORDERKEY; long C_CUSTKEY; STRING_TYPE C_NAME; STRING_TYPE C_ADDRESS; STRING_TYPE C_PHONE; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE C_COMMENT; STRING_TYPE N_NAME; long __av; 
    explicit REVENUELINEITEM2_entry() { /*REVENUELINEITEMLINEITEM_ORDERKEY = 0L; C_CUSTKEY = 0L; C_NAME = ""; C_ADDRESS = ""; C_PHONE = ""; C_ACCTBAL = 0.0; C_COMMENT = ""; N_NAME = ""; __av = 0L; */ }
    explicit REVENUELINEITEM2_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const STRING_TYPE& c7, const long c8) { REVENUELINEITEMLINEITEM_ORDERKEY = c0; C_CUSTKEY = c1; C_NAME = c2; C_ADDRESS = c3; C_PHONE = c4; C_ACCTBAL = c5; C_COMMENT = c6; N_NAME = c7; __av = c8; }
    REVENUELINEITEM2_entry(const REVENUELINEITEM2_entry& other) : REVENUELINEITEMLINEITEM_ORDERKEY( other.REVENUELINEITEMLINEITEM_ORDERKEY ), C_CUSTKEY( other.C_CUSTKEY ), C_NAME( other.C_NAME ), C_ADDRESS( other.C_ADDRESS ), C_PHONE( other.C_PHONE ), C_ACCTBAL( other.C_ACCTBAL ), C_COMMENT( other.C_COMMENT ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM2_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const STRING_TYPE& c7) { REVENUELINEITEMLINEITEM_ORDERKEY = c0; C_CUSTKEY = c1; C_NAME = c2; C_ADDRESS = c3; C_PHONE = c4; C_ACCTBAL = c5; C_COMMENT = c6; N_NAME = c7;  return *this; }
    FORCE_INLINE REVENUELINEITEM2_entry& modify0(const long c0) { REVENUELINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUELINEITEMLINEITEM_ORDERKEY);
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
  struct REVENUELINEITEM2_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUELINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.C_ADDRESS);
      hash_combine(h, e.C_PHONE);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.C_COMMENT);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM2_entry& x, const REVENUELINEITEM2_entry& y) {
      return x.REVENUELINEITEMLINEITEM_ORDERKEY == y.REVENUELINEITEMLINEITEM_ORDERKEY && x.C_CUSTKEY == y.C_CUSTKEY && x.C_NAME == y.C_NAME && x.C_ADDRESS == y.C_ADDRESS && x.C_PHONE == y.C_PHONE && x.C_ACCTBAL == y.C_ACCTBAL && x.C_COMMENT == y.C_COMMENT && x.N_NAME == y.N_NAME;
    }
  };
  
  struct REVENUELINEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUELINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM2_entry& x, const REVENUELINEITEM2_entry& y) {
      return x.REVENUELINEITEMLINEITEM_ORDERKEY == y.REVENUELINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM2_entry,long,
    HashIndex<REVENUELINEITEM2_entry,long,REVENUELINEITEM2_mapkey01234567_idxfn,true>,
    HashIndex<REVENUELINEITEM2_entry,long,REVENUELINEITEM2_mapkey0_idxfn,false>
  > REVENUELINEITEM2_map;
  typedef HashIndex<REVENUELINEITEM2_entry,long,REVENUELINEITEM2_mapkey01234567_idxfn,true> HashIndex_REVENUELINEITEM2_map_01234567;
  typedef HashIndex<REVENUELINEITEM2_entry,long,REVENUELINEITEM2_mapkey0_idxfn,false> HashIndex_REVENUELINEITEM2_map_0;
  
  struct REVENUELINEITEM2CUSTOMER1_entry {
    long REVENUELINEITEMLINEITEM_ORDERKEY; long REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY; long __av; 
    explicit REVENUELINEITEM2CUSTOMER1_entry() { /*REVENUELINEITEMLINEITEM_ORDERKEY = 0L; REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY = 0L; __av = 0L; */ }
    explicit REVENUELINEITEM2CUSTOMER1_entry(const long c0, const long c1, const long c2) { REVENUELINEITEMLINEITEM_ORDERKEY = c0; REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY = c1; __av = c2; }
    REVENUELINEITEM2CUSTOMER1_entry(const REVENUELINEITEM2CUSTOMER1_entry& other) : REVENUELINEITEMLINEITEM_ORDERKEY( other.REVENUELINEITEMLINEITEM_ORDERKEY ), REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY( other.REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM2CUSTOMER1_entry& modify(const long c0, const long c1) { REVENUELINEITEMLINEITEM_ORDERKEY = c0; REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    FORCE_INLINE REVENUELINEITEM2CUSTOMER1_entry& modify0(const long c0) { REVENUELINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUELINEITEM2CUSTOMER1_entry& modify1(const long c1) { REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUELINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM2CUSTOMER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM2CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUELINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM2CUSTOMER1_entry& x, const REVENUELINEITEM2CUSTOMER1_entry& y) {
      return x.REVENUELINEITEMLINEITEM_ORDERKEY == y.REVENUELINEITEMLINEITEM_ORDERKEY && x.REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY == y.REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct REVENUELINEITEM2CUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM2CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUELINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM2CUSTOMER1_entry& x, const REVENUELINEITEM2CUSTOMER1_entry& y) {
      return x.REVENUELINEITEMLINEITEM_ORDERKEY == y.REVENUELINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct REVENUELINEITEM2CUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM2CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM2CUSTOMER1_entry& x, const REVENUELINEITEM2CUSTOMER1_entry& y) {
      return x.REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY == y.REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM2CUSTOMER1_entry,long,
    HashIndex<REVENUELINEITEM2CUSTOMER1_entry,long,REVENUELINEITEM2CUSTOMER1_mapkey01_idxfn,true>,
    HashIndex<REVENUELINEITEM2CUSTOMER1_entry,long,REVENUELINEITEM2CUSTOMER1_mapkey0_idxfn,false>,
    HashIndex<REVENUELINEITEM2CUSTOMER1_entry,long,REVENUELINEITEM2CUSTOMER1_mapkey1_idxfn,false>
  > REVENUELINEITEM2CUSTOMER1_map;
  typedef HashIndex<REVENUELINEITEM2CUSTOMER1_entry,long,REVENUELINEITEM2CUSTOMER1_mapkey01_idxfn,true> HashIndex_REVENUELINEITEM2CUSTOMER1_map_01;
  typedef HashIndex<REVENUELINEITEM2CUSTOMER1_entry,long,REVENUELINEITEM2CUSTOMER1_mapkey0_idxfn,false> HashIndex_REVENUELINEITEM2CUSTOMER1_map_0;
  typedef HashIndex<REVENUELINEITEM2CUSTOMER1_entry,long,REVENUELINEITEM2CUSTOMER1_mapkey1_idxfn,false> HashIndex_REVENUELINEITEM2CUSTOMER1_map_1;
  
  struct REVENUEORDERS3_entry {
    long REVENUEORDERSORDERS_ORDERKEY; DOUBLE_TYPE __av; 
    explicit REVENUEORDERS3_entry() { /*REVENUEORDERSORDERS_ORDERKEY = 0L; __av = 0.0; */ }
    explicit REVENUEORDERS3_entry(const long c0, const DOUBLE_TYPE c1) { REVENUEORDERSORDERS_ORDERKEY = c0; __av = c1; }
    REVENUEORDERS3_entry(const REVENUEORDERS3_entry& other) : REVENUEORDERSORDERS_ORDERKEY( other.REVENUEORDERSORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUEORDERS3_entry& modify(const long c0) { REVENUEORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUEORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEORDERS3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUEORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS3_entry& x, const REVENUEORDERS3_entry& y) {
      return x.REVENUEORDERSORDERS_ORDERKEY == y.REVENUEORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEORDERS3_entry,DOUBLE_TYPE,
    HashIndex<REVENUEORDERS3_entry,DOUBLE_TYPE,REVENUEORDERS3_mapkey0_idxfn,true>
  > REVENUEORDERS3_map;
  typedef HashIndex<REVENUEORDERS3_entry,DOUBLE_TYPE,REVENUEORDERS3_mapkey0_idxfn,true> HashIndex_REVENUEORDERS3_map_0;
  
  struct REVENUEORDERS4_entry {
    long REVENUEORDERSORDERS_CUSTKEY; STRING_TYPE C_NAME; STRING_TYPE C_ADDRESS; STRING_TYPE C_PHONE; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE C_COMMENT; STRING_TYPE N_NAME; long __av; 
    explicit REVENUEORDERS4_entry() { /*REVENUEORDERSORDERS_CUSTKEY = 0L; C_NAME = ""; C_ADDRESS = ""; C_PHONE = ""; C_ACCTBAL = 0.0; C_COMMENT = ""; N_NAME = ""; __av = 0L; */ }
    explicit REVENUEORDERS4_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const long c7) { REVENUEORDERSORDERS_CUSTKEY = c0; C_NAME = c1; C_ADDRESS = c2; C_PHONE = c3; C_ACCTBAL = c4; C_COMMENT = c5; N_NAME = c6; __av = c7; }
    REVENUEORDERS4_entry(const REVENUEORDERS4_entry& other) : REVENUEORDERSORDERS_CUSTKEY( other.REVENUEORDERSORDERS_CUSTKEY ), C_NAME( other.C_NAME ), C_ADDRESS( other.C_ADDRESS ), C_PHONE( other.C_PHONE ), C_ACCTBAL( other.C_ACCTBAL ), C_COMMENT( other.C_COMMENT ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUEORDERS4_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6) { REVENUEORDERSORDERS_CUSTKEY = c0; C_NAME = c1; C_ADDRESS = c2; C_PHONE = c3; C_ACCTBAL = c4; C_COMMENT = c5; N_NAME = c6;  return *this; }
    FORCE_INLINE REVENUEORDERS4_entry& modify0(const long c0) { REVENUEORDERSORDERS_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUEORDERSORDERS_CUSTKEY);
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
  struct REVENUEORDERS4_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUEORDERSORDERS_CUSTKEY);
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.C_ADDRESS);
      hash_combine(h, e.C_PHONE);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.C_COMMENT);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS4_entry& x, const REVENUEORDERS4_entry& y) {
      return x.REVENUEORDERSORDERS_CUSTKEY == y.REVENUEORDERSORDERS_CUSTKEY && x.C_NAME == y.C_NAME && x.C_ADDRESS == y.C_ADDRESS && x.C_PHONE == y.C_PHONE && x.C_ACCTBAL == y.C_ACCTBAL && x.C_COMMENT == y.C_COMMENT && x.N_NAME == y.N_NAME;
    }
  };
  
  struct REVENUEORDERS4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEORDERS4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUEORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEORDERS4_entry& x, const REVENUEORDERS4_entry& y) {
      return x.REVENUEORDERSORDERS_CUSTKEY == y.REVENUEORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEORDERS4_entry,long,
    HashIndex<REVENUEORDERS4_entry,long,REVENUEORDERS4_mapkey0123456_idxfn,true>,
    HashIndex<REVENUEORDERS4_entry,long,REVENUEORDERS4_mapkey0_idxfn,false>
  > REVENUEORDERS4_map;
  typedef HashIndex<REVENUEORDERS4_entry,long,REVENUEORDERS4_mapkey0123456_idxfn,true> HashIndex_REVENUEORDERS4_map_0123456;
  typedef HashIndex<REVENUEORDERS4_entry,long,REVENUEORDERS4_mapkey0_idxfn,false> HashIndex_REVENUEORDERS4_map_0;
  
  struct REVENUECUSTOMER1_entry {
    long REVENUECUSTOMERCUSTOMER_CUSTKEY; DOUBLE_TYPE __av; 
    explicit REVENUECUSTOMER1_entry() { /*REVENUECUSTOMERCUSTOMER_CUSTKEY = 0L; __av = 0.0; */ }
    explicit REVENUECUSTOMER1_entry(const long c0, const DOUBLE_TYPE c1) { REVENUECUSTOMERCUSTOMER_CUSTKEY = c0; __av = c1; }
    REVENUECUSTOMER1_entry(const REVENUECUSTOMER1_entry& other) : REVENUECUSTOMERCUSTOMER_CUSTKEY( other.REVENUECUSTOMERCUSTOMER_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER1_entry& modify(const long c0) { REVENUECUSTOMERCUSTOMER_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUECUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUECUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUECUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER1_entry& x, const REVENUECUSTOMER1_entry& y) {
      return x.REVENUECUSTOMERCUSTOMER_CUSTKEY == y.REVENUECUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<REVENUECUSTOMER1_entry,DOUBLE_TYPE,REVENUECUSTOMER1_mapkey0_idxfn,true>
  > REVENUECUSTOMER1_map;
  typedef HashIndex<REVENUECUSTOMER1_entry,DOUBLE_TYPE,REVENUECUSTOMER1_mapkey0_idxfn,true> HashIndex_REVENUECUSTOMER1_map_0;
  
  struct REVENUECUSTOMER2_entry {
    long REVENUECUSTOMERCUSTOMER_NATIONKEY; STRING_TYPE N_NAME; long __av; 
    explicit REVENUECUSTOMER2_entry() { /*REVENUECUSTOMERCUSTOMER_NATIONKEY = 0L; N_NAME = ""; __av = 0L; */ }
    explicit REVENUECUSTOMER2_entry(const long c0, const STRING_TYPE& c1, const long c2) { REVENUECUSTOMERCUSTOMER_NATIONKEY = c0; N_NAME = c1; __av = c2; }
    REVENUECUSTOMER2_entry(const REVENUECUSTOMER2_entry& other) : REVENUECUSTOMERCUSTOMER_NATIONKEY( other.REVENUECUSTOMERCUSTOMER_NATIONKEY ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUECUSTOMER2_entry& modify(const long c0, const STRING_TYPE& c1) { REVENUECUSTOMERCUSTOMER_NATIONKEY = c0; N_NAME = c1;  return *this; }
    FORCE_INLINE REVENUECUSTOMER2_entry& modify0(const long c0) { REVENUECUSTOMERCUSTOMER_NATIONKEY = c0;  return *this; }
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
  struct REVENUECUSTOMER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUECUSTOMERCUSTOMER_NATIONKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER2_entry& x, const REVENUECUSTOMER2_entry& y) {
      return x.REVENUECUSTOMERCUSTOMER_NATIONKEY == y.REVENUECUSTOMERCUSTOMER_NATIONKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  struct REVENUECUSTOMER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUECUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUECUSTOMERCUSTOMER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUECUSTOMER2_entry& x, const REVENUECUSTOMER2_entry& y) {
      return x.REVENUECUSTOMERCUSTOMER_NATIONKEY == y.REVENUECUSTOMERCUSTOMER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUECUSTOMER2_entry,long,
    HashIndex<REVENUECUSTOMER2_entry,long,REVENUECUSTOMER2_mapkey01_idxfn,true>,
    HashIndex<REVENUECUSTOMER2_entry,long,REVENUECUSTOMER2_mapkey0_idxfn,false>
  > REVENUECUSTOMER2_map;
  typedef HashIndex<REVENUECUSTOMER2_entry,long,REVENUECUSTOMER2_mapkey01_idxfn,true> HashIndex_REVENUECUSTOMER2_map_01;
  typedef HashIndex<REVENUECUSTOMER2_entry,long,REVENUECUSTOMER2_mapkey0_idxfn,false> HashIndex_REVENUECUSTOMER2_map_0;
  
  
  
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
      c1 = STRING_TYPE("R");
      c3 = Udate(STRING_TYPE("1993-10-1"));
      c2 = Udate(STRING_TYPE("1994-1-1"));
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_NATION(const long nation_nationkey, const STRING_TYPE nation_name, const long nation_regionkey, const STRING_TYPE nation_comment) {
      NATION_entry e(nation_nationkey, nation_name, nation_regionkey, nation_comment, 1L);
      NATION.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_REVENUELINEITEM2_map_0* i1 = static_cast<HashIndex_REVENUELINEITEM2_map_0*>(REVENUELINEITEM2.index[1]);
          const HASH_RES_t h1 = REVENUELINEITEM2_mapkey0_idxfn::hash(se2.modify0(lineitem_orderkey));
          HashIndex_REVENUELINEITEM2_map_0::IdxNode* n1 = static_cast<HashIndex_REVENUELINEITEM2_map_0::IdxNode*>(i1->slice(se2, h1));
          REVENUELINEITEM2_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long c_custkey = e1->C_CUSTKEY;
              STRING_TYPE c_name = e1->C_NAME;
              STRING_TYPE c_address = e1->C_ADDRESS;
              STRING_TYPE c_phone = e1->C_PHONE;
              DOUBLE_TYPE c_acctbal = e1->C_ACCTBAL;
              STRING_TYPE c_comment = e1->C_COMMENT;
              STRING_TYPE n_name = e1->N_NAME;
              long v1 = e1->__av;
              (/*if */(lineitem_returnflag == c1) ? REVENUE.addOrDelOnZero(se1.modify(c_custkey,c_name,c_acctbal,n_name,c_address,c_phone,c_comment),(v1 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  REVENUELINEITEM2_mapkey0_idxfn::equals(se2, *e1)); 
          }
        }(/*if */(lineitem_returnflag == c1) ? REVENUEORDERS3.addOrDelOnZero(se3.modify(lineitem_orderkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        { //slice 
          const HashIndex_REVENUELINEITEM2CUSTOMER1_map_0* i2 = static_cast<HashIndex_REVENUELINEITEM2CUSTOMER1_map_0*>(REVENUELINEITEM2CUSTOMER1.index[1]);
          const HASH_RES_t h2 = REVENUELINEITEM2CUSTOMER1_mapkey0_idxfn::hash(se5.modify0(lineitem_orderkey));
          HashIndex_REVENUELINEITEM2CUSTOMER1_map_0::IdxNode* n2 = static_cast<HashIndex_REVENUELINEITEM2CUSTOMER1_map_0::IdxNode*>(i2->slice(se5, h2));
          REVENUELINEITEM2CUSTOMER1_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long revenuecustomercustomer_custkey = e2->REVENUELINEITEM2CUSTOMERCUSTOMER_CUSTKEY;
              long v2 = e2->__av;
              (/*if */(lineitem_returnflag == c1) ? REVENUECUSTOMER1.addOrDelOnZero(se4.modify(revenuecustomercustomer_custkey),(v2 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  REVENUELINEITEM2CUSTOMER1_mapkey0_idxfn::equals(se5, *e2)); 
          }
        }
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_REVENUEORDERS4_map_0* i3 = static_cast<HashIndex_REVENUEORDERS4_map_0*>(REVENUEORDERS4.index[1]);
          const HASH_RES_t h3 = REVENUEORDERS4_mapkey0_idxfn::hash(se8.modify0(orders_custkey));
          HashIndex_REVENUEORDERS4_map_0::IdxNode* n3 = static_cast<HashIndex_REVENUEORDERS4_map_0::IdxNode*>(i3->slice(se8, h3));
          REVENUEORDERS4_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              STRING_TYPE c_name = e3->C_NAME;
              STRING_TYPE c_address = e3->C_ADDRESS;
              STRING_TYPE c_phone = e3->C_PHONE;
              DOUBLE_TYPE c_acctbal = e3->C_ACCTBAL;
              STRING_TYPE c_comment = e3->C_COMMENT;
              STRING_TYPE n_name = e3->N_NAME;
              long v3 = e3->__av;
              (/*if */(c2 > orders_orderdate && orders_orderdate >= c3) ? REVENUE.addOrDelOnZero(se6.modify(orders_custkey,c_name,c_acctbal,n_name,c_address,c_phone,c_comment),(REVENUEORDERS3.getValueOrDefault(se7.modify(orders_orderkey)) * v3)) : (void)0);
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  REVENUEORDERS4_mapkey0_idxfn::equals(se8, *e3)); 
          }
        }{ //slice 
          const HashIndex_REVENUEORDERS4_map_0* i4 = static_cast<HashIndex_REVENUEORDERS4_map_0*>(REVENUEORDERS4.index[1]);
          const HASH_RES_t h4 = REVENUEORDERS4_mapkey0_idxfn::hash(se10.modify0(orders_custkey));
          HashIndex_REVENUEORDERS4_map_0::IdxNode* n4 = static_cast<HashIndex_REVENUEORDERS4_map_0::IdxNode*>(i4->slice(se10, h4));
          REVENUEORDERS4_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              STRING_TYPE c_name = e4->C_NAME;
              STRING_TYPE c_address = e4->C_ADDRESS;
              STRING_TYPE c_phone = e4->C_PHONE;
              DOUBLE_TYPE c_acctbal = e4->C_ACCTBAL;
              STRING_TYPE c_comment = e4->C_COMMENT;
              STRING_TYPE n_name = e4->N_NAME;
              long v4 = e4->__av;
              (/*if */(orders_orderdate >= c3 && c2 > orders_orderdate) ? REVENUELINEITEM2.addOrDelOnZero(se9.modify(orders_orderkey,orders_custkey,c_name,c_address,c_phone,c_acctbal,c_comment,n_name),v4) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  REVENUEORDERS4_mapkey0_idxfn::equals(se10, *e4)); 
          }
        }(/*if */(c2 > orders_orderdate && orders_orderdate >= c3) ? REVENUELINEITEM2CUSTOMER1.addOrDelOnZero(se11.modify(orders_orderkey,orders_custkey),1L) : (void)0);
        (/*if */(orders_orderdate >= c3 && c2 > orders_orderdate) ? REVENUECUSTOMER1.addOrDelOnZero(se12.modify(orders_custkey),REVENUEORDERS3.getValueOrDefault(se13.modify(orders_orderkey))) : (void)0);
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_REVENUECUSTOMER2_map_0* i5 = static_cast<HashIndex_REVENUECUSTOMER2_map_0*>(REVENUECUSTOMER2.index[1]);
          const HASH_RES_t h5 = REVENUECUSTOMER2_mapkey0_idxfn::hash(se16.modify0(customer_nationkey));
          HashIndex_REVENUECUSTOMER2_map_0::IdxNode* n5 = static_cast<HashIndex_REVENUECUSTOMER2_map_0::IdxNode*>(i5->slice(se16, h5));
          REVENUECUSTOMER2_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              STRING_TYPE n_name = e5->N_NAME;
              long v5 = e5->__av;
              REVENUE.addOrDelOnZero(se14.modify(customer_custkey,customer_name,customer_acctbal,n_name,customer_address,customer_phone,customer_comment),(REVENUECUSTOMER1.getValueOrDefault(se15.modify(customer_custkey)) * v5));
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  REVENUECUSTOMER2_mapkey0_idxfn::equals(se16, *e5)); 
          }
        }{ //slice 
          const HashIndex_REVENUELINEITEM2CUSTOMER1_map_1* i6 = static_cast<HashIndex_REVENUELINEITEM2CUSTOMER1_map_1*>(REVENUELINEITEM2CUSTOMER1.index[2]);
          const HASH_RES_t h7 = REVENUELINEITEM2CUSTOMER1_mapkey1_idxfn::hash(se19.modify1(customer_custkey));
          HashIndex_REVENUELINEITEM2CUSTOMER1_map_1::IdxNode* n6 = static_cast<HashIndex_REVENUELINEITEM2CUSTOMER1_map_1::IdxNode*>(i6->slice(se19, h7));
          REVENUELINEITEM2CUSTOMER1_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              long revenuelineitemlineitem_orderkey = e6->REVENUELINEITEMLINEITEM_ORDERKEY;
              long v6 = e6->__av;
              { //slice 
                const HashIndex_REVENUECUSTOMER2_map_0* i7 = static_cast<HashIndex_REVENUECUSTOMER2_map_0*>(REVENUECUSTOMER2.index[1]);
                const HASH_RES_t h6 = REVENUECUSTOMER2_mapkey0_idxfn::hash(se18.modify0(customer_nationkey));
                HashIndex_REVENUECUSTOMER2_map_0::IdxNode* n7 = static_cast<HashIndex_REVENUECUSTOMER2_map_0::IdxNode*>(i7->slice(se18, h6));
                REVENUECUSTOMER2_entry* e7;
               
                if (n7 && (e7 = n7->obj)) {
                  do {                
                    STRING_TYPE n_name = e7->N_NAME;
                    long v7 = e7->__av;
                    REVENUELINEITEM2.addOrDelOnZero(se17.modify(revenuelineitemlineitem_orderkey,customer_custkey,customer_name,customer_address,customer_phone,customer_acctbal,customer_comment,n_name),(v6 * v7));
                    n7 = n7->nxt;
                  } while (n7 && (e7 = n7->obj) && h6 == n7->hash &&  REVENUECUSTOMER2_mapkey0_idxfn::equals(se18, *e7)); 
                }
              }
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h7 == n6->hash &&  REVENUELINEITEM2CUSTOMER1_mapkey1_idxfn::equals(se19, *e6)); 
          }
        }{ //slice 
          const HashIndex_REVENUECUSTOMER2_map_0* i8 = static_cast<HashIndex_REVENUECUSTOMER2_map_0*>(REVENUECUSTOMER2.index[1]);
          const HASH_RES_t h8 = REVENUECUSTOMER2_mapkey0_idxfn::hash(se21.modify0(customer_nationkey));
          HashIndex_REVENUECUSTOMER2_map_0::IdxNode* n8 = static_cast<HashIndex_REVENUECUSTOMER2_map_0::IdxNode*>(i8->slice(se21, h8));
          REVENUECUSTOMER2_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              STRING_TYPE n_name = e8->N_NAME;
              long v8 = e8->__av;
              REVENUEORDERS4.addOrDelOnZero(se20.modify(customer_custkey,customer_name,customer_address,customer_phone,customer_acctbal,customer_comment,n_name),v8);
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h8 == n8->hash &&  REVENUECUSTOMER2_mapkey0_idxfn::equals(se21, *e8)); 
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        REVENUECUSTOMER2.clear();
        {  // foreach
          const HashIndex_NATION_map_0123* i9 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n9; 
          NATION_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long revenuecustomercustomer_nationkey = e9->NATION_NATIONKEY;
                STRING_TYPE n_name = e9->NATION_NAME;
                long n_regionkey = e9->NATION_REGIONKEY;
                STRING_TYPE n_comment = e9->NATION_COMMENT;
                long v9 = e9->__av;
                REVENUECUSTOMER2.addOrDelOnZero(se22.modify(revenuecustomercustomer_nationkey,n_name),v9);
              n9 = n9->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    REVENUE_entry se1;
    REVENUELINEITEM2_entry se2;
    REVENUEORDERS3_entry se3;
    REVENUECUSTOMER1_entry se4;
    REVENUELINEITEM2CUSTOMER1_entry se5;
    REVENUE_entry se6;
    REVENUEORDERS3_entry se7;
    REVENUEORDERS4_entry se8;
    REVENUELINEITEM2_entry se9;
    REVENUEORDERS4_entry se10;
    REVENUELINEITEM2CUSTOMER1_entry se11;
    REVENUECUSTOMER1_entry se12;
    REVENUEORDERS3_entry se13;
    REVENUE_entry se14;
    REVENUECUSTOMER1_entry se15;
    REVENUECUSTOMER2_entry se16;
    REVENUELINEITEM2_entry se17;
    REVENUECUSTOMER2_entry se18;
    REVENUELINEITEM2CUSTOMER1_entry se19;
    REVENUEORDERS4_entry se20;
    REVENUECUSTOMER2_entry se21;
    REVENUECUSTOMER2_entry se22;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REVENUELINEITEM2_map REVENUELINEITEM2;
    REVENUELINEITEM2CUSTOMER1_map REVENUELINEITEM2CUSTOMER1;
    REVENUEORDERS3_map REVENUEORDERS3;
    REVENUEORDERS4_map REVENUEORDERS4;
    REVENUECUSTOMER1_map REVENUECUSTOMER1;
    REVENUECUSTOMER2_map REVENUECUSTOMER2;
    
    /*const static*/ STRING_TYPE c1;
    /*const static*/ long c3;
    /*const static*/ long c2;
    /*const static*/ STRING_TYPE c4;
  
  };

}
