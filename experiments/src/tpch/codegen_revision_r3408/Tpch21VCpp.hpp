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
  
  struct NUMWAITLINEITEM2_entry {
    long NUMWAITLINEITEMLINEITEM_SUPPKEY; STRING_TYPE S_NAME; long __av; 
    explicit NUMWAITLINEITEM2_entry() { /*NUMWAITLINEITEMLINEITEM_SUPPKEY = 0L; S_NAME = ""; __av = 0L; */ }
    explicit NUMWAITLINEITEM2_entry(const long c0, const STRING_TYPE& c1, const long c2) { NUMWAITLINEITEMLINEITEM_SUPPKEY = c0; S_NAME = c1; __av = c2; }
    NUMWAITLINEITEM2_entry(const NUMWAITLINEITEM2_entry& other) : NUMWAITLINEITEMLINEITEM_SUPPKEY( other.NUMWAITLINEITEMLINEITEM_SUPPKEY ), S_NAME( other.S_NAME ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITLINEITEM2_entry& modify(const long c0, const STRING_TYPE& c1) { NUMWAITLINEITEMLINEITEM_SUPPKEY = c0; S_NAME = c1;  return *this; }
    FORCE_INLINE NUMWAITLINEITEM2_entry& modify0(const long c0) { NUMWAITLINEITEMLINEITEM_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NUMWAITLINEITEMLINEITEM_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITLINEITEM2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAITLINEITEMLINEITEM_SUPPKEY);
      hash_combine(h, e.S_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM2_entry& x, const NUMWAITLINEITEM2_entry& y) {
      return x.NUMWAITLINEITEMLINEITEM_SUPPKEY == y.NUMWAITLINEITEMLINEITEM_SUPPKEY && x.S_NAME == y.S_NAME;
    }
  };
  
  struct NUMWAITLINEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAITLINEITEMLINEITEM_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM2_entry& x, const NUMWAITLINEITEM2_entry& y) {
      return x.NUMWAITLINEITEMLINEITEM_SUPPKEY == y.NUMWAITLINEITEMLINEITEM_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITLINEITEM2_entry,long,
    HashIndex<NUMWAITLINEITEM2_entry,long,NUMWAITLINEITEM2_mapkey01_idxfn,true>,
    HashIndex<NUMWAITLINEITEM2_entry,long,NUMWAITLINEITEM2_mapkey0_idxfn,false>
  > NUMWAITLINEITEM2_map;
  typedef HashIndex<NUMWAITLINEITEM2_entry,long,NUMWAITLINEITEM2_mapkey01_idxfn,true> HashIndex_NUMWAITLINEITEM2_map_01;
  typedef HashIndex<NUMWAITLINEITEM2_entry,long,NUMWAITLINEITEM2_mapkey0_idxfn,false> HashIndex_NUMWAITLINEITEM2_map_0;
  
  struct NUMWAITLINEITEM3_entry {
    long NUMWAITLINEITEMLINEITEM_ORDERKEY; long __av; 
    explicit NUMWAITLINEITEM3_entry() { /*NUMWAITLINEITEMLINEITEM_ORDERKEY = 0L; __av = 0L; */ }
    explicit NUMWAITLINEITEM3_entry(const long c0, const long c1) { NUMWAITLINEITEMLINEITEM_ORDERKEY = c0; __av = c1; }
    NUMWAITLINEITEM3_entry(const NUMWAITLINEITEM3_entry& other) : NUMWAITLINEITEMLINEITEM_ORDERKEY( other.NUMWAITLINEITEMLINEITEM_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITLINEITEM3_entry& modify(const long c0) { NUMWAITLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NUMWAITLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITLINEITEM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAITLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM3_entry& x, const NUMWAITLINEITEM3_entry& y) {
      return x.NUMWAITLINEITEMLINEITEM_ORDERKEY == y.NUMWAITLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITLINEITEM3_entry,long,
    HashIndex<NUMWAITLINEITEM3_entry,long,NUMWAITLINEITEM3_mapkey0_idxfn,true>
  > NUMWAITLINEITEM3_map;
  typedef HashIndex<NUMWAITLINEITEM3_entry,long,NUMWAITLINEITEM3_mapkey0_idxfn,true> HashIndex_NUMWAITLINEITEM3_map_0;
  
  struct NUMWAITLINEITEM6_entry {
    long NUMWAITLINEITEMLINEITEM_ORDERKEY; long S_SUPPKEY; STRING_TYPE S_NAME; long __av; 
    explicit NUMWAITLINEITEM6_entry() { /*NUMWAITLINEITEMLINEITEM_ORDERKEY = 0L; S_SUPPKEY = 0L; S_NAME = ""; __av = 0L; */ }
    explicit NUMWAITLINEITEM6_entry(const long c0, const long c1, const STRING_TYPE& c2, const long c3) { NUMWAITLINEITEMLINEITEM_ORDERKEY = c0; S_SUPPKEY = c1; S_NAME = c2; __av = c3; }
    NUMWAITLINEITEM6_entry(const NUMWAITLINEITEM6_entry& other) : NUMWAITLINEITEMLINEITEM_ORDERKEY( other.NUMWAITLINEITEMLINEITEM_ORDERKEY ), S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITLINEITEM6_entry& modify(const long c0, const long c1, const STRING_TYPE& c2) { NUMWAITLINEITEMLINEITEM_ORDERKEY = c0; S_SUPPKEY = c1; S_NAME = c2;  return *this; }
    FORCE_INLINE NUMWAITLINEITEM6_entry& modify0(const long c0) { NUMWAITLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NUMWAITLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITLINEITEM6_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAITLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM6_entry& x, const NUMWAITLINEITEM6_entry& y) {
      return x.NUMWAITLINEITEMLINEITEM_ORDERKEY == y.NUMWAITLINEITEMLINEITEM_ORDERKEY && x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME;
    }
  };
  
  struct NUMWAITLINEITEM6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITLINEITEM6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAITLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITLINEITEM6_entry& x, const NUMWAITLINEITEM6_entry& y) {
      return x.NUMWAITLINEITEMLINEITEM_ORDERKEY == y.NUMWAITLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITLINEITEM6_entry,long,
    HashIndex<NUMWAITLINEITEM6_entry,long,NUMWAITLINEITEM6_mapkey012_idxfn,true>,
    HashIndex<NUMWAITLINEITEM6_entry,long,NUMWAITLINEITEM6_mapkey0_idxfn,false>
  > NUMWAITLINEITEM6_map;
  typedef HashIndex<NUMWAITLINEITEM6_entry,long,NUMWAITLINEITEM6_mapkey012_idxfn,true> HashIndex_NUMWAITLINEITEM6_map_012;
  typedef HashIndex<NUMWAITLINEITEM6_entry,long,NUMWAITLINEITEM6_mapkey0_idxfn,false> HashIndex_NUMWAITLINEITEM6_map_0;
  
  struct NUMWAITSUPPLIER1_entry {
    long L1_ORDERKEY; long NUMWAITSUPPLIERSUPPLIER_SUPPKEY; long __av; 
    explicit NUMWAITSUPPLIER1_entry() { /*L1_ORDERKEY = 0L; NUMWAITSUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0L; */ }
    explicit NUMWAITSUPPLIER1_entry(const long c0, const long c1, const long c2) { L1_ORDERKEY = c0; NUMWAITSUPPLIERSUPPLIER_SUPPKEY = c1; __av = c2; }
    NUMWAITSUPPLIER1_entry(const NUMWAITSUPPLIER1_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), NUMWAITSUPPLIERSUPPLIER_SUPPKEY( other.NUMWAITSUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITSUPPLIER1_entry& modify(const long c0, const long c1) { L1_ORDERKEY = c0; NUMWAITSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    FORCE_INLINE NUMWAITSUPPLIER1_entry& modify1(const long c1) { NUMWAITSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NUMWAITSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITSUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      hash_combine(h, e.NUMWAITSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER1_entry& x, const NUMWAITSUPPLIER1_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY && x.NUMWAITSUPPLIERSUPPLIER_SUPPKEY == y.NUMWAITSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  struct NUMWAITSUPPLIER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAITSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER1_entry& x, const NUMWAITSUPPLIER1_entry& y) {
      return x.NUMWAITSUPPLIERSUPPLIER_SUPPKEY == y.NUMWAITSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITSUPPLIER1_entry,long,
    HashIndex<NUMWAITSUPPLIER1_entry,long,NUMWAITSUPPLIER1_mapkey01_idxfn,true>,
    HashIndex<NUMWAITSUPPLIER1_entry,long,NUMWAITSUPPLIER1_mapkey1_idxfn,false>
  > NUMWAITSUPPLIER1_map;
  typedef HashIndex<NUMWAITSUPPLIER1_entry,long,NUMWAITSUPPLIER1_mapkey01_idxfn,true> HashIndex_NUMWAITSUPPLIER1_map_01;
  typedef HashIndex<NUMWAITSUPPLIER1_entry,long,NUMWAITSUPPLIER1_mapkey1_idxfn,false> HashIndex_NUMWAITSUPPLIER1_map_1;
  
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
  
  struct NUMWAITSUPPLIER2_entry {
    long NUMWAITSUPPLIERSUPPLIER_NATIONKEY; long __av; 
    explicit NUMWAITSUPPLIER2_entry() { /*NUMWAITSUPPLIERSUPPLIER_NATIONKEY = 0L; __av = 0L; */ }
    explicit NUMWAITSUPPLIER2_entry(const long c0, const long c1) { NUMWAITSUPPLIERSUPPLIER_NATIONKEY = c0; __av = c1; }
    NUMWAITSUPPLIER2_entry(const NUMWAITSUPPLIER2_entry& other) : NUMWAITSUPPLIERSUPPLIER_NATIONKEY( other.NUMWAITSUPPLIERSUPPLIER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAITSUPPLIER2_entry& modify(const long c0) { NUMWAITSUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NUMWAITSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAITSUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAITSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAITSUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAITSUPPLIER2_entry& x, const NUMWAITSUPPLIER2_entry& y) {
      return x.NUMWAITSUPPLIERSUPPLIER_NATIONKEY == y.NUMWAITSUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAITSUPPLIER2_entry,long,
    HashIndex<NUMWAITSUPPLIER2_entry,long,NUMWAITSUPPLIER2_mapkey0_idxfn,true>
  > NUMWAITSUPPLIER2_map;
  typedef HashIndex<NUMWAITSUPPLIER2_entry,long,NUMWAITSUPPLIER2_mapkey0_idxfn,true> HashIndex_NUMWAITSUPPLIER2_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
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
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg1 = 0L;
        long agg2 = 0L;
        { //slice 
          const HashIndex_NUMWAITSUPPLIER1_L2_1_map_0* i1 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0*>(NUMWAITSUPPLIER1_L2_1.index[1]);
          const HASH_RES_t h1 = NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::hash(se3.modify0(lineitem_orderkey));
          HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode* n1 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode*>(i1->slice(se3, h1));
          NUMWAITSUPPLIER1_L2_1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long l3_suppkey = e1->L3_SUPPKEY;
              long v1 = e1->__av;
              (/*if */(l3_suppkey != lineitem_suppkey) ? agg2 += v1 : 0L);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::equals(se3, *e1)); 
          }
        }long l1 = agg2;
        (/*if */(l1 == 0L) ? agg1 += 1L : 0L);
        { //slice 
          const HashIndex_NUMWAITLINEITEM2_map_0* i2 = static_cast<HashIndex_NUMWAITLINEITEM2_map_0*>(NUMWAITLINEITEM2.index[1]);
          const HASH_RES_t h3 = NUMWAITLINEITEM2_mapkey0_idxfn::hash(se5.modify0(lineitem_suppkey));
          HashIndex_NUMWAITLINEITEM2_map_0::IdxNode* n2 = static_cast<HashIndex_NUMWAITLINEITEM2_map_0::IdxNode*>(i2->slice(se5, h3));
          NUMWAITLINEITEM2_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              STRING_TYPE s_name = e2->S_NAME;
              long v2 = e2->__av;
              long agg3 = 0L;
              { //slice 
                const HashIndex_NUMWAITSUPPLIER1_E3_1_map_0* i3 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0*>(NUMWAITSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h2 = NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::hash(se4.modify0(lineitem_orderkey));
                HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode* n3 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode*>(i3->slice(se4, h2));
                NUMWAITSUPPLIER1_E3_1_entry* e3;
               
                if (n3 && (e3 = n3->obj)) {
                  do {                
                    long l2_suppkey = e3->L2_SUPPKEY;
                    long v3 = e3->__av;
                    (/*if */(l2_suppkey != lineitem_suppkey) ? agg3 += v3 : 0L);
                    n3 = n3->nxt;
                  } while (n3 && (e3 = n3->obj) && h2 == n3->hash &&  NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::equals(se4, *e3)); 
                }
              }(/*if */(lineitem_receiptdate > lineitem_commitdate) ? NUMWAIT.addOrDelOnZero(se1.modify(s_name),(NUMWAITLINEITEM3.getValueOrDefault(se2.modify(lineitem_orderkey)) * (agg1 * (v2 * (agg3 != 0 ? 1L : 0L))))) : (void)0);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h3 == n2->hash &&  NUMWAITLINEITEM2_mapkey0_idxfn::equals(se5, *e2)); 
          }
        }long l2 = 0L;
        { //slice 
          const HashIndex_NUMWAITLINEITEM6_map_0* i4 = static_cast<HashIndex_NUMWAITLINEITEM6_map_0*>(NUMWAITLINEITEM6.index[1]);
          const HASH_RES_t h6 = NUMWAITLINEITEM6_mapkey0_idxfn::hash(se8.modify0(lineitem_orderkey));
          HashIndex_NUMWAITLINEITEM6_map_0::IdxNode* n4 = static_cast<HashIndex_NUMWAITLINEITEM6_map_0::IdxNode*>(i4->slice(se8, h6));
          NUMWAITLINEITEM6_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long s_suppkey = e4->S_SUPPKEY;
              STRING_TYPE s_name = e4->S_NAME;
              long v4 = e4->__av;
              long agg4 = 0L;
              { //slice 
                const HashIndex_NUMWAITSUPPLIER1_L2_1_map_0* i5 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0*>(NUMWAITSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h4 = NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::hash(se6.modify0(lineitem_orderkey));
                HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode* n5 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode*>(i5->slice(se6, h4));
                NUMWAITSUPPLIER1_L2_1_entry* e5;
               
                if (n5 && (e5 = n5->obj)) {
                  do {                
                    long l3_suppkey = e5->L3_SUPPKEY;
                    long v5 = e5->__av;
                    (/*if */(l3_suppkey != s_suppkey) ? agg4 += v5 : 0L);
                    n5 = n5->nxt;
                  } while (n5 && (e5 = n5->obj) && h4 == n5->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::equals(se6, *e5)); 
                }
              }long agg5 = 0L;
              { //slice 
                const HashIndex_NUMWAITSUPPLIER1_E3_1_map_0* i6 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0*>(NUMWAITSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h5 = NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::hash(se7.modify0(lineitem_orderkey));
                HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode* n6 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode*>(i6->slice(se7, h5));
                NUMWAITSUPPLIER1_E3_1_entry* e6;
               
                if (n6 && (e6 = n6->obj)) {
                  do {                
                    long l2_suppkey = e6->L2_SUPPKEY;
                    long v6 = e6->__av;
                    (/*if */(l2_suppkey != s_suppkey) ? agg5 += v6 : 0L);
                    n6 = n6->nxt;
                  } while (n6 && (e6 = n6->obj) && h5 == n6->hash &&  NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::equals(se7, *e6)); 
                }
              }(/*if */(l2 == agg4) ? NUMWAIT.addOrDelOnZero(se1.modify(s_name),(NUMWAITLINEITEM3.getValueOrDefault(se2.modify(lineitem_orderkey)) * ((v4 * (agg5 != 0 ? 1L : 0L)) * -1L))) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h6 == n4->hash &&  NUMWAITLINEITEM6_mapkey0_idxfn::equals(se8, *e4)); 
          }
        }long l3 = 0L;
        { //slice 
          const HashIndex_NUMWAITLINEITEM6_map_0* i7 = static_cast<HashIndex_NUMWAITLINEITEM6_map_0*>(NUMWAITLINEITEM6.index[1]);
          const HASH_RES_t h9 = NUMWAITLINEITEM6_mapkey0_idxfn::hash(se11.modify0(lineitem_orderkey));
          HashIndex_NUMWAITLINEITEM6_map_0::IdxNode* n7 = static_cast<HashIndex_NUMWAITLINEITEM6_map_0::IdxNode*>(i7->slice(se11, h9));
          NUMWAITLINEITEM6_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              long s_suppkey = e7->S_SUPPKEY;
              STRING_TYPE s_name = e7->S_NAME;
              long v7 = e7->__av;
              long agg6 = 0L;
              { //slice 
                const HashIndex_NUMWAITSUPPLIER1_L2_1_map_0* i8 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0*>(NUMWAITSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h7 = NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::hash(se9.modify0(lineitem_orderkey));
                HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode* n8 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode*>(i8->slice(se9, h7));
                NUMWAITSUPPLIER1_L2_1_entry* e8;
               
                if (n8 && (e8 = n8->obj)) {
                  do {                
                    long l3_suppkey = e8->L3_SUPPKEY;
                    long v8 = e8->__av;
                    (/*if */(l3_suppkey != s_suppkey) ? agg6 += v8 : 0L);
                    n8 = n8->nxt;
                  } while (n8 && (e8 = n8->obj) && h7 == n8->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::equals(se9, *e8)); 
                }
              }long agg7 = 0L;
              { //slice 
                const HashIndex_NUMWAITSUPPLIER1_E3_1_map_0* i9 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0*>(NUMWAITSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h8 = NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::hash(se10.modify0(lineitem_orderkey));
                HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode* n9 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode*>(i9->slice(se10, h8));
                NUMWAITSUPPLIER1_E3_1_entry* e9;
               
                if (n9 && (e9 = n9->obj)) {
                  do {                
                    long l2_suppkey = e9->L2_SUPPKEY;
                    long v9 = e9->__av;
                    (/*if */(l2_suppkey != s_suppkey) ? agg7 += v9 : 0L);
                    n9 = n9->nxt;
                  } while (n9 && (e9 = n9->obj) && h8 == n9->hash &&  NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::equals(se10, *e9)); 
                }
              }(/*if */(l3 == (agg6 + (/*if */(lineitem_suppkey != s_suppkey && lineitem_receiptdate > lineitem_commitdate) ? 1L : 0L))) ? NUMWAIT.addOrDelOnZero(se1.modify(s_name),(NUMWAITLINEITEM3.getValueOrDefault(se2.modify(lineitem_orderkey)) * (v7 * ((agg7 + (/*if */(lineitem_suppkey != s_suppkey) ? 1L : 0L)) != 0 ? 1L : 0L)))) : (void)0);
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h9 == n7->hash &&  NUMWAITLINEITEM6_mapkey0_idxfn::equals(se11, *e7)); 
          }
        }{ //slice 
          const HashIndex_NUMWAITLINEITEM2_map_0* i10 = static_cast<HashIndex_NUMWAITLINEITEM2_map_0*>(NUMWAITLINEITEM2.index[1]);
          const HASH_RES_t h10 = NUMWAITLINEITEM2_mapkey0_idxfn::hash(se13.modify0(lineitem_suppkey));
          HashIndex_NUMWAITLINEITEM2_map_0::IdxNode* n10 = static_cast<HashIndex_NUMWAITLINEITEM2_map_0::IdxNode*>(i10->slice(se13, h10));
          NUMWAITLINEITEM2_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              STRING_TYPE s_name = e10->S_NAME;
              long v10 = e10->__av;
              (/*if */(lineitem_receiptdate > lineitem_commitdate) ? NUMWAITLINEITEM6.addOrDelOnZero(se12.modify(lineitem_orderkey,lineitem_suppkey,s_name),v10) : (void)0);
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h10 == n10->hash &&  NUMWAITLINEITEM2_mapkey0_idxfn::equals(se13, *e10)); 
          }
        }(/*if */(lineitem_receiptdate > lineitem_commitdate) ? NUMWAITSUPPLIER1.addOrDelOnZero(se14.modify(lineitem_orderkey,lineitem_suppkey),NUMWAITLINEITEM3.getValueOrDefault(se15.modify(lineitem_orderkey))) : (void)0);
        (/*if */(lineitem_receiptdate > lineitem_commitdate) ? NUMWAITSUPPLIER1_L2_1.addOrDelOnZero(se16.modify(lineitem_orderkey,lineitem_suppkey),1L) : (void)0);
        NUMWAITSUPPLIER1_E3_1.addOrDelOnZero(se17.modify(lineitem_orderkey,lineitem_suppkey),1L);
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long l4 = 0L;
        { //slice 
          const HashIndex_NUMWAITLINEITEM6_map_0* i11 = static_cast<HashIndex_NUMWAITLINEITEM6_map_0*>(NUMWAITLINEITEM6.index[1]);
          const HASH_RES_t h13 = NUMWAITLINEITEM6_mapkey0_idxfn::hash(se21.modify0(orders_orderkey));
          HashIndex_NUMWAITLINEITEM6_map_0::IdxNode* n11 = static_cast<HashIndex_NUMWAITLINEITEM6_map_0::IdxNode*>(i11->slice(se21, h13));
          NUMWAITLINEITEM6_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              long s_suppkey = e11->S_SUPPKEY;
              STRING_TYPE s_name = e11->S_NAME;
              long v11 = e11->__av;
              long agg8 = 0L;
              { //slice 
                const HashIndex_NUMWAITSUPPLIER1_L2_1_map_0* i12 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0*>(NUMWAITSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h11 = NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::hash(se19.modify0(orders_orderkey));
                HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode* n12 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode*>(i12->slice(se19, h11));
                NUMWAITSUPPLIER1_L2_1_entry* e12;
               
                if (n12 && (e12 = n12->obj)) {
                  do {                
                    long l3_suppkey = e12->L3_SUPPKEY;
                    long v12 = e12->__av;
                    (/*if */(l3_suppkey != s_suppkey) ? agg8 += v12 : 0L);
                    n12 = n12->nxt;
                  } while (n12 && (e12 = n12->obj) && h11 == n12->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::equals(se19, *e12)); 
                }
              }long agg9 = 0L;
              { //slice 
                const HashIndex_NUMWAITSUPPLIER1_E3_1_map_0* i13 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0*>(NUMWAITSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h12 = NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::hash(se20.modify0(orders_orderkey));
                HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode* n13 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode*>(i13->slice(se20, h12));
                NUMWAITSUPPLIER1_E3_1_entry* e13;
               
                if (n13 && (e13 = n13->obj)) {
                  do {                
                    long l2_suppkey = e13->L2_SUPPKEY;
                    long v13 = e13->__av;
                    (/*if */(l2_suppkey != s_suppkey) ? agg9 += v13 : 0L);
                    n13 = n13->nxt;
                  } while (n13 && (e13 = n13->obj) && h12 == n13->hash &&  NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::equals(se20, *e13)); 
                }
              }(/*if */(orders_orderstatus == c1 && l4 == agg8) ? NUMWAIT.addOrDelOnZero(se18.modify(s_name),(v11 * (agg9 != 0 ? 1L : 0L))) : (void)0);
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h13 == n11->hash &&  NUMWAITLINEITEM6_mapkey0_idxfn::equals(se21, *e11)); 
          }
        }(/*if */(orders_orderstatus == c1) ? NUMWAITLINEITEM3.addOrDelOnZero(se22.modify(orders_orderkey),1L) : (void)0);
        { //slice 
          const HashIndex_NUMWAITSUPPLIER1_L2_1_map_0* i14 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0*>(NUMWAITSUPPLIER1_L2_1.index[1]);
          const HASH_RES_t h14 = NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::hash(se24.modify0(orders_orderkey));
          HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode* n14 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode*>(i14->slice(se24, h14));
          NUMWAITSUPPLIER1_L2_1_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              long numwaitsuppliersupplier_suppkey = e14->L3_SUPPKEY;
              long v14 = e14->__av;
              (/*if */(orders_orderstatus == c1) ? NUMWAITSUPPLIER1.addOrDelOnZero(se23.modify(orders_orderkey,numwaitsuppliersupplier_suppkey),v14) : (void)0);
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h14 == n14->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::equals(se24, *e14)); 
          }
        }
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg10 = 0L;
        long l5 = 0L;
        { //slice 
          const HashIndex_NUMWAITSUPPLIER1_map_1* i15 = static_cast<HashIndex_NUMWAITSUPPLIER1_map_1*>(NUMWAITSUPPLIER1.index[1]);
          const HASH_RES_t h17 = NUMWAITSUPPLIER1_mapkey1_idxfn::hash(se29.modify1(supplier_suppkey));
          HashIndex_NUMWAITSUPPLIER1_map_1::IdxNode* n15 = static_cast<HashIndex_NUMWAITSUPPLIER1_map_1::IdxNode*>(i15->slice(se29, h17));
          NUMWAITSUPPLIER1_entry* e15;
         
          if (n15 && (e15 = n15->obj)) {
            do {                
              long l1_orderkey = e15->L1_ORDERKEY;
              long v15 = e15->__av;
              long agg11 = 0L;
              { //slice 
                const HashIndex_NUMWAITSUPPLIER1_L2_1_map_0* i16 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0*>(NUMWAITSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h15 = NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::hash(se27.modify0(l1_orderkey));
                HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode* n16 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_0::IdxNode*>(i16->slice(se27, h15));
                NUMWAITSUPPLIER1_L2_1_entry* e16;
               
                if (n16 && (e16 = n16->obj)) {
                  do {                
                    long l3_suppkey = e16->L3_SUPPKEY;
                    long v16 = e16->__av;
                    (/*if */(l3_suppkey != supplier_suppkey) ? agg11 += v16 : 0L);
                    n16 = n16->nxt;
                  } while (n16 && (e16 = n16->obj) && h15 == n16->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey0_idxfn::equals(se27, *e16)); 
                }
              }long agg12 = 0L;
              { //slice 
                const HashIndex_NUMWAITSUPPLIER1_E3_1_map_0* i17 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0*>(NUMWAITSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h16 = NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::hash(se28.modify0(l1_orderkey));
                HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode* n17 = static_cast<HashIndex_NUMWAITSUPPLIER1_E3_1_map_0::IdxNode*>(i17->slice(se28, h16));
                NUMWAITSUPPLIER1_E3_1_entry* e17;
               
                if (n17 && (e17 = n17->obj)) {
                  do {                
                    long l2_suppkey = e17->L2_SUPPKEY;
                    long v17 = e17->__av;
                    (/*if */(l2_suppkey != supplier_suppkey) ? agg12 += v17 : 0L);
                    n17 = n17->nxt;
                  } while (n17 && (e17 = n17->obj) && h16 == n17->hash &&  NUMWAITSUPPLIER1_E3_1_mapkey0_idxfn::equals(se28, *e17)); 
                }
              }(/*if */(l5 == agg11) ? agg10 += (v15 * (agg12 != 0 ? 1L : 0L)) : 0L);
              n15 = n15->nxt;
            } while (n15 && (e15 = n15->obj) && h17 == n15->hash &&  NUMWAITSUPPLIER1_mapkey1_idxfn::equals(se29, *e15)); 
          }
        }NUMWAIT.addOrDelOnZero(se25.modify(supplier_name),(NUMWAITSUPPLIER2.getValueOrDefault(se26.modify(supplier_nationkey)) * agg10));
        NUMWAITLINEITEM2.addOrDelOnZero(se30.modify(supplier_suppkey,supplier_name),NUMWAITSUPPLIER2.getValueOrDefault(se31.modify(supplier_nationkey)));
        { //slice 
          const HashIndex_NUMWAITSUPPLIER1_L2_1_map_1* i18 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_1*>(NUMWAITSUPPLIER1_L2_1.index[2]);
          const HASH_RES_t h18 = NUMWAITSUPPLIER1_L2_1_mapkey1_idxfn::hash(se34.modify1(supplier_suppkey));
          HashIndex_NUMWAITSUPPLIER1_L2_1_map_1::IdxNode* n18 = static_cast<HashIndex_NUMWAITSUPPLIER1_L2_1_map_1::IdxNode*>(i18->slice(se34, h18));
          NUMWAITSUPPLIER1_L2_1_entry* e18;
         
          if (n18 && (e18 = n18->obj)) {
            do {                
              long numwaitlineitemlineitem_orderkey = e18->L1_ORDERKEY;
              long v18 = e18->__av;
              NUMWAITLINEITEM6.addOrDelOnZero(se32.modify(numwaitlineitemlineitem_orderkey,supplier_suppkey,supplier_name),(NUMWAITSUPPLIER2.getValueOrDefault(se33.modify(supplier_nationkey)) * v18));
              n18 = n18->nxt;
            } while (n18 && (e18 = n18->obj) && h18 == n18->hash &&  NUMWAITSUPPLIER1_L2_1_mapkey1_idxfn::equals(se34, *e18)); 
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        NUMWAITSUPPLIER2.clear();
        STRING_TYPE l6 = c2;
        { //slice 
          const HashIndex_NATION_map_1* i19 = static_cast<HashIndex_NATION_map_1*>(NATION.index[1]);
          const HASH_RES_t h19 = NATION_mapkey1_idxfn::hash(se36.modify1(l6));
          HashIndex_NATION_map_1::IdxNode* n19 = static_cast<HashIndex_NATION_map_1::IdxNode*>(i19->slice(se36, h19));
          NATION_entry* e19;
         
          if (n19 && (e19 = n19->obj)) {
            do {                
              long numwaitsuppliersupplier_nationkey = e19->NATION_NATIONKEY;
              long n_regionkey = e19->NATION_REGIONKEY;
              STRING_TYPE n_comment = e19->NATION_COMMENT;
              long v19 = e19->__av;
              NUMWAITSUPPLIER2.addOrDelOnZero(se35.modify(numwaitsuppliersupplier_nationkey),v19);
              n19 = n19->nxt;
            } while (n19 && (e19 = n19->obj) && h19 == n19->hash &&  NATION_mapkey1_idxfn::equals(se36, *e19)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    NUMWAIT_entry se1;
    NUMWAITLINEITEM3_entry se2;
    NUMWAITSUPPLIER1_L2_1_entry se3;
    NUMWAITSUPPLIER1_E3_1_entry se4;
    NUMWAITLINEITEM2_entry se5;
    NUMWAITSUPPLIER1_L2_1_entry se6;
    NUMWAITSUPPLIER1_E3_1_entry se7;
    NUMWAITLINEITEM6_entry se8;
    NUMWAITSUPPLIER1_L2_1_entry se9;
    NUMWAITSUPPLIER1_E3_1_entry se10;
    NUMWAITLINEITEM6_entry se11;
    NUMWAITLINEITEM6_entry se12;
    NUMWAITLINEITEM2_entry se13;
    NUMWAITSUPPLIER1_entry se14;
    NUMWAITLINEITEM3_entry se15;
    NUMWAITSUPPLIER1_L2_1_entry se16;
    NUMWAITSUPPLIER1_E3_1_entry se17;
    NUMWAIT_entry se18;
    NUMWAITSUPPLIER1_L2_1_entry se19;
    NUMWAITSUPPLIER1_E3_1_entry se20;
    NUMWAITLINEITEM6_entry se21;
    NUMWAITLINEITEM3_entry se22;
    NUMWAITSUPPLIER1_entry se23;
    NUMWAITSUPPLIER1_L2_1_entry se24;
    NUMWAIT_entry se25;
    NUMWAITSUPPLIER2_entry se26;
    NUMWAITSUPPLIER1_L2_1_entry se27;
    NUMWAITSUPPLIER1_E3_1_entry se28;
    NUMWAITSUPPLIER1_entry se29;
    NUMWAITLINEITEM2_entry se30;
    NUMWAITSUPPLIER2_entry se31;
    NUMWAITLINEITEM6_entry se32;
    NUMWAITSUPPLIER2_entry se33;
    NUMWAITSUPPLIER1_L2_1_entry se34;
    NUMWAITSUPPLIER2_entry se35;
    NATION_entry se36;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    NUMWAITLINEITEM2_map NUMWAITLINEITEM2;
    NUMWAITLINEITEM3_map NUMWAITLINEITEM3;
    NUMWAITLINEITEM6_map NUMWAITLINEITEM6;
    NUMWAITSUPPLIER1_map NUMWAITSUPPLIER1;
    NUMWAITSUPPLIER1_L2_1_map NUMWAITSUPPLIER1_L2_1;
    NUMWAITSUPPLIER1_E3_1_map NUMWAITSUPPLIER1_E3_1;
    NUMWAITSUPPLIER2_map NUMWAITSUPPLIER2;
    
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c2;
  
  };

}
