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
  
  struct NUMWAIT_mLINEITEM1_entry {
    long NUMWAIT_mLINEITEMLINEITEM_ORDERKEY; long __av; 
    explicit NUMWAIT_mLINEITEM1_entry() { /*NUMWAIT_mLINEITEMLINEITEM_ORDERKEY = 0L; __av = 0L; */ }
    explicit NUMWAIT_mLINEITEM1_entry(const long c0, const long c1) { NUMWAIT_mLINEITEMLINEITEM_ORDERKEY = c0; __av = c1; }
    NUMWAIT_mLINEITEM1_entry(const NUMWAIT_mLINEITEM1_entry& other) : NUMWAIT_mLINEITEMLINEITEM_ORDERKEY( other.NUMWAIT_mLINEITEMLINEITEM_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAIT_mLINEITEM1_entry& modify(const long c0) { NUMWAIT_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NUMWAIT_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAIT_mLINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAIT_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mLINEITEM1_entry& x, const NUMWAIT_mLINEITEM1_entry& y) {
      return x.NUMWAIT_mLINEITEMLINEITEM_ORDERKEY == y.NUMWAIT_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAIT_mLINEITEM1_entry,long,
    HashIndex<NUMWAIT_mLINEITEM1_entry,long,NUMWAIT_mLINEITEM1_mapkey0_idxfn,true>
  > NUMWAIT_mLINEITEM1_map;
  typedef HashIndex<NUMWAIT_mLINEITEM1_entry,long,NUMWAIT_mLINEITEM1_mapkey0_idxfn,true> HashIndex_NUMWAIT_mLINEITEM1_map_0;
  
  struct NUMWAIT_mLINEITEM2_entry {
    long NUMWAIT_mLINEITEMLINEITEM_SUPPKEY; STRING_TYPE S_NAME; long __av; 
    explicit NUMWAIT_mLINEITEM2_entry() { /*NUMWAIT_mLINEITEMLINEITEM_SUPPKEY = 0L; S_NAME = ""; __av = 0L; */ }
    explicit NUMWAIT_mLINEITEM2_entry(const long c0, const STRING_TYPE& c1, const long c2) { NUMWAIT_mLINEITEMLINEITEM_SUPPKEY = c0; S_NAME = c1; __av = c2; }
    NUMWAIT_mLINEITEM2_entry(const NUMWAIT_mLINEITEM2_entry& other) : NUMWAIT_mLINEITEMLINEITEM_SUPPKEY( other.NUMWAIT_mLINEITEMLINEITEM_SUPPKEY ), S_NAME( other.S_NAME ), __av( other.__av ) {}
    FORCE_INLINE NUMWAIT_mLINEITEM2_entry& modify(const long c0, const STRING_TYPE& c1) { NUMWAIT_mLINEITEMLINEITEM_SUPPKEY = c0; S_NAME = c1;  return *this; }
    FORCE_INLINE NUMWAIT_mLINEITEM2_entry& modify0(const long c0) { NUMWAIT_mLINEITEMLINEITEM_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NUMWAIT_mLINEITEMLINEITEM_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAIT_mLINEITEM2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAIT_mLINEITEMLINEITEM_SUPPKEY);
      hash_combine(h, e.S_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mLINEITEM2_entry& x, const NUMWAIT_mLINEITEM2_entry& y) {
      return x.NUMWAIT_mLINEITEMLINEITEM_SUPPKEY == y.NUMWAIT_mLINEITEMLINEITEM_SUPPKEY && x.S_NAME == y.S_NAME;
    }
  };
  
  struct NUMWAIT_mLINEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAIT_mLINEITEMLINEITEM_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mLINEITEM2_entry& x, const NUMWAIT_mLINEITEM2_entry& y) {
      return x.NUMWAIT_mLINEITEMLINEITEM_SUPPKEY == y.NUMWAIT_mLINEITEMLINEITEM_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAIT_mLINEITEM2_entry,long,
    HashIndex<NUMWAIT_mLINEITEM2_entry,long,NUMWAIT_mLINEITEM2_mapkey01_idxfn,true>,
    HashIndex<NUMWAIT_mLINEITEM2_entry,long,NUMWAIT_mLINEITEM2_mapkey0_idxfn,false>
  > NUMWAIT_mLINEITEM2_map;
  typedef HashIndex<NUMWAIT_mLINEITEM2_entry,long,NUMWAIT_mLINEITEM2_mapkey01_idxfn,true> HashIndex_NUMWAIT_mLINEITEM2_map_01;
  typedef HashIndex<NUMWAIT_mLINEITEM2_entry,long,NUMWAIT_mLINEITEM2_mapkey0_idxfn,false> HashIndex_NUMWAIT_mLINEITEM2_map_0;
  
  struct NUMWAIT_mLINEITEM7_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; long NUMWAIT_mLINEITEMLINEITEM_ORDERKEY; long __av; 
    explicit NUMWAIT_mLINEITEM7_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; NUMWAIT_mLINEITEMLINEITEM_ORDERKEY = 0L; __av = 0L; */ }
    explicit NUMWAIT_mLINEITEM7_entry(const long c0, const STRING_TYPE& c1, const long c2, const long c3) { S_SUPPKEY = c0; S_NAME = c1; NUMWAIT_mLINEITEMLINEITEM_ORDERKEY = c2; __av = c3; }
    NUMWAIT_mLINEITEM7_entry(const NUMWAIT_mLINEITEM7_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), NUMWAIT_mLINEITEMLINEITEM_ORDERKEY( other.NUMWAIT_mLINEITEMLINEITEM_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAIT_mLINEITEM7_entry& modify(const long c0, const STRING_TYPE& c1, const long c2) { S_SUPPKEY = c0; S_NAME = c1; NUMWAIT_mLINEITEMLINEITEM_ORDERKEY = c2;  return *this; }
    FORCE_INLINE NUMWAIT_mLINEITEM7_entry& modify2(const long c2) { NUMWAIT_mLINEITEMLINEITEM_ORDERKEY = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NUMWAIT_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAIT_mLINEITEM7_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mLINEITEM7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.NUMWAIT_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mLINEITEM7_entry& x, const NUMWAIT_mLINEITEM7_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.NUMWAIT_mLINEITEMLINEITEM_ORDERKEY == y.NUMWAIT_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct NUMWAIT_mLINEITEM7_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mLINEITEM7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAIT_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mLINEITEM7_entry& x, const NUMWAIT_mLINEITEM7_entry& y) {
      return x.NUMWAIT_mLINEITEMLINEITEM_ORDERKEY == y.NUMWAIT_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAIT_mLINEITEM7_entry,long,
    HashIndex<NUMWAIT_mLINEITEM7_entry,long,NUMWAIT_mLINEITEM7_mapkey012_idxfn,true>,
    HashIndex<NUMWAIT_mLINEITEM7_entry,long,NUMWAIT_mLINEITEM7_mapkey2_idxfn,false>
  > NUMWAIT_mLINEITEM7_map;
  typedef HashIndex<NUMWAIT_mLINEITEM7_entry,long,NUMWAIT_mLINEITEM7_mapkey012_idxfn,true> HashIndex_NUMWAIT_mLINEITEM7_map_012;
  typedef HashIndex<NUMWAIT_mLINEITEM7_entry,long,NUMWAIT_mLINEITEM7_mapkey2_idxfn,false> HashIndex_NUMWAIT_mLINEITEM7_map_2;
  
  struct NUMWAIT_mSUPPLIER1_entry {
    long L1_ORDERKEY; long NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY; long __av; 
    explicit NUMWAIT_mSUPPLIER1_entry() { /*L1_ORDERKEY = 0L; NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0L; */ }
    explicit NUMWAIT_mSUPPLIER1_entry(const long c0, const long c1, const long c2) { L1_ORDERKEY = c0; NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY = c1; __av = c2; }
    NUMWAIT_mSUPPLIER1_entry(const NUMWAIT_mSUPPLIER1_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY( other.NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAIT_mSUPPLIER1_entry& modify(const long c0, const long c1) { L1_ORDERKEY = c0; NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    FORCE_INLINE NUMWAIT_mSUPPLIER1_entry& modify1(const long c1) { NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L1_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAIT_mSUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      hash_combine(h, e.NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mSUPPLIER1_entry& x, const NUMWAIT_mSUPPLIER1_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY && x.NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY == y.NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  struct NUMWAIT_mSUPPLIER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mSUPPLIER1_entry& x, const NUMWAIT_mSUPPLIER1_entry& y) {
      return x.NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY == y.NUMWAIT_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAIT_mSUPPLIER1_entry,long,
    HashIndex<NUMWAIT_mSUPPLIER1_entry,long,NUMWAIT_mSUPPLIER1_mapkey01_idxfn,true>,
    HashIndex<NUMWAIT_mSUPPLIER1_entry,long,NUMWAIT_mSUPPLIER1_mapkey1_idxfn,false>
  > NUMWAIT_mSUPPLIER1_map;
  typedef HashIndex<NUMWAIT_mSUPPLIER1_entry,long,NUMWAIT_mSUPPLIER1_mapkey01_idxfn,true> HashIndex_NUMWAIT_mSUPPLIER1_map_01;
  typedef HashIndex<NUMWAIT_mSUPPLIER1_entry,long,NUMWAIT_mSUPPLIER1_mapkey1_idxfn,false> HashIndex_NUMWAIT_mSUPPLIER1_map_1;
  
  struct NUMWAIT_mSUPPLIER1_L2_1_entry {
    long L1_ORDERKEY; long L3_SUPPKEY; long __av; 
    explicit NUMWAIT_mSUPPLIER1_L2_1_entry() { /*L1_ORDERKEY = 0L; L3_SUPPKEY = 0L; __av = 0L; */ }
    explicit NUMWAIT_mSUPPLIER1_L2_1_entry(const long c0, const long c1, const long c2) { L1_ORDERKEY = c0; L3_SUPPKEY = c1; __av = c2; }
    NUMWAIT_mSUPPLIER1_L2_1_entry(const NUMWAIT_mSUPPLIER1_L2_1_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), L3_SUPPKEY( other.L3_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAIT_mSUPPLIER1_L2_1_entry& modify(const long c0, const long c1) { L1_ORDERKEY = c0; L3_SUPPKEY = c1;  return *this; }
    FORCE_INLINE NUMWAIT_mSUPPLIER1_L2_1_entry& modify0(const long c0) { L1_ORDERKEY = c0;  return *this; }
    FORCE_INLINE NUMWAIT_mSUPPLIER1_L2_1_entry& modify1(const long c1) { L3_SUPPKEY = c1;  return *this; }
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
  struct NUMWAIT_mSUPPLIER1_L2_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mSUPPLIER1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      hash_combine(h, e.L3_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mSUPPLIER1_L2_1_entry& x, const NUMWAIT_mSUPPLIER1_L2_1_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY && x.L3_SUPPKEY == y.L3_SUPPKEY;
    }
  };
  
  struct NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mSUPPLIER1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mSUPPLIER1_L2_1_entry& x, const NUMWAIT_mSUPPLIER1_L2_1_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY;
    }
  };
  
  struct NUMWAIT_mSUPPLIER1_L2_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mSUPPLIER1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L3_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mSUPPLIER1_L2_1_entry& x, const NUMWAIT_mSUPPLIER1_L2_1_entry& y) {
      return x.L3_SUPPKEY == y.L3_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAIT_mSUPPLIER1_L2_1_entry,long,
    HashIndex<NUMWAIT_mSUPPLIER1_L2_1_entry,long,NUMWAIT_mSUPPLIER1_L2_1_mapkey01_idxfn,true>,
    HashIndex<NUMWAIT_mSUPPLIER1_L2_1_entry,long,NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn,false>,
    HashIndex<NUMWAIT_mSUPPLIER1_L2_1_entry,long,NUMWAIT_mSUPPLIER1_L2_1_mapkey1_idxfn,false>
  > NUMWAIT_mSUPPLIER1_L2_1_map;
  typedef HashIndex<NUMWAIT_mSUPPLIER1_L2_1_entry,long,NUMWAIT_mSUPPLIER1_L2_1_mapkey01_idxfn,true> HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_01;
  typedef HashIndex<NUMWAIT_mSUPPLIER1_L2_1_entry,long,NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn,false> HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0;
  typedef HashIndex<NUMWAIT_mSUPPLIER1_L2_1_entry,long,NUMWAIT_mSUPPLIER1_L2_1_mapkey1_idxfn,false> HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_1;
  
  struct NUMWAIT_mSUPPLIER1_E3_1_entry {
    long L1_ORDERKEY; long L2_SUPPKEY; long __av; 
    explicit NUMWAIT_mSUPPLIER1_E3_1_entry() { /*L1_ORDERKEY = 0L; L2_SUPPKEY = 0L; __av = 0L; */ }
    explicit NUMWAIT_mSUPPLIER1_E3_1_entry(const long c0, const long c1, const long c2) { L1_ORDERKEY = c0; L2_SUPPKEY = c1; __av = c2; }
    NUMWAIT_mSUPPLIER1_E3_1_entry(const NUMWAIT_mSUPPLIER1_E3_1_entry& other) : L1_ORDERKEY( other.L1_ORDERKEY ), L2_SUPPKEY( other.L2_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAIT_mSUPPLIER1_E3_1_entry& modify(const long c0, const long c1) { L1_ORDERKEY = c0; L2_SUPPKEY = c1;  return *this; }
    FORCE_INLINE NUMWAIT_mSUPPLIER1_E3_1_entry& modify0(const long c0) { L1_ORDERKEY = c0;  return *this; }
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
  struct NUMWAIT_mSUPPLIER1_E3_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mSUPPLIER1_E3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      hash_combine(h, e.L2_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mSUPPLIER1_E3_1_entry& x, const NUMWAIT_mSUPPLIER1_E3_1_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY && x.L2_SUPPKEY == y.L2_SUPPKEY;
    }
  };
  
  struct NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mSUPPLIER1_E3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L1_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mSUPPLIER1_E3_1_entry& x, const NUMWAIT_mSUPPLIER1_E3_1_entry& y) {
      return x.L1_ORDERKEY == y.L1_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAIT_mSUPPLIER1_E3_1_entry,long,
    HashIndex<NUMWAIT_mSUPPLIER1_E3_1_entry,long,NUMWAIT_mSUPPLIER1_E3_1_mapkey01_idxfn,true>,
    HashIndex<NUMWAIT_mSUPPLIER1_E3_1_entry,long,NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn,false>
  > NUMWAIT_mSUPPLIER1_E3_1_map;
  typedef HashIndex<NUMWAIT_mSUPPLIER1_E3_1_entry,long,NUMWAIT_mSUPPLIER1_E3_1_mapkey01_idxfn,true> HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_01;
  typedef HashIndex<NUMWAIT_mSUPPLIER1_E3_1_entry,long,NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn,false> HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0;
  
  struct NUMWAIT_mSUPPLIER2_entry {
    long NUMWAIT_mSUPPLIERSUPPLIER_NATIONKEY; long __av; 
    explicit NUMWAIT_mSUPPLIER2_entry() { /*NUMWAIT_mSUPPLIERSUPPLIER_NATIONKEY = 0L; __av = 0L; */ }
    explicit NUMWAIT_mSUPPLIER2_entry(const long c0, const long c1) { NUMWAIT_mSUPPLIERSUPPLIER_NATIONKEY = c0; __av = c1; }
    NUMWAIT_mSUPPLIER2_entry(const NUMWAIT_mSUPPLIER2_entry& other) : NUMWAIT_mSUPPLIERSUPPLIER_NATIONKEY( other.NUMWAIT_mSUPPLIERSUPPLIER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMWAIT_mSUPPLIER2_entry& modify(const long c0) { NUMWAIT_mSUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NUMWAIT_mSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMWAIT_mSUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMWAIT_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NUMWAIT_mSUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMWAIT_mSUPPLIER2_entry& x, const NUMWAIT_mSUPPLIER2_entry& y) {
      return x.NUMWAIT_mSUPPLIERSUPPLIER_NATIONKEY == y.NUMWAIT_mSUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<NUMWAIT_mSUPPLIER2_entry,long,
    HashIndex<NUMWAIT_mSUPPLIER2_entry,long,NUMWAIT_mSUPPLIER2_mapkey0_idxfn,true>
  > NUMWAIT_mSUPPLIER2_map;
  typedef HashIndex<NUMWAIT_mSUPPLIER2_entry,long,NUMWAIT_mSUPPLIER2_mapkey0_idxfn,true> HashIndex_NUMWAIT_mSUPPLIER2_map_0;
  
  
  
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
        long l1 = 0L;
        { //slice 
          const HashIndex_NUMWAIT_mLINEITEM7_map_2* i1 = static_cast<HashIndex_NUMWAIT_mLINEITEM7_map_2*>(NUMWAIT_mLINEITEM7.index[1]);
          const HASH_RES_t h3 = NUMWAIT_mLINEITEM7_mapkey2_idxfn::hash(se5.modify2(lineitem_orderkey));
          HashIndex_NUMWAIT_mLINEITEM7_map_2::IdxNode* n1 = static_cast<HashIndex_NUMWAIT_mLINEITEM7_map_2::IdxNode*>(i1->slice(se5, h3));
          NUMWAIT_mLINEITEM7_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long s_suppkey = e1->S_SUPPKEY;
              STRING_TYPE s_name = e1->S_NAME;
              long v1 = e1->__av;
              long agg1 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0* i2 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0*>(NUMWAIT_mSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h1 = NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::hash(se3.modify0(lineitem_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode* n2 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode*>(i2->slice(se3, h1));
                NUMWAIT_mSUPPLIER1_L2_1_entry* e2;
               
                if (n2 && (e2 = n2->obj)) {
                  do {                
                    long l3_suppkey = e2->L3_SUPPKEY;
                    long v2 = e2->__av;
                    (/*if */(l3_suppkey != s_suppkey) ? agg1 += v2 : 0L);
                    n2 = n2->nxt;
                  } while (n2 && (e2 = n2->obj) && h1 == n2->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::equals(se3, *e2)); 
                }
              }long agg2 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0* i3 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0*>(NUMWAIT_mSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h2 = NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::hash(se4.modify0(lineitem_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode* n3 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode*>(i3->slice(se4, h2));
                NUMWAIT_mSUPPLIER1_E3_1_entry* e3;
               
                if (n3 && (e3 = n3->obj)) {
                  do {                
                    long l2_suppkey = e3->L2_SUPPKEY;
                    long v3 = e3->__av;
                    (/*if */(l2_suppkey != s_suppkey) ? agg2 += v3 : 0L);
                    n3 = n3->nxt;
                  } while (n3 && (e3 = n3->obj) && h2 == n3->hash &&  NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::equals(se4, *e3)); 
                }
              }(/*if */(l1 == agg1) ? NUMWAIT.addOrDelOnZero(se1.modify(s_name),(NUMWAIT_mLINEITEM1.getValueOrDefault(se2.modify(lineitem_orderkey)) * ((v1 * (agg2 != 0 ? 1L : 0L)) * -1L))) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h3 == n1->hash &&  NUMWAIT_mLINEITEM7_mapkey2_idxfn::equals(se5, *e1)); 
          }
        }long l2 = 0L;
        { //slice 
          const HashIndex_NUMWAIT_mLINEITEM7_map_2* i4 = static_cast<HashIndex_NUMWAIT_mLINEITEM7_map_2*>(NUMWAIT_mLINEITEM7.index[1]);
          const HASH_RES_t h6 = NUMWAIT_mLINEITEM7_mapkey2_idxfn::hash(se8.modify2(lineitem_orderkey));
          HashIndex_NUMWAIT_mLINEITEM7_map_2::IdxNode* n4 = static_cast<HashIndex_NUMWAIT_mLINEITEM7_map_2::IdxNode*>(i4->slice(se8, h6));
          NUMWAIT_mLINEITEM7_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long s_suppkey = e4->S_SUPPKEY;
              STRING_TYPE s_name = e4->S_NAME;
              long v4 = e4->__av;
              long agg3 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0* i5 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0*>(NUMWAIT_mSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h4 = NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::hash(se6.modify0(lineitem_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode* n5 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode*>(i5->slice(se6, h4));
                NUMWAIT_mSUPPLIER1_L2_1_entry* e5;
               
                if (n5 && (e5 = n5->obj)) {
                  do {                
                    long l3_suppkey = e5->L3_SUPPKEY;
                    long v5 = e5->__av;
                    (/*if */(l3_suppkey != s_suppkey) ? agg3 += v5 : 0L);
                    n5 = n5->nxt;
                  } while (n5 && (e5 = n5->obj) && h4 == n5->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::equals(se6, *e5)); 
                }
              }long agg4 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0* i6 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0*>(NUMWAIT_mSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h5 = NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::hash(se7.modify0(lineitem_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode* n6 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode*>(i6->slice(se7, h5));
                NUMWAIT_mSUPPLIER1_E3_1_entry* e6;
               
                if (n6 && (e6 = n6->obj)) {
                  do {                
                    long l2_suppkey = e6->L2_SUPPKEY;
                    long v6 = e6->__av;
                    (/*if */(l2_suppkey != s_suppkey) ? agg4 += v6 : 0L);
                    n6 = n6->nxt;
                  } while (n6 && (e6 = n6->obj) && h5 == n6->hash &&  NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::equals(se7, *e6)); 
                }
              }(/*if */(l2 == (agg3 + (/*if */(lineitem_suppkey != s_suppkey && lineitem_receiptdate > lineitem_commitdate) ? 1L : 0L))) ? NUMWAIT.addOrDelOnZero(se1.modify(s_name),(NUMWAIT_mLINEITEM1.getValueOrDefault(se2.modify(lineitem_orderkey)) * (v4 * ((agg4 + (/*if */(lineitem_suppkey != s_suppkey) ? 1L : 0L)) != 0 ? 1L : 0L)))) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h6 == n4->hash &&  NUMWAIT_mLINEITEM7_mapkey2_idxfn::equals(se8, *e4)); 
          }
        }{ //slice 
          const HashIndex_NUMWAIT_mLINEITEM2_map_0* i7 = static_cast<HashIndex_NUMWAIT_mLINEITEM2_map_0*>(NUMWAIT_mLINEITEM2.index[1]);
          const HASH_RES_t h9 = NUMWAIT_mLINEITEM2_mapkey0_idxfn::hash(se11.modify0(lineitem_suppkey));
          HashIndex_NUMWAIT_mLINEITEM2_map_0::IdxNode* n7 = static_cast<HashIndex_NUMWAIT_mLINEITEM2_map_0::IdxNode*>(i7->slice(se11, h9));
          NUMWAIT_mLINEITEM2_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              STRING_TYPE s_name = e7->S_NAME;
              long v7 = e7->__av;
              long agg5 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0* i8 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0*>(NUMWAIT_mSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h7 = NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::hash(se9.modify0(lineitem_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode* n8 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode*>(i8->slice(se9, h7));
                NUMWAIT_mSUPPLIER1_E3_1_entry* e8;
               
                if (n8 && (e8 = n8->obj)) {
                  do {                
                    long l2_suppkey = e8->L2_SUPPKEY;
                    long v8 = e8->__av;
                    (/*if */(l2_suppkey != lineitem_suppkey) ? agg5 += v8 : 0L);
                    n8 = n8->nxt;
                  } while (n8 && (e8 = n8->obj) && h7 == n8->hash &&  NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::equals(se9, *e8)); 
                }
              }long agg6 = 0L;
              long agg7 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0* i9 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0*>(NUMWAIT_mSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h8 = NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::hash(se10.modify0(lineitem_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode* n9 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode*>(i9->slice(se10, h8));
                NUMWAIT_mSUPPLIER1_L2_1_entry* e9;
               
                if (n9 && (e9 = n9->obj)) {
                  do {                
                    long l3_suppkey = e9->L3_SUPPKEY;
                    long v9 = e9->__av;
                    (/*if */(l3_suppkey != lineitem_suppkey) ? agg7 += v9 : 0L);
                    n9 = n9->nxt;
                  } while (n9 && (e9 = n9->obj) && h8 == n9->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::equals(se10, *e9)); 
                }
              }long l3 = agg7;
              (/*if */(l3 == 0L) ? agg6 += 1L : 0L);
              (/*if */(lineitem_receiptdate > lineitem_commitdate) ? NUMWAIT.addOrDelOnZero(se1.modify(s_name),(NUMWAIT_mLINEITEM1.getValueOrDefault(se2.modify(lineitem_orderkey)) * (v7 * ((agg5 != 0 ? 1L : 0L) * agg6)))) : (void)0);
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h9 == n7->hash &&  NUMWAIT_mLINEITEM2_mapkey0_idxfn::equals(se11, *e7)); 
          }
        }{ //slice 
          const HashIndex_NUMWAIT_mLINEITEM2_map_0* i10 = static_cast<HashIndex_NUMWAIT_mLINEITEM2_map_0*>(NUMWAIT_mLINEITEM2.index[1]);
          const HASH_RES_t h10 = NUMWAIT_mLINEITEM2_mapkey0_idxfn::hash(se13.modify0(lineitem_suppkey));
          HashIndex_NUMWAIT_mLINEITEM2_map_0::IdxNode* n10 = static_cast<HashIndex_NUMWAIT_mLINEITEM2_map_0::IdxNode*>(i10->slice(se13, h10));
          NUMWAIT_mLINEITEM2_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              STRING_TYPE s_name = e10->S_NAME;
              long v10 = e10->__av;
              (/*if */(lineitem_receiptdate > lineitem_commitdate) ? NUMWAIT_mLINEITEM7.addOrDelOnZero(se12.modify(lineitem_suppkey,s_name,lineitem_orderkey),v10) : (void)0);
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h10 == n10->hash &&  NUMWAIT_mLINEITEM2_mapkey0_idxfn::equals(se13, *e10)); 
          }
        }(/*if */(lineitem_receiptdate > lineitem_commitdate) ? NUMWAIT_mSUPPLIER1.addOrDelOnZero(se14.modify(lineitem_orderkey,lineitem_suppkey),NUMWAIT_mLINEITEM1.getValueOrDefault(se15.modify(lineitem_orderkey))) : (void)0);
        (/*if */(lineitem_receiptdate > lineitem_commitdate) ? NUMWAIT_mSUPPLIER1_L2_1.addOrDelOnZero(se16.modify(lineitem_orderkey,lineitem_suppkey),1L) : (void)0);
        NUMWAIT_mSUPPLIER1_E3_1.addOrDelOnZero(se17.modify(lineitem_orderkey,lineitem_suppkey),1L);
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long l4 = 0L;
        { //slice 
          const HashIndex_NUMWAIT_mLINEITEM7_map_2* i11 = static_cast<HashIndex_NUMWAIT_mLINEITEM7_map_2*>(NUMWAIT_mLINEITEM7.index[1]);
          const HASH_RES_t h13 = NUMWAIT_mLINEITEM7_mapkey2_idxfn::hash(se22.modify2(lineitem_orderkey));
          HashIndex_NUMWAIT_mLINEITEM7_map_2::IdxNode* n11 = static_cast<HashIndex_NUMWAIT_mLINEITEM7_map_2::IdxNode*>(i11->slice(se22, h13));
          NUMWAIT_mLINEITEM7_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              long s_suppkey = e11->S_SUPPKEY;
              STRING_TYPE s_name = e11->S_NAME;
              long v11 = e11->__av;
              long agg8 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0* i12 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0*>(NUMWAIT_mSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h11 = NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::hash(se20.modify0(lineitem_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode* n12 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode*>(i12->slice(se20, h11));
                NUMWAIT_mSUPPLIER1_L2_1_entry* e12;
               
                if (n12 && (e12 = n12->obj)) {
                  do {                
                    long l3_suppkey = e12->L3_SUPPKEY;
                    long v12 = e12->__av;
                    (/*if */(l3_suppkey != s_suppkey) ? agg8 += v12 : 0L);
                    n12 = n12->nxt;
                  } while (n12 && (e12 = n12->obj) && h11 == n12->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::equals(se20, *e12)); 
                }
              }long agg9 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0* i13 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0*>(NUMWAIT_mSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h12 = NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::hash(se21.modify0(lineitem_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode* n13 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode*>(i13->slice(se21, h12));
                NUMWAIT_mSUPPLIER1_E3_1_entry* e13;
               
                if (n13 && (e13 = n13->obj)) {
                  do {                
                    long l2_suppkey = e13->L2_SUPPKEY;
                    long v13 = e13->__av;
                    (/*if */(l2_suppkey != s_suppkey) ? agg9 += v13 : 0L);
                    n13 = n13->nxt;
                  } while (n13 && (e13 = n13->obj) && h12 == n13->hash &&  NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::equals(se21, *e13)); 
                }
              }(/*if */(l4 == agg8) ? NUMWAIT.addOrDelOnZero(se18.modify(s_name),(NUMWAIT_mLINEITEM1.getValueOrDefault(se19.modify(lineitem_orderkey)) * ((v11 * (agg9 != 0 ? 1L : 0L)) * -1L))) : (void)0);
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h13 == n11->hash &&  NUMWAIT_mLINEITEM7_mapkey2_idxfn::equals(se22, *e11)); 
          }
        }long l5 = 0L;
        { //slice 
          const HashIndex_NUMWAIT_mLINEITEM7_map_2* i14 = static_cast<HashIndex_NUMWAIT_mLINEITEM7_map_2*>(NUMWAIT_mLINEITEM7.index[1]);
          const HASH_RES_t h16 = NUMWAIT_mLINEITEM7_mapkey2_idxfn::hash(se25.modify2(lineitem_orderkey));
          HashIndex_NUMWAIT_mLINEITEM7_map_2::IdxNode* n14 = static_cast<HashIndex_NUMWAIT_mLINEITEM7_map_2::IdxNode*>(i14->slice(se25, h16));
          NUMWAIT_mLINEITEM7_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              long s_suppkey = e14->S_SUPPKEY;
              STRING_TYPE s_name = e14->S_NAME;
              long v14 = e14->__av;
              long agg10 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0* i15 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0*>(NUMWAIT_mSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h14 = NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::hash(se23.modify0(lineitem_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode* n15 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode*>(i15->slice(se23, h14));
                NUMWAIT_mSUPPLIER1_L2_1_entry* e15;
               
                if (n15 && (e15 = n15->obj)) {
                  do {                
                    long l3_suppkey = e15->L3_SUPPKEY;
                    long v15 = e15->__av;
                    (/*if */(l3_suppkey != s_suppkey) ? agg10 += v15 : 0L);
                    n15 = n15->nxt;
                  } while (n15 && (e15 = n15->obj) && h14 == n15->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::equals(se23, *e15)); 
                }
              }long agg11 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0* i16 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0*>(NUMWAIT_mSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h15 = NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::hash(se24.modify0(lineitem_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode* n16 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode*>(i16->slice(se24, h15));
                NUMWAIT_mSUPPLIER1_E3_1_entry* e16;
               
                if (n16 && (e16 = n16->obj)) {
                  do {                
                    long l2_suppkey = e16->L2_SUPPKEY;
                    long v16 = e16->__av;
                    (/*if */(l2_suppkey != s_suppkey) ? agg11 += v16 : 0L);
                    n16 = n16->nxt;
                  } while (n16 && (e16 = n16->obj) && h15 == n16->hash &&  NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::equals(se24, *e16)); 
                }
              }(/*if */(l5 == (agg10 + (/*if */(lineitem_suppkey != s_suppkey && lineitem_receiptdate > lineitem_commitdate) ? -1L : 0L))) ? NUMWAIT.addOrDelOnZero(se18.modify(s_name),(NUMWAIT_mLINEITEM1.getValueOrDefault(se19.modify(lineitem_orderkey)) * (v14 * ((agg11 + (/*if */(lineitem_suppkey != s_suppkey) ? -1L : 0L)) != 0 ? 1L : 0L)))) : (void)0);
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h16 == n14->hash &&  NUMWAIT_mLINEITEM7_mapkey2_idxfn::equals(se25, *e14)); 
          }
        }{ //slice 
          const HashIndex_NUMWAIT_mLINEITEM2_map_0* i17 = static_cast<HashIndex_NUMWAIT_mLINEITEM2_map_0*>(NUMWAIT_mLINEITEM2.index[1]);
          const HASH_RES_t h19 = NUMWAIT_mLINEITEM2_mapkey0_idxfn::hash(se28.modify0(lineitem_suppkey));
          HashIndex_NUMWAIT_mLINEITEM2_map_0::IdxNode* n17 = static_cast<HashIndex_NUMWAIT_mLINEITEM2_map_0::IdxNode*>(i17->slice(se28, h19));
          NUMWAIT_mLINEITEM2_entry* e17;
         
          if (n17 && (e17 = n17->obj)) {
            do {                
              STRING_TYPE s_name = e17->S_NAME;
              long v17 = e17->__av;
              long agg12 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0* i18 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0*>(NUMWAIT_mSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h17 = NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::hash(se26.modify0(lineitem_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode* n18 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode*>(i18->slice(se26, h17));
                NUMWAIT_mSUPPLIER1_E3_1_entry* e18;
               
                if (n18 && (e18 = n18->obj)) {
                  do {                
                    long l2_suppkey = e18->L2_SUPPKEY;
                    long v18 = e18->__av;
                    (/*if */(l2_suppkey != lineitem_suppkey) ? agg12 += v18 : 0L);
                    n18 = n18->nxt;
                  } while (n18 && (e18 = n18->obj) && h17 == n18->hash &&  NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::equals(se26, *e18)); 
                }
              }long agg13 = 0L;
              long agg14 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0* i19 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0*>(NUMWAIT_mSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h18 = NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::hash(se27.modify0(lineitem_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode* n19 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode*>(i19->slice(se27, h18));
                NUMWAIT_mSUPPLIER1_L2_1_entry* e19;
               
                if (n19 && (e19 = n19->obj)) {
                  do {                
                    long l3_suppkey = e19->L3_SUPPKEY;
                    long v19 = e19->__av;
                    (/*if */(l3_suppkey != lineitem_suppkey) ? agg14 += v19 : 0L);
                    n19 = n19->nxt;
                  } while (n19 && (e19 = n19->obj) && h18 == n19->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::equals(se27, *e19)); 
                }
              }long l6 = agg14;
              (/*if */(l6 == 0L) ? agg13 += 1L : 0L);
              (/*if */(lineitem_receiptdate > lineitem_commitdate) ? NUMWAIT.addOrDelOnZero(se18.modify(s_name),(NUMWAIT_mLINEITEM1.getValueOrDefault(se19.modify(lineitem_orderkey)) * (v17 * ((agg12 != 0 ? 1L : 0L) * (agg13 * -1L))))) : (void)0);
              n17 = n17->nxt;
            } while (n17 && (e17 = n17->obj) && h19 == n17->hash &&  NUMWAIT_mLINEITEM2_mapkey0_idxfn::equals(se28, *e17)); 
          }
        }{ //slice 
          const HashIndex_NUMWAIT_mLINEITEM2_map_0* i20 = static_cast<HashIndex_NUMWAIT_mLINEITEM2_map_0*>(NUMWAIT_mLINEITEM2.index[1]);
          const HASH_RES_t h20 = NUMWAIT_mLINEITEM2_mapkey0_idxfn::hash(se30.modify0(lineitem_suppkey));
          HashIndex_NUMWAIT_mLINEITEM2_map_0::IdxNode* n20 = static_cast<HashIndex_NUMWAIT_mLINEITEM2_map_0::IdxNode*>(i20->slice(se30, h20));
          NUMWAIT_mLINEITEM2_entry* e20;
         
          if (n20 && (e20 = n20->obj)) {
            do {                
              STRING_TYPE s_name = e20->S_NAME;
              long v20 = e20->__av;
              (/*if */(lineitem_receiptdate > lineitem_commitdate) ? NUMWAIT_mLINEITEM7.addOrDelOnZero(se29.modify(lineitem_suppkey,s_name,lineitem_orderkey),(v20 * -1L)) : (void)0);
              n20 = n20->nxt;
            } while (n20 && (e20 = n20->obj) && h20 == n20->hash &&  NUMWAIT_mLINEITEM2_mapkey0_idxfn::equals(se30, *e20)); 
          }
        }(/*if */(lineitem_receiptdate > lineitem_commitdate) ? NUMWAIT_mSUPPLIER1.addOrDelOnZero(se31.modify(lineitem_orderkey,lineitem_suppkey),(NUMWAIT_mLINEITEM1.getValueOrDefault(se32.modify(lineitem_orderkey)) * -1L)) : (void)0);
        (/*if */(lineitem_receiptdate > lineitem_commitdate) ? NUMWAIT_mSUPPLIER1_L2_1.addOrDelOnZero(se33.modify(lineitem_orderkey,lineitem_suppkey),-1L) : (void)0);
        NUMWAIT_mSUPPLIER1_E3_1.addOrDelOnZero(se34.modify(lineitem_orderkey,lineitem_suppkey),-1L);
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long l7 = 0L;
        { //slice 
          const HashIndex_NUMWAIT_mLINEITEM7_map_2* i21 = static_cast<HashIndex_NUMWAIT_mLINEITEM7_map_2*>(NUMWAIT_mLINEITEM7.index[1]);
          const HASH_RES_t h23 = NUMWAIT_mLINEITEM7_mapkey2_idxfn::hash(se38.modify2(orders_orderkey));
          HashIndex_NUMWAIT_mLINEITEM7_map_2::IdxNode* n21 = static_cast<HashIndex_NUMWAIT_mLINEITEM7_map_2::IdxNode*>(i21->slice(se38, h23));
          NUMWAIT_mLINEITEM7_entry* e21;
         
          if (n21 && (e21 = n21->obj)) {
            do {                
              long s_suppkey = e21->S_SUPPKEY;
              STRING_TYPE s_name = e21->S_NAME;
              long v21 = e21->__av;
              long agg15 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0* i22 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0*>(NUMWAIT_mSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h21 = NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::hash(se36.modify0(orders_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode* n22 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode*>(i22->slice(se36, h21));
                NUMWAIT_mSUPPLIER1_L2_1_entry* e22;
               
                if (n22 && (e22 = n22->obj)) {
                  do {                
                    long l3_suppkey = e22->L3_SUPPKEY;
                    long v22 = e22->__av;
                    (/*if */(l3_suppkey != s_suppkey) ? agg15 += v22 : 0L);
                    n22 = n22->nxt;
                  } while (n22 && (e22 = n22->obj) && h21 == n22->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::equals(se36, *e22)); 
                }
              }long agg16 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0* i23 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0*>(NUMWAIT_mSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h22 = NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::hash(se37.modify0(orders_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode* n23 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode*>(i23->slice(se37, h22));
                NUMWAIT_mSUPPLIER1_E3_1_entry* e23;
               
                if (n23 && (e23 = n23->obj)) {
                  do {                
                    long l2_suppkey = e23->L2_SUPPKEY;
                    long v23 = e23->__av;
                    (/*if */(l2_suppkey != s_suppkey) ? agg16 += v23 : 0L);
                    n23 = n23->nxt;
                  } while (n23 && (e23 = n23->obj) && h22 == n23->hash &&  NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::equals(se37, *e23)); 
                }
              }(/*if */(orders_orderstatus == c1 && l7 == agg15) ? NUMWAIT.addOrDelOnZero(se35.modify(s_name),(v21 * (agg16 != 0 ? 1L : 0L))) : (void)0);
              n21 = n21->nxt;
            } while (n21 && (e21 = n21->obj) && h23 == n21->hash &&  NUMWAIT_mLINEITEM7_mapkey2_idxfn::equals(se38, *e21)); 
          }
        }(/*if */(orders_orderstatus == c1) ? NUMWAIT_mLINEITEM1.addOrDelOnZero(se39.modify(orders_orderkey),1L) : (void)0);
        { //slice 
          const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0* i24 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0*>(NUMWAIT_mSUPPLIER1_L2_1.index[1]);
          const HASH_RES_t h24 = NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::hash(se41.modify0(orders_orderkey));
          HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode* n24 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode*>(i24->slice(se41, h24));
          NUMWAIT_mSUPPLIER1_L2_1_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              long numwait_msuppliersupplier_suppkey = e24->L3_SUPPKEY;
              long v24 = e24->__av;
              (/*if */(orders_orderstatus == c1) ? NUMWAIT_mSUPPLIER1.addOrDelOnZero(se40.modify(orders_orderkey,numwait_msuppliersupplier_suppkey),v24) : (void)0);
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h24 == n24->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::equals(se41, *e24)); 
          }
        }
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long l8 = 0L;
        { //slice 
          const HashIndex_NUMWAIT_mLINEITEM7_map_2* i25 = static_cast<HashIndex_NUMWAIT_mLINEITEM7_map_2*>(NUMWAIT_mLINEITEM7.index[1]);
          const HASH_RES_t h27 = NUMWAIT_mLINEITEM7_mapkey2_idxfn::hash(se45.modify2(orders_orderkey));
          HashIndex_NUMWAIT_mLINEITEM7_map_2::IdxNode* n25 = static_cast<HashIndex_NUMWAIT_mLINEITEM7_map_2::IdxNode*>(i25->slice(se45, h27));
          NUMWAIT_mLINEITEM7_entry* e25;
         
          if (n25 && (e25 = n25->obj)) {
            do {                
              long s_suppkey = e25->S_SUPPKEY;
              STRING_TYPE s_name = e25->S_NAME;
              long v25 = e25->__av;
              long agg17 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0* i26 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0*>(NUMWAIT_mSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h25 = NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::hash(se43.modify0(orders_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode* n26 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode*>(i26->slice(se43, h25));
                NUMWAIT_mSUPPLIER1_L2_1_entry* e26;
               
                if (n26 && (e26 = n26->obj)) {
                  do {                
                    long l3_suppkey = e26->L3_SUPPKEY;
                    long v26 = e26->__av;
                    (/*if */(l3_suppkey != s_suppkey) ? agg17 += v26 : 0L);
                    n26 = n26->nxt;
                  } while (n26 && (e26 = n26->obj) && h25 == n26->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::equals(se43, *e26)); 
                }
              }long agg18 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0* i27 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0*>(NUMWAIT_mSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h26 = NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::hash(se44.modify0(orders_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode* n27 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode*>(i27->slice(se44, h26));
                NUMWAIT_mSUPPLIER1_E3_1_entry* e27;
               
                if (n27 && (e27 = n27->obj)) {
                  do {                
                    long l2_suppkey = e27->L2_SUPPKEY;
                    long v27 = e27->__av;
                    (/*if */(l2_suppkey != s_suppkey) ? agg18 += v27 : 0L);
                    n27 = n27->nxt;
                  } while (n27 && (e27 = n27->obj) && h26 == n27->hash &&  NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::equals(se44, *e27)); 
                }
              }(/*if */(orders_orderstatus == c1 && l8 == agg17) ? NUMWAIT.addOrDelOnZero(se42.modify(s_name),((v25 * (agg18 != 0 ? 1L : 0L)) * -1L)) : (void)0);
              n25 = n25->nxt;
            } while (n25 && (e25 = n25->obj) && h27 == n25->hash &&  NUMWAIT_mLINEITEM7_mapkey2_idxfn::equals(se45, *e25)); 
          }
        }(/*if */(orders_orderstatus == c1) ? NUMWAIT_mLINEITEM1.addOrDelOnZero(se46.modify(orders_orderkey),-1L) : (void)0);
        { //slice 
          const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0* i28 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0*>(NUMWAIT_mSUPPLIER1_L2_1.index[1]);
          const HASH_RES_t h28 = NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::hash(se48.modify0(orders_orderkey));
          HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode* n28 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode*>(i28->slice(se48, h28));
          NUMWAIT_mSUPPLIER1_L2_1_entry* e28;
         
          if (n28 && (e28 = n28->obj)) {
            do {                
              long numwait_msuppliersupplier_suppkey = e28->L3_SUPPKEY;
              long v28 = e28->__av;
              (/*if */(orders_orderstatus == c1) ? NUMWAIT_mSUPPLIER1.addOrDelOnZero(se47.modify(orders_orderkey,numwait_msuppliersupplier_suppkey),(v28 * -1L)) : (void)0);
              n28 = n28->nxt;
            } while (n28 && (e28 = n28->obj) && h28 == n28->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::equals(se48, *e28)); 
          }
        }
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg19 = 0L;
        long l9 = 0L;
        { //slice 
          const HashIndex_NUMWAIT_mSUPPLIER1_map_1* i29 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_map_1*>(NUMWAIT_mSUPPLIER1.index[1]);
          const HASH_RES_t h31 = NUMWAIT_mSUPPLIER1_mapkey1_idxfn::hash(se52.modify1(supplier_suppkey));
          HashIndex_NUMWAIT_mSUPPLIER1_map_1::IdxNode* n29 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_map_1::IdxNode*>(i29->slice(se52, h31));
          NUMWAIT_mSUPPLIER1_entry* e29;
         
          if (n29 && (e29 = n29->obj)) {
            do {                
              long l1_orderkey = e29->L1_ORDERKEY;
              long v29 = e29->__av;
              long agg20 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0* i30 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0*>(NUMWAIT_mSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h29 = NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::hash(se50.modify0(l1_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode* n30 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode*>(i30->slice(se50, h29));
                NUMWAIT_mSUPPLIER1_L2_1_entry* e30;
               
                if (n30 && (e30 = n30->obj)) {
                  do {                
                    long l3_suppkey = e30->L3_SUPPKEY;
                    long v30 = e30->__av;
                    (/*if */(l3_suppkey != supplier_suppkey) ? agg20 += v30 : 0L);
                    n30 = n30->nxt;
                  } while (n30 && (e30 = n30->obj) && h29 == n30->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::equals(se50, *e30)); 
                }
              }long agg21 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0* i31 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0*>(NUMWAIT_mSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h30 = NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::hash(se51.modify0(l1_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode* n31 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode*>(i31->slice(se51, h30));
                NUMWAIT_mSUPPLIER1_E3_1_entry* e31;
               
                if (n31 && (e31 = n31->obj)) {
                  do {                
                    long l2_suppkey = e31->L2_SUPPKEY;
                    long v31 = e31->__av;
                    (/*if */(l2_suppkey != supplier_suppkey) ? agg21 += v31 : 0L);
                    n31 = n31->nxt;
                  } while (n31 && (e31 = n31->obj) && h30 == n31->hash &&  NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::equals(se51, *e31)); 
                }
              }(/*if */(l9 == agg20) ? agg19 += (v29 * (agg21 != 0 ? 1L : 0L)) : 0L);
              n29 = n29->nxt;
            } while (n29 && (e29 = n29->obj) && h31 == n29->hash &&  NUMWAIT_mSUPPLIER1_mapkey1_idxfn::equals(se52, *e29)); 
          }
        }NUMWAIT.addOrDelOnZero(se49.modify(supplier_name),(agg19 * NUMWAIT_mSUPPLIER2.getValueOrDefault(se53.modify(supplier_nationkey))));
        NUMWAIT_mLINEITEM2.addOrDelOnZero(se54.modify(supplier_suppkey,supplier_name),NUMWAIT_mSUPPLIER2.getValueOrDefault(se55.modify(supplier_nationkey)));
        { //slice 
          const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_1* i32 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_1*>(NUMWAIT_mSUPPLIER1_L2_1.index[2]);
          const HASH_RES_t h32 = NUMWAIT_mSUPPLIER1_L2_1_mapkey1_idxfn::hash(se58.modify1(supplier_suppkey));
          HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_1::IdxNode* n32 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_1::IdxNode*>(i32->slice(se58, h32));
          NUMWAIT_mSUPPLIER1_L2_1_entry* e32;
         
          if (n32 && (e32 = n32->obj)) {
            do {                
              long numwait_mlineitemlineitem_orderkey = e32->L1_ORDERKEY;
              long v32 = e32->__av;
              NUMWAIT_mLINEITEM7.addOrDelOnZero(se56.modify(supplier_suppkey,supplier_name,numwait_mlineitemlineitem_orderkey),(NUMWAIT_mSUPPLIER2.getValueOrDefault(se57.modify(supplier_nationkey)) * v32));
              n32 = n32->nxt;
            } while (n32 && (e32 = n32->obj) && h32 == n32->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey1_idxfn::equals(se58, *e32)); 
          }
        }
      }
    }
    void on_delete_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg22 = 0L;
        long l10 = 0L;
        { //slice 
          const HashIndex_NUMWAIT_mSUPPLIER1_map_1* i33 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_map_1*>(NUMWAIT_mSUPPLIER1.index[1]);
          const HASH_RES_t h35 = NUMWAIT_mSUPPLIER1_mapkey1_idxfn::hash(se62.modify1(supplier_suppkey));
          HashIndex_NUMWAIT_mSUPPLIER1_map_1::IdxNode* n33 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_map_1::IdxNode*>(i33->slice(se62, h35));
          NUMWAIT_mSUPPLIER1_entry* e33;
         
          if (n33 && (e33 = n33->obj)) {
            do {                
              long l1_orderkey = e33->L1_ORDERKEY;
              long v33 = e33->__av;
              long agg23 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0* i34 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0*>(NUMWAIT_mSUPPLIER1_L2_1.index[1]);
                const HASH_RES_t h33 = NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::hash(se60.modify0(l1_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode* n34 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_0::IdxNode*>(i34->slice(se60, h33));
                NUMWAIT_mSUPPLIER1_L2_1_entry* e34;
               
                if (n34 && (e34 = n34->obj)) {
                  do {                
                    long l3_suppkey = e34->L3_SUPPKEY;
                    long v34 = e34->__av;
                    (/*if */(l3_suppkey != supplier_suppkey) ? agg23 += v34 : 0L);
                    n34 = n34->nxt;
                  } while (n34 && (e34 = n34->obj) && h33 == n34->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey0_idxfn::equals(se60, *e34)); 
                }
              }long agg24 = 0L;
              { //slice 
                const HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0* i35 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0*>(NUMWAIT_mSUPPLIER1_E3_1.index[1]);
                const HASH_RES_t h34 = NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::hash(se61.modify0(l1_orderkey));
                HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode* n35 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_E3_1_map_0::IdxNode*>(i35->slice(se61, h34));
                NUMWAIT_mSUPPLIER1_E3_1_entry* e35;
               
                if (n35 && (e35 = n35->obj)) {
                  do {                
                    long l2_suppkey = e35->L2_SUPPKEY;
                    long v35 = e35->__av;
                    (/*if */(l2_suppkey != supplier_suppkey) ? agg24 += v35 : 0L);
                    n35 = n35->nxt;
                  } while (n35 && (e35 = n35->obj) && h34 == n35->hash &&  NUMWAIT_mSUPPLIER1_E3_1_mapkey0_idxfn::equals(se61, *e35)); 
                }
              }(/*if */(l10 == agg23) ? agg22 += (v33 * (agg24 != 0 ? 1L : 0L)) : 0L);
              n33 = n33->nxt;
            } while (n33 && (e33 = n33->obj) && h35 == n33->hash &&  NUMWAIT_mSUPPLIER1_mapkey1_idxfn::equals(se62, *e33)); 
          }
        }NUMWAIT.addOrDelOnZero(se59.modify(supplier_name),(agg22 * (NUMWAIT_mSUPPLIER2.getValueOrDefault(se63.modify(supplier_nationkey)) * -1L)));
        NUMWAIT_mLINEITEM2.addOrDelOnZero(se64.modify(supplier_suppkey,supplier_name),(NUMWAIT_mSUPPLIER2.getValueOrDefault(se65.modify(supplier_nationkey)) * -1L));
        { //slice 
          const HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_1* i36 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_1*>(NUMWAIT_mSUPPLIER1_L2_1.index[2]);
          const HASH_RES_t h36 = NUMWAIT_mSUPPLIER1_L2_1_mapkey1_idxfn::hash(se68.modify1(supplier_suppkey));
          HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_1::IdxNode* n36 = static_cast<HashIndex_NUMWAIT_mSUPPLIER1_L2_1_map_1::IdxNode*>(i36->slice(se68, h36));
          NUMWAIT_mSUPPLIER1_L2_1_entry* e36;
         
          if (n36 && (e36 = n36->obj)) {
            do {                
              long numwait_mlineitemlineitem_orderkey = e36->L1_ORDERKEY;
              long v36 = e36->__av;
              NUMWAIT_mLINEITEM7.addOrDelOnZero(se66.modify(supplier_suppkey,supplier_name,numwait_mlineitemlineitem_orderkey),(NUMWAIT_mSUPPLIER2.getValueOrDefault(se67.modify(supplier_nationkey)) * (v36 * -1L)));
              n36 = n36->nxt;
            } while (n36 && (e36 = n36->obj) && h36 == n36->hash &&  NUMWAIT_mSUPPLIER1_L2_1_mapkey1_idxfn::equals(se68, *e36)); 
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        NUMWAIT_mSUPPLIER2.clear();
        STRING_TYPE l11 = c2;
        { //slice 
          const HashIndex_NATION_map_1* i37 = static_cast<HashIndex_NATION_map_1*>(NATION.index[1]);
          const HASH_RES_t h37 = NATION_mapkey1_idxfn::hash(se70.modify1(l11));
          HashIndex_NATION_map_1::IdxNode* n37 = static_cast<HashIndex_NATION_map_1::IdxNode*>(i37->slice(se70, h37));
          NATION_entry* e37;
         
          if (n37 && (e37 = n37->obj)) {
            do {                
              long numwait_msuppliersupplier_nationkey = e37->NATION_NATIONKEY;
              long n_regionkey = e37->NATION_REGIONKEY;
              STRING_TYPE n_comment = e37->NATION_COMMENT;
              long v37 = e37->__av;
              NUMWAIT_mSUPPLIER2.addOrDelOnZero(se69.modify(numwait_msuppliersupplier_nationkey),v37);
              n37 = n37->nxt;
            } while (n37 && (e37 = n37->obj) && h37 == n37->hash &&  NATION_mapkey1_idxfn::equals(se70, *e37)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    NUMWAIT_entry se1;
    NUMWAIT_mLINEITEM1_entry se2;
    NUMWAIT_mSUPPLIER1_L2_1_entry se3;
    NUMWAIT_mSUPPLIER1_E3_1_entry se4;
    NUMWAIT_mLINEITEM7_entry se5;
    NUMWAIT_mSUPPLIER1_L2_1_entry se6;
    NUMWAIT_mSUPPLIER1_E3_1_entry se7;
    NUMWAIT_mLINEITEM7_entry se8;
    NUMWAIT_mSUPPLIER1_E3_1_entry se9;
    NUMWAIT_mSUPPLIER1_L2_1_entry se10;
    NUMWAIT_mLINEITEM2_entry se11;
    NUMWAIT_mLINEITEM7_entry se12;
    NUMWAIT_mLINEITEM2_entry se13;
    NUMWAIT_mSUPPLIER1_entry se14;
    NUMWAIT_mLINEITEM1_entry se15;
    NUMWAIT_mSUPPLIER1_L2_1_entry se16;
    NUMWAIT_mSUPPLIER1_E3_1_entry se17;
    NUMWAIT_entry se18;
    NUMWAIT_mLINEITEM1_entry se19;
    NUMWAIT_mSUPPLIER1_L2_1_entry se20;
    NUMWAIT_mSUPPLIER1_E3_1_entry se21;
    NUMWAIT_mLINEITEM7_entry se22;
    NUMWAIT_mSUPPLIER1_L2_1_entry se23;
    NUMWAIT_mSUPPLIER1_E3_1_entry se24;
    NUMWAIT_mLINEITEM7_entry se25;
    NUMWAIT_mSUPPLIER1_E3_1_entry se26;
    NUMWAIT_mSUPPLIER1_L2_1_entry se27;
    NUMWAIT_mLINEITEM2_entry se28;
    NUMWAIT_mLINEITEM7_entry se29;
    NUMWAIT_mLINEITEM2_entry se30;
    NUMWAIT_mSUPPLIER1_entry se31;
    NUMWAIT_mLINEITEM1_entry se32;
    NUMWAIT_mSUPPLIER1_L2_1_entry se33;
    NUMWAIT_mSUPPLIER1_E3_1_entry se34;
    NUMWAIT_entry se35;
    NUMWAIT_mSUPPLIER1_L2_1_entry se36;
    NUMWAIT_mSUPPLIER1_E3_1_entry se37;
    NUMWAIT_mLINEITEM7_entry se38;
    NUMWAIT_mLINEITEM1_entry se39;
    NUMWAIT_mSUPPLIER1_entry se40;
    NUMWAIT_mSUPPLIER1_L2_1_entry se41;
    NUMWAIT_entry se42;
    NUMWAIT_mSUPPLIER1_L2_1_entry se43;
    NUMWAIT_mSUPPLIER1_E3_1_entry se44;
    NUMWAIT_mLINEITEM7_entry se45;
    NUMWAIT_mLINEITEM1_entry se46;
    NUMWAIT_mSUPPLIER1_entry se47;
    NUMWAIT_mSUPPLIER1_L2_1_entry se48;
    NUMWAIT_entry se49;
    NUMWAIT_mSUPPLIER1_L2_1_entry se50;
    NUMWAIT_mSUPPLIER1_E3_1_entry se51;
    NUMWAIT_mSUPPLIER1_entry se52;
    NUMWAIT_mSUPPLIER2_entry se53;
    NUMWAIT_mLINEITEM2_entry se54;
    NUMWAIT_mSUPPLIER2_entry se55;
    NUMWAIT_mLINEITEM7_entry se56;
    NUMWAIT_mSUPPLIER2_entry se57;
    NUMWAIT_mSUPPLIER1_L2_1_entry se58;
    NUMWAIT_entry se59;
    NUMWAIT_mSUPPLIER1_L2_1_entry se60;
    NUMWAIT_mSUPPLIER1_E3_1_entry se61;
    NUMWAIT_mSUPPLIER1_entry se62;
    NUMWAIT_mSUPPLIER2_entry se63;
    NUMWAIT_mLINEITEM2_entry se64;
    NUMWAIT_mSUPPLIER2_entry se65;
    NUMWAIT_mLINEITEM7_entry se66;
    NUMWAIT_mSUPPLIER2_entry se67;
    NUMWAIT_mSUPPLIER1_L2_1_entry se68;
    NUMWAIT_mSUPPLIER2_entry se69;
    NATION_entry se70;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    NUMWAIT_mLINEITEM1_map NUMWAIT_mLINEITEM1;
    NUMWAIT_mLINEITEM2_map NUMWAIT_mLINEITEM2;
    NUMWAIT_mLINEITEM7_map NUMWAIT_mLINEITEM7;
    NUMWAIT_mSUPPLIER1_map NUMWAIT_mSUPPLIER1;
    NUMWAIT_mSUPPLIER1_L2_1_map NUMWAIT_mSUPPLIER1_L2_1;
    NUMWAIT_mSUPPLIER1_E3_1_map NUMWAIT_mSUPPLIER1_E3_1;
    NUMWAIT_mSUPPLIER2_map NUMWAIT_mSUPPLIER2;
    
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c2;
  
  };

}
