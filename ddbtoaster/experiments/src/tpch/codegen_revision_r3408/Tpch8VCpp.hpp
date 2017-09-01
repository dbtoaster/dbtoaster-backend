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
  
  struct MKT_SHAREORDERS1_L2_1_L1_4_entry {
    long MKT_SHAREORDERSORDERS_CUSTKEY; long __av; 
    explicit MKT_SHAREORDERS1_L2_1_L1_4_entry() { /*MKT_SHAREORDERSORDERS_CUSTKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1_L2_1_L1_4_entry(const long c0, const long c1) { MKT_SHAREORDERSORDERS_CUSTKEY = c0; __av = c1; }
    MKT_SHAREORDERS1_L2_1_L1_4_entry(const MKT_SHAREORDERS1_L2_1_L1_4_entry& other) : MKT_SHAREORDERSORDERS_CUSTKEY( other.MKT_SHAREORDERSORDERS_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_4_entry& modify(const long c0) { MKT_SHAREORDERSORDERS_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERSORDERS_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L2_1_L1_4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_4_entry& x, const MKT_SHAREORDERS1_L2_1_L1_4_entry& y) {
      return x.MKT_SHAREORDERSORDERS_CUSTKEY == y.MKT_SHAREORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L2_1_L1_4_entry,long,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_4_entry,long,MKT_SHAREORDERS1_L2_1_L1_4_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1_L2_1_L1_4_map;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_4_entry,long,MKT_SHAREORDERS1_L2_1_L1_4_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1_L2_1_L1_4_map_0;
  
  struct MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry {
    long MKT_SHAREORDERS1_L2_1_L1_4CUSTOMERCUSTOMER_NATIONKEY; long __av; 
    explicit MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry() { /*MKT_SHAREORDERS1_L2_1_L1_4CUSTOMERCUSTOMER_NATIONKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry(const long c0, const long c1) { MKT_SHAREORDERS1_L2_1_L1_4CUSTOMERCUSTOMER_NATIONKEY = c0; __av = c1; }
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry(const MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry& other) : MKT_SHAREORDERS1_L2_1_L1_4CUSTOMERCUSTOMER_NATIONKEY( other.MKT_SHAREORDERS1_L2_1_L1_4CUSTOMERCUSTOMER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry& modify(const long c0) { MKT_SHAREORDERS1_L2_1_L1_4CUSTOMERCUSTOMER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERS1_L2_1_L1_4CUSTOMERCUSTOMER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERS1_L2_1_L1_4CUSTOMERCUSTOMER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry& x, const MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry& y) {
      return x.MKT_SHAREORDERS1_L2_1_L1_4CUSTOMERCUSTOMER_NATIONKEY == y.MKT_SHAREORDERS1_L2_1_L1_4CUSTOMERCUSTOMER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry,long,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry,long,MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_map;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry,long,MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_map_0;
  
  struct MKT_SHAREORDERS1_L2_1_L1_5_entry {
    long MKT_SHAREORDERSORDERS_ORDERKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1_L2_1_L1_5_entry() { /*MKT_SHAREORDERSORDERS_ORDERKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1_L2_1_L1_5_entry(const long c0, const DOUBLE_TYPE c1) { MKT_SHAREORDERSORDERS_ORDERKEY = c0; __av = c1; }
    MKT_SHAREORDERS1_L2_1_L1_5_entry(const MKT_SHAREORDERS1_L2_1_L1_5_entry& other) : MKT_SHAREORDERSORDERS_ORDERKEY( other.MKT_SHAREORDERSORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5_entry& modify(const long c0) { MKT_SHAREORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L2_1_L1_5_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5_entry& y) {
      return x.MKT_SHAREORDERSORDERS_ORDERKEY == y.MKT_SHAREORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L2_1_L1_5_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1_L2_1_L1_5_map;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5_map_0;
  
  struct MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry {
    long MKT_SHAREORDERSORDERS_ORDERKEY; long MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry() { /*MKT_SHAREORDERSORDERS_ORDERKEY = 0L; MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { MKT_SHAREORDERSORDERS_ORDERKEY = c0; MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY = c1; __av = c2; }
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& other) : MKT_SHAREORDERSORDERS_ORDERKEY( other.MKT_SHAREORDERSORDERS_ORDERKEY ), MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& modify(const long c0, const long c1) { MKT_SHAREORDERSORDERS_ORDERKEY = c0; MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& modify0(const long c0) { MKT_SHAREORDERSORDERS_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& modify1(const long c1) { MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERSORDERS_ORDERKEY);
      hash_combine(h, e.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& y) {
      return x.MKT_SHAREORDERSORDERS_ORDERKEY == y.MKT_SHAREORDERSORDERS_ORDERKEY && x.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  struct MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& y) {
      return x.MKT_SHAREORDERSORDERS_ORDERKEY == y.MKT_SHAREORDERSORDERS_ORDERKEY;
    }
  };
  
  struct MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry& y) {
      return x.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey1_idxfn,false>
  > MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey01_idxfn,true> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_01;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_1;
  
  struct MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry {
    long MKT_SHAREORDERSORDERS_ORDERKEY; long MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY; long MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry() { /*MKT_SHAREORDERSORDERS_ORDERKEY = 0L; MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY = 0L; MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { MKT_SHAREORDERSORDERS_ORDERKEY = c0; MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY = c1; MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY = c2; __av = c3; }
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& other) : MKT_SHAREORDERSORDERS_ORDERKEY( other.MKT_SHAREORDERSORDERS_ORDERKEY ), MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY( other.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY ), MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& modify(const long c0, const long c1, const long c2) { MKT_SHAREORDERSORDERS_ORDERKEY = c0; MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY = c1; MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY = c2;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& modify0(const long c0) { MKT_SHAREORDERSORDERS_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& modify1(const long c1) { MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& modify2(const long c2) { MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERSORDERS_ORDERKEY);
      hash_combine(h, e.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREORDERSORDERS_ORDERKEY == y.MKT_SHAREORDERSORDERS_ORDERKEY && x.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY == y.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY && x.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  struct MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREORDERSORDERS_ORDERKEY == y.MKT_SHAREORDERSORDERS_ORDERKEY;
    }
  };
  
  struct MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY == y.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey1_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey2_idxfn,false>
  > MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey012_idxfn,true> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_012;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_1;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey2_idxfn,false> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_2;
  
  struct MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry {
    long MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_NATIONKEY; long __av; 
    explicit MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry() { /*MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_NATIONKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry(const long c0, const long c1) { MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_NATIONKEY = c0; __av = c1; }
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry& other) : MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_NATIONKEY( other.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry& modify(const long c0) { MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry& y) {
      return x.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_NATIONKEY == y.MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry,long,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry,long,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_map;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry,long,MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_map_0;
  
  struct MKT_SHAREORDERS1_L2_1_L1_5PART2_entry {
    long MKT_SHAREORDERSORDERS_ORDERKEY; long MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS1_L2_1_L1_5PART2_entry() { /*MKT_SHAREORDERSORDERS_ORDERKEY = 0L; MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS1_L2_1_L1_5PART2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { MKT_SHAREORDERSORDERS_ORDERKEY = c0; MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY = c1; __av = c2; }
    MKT_SHAREORDERS1_L2_1_L1_5PART2_entry(const MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& other) : MKT_SHAREORDERSORDERS_ORDERKEY( other.MKT_SHAREORDERSORDERS_ORDERKEY ), MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY( other.MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& modify(const long c0, const long c1) { MKT_SHAREORDERSORDERS_ORDERKEY = c0; MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& modify0(const long c0) { MKT_SHAREORDERSORDERS_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& modify1(const long c1) { MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERSORDERS_ORDERKEY);
      hash_combine(h, e.MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& y) {
      return x.MKT_SHAREORDERSORDERS_ORDERKEY == y.MKT_SHAREORDERSORDERS_ORDERKEY && x.MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY == y.MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& y) {
      return x.MKT_SHAREORDERSORDERS_ORDERKEY == y.MKT_SHAREORDERSORDERS_ORDERKEY;
    }
  };
  
  struct MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5PART2_entry& y) {
      return x.MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY == y.MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L2_1_L1_5PART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey1_idxfn,false>
  > MKT_SHAREORDERS1_L2_1_L1_5PART2_map;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey01_idxfn,true> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_01;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_0;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_1;
  
  struct MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry {
    long MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_PARTKEY; long __av; 
    explicit MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry() { /*MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_PARTKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry(const long c0, const long c1) { MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_PARTKEY = c0; __av = c1; }
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry(const MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry& other) : MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_PARTKEY( other.MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry& modify(const long c0) { MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry& y) {
      return x.MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_PARTKEY == y.MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry,long,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry,long,MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_map;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry,long,MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_map_0;
  
  struct MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry {
    long MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_SUPPKEY; long __av; 
    explicit MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry() { /*MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_SUPPKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry(const long c0, const long c1) { MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_SUPPKEY = c0; __av = c1; }
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry(const MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry& other) : MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_SUPPKEY( other.MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry& modify(const long c0) { MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry& x, const MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry& y) {
      return x.MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_SUPPKEY == y.MKT_SHAREORDERS1_L2_1_L1_5LINEITEMLINEITEM_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry,long,
    HashIndex<MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry,long,MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_mapkey0_idxfn,true>
  > MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_map;
  typedef HashIndex<MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry,long,MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_map_0;
  
  struct MKT_SHAREORDERS6_entry {
    long MKT_SHAREORDERSORDERS_ORDERKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS6_entry() { /*MKT_SHAREORDERSORDERS_ORDERKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS6_entry(const long c0, const DOUBLE_TYPE c1) { MKT_SHAREORDERSORDERS_ORDERKEY = c0; __av = c1; }
    MKT_SHAREORDERS6_entry(const MKT_SHAREORDERS6_entry& other) : MKT_SHAREORDERSORDERS_ORDERKEY( other.MKT_SHAREORDERSORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS6_entry& modify(const long c0) { MKT_SHAREORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS6_entry& x, const MKT_SHAREORDERS6_entry& y) {
      return x.MKT_SHAREORDERSORDERS_ORDERKEY == y.MKT_SHAREORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS6_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS6_entry,DOUBLE_TYPE,MKT_SHAREORDERS6_mapkey0_idxfn,true>
  > MKT_SHAREORDERS6_map;
  typedef HashIndex<MKT_SHAREORDERS6_entry,DOUBLE_TYPE,MKT_SHAREORDERS6_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS6_map_0;
  
  struct MKT_SHAREORDERS6SUPPLIER2_entry {
    long MKT_SHAREORDERS6SUPPLIERSUPPLIER_NATIONKEY; long __av; 
    explicit MKT_SHAREORDERS6SUPPLIER2_entry() { /*MKT_SHAREORDERS6SUPPLIERSUPPLIER_NATIONKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS6SUPPLIER2_entry(const long c0, const long c1) { MKT_SHAREORDERS6SUPPLIERSUPPLIER_NATIONKEY = c0; __av = c1; }
    MKT_SHAREORDERS6SUPPLIER2_entry(const MKT_SHAREORDERS6SUPPLIER2_entry& other) : MKT_SHAREORDERS6SUPPLIERSUPPLIER_NATIONKEY( other.MKT_SHAREORDERS6SUPPLIERSUPPLIER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS6SUPPLIER2_entry& modify(const long c0) { MKT_SHAREORDERS6SUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERS6SUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS6SUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS6SUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERS6SUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS6SUPPLIER2_entry& x, const MKT_SHAREORDERS6SUPPLIER2_entry& y) {
      return x.MKT_SHAREORDERS6SUPPLIERSUPPLIER_NATIONKEY == y.MKT_SHAREORDERS6SUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS6SUPPLIER2_entry,long,
    HashIndex<MKT_SHAREORDERS6SUPPLIER2_entry,long,MKT_SHAREORDERS6SUPPLIER2_mapkey0_idxfn,true>
  > MKT_SHAREORDERS6SUPPLIER2_map;
  typedef HashIndex<MKT_SHAREORDERS6SUPPLIER2_entry,long,MKT_SHAREORDERS6SUPPLIER2_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS6SUPPLIER2_map_0;
  
  struct MKT_SHAREORDERS6PART2_entry {
    long MKT_SHAREORDERSORDERS_ORDERKEY; long MKT_SHAREORDERS6PARTPART_PARTKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHAREORDERS6PART2_entry() { /*MKT_SHAREORDERSORDERS_ORDERKEY = 0L; MKT_SHAREORDERS6PARTPART_PARTKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHAREORDERS6PART2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { MKT_SHAREORDERSORDERS_ORDERKEY = c0; MKT_SHAREORDERS6PARTPART_PARTKEY = c1; __av = c2; }
    MKT_SHAREORDERS6PART2_entry(const MKT_SHAREORDERS6PART2_entry& other) : MKT_SHAREORDERSORDERS_ORDERKEY( other.MKT_SHAREORDERSORDERS_ORDERKEY ), MKT_SHAREORDERS6PARTPART_PARTKEY( other.MKT_SHAREORDERS6PARTPART_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS6PART2_entry& modify(const long c0, const long c1) { MKT_SHAREORDERSORDERS_ORDERKEY = c0; MKT_SHAREORDERS6PARTPART_PARTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS6PART2_entry& modify0(const long c0) { MKT_SHAREORDERSORDERS_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREORDERS6PART2_entry& modify1(const long c1) { MKT_SHAREORDERS6PARTPART_PARTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERS6PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS6PART2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS6PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERSORDERS_ORDERKEY);
      hash_combine(h, e.MKT_SHAREORDERS6PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS6PART2_entry& x, const MKT_SHAREORDERS6PART2_entry& y) {
      return x.MKT_SHAREORDERSORDERS_ORDERKEY == y.MKT_SHAREORDERSORDERS_ORDERKEY && x.MKT_SHAREORDERS6PARTPART_PARTKEY == y.MKT_SHAREORDERS6PARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHAREORDERS6PART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS6PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS6PART2_entry& x, const MKT_SHAREORDERS6PART2_entry& y) {
      return x.MKT_SHAREORDERSORDERS_ORDERKEY == y.MKT_SHAREORDERSORDERS_ORDERKEY;
    }
  };
  
  struct MKT_SHAREORDERS6PART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS6PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERS6PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS6PART2_entry& x, const MKT_SHAREORDERS6PART2_entry& y) {
      return x.MKT_SHAREORDERS6PARTPART_PARTKEY == y.MKT_SHAREORDERS6PARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS6PART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREORDERS6PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS6PART2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREORDERS6PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS6PART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREORDERS6PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS6PART2_mapkey1_idxfn,false>
  > MKT_SHAREORDERS6PART2_map;
  typedef HashIndex<MKT_SHAREORDERS6PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS6PART2_mapkey01_idxfn,true> HashIndex_MKT_SHAREORDERS6PART2_map_01;
  typedef HashIndex<MKT_SHAREORDERS6PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS6PART2_mapkey0_idxfn,false> HashIndex_MKT_SHAREORDERS6PART2_map_0;
  typedef HashIndex<MKT_SHAREORDERS6PART2_entry,DOUBLE_TYPE,MKT_SHAREORDERS6PART2_mapkey1_idxfn,false> HashIndex_MKT_SHAREORDERS6PART2_map_1;
  
  struct MKT_SHAREORDERS6LINEITEM2_entry {
    long MKT_SHAREORDERS6LINEITEMLINEITEM_SUPPKEY; long __av; 
    explicit MKT_SHAREORDERS6LINEITEM2_entry() { /*MKT_SHAREORDERS6LINEITEMLINEITEM_SUPPKEY = 0L; __av = 0L; */ }
    explicit MKT_SHAREORDERS6LINEITEM2_entry(const long c0, const long c1) { MKT_SHAREORDERS6LINEITEMLINEITEM_SUPPKEY = c0; __av = c1; }
    MKT_SHAREORDERS6LINEITEM2_entry(const MKT_SHAREORDERS6LINEITEM2_entry& other) : MKT_SHAREORDERS6LINEITEMLINEITEM_SUPPKEY( other.MKT_SHAREORDERS6LINEITEMLINEITEM_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREORDERS6LINEITEM2_entry& modify(const long c0) { MKT_SHAREORDERS6LINEITEMLINEITEM_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREORDERS6LINEITEMLINEITEM_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREORDERS6LINEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREORDERS6LINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREORDERS6LINEITEMLINEITEM_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREORDERS6LINEITEM2_entry& x, const MKT_SHAREORDERS6LINEITEM2_entry& y) {
      return x.MKT_SHAREORDERS6LINEITEMLINEITEM_SUPPKEY == y.MKT_SHAREORDERS6LINEITEMLINEITEM_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREORDERS6LINEITEM2_entry,long,
    HashIndex<MKT_SHAREORDERS6LINEITEM2_entry,long,MKT_SHAREORDERS6LINEITEM2_mapkey0_idxfn,true>
  > MKT_SHAREORDERS6LINEITEM2_map;
  typedef HashIndex<MKT_SHAREORDERS6LINEITEM2_entry,long,MKT_SHAREORDERS6LINEITEM2_mapkey0_idxfn,true> HashIndex_MKT_SHAREORDERS6LINEITEM2_map_0;
  
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
  
  struct MKT_SHAREPART1CUSTOMER2_entry {
    long MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1CUSTOMER2_entry() { /*MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1CUSTOMER2_entry(const long c0, const date c1, const DOUBLE_TYPE c2) { MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c0; O_ORDERDATE = c1; __av = c2; }
    MKT_SHAREPART1CUSTOMER2_entry(const MKT_SHAREPART1CUSTOMER2_entry& other) : MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2_entry& modify(const long c0, const date c1) { MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c0; O_ORDERDATE = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2_entry& modify0(const long c0) { MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1CUSTOMER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2_entry& x, const MKT_SHAREPART1CUSTOMER2_entry& y) {
      return x.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2_entry& x, const MKT_SHAREPART1CUSTOMER2_entry& y) {
      return x.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1CUSTOMER2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1CUSTOMER2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1CUSTOMER2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2_mapkey0_idxfn,false>
  > MKT_SHAREPART1CUSTOMER2_map;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1CUSTOMER2_map_01;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER2_map_0;
  
  struct MKT_SHAREPART1CUSTOMER2LINEITEM3_entry {
    long MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY; long MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY; date O_ORDERDATE; long __av; 
    explicit MKT_SHAREPART1CUSTOMER2LINEITEM3_entry() { /*MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY = 0L; MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit MKT_SHAREPART1CUSTOMER2LINEITEM3_entry(const long c0, const long c1, const date c2, const long c3) { MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY = c0; MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHAREPART1CUSTOMER2LINEITEM3_entry(const MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& other) : MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY( other.MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY ), MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& modify(const long c0, const long c1, const date c2) { MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY = c0; MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c1; O_ORDERDATE = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& modify0(const long c0) { MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& modify1(const long c1) { MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& x, const MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& y) {
      return x.MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY == y.MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY && x.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& x, const MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& y) {
      return x.MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY == y.MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& x, const MKT_SHAREPART1CUSTOMER2LINEITEM3_entry& y) {
      return x.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1CUSTOMER2LINEITEM3_entry,long,
    HashIndex<MKT_SHAREPART1CUSTOMER2LINEITEM3_entry,long,MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1CUSTOMER2LINEITEM3_entry,long,MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1CUSTOMER2LINEITEM3_entry,long,MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey1_idxfn,false>
  > MKT_SHAREPART1CUSTOMER2LINEITEM3_map;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2LINEITEM3_entry,long,MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_012;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2LINEITEM3_entry,long,MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2LINEITEM3_entry,long,MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_1;
  
  struct MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry {
    long MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY; long MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry() { /*MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = 0L; MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry(const long c0, const long c1, const date c2, const DOUBLE_TYPE c3) { MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = c0; MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry(const MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& other) : MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY ), MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& modify(const long c0, const long c1, const date c2) { MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = c0; MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c1; O_ORDERDATE = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& modify1(const long c1) { MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& modify0(const long c0) { MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& x, const MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& y) {
      return x.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY && x.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& x, const MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& y) {
      return x.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& x, const MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry& y) {
      return x.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey1_idxfn,false>,
    HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey0_idxfn,false>
  > MKT_SHAREPART1CUSTOMER2SUPPLIER2_map;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2_map_012;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2_map_1;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2_map_0;
  
  struct MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry {
    long MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY; long MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY; long MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry() { /*MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY = 0L; MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = 0L; MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry(const long c0, const long c1, const long c2, const date c3, const DOUBLE_TYPE c4) { MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY = c0; MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = c1; MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c2; O_ORDERDATE = c3; __av = c4; }
    MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry(const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& other) : MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY( other.MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY ), MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY ), MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& modify(const long c0, const long c1, const long c2, const date c3) { MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY = c0; MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = c1; MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c2; O_ORDERDATE = c3;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& modify0(const long c0) { MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& modify2(const long c2) { MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& modify1(const long c1) { MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& x, const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& y) {
      return x.MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY == y.MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY && x.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY && x.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& x, const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& y) {
      return x.MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY == y.MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& x, const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& y) {
      return x.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& x, const MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry& y) {
      return x.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey0123_idxfn,true>,
    HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey2_idxfn,false>,
    HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey1_idxfn,false>
  > MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey0123_idxfn,true> HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_0123;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_0;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey2_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_2;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_1;
  
  struct MKT_SHAREPART1CUSTOMER2PART2_entry {
    long MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY; long MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1CUSTOMER2PART2_entry() { /*MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY = 0L; MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1CUSTOMER2PART2_entry(const long c0, const long c1, const date c2, const DOUBLE_TYPE c3) { MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY = c0; MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHAREPART1CUSTOMER2PART2_entry(const MKT_SHAREPART1CUSTOMER2PART2_entry& other) : MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY( other.MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY ), MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2PART2_entry& modify(const long c0, const long c1, const date c2) { MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY = c0; MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c1; O_ORDERDATE = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2PART2_entry& modify0(const long c0) { MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1CUSTOMER2PART2_entry& modify1(const long c1) { MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1CUSTOMER2PART2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2PART2_entry& x, const MKT_SHAREPART1CUSTOMER2PART2_entry& y) {
      return x.MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY == y.MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY && x.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER2PART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2PART2_entry& x, const MKT_SHAREPART1CUSTOMER2PART2_entry& y) {
      return x.MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY == y.MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHAREPART1CUSTOMER2PART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1CUSTOMER2PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1CUSTOMER2PART2_entry& x, const MKT_SHAREPART1CUSTOMER2PART2_entry& y) {
      return x.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1CUSTOMER2PART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1CUSTOMER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2PART2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1CUSTOMER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2PART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1CUSTOMER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2PART2_mapkey1_idxfn,false>
  > MKT_SHAREPART1CUSTOMER2PART2_map;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2PART2_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1CUSTOMER2PART2_map_012;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2PART2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER2PART2_map_0;
  typedef HashIndex<MKT_SHAREPART1CUSTOMER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1CUSTOMER2PART2_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1CUSTOMER2PART2_map_1;
  
  struct MKT_SHAREPART1LINEITEM1_entry {
    long MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY; date O_ORDERDATE; long __av; 
    explicit MKT_SHAREPART1LINEITEM1_entry() { /*MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY = 0L; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit MKT_SHAREPART1LINEITEM1_entry(const long c0, const date c1, const long c2) { MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY = c0; O_ORDERDATE = c1; __av = c2; }
    MKT_SHAREPART1LINEITEM1_entry(const MKT_SHAREPART1LINEITEM1_entry& other) : MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY( other.MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1LINEITEM1_entry& modify(const long c0, const date c1) { MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY = c0; O_ORDERDATE = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1LINEITEM1_entry& modify0(const long c0) { MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1LINEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1LINEITEM1_entry& x, const MKT_SHAREPART1LINEITEM1_entry& y) {
      return x.MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY == y.MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1LINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1LINEITEM1_entry& x, const MKT_SHAREPART1LINEITEM1_entry& y) {
      return x.MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY == y.MKT_SHAREPART1LINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1LINEITEM1_entry,long,
    HashIndex<MKT_SHAREPART1LINEITEM1_entry,long,MKT_SHAREPART1LINEITEM1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1LINEITEM1_entry,long,MKT_SHAREPART1LINEITEM1_mapkey0_idxfn,false>
  > MKT_SHAREPART1LINEITEM1_map;
  typedef HashIndex<MKT_SHAREPART1LINEITEM1_entry,long,MKT_SHAREPART1LINEITEM1_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1LINEITEM1_map_01;
  typedef HashIndex<MKT_SHAREPART1LINEITEM1_entry,long,MKT_SHAREPART1LINEITEM1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1LINEITEM1_map_0;
  
  struct MKT_SHAREPART1SUPPLIER1_entry {
    long MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1SUPPLIER1_entry() { /*MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1SUPPLIER1_entry(const long c0, const date c1, const DOUBLE_TYPE c2) { MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY = c0; O_ORDERDATE = c1; __av = c2; }
    MKT_SHAREPART1SUPPLIER1_entry(const MKT_SHAREPART1SUPPLIER1_entry& other) : MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1SUPPLIER1_entry& modify(const long c0, const date c1) { MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY = c0; O_ORDERDATE = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1SUPPLIER1_entry& modify0(const long c0) { MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1SUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1SUPPLIER1_entry& x, const MKT_SHAREPART1SUPPLIER1_entry& y) {
      return x.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1SUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1SUPPLIER1_entry& x, const MKT_SHAREPART1SUPPLIER1_entry& y) {
      return x.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1SUPPLIER1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_mapkey0_idxfn,false>
  > MKT_SHAREPART1SUPPLIER1_map;
  typedef HashIndex<MKT_SHAREPART1SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1SUPPLIER1_map_01;
  typedef HashIndex<MKT_SHAREPART1SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1SUPPLIER1_map_0;
  
  struct MKT_SHAREPART1SUPPLIER1PART2_entry {
    long MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY; long MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1SUPPLIER1PART2_entry() { /*MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY = 0L; MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1SUPPLIER1PART2_entry(const long c0, const long c1, const date c2, const DOUBLE_TYPE c3) { MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY = c0; MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHAREPART1SUPPLIER1PART2_entry(const MKT_SHAREPART1SUPPLIER1PART2_entry& other) : MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY( other.MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY ), MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1SUPPLIER1PART2_entry& modify(const long c0, const long c1, const date c2) { MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY = c0; MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY = c1; O_ORDERDATE = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1SUPPLIER1PART2_entry& modify0(const long c0) { MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1SUPPLIER1PART2_entry& modify1(const long c1) { MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1SUPPLIER1PART2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1SUPPLIER1PART2_entry& x, const MKT_SHAREPART1SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY == y.MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY && x.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1SUPPLIER1PART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1SUPPLIER1PART2_entry& x, const MKT_SHAREPART1SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY == y.MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHAREPART1SUPPLIER1PART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1SUPPLIER1PART2_entry& x, const MKT_SHAREPART1SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1SUPPLIER1PART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1PART2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1PART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1PART2_mapkey1_idxfn,false>
  > MKT_SHAREPART1SUPPLIER1PART2_map;
  typedef HashIndex<MKT_SHAREPART1SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1PART2_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1SUPPLIER1PART2_map_012;
  typedef HashIndex<MKT_SHAREPART1SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1PART2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1SUPPLIER1PART2_map_0;
  typedef HashIndex<MKT_SHAREPART1SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1SUPPLIER1PART2_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1SUPPLIER1PART2_map_1;
  
  struct MKT_SHAREPART1PART2_entry {
    long MKT_SHAREPART1PARTPART_PARTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1PART2_entry() { /*MKT_SHAREPART1PARTPART_PARTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHAREPART1PART2_entry(const long c0, const date c1, const DOUBLE_TYPE c2) { MKT_SHAREPART1PARTPART_PARTKEY = c0; O_ORDERDATE = c1; __av = c2; }
    MKT_SHAREPART1PART2_entry(const MKT_SHAREPART1PART2_entry& other) : MKT_SHAREPART1PARTPART_PARTKEY( other.MKT_SHAREPART1PARTPART_PARTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1PART2_entry& modify(const long c0, const date c1) { MKT_SHAREPART1PARTPART_PARTKEY = c0; O_ORDERDATE = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1PART2_entry& modify0(const long c0) { MKT_SHAREPART1PARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1PART2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1PARTPART_PARTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1PART2_entry& x, const MKT_SHAREPART1PART2_entry& y) {
      return x.MKT_SHAREPART1PARTPART_PARTKEY == y.MKT_SHAREPART1PARTPART_PARTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHAREPART1PART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1PART2_entry& x, const MKT_SHAREPART1PART2_entry& y) {
      return x.MKT_SHAREPART1PARTPART_PARTKEY == y.MKT_SHAREPART1PARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1PART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1PART2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1PART2_mapkey0_idxfn,false>
  > MKT_SHAREPART1PART2_map;
  typedef HashIndex<MKT_SHAREPART1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1PART2_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1PART2_map_01;
  typedef HashIndex<MKT_SHAREPART1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1PART2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1PART2_map_0;
  
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
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry {
    long MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry() { /*MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry& other) : MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry& modify(const long c0, const long c1) { MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry& modify0(const long c0) { MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_mapkey0_idxfn,false>
  > MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_map_01;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_map_0;
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry {
    long MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY; long MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY; long TOTAL_O_YEAR; long __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry() { /*MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY = 0L; MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0L; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry(const long c0, const long c1, const long c2, const long c3) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY = c0; MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& other) : MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY( other.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY ), MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& modify(const long c0, const long c1, const long c2) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY = c0; MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& modify0(const long c0) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& modify1(const long c1) { MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY && x.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry,long,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry,long,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry,long,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry,long,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey1_idxfn,false>
  > MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry,long,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_012;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry,long,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry,long,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_1;
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry {
    long MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY; long MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry() { /*MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = 0L; MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = c0; MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& other) : MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY ), MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& modify(const long c0, const long c1, const long c2) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = c0; MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& modify1(const long c1) { MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& modify0(const long c0) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY && x.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey1_idxfn,false>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey0_idxfn,false>
  > MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map_012;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map_1;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map_0;
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry {
    long MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY; long MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY; long MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry() { /*MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY = 0L; MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = 0L; MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY = c0; MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = c1; MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c2; TOTAL_O_YEAR = c3; __av = c4; }
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& other) : MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY( other.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY ), MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY ), MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& modify(const long c0, const long c1, const long c2, const long c3) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY = c0; MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = c1; MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c2; TOTAL_O_YEAR = c3;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& modify0(const long c0) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& modify2(const long c2) { MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& modify1(const long c1) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY && x.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY && x.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey0123_idxfn,true>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey2_idxfn,false>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey1_idxfn,false>
  > MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey0123_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_0123;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_0;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey2_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_2;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_1;
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry {
    long MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY; long MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry() { /*MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY = 0L; MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY = c0; MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& other) : MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY( other.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY ), MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& modify(const long c0, const long c1, const long c2) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY = c0; MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& modify0(const long c0) { MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& modify1(const long c1) { MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY && x.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& x, const MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey1_idxfn,false>
  > MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map_012;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map_0;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map_1;
  
  struct MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry {
    long MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY; long TOTAL_O_YEAR; long __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry() { /*MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0L; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry(const long c0, const long c1, const long c2) { MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry(const MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry& other) : MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY( other.MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry& modify(const long c0, const long c1) { MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry& modify0(const long c0) { MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry& x, const MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY == y.MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry& x, const MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY == y.MKT_SHAREPART1_L2_1_L1_1LINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry,long,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry,long,MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry,long,MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey0_idxfn,false>
  > MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry,long,MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_01;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry,long,MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0;
  
  struct MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry {
    long MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry() { /*MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry(const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry& other) : MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry& modify(const long c0, const long c1) { MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry& modify0(const long c0) { MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry& x, const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry& x, const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_mapkey0_idxfn,false>
  > MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_map_01;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_map_0;
  
  struct MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry {
    long MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY; long MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry() { /*MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY = 0L; MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY = c0; MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry(const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& other) : MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY( other.MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY ), MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& modify(const long c0, const long c1, const long c2) { MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY = c0; MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& modify0(const long c0) { MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& modify1(const long c1) { MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& x, const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY == y.MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY && x.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& x, const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY == y.MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& x, const MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey1_idxfn,false>
  > MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey012_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map_012;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map_0;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey1_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map_1;
  
  struct MKT_SHAREPART1_L2_1_L1_1PART2_entry {
    long MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHAREPART1_L2_1_L1_1PART2_entry() { /*MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHAREPART1_L2_1_L1_1PART2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHAREPART1_L2_1_L1_1PART2_entry(const MKT_SHAREPART1_L2_1_L1_1PART2_entry& other) : MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY( other.MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1PART2_entry& modify(const long c0, const long c1) { MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHAREPART1_L2_1_L1_1PART2_entry& modify0(const long c0) { MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHAREPART1_L2_1_L1_1PART2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1PART2_entry& x, const MKT_SHAREPART1_L2_1_L1_1PART2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY == y.MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHAREPART1_L2_1_L1_1PART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHAREPART1_L2_1_L1_1PART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHAREPART1_L2_1_L1_1PART2_entry& x, const MKT_SHAREPART1_L2_1_L1_1PART2_entry& y) {
      return x.MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY == y.MKT_SHAREPART1_L2_1_L1_1PARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHAREPART1_L2_1_L1_1PART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1PART2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHAREPART1_L2_1_L1_1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1PART2_mapkey0_idxfn,false>
  > MKT_SHAREPART1_L2_1_L1_1PART2_map;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1PART2_mapkey01_idxfn,true> HashIndex_MKT_SHAREPART1_L2_1_L1_1PART2_map_01;
  typedef HashIndex<MKT_SHAREPART1_L2_1_L1_1PART2_entry,DOUBLE_TYPE,MKT_SHAREPART1_L2_1_L1_1PART2_mapkey0_idxfn,false> HashIndex_MKT_SHAREPART1_L2_1_L1_1PART2_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
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
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        MKT_SHAREORDERS1_L2_1_L1_5.addOrDelOnZero(se1.modify(lineitem_orderkey),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1.getValueOrDefault(se2.modify(lineitem_partkey)) * (MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2.getValueOrDefault(se3.modify(lineitem_suppkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
        MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1.addOrDelOnZero(se4.modify(lineitem_orderkey,lineitem_suppkey),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1.getValueOrDefault(se5.modify(lineitem_partkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
        MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2.addOrDelOnZero(se6.modify(lineitem_orderkey,lineitem_partkey,lineitem_suppkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount))));
        MKT_SHAREORDERS1_L2_1_L1_5PART2.addOrDelOnZero(se7.modify(lineitem_orderkey,lineitem_partkey),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2.getValueOrDefault(se8.modify(lineitem_suppkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
        MKT_SHAREORDERS6.addOrDelOnZero(se9.modify(lineitem_orderkey),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1.getValueOrDefault(se10.modify(lineitem_partkey)) * (MKT_SHAREORDERS6LINEITEM2.getValueOrDefault(se11.modify(lineitem_suppkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
        MKT_SHAREORDERS6PART2.addOrDelOnZero(se12.modify(lineitem_orderkey,lineitem_partkey),(MKT_SHAREORDERS6LINEITEM2.getValueOrDefault(se13.modify(lineitem_suppkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
        { //slice 
          const HashIndex_MKT_SHAREPART1LINEITEM1_map_0* i1 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_map_0*>(MKT_SHAREPART1LINEITEM1.index[1]);
          const HASH_RES_t h1 = MKT_SHAREPART1LINEITEM1_mapkey0_idxfn::hash(se17.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1LINEITEM1_map_0::IdxNode* n1 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_map_0::IdxNode*>(i1->slice(se17, h1));
          MKT_SHAREPART1LINEITEM1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              date o_orderdate = e1->O_ORDERDATE;
              long v1 = e1->__av;
              MKT_SHAREPART1.addOrDelOnZero(se14.modify(o_orderdate),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1.getValueOrDefault(se15.modify(lineitem_partkey)) * (MKT_SHAREORDERS6LINEITEM2.getValueOrDefault(se16.modify(lineitem_suppkey)) * (v1 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  MKT_SHAREPART1LINEITEM1_mapkey0_idxfn::equals(se17, *e1)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0* i2 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0*>(MKT_SHAREPART1CUSTOMER2LINEITEM3.index[1]);
          const HASH_RES_t h2 = MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey0_idxfn::hash(se21.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0::IdxNode* n2 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0::IdxNode*>(i2->slice(se21, h2));
          MKT_SHAREPART1CUSTOMER2LINEITEM3_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long mkt_sharepart1customercustomer_custkey = e2->MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e2->O_ORDERDATE;
              long v2 = e2->__av;
              MKT_SHAREPART1CUSTOMER2.addOrDelOnZero(se18.modify(mkt_sharepart1customercustomer_custkey,o_orderdate),(MKT_SHAREORDERS6LINEITEM2.getValueOrDefault(se19.modify(lineitem_suppkey)) * (MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1.getValueOrDefault(se20.modify(lineitem_partkey)) * (v2 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey0_idxfn::equals(se21, *e2)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0* i3 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0*>(MKT_SHAREPART1CUSTOMER2LINEITEM3.index[1]);
          const HASH_RES_t h3 = MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey0_idxfn::hash(se24.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0::IdxNode* n3 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0::IdxNode*>(i3->slice(se24, h3));
          MKT_SHAREPART1CUSTOMER2LINEITEM3_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              long mkt_sharepart1customercustomer_custkey = e3->MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e3->O_ORDERDATE;
              long v3 = e3->__av;
              MKT_SHAREPART1CUSTOMER2SUPPLIER2.addOrDelOnZero(se22.modify(lineitem_suppkey,mkt_sharepart1customercustomer_custkey,o_orderdate),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1.getValueOrDefault(se23.modify(lineitem_partkey)) * (v3 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey0_idxfn::equals(se24, *e3)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0* i4 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0*>(MKT_SHAREPART1CUSTOMER2LINEITEM3.index[1]);
          const HASH_RES_t h4 = MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey0_idxfn::hash(se26.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0::IdxNode* n4 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0::IdxNode*>(i4->slice(se26, h4));
          MKT_SHAREPART1CUSTOMER2LINEITEM3_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long mkt_sharepart1customercustomer_custkey = e4->MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e4->O_ORDERDATE;
              long v4 = e4->__av;
              MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2.addOrDelOnZero(se25.modify(lineitem_partkey,lineitem_suppkey,mkt_sharepart1customercustomer_custkey,o_orderdate),(v4 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey0_idxfn::equals(se26, *e4)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0* i5 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0*>(MKT_SHAREPART1CUSTOMER2LINEITEM3.index[1]);
          const HASH_RES_t h5 = MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey0_idxfn::hash(se29.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0::IdxNode* n5 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_0::IdxNode*>(i5->slice(se29, h5));
          MKT_SHAREPART1CUSTOMER2LINEITEM3_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long mkt_sharepart1customercustomer_custkey = e5->MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e5->O_ORDERDATE;
              long v5 = e5->__av;
              MKT_SHAREPART1CUSTOMER2PART2.addOrDelOnZero(se27.modify(lineitem_partkey,mkt_sharepart1customercustomer_custkey,o_orderdate),(MKT_SHAREORDERS6LINEITEM2.getValueOrDefault(se28.modify(lineitem_suppkey)) * (v5 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey0_idxfn::equals(se29, *e5)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1LINEITEM1_map_0* i6 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_map_0*>(MKT_SHAREPART1LINEITEM1.index[1]);
          const HASH_RES_t h6 = MKT_SHAREPART1LINEITEM1_mapkey0_idxfn::hash(se32.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1LINEITEM1_map_0::IdxNode* n6 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_map_0::IdxNode*>(i6->slice(se32, h6));
          MKT_SHAREPART1LINEITEM1_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              date o_orderdate = e6->O_ORDERDATE;
              long v6 = e6->__av;
              MKT_SHAREPART1SUPPLIER1.addOrDelOnZero(se30.modify(lineitem_suppkey,o_orderdate),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1.getValueOrDefault(se31.modify(lineitem_partkey)) * (v6 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h6 == n6->hash &&  MKT_SHAREPART1LINEITEM1_mapkey0_idxfn::equals(se32, *e6)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1LINEITEM1_map_0* i7 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_map_0*>(MKT_SHAREPART1LINEITEM1.index[1]);
          const HASH_RES_t h7 = MKT_SHAREPART1LINEITEM1_mapkey0_idxfn::hash(se34.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1LINEITEM1_map_0::IdxNode* n7 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_map_0::IdxNode*>(i7->slice(se34, h7));
          MKT_SHAREPART1LINEITEM1_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              date o_orderdate = e7->O_ORDERDATE;
              long v7 = e7->__av;
              MKT_SHAREPART1SUPPLIER1PART2.addOrDelOnZero(se33.modify(lineitem_partkey,lineitem_suppkey,o_orderdate),(v7 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h7 == n7->hash &&  MKT_SHAREPART1LINEITEM1_mapkey0_idxfn::equals(se34, *e7)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1LINEITEM1_map_0* i8 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_map_0*>(MKT_SHAREPART1LINEITEM1.index[1]);
          const HASH_RES_t h8 = MKT_SHAREPART1LINEITEM1_mapkey0_idxfn::hash(se37.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1LINEITEM1_map_0::IdxNode* n8 = static_cast<HashIndex_MKT_SHAREPART1LINEITEM1_map_0::IdxNode*>(i8->slice(se37, h8));
          MKT_SHAREPART1LINEITEM1_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              date o_orderdate = e8->O_ORDERDATE;
              long v8 = e8->__av;
              MKT_SHAREPART1PART2.addOrDelOnZero(se35.modify(lineitem_partkey,o_orderdate),(MKT_SHAREORDERS6LINEITEM2.getValueOrDefault(se36.modify(lineitem_suppkey)) * (v8 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h8 == n8->hash &&  MKT_SHAREPART1LINEITEM1_mapkey0_idxfn::equals(se37, *e8)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0* i9 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0*>(MKT_SHAREPART1_L2_1_L1_1LINEITEM1.index[1]);
          const HASH_RES_t h9 = MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey0_idxfn::hash(se41.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0::IdxNode* n9 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0::IdxNode*>(i9->slice(se41, h9));
          MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              long total_o_year = e9->TOTAL_O_YEAR;
              long v9 = e9->__av;
              MKT_SHAREPART1_L2_1_L1_1.addOrDelOnZero(se38.modify(total_o_year),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1.getValueOrDefault(se39.modify(lineitem_partkey)) * (MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2.getValueOrDefault(se40.modify(lineitem_suppkey)) * (v9 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h9 == n9->hash &&  MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey0_idxfn::equals(se41, *e9)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0* i10 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2.index[1]);
          const HASH_RES_t h10 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey0_idxfn::hash(se45.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0::IdxNode* n10 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0::IdxNode*>(i10->slice(se45, h10));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1customercustomer_custkey = e10->MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e10->TOTAL_O_YEAR;
              long v10 = e10->__av;
              MKT_SHAREPART1_L2_1_L1_1CUSTOMER2.addOrDelOnZero(se42.modify(mkt_sharepart1_l2_1_l1_1customercustomer_custkey,total_o_year),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1.getValueOrDefault(se43.modify(lineitem_partkey)) * (MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2.getValueOrDefault(se44.modify(lineitem_suppkey)) * (v10 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h10 == n10->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey0_idxfn::equals(se45, *e10)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0* i11 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2.index[1]);
          const HASH_RES_t h11 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey0_idxfn::hash(se48.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0::IdxNode* n11 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0::IdxNode*>(i11->slice(se48, h11));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1customercustomer_custkey = e11->MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e11->TOTAL_O_YEAR;
              long v11 = e11->__av;
              MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1.addOrDelOnZero(se46.modify(lineitem_suppkey,mkt_sharepart1_l2_1_l1_1customercustomer_custkey,total_o_year),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1.getValueOrDefault(se47.modify(lineitem_partkey)) * (v11 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h11 == n11->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey0_idxfn::equals(se48, *e11)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0* i12 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2.index[1]);
          const HASH_RES_t h12 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey0_idxfn::hash(se50.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0::IdxNode* n12 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0::IdxNode*>(i12->slice(se50, h12));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1customercustomer_custkey = e12->MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e12->TOTAL_O_YEAR;
              long v12 = e12->__av;
              MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2.addOrDelOnZero(se49.modify(lineitem_partkey,lineitem_suppkey,mkt_sharepart1_l2_1_l1_1customercustomer_custkey,total_o_year),(v12 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h12 == n12->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey0_idxfn::equals(se50, *e12)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0* i13 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2.index[1]);
          const HASH_RES_t h13 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey0_idxfn::hash(se53.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0::IdxNode* n13 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_0::IdxNode*>(i13->slice(se53, h13));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry* e13;
         
          if (n13 && (e13 = n13->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1customercustomer_custkey = e13->MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e13->TOTAL_O_YEAR;
              long v13 = e13->__av;
              MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2.addOrDelOnZero(se51.modify(lineitem_partkey,mkt_sharepart1_l2_1_l1_1customercustomer_custkey,total_o_year),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2.getValueOrDefault(se52.modify(lineitem_suppkey)) * (v13 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n13 = n13->nxt;
            } while (n13 && (e13 = n13->obj) && h13 == n13->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey0_idxfn::equals(se53, *e13)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0* i14 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0*>(MKT_SHAREPART1_L2_1_L1_1LINEITEM1.index[1]);
          const HASH_RES_t h14 = MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey0_idxfn::hash(se56.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0::IdxNode* n14 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0::IdxNode*>(i14->slice(se56, h14));
          MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              long total_o_year = e14->TOTAL_O_YEAR;
              long v14 = e14->__av;
              MKT_SHAREPART1_L2_1_L1_1SUPPLIER1.addOrDelOnZero(se54.modify(lineitem_suppkey,total_o_year),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1.getValueOrDefault(se55.modify(lineitem_partkey)) * (v14 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h14 == n14->hash &&  MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey0_idxfn::equals(se56, *e14)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0* i15 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0*>(MKT_SHAREPART1_L2_1_L1_1LINEITEM1.index[1]);
          const HASH_RES_t h15 = MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey0_idxfn::hash(se58.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0::IdxNode* n15 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0::IdxNode*>(i15->slice(se58, h15));
          MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry* e15;
         
          if (n15 && (e15 = n15->obj)) {
            do {                
              long total_o_year = e15->TOTAL_O_YEAR;
              long v15 = e15->__av;
              MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2.addOrDelOnZero(se57.modify(lineitem_partkey,lineitem_suppkey,total_o_year),(v15 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n15 = n15->nxt;
            } while (n15 && (e15 = n15->obj) && h15 == n15->hash &&  MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey0_idxfn::equals(se58, *e15)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0* i16 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0*>(MKT_SHAREPART1_L2_1_L1_1LINEITEM1.index[1]);
          const HASH_RES_t h16 = MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey0_idxfn::hash(se61.modify0(lineitem_orderkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0::IdxNode* n16 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map_0::IdxNode*>(i16->slice(se61, h16));
          MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry* e16;
         
          if (n16 && (e16 = n16->obj)) {
            do {                
              long total_o_year = e16->TOTAL_O_YEAR;
              long v16 = e16->__av;
              MKT_SHAREPART1_L2_1_L1_1PART2.addOrDelOnZero(se59.modify(lineitem_partkey,total_o_year),(MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2.getValueOrDefault(se60.modify(lineitem_suppkey)) * (v16 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n16 = n16->nxt;
            } while (n16 && (e16 = n16->obj) && h16 == n16->hash &&  MKT_SHAREPART1_L2_1_L1_1LINEITEM1_mapkey0_idxfn::equals(se61, *e16)); 
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHAREPART1_map_0* i17 = static_cast<HashIndex_MKT_SHAREPART1_map_0*>(MKT_SHAREPART1.index[0]);
          HashIndex_MKT_SHAREPART1_map_0::IdxNode* n17; 
          MKT_SHAREPART1_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                date o_orderdate = e17->O_ORDERDATE;
                DOUBLE_TYPE v17 = e17->__av;
                long l1 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg1 = 0.0;
                DOUBLE_TYPE l3 = MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se63.modify(l1));
                agg1 += Ulistmax(1L, l3);
                DOUBLE_TYPE l2 = agg1;
                MKT_SHARE.addOrDelOnZero(se62.modify(l1),(v17 * Udiv(l2)));
              n17 = n17->nxt;
            }
          }
        }
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long l4 = Uyear_part(orders_orderdate);
        DOUBLE_TYPE agg2 = 0.0;
        DOUBLE_TYPE agg3 = 0.0;
        DOUBLE_TYPE l6 = (MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se65.modify(l4)) + (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? (MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se66.modify(orders_custkey)) * MKT_SHAREORDERS1_L2_1_L1_5.getValueOrDefault(se67.modify(orders_orderkey))) : 0.0));
        agg3 += Ulistmax(1L, l6);
        DOUBLE_TYPE l5 = agg3;
        {  // foreach
          const HashIndex_MKT_SHAREPART1_map_0* i18 = static_cast<HashIndex_MKT_SHAREPART1_map_0*>(MKT_SHAREPART1.index[0]);
          HashIndex_MKT_SHAREPART1_map_0::IdxNode* n18; 
          MKT_SHAREPART1_entry* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
                date o_orderdate = e18->O_ORDERDATE;
                DOUBLE_TYPE v18 = e18->__av;
                (/*if */(l4 == Uyear_part(o_orderdate)) ? agg2 += (v18 * Udiv(l5)) : 0.0);
              n18 = n18->nxt;
            }
          }
        }DOUBLE_TYPE agg4 = 0.0;
        DOUBLE_TYPE agg5 = 0.0;
        DOUBLE_TYPE l8 = MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se68.modify(l4));
        agg5 += Ulistmax(1L, l8);
        DOUBLE_TYPE l7 = agg5;
        {  // foreach
          const HashIndex_MKT_SHAREPART1_map_0* i19 = static_cast<HashIndex_MKT_SHAREPART1_map_0*>(MKT_SHAREPART1.index[0]);
          HashIndex_MKT_SHAREPART1_map_0::IdxNode* n19; 
          MKT_SHAREPART1_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                date o_orderdate = e19->O_ORDERDATE;
                DOUBLE_TYPE v19 = e19->__av;
                (/*if */(l4 == Uyear_part(o_orderdate)) ? agg4 += (v19 * Udiv(l7)) : 0.0);
              n19 = n19->nxt;
            }
          }
        }DOUBLE_TYPE agg6 = 0.0;
        DOUBLE_TYPE agg7 = 0.0;
        DOUBLE_TYPE l10 = (MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se71.modify(l4)) + (MKT_SHAREORDERS1_L2_1_L1_5.getValueOrDefault(se72.modify(orders_orderkey)) * MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se73.modify(orders_custkey))));
        agg7 += Ulistmax(1L, l10);
        DOUBLE_TYPE l9 = agg7;
        agg6 += Udiv(l9);
        MKT_SHARE.addOrDelOnZero(se64.modify(l4),(agg2 + ((agg4 * -1L) + (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? (MKT_SHAREORDERS6.getValueOrDefault(se69.modify(orders_orderkey)) * (MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se70.modify(orders_custkey)) * agg6)) : 0.0))));
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1.addOrDelOnZero(se74.modify(orders_orderdate),(MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se75.modify(orders_custkey)) * MKT_SHAREORDERS6.getValueOrDefault(se76.modify(orders_orderkey)))) : (void)0);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1CUSTOMER2.addOrDelOnZero(se77.modify(orders_custkey,orders_orderdate),MKT_SHAREORDERS6.getValueOrDefault(se78.modify(orders_orderkey))) : (void)0);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1CUSTOMER2LINEITEM3.addOrDelOnZero(se79.modify(orders_orderkey,orders_custkey,orders_orderdate),1L) : (void)0);
        { //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0* i20 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1.index[1]);
          const HASH_RES_t h17 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey0_idxfn::hash(se81.modify0(orders_orderkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0::IdxNode* n20 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0::IdxNode*>(i20->slice(se81, h17));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry* e20;
         
          if (n20 && (e20 = n20->obj)) {
            do {                
              long mkt_sharepart1customer2suppliersupplier_suppkey = e20->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v20 = e20->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1CUSTOMER2SUPPLIER2.addOrDelOnZero(se80.modify(mkt_sharepart1customer2suppliersupplier_suppkey,orders_custkey,orders_orderdate),v20) : (void)0);
              n20 = n20->nxt;
            } while (n20 && (e20 = n20->obj) && h17 == n20->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey0_idxfn::equals(se81, *e20)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0* i21 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2.index[1]);
          const HASH_RES_t h18 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey0_idxfn::hash(se83.modify0(orders_orderkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0::IdxNode* n21 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0::IdxNode*>(i21->slice(se83, h18));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry* e21;
         
          if (n21 && (e21 = n21->obj)) {
            do {                
              long mkt_sharepart1customer2supplier2partpart_partkey = e21->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY;
              long mkt_sharepart1customer2suppliersupplier_suppkey = e21->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v21 = e21->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2.addOrDelOnZero(se82.modify(mkt_sharepart1customer2supplier2partpart_partkey,mkt_sharepart1customer2suppliersupplier_suppkey,orders_custkey,orders_orderdate),v21) : (void)0);
              n21 = n21->nxt;
            } while (n21 && (e21 = n21->obj) && h18 == n21->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey0_idxfn::equals(se83, *e21)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREORDERS6PART2_map_0* i22 = static_cast<HashIndex_MKT_SHAREORDERS6PART2_map_0*>(MKT_SHAREORDERS6PART2.index[1]);
          const HASH_RES_t h19 = MKT_SHAREORDERS6PART2_mapkey0_idxfn::hash(se85.modify0(orders_orderkey));
          HashIndex_MKT_SHAREORDERS6PART2_map_0::IdxNode* n22 = static_cast<HashIndex_MKT_SHAREORDERS6PART2_map_0::IdxNode*>(i22->slice(se85, h19));
          MKT_SHAREORDERS6PART2_entry* e22;
         
          if (n22 && (e22 = n22->obj)) {
            do {                
              long mkt_sharepart1customer2partpart_partkey = e22->MKT_SHAREORDERS6PARTPART_PARTKEY;
              DOUBLE_TYPE v22 = e22->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1CUSTOMER2PART2.addOrDelOnZero(se84.modify(mkt_sharepart1customer2partpart_partkey,orders_custkey,orders_orderdate),v22) : (void)0);
              n22 = n22->nxt;
            } while (n22 && (e22 = n22->obj) && h19 == n22->hash &&  MKT_SHAREORDERS6PART2_mapkey0_idxfn::equals(se85, *e22)); 
          }
        }(/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1LINEITEM1.addOrDelOnZero(se86.modify(orders_orderkey,orders_orderdate),MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se87.modify(orders_custkey))) : (void)0);
        { //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0* i23 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1.index[1]);
          const HASH_RES_t h20 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey0_idxfn::hash(se90.modify0(orders_orderkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0::IdxNode* n23 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0::IdxNode*>(i23->slice(se90, h20));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry* e23;
         
          if (n23 && (e23 = n23->obj)) {
            do {                
              long mkt_sharepart1suppliersupplier_suppkey = e23->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v23 = e23->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1SUPPLIER1.addOrDelOnZero(se88.modify(mkt_sharepart1suppliersupplier_suppkey,orders_orderdate),(MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se89.modify(orders_custkey)) * v23)) : (void)0);
              n23 = n23->nxt;
            } while (n23 && (e23 = n23->obj) && h20 == n23->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey0_idxfn::equals(se90, *e23)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0* i24 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2.index[1]);
          const HASH_RES_t h21 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey0_idxfn::hash(se93.modify0(orders_orderkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0::IdxNode* n24 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0::IdxNode*>(i24->slice(se93, h21));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              long mkt_sharepart1supplier1partpart_partkey = e24->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY;
              long mkt_sharepart1suppliersupplier_suppkey = e24->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v24 = e24->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1SUPPLIER1PART2.addOrDelOnZero(se91.modify(mkt_sharepart1supplier1partpart_partkey,mkt_sharepart1suppliersupplier_suppkey,orders_orderdate),(MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se92.modify(orders_custkey)) * v24)) : (void)0);
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h21 == n24->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey0_idxfn::equals(se93, *e24)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREORDERS6PART2_map_0* i25 = static_cast<HashIndex_MKT_SHAREORDERS6PART2_map_0*>(MKT_SHAREORDERS6PART2.index[1]);
          const HASH_RES_t h22 = MKT_SHAREORDERS6PART2_mapkey0_idxfn::hash(se96.modify0(orders_orderkey));
          HashIndex_MKT_SHAREORDERS6PART2_map_0::IdxNode* n25 = static_cast<HashIndex_MKT_SHAREORDERS6PART2_map_0::IdxNode*>(i25->slice(se96, h22));
          MKT_SHAREORDERS6PART2_entry* e25;
         
          if (n25 && (e25 = n25->obj)) {
            do {                
              long mkt_sharepart1partpart_partkey = e25->MKT_SHAREORDERS6PARTPART_PARTKEY;
              DOUBLE_TYPE v25 = e25->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1PART2.addOrDelOnZero(se94.modify(mkt_sharepart1partpart_partkey,orders_orderdate),(MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se95.modify(orders_custkey)) * v25)) : (void)0);
              n25 = n25->nxt;
            } while (n25 && (e25 = n25->obj) && h22 == n25->hash &&  MKT_SHAREORDERS6PART2_mapkey0_idxfn::equals(se96, *e25)); 
          }
        }long l11 = Uyear_part(orders_orderdate);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1_L2_1_L1_1.addOrDelOnZero(se97.modify(l11),(MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se98.modify(orders_custkey)) * MKT_SHAREORDERS1_L2_1_L1_5.getValueOrDefault(se99.modify(orders_orderkey)))) : (void)0);
        long l12 = Uyear_part(orders_orderdate);
        (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHAREPART1_L2_1_L1_1CUSTOMER2.addOrDelOnZero(se100.modify(orders_custkey,l12),MKT_SHAREORDERS1_L2_1_L1_5.getValueOrDefault(se101.modify(orders_orderkey))) : (void)0);
        long l13 = Uyear_part(orders_orderdate);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2.addOrDelOnZero(se102.modify(orders_orderkey,orders_custkey,l13),1L) : (void)0);
        long l14 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0* i26 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1.index[1]);
          const HASH_RES_t h23 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey0_idxfn::hash(se104.modify0(orders_orderkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0::IdxNode* n26 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0::IdxNode*>(i26->slice(se104, h23));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry* e26;
         
          if (n26 && (e26 = n26->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1customer2suppliersupplier_suppkey = e26->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v26 = e26->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1.addOrDelOnZero(se103.modify(mkt_sharepart1_l2_1_l1_1customer2suppliersupplier_suppkey,orders_custkey,l14),v26) : (void)0);
              n26 = n26->nxt;
            } while (n26 && (e26 = n26->obj) && h23 == n26->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey0_idxfn::equals(se104, *e26)); 
          }
        }long l15 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0* i27 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2.index[1]);
          const HASH_RES_t h24 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey0_idxfn::hash(se106.modify0(orders_orderkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0::IdxNode* n27 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0::IdxNode*>(i27->slice(se106, h24));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry* e27;
         
          if (n27 && (e27 = n27->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1customer2supplier1partpart_partkey = e27->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY;
              long mkt_sharepart1_l2_1_l1_1customer2suppliersupplier_suppkey = e27->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v27 = e27->__av;
              (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2.addOrDelOnZero(se105.modify(mkt_sharepart1_l2_1_l1_1customer2supplier1partpart_partkey,mkt_sharepart1_l2_1_l1_1customer2suppliersupplier_suppkey,orders_custkey,l15),v27) : (void)0);
              n27 = n27->nxt;
            } while (n27 && (e27 = n27->obj) && h24 == n27->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey0_idxfn::equals(se106, *e27)); 
          }
        }long l16 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_0* i28 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_0*>(MKT_SHAREORDERS1_L2_1_L1_5PART2.index[1]);
          const HASH_RES_t h25 = MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey0_idxfn::hash(se108.modify0(orders_orderkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_0::IdxNode* n28 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_0::IdxNode*>(i28->slice(se108, h25));
          MKT_SHAREORDERS1_L2_1_L1_5PART2_entry* e28;
         
          if (n28 && (e28 = n28->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1customer2partpart_partkey = e28->MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY;
              DOUBLE_TYPE v28 = e28->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2.addOrDelOnZero(se107.modify(mkt_sharepart1_l2_1_l1_1customer2partpart_partkey,orders_custkey,l16),v28) : (void)0);
              n28 = n28->nxt;
            } while (n28 && (e28 = n28->obj) && h25 == n28->hash &&  MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey0_idxfn::equals(se108, *e28)); 
          }
        }long l17 = Uyear_part(orders_orderdate);
        (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHAREPART1_L2_1_L1_1LINEITEM1.addOrDelOnZero(se109.modify(orders_orderkey,l17),MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se110.modify(orders_custkey))) : (void)0);
        long l18 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0* i29 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1.index[1]);
          const HASH_RES_t h26 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey0_idxfn::hash(se113.modify0(orders_orderkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0::IdxNode* n29 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_0::IdxNode*>(i29->slice(se113, h26));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry* e29;
         
          if (n29 && (e29 = n29->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1suppliersupplier_suppkey = e29->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v29 = e29->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1_L2_1_L1_1SUPPLIER1.addOrDelOnZero(se111.modify(mkt_sharepart1_l2_1_l1_1suppliersupplier_suppkey,l18),(MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se112.modify(orders_custkey)) * v29)) : (void)0);
              n29 = n29->nxt;
            } while (n29 && (e29 = n29->obj) && h26 == n29->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey0_idxfn::equals(se113, *e29)); 
          }
        }long l19 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0* i30 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2.index[1]);
          const HASH_RES_t h27 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey0_idxfn::hash(se116.modify0(orders_orderkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0::IdxNode* n30 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_0::IdxNode*>(i30->slice(se116, h27));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry* e30;
         
          if (n30 && (e30 = n30->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1supplier1partpart_partkey = e30->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY;
              long mkt_sharepart1_l2_1_l1_1suppliersupplier_suppkey = e30->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v30 = e30->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2.addOrDelOnZero(se114.modify(mkt_sharepart1_l2_1_l1_1supplier1partpart_partkey,mkt_sharepart1_l2_1_l1_1suppliersupplier_suppkey,l19),(MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se115.modify(orders_custkey)) * v30)) : (void)0);
              n30 = n30->nxt;
            } while (n30 && (e30 = n30->obj) && h27 == n30->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey0_idxfn::equals(se116, *e30)); 
          }
        }long l20 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_0* i31 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_0*>(MKT_SHAREORDERS1_L2_1_L1_5PART2.index[1]);
          const HASH_RES_t h28 = MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey0_idxfn::hash(se119.modify0(orders_orderkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_0::IdxNode* n31 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_0::IdxNode*>(i31->slice(se119, h28));
          MKT_SHAREORDERS1_L2_1_L1_5PART2_entry* e31;
         
          if (n31 && (e31 = n31->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1partpart_partkey = e31->MKT_SHAREORDERS1_L2_1_L1_5PARTPART_PARTKEY;
              DOUBLE_TYPE v31 = e31->__av;
              (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHAREPART1_L2_1_L1_1PART2.addOrDelOnZero(se117.modify(mkt_sharepart1_l2_1_l1_1partpart_partkey,l20),(MKT_SHAREORDERS1_L2_1_L1_4.getValueOrDefault(se118.modify(orders_custkey)) * v31)) : (void)0);
              n31 = n31->nxt;
            } while (n31 && (e31 = n31->obj) && h28 == n31->hash &&  MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey0_idxfn::equals(se119, *e31)); 
          }
        }
      }
    }
    void on_insert_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_1* i32 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_1*>(MKT_SHAREORDERS1_L2_1_L1_5PART2.index[2]);
          const HASH_RES_t h29 = MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey1_idxfn::hash(se121.modify1(part_partkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_1::IdxNode* n32 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5PART2_map_1::IdxNode*>(i32->slice(se121, h29));
          MKT_SHAREORDERS1_L2_1_L1_5PART2_entry* e32;
         
          if (n32 && (e32 = n32->obj)) {
            do {                
              long mkt_shareordersorders_orderkey = e32->MKT_SHAREORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v32 = e32->__av;
              (/*if */(part_type == c3) ? MKT_SHAREORDERS1_L2_1_L1_5.addOrDelOnZero(se120.modify(mkt_shareordersorders_orderkey),v32) : (void)0);
              n32 = n32->nxt;
            } while (n32 && (e32 = n32->obj) && h29 == n32->hash &&  MKT_SHAREORDERS1_L2_1_L1_5PART2_mapkey1_idxfn::equals(se121, *e32)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_1* i33 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_1*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2.index[2]);
          const HASH_RES_t h30 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey1_idxfn::hash(se123.modify1(part_partkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_1::IdxNode* n33 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_1::IdxNode*>(i33->slice(se123, h30));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry* e33;
         
          if (n33 && (e33 = n33->obj)) {
            do {                
              long mkt_shareordersorders_orderkey = e33->MKT_SHAREORDERSORDERS_ORDERKEY;
              long mkt_shareorders1_l2_1_l1_5suppliersupplier_suppkey = e33->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v33 = e33->__av;
              (/*if */(part_type == c3) ? MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1.addOrDelOnZero(se122.modify(mkt_shareordersorders_orderkey,mkt_shareorders1_l2_1_l1_5suppliersupplier_suppkey),v33) : (void)0);
              n33 = n33->nxt;
            } while (n33 && (e33 = n33->obj) && h30 == n33->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey1_idxfn::equals(se123, *e33)); 
          }
        }(/*if */(part_type == c3) ? MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1.addOrDelOnZero(se124.modify(part_partkey),1L) : (void)0);
        { //slice 
          const HashIndex_MKT_SHAREORDERS6PART2_map_1* i34 = static_cast<HashIndex_MKT_SHAREORDERS6PART2_map_1*>(MKT_SHAREORDERS6PART2.index[2]);
          const HASH_RES_t h31 = MKT_SHAREORDERS6PART2_mapkey1_idxfn::hash(se126.modify1(part_partkey));
          HashIndex_MKT_SHAREORDERS6PART2_map_1::IdxNode* n34 = static_cast<HashIndex_MKT_SHAREORDERS6PART2_map_1::IdxNode*>(i34->slice(se126, h31));
          MKT_SHAREORDERS6PART2_entry* e34;
         
          if (n34 && (e34 = n34->obj)) {
            do {                
              long mkt_shareordersorders_orderkey = e34->MKT_SHAREORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v34 = e34->__av;
              (/*if */(part_type == c3) ? MKT_SHAREORDERS6.addOrDelOnZero(se125.modify(mkt_shareordersorders_orderkey),v34) : (void)0);
              n34 = n34->nxt;
            } while (n34 && (e34 = n34->obj) && h31 == n34->hash &&  MKT_SHAREORDERS6PART2_mapkey1_idxfn::equals(se126, *e34)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1PART2_map_0* i35 = static_cast<HashIndex_MKT_SHAREPART1PART2_map_0*>(MKT_SHAREPART1PART2.index[1]);
          const HASH_RES_t h32 = MKT_SHAREPART1PART2_mapkey0_idxfn::hash(se128.modify0(part_partkey));
          HashIndex_MKT_SHAREPART1PART2_map_0::IdxNode* n35 = static_cast<HashIndex_MKT_SHAREPART1PART2_map_0::IdxNode*>(i35->slice(se128, h32));
          MKT_SHAREPART1PART2_entry* e35;
         
          if (n35 && (e35 = n35->obj)) {
            do {                
              date o_orderdate = e35->O_ORDERDATE;
              DOUBLE_TYPE v35 = e35->__av;
              (/*if */(part_type == c3) ? MKT_SHAREPART1.addOrDelOnZero(se127.modify(o_orderdate),v35) : (void)0);
              n35 = n35->nxt;
            } while (n35 && (e35 = n35->obj) && h32 == n35->hash &&  MKT_SHAREPART1PART2_mapkey0_idxfn::equals(se128, *e35)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2PART2_map_0* i36 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2PART2_map_0*>(MKT_SHAREPART1CUSTOMER2PART2.index[1]);
          const HASH_RES_t h33 = MKT_SHAREPART1CUSTOMER2PART2_mapkey0_idxfn::hash(se130.modify0(part_partkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2PART2_map_0::IdxNode* n36 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2PART2_map_0::IdxNode*>(i36->slice(se130, h33));
          MKT_SHAREPART1CUSTOMER2PART2_entry* e36;
         
          if (n36 && (e36 = n36->obj)) {
            do {                
              long mkt_sharepart1customercustomer_custkey = e36->MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e36->O_ORDERDATE;
              DOUBLE_TYPE v36 = e36->__av;
              (/*if */(part_type == c3) ? MKT_SHAREPART1CUSTOMER2.addOrDelOnZero(se129.modify(mkt_sharepart1customercustomer_custkey,o_orderdate),v36) : (void)0);
              n36 = n36->nxt;
            } while (n36 && (e36 = n36->obj) && h33 == n36->hash &&  MKT_SHAREPART1CUSTOMER2PART2_mapkey0_idxfn::equals(se130, *e36)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_0* i37 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_0*>(MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2.index[1]);
          const HASH_RES_t h34 = MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey0_idxfn::hash(se132.modify0(part_partkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_0::IdxNode* n37 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_0::IdxNode*>(i37->slice(se132, h34));
          MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry* e37;
         
          if (n37 && (e37 = n37->obj)) {
            do {                
              long mkt_sharepart1customer2suppliersupplier_suppkey = e37->MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY;
              long mkt_sharepart1customercustomer_custkey = e37->MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e37->O_ORDERDATE;
              DOUBLE_TYPE v37 = e37->__av;
              (/*if */(part_type == c3) ? MKT_SHAREPART1CUSTOMER2SUPPLIER2.addOrDelOnZero(se131.modify(mkt_sharepart1customer2suppliersupplier_suppkey,mkt_sharepart1customercustomer_custkey,o_orderdate),v37) : (void)0);
              n37 = n37->nxt;
            } while (n37 && (e37 = n37->obj) && h34 == n37->hash &&  MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey0_idxfn::equals(se132, *e37)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1SUPPLIER1PART2_map_0* i38 = static_cast<HashIndex_MKT_SHAREPART1SUPPLIER1PART2_map_0*>(MKT_SHAREPART1SUPPLIER1PART2.index[1]);
          const HASH_RES_t h35 = MKT_SHAREPART1SUPPLIER1PART2_mapkey0_idxfn::hash(se134.modify0(part_partkey));
          HashIndex_MKT_SHAREPART1SUPPLIER1PART2_map_0::IdxNode* n38 = static_cast<HashIndex_MKT_SHAREPART1SUPPLIER1PART2_map_0::IdxNode*>(i38->slice(se134, h35));
          MKT_SHAREPART1SUPPLIER1PART2_entry* e38;
         
          if (n38 && (e38 = n38->obj)) {
            do {                
              long mkt_sharepart1suppliersupplier_suppkey = e38->MKT_SHAREPART1SUPPLIERSUPPLIER_SUPPKEY;
              date o_orderdate = e38->O_ORDERDATE;
              DOUBLE_TYPE v38 = e38->__av;
              (/*if */(part_type == c3) ? MKT_SHAREPART1SUPPLIER1.addOrDelOnZero(se133.modify(mkt_sharepart1suppliersupplier_suppkey,o_orderdate),v38) : (void)0);
              n38 = n38->nxt;
            } while (n38 && (e38 = n38->obj) && h35 == n38->hash &&  MKT_SHAREPART1SUPPLIER1PART2_mapkey0_idxfn::equals(se134, *e38)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1PART2_map_0* i39 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1PART2_map_0*>(MKT_SHAREPART1_L2_1_L1_1PART2.index[1]);
          const HASH_RES_t h36 = MKT_SHAREPART1_L2_1_L1_1PART2_mapkey0_idxfn::hash(se136.modify0(part_partkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1PART2_map_0::IdxNode* n39 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1PART2_map_0::IdxNode*>(i39->slice(se136, h36));
          MKT_SHAREPART1_L2_1_L1_1PART2_entry* e39;
         
          if (n39 && (e39 = n39->obj)) {
            do {                
              long total_o_year = e39->TOTAL_O_YEAR;
              DOUBLE_TYPE v39 = e39->__av;
              (/*if */(part_type == c3) ? MKT_SHAREPART1_L2_1_L1_1.addOrDelOnZero(se135.modify(total_o_year),v39) : (void)0);
              n39 = n39->nxt;
            } while (n39 && (e39 = n39->obj) && h36 == n39->hash &&  MKT_SHAREPART1_L2_1_L1_1PART2_mapkey0_idxfn::equals(se136, *e39)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map_0* i40 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map_0*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2.index[1]);
          const HASH_RES_t h37 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey0_idxfn::hash(se138.modify0(part_partkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map_0::IdxNode* n40 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map_0::IdxNode*>(i40->slice(se138, h37));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry* e40;
         
          if (n40 && (e40 = n40->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1customercustomer_custkey = e40->MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e40->TOTAL_O_YEAR;
              DOUBLE_TYPE v40 = e40->__av;
              (/*if */(part_type == c3) ? MKT_SHAREPART1_L2_1_L1_1CUSTOMER2.addOrDelOnZero(se137.modify(mkt_sharepart1_l2_1_l1_1customercustomer_custkey,total_o_year),v40) : (void)0);
              n40 = n40->nxt;
            } while (n40 && (e40 = n40->obj) && h37 == n40->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey0_idxfn::equals(se138, *e40)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_0* i41 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_0*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2.index[1]);
          const HASH_RES_t h38 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey0_idxfn::hash(se140.modify0(part_partkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_0::IdxNode* n41 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_0::IdxNode*>(i41->slice(se140, h38));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry* e41;
         
          if (n41 && (e41 = n41->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1customer2suppliersupplier_suppkey = e41->MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY;
              long mkt_sharepart1_l2_1_l1_1customercustomer_custkey = e41->MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e41->TOTAL_O_YEAR;
              DOUBLE_TYPE v41 = e41->__av;
              (/*if */(part_type == c3) ? MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1.addOrDelOnZero(se139.modify(mkt_sharepart1_l2_1_l1_1customer2suppliersupplier_suppkey,mkt_sharepart1_l2_1_l1_1customercustomer_custkey,total_o_year),v41) : (void)0);
              n41 = n41->nxt;
            } while (n41 && (e41 = n41->obj) && h38 == n41->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey0_idxfn::equals(se140, *e41)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map_0* i42 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map_0*>(MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2.index[1]);
          const HASH_RES_t h39 = MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey0_idxfn::hash(se142.modify0(part_partkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map_0::IdxNode* n42 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map_0::IdxNode*>(i42->slice(se142, h39));
          MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry* e42;
         
          if (n42 && (e42 = n42->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1suppliersupplier_suppkey = e42->MKT_SHAREPART1_L2_1_L1_1SUPPLIERSUPPLIER_SUPPKEY;
              long total_o_year = e42->TOTAL_O_YEAR;
              DOUBLE_TYPE v42 = e42->__av;
              (/*if */(part_type == c3) ? MKT_SHAREPART1_L2_1_L1_1SUPPLIER1.addOrDelOnZero(se141.modify(mkt_sharepart1_l2_1_l1_1suppliersupplier_suppkey,total_o_year),v42) : (void)0);
              n42 = n42->nxt;
            } while (n42 && (e42 = n42->obj) && h39 == n42->hash &&  MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey0_idxfn::equals(se142, *e42)); 
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHAREPART1_map_0* i43 = static_cast<HashIndex_MKT_SHAREPART1_map_0*>(MKT_SHAREPART1.index[0]);
          HashIndex_MKT_SHAREPART1_map_0::IdxNode* n43; 
          MKT_SHAREPART1_entry* e43;
        
          for (size_t i = 0; i < i43->size_; i++)
          {
            n43 = i43->buckets_ + i;
            while (n43 && (e43 = n43->obj))
            {
                date o_orderdate = e43->O_ORDERDATE;
                DOUBLE_TYPE v43 = e43->__av;
                long l21 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg8 = 0.0;
                DOUBLE_TYPE l23 = MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se144.modify(l21));
                agg8 += Ulistmax(1L, l23);
                DOUBLE_TYPE l22 = agg8;
                MKT_SHARE.addOrDelOnZero(se143.modify(l21),(v43 * Udiv(l22)));
              n43 = n43->nxt;
            }
          }
        }
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        MKT_SHAREORDERS1_L2_1_L1_4.addOrDelOnZero(se145.modify(customer_custkey),MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.getValueOrDefault(se146.modify(customer_nationkey)));
        { //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2_map_0* i44 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2_map_0*>(MKT_SHAREPART1CUSTOMER2.index[1]);
          const HASH_RES_t h40 = MKT_SHAREPART1CUSTOMER2_mapkey0_idxfn::hash(se149.modify0(customer_custkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2_map_0::IdxNode* n44 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2_map_0::IdxNode*>(i44->slice(se149, h40));
          MKT_SHAREPART1CUSTOMER2_entry* e44;
         
          if (n44 && (e44 = n44->obj)) {
            do {                
              date o_orderdate = e44->O_ORDERDATE;
              DOUBLE_TYPE v44 = e44->__av;
              MKT_SHAREPART1.addOrDelOnZero(se147.modify(o_orderdate),(MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.getValueOrDefault(se148.modify(customer_nationkey)) * v44));
              n44 = n44->nxt;
            } while (n44 && (e44 = n44->obj) && h40 == n44->hash &&  MKT_SHAREPART1CUSTOMER2_mapkey0_idxfn::equals(se149, *e44)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_1* i45 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_1*>(MKT_SHAREPART1CUSTOMER2LINEITEM3.index[2]);
          const HASH_RES_t h41 = MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey1_idxfn::hash(se152.modify1(customer_custkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_1::IdxNode* n45 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2LINEITEM3_map_1::IdxNode*>(i45->slice(se152, h41));
          MKT_SHAREPART1CUSTOMER2LINEITEM3_entry* e45;
         
          if (n45 && (e45 = n45->obj)) {
            do {                
              long mkt_sharepart1lineitemlineitem_orderkey = e45->MKT_SHAREPART1CUSTOMER2LINEITEMLINEITEM_ORDERKEY;
              date o_orderdate = e45->O_ORDERDATE;
              long v45 = e45->__av;
              MKT_SHAREPART1LINEITEM1.addOrDelOnZero(se150.modify(mkt_sharepart1lineitemlineitem_orderkey,o_orderdate),(MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.getValueOrDefault(se151.modify(customer_nationkey)) * v45));
              n45 = n45->nxt;
            } while (n45 && (e45 = n45->obj) && h41 == n45->hash &&  MKT_SHAREPART1CUSTOMER2LINEITEM3_mapkey1_idxfn::equals(se152, *e45)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2_map_1* i46 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2_map_1*>(MKT_SHAREPART1CUSTOMER2SUPPLIER2.index[1]);
          const HASH_RES_t h42 = MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey1_idxfn::hash(se155.modify1(customer_custkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2_map_1::IdxNode* n46 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2_map_1::IdxNode*>(i46->slice(se155, h42));
          MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry* e46;
         
          if (n46 && (e46 = n46->obj)) {
            do {                
              long mkt_sharepart1suppliersupplier_suppkey = e46->MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY;
              date o_orderdate = e46->O_ORDERDATE;
              DOUBLE_TYPE v46 = e46->__av;
              MKT_SHAREPART1SUPPLIER1.addOrDelOnZero(se153.modify(mkt_sharepart1suppliersupplier_suppkey,o_orderdate),(MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.getValueOrDefault(se154.modify(customer_nationkey)) * v46));
              n46 = n46->nxt;
            } while (n46 && (e46 = n46->obj) && h42 == n46->hash &&  MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey1_idxfn::equals(se155, *e46)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_2* i47 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_2*>(MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2.index[2]);
          const HASH_RES_t h43 = MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey2_idxfn::hash(se158.modify2(customer_custkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_2::IdxNode* n47 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_2::IdxNode*>(i47->slice(se158, h43));
          MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry* e47;
         
          if (n47 && (e47 = n47->obj)) {
            do {                
              long mkt_sharepart1supplier1partpart_partkey = e47->MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY;
              long mkt_sharepart1suppliersupplier_suppkey = e47->MKT_SHAREPART1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY;
              date o_orderdate = e47->O_ORDERDATE;
              DOUBLE_TYPE v47 = e47->__av;
              MKT_SHAREPART1SUPPLIER1PART2.addOrDelOnZero(se156.modify(mkt_sharepart1supplier1partpart_partkey,mkt_sharepart1suppliersupplier_suppkey,o_orderdate),(MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.getValueOrDefault(se157.modify(customer_nationkey)) * v47));
              n47 = n47->nxt;
            } while (n47 && (e47 = n47->obj) && h43 == n47->hash &&  MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey2_idxfn::equals(se158, *e47)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2PART2_map_1* i48 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2PART2_map_1*>(MKT_SHAREPART1CUSTOMER2PART2.index[2]);
          const HASH_RES_t h44 = MKT_SHAREPART1CUSTOMER2PART2_mapkey1_idxfn::hash(se161.modify1(customer_custkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2PART2_map_1::IdxNode* n48 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2PART2_map_1::IdxNode*>(i48->slice(se161, h44));
          MKT_SHAREPART1CUSTOMER2PART2_entry* e48;
         
          if (n48 && (e48 = n48->obj)) {
            do {                
              long mkt_sharepart1partpart_partkey = e48->MKT_SHAREPART1CUSTOMER2PARTPART_PARTKEY;
              date o_orderdate = e48->O_ORDERDATE;
              DOUBLE_TYPE v48 = e48->__av;
              MKT_SHAREPART1PART2.addOrDelOnZero(se159.modify(mkt_sharepart1partpart_partkey,o_orderdate),(MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.getValueOrDefault(se160.modify(customer_nationkey)) * v48));
              n48 = n48->nxt;
            } while (n48 && (e48 = n48->obj) && h44 == n48->hash &&  MKT_SHAREPART1CUSTOMER2PART2_mapkey1_idxfn::equals(se161, *e48)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_map_0* i49 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_map_0*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2.index[1]);
          const HASH_RES_t h45 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_mapkey0_idxfn::hash(se164.modify0(customer_custkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_map_0::IdxNode* n49 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_map_0::IdxNode*>(i49->slice(se164, h45));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry* e49;
         
          if (n49 && (e49 = n49->obj)) {
            do {                
              long total_o_year = e49->TOTAL_O_YEAR;
              DOUBLE_TYPE v49 = e49->__av;
              MKT_SHAREPART1_L2_1_L1_1.addOrDelOnZero(se162.modify(total_o_year),(MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.getValueOrDefault(se163.modify(customer_nationkey)) * v49));
              n49 = n49->nxt;
            } while (n49 && (e49 = n49->obj) && h45 == n49->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_mapkey0_idxfn::equals(se164, *e49)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_1* i50 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_1*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2.index[2]);
          const HASH_RES_t h46 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey1_idxfn::hash(se167.modify1(customer_custkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_1::IdxNode* n50 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map_1::IdxNode*>(i50->slice(se167, h46));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry* e50;
         
          if (n50 && (e50 = n50->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1lineitemlineitem_orderkey = e50->MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEMLINEITEM_ORDERKEY;
              long total_o_year = e50->TOTAL_O_YEAR;
              long v50 = e50->__av;
              MKT_SHAREPART1_L2_1_L1_1LINEITEM1.addOrDelOnZero(se165.modify(mkt_sharepart1_l2_1_l1_1lineitemlineitem_orderkey,total_o_year),(MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.getValueOrDefault(se166.modify(customer_nationkey)) * v50));
              n50 = n50->nxt;
            } while (n50 && (e50 = n50->obj) && h46 == n50->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_mapkey1_idxfn::equals(se167, *e50)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map_1* i51 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map_1*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1.index[1]);
          const HASH_RES_t h47 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey1_idxfn::hash(se170.modify1(customer_custkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map_1::IdxNode* n51 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map_1::IdxNode*>(i51->slice(se170, h47));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry* e51;
         
          if (n51 && (e51 = n51->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1suppliersupplier_suppkey = e51->MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY;
              long total_o_year = e51->TOTAL_O_YEAR;
              DOUBLE_TYPE v51 = e51->__av;
              MKT_SHAREPART1_L2_1_L1_1SUPPLIER1.addOrDelOnZero(se168.modify(mkt_sharepart1_l2_1_l1_1suppliersupplier_suppkey,total_o_year),(MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.getValueOrDefault(se169.modify(customer_nationkey)) * v51));
              n51 = n51->nxt;
            } while (n51 && (e51 = n51->obj) && h47 == n51->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey1_idxfn::equals(se170, *e51)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_2* i52 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_2*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2.index[2]);
          const HASH_RES_t h48 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey2_idxfn::hash(se173.modify2(customer_custkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_2::IdxNode* n52 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_2::IdxNode*>(i52->slice(se173, h48));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry* e52;
         
          if (n52 && (e52 = n52->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1supplier1partpart_partkey = e52->MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY;
              long mkt_sharepart1_l2_1_l1_1suppliersupplier_suppkey = e52->MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIERSUPPLIER_SUPPKEY;
              long total_o_year = e52->TOTAL_O_YEAR;
              DOUBLE_TYPE v52 = e52->__av;
              MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2.addOrDelOnZero(se171.modify(mkt_sharepart1_l2_1_l1_1supplier1partpart_partkey,mkt_sharepart1_l2_1_l1_1suppliersupplier_suppkey,total_o_year),(MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.getValueOrDefault(se172.modify(customer_nationkey)) * v52));
              n52 = n52->nxt;
            } while (n52 && (e52 = n52->obj) && h48 == n52->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey2_idxfn::equals(se173, *e52)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map_1* i53 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map_1*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2.index[2]);
          const HASH_RES_t h49 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey1_idxfn::hash(se176.modify1(customer_custkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map_1::IdxNode* n53 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map_1::IdxNode*>(i53->slice(se176, h49));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry* e53;
         
          if (n53 && (e53 = n53->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1partpart_partkey = e53->MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PARTPART_PARTKEY;
              long total_o_year = e53->TOTAL_O_YEAR;
              DOUBLE_TYPE v53 = e53->__av;
              MKT_SHAREPART1_L2_1_L1_1PART2.addOrDelOnZero(se174.modify(mkt_sharepart1_l2_1_l1_1partpart_partkey,total_o_year),(MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.getValueOrDefault(se175.modify(customer_nationkey)) * v53));
              n53 = n53->nxt;
            } while (n53 && (e53 = n53->obj) && h49 == n53->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_mapkey1_idxfn::equals(se176, *e53)); 
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHAREPART1_map_0* i54 = static_cast<HashIndex_MKT_SHAREPART1_map_0*>(MKT_SHAREPART1.index[0]);
          HashIndex_MKT_SHAREPART1_map_0::IdxNode* n54; 
          MKT_SHAREPART1_entry* e54;
        
          for (size_t i = 0; i < i54->size_; i++)
          {
            n54 = i54->buckets_ + i;
            while (n54 && (e54 = n54->obj))
            {
                date o_orderdate = e54->O_ORDERDATE;
                DOUBLE_TYPE v54 = e54->__av;
                long l24 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg9 = 0.0;
                DOUBLE_TYPE l26 = MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se178.modify(l24));
                agg9 += Ulistmax(1L, l26);
                DOUBLE_TYPE l25 = agg9;
                MKT_SHARE.addOrDelOnZero(se177.modify(l24),(v54 * Udiv(l25)));
              n54 = n54->nxt;
            }
          }
        }
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_1* i55 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_1*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1.index[2]);
          const HASH_RES_t h50 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey1_idxfn::hash(se181.modify1(supplier_suppkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_1::IdxNode* n55 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_1::IdxNode*>(i55->slice(se181, h50));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry* e55;
         
          if (n55 && (e55 = n55->obj)) {
            do {                
              long mkt_shareordersorders_orderkey = e55->MKT_SHAREORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v55 = e55->__av;
              MKT_SHAREORDERS1_L2_1_L1_5.addOrDelOnZero(se179.modify(mkt_shareordersorders_orderkey),(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2.getValueOrDefault(se180.modify(supplier_nationkey)) * v55));
              n55 = n55->nxt;
            } while (n55 && (e55 = n55->obj) && h50 == n55->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey1_idxfn::equals(se181, *e55)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_2* i56 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_2*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2.index[3]);
          const HASH_RES_t h51 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey2_idxfn::hash(se184.modify2(supplier_suppkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_2::IdxNode* n56 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_2::IdxNode*>(i56->slice(se184, h51));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry* e56;
         
          if (n56 && (e56 = n56->obj)) {
            do {                
              long mkt_shareordersorders_orderkey = e56->MKT_SHAREORDERSORDERS_ORDERKEY;
              long mkt_shareorders1_l2_1_l1_5partpart_partkey = e56->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY;
              DOUBLE_TYPE v56 = e56->__av;
              MKT_SHAREORDERS1_L2_1_L1_5PART2.addOrDelOnZero(se182.modify(mkt_shareordersorders_orderkey,mkt_shareorders1_l2_1_l1_5partpart_partkey),(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2.getValueOrDefault(se183.modify(supplier_nationkey)) * v56));
              n56 = n56->nxt;
            } while (n56 && (e56 = n56->obj) && h51 == n56->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey2_idxfn::equals(se184, *e56)); 
          }
        }MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2.addOrDelOnZero(se185.modify(supplier_suppkey),MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2.getValueOrDefault(se186.modify(supplier_nationkey)));
        { //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_1* i57 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_1*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1.index[2]);
          const HASH_RES_t h52 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey1_idxfn::hash(se189.modify1(supplier_suppkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_1::IdxNode* n57 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map_1::IdxNode*>(i57->slice(se189, h52));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry* e57;
         
          if (n57 && (e57 = n57->obj)) {
            do {                
              long mkt_shareordersorders_orderkey = e57->MKT_SHAREORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v57 = e57->__av;
              MKT_SHAREORDERS6.addOrDelOnZero(se187.modify(mkt_shareordersorders_orderkey),(MKT_SHAREORDERS6SUPPLIER2.getValueOrDefault(se188.modify(supplier_nationkey)) * v57));
              n57 = n57->nxt;
            } while (n57 && (e57 = n57->obj) && h52 == n57->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_mapkey1_idxfn::equals(se189, *e57)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_2* i58 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_2*>(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2.index[3]);
          const HASH_RES_t h53 = MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey2_idxfn::hash(se192.modify2(supplier_suppkey));
          HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_2::IdxNode* n58 = static_cast<HashIndex_MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map_2::IdxNode*>(i58->slice(se192, h53));
          MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry* e58;
         
          if (n58 && (e58 = n58->obj)) {
            do {                
              long mkt_shareordersorders_orderkey = e58->MKT_SHAREORDERSORDERS_ORDERKEY;
              long mkt_shareorders6partpart_partkey = e58->MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PARTPART_PARTKEY;
              DOUBLE_TYPE v58 = e58->__av;
              MKT_SHAREORDERS6PART2.addOrDelOnZero(se190.modify(mkt_shareordersorders_orderkey,mkt_shareorders6partpart_partkey),(MKT_SHAREORDERS6SUPPLIER2.getValueOrDefault(se191.modify(supplier_nationkey)) * v58));
              n58 = n58->nxt;
            } while (n58 && (e58 = n58->obj) && h53 == n58->hash &&  MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_mapkey2_idxfn::equals(se192, *e58)); 
          }
        }MKT_SHAREORDERS6LINEITEM2.addOrDelOnZero(se193.modify(supplier_suppkey),MKT_SHAREORDERS6SUPPLIER2.getValueOrDefault(se194.modify(supplier_nationkey)));
        { //slice 
          const HashIndex_MKT_SHAREPART1SUPPLIER1_map_0* i59 = static_cast<HashIndex_MKT_SHAREPART1SUPPLIER1_map_0*>(MKT_SHAREPART1SUPPLIER1.index[1]);
          const HASH_RES_t h54 = MKT_SHAREPART1SUPPLIER1_mapkey0_idxfn::hash(se197.modify0(supplier_suppkey));
          HashIndex_MKT_SHAREPART1SUPPLIER1_map_0::IdxNode* n59 = static_cast<HashIndex_MKT_SHAREPART1SUPPLIER1_map_0::IdxNode*>(i59->slice(se197, h54));
          MKT_SHAREPART1SUPPLIER1_entry* e59;
         
          if (n59 && (e59 = n59->obj)) {
            do {                
              date o_orderdate = e59->O_ORDERDATE;
              DOUBLE_TYPE v59 = e59->__av;
              MKT_SHAREPART1.addOrDelOnZero(se195.modify(o_orderdate),(MKT_SHAREORDERS6SUPPLIER2.getValueOrDefault(se196.modify(supplier_nationkey)) * v59));
              n59 = n59->nxt;
            } while (n59 && (e59 = n59->obj) && h54 == n59->hash &&  MKT_SHAREPART1SUPPLIER1_mapkey0_idxfn::equals(se197, *e59)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2_map_0* i60 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2_map_0*>(MKT_SHAREPART1CUSTOMER2SUPPLIER2.index[2]);
          const HASH_RES_t h55 = MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey0_idxfn::hash(se200.modify0(supplier_suppkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2_map_0::IdxNode* n60 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2_map_0::IdxNode*>(i60->slice(se200, h55));
          MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry* e60;
         
          if (n60 && (e60 = n60->obj)) {
            do {                
              long mkt_sharepart1customercustomer_custkey = e60->MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e60->O_ORDERDATE;
              DOUBLE_TYPE v60 = e60->__av;
              MKT_SHAREPART1CUSTOMER2.addOrDelOnZero(se198.modify(mkt_sharepart1customercustomer_custkey,o_orderdate),(MKT_SHAREORDERS6SUPPLIER2.getValueOrDefault(se199.modify(supplier_nationkey)) * v60));
              n60 = n60->nxt;
            } while (n60 && (e60 = n60->obj) && h55 == n60->hash &&  MKT_SHAREPART1CUSTOMER2SUPPLIER2_mapkey0_idxfn::equals(se200, *e60)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_1* i61 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_1*>(MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2.index[3]);
          const HASH_RES_t h56 = MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey1_idxfn::hash(se203.modify1(supplier_suppkey));
          HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_1::IdxNode* n61 = static_cast<HashIndex_MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map_1::IdxNode*>(i61->slice(se203, h56));
          MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry* e61;
         
          if (n61 && (e61 = n61->obj)) {
            do {                
              long mkt_sharepart1customer2partpart_partkey = e61->MKT_SHAREPART1CUSTOMER2SUPPLIER2PARTPART_PARTKEY;
              long mkt_sharepart1customercustomer_custkey = e61->MKT_SHAREPART1CUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e61->O_ORDERDATE;
              DOUBLE_TYPE v61 = e61->__av;
              MKT_SHAREPART1CUSTOMER2PART2.addOrDelOnZero(se201.modify(mkt_sharepart1customer2partpart_partkey,mkt_sharepart1customercustomer_custkey,o_orderdate),(MKT_SHAREORDERS6SUPPLIER2.getValueOrDefault(se202.modify(supplier_nationkey)) * v61));
              n61 = n61->nxt;
            } while (n61 && (e61 = n61->obj) && h56 == n61->hash &&  MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_mapkey1_idxfn::equals(se203, *e61)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1SUPPLIER1PART2_map_1* i62 = static_cast<HashIndex_MKT_SHAREPART1SUPPLIER1PART2_map_1*>(MKT_SHAREPART1SUPPLIER1PART2.index[2]);
          const HASH_RES_t h57 = MKT_SHAREPART1SUPPLIER1PART2_mapkey1_idxfn::hash(se206.modify1(supplier_suppkey));
          HashIndex_MKT_SHAREPART1SUPPLIER1PART2_map_1::IdxNode* n62 = static_cast<HashIndex_MKT_SHAREPART1SUPPLIER1PART2_map_1::IdxNode*>(i62->slice(se206, h57));
          MKT_SHAREPART1SUPPLIER1PART2_entry* e62;
         
          if (n62 && (e62 = n62->obj)) {
            do {                
              long mkt_sharepart1partpart_partkey = e62->MKT_SHAREPART1SUPPLIER1PARTPART_PARTKEY;
              date o_orderdate = e62->O_ORDERDATE;
              DOUBLE_TYPE v62 = e62->__av;
              MKT_SHAREPART1PART2.addOrDelOnZero(se204.modify(mkt_sharepart1partpart_partkey,o_orderdate),(MKT_SHAREORDERS6SUPPLIER2.getValueOrDefault(se205.modify(supplier_nationkey)) * v62));
              n62 = n62->nxt;
            } while (n62 && (e62 = n62->obj) && h57 == n62->hash &&  MKT_SHAREPART1SUPPLIER1PART2_mapkey1_idxfn::equals(se206, *e62)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_map_0* i63 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_map_0*>(MKT_SHAREPART1_L2_1_L1_1SUPPLIER1.index[1]);
          const HASH_RES_t h58 = MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_mapkey0_idxfn::hash(se209.modify0(supplier_suppkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_map_0::IdxNode* n63 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_map_0::IdxNode*>(i63->slice(se209, h58));
          MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry* e63;
         
          if (n63 && (e63 = n63->obj)) {
            do {                
              long total_o_year = e63->TOTAL_O_YEAR;
              DOUBLE_TYPE v63 = e63->__av;
              MKT_SHAREPART1_L2_1_L1_1.addOrDelOnZero(se207.modify(total_o_year),(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2.getValueOrDefault(se208.modify(supplier_nationkey)) * v63));
              n63 = n63->nxt;
            } while (n63 && (e63 = n63->obj) && h58 == n63->hash &&  MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_mapkey0_idxfn::equals(se209, *e63)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map_0* i64 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map_0*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1.index[2]);
          const HASH_RES_t h59 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey0_idxfn::hash(se212.modify0(supplier_suppkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map_0::IdxNode* n64 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map_0::IdxNode*>(i64->slice(se212, h59));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry* e64;
         
          if (n64 && (e64 = n64->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1customercustomer_custkey = e64->MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e64->TOTAL_O_YEAR;
              DOUBLE_TYPE v64 = e64->__av;
              MKT_SHAREPART1_L2_1_L1_1CUSTOMER2.addOrDelOnZero(se210.modify(mkt_sharepart1_l2_1_l1_1customercustomer_custkey,total_o_year),(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2.getValueOrDefault(se211.modify(supplier_nationkey)) * v64));
              n64 = n64->nxt;
            } while (n64 && (e64 = n64->obj) && h59 == n64->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_mapkey0_idxfn::equals(se212, *e64)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_1* i65 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_1*>(MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2.index[3]);
          const HASH_RES_t h60 = MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey1_idxfn::hash(se215.modify1(supplier_suppkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_1::IdxNode* n65 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map_1::IdxNode*>(i65->slice(se215, h60));
          MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry* e65;
         
          if (n65 && (e65 = n65->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1customer2partpart_partkey = e65->MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PARTPART_PARTKEY;
              long mkt_sharepart1_l2_1_l1_1customercustomer_custkey = e65->MKT_SHAREPART1_L2_1_L1_1CUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e65->TOTAL_O_YEAR;
              DOUBLE_TYPE v65 = e65->__av;
              MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2.addOrDelOnZero(se213.modify(mkt_sharepart1_l2_1_l1_1customer2partpart_partkey,mkt_sharepart1_l2_1_l1_1customercustomer_custkey,total_o_year),(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2.getValueOrDefault(se214.modify(supplier_nationkey)) * v65));
              n65 = n65->nxt;
            } while (n65 && (e65 = n65->obj) && h60 == n65->hash &&  MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_mapkey1_idxfn::equals(se215, *e65)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map_1* i66 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map_1*>(MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2.index[2]);
          const HASH_RES_t h61 = MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey1_idxfn::hash(se218.modify1(supplier_suppkey));
          HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map_1::IdxNode* n66 = static_cast<HashIndex_MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map_1::IdxNode*>(i66->slice(se218, h61));
          MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry* e66;
         
          if (n66 && (e66 = n66->obj)) {
            do {                
              long mkt_sharepart1_l2_1_l1_1partpart_partkey = e66->MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PARTPART_PARTKEY;
              long total_o_year = e66->TOTAL_O_YEAR;
              DOUBLE_TYPE v66 = e66->__av;
              MKT_SHAREPART1_L2_1_L1_1PART2.addOrDelOnZero(se216.modify(mkt_sharepart1_l2_1_l1_1partpart_partkey,total_o_year),(MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2.getValueOrDefault(se217.modify(supplier_nationkey)) * v66));
              n66 = n66->nxt;
            } while (n66 && (e66 = n66->obj) && h61 == n66->hash &&  MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_mapkey1_idxfn::equals(se218, *e66)); 
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHAREPART1_map_0* i67 = static_cast<HashIndex_MKT_SHAREPART1_map_0*>(MKT_SHAREPART1.index[0]);
          HashIndex_MKT_SHAREPART1_map_0::IdxNode* n67; 
          MKT_SHAREPART1_entry* e67;
        
          for (size_t i = 0; i < i67->size_; i++)
          {
            n67 = i67->buckets_ + i;
            while (n67 && (e67 = n67->obj))
            {
                date o_orderdate = e67->O_ORDERDATE;
                DOUBLE_TYPE v67 = e67->__av;
                long l27 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg10 = 0.0;
                DOUBLE_TYPE l29 = MKT_SHAREPART1_L2_1_L1_1.getValueOrDefault(se220.modify(l27));
                agg10 += Ulistmax(1L, l29);
                DOUBLE_TYPE l28 = agg10;
                MKT_SHARE.addOrDelOnZero(se219.modify(l27),(v67 * Udiv(l28)));
              n67 = n67->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.clear();
        STRING_TYPE l30 = c4;
        {  // foreach
          const HashIndex_NATION_map_0123* i68 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n68; 
          NATION_entry* e68;
        
          for (size_t i = 0; i < i68->size_; i++)
          {
            n68 = i68->buckets_ + i;
            while (n68 && (e68 = n68->obj))
            {
                long mkt_shareorders1_l2_1_l1_4customercustomer_nationkey = e68->NATION_NATIONKEY;
                STRING_TYPE n1_name = e68->NATION_NAME;
                long n1_regionkey = e68->NATION_REGIONKEY;
                STRING_TYPE n1_comment = e68->NATION_COMMENT;
                long v68 = e68->__av;
                { //slice 
                  const HashIndex_REGION_map_01* i69 = static_cast<HashIndex_REGION_map_01*>(REGION.index[1]);
                  const HASH_RES_t h62 = REGION_mapkey01_idxfn::hash(se222.modify01(n1_regionkey, l30));
                  HashIndex_REGION_map_01::IdxNode* n69 = static_cast<HashIndex_REGION_map_01::IdxNode*>(i69->slice(se222, h62));
                  REGION_entry* e69;
                 
                  if (n69 && (e69 = n69->obj)) {
                    do {                
                      STRING_TYPE r_comment = e69->REGION_COMMENT;
                      long v69 = e69->__av;
                      MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1.addOrDelOnZero(se221.modify(mkt_shareorders1_l2_1_l1_4customercustomer_nationkey),(v68 * v69));
                      n69 = n69->nxt;
                    } while (n69 && (e69 = n69->obj) && h62 == n69->hash &&  REGION_mapkey01_idxfn::equals(se222, *e69)); 
                  }
                }
              n68 = n68->nxt;
            }
          }
        }MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2.clear();
        {  // foreach
          const HashIndex_NATION_map_0123* i70 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n70; 
          NATION_entry* e70;
        
          for (size_t i = 0; i < i70->size_; i++)
          {
            n70 = i70->buckets_ + i;
            while (n70 && (e70 = n70->obj))
            {
                long mkt_shareorders1_l2_1_l1_5suppliersupplier_nationkey = e70->NATION_NATIONKEY;
                STRING_TYPE n2_name = e70->NATION_NAME;
                long n2_regionkey = e70->NATION_REGIONKEY;
                STRING_TYPE n2_comment = e70->NATION_COMMENT;
                long v70 = e70->__av;
                MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2.addOrDelOnZero(se223.modify(mkt_shareorders1_l2_1_l1_5suppliersupplier_nationkey),v70);
              n70 = n70->nxt;
            }
          }
        }MKT_SHAREORDERS6SUPPLIER2.clear();
        STRING_TYPE l31 = c5;
        { //slice 
          const HashIndex_NATION_map_1* i71 = static_cast<HashIndex_NATION_map_1*>(NATION.index[1]);
          const HASH_RES_t h63 = NATION_mapkey1_idxfn::hash(se225.modify1(l31));
          HashIndex_NATION_map_1::IdxNode* n71 = static_cast<HashIndex_NATION_map_1::IdxNode*>(i71->slice(se225, h63));
          NATION_entry* e71;
         
          if (n71 && (e71 = n71->obj)) {
            do {                
              long mkt_shareorders6suppliersupplier_nationkey = e71->NATION_NATIONKEY;
              long n2_regionkey = e71->NATION_REGIONKEY;
              STRING_TYPE n2_comment = e71->NATION_COMMENT;
              long v71 = e71->__av;
              MKT_SHAREORDERS6SUPPLIER2.addOrDelOnZero(se224.modify(mkt_shareorders6suppliersupplier_nationkey),v71);
              n71 = n71->nxt;
            } while (n71 && (e71 = n71->obj) && h63 == n71->hash &&  NATION_mapkey1_idxfn::equals(se225, *e71)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    MKT_SHAREORDERS1_L2_1_L1_5_entry se1;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry se2;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry se3;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry se4;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry se5;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry se6;
    MKT_SHAREORDERS1_L2_1_L1_5PART2_entry se7;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry se8;
    MKT_SHAREORDERS6_entry se9;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry se10;
    MKT_SHAREORDERS6LINEITEM2_entry se11;
    MKT_SHAREORDERS6PART2_entry se12;
    MKT_SHAREORDERS6LINEITEM2_entry se13;
    MKT_SHAREPART1_entry se14;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry se15;
    MKT_SHAREORDERS6LINEITEM2_entry se16;
    MKT_SHAREPART1LINEITEM1_entry se17;
    MKT_SHAREPART1CUSTOMER2_entry se18;
    MKT_SHAREORDERS6LINEITEM2_entry se19;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry se20;
    MKT_SHAREPART1CUSTOMER2LINEITEM3_entry se21;
    MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry se22;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry se23;
    MKT_SHAREPART1CUSTOMER2LINEITEM3_entry se24;
    MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry se25;
    MKT_SHAREPART1CUSTOMER2LINEITEM3_entry se26;
    MKT_SHAREPART1CUSTOMER2PART2_entry se27;
    MKT_SHAREORDERS6LINEITEM2_entry se28;
    MKT_SHAREPART1CUSTOMER2LINEITEM3_entry se29;
    MKT_SHAREPART1SUPPLIER1_entry se30;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry se31;
    MKT_SHAREPART1LINEITEM1_entry se32;
    MKT_SHAREPART1SUPPLIER1PART2_entry se33;
    MKT_SHAREPART1LINEITEM1_entry se34;
    MKT_SHAREPART1PART2_entry se35;
    MKT_SHAREORDERS6LINEITEM2_entry se36;
    MKT_SHAREPART1LINEITEM1_entry se37;
    MKT_SHAREPART1_L2_1_L1_1_entry se38;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry se39;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry se40;
    MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry se41;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry se42;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry se43;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry se44;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry se45;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry se46;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry se47;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry se48;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry se49;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry se50;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry se51;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry se52;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry se53;
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry se54;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry se55;
    MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry se56;
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry se57;
    MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry se58;
    MKT_SHAREPART1_L2_1_L1_1PART2_entry se59;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry se60;
    MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry se61;
    MKT_SHARE_entry se62;
    MKT_SHAREPART1_L2_1_L1_1_entry se63;
    MKT_SHARE_entry se64;
    MKT_SHAREPART1_L2_1_L1_1_entry se65;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se66;
    MKT_SHAREORDERS1_L2_1_L1_5_entry se67;
    MKT_SHAREPART1_L2_1_L1_1_entry se68;
    MKT_SHAREORDERS6_entry se69;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se70;
    MKT_SHAREPART1_L2_1_L1_1_entry se71;
    MKT_SHAREORDERS1_L2_1_L1_5_entry se72;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se73;
    MKT_SHAREPART1_entry se74;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se75;
    MKT_SHAREORDERS6_entry se76;
    MKT_SHAREPART1CUSTOMER2_entry se77;
    MKT_SHAREORDERS6_entry se78;
    MKT_SHAREPART1CUSTOMER2LINEITEM3_entry se79;
    MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry se80;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry se81;
    MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry se82;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry se83;
    MKT_SHAREPART1CUSTOMER2PART2_entry se84;
    MKT_SHAREORDERS6PART2_entry se85;
    MKT_SHAREPART1LINEITEM1_entry se86;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se87;
    MKT_SHAREPART1SUPPLIER1_entry se88;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se89;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry se90;
    MKT_SHAREPART1SUPPLIER1PART2_entry se91;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se92;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry se93;
    MKT_SHAREPART1PART2_entry se94;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se95;
    MKT_SHAREORDERS6PART2_entry se96;
    MKT_SHAREPART1_L2_1_L1_1_entry se97;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se98;
    MKT_SHAREORDERS1_L2_1_L1_5_entry se99;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry se100;
    MKT_SHAREORDERS1_L2_1_L1_5_entry se101;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry se102;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry se103;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry se104;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry se105;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry se106;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry se107;
    MKT_SHAREORDERS1_L2_1_L1_5PART2_entry se108;
    MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry se109;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se110;
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry se111;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se112;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry se113;
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry se114;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se115;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry se116;
    MKT_SHAREPART1_L2_1_L1_1PART2_entry se117;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se118;
    MKT_SHAREORDERS1_L2_1_L1_5PART2_entry se119;
    MKT_SHAREORDERS1_L2_1_L1_5_entry se120;
    MKT_SHAREORDERS1_L2_1_L1_5PART2_entry se121;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry se122;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry se123;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_entry se124;
    MKT_SHAREORDERS6_entry se125;
    MKT_SHAREORDERS6PART2_entry se126;
    MKT_SHAREPART1_entry se127;
    MKT_SHAREPART1PART2_entry se128;
    MKT_SHAREPART1CUSTOMER2_entry se129;
    MKT_SHAREPART1CUSTOMER2PART2_entry se130;
    MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry se131;
    MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry se132;
    MKT_SHAREPART1SUPPLIER1_entry se133;
    MKT_SHAREPART1SUPPLIER1PART2_entry se134;
    MKT_SHAREPART1_L2_1_L1_1_entry se135;
    MKT_SHAREPART1_L2_1_L1_1PART2_entry se136;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry se137;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry se138;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry se139;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry se140;
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry se141;
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry se142;
    MKT_SHARE_entry se143;
    MKT_SHAREPART1_L2_1_L1_1_entry se144;
    MKT_SHAREORDERS1_L2_1_L1_4_entry se145;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry se146;
    MKT_SHAREPART1_entry se147;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry se148;
    MKT_SHAREPART1CUSTOMER2_entry se149;
    MKT_SHAREPART1LINEITEM1_entry se150;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry se151;
    MKT_SHAREPART1CUSTOMER2LINEITEM3_entry se152;
    MKT_SHAREPART1SUPPLIER1_entry se153;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry se154;
    MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry se155;
    MKT_SHAREPART1SUPPLIER1PART2_entry se156;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry se157;
    MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry se158;
    MKT_SHAREPART1PART2_entry se159;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry se160;
    MKT_SHAREPART1CUSTOMER2PART2_entry se161;
    MKT_SHAREPART1_L2_1_L1_1_entry se162;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry se163;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry se164;
    MKT_SHAREPART1_L2_1_L1_1LINEITEM1_entry se165;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry se166;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_entry se167;
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry se168;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry se169;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry se170;
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry se171;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry se172;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry se173;
    MKT_SHAREPART1_L2_1_L1_1PART2_entry se174;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry se175;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry se176;
    MKT_SHARE_entry se177;
    MKT_SHAREPART1_L2_1_L1_1_entry se178;
    MKT_SHAREORDERS1_L2_1_L1_5_entry se179;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry se180;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry se181;
    MKT_SHAREORDERS1_L2_1_L1_5PART2_entry se182;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry se183;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry se184;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_entry se185;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry se186;
    MKT_SHAREORDERS6_entry se187;
    MKT_SHAREORDERS6SUPPLIER2_entry se188;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_entry se189;
    MKT_SHAREORDERS6PART2_entry se190;
    MKT_SHAREORDERS6SUPPLIER2_entry se191;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_entry se192;
    MKT_SHAREORDERS6LINEITEM2_entry se193;
    MKT_SHAREORDERS6SUPPLIER2_entry se194;
    MKT_SHAREPART1_entry se195;
    MKT_SHAREORDERS6SUPPLIER2_entry se196;
    MKT_SHAREPART1SUPPLIER1_entry se197;
    MKT_SHAREPART1CUSTOMER2_entry se198;
    MKT_SHAREORDERS6SUPPLIER2_entry se199;
    MKT_SHAREPART1CUSTOMER2SUPPLIER2_entry se200;
    MKT_SHAREPART1CUSTOMER2PART2_entry se201;
    MKT_SHAREORDERS6SUPPLIER2_entry se202;
    MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_entry se203;
    MKT_SHAREPART1PART2_entry se204;
    MKT_SHAREORDERS6SUPPLIER2_entry se205;
    MKT_SHAREPART1SUPPLIER1PART2_entry se206;
    MKT_SHAREPART1_L2_1_L1_1_entry se207;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry se208;
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_entry se209;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_entry se210;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry se211;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_entry se212;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_entry se213;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry se214;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_entry se215;
    MKT_SHAREPART1_L2_1_L1_1PART2_entry se216;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry se217;
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_entry se218;
    MKT_SHARE_entry se219;
    MKT_SHAREPART1_L2_1_L1_1_entry se220;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_entry se221;
    REGION_entry se222;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_entry se223;
    MKT_SHAREORDERS6SUPPLIER2_entry se224;
    NATION_entry se225;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REGION_map REGION;
    MKT_SHAREORDERS1_L2_1_L1_4_map MKT_SHAREORDERS1_L2_1_L1_4;
    MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1_map MKT_SHAREORDERS1_L2_1_L1_4CUSTOMER1;
    MKT_SHAREORDERS1_L2_1_L1_5_map MKT_SHAREORDERS1_L2_1_L1_5;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1_map MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2_map MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER1PART2;
    MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2_map MKT_SHAREORDERS1_L2_1_L1_5SUPPLIER2;
    MKT_SHAREORDERS1_L2_1_L1_5PART2_map MKT_SHAREORDERS1_L2_1_L1_5PART2;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1_map MKT_SHAREORDERS1_L2_1_L1_5LINEITEM1;
    MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2_map MKT_SHAREORDERS1_L2_1_L1_5LINEITEM2;
    MKT_SHAREORDERS6_map MKT_SHAREORDERS6;
    MKT_SHAREORDERS6SUPPLIER2_map MKT_SHAREORDERS6SUPPLIER2;
    MKT_SHAREORDERS6PART2_map MKT_SHAREORDERS6PART2;
    MKT_SHAREORDERS6LINEITEM2_map MKT_SHAREORDERS6LINEITEM2;
    MKT_SHAREPART1_map MKT_SHAREPART1;
    MKT_SHAREPART1CUSTOMER2_map MKT_SHAREPART1CUSTOMER2;
    MKT_SHAREPART1CUSTOMER2LINEITEM3_map MKT_SHAREPART1CUSTOMER2LINEITEM3;
    MKT_SHAREPART1CUSTOMER2SUPPLIER2_map MKT_SHAREPART1CUSTOMER2SUPPLIER2;
    MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2_map MKT_SHAREPART1CUSTOMER2SUPPLIER2PART2;
    MKT_SHAREPART1CUSTOMER2PART2_map MKT_SHAREPART1CUSTOMER2PART2;
    MKT_SHAREPART1LINEITEM1_map MKT_SHAREPART1LINEITEM1;
    MKT_SHAREPART1SUPPLIER1_map MKT_SHAREPART1SUPPLIER1;
    MKT_SHAREPART1SUPPLIER1PART2_map MKT_SHAREPART1SUPPLIER1PART2;
    MKT_SHAREPART1PART2_map MKT_SHAREPART1PART2;
    MKT_SHAREPART1_L2_1_L1_1_map MKT_SHAREPART1_L2_1_L1_1;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2_map MKT_SHAREPART1_L2_1_L1_1CUSTOMER2;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2_map MKT_SHAREPART1_L2_1_L1_1CUSTOMER2LINEITEM2;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1_map MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2_map MKT_SHAREPART1_L2_1_L1_1CUSTOMER2SUPPLIER1PART2;
    MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2_map MKT_SHAREPART1_L2_1_L1_1CUSTOMER2PART2;
    MKT_SHAREPART1_L2_1_L1_1LINEITEM1_map MKT_SHAREPART1_L2_1_L1_1LINEITEM1;
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1_map MKT_SHAREPART1_L2_1_L1_1SUPPLIER1;
    MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2_map MKT_SHAREPART1_L2_1_L1_1SUPPLIER1PART2;
    MKT_SHAREPART1_L2_1_L1_1PART2_map MKT_SHAREPART1_L2_1_L1_1PART2;
    
    /*const static*/ long c2;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c5;
  
  };

}
