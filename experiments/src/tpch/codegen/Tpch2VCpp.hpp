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
  
  struct COUNT_entry {
    DOUBLE_TYPE S_ACCTBAL; STRING_TYPE S_NAME; STRING_TYPE N_NAME; long P_PARTKEY; STRING_TYPE P_MFGR; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; STRING_TYPE S_COMMENT; long __av; 
    explicit COUNT_entry() { /*S_ACCTBAL = 0.0; S_NAME = ""; N_NAME = ""; P_PARTKEY = 0L; P_MFGR = ""; S_ADDRESS = ""; S_PHONE = ""; S_COMMENT = ""; __av = 0L; */ }
    explicit COUNT_entry(const DOUBLE_TYPE c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const STRING_TYPE& c7, const long c8) { S_ACCTBAL = c0; S_NAME = c1; N_NAME = c2; P_PARTKEY = c3; P_MFGR = c4; S_ADDRESS = c5; S_PHONE = c6; S_COMMENT = c7; __av = c8; }
    COUNT_entry(const COUNT_entry& other) : S_ACCTBAL( other.S_ACCTBAL ), S_NAME( other.S_NAME ), N_NAME( other.N_NAME ), P_PARTKEY( other.P_PARTKEY ), P_MFGR( other.P_MFGR ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), S_COMMENT( other.S_COMMENT ), __av( other.__av ) {}
    FORCE_INLINE COUNT_entry& modify(const DOUBLE_TYPE c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const STRING_TYPE& c7) { S_ACCTBAL = c0; S_NAME = c1; N_NAME = c2; P_PARTKEY = c3; P_MFGR = c4; S_ADDRESS = c5; S_PHONE = c6; S_COMMENT = c7;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_MFGR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_ACCTBAL);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.N_NAME);
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.P_MFGR);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.S_COMMENT);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_entry& x, const COUNT_entry& y) {
      return x.S_ACCTBAL == y.S_ACCTBAL && x.S_NAME == y.S_NAME && x.N_NAME == y.N_NAME && x.P_PARTKEY == y.P_PARTKEY && x.P_MFGR == y.P_MFGR && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE && x.S_COMMENT == y.S_COMMENT;
    }
  };
  
  typedef MultiHashMap<COUNT_entry,long,
    HashIndex<COUNT_entry,long,COUNT_mapkey01234567_idxfn,true>
  > COUNT_map;
  typedef HashIndex<COUNT_entry,long,COUNT_mapkey01234567_idxfn,true> HashIndex_COUNT_map_01234567;
  
  struct COUNT_mPARTSUPP2_entry {
    long COUNT_mPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE P_MFGR; long __av; 
    explicit COUNT_mPARTSUPP2_entry() { /*COUNT_mPARTSUPPPARTSUPP_PARTKEY = 0L; P_MFGR = ""; __av = 0L; */ }
    explicit COUNT_mPARTSUPP2_entry(const long c0, const STRING_TYPE& c1, const long c2) { COUNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_MFGR = c1; __av = c2; }
    COUNT_mPARTSUPP2_entry(const COUNT_mPARTSUPP2_entry& other) : COUNT_mPARTSUPPPARTSUPP_PARTKEY( other.COUNT_mPARTSUPPPARTSUPP_PARTKEY ), P_MFGR( other.P_MFGR ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mPARTSUPP2_entry& modify(const long c0, const STRING_TYPE& c1) { COUNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_MFGR = c1;  return *this; }
    FORCE_INLINE COUNT_mPARTSUPP2_entry& modify0(const long c0) { COUNT_mPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mPARTSUPPPARTSUPP_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_MFGR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mPARTSUPP2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPARTSUPP2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.P_MFGR);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPARTSUPP2_entry& x, const COUNT_mPARTSUPP2_entry& y) {
      return x.COUNT_mPARTSUPPPARTSUPP_PARTKEY == y.COUNT_mPARTSUPPPARTSUPP_PARTKEY && x.P_MFGR == y.P_MFGR;
    }
  };
  
  struct COUNT_mPARTSUPP2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPARTSUPP2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPARTSUPP2_entry& x, const COUNT_mPARTSUPP2_entry& y) {
      return x.COUNT_mPARTSUPPPARTSUPP_PARTKEY == y.COUNT_mPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mPARTSUPP2_entry,long,
    HashIndex<COUNT_mPARTSUPP2_entry,long,COUNT_mPARTSUPP2_mapkey01_idxfn,true>,
    HashIndex<COUNT_mPARTSUPP2_entry,long,COUNT_mPARTSUPP2_mapkey0_idxfn,false>
  > COUNT_mPARTSUPP2_map;
  typedef HashIndex<COUNT_mPARTSUPP2_entry,long,COUNT_mPARTSUPP2_mapkey01_idxfn,true> HashIndex_COUNT_mPARTSUPP2_map_01;
  typedef HashIndex<COUNT_mPARTSUPP2_entry,long,COUNT_mPARTSUPP2_mapkey0_idxfn,false> HashIndex_COUNT_mPARTSUPP2_map_0;
  
  struct COUNT_mPARTSUPP3_entry {
    long COUNT_mPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; DOUBLE_TYPE S_ACCTBAL; STRING_TYPE S_COMMENT; STRING_TYPE N_NAME; long __av; 
    explicit COUNT_mPARTSUPP3_entry() { /*COUNT_mPARTSUPPPARTSUPP_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; S_ACCTBAL = 0.0; S_COMMENT = ""; N_NAME = ""; __av = 0L; */ }
    explicit COUNT_mPARTSUPP3_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const long c7) { COUNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; S_ACCTBAL = c4; S_COMMENT = c5; N_NAME = c6; __av = c7; }
    COUNT_mPARTSUPP3_entry(const COUNT_mPARTSUPP3_entry& other) : COUNT_mPARTSUPPPARTSUPP_SUPPKEY( other.COUNT_mPARTSUPPPARTSUPP_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), S_ACCTBAL( other.S_ACCTBAL ), S_COMMENT( other.S_COMMENT ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mPARTSUPP3_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6) { COUNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; S_ACCTBAL = c4; S_COMMENT = c5; N_NAME = c6;  return *this; }
    FORCE_INLINE COUNT_mPARTSUPP3_entry& modify0(const long c0) { COUNT_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mPARTSUPPPARTSUPP_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mPARTSUPP3_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPARTSUPP3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.S_ACCTBAL);
      hash_combine(h, e.S_COMMENT);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPARTSUPP3_entry& x, const COUNT_mPARTSUPP3_entry& y) {
      return x.COUNT_mPARTSUPPPARTSUPP_SUPPKEY == y.COUNT_mPARTSUPPPARTSUPP_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE && x.S_ACCTBAL == y.S_ACCTBAL && x.S_COMMENT == y.S_COMMENT && x.N_NAME == y.N_NAME;
    }
  };
  
  struct COUNT_mPARTSUPP3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPARTSUPP3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPARTSUPP3_entry& x, const COUNT_mPARTSUPP3_entry& y) {
      return x.COUNT_mPARTSUPPPARTSUPP_SUPPKEY == y.COUNT_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mPARTSUPP3_entry,long,
    HashIndex<COUNT_mPARTSUPP3_entry,long,COUNT_mPARTSUPP3_mapkey0123456_idxfn,true>,
    HashIndex<COUNT_mPARTSUPP3_entry,long,COUNT_mPARTSUPP3_mapkey0_idxfn,false>
  > COUNT_mPARTSUPP3_map;
  typedef HashIndex<COUNT_mPARTSUPP3_entry,long,COUNT_mPARTSUPP3_mapkey0123456_idxfn,true> HashIndex_COUNT_mPARTSUPP3_map_0123456;
  typedef HashIndex<COUNT_mPARTSUPP3_entry,long,COUNT_mPARTSUPP3_mapkey0_idxfn,false> HashIndex_COUNT_mPARTSUPP3_map_0;
  
  struct COUNT_mPARTSUPP3_mSUPPLIER1_entry {
    long COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY; STRING_TYPE N_NAME; long __av; 
    explicit COUNT_mPARTSUPP3_mSUPPLIER1_entry() { /*COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY = 0L; N_NAME = ""; __av = 0L; */ }
    explicit COUNT_mPARTSUPP3_mSUPPLIER1_entry(const long c0, const STRING_TYPE& c1, const long c2) { COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY = c0; N_NAME = c1; __av = c2; }
    COUNT_mPARTSUPP3_mSUPPLIER1_entry(const COUNT_mPARTSUPP3_mSUPPLIER1_entry& other) : COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY( other.COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mPARTSUPP3_mSUPPLIER1_entry& modify(const long c0, const STRING_TYPE& c1) { COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY = c0; N_NAME = c1;  return *this; }
    FORCE_INLINE COUNT_mPARTSUPP3_mSUPPLIER1_entry& modify0(const long c0) { COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mPARTSUPP3_mSUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPARTSUPP3_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPARTSUPP3_mSUPPLIER1_entry& x, const COUNT_mPARTSUPP3_mSUPPLIER1_entry& y) {
      return x.COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY == y.COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  struct COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPARTSUPP3_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPARTSUPP3_mSUPPLIER1_entry& x, const COUNT_mPARTSUPP3_mSUPPLIER1_entry& y) {
      return x.COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY == y.COUNT_mPARTSUPP3_mSUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mPARTSUPP3_mSUPPLIER1_entry,long,
    HashIndex<COUNT_mPARTSUPP3_mSUPPLIER1_entry,long,COUNT_mPARTSUPP3_mSUPPLIER1_mapkey01_idxfn,true>,
    HashIndex<COUNT_mPARTSUPP3_mSUPPLIER1_entry,long,COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn,false>
  > COUNT_mPARTSUPP3_mSUPPLIER1_map;
  typedef HashIndex<COUNT_mPARTSUPP3_mSUPPLIER1_entry,long,COUNT_mPARTSUPP3_mSUPPLIER1_mapkey01_idxfn,true> HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_01;
  typedef HashIndex<COUNT_mPARTSUPP3_mSUPPLIER1_entry,long,COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn,false> HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0;
  
  struct COUNT_mPARTSUPP5_L2_3_entry {
    long COUNT_mPARTSUPPPARTSUPP_SUPPKEY; long __av; 
    explicit COUNT_mPARTSUPP5_L2_3_entry() { /*COUNT_mPARTSUPPPARTSUPP_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNT_mPARTSUPP5_L2_3_entry(const long c0, const long c1) { COUNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; __av = c1; }
    COUNT_mPARTSUPP5_L2_3_entry(const COUNT_mPARTSUPP5_L2_3_entry& other) : COUNT_mPARTSUPPPARTSUPP_SUPPKEY( other.COUNT_mPARTSUPPPARTSUPP_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mPARTSUPP5_L2_3_entry& modify(const long c0) { COUNT_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mPARTSUPPPARTSUPP_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mPARTSUPP5_L2_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPARTSUPP5_L2_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPARTSUPP5_L2_3_entry& x, const COUNT_mPARTSUPP5_L2_3_entry& y) {
      return x.COUNT_mPARTSUPPPARTSUPP_SUPPKEY == y.COUNT_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mPARTSUPP5_L2_3_entry,long,
    HashIndex<COUNT_mPARTSUPP5_L2_3_entry,long,COUNT_mPARTSUPP5_L2_3_mapkey0_idxfn,true>
  > COUNT_mPARTSUPP5_L2_3_map;
  typedef HashIndex<COUNT_mPARTSUPP5_L2_3_entry,long,COUNT_mPARTSUPP5_L2_3_mapkey0_idxfn,true> HashIndex_COUNT_mPARTSUPP5_L2_3_map_0;
  
  struct COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry {
    long COUNT_mPARTSUPP5_L2_3_mSUPPLIERSUPPLIER_NATIONKEY; long __av; 
    explicit COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry() { /*COUNT_mPARTSUPP5_L2_3_mSUPPLIERSUPPLIER_NATIONKEY = 0L; __av = 0L; */ }
    explicit COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry(const long c0, const long c1) { COUNT_mPARTSUPP5_L2_3_mSUPPLIERSUPPLIER_NATIONKEY = c0; __av = c1; }
    COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry(const COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry& other) : COUNT_mPARTSUPP5_L2_3_mSUPPLIERSUPPLIER_NATIONKEY( other.COUNT_mPARTSUPP5_L2_3_mSUPPLIERSUPPLIER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry& modify(const long c0) { COUNT_mPARTSUPP5_L2_3_mSUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mPARTSUPP5_L2_3_mSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTSUPP5_L2_3_mSUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry& x, const COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry& y) {
      return x.COUNT_mPARTSUPP5_L2_3_mSUPPLIERSUPPLIER_NATIONKEY == y.COUNT_mPARTSUPP5_L2_3_mSUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry,long,
    HashIndex<COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry,long,COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_mapkey0_idxfn,true>
  > COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_map;
  typedef HashIndex<COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry,long,COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_mapkey0_idxfn,true> HashIndex_COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_map_0;
  
  struct COUNT_mSUPPLIER1_entry {
    long P_PARTKEY; STRING_TYPE P_MFGR; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; DOUBLE_TYPE S_ACCTBAL; STRING_TYPE S_COMMENT; DOUBLE_TYPE PS_SUPPLYCOST; STRING_TYPE N_NAME; long __av; 
    explicit COUNT_mSUPPLIER1_entry() { /*P_PARTKEY = 0L; P_MFGR = ""; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; S_ACCTBAL = 0.0; S_COMMENT = ""; PS_SUPPLYCOST = 0.0; N_NAME = ""; __av = 0L; */ }
    explicit COUNT_mSUPPLIER1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8, const long c9) { P_PARTKEY = c0; P_MFGR = c1; S_NAME = c2; S_ADDRESS = c3; S_PHONE = c4; S_ACCTBAL = c5; S_COMMENT = c6; PS_SUPPLYCOST = c7; N_NAME = c8; __av = c9; }
    COUNT_mSUPPLIER1_entry(const COUNT_mSUPPLIER1_entry& other) : P_PARTKEY( other.P_PARTKEY ), P_MFGR( other.P_MFGR ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), S_ACCTBAL( other.S_ACCTBAL ), S_COMMENT( other.S_COMMENT ), PS_SUPPLYCOST( other.PS_SUPPLYCOST ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mSUPPLIER1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8) { P_PARTKEY = c0; P_MFGR = c1; S_NAME = c2; S_ADDRESS = c3; S_PHONE = c4; S_ACCTBAL = c5; S_COMMENT = c6; PS_SUPPLYCOST = c7; N_NAME = c8;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_MFGR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mSUPPLIER1_mapkey012345678_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.P_MFGR);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.S_ACCTBAL);
      hash_combine(h, e.S_COMMENT);
      hash_combine(h, e.PS_SUPPLYCOST);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mSUPPLIER1_entry& x, const COUNT_mSUPPLIER1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.P_MFGR == y.P_MFGR && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE && x.S_ACCTBAL == y.S_ACCTBAL && x.S_COMMENT == y.S_COMMENT && x.PS_SUPPLYCOST == y.PS_SUPPLYCOST && x.N_NAME == y.N_NAME;
    }
  };
  
  typedef MultiHashMap<COUNT_mSUPPLIER1_entry,long,
    HashIndex<COUNT_mSUPPLIER1_entry,long,COUNT_mSUPPLIER1_mapkey012345678_idxfn,true>
  > COUNT_mSUPPLIER1_map;
  typedef HashIndex<COUNT_mSUPPLIER1_entry,long,COUNT_mSUPPLIER1_mapkey012345678_idxfn,true> HashIndex_COUNT_mSUPPLIER1_map_012345678;
  
  struct COUNT_mSUPPLIER1_mSUPPLIER2_entry {
    long P_PARTKEY; long COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE PS_SUPPLYCOST; STRING_TYPE P_MFGR; long __av; 
    explicit COUNT_mSUPPLIER1_mSUPPLIER2_entry() { /*P_PARTKEY = 0L; COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; PS_SUPPLYCOST = 0.0; P_MFGR = ""; __av = 0L; */ }
    explicit COUNT_mSUPPLIER1_mSUPPLIER2_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3, const long c4) { P_PARTKEY = c0; COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY = c1; PS_SUPPLYCOST = c2; P_MFGR = c3; __av = c4; }
    COUNT_mSUPPLIER1_mSUPPLIER2_entry(const COUNT_mSUPPLIER1_mSUPPLIER2_entry& other) : P_PARTKEY( other.P_PARTKEY ), COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY( other.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY ), PS_SUPPLYCOST( other.PS_SUPPLYCOST ), P_MFGR( other.P_MFGR ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mSUPPLIER1_mSUPPLIER2_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3) { P_PARTKEY = c0; COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY = c1; PS_SUPPLYCOST = c2; P_MFGR = c3;  return *this; }
    FORCE_INLINE COUNT_mSUPPLIER1_mSUPPLIER2_entry& modify1(const long c1) { COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_MFGR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mSUPPLIER1_mSUPPLIER2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mSUPPLIER1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.PS_SUPPLYCOST);
      hash_combine(h, e.P_MFGR);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mSUPPLIER1_mSUPPLIER2_entry& x, const COUNT_mSUPPLIER1_mSUPPLIER2_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY == y.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY && x.PS_SUPPLYCOST == y.PS_SUPPLYCOST && x.P_MFGR == y.P_MFGR;
    }
  };
  
  struct COUNT_mSUPPLIER1_mSUPPLIER2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mSUPPLIER1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mSUPPLIER1_mSUPPLIER2_entry& x, const COUNT_mSUPPLIER1_mSUPPLIER2_entry& y) {
      return x.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY == y.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mSUPPLIER1_mSUPPLIER2_entry,long,
    HashIndex<COUNT_mSUPPLIER1_mSUPPLIER2_entry,long,COUNT_mSUPPLIER1_mSUPPLIER2_mapkey0123_idxfn,true>,
    HashIndex<COUNT_mSUPPLIER1_mSUPPLIER2_entry,long,COUNT_mSUPPLIER1_mSUPPLIER2_mapkey1_idxfn,false>
  > COUNT_mSUPPLIER1_mSUPPLIER2_map;
  typedef HashIndex<COUNT_mSUPPLIER1_mSUPPLIER2_entry,long,COUNT_mSUPPLIER1_mSUPPLIER2_mapkey0123_idxfn,true> HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_map_0123;
  typedef HashIndex<COUNT_mSUPPLIER1_mSUPPLIER2_entry,long,COUNT_mSUPPLIER1_mSUPPLIER2_mapkey1_idxfn,false> HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_map_1;
  
  struct COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry {
    long COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY; long COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE PS_SUPPLYCOST; long __av; 
    explicit COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry() { /*COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY = 0L; COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; PS_SUPPLYCOST = 0.0; __av = 0L; */ }
    explicit COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const long c3) { COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY = c0; COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY = c1; PS_SUPPLYCOST = c2; __av = c3; }
    COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry(const COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& other) : COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY( other.COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY ), COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY( other.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY ), PS_SUPPLYCOST( other.PS_SUPPLYCOST ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2) { COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY = c0; COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY = c1; PS_SUPPLYCOST = c2;  return *this; }
    FORCE_INLINE COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& modify0(const long c0) { COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& modify1(const long c1) { COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY);
      hash_combine(h, e.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.PS_SUPPLYCOST);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& x, const COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& y) {
      return x.COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY == y.COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY && x.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY == y.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY && x.PS_SUPPLYCOST == y.PS_SUPPLYCOST;
    }
  };
  
  struct COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& x, const COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& y) {
      return x.COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY == y.COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY;
    }
  };
  
  struct COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& x, const COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry& y) {
      return x.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY == y.COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry,long,
    HashIndex<COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry,long,COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey012_idxfn,true>,
    HashIndex<COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry,long,COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey0_idxfn,false>,
    HashIndex<COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry,long,COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey1_idxfn,false>
  > COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map;
  typedef HashIndex<COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry,long,COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey012_idxfn,true> HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_012;
  typedef HashIndex<COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry,long,COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey0_idxfn,false> HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_0;
  typedef HashIndex<COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry,long,COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey1_idxfn,false> HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1;
  
  struct COUNT_mPART3_entry {
    long COUNT_mPARTPART_PARTKEY; DOUBLE_TYPE PS_SUPPLYCOST; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; DOUBLE_TYPE S_ACCTBAL; STRING_TYPE S_COMMENT; STRING_TYPE N_NAME; long __av; 
    explicit COUNT_mPART3_entry() { /*COUNT_mPARTPART_PARTKEY = 0L; PS_SUPPLYCOST = 0.0; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; S_ACCTBAL = 0.0; S_COMMENT = ""; N_NAME = ""; __av = 0L; */ }
    explicit COUNT_mPART3_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const STRING_TYPE& c7, const long c8) { COUNT_mPARTPART_PARTKEY = c0; PS_SUPPLYCOST = c1; S_NAME = c2; S_ADDRESS = c3; S_PHONE = c4; S_ACCTBAL = c5; S_COMMENT = c6; N_NAME = c7; __av = c8; }
    COUNT_mPART3_entry(const COUNT_mPART3_entry& other) : COUNT_mPARTPART_PARTKEY( other.COUNT_mPARTPART_PARTKEY ), PS_SUPPLYCOST( other.PS_SUPPLYCOST ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), S_ACCTBAL( other.S_ACCTBAL ), S_COMMENT( other.S_COMMENT ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mPART3_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const STRING_TYPE& c7) { COUNT_mPARTPART_PARTKEY = c0; PS_SUPPLYCOST = c1; S_NAME = c2; S_ADDRESS = c3; S_PHONE = c4; S_ACCTBAL = c5; S_COMMENT = c6; N_NAME = c7;  return *this; }
    FORCE_INLINE COUNT_mPART3_entry& modify0(const long c0) { COUNT_mPARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mPART3_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPART3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTPART_PARTKEY);
      hash_combine(h, e.PS_SUPPLYCOST);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.S_ACCTBAL);
      hash_combine(h, e.S_COMMENT);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPART3_entry& x, const COUNT_mPART3_entry& y) {
      return x.COUNT_mPARTPART_PARTKEY == y.COUNT_mPARTPART_PARTKEY && x.PS_SUPPLYCOST == y.PS_SUPPLYCOST && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE && x.S_ACCTBAL == y.S_ACCTBAL && x.S_COMMENT == y.S_COMMENT && x.N_NAME == y.N_NAME;
    }
  };
  
  struct COUNT_mPART3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPART3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPART3_entry& x, const COUNT_mPART3_entry& y) {
      return x.COUNT_mPARTPART_PARTKEY == y.COUNT_mPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mPART3_entry,long,
    HashIndex<COUNT_mPART3_entry,long,COUNT_mPART3_mapkey01234567_idxfn,true>,
    HashIndex<COUNT_mPART3_entry,long,COUNT_mPART3_mapkey0_idxfn,false>
  > COUNT_mPART3_map;
  typedef HashIndex<COUNT_mPART3_entry,long,COUNT_mPART3_mapkey01234567_idxfn,true> HashIndex_COUNT_mPART3_map_01234567;
  typedef HashIndex<COUNT_mPART3_entry,long,COUNT_mPART3_mapkey0_idxfn,false> HashIndex_COUNT_mPART3_map_0;
  
  struct COUNT_mPART3_L2_1_entry {
    long COUNT_mPARTPART_PARTKEY; DOUBLE_TYPE PS2_SUPPLYCOST; long __av; 
    explicit COUNT_mPART3_L2_1_entry() { /*COUNT_mPARTPART_PARTKEY = 0L; PS2_SUPPLYCOST = 0.0; __av = 0L; */ }
    explicit COUNT_mPART3_L2_1_entry(const long c0, const DOUBLE_TYPE c1, const long c2) { COUNT_mPARTPART_PARTKEY = c0; PS2_SUPPLYCOST = c1; __av = c2; }
    COUNT_mPART3_L2_1_entry(const COUNT_mPART3_L2_1_entry& other) : COUNT_mPARTPART_PARTKEY( other.COUNT_mPARTPART_PARTKEY ), PS2_SUPPLYCOST( other.PS2_SUPPLYCOST ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mPART3_L2_1_entry& modify(const long c0, const DOUBLE_TYPE c1) { COUNT_mPARTPART_PARTKEY = c0; PS2_SUPPLYCOST = c1;  return *this; }
    FORCE_INLINE COUNT_mPART3_L2_1_entry& modify0(const long c0) { COUNT_mPARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS2_SUPPLYCOST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mPART3_L2_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPART3_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTPART_PARTKEY);
      hash_combine(h, e.PS2_SUPPLYCOST);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPART3_L2_1_entry& x, const COUNT_mPART3_L2_1_entry& y) {
      return x.COUNT_mPARTPART_PARTKEY == y.COUNT_mPARTPART_PARTKEY && x.PS2_SUPPLYCOST == y.PS2_SUPPLYCOST;
    }
  };
  
  struct COUNT_mPART3_L2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPART3_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPART3_L2_1_entry& x, const COUNT_mPART3_L2_1_entry& y) {
      return x.COUNT_mPARTPART_PARTKEY == y.COUNT_mPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mPART3_L2_1_entry,long,
    HashIndex<COUNT_mPART3_L2_1_entry,long,COUNT_mPART3_L2_1_mapkey01_idxfn,true>,
    HashIndex<COUNT_mPART3_L2_1_entry,long,COUNT_mPART3_L2_1_mapkey0_idxfn,false>
  > COUNT_mPART3_L2_1_map;
  typedef HashIndex<COUNT_mPART3_L2_1_entry,long,COUNT_mPART3_L2_1_mapkey01_idxfn,true> HashIndex_COUNT_mPART3_L2_1_map_01;
  typedef HashIndex<COUNT_mPART3_L2_1_entry,long,COUNT_mPART3_L2_1_mapkey0_idxfn,false> HashIndex_COUNT_mPART3_L2_1_map_0;
  
  struct tuple7_SSSDSS_L {
    STRING_TYPE _1; STRING_TYPE _2; STRING_TYPE _3; DOUBLE_TYPE _4; STRING_TYPE _5; STRING_TYPE _6; long __av;
    explicit tuple7_SSSDSS_L() { }
    explicit tuple7_SSSDSS_L(const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; _5 = c5; _6 = c6; __av = c__av;}
    int operator==(const tuple7_SSSDSS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4) && (this->_5==rhs._5) && (this->_6==rhs._6)); }
    FORCE_INLINE tuple7_SSSDSS_L& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const STRING_TYPE& c5, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; _5 = c4; _6 = c5; __av = c__av; return *this; }
    static bool equals(const tuple7_SSSDSS_L &x, const tuple7_SSSDSS_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4) && (x._5==y._5) && (x._6==y._6)); }
    static long hash(const tuple7_SSSDSS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
      hash_combine(h, e._5);
      hash_combine(h, e._6);
      return h;
    }
  };
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const COUNT_map& _COUNT = get_COUNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(COUNT), _COUNT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const COUNT_map& get_COUNT() const {
      return COUNT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    COUNT_map COUNT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), _c1(16U), _c2(16U), agg1(16U), agg3(16U) {
      c1 = STRING_TYPE("EUROPE");
      /* regex_t init */
      if(regcomp(&preg1, "^.*BRASS$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^.*BRASS$/" << endl;
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
    
    void on_insert_REGION(const long region_regionkey, const STRING_TYPE region_name, const STRING_TYPE region_comment) {
      REGION_entry e(region_regionkey, region_name, region_comment, 1L);
      REGION.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    void on_insert_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  //++tN;
        agg1.clear();
        
        long l1 = 0L;
        { //slice 
          const HashIndex_COUNT_mPART3_map_0* i1 = static_cast<HashIndex_COUNT_mPART3_map_0*>(COUNT_mPART3.index[1]);
          const HASH_RES_t h2 = COUNT_mPART3_mapkey0_idxfn::hash(se3.modify0(part_partkey));
          HashIndex_COUNT_mPART3_map_0::IdxNode* n1 = static_cast<HashIndex_COUNT_mPART3_map_0::IdxNode*>(i1->slice(se3, h2));
          COUNT_mPART3_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              DOUBLE_TYPE ps_supplycost = e1->PS_SUPPLYCOST;
              STRING_TYPE s_name = e1->S_NAME;
              STRING_TYPE s_address = e1->S_ADDRESS;
              STRING_TYPE s_phone = e1->S_PHONE;
              DOUBLE_TYPE s_acctbal = e1->S_ACCTBAL;
              STRING_TYPE s_comment = e1->S_COMMENT;
              STRING_TYPE n_name = e1->N_NAME;
              long v1 = e1->__av;
              long agg2 = 0L;
              { //slice 
                const HashIndex_COUNT_mPART3_L2_1_map_0* i2 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0*>(COUNT_mPART3_L2_1.index[1]);
                const HASH_RES_t h1 = COUNT_mPART3_L2_1_mapkey0_idxfn::hash(se2.modify0(part_partkey));
                HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode* n2 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode*>(i2->slice(se2, h1));
                COUNT_mPART3_L2_1_entry* e2;
               
                if (n2 && (e2 = n2->obj)) {
                  do {                
                    DOUBLE_TYPE ps2_supplycost = e2->PS2_SUPPLYCOST;
                    long v2 = e2->__av;
                    (/*if */(ps_supplycost > ps2_supplycost) ? agg2 += v2 : 0L);
                    n2 = n2->nxt;
                  } while (n2 && (e2 = n2->obj) && h1 == n2->hash &&  COUNT_mPART3_L2_1_mapkey0_idxfn::equals(se2, *e2)); 
                }
              }(/*if */(l1 == agg2) ? agg1.addOrDelOnZero(st1.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,v1), v1) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h2 == n1->hash &&  COUNT_mPART3_mapkey0_idxfn::equals(se3, *e1)); 
          }
        }{  // temp foreach
          const HashIndex<tuple7_SSSDSS_L, long>* i3 = static_cast<HashIndex<tuple7_SSSDSS_L, long>*>(agg1.index[0]);
          HashIndex<tuple7_SSSDSS_L, long>::IdxNode* n3; 
          tuple7_SSSDSS_L* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
              STRING_TYPE s_name = e3->_1;
              STRING_TYPE s_address = e3->_2;
              STRING_TYPE s_phone = e3->_3;
              DOUBLE_TYPE s_acctbal = e3->_4;
              STRING_TYPE s_comment = e3->_5;
              STRING_TYPE n_name = e3->_6;  
              long v3 = e3->__av; 
            (/*if */(0L != Upreg_match(preg1,part_type) && part_size == 15L) ? COUNT.addOrDelOnZero(se1.modify(s_acctbal,s_name,n_name,part_partkey,part_mfgr,s_address,s_phone,s_comment),v3) : (void)0);      
              n3 = n3->nxt;
            }
          }
        }(/*if */(0L != Upreg_match(preg1,part_type) && part_size == 15L) ? COUNT_mPARTSUPP2.addOrDelOnZero(se4.modify(part_partkey,part_mfgr),1L) : (void)0);
        { //slice 
          const HashIndex_COUNT_mPART3_map_0* i4 = static_cast<HashIndex_COUNT_mPART3_map_0*>(COUNT_mPART3.index[1]);
          const HASH_RES_t h3 = COUNT_mPART3_mapkey0_idxfn::hash(se6.modify0(part_partkey));
          HashIndex_COUNT_mPART3_map_0::IdxNode* n4 = static_cast<HashIndex_COUNT_mPART3_map_0::IdxNode*>(i4->slice(se6, h3));
          COUNT_mPART3_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              DOUBLE_TYPE ps_supplycost = e4->PS_SUPPLYCOST;
              STRING_TYPE s_name = e4->S_NAME;
              STRING_TYPE s_address = e4->S_ADDRESS;
              STRING_TYPE s_phone = e4->S_PHONE;
              DOUBLE_TYPE s_acctbal = e4->S_ACCTBAL;
              STRING_TYPE s_comment = e4->S_COMMENT;
              STRING_TYPE n_name = e4->N_NAME;
              long v4 = e4->__av;
              (/*if */(0L != Upreg_match(preg1,part_type) && part_size == 15L) ? COUNT_mSUPPLIER1.addOrDelOnZero(se5.modify(part_partkey,part_mfgr,s_name,s_address,s_phone,s_acctbal,s_comment,ps_supplycost,n_name),v4) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h3 == n4->hash &&  COUNT_mPART3_mapkey0_idxfn::equals(se6, *e4)); 
          }
        }{ //slice 
          const HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_0* i5 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_0*>(COUNT_mSUPPLIER1_mSUPPLIER2_mPART3.index[1]);
          const HASH_RES_t h4 = COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey0_idxfn::hash(se8.modify0(part_partkey));
          HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_0::IdxNode* n5 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_0::IdxNode*>(i5->slice(se8, h4));
          COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long count_msupplier1_msuppliersupplier_suppkey = e5->COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE ps_supplycost = e5->PS_SUPPLYCOST;
              long v5 = e5->__av;
              (/*if */(0L != Upreg_match(preg1,part_type) && part_size == 15L) ? COUNT_mSUPPLIER1_mSUPPLIER2.addOrDelOnZero(se7.modify(part_partkey,count_msupplier1_msuppliersupplier_suppkey,ps_supplycost,part_mfgr),v5) : (void)0);
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h4 == n5->hash &&  COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey0_idxfn::equals(se8, *e5)); 
          }
        }
      }
    }
    void on_delete_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  //++tN;
        agg3.clear();
        
        long l2 = 0L;
        { //slice 
          const HashIndex_COUNT_mPART3_map_0* i6 = static_cast<HashIndex_COUNT_mPART3_map_0*>(COUNT_mPART3.index[1]);
          const HASH_RES_t h6 = COUNT_mPART3_mapkey0_idxfn::hash(se11.modify0(part_partkey));
          HashIndex_COUNT_mPART3_map_0::IdxNode* n6 = static_cast<HashIndex_COUNT_mPART3_map_0::IdxNode*>(i6->slice(se11, h6));
          COUNT_mPART3_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              DOUBLE_TYPE ps_supplycost = e6->PS_SUPPLYCOST;
              STRING_TYPE s_name = e6->S_NAME;
              STRING_TYPE s_address = e6->S_ADDRESS;
              STRING_TYPE s_phone = e6->S_PHONE;
              DOUBLE_TYPE s_acctbal = e6->S_ACCTBAL;
              STRING_TYPE s_comment = e6->S_COMMENT;
              STRING_TYPE n_name = e6->N_NAME;
              long v6 = e6->__av;
              long agg4 = 0L;
              { //slice 
                const HashIndex_COUNT_mPART3_L2_1_map_0* i7 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0*>(COUNT_mPART3_L2_1.index[1]);
                const HASH_RES_t h5 = COUNT_mPART3_L2_1_mapkey0_idxfn::hash(se10.modify0(part_partkey));
                HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode* n7 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode*>(i7->slice(se10, h5));
                COUNT_mPART3_L2_1_entry* e7;
               
                if (n7 && (e7 = n7->obj)) {
                  do {                
                    DOUBLE_TYPE ps2_supplycost = e7->PS2_SUPPLYCOST;
                    long v7 = e7->__av;
                    (/*if */(ps_supplycost > ps2_supplycost) ? agg4 += v7 : 0L);
                    n7 = n7->nxt;
                  } while (n7 && (e7 = n7->obj) && h5 == n7->hash &&  COUNT_mPART3_L2_1_mapkey0_idxfn::equals(se10, *e7)); 
                }
              }(/*if */(l2 == agg4) ? agg3.addOrDelOnZero(st2.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,v6), v6) : (void)0);
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h6 == n6->hash &&  COUNT_mPART3_mapkey0_idxfn::equals(se11, *e6)); 
          }
        }{  // temp foreach
          const HashIndex<tuple7_SSSDSS_L, long>* i8 = static_cast<HashIndex<tuple7_SSSDSS_L, long>*>(agg3.index[0]);
          HashIndex<tuple7_SSSDSS_L, long>::IdxNode* n8; 
          tuple7_SSSDSS_L* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
              STRING_TYPE s_name = e8->_1;
              STRING_TYPE s_address = e8->_2;
              STRING_TYPE s_phone = e8->_3;
              DOUBLE_TYPE s_acctbal = e8->_4;
              STRING_TYPE s_comment = e8->_5;
              STRING_TYPE n_name = e8->_6;  
              long v8 = e8->__av; 
            (/*if */(0L != Upreg_match(preg1,part_type) && part_size == 15L) ? COUNT.addOrDelOnZero(se9.modify(s_acctbal,s_name,n_name,part_partkey,part_mfgr,s_address,s_phone,s_comment),(v8 * -1L)) : (void)0);      
              n8 = n8->nxt;
            }
          }
        }(/*if */(0L != Upreg_match(preg1,part_type) && part_size == 15L) ? COUNT_mPARTSUPP2.addOrDelOnZero(se12.modify(part_partkey,part_mfgr),-1L) : (void)0);
        { //slice 
          const HashIndex_COUNT_mPART3_map_0* i9 = static_cast<HashIndex_COUNT_mPART3_map_0*>(COUNT_mPART3.index[1]);
          const HASH_RES_t h7 = COUNT_mPART3_mapkey0_idxfn::hash(se14.modify0(part_partkey));
          HashIndex_COUNT_mPART3_map_0::IdxNode* n9 = static_cast<HashIndex_COUNT_mPART3_map_0::IdxNode*>(i9->slice(se14, h7));
          COUNT_mPART3_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              DOUBLE_TYPE ps_supplycost = e9->PS_SUPPLYCOST;
              STRING_TYPE s_name = e9->S_NAME;
              STRING_TYPE s_address = e9->S_ADDRESS;
              STRING_TYPE s_phone = e9->S_PHONE;
              DOUBLE_TYPE s_acctbal = e9->S_ACCTBAL;
              STRING_TYPE s_comment = e9->S_COMMENT;
              STRING_TYPE n_name = e9->N_NAME;
              long v9 = e9->__av;
              (/*if */(0L != Upreg_match(preg1,part_type) && part_size == 15L) ? COUNT_mSUPPLIER1.addOrDelOnZero(se13.modify(part_partkey,part_mfgr,s_name,s_address,s_phone,s_acctbal,s_comment,ps_supplycost,n_name),(v9 * -1L)) : (void)0);
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h7 == n9->hash &&  COUNT_mPART3_mapkey0_idxfn::equals(se14, *e9)); 
          }
        }{ //slice 
          const HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_0* i10 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_0*>(COUNT_mSUPPLIER1_mSUPPLIER2_mPART3.index[1]);
          const HASH_RES_t h8 = COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey0_idxfn::hash(se16.modify0(part_partkey));
          HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_0::IdxNode* n10 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_0::IdxNode*>(i10->slice(se16, h8));
          COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              long count_msupplier1_msuppliersupplier_suppkey = e10->COUNT_mSUPPLIER1_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE ps_supplycost = e10->PS_SUPPLYCOST;
              long v10 = e10->__av;
              (/*if */(0L != Upreg_match(preg1,part_type) && part_size == 15L) ? COUNT_mSUPPLIER1_mSUPPLIER2.addOrDelOnZero(se15.modify(part_partkey,count_msupplier1_msuppliersupplier_suppkey,ps_supplycost,part_mfgr),(v10 * -1L)) : (void)0);
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h8 == n10->hash &&  COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey0_idxfn::equals(se16, *e10)); 
          }
        }
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0* i11 = static_cast<HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0*>(COUNT_mPARTSUPP3_mSUPPLIER1.index[1]);
          const HASH_RES_t h9 = COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn::hash(se18.modify0(supplier_nationkey));
          HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0::IdxNode* n11 = static_cast<HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0::IdxNode*>(i11->slice(se18, h9));
          COUNT_mPARTSUPP3_mSUPPLIER1_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              STRING_TYPE n_name = e11->N_NAME;
              long v11 = e11->__av;
              COUNT_mPARTSUPP3.addOrDelOnZero(se17.modify(supplier_suppkey,supplier_name,supplier_address,supplier_phone,supplier_acctbal,supplier_comment,n_name),v11);
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h9 == n11->hash &&  COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn::equals(se18, *e11)); 
          }
        }COUNT_mPARTSUPP5_L2_3.addOrDelOnZero(se19.modify(supplier_suppkey),COUNT_mPARTSUPP5_L2_3_mSUPPLIER1.getValueOrDefault(se20.modify(supplier_nationkey)));
        { //slice 
          const HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0* i12 = static_cast<HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0*>(COUNT_mPARTSUPP3_mSUPPLIER1.index[1]);
          const HASH_RES_t h11 = COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn::hash(se23.modify0(supplier_nationkey));
          HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0::IdxNode* n12 = static_cast<HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0::IdxNode*>(i12->slice(se23, h11));
          COUNT_mPARTSUPP3_mSUPPLIER1_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              STRING_TYPE n_name = e12->N_NAME;
              long v12 = e12->__av;
              { //slice 
                const HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_map_1* i13 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_map_1*>(COUNT_mSUPPLIER1_mSUPPLIER2.index[1]);
                const HASH_RES_t h10 = COUNT_mSUPPLIER1_mSUPPLIER2_mapkey1_idxfn::hash(se22.modify1(supplier_suppkey));
                HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_map_1::IdxNode* n13 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_map_1::IdxNode*>(i13->slice(se22, h10));
                COUNT_mSUPPLIER1_mSUPPLIER2_entry* e13;
               
                if (n13 && (e13 = n13->obj)) {
                  do {                
                    long p_partkey = e13->P_PARTKEY;
                    DOUBLE_TYPE ps_supplycost = e13->PS_SUPPLYCOST;
                    STRING_TYPE p_mfgr = e13->P_MFGR;
                    long v13 = e13->__av;
                    COUNT_mSUPPLIER1.addOrDelOnZero(se21.modify(p_partkey,p_mfgr,supplier_name,supplier_address,supplier_phone,supplier_acctbal,supplier_comment,ps_supplycost,n_name),(v12 * v13));
                    n13 = n13->nxt;
                  } while (n13 && (e13 = n13->obj) && h10 == n13->hash &&  COUNT_mSUPPLIER1_mSUPPLIER2_mapkey1_idxfn::equals(se22, *e13)); 
                }
              }
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h11 == n12->hash &&  COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn::equals(se23, *e12)); 
          }
        }{ //slice 
          const HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0* i14 = static_cast<HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0*>(COUNT_mPARTSUPP3_mSUPPLIER1.index[1]);
          const HASH_RES_t h13 = COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn::hash(se26.modify0(supplier_nationkey));
          HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0::IdxNode* n14 = static_cast<HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0::IdxNode*>(i14->slice(se26, h13));
          COUNT_mPARTSUPP3_mSUPPLIER1_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              STRING_TYPE n_name = e14->N_NAME;
              long v14 = e14->__av;
              { //slice 
                const HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1* i15 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1*>(COUNT_mSUPPLIER1_mSUPPLIER2_mPART3.index[2]);
                const HASH_RES_t h12 = COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey1_idxfn::hash(se25.modify1(supplier_suppkey));
                HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1::IdxNode* n15 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1::IdxNode*>(i15->slice(se25, h12));
                COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry* e15;
               
                if (n15 && (e15 = n15->obj)) {
                  do {                
                    long count_mpartpart_partkey = e15->COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY;
                    DOUBLE_TYPE ps_supplycost = e15->PS_SUPPLYCOST;
                    long v15 = e15->__av;
                    COUNT_mPART3.addOrDelOnZero(se24.modify(count_mpartpart_partkey,ps_supplycost,supplier_name,supplier_address,supplier_phone,supplier_acctbal,supplier_comment,n_name),(v14 * v15));
                    n15 = n15->nxt;
                  } while (n15 && (e15 = n15->obj) && h12 == n15->hash &&  COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey1_idxfn::equals(se25, *e15)); 
                }
              }
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h13 == n14->hash &&  COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn::equals(se26, *e14)); 
          }
        }{ //slice 
          const HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1* i16 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1*>(COUNT_mSUPPLIER1_mSUPPLIER2_mPART3.index[2]);
          const HASH_RES_t h14 = COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey1_idxfn::hash(se29.modify1(supplier_suppkey));
          HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1::IdxNode* n16 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1::IdxNode*>(i16->slice(se29, h14));
          COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry* e16;
         
          if (n16 && (e16 = n16->obj)) {
            do {                
              long count_mpartpart_partkey = e16->COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY;
              DOUBLE_TYPE ps2_supplycost = e16->PS_SUPPLYCOST;
              long v16 = e16->__av;
              COUNT_mPART3_L2_1.addOrDelOnZero(se27.modify(count_mpartpart_partkey,ps2_supplycost),(COUNT_mPARTSUPP5_L2_3_mSUPPLIER1.getValueOrDefault(se28.modify(supplier_nationkey)) * v16));
              n16 = n16->nxt;
            } while (n16 && (e16 = n16->obj) && h14 == n16->hash &&  COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey1_idxfn::equals(se29, *e16)); 
          }
        }COUNT.clear();
        long l3 = 0L;
        {  // foreach
          const HashIndex_COUNT_mSUPPLIER1_map_012345678* i17 = static_cast<HashIndex_COUNT_mSUPPLIER1_map_012345678*>(COUNT_mSUPPLIER1.index[0]);
          HashIndex_COUNT_mSUPPLIER1_map_012345678::IdxNode* n17; 
          COUNT_mSUPPLIER1_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long p_partkey = e17->P_PARTKEY;
                STRING_TYPE p_mfgr = e17->P_MFGR;
                STRING_TYPE s_name = e17->S_NAME;
                STRING_TYPE s_address = e17->S_ADDRESS;
                STRING_TYPE s_phone = e17->S_PHONE;
                DOUBLE_TYPE s_acctbal = e17->S_ACCTBAL;
                STRING_TYPE s_comment = e17->S_COMMENT;
                DOUBLE_TYPE ps_supplycost = e17->PS_SUPPLYCOST;
                STRING_TYPE n_name = e17->N_NAME;
                long v17 = e17->__av;
                long agg5 = 0L;
                { //slice 
                  const HashIndex_COUNT_mPART3_L2_1_map_0* i18 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0*>(COUNT_mPART3_L2_1.index[1]);
                  const HASH_RES_t h15 = COUNT_mPART3_L2_1_mapkey0_idxfn::hash(se31.modify0(p_partkey));
                  HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode* n18 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode*>(i18->slice(se31, h15));
                  COUNT_mPART3_L2_1_entry* e18;
                 
                  if (n18 && (e18 = n18->obj)) {
                    do {                
                      DOUBLE_TYPE ps2_supplycost = e18->PS2_SUPPLYCOST;
                      long v18 = e18->__av;
                      (/*if */(ps_supplycost > ps2_supplycost) ? agg5 += v18 : 0L);
                      n18 = n18->nxt;
                    } while (n18 && (e18 = n18->obj) && h15 == n18->hash &&  COUNT_mPART3_L2_1_mapkey0_idxfn::equals(se31, *e18)); 
                  }
                }(/*if */(l3 == agg5) ? COUNT.addOrDelOnZero(se30.modify(s_acctbal,s_name,n_name,p_partkey,p_mfgr,s_address,s_phone,s_comment),v17) : (void)0);
              n17 = n17->nxt;
            }
          }
        }
      }
    }
    void on_delete_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0* i19 = static_cast<HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0*>(COUNT_mPARTSUPP3_mSUPPLIER1.index[1]);
          const HASH_RES_t h16 = COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn::hash(se33.modify0(supplier_nationkey));
          HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0::IdxNode* n19 = static_cast<HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0::IdxNode*>(i19->slice(se33, h16));
          COUNT_mPARTSUPP3_mSUPPLIER1_entry* e19;
         
          if (n19 && (e19 = n19->obj)) {
            do {                
              STRING_TYPE n_name = e19->N_NAME;
              long v19 = e19->__av;
              COUNT_mPARTSUPP3.addOrDelOnZero(se32.modify(supplier_suppkey,supplier_name,supplier_address,supplier_phone,supplier_acctbal,supplier_comment,n_name),(v19 * -1L));
              n19 = n19->nxt;
            } while (n19 && (e19 = n19->obj) && h16 == n19->hash &&  COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn::equals(se33, *e19)); 
          }
        }COUNT_mPARTSUPP5_L2_3.addOrDelOnZero(se34.modify(supplier_suppkey),(COUNT_mPARTSUPP5_L2_3_mSUPPLIER1.getValueOrDefault(se35.modify(supplier_nationkey)) * -1L));
        { //slice 
          const HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0* i20 = static_cast<HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0*>(COUNT_mPARTSUPP3_mSUPPLIER1.index[1]);
          const HASH_RES_t h18 = COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn::hash(se38.modify0(supplier_nationkey));
          HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0::IdxNode* n20 = static_cast<HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0::IdxNode*>(i20->slice(se38, h18));
          COUNT_mPARTSUPP3_mSUPPLIER1_entry* e20;
         
          if (n20 && (e20 = n20->obj)) {
            do {                
              STRING_TYPE n_name = e20->N_NAME;
              long v20 = e20->__av;
              { //slice 
                const HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_map_1* i21 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_map_1*>(COUNT_mSUPPLIER1_mSUPPLIER2.index[1]);
                const HASH_RES_t h17 = COUNT_mSUPPLIER1_mSUPPLIER2_mapkey1_idxfn::hash(se37.modify1(supplier_suppkey));
                HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_map_1::IdxNode* n21 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_map_1::IdxNode*>(i21->slice(se37, h17));
                COUNT_mSUPPLIER1_mSUPPLIER2_entry* e21;
               
                if (n21 && (e21 = n21->obj)) {
                  do {                
                    long p_partkey = e21->P_PARTKEY;
                    DOUBLE_TYPE ps_supplycost = e21->PS_SUPPLYCOST;
                    STRING_TYPE p_mfgr = e21->P_MFGR;
                    long v21 = e21->__av;
                    COUNT_mSUPPLIER1.addOrDelOnZero(se36.modify(p_partkey,p_mfgr,supplier_name,supplier_address,supplier_phone,supplier_acctbal,supplier_comment,ps_supplycost,n_name),(v20 * (v21 * -1L)));
                    n21 = n21->nxt;
                  } while (n21 && (e21 = n21->obj) && h17 == n21->hash &&  COUNT_mSUPPLIER1_mSUPPLIER2_mapkey1_idxfn::equals(se37, *e21)); 
                }
              }
              n20 = n20->nxt;
            } while (n20 && (e20 = n20->obj) && h18 == n20->hash &&  COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn::equals(se38, *e20)); 
          }
        }{ //slice 
          const HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0* i22 = static_cast<HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0*>(COUNT_mPARTSUPP3_mSUPPLIER1.index[1]);
          const HASH_RES_t h20 = COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn::hash(se41.modify0(supplier_nationkey));
          HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0::IdxNode* n22 = static_cast<HashIndex_COUNT_mPARTSUPP3_mSUPPLIER1_map_0::IdxNode*>(i22->slice(se41, h20));
          COUNT_mPARTSUPP3_mSUPPLIER1_entry* e22;
         
          if (n22 && (e22 = n22->obj)) {
            do {                
              STRING_TYPE n_name = e22->N_NAME;
              long v22 = e22->__av;
              { //slice 
                const HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1* i23 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1*>(COUNT_mSUPPLIER1_mSUPPLIER2_mPART3.index[2]);
                const HASH_RES_t h19 = COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey1_idxfn::hash(se40.modify1(supplier_suppkey));
                HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1::IdxNode* n23 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1::IdxNode*>(i23->slice(se40, h19));
                COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry* e23;
               
                if (n23 && (e23 = n23->obj)) {
                  do {                
                    long count_mpartpart_partkey = e23->COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY;
                    DOUBLE_TYPE ps_supplycost = e23->PS_SUPPLYCOST;
                    long v23 = e23->__av;
                    COUNT_mPART3.addOrDelOnZero(se39.modify(count_mpartpart_partkey,ps_supplycost,supplier_name,supplier_address,supplier_phone,supplier_acctbal,supplier_comment,n_name),(v22 * (v23 * -1L)));
                    n23 = n23->nxt;
                  } while (n23 && (e23 = n23->obj) && h19 == n23->hash &&  COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey1_idxfn::equals(se40, *e23)); 
                }
              }
              n22 = n22->nxt;
            } while (n22 && (e22 = n22->obj) && h20 == n22->hash &&  COUNT_mPARTSUPP3_mSUPPLIER1_mapkey0_idxfn::equals(se41, *e22)); 
          }
        }{ //slice 
          const HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1* i24 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1*>(COUNT_mSUPPLIER1_mSUPPLIER2_mPART3.index[2]);
          const HASH_RES_t h21 = COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey1_idxfn::hash(se44.modify1(supplier_suppkey));
          HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1::IdxNode* n24 = static_cast<HashIndex_COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map_1::IdxNode*>(i24->slice(se44, h21));
          COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              long count_mpartpart_partkey = e24->COUNT_mSUPPLIER1_mSUPPLIER2_mPARTPART_PARTKEY;
              DOUBLE_TYPE ps2_supplycost = e24->PS_SUPPLYCOST;
              long v24 = e24->__av;
              COUNT_mPART3_L2_1.addOrDelOnZero(se42.modify(count_mpartpart_partkey,ps2_supplycost),(COUNT_mPARTSUPP5_L2_3_mSUPPLIER1.getValueOrDefault(se43.modify(supplier_nationkey)) * (v24 * -1L)));
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h21 == n24->hash &&  COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_mapkey1_idxfn::equals(se44, *e24)); 
          }
        }COUNT.clear();
        long l4 = 0L;
        {  // foreach
          const HashIndex_COUNT_mSUPPLIER1_map_012345678* i25 = static_cast<HashIndex_COUNT_mSUPPLIER1_map_012345678*>(COUNT_mSUPPLIER1.index[0]);
          HashIndex_COUNT_mSUPPLIER1_map_012345678::IdxNode* n25; 
          COUNT_mSUPPLIER1_entry* e25;
        
          for (size_t i = 0; i < i25->size_; i++)
          {
            n25 = i25->buckets_ + i;
            while (n25 && (e25 = n25->obj))
            {
                long p_partkey = e25->P_PARTKEY;
                STRING_TYPE p_mfgr = e25->P_MFGR;
                STRING_TYPE s_name = e25->S_NAME;
                STRING_TYPE s_address = e25->S_ADDRESS;
                STRING_TYPE s_phone = e25->S_PHONE;
                DOUBLE_TYPE s_acctbal = e25->S_ACCTBAL;
                STRING_TYPE s_comment = e25->S_COMMENT;
                DOUBLE_TYPE ps_supplycost = e25->PS_SUPPLYCOST;
                STRING_TYPE n_name = e25->N_NAME;
                long v25 = e25->__av;
                long agg6 = 0L;
                { //slice 
                  const HashIndex_COUNT_mPART3_L2_1_map_0* i26 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0*>(COUNT_mPART3_L2_1.index[1]);
                  const HASH_RES_t h22 = COUNT_mPART3_L2_1_mapkey0_idxfn::hash(se46.modify0(p_partkey));
                  HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode* n26 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode*>(i26->slice(se46, h22));
                  COUNT_mPART3_L2_1_entry* e26;
                 
                  if (n26 && (e26 = n26->obj)) {
                    do {                
                      DOUBLE_TYPE ps2_supplycost = e26->PS2_SUPPLYCOST;
                      long v26 = e26->__av;
                      (/*if */(ps_supplycost > ps2_supplycost) ? agg6 += v26 : 0L);
                      n26 = n26->nxt;
                    } while (n26 && (e26 = n26->obj) && h22 == n26->hash &&  COUNT_mPART3_L2_1_mapkey0_idxfn::equals(se46, *e26)); 
                  }
                }(/*if */(l4 == agg6) ? COUNT.addOrDelOnZero(se45.modify(s_acctbal,s_name,n_name,p_partkey,p_mfgr,s_address,s_phone,s_comment),v25) : (void)0);
              n25 = n25->nxt;
            }
          }
        }
      }
    }
    void on_insert_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  //++tN;
        _c1.clear();
        long l5 = 0L;
        { //slice 
          const HashIndex_COUNT_mPART3_map_0* i27 = static_cast<HashIndex_COUNT_mPART3_map_0*>(COUNT_mPART3.index[1]);
          const HASH_RES_t h24 = COUNT_mPART3_mapkey0_idxfn::hash(se50.modify0(partsupp_partkey));
          HashIndex_COUNT_mPART3_map_0::IdxNode* n27 = static_cast<HashIndex_COUNT_mPART3_map_0::IdxNode*>(i27->slice(se50, h24));
          COUNT_mPART3_entry* e27;
         
          if (n27 && (e27 = n27->obj)) {
            do {                
              DOUBLE_TYPE ps_supplycost = e27->PS_SUPPLYCOST;
              STRING_TYPE s_name = e27->S_NAME;
              STRING_TYPE s_address = e27->S_ADDRESS;
              STRING_TYPE s_phone = e27->S_PHONE;
              DOUBLE_TYPE s_acctbal = e27->S_ACCTBAL;
              STRING_TYPE s_comment = e27->S_COMMENT;
              STRING_TYPE n_name = e27->N_NAME;
              long v28 = e27->__av;
              long agg7 = 0L;
              { //slice 
                const HashIndex_COUNT_mPART3_L2_1_map_0* i28 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0*>(COUNT_mPART3_L2_1.index[1]);
                const HASH_RES_t h23 = COUNT_mPART3_L2_1_mapkey0_idxfn::hash(se48.modify0(partsupp_partkey));
                HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode* n28 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode*>(i28->slice(se48, h23));
                COUNT_mPART3_L2_1_entry* e28;
               
                if (n28 && (e28 = n28->obj)) {
                  do {                
                    DOUBLE_TYPE ps2_supplycost = e28->PS2_SUPPLYCOST;
                    long v29 = e28->__av;
                    (/*if */(ps_supplycost > ps2_supplycost) ? agg7 += v29 : 0L);
                    n28 = n28->nxt;
                  } while (n28 && (e28 = n28->obj) && h23 == n28->hash &&  COUNT_mPART3_L2_1_mapkey0_idxfn::equals(se48, *e28)); 
                }
              }(/*if */(l5 == (agg7 + (/*if */(ps_supplycost > partsupp_supplycost) ? COUNT_mPARTSUPP5_L2_3.getValueOrDefault(se49.modify(partsupp_suppkey)) : 0L))) ? _c1.addOrDelOnZero(st3.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,v28), v28) : (void)0);
              n27 = n27->nxt;
            } while (n27 && (e27 = n27->obj) && h24 == n27->hash &&  COUNT_mPART3_mapkey0_idxfn::equals(se50, *e27)); 
          }
        }long agg8 = 0L;
        long agg9 = 0L;
        { //slice 
          const HashIndex_COUNT_mPART3_L2_1_map_0* i29 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0*>(COUNT_mPART3_L2_1.index[1]);
          const HASH_RES_t h25 = COUNT_mPART3_L2_1_mapkey0_idxfn::hash(se51.modify0(partsupp_partkey));
          HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode* n29 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode*>(i29->slice(se51, h25));
          COUNT_mPART3_L2_1_entry* e29;
         
          if (n29 && (e29 = n29->obj)) {
            do {                
              DOUBLE_TYPE ps2_supplycost = e29->PS2_SUPPLYCOST;
              long v30 = e29->__av;
              (/*if */(partsupp_supplycost > ps2_supplycost) ? agg9 += v30 : 0L);
              n29 = n29->nxt;
            } while (n29 && (e29 = n29->obj) && h25 == n29->hash &&  COUNT_mPART3_L2_1_mapkey0_idxfn::equals(se51, *e29)); 
          }
        }long l6 = agg9;
        (/*if */(l6 == 0L) ? agg8 += 1L : 0L);
        { //slice 
          const HashIndex_COUNT_mPARTSUPP3_map_0* i30 = static_cast<HashIndex_COUNT_mPARTSUPP3_map_0*>(COUNT_mPARTSUPP3.index[1]);
          const HASH_RES_t h26 = COUNT_mPARTSUPP3_mapkey0_idxfn::hash(se52.modify0(partsupp_suppkey));
          HashIndex_COUNT_mPARTSUPP3_map_0::IdxNode* n30 = static_cast<HashIndex_COUNT_mPARTSUPP3_map_0::IdxNode*>(i30->slice(se52, h26));
          COUNT_mPARTSUPP3_entry* e30;
         
          if (n30 && (e30 = n30->obj)) {
            do {                
              STRING_TYPE s_name = e30->S_NAME;
              STRING_TYPE s_address = e30->S_ADDRESS;
              STRING_TYPE s_phone = e30->S_PHONE;
              DOUBLE_TYPE s_acctbal = e30->S_ACCTBAL;
              STRING_TYPE s_comment = e30->S_COMMENT;
              STRING_TYPE n_name = e30->N_NAME;
              long v31 = e30->__av;
              _c1.addOrDelOnZero(st4.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,(agg8 * v31)), (agg8 * v31));
              n30 = n30->nxt;
            } while (n30 && (e30 = n30->obj) && h26 == n30->hash &&  COUNT_mPARTSUPP3_mapkey0_idxfn::equals(se52, *e30)); 
          }
        }long l7 = 0L;
        { //slice 
          const HashIndex_COUNT_mPART3_map_0* i31 = static_cast<HashIndex_COUNT_mPART3_map_0*>(COUNT_mPART3.index[1]);
          const HASH_RES_t h28 = COUNT_mPART3_mapkey0_idxfn::hash(se54.modify0(partsupp_partkey));
          HashIndex_COUNT_mPART3_map_0::IdxNode* n31 = static_cast<HashIndex_COUNT_mPART3_map_0::IdxNode*>(i31->slice(se54, h28));
          COUNT_mPART3_entry* e31;
         
          if (n31 && (e31 = n31->obj)) {
            do {                
              DOUBLE_TYPE ps_supplycost = e31->PS_SUPPLYCOST;
              STRING_TYPE s_name = e31->S_NAME;
              STRING_TYPE s_address = e31->S_ADDRESS;
              STRING_TYPE s_phone = e31->S_PHONE;
              DOUBLE_TYPE s_acctbal = e31->S_ACCTBAL;
              STRING_TYPE s_comment = e31->S_COMMENT;
              STRING_TYPE n_name = e31->N_NAME;
              long v32 = e31->__av;
              long agg10 = 0L;
              { //slice 
                const HashIndex_COUNT_mPART3_L2_1_map_0* i32 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0*>(COUNT_mPART3_L2_1.index[1]);
                const HASH_RES_t h27 = COUNT_mPART3_L2_1_mapkey0_idxfn::hash(se53.modify0(partsupp_partkey));
                HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode* n32 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode*>(i32->slice(se53, h27));
                COUNT_mPART3_L2_1_entry* e32;
               
                if (n32 && (e32 = n32->obj)) {
                  do {                
                    DOUBLE_TYPE ps2_supplycost = e32->PS2_SUPPLYCOST;
                    long v33 = e32->__av;
                    (/*if */(ps_supplycost > ps2_supplycost) ? agg10 += v33 : 0L);
                    n32 = n32->nxt;
                  } while (n32 && (e32 = n32->obj) && h27 == n32->hash &&  COUNT_mPART3_L2_1_mapkey0_idxfn::equals(se53, *e32)); 
                }
              }(/*if */(l7 == agg10) ? _c1.addOrDelOnZero(st5.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,(v32 * -1L)), (v32 * -1L)) : (void)0);
              n31 = n31->nxt;
            } while (n31 && (e31 = n31->obj) && h28 == n31->hash &&  COUNT_mPART3_mapkey0_idxfn::equals(se54, *e31)); 
          }
        }{  // temp foreach
          const HashIndex<tuple7_SSSDSS_L, long>* i33 = static_cast<HashIndex<tuple7_SSSDSS_L, long>*>(_c1.index[0]);
          HashIndex<tuple7_SSSDSS_L, long>::IdxNode* n33; 
          tuple7_SSSDSS_L* e33;
        
          for (size_t i = 0; i < i33->size_; i++)
          {
            n33 = i33->buckets_ + i;
            while (n33 && (e33 = n33->obj))
            {
              STRING_TYPE s_name = e33->_1;
              STRING_TYPE s_address = e33->_2;
              STRING_TYPE s_phone = e33->_3;
              DOUBLE_TYPE s_acctbal = e33->_4;
              STRING_TYPE s_comment = e33->_5;
              STRING_TYPE n_name = e33->_6;  
              long v34 = e33->__av; 
            { //slice 
              const HashIndex_COUNT_mPARTSUPP2_map_0* i34 = static_cast<HashIndex_COUNT_mPARTSUPP2_map_0*>(COUNT_mPARTSUPP2.index[1]);
              const HASH_RES_t h29 = COUNT_mPARTSUPP2_mapkey0_idxfn::hash(se55.modify0(partsupp_partkey));
              HashIndex_COUNT_mPARTSUPP2_map_0::IdxNode* n34 = static_cast<HashIndex_COUNT_mPARTSUPP2_map_0::IdxNode*>(i34->slice(se55, h29));
              COUNT_mPARTSUPP2_entry* e34;
             
              if (n34 && (e34 = n34->obj)) {
                do {                
                  STRING_TYPE p_mfgr = e34->P_MFGR;
                  long v35 = e34->__av;
                  COUNT.addOrDelOnZero(se47.modify(s_acctbal,s_name,n_name,partsupp_partkey,p_mfgr,s_address,s_phone,s_comment),(v34 * v35));
                  n34 = n34->nxt;
                } while (n34 && (e34 = n34->obj) && h29 == n34->hash &&  COUNT_mPARTSUPP2_mapkey0_idxfn::equals(se55, *e34)); 
              }
            }      
              n33 = n33->nxt;
            }
          }
        }{ //slice 
          const HashIndex_COUNT_mPARTSUPP3_map_0* i35 = static_cast<HashIndex_COUNT_mPARTSUPP3_map_0*>(COUNT_mPARTSUPP3.index[1]);
          const HASH_RES_t h31 = COUNT_mPARTSUPP3_mapkey0_idxfn::hash(se58.modify0(partsupp_suppkey));
          HashIndex_COUNT_mPARTSUPP3_map_0::IdxNode* n35 = static_cast<HashIndex_COUNT_mPARTSUPP3_map_0::IdxNode*>(i35->slice(se58, h31));
          COUNT_mPARTSUPP3_entry* e35;
         
          if (n35 && (e35 = n35->obj)) {
            do {                
              STRING_TYPE s_name = e35->S_NAME;
              STRING_TYPE s_address = e35->S_ADDRESS;
              STRING_TYPE s_phone = e35->S_PHONE;
              DOUBLE_TYPE s_acctbal = e35->S_ACCTBAL;
              STRING_TYPE s_comment = e35->S_COMMENT;
              STRING_TYPE n_name = e35->N_NAME;
              long v36 = e35->__av;
              { //slice 
                const HashIndex_COUNT_mPARTSUPP2_map_0* i36 = static_cast<HashIndex_COUNT_mPARTSUPP2_map_0*>(COUNT_mPARTSUPP2.index[1]);
                const HASH_RES_t h30 = COUNT_mPARTSUPP2_mapkey0_idxfn::hash(se57.modify0(partsupp_partkey));
                HashIndex_COUNT_mPARTSUPP2_map_0::IdxNode* n36 = static_cast<HashIndex_COUNT_mPARTSUPP2_map_0::IdxNode*>(i36->slice(se57, h30));
                COUNT_mPARTSUPP2_entry* e36;
               
                if (n36 && (e36 = n36->obj)) {
                  do {                
                    STRING_TYPE p_mfgr = e36->P_MFGR;
                    long v37 = e36->__av;
                    COUNT_mSUPPLIER1.addOrDelOnZero(se56.modify(partsupp_partkey,p_mfgr,s_name,s_address,s_phone,s_acctbal,s_comment,partsupp_supplycost,n_name),(v36 * v37));
                    n36 = n36->nxt;
                  } while (n36 && (e36 = n36->obj) && h30 == n36->hash &&  COUNT_mPARTSUPP2_mapkey0_idxfn::equals(se57, *e36)); 
                }
              }
              n35 = n35->nxt;
            } while (n35 && (e35 = n35->obj) && h31 == n35->hash &&  COUNT_mPARTSUPP3_mapkey0_idxfn::equals(se58, *e35)); 
          }
        }{ //slice 
          const HashIndex_COUNT_mPARTSUPP2_map_0* i37 = static_cast<HashIndex_COUNT_mPARTSUPP2_map_0*>(COUNT_mPARTSUPP2.index[1]);
          const HASH_RES_t h32 = COUNT_mPARTSUPP2_mapkey0_idxfn::hash(se60.modify0(partsupp_partkey));
          HashIndex_COUNT_mPARTSUPP2_map_0::IdxNode* n37 = static_cast<HashIndex_COUNT_mPARTSUPP2_map_0::IdxNode*>(i37->slice(se60, h32));
          COUNT_mPARTSUPP2_entry* e37;
         
          if (n37 && (e37 = n37->obj)) {
            do {                
              STRING_TYPE p_mfgr = e37->P_MFGR;
              long v38 = e37->__av;
              COUNT_mSUPPLIER1_mSUPPLIER2.addOrDelOnZero(se59.modify(partsupp_partkey,partsupp_suppkey,partsupp_supplycost,p_mfgr),v38);
              n37 = n37->nxt;
            } while (n37 && (e37 = n37->obj) && h32 == n37->hash &&  COUNT_mPARTSUPP2_mapkey0_idxfn::equals(se60, *e37)); 
          }
        }COUNT_mSUPPLIER1_mSUPPLIER2_mPART3.addOrDelOnZero(se61.modify(partsupp_partkey,partsupp_suppkey,partsupp_supplycost),1L);
        { //slice 
          const HashIndex_COUNT_mPARTSUPP3_map_0* i38 = static_cast<HashIndex_COUNT_mPARTSUPP3_map_0*>(COUNT_mPARTSUPP3.index[1]);
          const HASH_RES_t h33 = COUNT_mPARTSUPP3_mapkey0_idxfn::hash(se63.modify0(partsupp_suppkey));
          HashIndex_COUNT_mPARTSUPP3_map_0::IdxNode* n38 = static_cast<HashIndex_COUNT_mPARTSUPP3_map_0::IdxNode*>(i38->slice(se63, h33));
          COUNT_mPARTSUPP3_entry* e38;
         
          if (n38 && (e38 = n38->obj)) {
            do {                
              STRING_TYPE s_name = e38->S_NAME;
              STRING_TYPE s_address = e38->S_ADDRESS;
              STRING_TYPE s_phone = e38->S_PHONE;
              DOUBLE_TYPE s_acctbal = e38->S_ACCTBAL;
              STRING_TYPE s_comment = e38->S_COMMENT;
              STRING_TYPE n_name = e38->N_NAME;
              long v39 = e38->__av;
              COUNT_mPART3.addOrDelOnZero(se62.modify(partsupp_partkey,partsupp_supplycost,s_name,s_address,s_phone,s_acctbal,s_comment,n_name),v39);
              n38 = n38->nxt;
            } while (n38 && (e38 = n38->obj) && h33 == n38->hash &&  COUNT_mPARTSUPP3_mapkey0_idxfn::equals(se63, *e38)); 
          }
        }COUNT_mPART3_L2_1.addOrDelOnZero(se64.modify(partsupp_partkey,partsupp_supplycost),COUNT_mPARTSUPP5_L2_3.getValueOrDefault(se65.modify(partsupp_suppkey)));
      }
    }
    void on_delete_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  //++tN;
        _c2.clear();
        long l8 = 0L;
        { //slice 
          const HashIndex_COUNT_mPART3_map_0* i39 = static_cast<HashIndex_COUNT_mPART3_map_0*>(COUNT_mPART3.index[1]);
          const HASH_RES_t h35 = COUNT_mPART3_mapkey0_idxfn::hash(se69.modify0(partsupp_partkey));
          HashIndex_COUNT_mPART3_map_0::IdxNode* n39 = static_cast<HashIndex_COUNT_mPART3_map_0::IdxNode*>(i39->slice(se69, h35));
          COUNT_mPART3_entry* e39;
         
          if (n39 && (e39 = n39->obj)) {
            do {                
              DOUBLE_TYPE ps_supplycost = e39->PS_SUPPLYCOST;
              STRING_TYPE s_name = e39->S_NAME;
              STRING_TYPE s_address = e39->S_ADDRESS;
              STRING_TYPE s_phone = e39->S_PHONE;
              DOUBLE_TYPE s_acctbal = e39->S_ACCTBAL;
              STRING_TYPE s_comment = e39->S_COMMENT;
              STRING_TYPE n_name = e39->N_NAME;
              long v41 = e39->__av;
              long agg11 = 0L;
              { //slice 
                const HashIndex_COUNT_mPART3_L2_1_map_0* i40 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0*>(COUNT_mPART3_L2_1.index[1]);
                const HASH_RES_t h34 = COUNT_mPART3_L2_1_mapkey0_idxfn::hash(se67.modify0(partsupp_partkey));
                HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode* n40 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode*>(i40->slice(se67, h34));
                COUNT_mPART3_L2_1_entry* e40;
               
                if (n40 && (e40 = n40->obj)) {
                  do {                
                    DOUBLE_TYPE ps2_supplycost = e40->PS2_SUPPLYCOST;
                    long v42 = e40->__av;
                    (/*if */(ps_supplycost > ps2_supplycost) ? agg11 += v42 : 0L);
                    n40 = n40->nxt;
                  } while (n40 && (e40 = n40->obj) && h34 == n40->hash &&  COUNT_mPART3_L2_1_mapkey0_idxfn::equals(se67, *e40)); 
                }
              }(/*if */(l8 == (agg11 + (/*if */(ps_supplycost > partsupp_supplycost) ? (COUNT_mPARTSUPP5_L2_3.getValueOrDefault(se68.modify(partsupp_suppkey)) * -1L) : 0L))) ? _c2.addOrDelOnZero(st6.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,v41), v41) : (void)0);
              n39 = n39->nxt;
            } while (n39 && (e39 = n39->obj) && h35 == n39->hash &&  COUNT_mPART3_mapkey0_idxfn::equals(se69, *e39)); 
          }
        }long agg12 = 0L;
        long agg13 = 0L;
        { //slice 
          const HashIndex_COUNT_mPART3_L2_1_map_0* i41 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0*>(COUNT_mPART3_L2_1.index[1]);
          const HASH_RES_t h36 = COUNT_mPART3_L2_1_mapkey0_idxfn::hash(se70.modify0(partsupp_partkey));
          HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode* n41 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode*>(i41->slice(se70, h36));
          COUNT_mPART3_L2_1_entry* e41;
         
          if (n41 && (e41 = n41->obj)) {
            do {                
              DOUBLE_TYPE ps2_supplycost = e41->PS2_SUPPLYCOST;
              long v43 = e41->__av;
              (/*if */(partsupp_supplycost > ps2_supplycost) ? agg13 += v43 : 0L);
              n41 = n41->nxt;
            } while (n41 && (e41 = n41->obj) && h36 == n41->hash &&  COUNT_mPART3_L2_1_mapkey0_idxfn::equals(se70, *e41)); 
          }
        }long l9 = agg13;
        (/*if */(l9 == 0L) ? agg12 += 1L : 0L);
        { //slice 
          const HashIndex_COUNT_mPARTSUPP3_map_0* i42 = static_cast<HashIndex_COUNT_mPARTSUPP3_map_0*>(COUNT_mPARTSUPP3.index[1]);
          const HASH_RES_t h37 = COUNT_mPARTSUPP3_mapkey0_idxfn::hash(se71.modify0(partsupp_suppkey));
          HashIndex_COUNT_mPARTSUPP3_map_0::IdxNode* n42 = static_cast<HashIndex_COUNT_mPARTSUPP3_map_0::IdxNode*>(i42->slice(se71, h37));
          COUNT_mPARTSUPP3_entry* e42;
         
          if (n42 && (e42 = n42->obj)) {
            do {                
              STRING_TYPE s_name = e42->S_NAME;
              STRING_TYPE s_address = e42->S_ADDRESS;
              STRING_TYPE s_phone = e42->S_PHONE;
              DOUBLE_TYPE s_acctbal = e42->S_ACCTBAL;
              STRING_TYPE s_comment = e42->S_COMMENT;
              STRING_TYPE n_name = e42->N_NAME;
              long v44 = e42->__av;
              _c2.addOrDelOnZero(st7.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,(agg12 * (v44 * -1L))), (agg12 * (v44 * -1L)));
              n42 = n42->nxt;
            } while (n42 && (e42 = n42->obj) && h37 == n42->hash &&  COUNT_mPARTSUPP3_mapkey0_idxfn::equals(se71, *e42)); 
          }
        }long l10 = 0L;
        { //slice 
          const HashIndex_COUNT_mPART3_map_0* i43 = static_cast<HashIndex_COUNT_mPART3_map_0*>(COUNT_mPART3.index[1]);
          const HASH_RES_t h39 = COUNT_mPART3_mapkey0_idxfn::hash(se73.modify0(partsupp_partkey));
          HashIndex_COUNT_mPART3_map_0::IdxNode* n43 = static_cast<HashIndex_COUNT_mPART3_map_0::IdxNode*>(i43->slice(se73, h39));
          COUNT_mPART3_entry* e43;
         
          if (n43 && (e43 = n43->obj)) {
            do {                
              DOUBLE_TYPE ps_supplycost = e43->PS_SUPPLYCOST;
              STRING_TYPE s_name = e43->S_NAME;
              STRING_TYPE s_address = e43->S_ADDRESS;
              STRING_TYPE s_phone = e43->S_PHONE;
              DOUBLE_TYPE s_acctbal = e43->S_ACCTBAL;
              STRING_TYPE s_comment = e43->S_COMMENT;
              STRING_TYPE n_name = e43->N_NAME;
              long v45 = e43->__av;
              long agg14 = 0L;
              { //slice 
                const HashIndex_COUNT_mPART3_L2_1_map_0* i44 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0*>(COUNT_mPART3_L2_1.index[1]);
                const HASH_RES_t h38 = COUNT_mPART3_L2_1_mapkey0_idxfn::hash(se72.modify0(partsupp_partkey));
                HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode* n44 = static_cast<HashIndex_COUNT_mPART3_L2_1_map_0::IdxNode*>(i44->slice(se72, h38));
                COUNT_mPART3_L2_1_entry* e44;
               
                if (n44 && (e44 = n44->obj)) {
                  do {                
                    DOUBLE_TYPE ps2_supplycost = e44->PS2_SUPPLYCOST;
                    long v46 = e44->__av;
                    (/*if */(ps_supplycost > ps2_supplycost) ? agg14 += v46 : 0L);
                    n44 = n44->nxt;
                  } while (n44 && (e44 = n44->obj) && h38 == n44->hash &&  COUNT_mPART3_L2_1_mapkey0_idxfn::equals(se72, *e44)); 
                }
              }(/*if */(l10 == agg14) ? _c2.addOrDelOnZero(st8.modify(s_name,s_address,s_phone,s_acctbal,s_comment,n_name,(v45 * -1L)), (v45 * -1L)) : (void)0);
              n43 = n43->nxt;
            } while (n43 && (e43 = n43->obj) && h39 == n43->hash &&  COUNT_mPART3_mapkey0_idxfn::equals(se73, *e43)); 
          }
        }{  // temp foreach
          const HashIndex<tuple7_SSSDSS_L, long>* i45 = static_cast<HashIndex<tuple7_SSSDSS_L, long>*>(_c2.index[0]);
          HashIndex<tuple7_SSSDSS_L, long>::IdxNode* n45; 
          tuple7_SSSDSS_L* e45;
        
          for (size_t i = 0; i < i45->size_; i++)
          {
            n45 = i45->buckets_ + i;
            while (n45 && (e45 = n45->obj))
            {
              STRING_TYPE s_name = e45->_1;
              STRING_TYPE s_address = e45->_2;
              STRING_TYPE s_phone = e45->_3;
              DOUBLE_TYPE s_acctbal = e45->_4;
              STRING_TYPE s_comment = e45->_5;
              STRING_TYPE n_name = e45->_6;  
              long v47 = e45->__av; 
            { //slice 
              const HashIndex_COUNT_mPARTSUPP2_map_0* i46 = static_cast<HashIndex_COUNT_mPARTSUPP2_map_0*>(COUNT_mPARTSUPP2.index[1]);
              const HASH_RES_t h40 = COUNT_mPARTSUPP2_mapkey0_idxfn::hash(se74.modify0(partsupp_partkey));
              HashIndex_COUNT_mPARTSUPP2_map_0::IdxNode* n46 = static_cast<HashIndex_COUNT_mPARTSUPP2_map_0::IdxNode*>(i46->slice(se74, h40));
              COUNT_mPARTSUPP2_entry* e46;
             
              if (n46 && (e46 = n46->obj)) {
                do {                
                  STRING_TYPE p_mfgr = e46->P_MFGR;
                  long v48 = e46->__av;
                  COUNT.addOrDelOnZero(se66.modify(s_acctbal,s_name,n_name,partsupp_partkey,p_mfgr,s_address,s_phone,s_comment),(v47 * v48));
                  n46 = n46->nxt;
                } while (n46 && (e46 = n46->obj) && h40 == n46->hash &&  COUNT_mPARTSUPP2_mapkey0_idxfn::equals(se74, *e46)); 
              }
            }      
              n45 = n45->nxt;
            }
          }
        }{ //slice 
          const HashIndex_COUNT_mPARTSUPP3_map_0* i47 = static_cast<HashIndex_COUNT_mPARTSUPP3_map_0*>(COUNT_mPARTSUPP3.index[1]);
          const HASH_RES_t h42 = COUNT_mPARTSUPP3_mapkey0_idxfn::hash(se77.modify0(partsupp_suppkey));
          HashIndex_COUNT_mPARTSUPP3_map_0::IdxNode* n47 = static_cast<HashIndex_COUNT_mPARTSUPP3_map_0::IdxNode*>(i47->slice(se77, h42));
          COUNT_mPARTSUPP3_entry* e47;
         
          if (n47 && (e47 = n47->obj)) {
            do {                
              STRING_TYPE s_name = e47->S_NAME;
              STRING_TYPE s_address = e47->S_ADDRESS;
              STRING_TYPE s_phone = e47->S_PHONE;
              DOUBLE_TYPE s_acctbal = e47->S_ACCTBAL;
              STRING_TYPE s_comment = e47->S_COMMENT;
              STRING_TYPE n_name = e47->N_NAME;
              long v49 = e47->__av;
              { //slice 
                const HashIndex_COUNT_mPARTSUPP2_map_0* i48 = static_cast<HashIndex_COUNT_mPARTSUPP2_map_0*>(COUNT_mPARTSUPP2.index[1]);
                const HASH_RES_t h41 = COUNT_mPARTSUPP2_mapkey0_idxfn::hash(se76.modify0(partsupp_partkey));
                HashIndex_COUNT_mPARTSUPP2_map_0::IdxNode* n48 = static_cast<HashIndex_COUNT_mPARTSUPP2_map_0::IdxNode*>(i48->slice(se76, h41));
                COUNT_mPARTSUPP2_entry* e48;
               
                if (n48 && (e48 = n48->obj)) {
                  do {                
                    STRING_TYPE p_mfgr = e48->P_MFGR;
                    long v50 = e48->__av;
                    COUNT_mSUPPLIER1.addOrDelOnZero(se75.modify(partsupp_partkey,p_mfgr,s_name,s_address,s_phone,s_acctbal,s_comment,partsupp_supplycost,n_name),(v49 * (v50 * -1L)));
                    n48 = n48->nxt;
                  } while (n48 && (e48 = n48->obj) && h41 == n48->hash &&  COUNT_mPARTSUPP2_mapkey0_idxfn::equals(se76, *e48)); 
                }
              }
              n47 = n47->nxt;
            } while (n47 && (e47 = n47->obj) && h42 == n47->hash &&  COUNT_mPARTSUPP3_mapkey0_idxfn::equals(se77, *e47)); 
          }
        }{ //slice 
          const HashIndex_COUNT_mPARTSUPP2_map_0* i49 = static_cast<HashIndex_COUNT_mPARTSUPP2_map_0*>(COUNT_mPARTSUPP2.index[1]);
          const HASH_RES_t h43 = COUNT_mPARTSUPP2_mapkey0_idxfn::hash(se79.modify0(partsupp_partkey));
          HashIndex_COUNT_mPARTSUPP2_map_0::IdxNode* n49 = static_cast<HashIndex_COUNT_mPARTSUPP2_map_0::IdxNode*>(i49->slice(se79, h43));
          COUNT_mPARTSUPP2_entry* e49;
         
          if (n49 && (e49 = n49->obj)) {
            do {                
              STRING_TYPE p_mfgr = e49->P_MFGR;
              long v51 = e49->__av;
              COUNT_mSUPPLIER1_mSUPPLIER2.addOrDelOnZero(se78.modify(partsupp_partkey,partsupp_suppkey,partsupp_supplycost,p_mfgr),(v51 * -1L));
              n49 = n49->nxt;
            } while (n49 && (e49 = n49->obj) && h43 == n49->hash &&  COUNT_mPARTSUPP2_mapkey0_idxfn::equals(se79, *e49)); 
          }
        }COUNT_mSUPPLIER1_mSUPPLIER2_mPART3.addOrDelOnZero(se80.modify(partsupp_partkey,partsupp_suppkey,partsupp_supplycost),-1L);
        { //slice 
          const HashIndex_COUNT_mPARTSUPP3_map_0* i50 = static_cast<HashIndex_COUNT_mPARTSUPP3_map_0*>(COUNT_mPARTSUPP3.index[1]);
          const HASH_RES_t h44 = COUNT_mPARTSUPP3_mapkey0_idxfn::hash(se82.modify0(partsupp_suppkey));
          HashIndex_COUNT_mPARTSUPP3_map_0::IdxNode* n50 = static_cast<HashIndex_COUNT_mPARTSUPP3_map_0::IdxNode*>(i50->slice(se82, h44));
          COUNT_mPARTSUPP3_entry* e50;
         
          if (n50 && (e50 = n50->obj)) {
            do {                
              STRING_TYPE s_name = e50->S_NAME;
              STRING_TYPE s_address = e50->S_ADDRESS;
              STRING_TYPE s_phone = e50->S_PHONE;
              DOUBLE_TYPE s_acctbal = e50->S_ACCTBAL;
              STRING_TYPE s_comment = e50->S_COMMENT;
              STRING_TYPE n_name = e50->N_NAME;
              long v52 = e50->__av;
              COUNT_mPART3.addOrDelOnZero(se81.modify(partsupp_partkey,partsupp_supplycost,s_name,s_address,s_phone,s_acctbal,s_comment,n_name),(v52 * -1L));
              n50 = n50->nxt;
            } while (n50 && (e50 = n50->obj) && h44 == n50->hash &&  COUNT_mPARTSUPP3_mapkey0_idxfn::equals(se82, *e50)); 
          }
        }COUNT_mPART3_L2_1.addOrDelOnZero(se83.modify(partsupp_partkey,partsupp_supplycost),(COUNT_mPARTSUPP5_L2_3.getValueOrDefault(se84.modify(partsupp_suppkey)) * -1L));
      }
    }
    void on_system_ready_event() {
      {  //
        COUNT_mPARTSUPP3_mSUPPLIER1.clear();
        STRING_TYPE l11 = c1;
        {  // foreach
          const HashIndex_NATION_map_0123* i51 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n51; 
          NATION_entry* e51;
        
          for (size_t i = 0; i < i51->size_; i++)
          {
            n51 = i51->buckets_ + i;
            while (n51 && (e51 = n51->obj))
            {
                long count_mpartsupp3_msuppliersupplier_nationkey = e51->NATION_NATIONKEY;
                STRING_TYPE n_name = e51->NATION_NAME;
                long n_regionkey = e51->NATION_REGIONKEY;
                STRING_TYPE n_comment = e51->NATION_COMMENT;
                long v53 = e51->__av;
                { //slice 
                  const HashIndex_REGION_map_01* i52 = static_cast<HashIndex_REGION_map_01*>(REGION.index[1]);
                  const HASH_RES_t h45 = REGION_mapkey01_idxfn::hash(se86.modify01(n_regionkey, l11));
                  HashIndex_REGION_map_01::IdxNode* n52 = static_cast<HashIndex_REGION_map_01::IdxNode*>(i52->slice(se86, h45));
                  REGION_entry* e52;
                 
                  if (n52 && (e52 = n52->obj)) {
                    do {                
                      STRING_TYPE r_comment = e52->REGION_COMMENT;
                      long v54 = e52->__av;
                      COUNT_mPARTSUPP3_mSUPPLIER1.addOrDelOnZero(se85.modify(count_mpartsupp3_msuppliersupplier_nationkey,n_name),(v53 * v54));
                      n52 = n52->nxt;
                    } while (n52 && (e52 = n52->obj) && h45 == n52->hash &&  REGION_mapkey01_idxfn::equals(se86, *e52)); 
                  }
                }
              n51 = n51->nxt;
            }
          }
        }COUNT_mPARTSUPP5_L2_3_mSUPPLIER1.clear();
        STRING_TYPE l12 = c1;
        {  // foreach
          const HashIndex_NATION_map_0123* i53 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n53; 
          NATION_entry* e53;
        
          for (size_t i = 0; i < i53->size_; i++)
          {
            n53 = i53->buckets_ + i;
            while (n53 && (e53 = n53->obj))
            {
                long count_mpartsupp5_l2_3_msuppliersupplier_nationkey = e53->NATION_NATIONKEY;
                STRING_TYPE n2_name = e53->NATION_NAME;
                long n2_regionkey = e53->NATION_REGIONKEY;
                STRING_TYPE n2_comment = e53->NATION_COMMENT;
                long v55 = e53->__av;
                { //slice 
                  const HashIndex_REGION_map_01* i54 = static_cast<HashIndex_REGION_map_01*>(REGION.index[1]);
                  const HASH_RES_t h46 = REGION_mapkey01_idxfn::hash(se88.modify01(n2_regionkey, l12));
                  HashIndex_REGION_map_01::IdxNode* n54 = static_cast<HashIndex_REGION_map_01::IdxNode*>(i54->slice(se88, h46));
                  REGION_entry* e54;
                 
                  if (n54 && (e54 = n54->obj)) {
                    do {                
                      STRING_TYPE r2_comment = e54->REGION_COMMENT;
                      long v56 = e54->__av;
                      COUNT_mPARTSUPP5_L2_3_mSUPPLIER1.addOrDelOnZero(se87.modify(count_mpartsupp5_l2_3_msuppliersupplier_nationkey),(v55 * v56));
                      n54 = n54->nxt;
                    } while (n54 && (e54 = n54->obj) && h46 == n54->hash &&  REGION_mapkey01_idxfn::equals(se88, *e54)); 
                  }
                }
              n53 = n53->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNT_entry se1;
    COUNT_mPART3_L2_1_entry se2;
    tuple7_SSSDSS_L st1;
    COUNT_mPART3_entry se3;
    COUNT_mPARTSUPP2_entry se4;
    COUNT_mSUPPLIER1_entry se5;
    COUNT_mPART3_entry se6;
    COUNT_mSUPPLIER1_mSUPPLIER2_entry se7;
    COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry se8;
    COUNT_entry se9;
    COUNT_mPART3_L2_1_entry se10;
    tuple7_SSSDSS_L st2;
    COUNT_mPART3_entry se11;
    COUNT_mPARTSUPP2_entry se12;
    COUNT_mSUPPLIER1_entry se13;
    COUNT_mPART3_entry se14;
    COUNT_mSUPPLIER1_mSUPPLIER2_entry se15;
    COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry se16;
    COUNT_mPARTSUPP3_entry se17;
    COUNT_mPARTSUPP3_mSUPPLIER1_entry se18;
    COUNT_mPARTSUPP5_L2_3_entry se19;
    COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry se20;
    COUNT_mSUPPLIER1_entry se21;
    COUNT_mSUPPLIER1_mSUPPLIER2_entry se22;
    COUNT_mPARTSUPP3_mSUPPLIER1_entry se23;
    COUNT_mPART3_entry se24;
    COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry se25;
    COUNT_mPARTSUPP3_mSUPPLIER1_entry se26;
    COUNT_mPART3_L2_1_entry se27;
    COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry se28;
    COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry se29;
    COUNT_entry se30;
    COUNT_mPART3_L2_1_entry se31;
    COUNT_mPARTSUPP3_entry se32;
    COUNT_mPARTSUPP3_mSUPPLIER1_entry se33;
    COUNT_mPARTSUPP5_L2_3_entry se34;
    COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry se35;
    COUNT_mSUPPLIER1_entry se36;
    COUNT_mSUPPLIER1_mSUPPLIER2_entry se37;
    COUNT_mPARTSUPP3_mSUPPLIER1_entry se38;
    COUNT_mPART3_entry se39;
    COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry se40;
    COUNT_mPARTSUPP3_mSUPPLIER1_entry se41;
    COUNT_mPART3_L2_1_entry se42;
    COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry se43;
    COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry se44;
    COUNT_entry se45;
    COUNT_mPART3_L2_1_entry se46;
    COUNT_entry se47;
    COUNT_mPART3_L2_1_entry se48;
    COUNT_mPARTSUPP5_L2_3_entry se49;
    tuple7_SSSDSS_L st3;
    COUNT_mPART3_entry se50;
    COUNT_mPART3_L2_1_entry se51;
    tuple7_SSSDSS_L st4;
    COUNT_mPARTSUPP3_entry se52;
    COUNT_mPART3_L2_1_entry se53;
    tuple7_SSSDSS_L st5;
    COUNT_mPART3_entry se54;
    COUNT_mPARTSUPP2_entry se55;
    COUNT_mSUPPLIER1_entry se56;
    COUNT_mPARTSUPP2_entry se57;
    COUNT_mPARTSUPP3_entry se58;
    COUNT_mSUPPLIER1_mSUPPLIER2_entry se59;
    COUNT_mPARTSUPP2_entry se60;
    COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry se61;
    COUNT_mPART3_entry se62;
    COUNT_mPARTSUPP3_entry se63;
    COUNT_mPART3_L2_1_entry se64;
    COUNT_mPARTSUPP5_L2_3_entry se65;
    COUNT_entry se66;
    COUNT_mPART3_L2_1_entry se67;
    COUNT_mPARTSUPP5_L2_3_entry se68;
    tuple7_SSSDSS_L st6;
    COUNT_mPART3_entry se69;
    COUNT_mPART3_L2_1_entry se70;
    tuple7_SSSDSS_L st7;
    COUNT_mPARTSUPP3_entry se71;
    COUNT_mPART3_L2_1_entry se72;
    tuple7_SSSDSS_L st8;
    COUNT_mPART3_entry se73;
    COUNT_mPARTSUPP2_entry se74;
    COUNT_mSUPPLIER1_entry se75;
    COUNT_mPARTSUPP2_entry se76;
    COUNT_mPARTSUPP3_entry se77;
    COUNT_mSUPPLIER1_mSUPPLIER2_entry se78;
    COUNT_mPARTSUPP2_entry se79;
    COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_entry se80;
    COUNT_mPART3_entry se81;
    COUNT_mPARTSUPP3_entry se82;
    COUNT_mPART3_L2_1_entry se83;
    COUNT_mPARTSUPP5_L2_3_entry se84;
    COUNT_mPARTSUPP3_mSUPPLIER1_entry se85;
    REGION_entry se86;
    COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_entry se87;
    REGION_entry se88;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REGION_map REGION;
    COUNT_mPARTSUPP2_map COUNT_mPARTSUPP2;
    COUNT_mPARTSUPP3_map COUNT_mPARTSUPP3;
    COUNT_mPARTSUPP3_mSUPPLIER1_map COUNT_mPARTSUPP3_mSUPPLIER1;
    COUNT_mPARTSUPP5_L2_3_map COUNT_mPARTSUPP5_L2_3;
    COUNT_mPARTSUPP5_L2_3_mSUPPLIER1_map COUNT_mPARTSUPP5_L2_3_mSUPPLIER1;
    COUNT_mSUPPLIER1_map COUNT_mSUPPLIER1;
    COUNT_mSUPPLIER1_mSUPPLIER2_map COUNT_mSUPPLIER1_mSUPPLIER2;
    COUNT_mSUPPLIER1_mSUPPLIER2_mPART3_map COUNT_mSUPPLIER1_mSUPPLIER2_mPART3;
    COUNT_mPART3_map COUNT_mPART3;
    COUNT_mPART3_L2_1_map COUNT_mPART3_L2_1;
    MultiHashMap<tuple7_SSSDSS_L,long,HashIndex<tuple7_SSSDSS_L,long> > _c1;
    MultiHashMap<tuple7_SSSDSS_L,long,HashIndex<tuple7_SSSDSS_L,long> > _c2;
    MultiHashMap<tuple7_SSSDSS_L,long,HashIndex<tuple7_SSSDSS_L,long> > agg1;
    MultiHashMap<tuple7_SSSDSS_L,long,HashIndex<tuple7_SSSDSS_L,long> > agg3;
    /*const static*/ STRING_TYPE c1;
  
  };

}
