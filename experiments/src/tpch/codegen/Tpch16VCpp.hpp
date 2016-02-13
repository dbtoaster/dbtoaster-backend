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
  struct SUPPLIER_CNT_entry {
    STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_entry() { /*P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const long c3) { P_BRAND = c0; P_TYPE = c1; P_SIZE = c2; __av = c3; }
    SUPPLIER_CNT_entry(const SUPPLIER_CNT_entry& other) : P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { P_BRAND = c0; P_TYPE = c1; P_SIZE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNT_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_entry& x, const SUPPLIER_CNT_entry& y) {
      return x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_entry,long,
    HashIndex<SUPPLIER_CNT_entry,long,SUPPLIER_CNT_mapkey012_idxfn,true>
  > SUPPLIER_CNT_map;
  typedef HashIndex<SUPPLIER_CNT_entry,long,SUPPLIER_CNT_mapkey012_idxfn,true> HashIndex_SUPPLIER_CNT_map_012;
  
  struct SUPPLIER_CNT_mPART4_E1_1_entry {
    STRING_TYPE SUPPLIER_CNT_mPARTPART_BRAND; STRING_TYPE SUPPLIER_CNT_mPARTPART_TYPE; long SUPPLIER_CNT_mPARTPART_SIZE; long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNT_mPART4_E1_1_entry() { /*SUPPLIER_CNT_mPARTPART_BRAND = ""; SUPPLIER_CNT_mPARTPART_TYPE = ""; SUPPLIER_CNT_mPARTPART_SIZE = 0L; PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPART4_E1_1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTPART_BRAND = c0; SUPPLIER_CNT_mPARTPART_TYPE = c1; SUPPLIER_CNT_mPARTPART_SIZE = c2; PS_SUPPKEY = c3; __av = c4; }
    SUPPLIER_CNT_mPART4_E1_1_entry(const SUPPLIER_CNT_mPART4_E1_1_entry& other) : SUPPLIER_CNT_mPARTPART_BRAND( other.SUPPLIER_CNT_mPARTPART_BRAND ), SUPPLIER_CNT_mPARTPART_TYPE( other.SUPPLIER_CNT_mPARTPART_TYPE ), SUPPLIER_CNT_mPARTPART_SIZE( other.SUPPLIER_CNT_mPARTPART_SIZE ), PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPART4_E1_1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const long c3) { SUPPLIER_CNT_mPARTPART_BRAND = c0; SUPPLIER_CNT_mPARTPART_TYPE = c1; SUPPLIER_CNT_mPARTPART_SIZE = c2; PS_SUPPKEY = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPART4_E1_1_entry& modify012(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { SUPPLIER_CNT_mPARTPART_BRAND = c0; SUPPLIER_CNT_mPARTPART_TYPE = c1; SUPPLIER_CNT_mPARTPART_SIZE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNT_mPARTPART_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNT_mPARTPART_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNT_mPARTPART_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNT_mPART4_E1_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPART4_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_BRAND);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_TYPE);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_SIZE);
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPART4_E1_1_entry& x, const SUPPLIER_CNT_mPART4_E1_1_entry& y) {
      return x.SUPPLIER_CNT_mPARTPART_BRAND == y.SUPPLIER_CNT_mPARTPART_BRAND && x.SUPPLIER_CNT_mPARTPART_TYPE == y.SUPPLIER_CNT_mPARTPART_TYPE && x.SUPPLIER_CNT_mPARTPART_SIZE == y.SUPPLIER_CNT_mPARTPART_SIZE && x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  struct SUPPLIER_CNT_mPART4_E1_1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPART4_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_BRAND);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_TYPE);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPART4_E1_1_entry& x, const SUPPLIER_CNT_mPART4_E1_1_entry& y) {
      return x.SUPPLIER_CNT_mPARTPART_BRAND == y.SUPPLIER_CNT_mPARTPART_BRAND && x.SUPPLIER_CNT_mPARTPART_TYPE == y.SUPPLIER_CNT_mPARTPART_TYPE && x.SUPPLIER_CNT_mPARTPART_SIZE == y.SUPPLIER_CNT_mPARTPART_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPART4_E1_1_entry,long,
    HashIndex<SUPPLIER_CNT_mPART4_E1_1_entry,long,SUPPLIER_CNT_mPART4_E1_1_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPART4_E1_1_entry,long,SUPPLIER_CNT_mPART4_E1_1_mapkey012_idxfn,false>
  > SUPPLIER_CNT_mPART4_E1_1_map;
  typedef HashIndex<SUPPLIER_CNT_mPART4_E1_1_entry,long,SUPPLIER_CNT_mPART4_E1_1_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPART4_E1_1_entry,long,SUPPLIER_CNT_mPART4_E1_1_mapkey012_idxfn,false> HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012;
  
  struct SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry {
    long SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE SUPPLIER_CNT_mPARTPART_BRAND; STRING_TYPE SUPPLIER_CNT_mPARTPART_TYPE; long SUPPLIER_CNT_mPARTPART_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry() { /*SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY = 0L; SUPPLIER_CNT_mPARTPART_BRAND = ""; SUPPLIER_CNT_mPARTPART_TYPE = ""; SUPPLIER_CNT_mPARTPART_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY = c0; SUPPLIER_CNT_mPARTPART_BRAND = c1; SUPPLIER_CNT_mPARTPART_TYPE = c2; SUPPLIER_CNT_mPARTPART_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry(const SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry& other) : SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY ), SUPPLIER_CNT_mPARTPART_BRAND( other.SUPPLIER_CNT_mPARTPART_BRAND ), SUPPLIER_CNT_mPARTPART_TYPE( other.SUPPLIER_CNT_mPARTPART_TYPE ), SUPPLIER_CNT_mPARTPART_SIZE( other.SUPPLIER_CNT_mPARTPART_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY = c0; SUPPLIER_CNT_mPARTPART_BRAND = c1; SUPPLIER_CNT_mPARTPART_TYPE = c2; SUPPLIER_CNT_mPARTPART_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry& modify0(const long c0) { SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNT_mPARTPART_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNT_mPARTPART_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNT_mPARTPART_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_BRAND);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_TYPE);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry& x, const SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry& y) {
      return x.SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY && x.SUPPLIER_CNT_mPARTPART_BRAND == y.SUPPLIER_CNT_mPARTPART_BRAND && x.SUPPLIER_CNT_mPARTPART_TYPE == y.SUPPLIER_CNT_mPARTPART_TYPE && x.SUPPLIER_CNT_mPARTPART_SIZE == y.SUPPLIER_CNT_mPARTPART_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry& x, const SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry& y) {
      return x.SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPART4_E1_1_mPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry,long,
    HashIndex<SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry,long,SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry,long,SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_map;
  typedef HashIndex<SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry,long,SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry,long,SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_map_0;
  
  struct SUPPLIER_CNT_mPART4_E1_2_entry {
    long SUPPLIER_CNT_mPARTPART_PARTKEY; long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNT_mPART4_E1_2_entry() { /*SUPPLIER_CNT_mPARTPART_PARTKEY = 0L; PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPART4_E1_2_entry(const long c0, const long c1, const long c2) { SUPPLIER_CNT_mPARTPART_PARTKEY = c0; PS_SUPPKEY = c1; __av = c2; }
    SUPPLIER_CNT_mPART4_E1_2_entry(const SUPPLIER_CNT_mPART4_E1_2_entry& other) : SUPPLIER_CNT_mPARTPART_PARTKEY( other.SUPPLIER_CNT_mPARTPART_PARTKEY ), PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPART4_E1_2_entry& modify(const long c0, const long c1) { SUPPLIER_CNT_mPARTPART_PARTKEY = c0; PS_SUPPKEY = c1;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPART4_E1_2_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNT_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNT_mPART4_E1_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPART4_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_PARTKEY);
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPART4_E1_2_entry& x, const SUPPLIER_CNT_mPART4_E1_2_entry& y) {
      return x.SUPPLIER_CNT_mPARTPART_PARTKEY == y.SUPPLIER_CNT_mPARTPART_PARTKEY && x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  struct SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPART4_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPART4_E1_2_entry& x, const SUPPLIER_CNT_mPART4_E1_2_entry& y) {
      return x.SUPPLIER_CNT_mPARTPART_PARTKEY == y.SUPPLIER_CNT_mPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPART4_E1_2_entry,long,
    HashIndex<SUPPLIER_CNT_mPART4_E1_2_entry,long,SUPPLIER_CNT_mPART4_E1_2_mapkey01_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPART4_E1_2_entry,long,SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPART4_E1_2_map;
  typedef HashIndex<SUPPLIER_CNT_mPART4_E1_2_entry,long,SUPPLIER_CNT_mPART4_E1_2_mapkey01_idxfn,true> HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_01;
  typedef HashIndex<SUPPLIER_CNT_mPART4_E1_2_entry,long,SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry(const long c0, const long c1) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; __av = c1; }
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry& modify(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_mapkey0_idxfn,true>
  > SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_mapkey0_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_2_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_2_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_2_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_2_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_2_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_2_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_2_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_2_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_2_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_2_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_2_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_2_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_2_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_2_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_2_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_2_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_4_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_4_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_4_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_4_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_4_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_4_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_4_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_4_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_4_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0;
  
  struct tuple4_SSL_L {
    STRING_TYPE _1; STRING_TYPE _2; long _3; long __av;
    explicit tuple4_SSL_L() { }
    explicit tuple4_SSL_L(const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; __av = c__av;}
    int operator==(const tuple4_SSL_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3)); }
    FORCE_INLINE tuple4_SSL_L& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, long c__av) { _1 = c0; _2 = c1; _3 = c2; __av = c__av; return *this; }
    static bool equals(const tuple4_SSL_L &x, const tuple4_SSL_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3)); }
    static long hash(const tuple4_SSL_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      return h;
    }
  };
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
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const SUPPLIER_CNT_map& _SUPPLIER_CNT = get_SUPPLIER_CNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(SUPPLIER_CNT), _SUPPLIER_CNT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const SUPPLIER_CNT_map& get_SUPPLIER_CNT() const {
      return SUPPLIER_CNT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    SUPPLIER_CNT_map SUPPLIER_CNT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), agg11(16U), agg6(16U), agg13(16U), agg8(16U), agg16(16U), agg2(16U), agg10(16U), agg4(16U), agg12(16U), agg15(16U), agg14(16U), agg9(16U) {
      c1 = STRING_TYPE("Brand#45");
      /* regex_t init */
      if(regcomp(&preg2, "^.*Customer.*Complaints.*$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^.*Customer.*Complaints.*$/" << endl;
        exit(-1);
      }
      if(regcomp(&preg1, "^MEDIUM POLISHED.*$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^MEDIUM POLISHED.*$/" << endl;
        exit(-1);
      }
    }
  
    ~data_t() {
      regfree(&preg2);
      regfree(&preg1);
    }
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  //++tN;
        long agg1 = 0L;
        agg2.clear();
        
        long l1 = 0L;
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012* i1 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012*>(SUPPLIER_CNT_mPART4_E1_1.index[1]);
          const HASH_RES_t h1 = SUPPLIER_CNT_mPART4_E1_1_mapkey012_idxfn::hash(se3.modify012(part_brand, part_type, part_size));
          HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012::IdxNode* n1 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012::IdxNode*>(i1->slice(se3, h1));
          SUPPLIER_CNT_mPART4_E1_1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long ps_suppkey = e1->PS_SUPPKEY;
              long v1 = e1->__av;
              (/*if */(l1 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se2.modify(ps_suppkey))) ? agg2.addOrDelOnZero(st1.modify(ps_suppkey,v1), v1) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  SUPPLIER_CNT_mPART4_E1_1_mapkey012_idxfn::equals(se3, *e1)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0* i2 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0*>(SUPPLIER_CNT_mPART4_E1_2.index[1]);
          const HASH_RES_t h2 = SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn::hash(se5.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0::IdxNode* n2 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0::IdxNode*>(i2->slice(se5, h2));
          SUPPLIER_CNT_mPART4_E1_2_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long ps_suppkey = e2->PS_SUPPKEY;
              long v2 = e2->__av;
              (/*if */(l1 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se4.modify(ps_suppkey))) ? agg2.addOrDelOnZero(st2.modify(ps_suppkey,v2), v2) : (void)0);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn::equals(se5, *e2)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i3 = static_cast<HashIndex<tuple2_L_L, long>*>(agg2.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n3; 
          tuple2_L_L* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
              long ps_suppkey = e3->_1;  
              long v3 = e3->__av; 
            agg1 += (v3 != 0 ? 1L : 0L);      
              n3 = n3->nxt;
            }
          }
        }long agg3 = 0L;
        agg4.clear();
        
        long l2 = 0L;
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012* i4 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012*>(SUPPLIER_CNT_mPART4_E1_1.index[1]);
          const HASH_RES_t h3 = SUPPLIER_CNT_mPART4_E1_1_mapkey012_idxfn::hash(se7.modify012(part_brand, part_type, part_size));
          HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012::IdxNode* n4 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012::IdxNode*>(i4->slice(se7, h3));
          SUPPLIER_CNT_mPART4_E1_1_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long ps_suppkey = e4->PS_SUPPKEY;
              long v4 = e4->__av;
              (/*if */(l2 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se6.modify(ps_suppkey))) ? agg4.addOrDelOnZero(st3.modify(ps_suppkey,v4), v4) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h3 == n4->hash &&  SUPPLIER_CNT_mPART4_E1_1_mapkey012_idxfn::equals(se7, *e4)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i5 = static_cast<HashIndex<tuple2_L_L, long>*>(agg4.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n5; 
          tuple2_L_L* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
              long ps_suppkey = e5->_1;  
              long v5 = e5->__av; 
            agg3 += (v5 != 0 ? 1L : 0L);      
              n5 = n5->nxt;
            }
          }
        }(/*if */(part_brand != c1 && 0L == Upreg_match(preg1,part_type) && ((part_size == 49L) || (part_size == 14L) || (part_size == 23L) || (part_size == 45L) || (part_size == 19L) || (part_size == 3L) || (part_size == 36L) || (part_size == 9L))) ? SUPPLIER_CNT.addOrDelOnZero(se1.modify(part_brand,part_type,part_size),(agg1 + (agg3 * -1L))) : (void)0);
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0* i6 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0*>(SUPPLIER_CNT_mPART4_E1_2.index[1]);
          const HASH_RES_t h4 = SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn::hash(se9.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0::IdxNode* n6 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0::IdxNode*>(i6->slice(se9, h4));
          SUPPLIER_CNT_mPART4_E1_2_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              long ps_suppkey = e6->PS_SUPPKEY;
              long v6 = e6->__av;
              SUPPLIER_CNT_mPART4_E1_1.addOrDelOnZero(se8.modify(part_brand,part_type,part_size,ps_suppkey),v6);
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h4 == n6->hash &&  SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn::equals(se9, *e6)); 
          }
        }SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1.addOrDelOnZero(se10.modify(part_partkey,part_brand,part_type,part_size),1L);
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0* i7 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0*>(SUPPLIER_CNT_mPART4_E1_2.index[1]);
          const HASH_RES_t h5 = SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn::hash(se12.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0::IdxNode* n7 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0::IdxNode*>(i7->slice(se12, h5));
          SUPPLIER_CNT_mPART4_E1_2_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e7->PS_SUPPKEY;
              long v7 = e7->__av;
              (/*if */(part_brand != c1 && 0L == Upreg_match(preg1,part_type) && ((part_size == 49L) || (part_size == 14L) || (part_size == 23L) || (part_size == 45L) || (part_size == 19L) || (part_size == 3L) || (part_size == 36L) || (part_size == 9L))) ? SUPPLIER_CNT_mPARTSUPP1_E1_2.addOrDelOnZero(se11.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),v7) : (void)0);
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h5 == n7->hash &&  SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn::equals(se12, *e7)); 
          }
        }(/*if */(((part_size == 49L) || (part_size == 14L) || (part_size == 23L) || (part_size == 45L) || (part_size == 19L) || (part_size == 3L) || (part_size == 36L) || (part_size == 9L)) && 0L == Upreg_match(preg1,part_type) && part_brand != c1) ? SUPPLIER_CNT_mPARTSUPP1_E1_4.addOrDelOnZero(se13.modify(part_partkey,part_brand,part_type,part_size),1L) : (void)0);
      }
    }
    void on_delete_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  //++tN;
        long agg5 = 0L;
        agg6.clear();
        
        long l3 = 0L;
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012* i8 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012*>(SUPPLIER_CNT_mPART4_E1_1.index[1]);
          const HASH_RES_t h6 = SUPPLIER_CNT_mPART4_E1_1_mapkey012_idxfn::hash(se16.modify012(part_brand, part_type, part_size));
          HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012::IdxNode* n8 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012::IdxNode*>(i8->slice(se16, h6));
          SUPPLIER_CNT_mPART4_E1_1_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              long ps_suppkey = e8->PS_SUPPKEY;
              long v8 = e8->__av;
              (/*if */(l3 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se15.modify(ps_suppkey))) ? agg6.addOrDelOnZero(st4.modify(ps_suppkey,v8), v8) : (void)0);
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h6 == n8->hash &&  SUPPLIER_CNT_mPART4_E1_1_mapkey012_idxfn::equals(se16, *e8)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0* i9 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0*>(SUPPLIER_CNT_mPART4_E1_2.index[1]);
          const HASH_RES_t h7 = SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn::hash(se18.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0::IdxNode* n9 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0::IdxNode*>(i9->slice(se18, h7));
          SUPPLIER_CNT_mPART4_E1_2_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              long ps_suppkey = e9->PS_SUPPKEY;
              long v9 = e9->__av;
              (/*if */(l3 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se17.modify(ps_suppkey))) ? agg6.addOrDelOnZero(st5.modify(ps_suppkey,(v9 * -1L)), (v9 * -1L)) : (void)0);
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h7 == n9->hash &&  SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn::equals(se18, *e9)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i10 = static_cast<HashIndex<tuple2_L_L, long>*>(agg6.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n10; 
          tuple2_L_L* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
              long ps_suppkey = e10->_1;  
              long v10 = e10->__av; 
            agg5 += (v10 != 0 ? 1L : 0L);      
              n10 = n10->nxt;
            }
          }
        }long agg7 = 0L;
        agg8.clear();
        
        long l4 = 0L;
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012* i11 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012*>(SUPPLIER_CNT_mPART4_E1_1.index[1]);
          const HASH_RES_t h8 = SUPPLIER_CNT_mPART4_E1_1_mapkey012_idxfn::hash(se20.modify012(part_brand, part_type, part_size));
          HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012::IdxNode* n11 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_1_map_012::IdxNode*>(i11->slice(se20, h8));
          SUPPLIER_CNT_mPART4_E1_1_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              long ps_suppkey = e11->PS_SUPPKEY;
              long v11 = e11->__av;
              (/*if */(l4 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se19.modify(ps_suppkey))) ? agg8.addOrDelOnZero(st6.modify(ps_suppkey,v11), v11) : (void)0);
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h8 == n11->hash &&  SUPPLIER_CNT_mPART4_E1_1_mapkey012_idxfn::equals(se20, *e11)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i12 = static_cast<HashIndex<tuple2_L_L, long>*>(agg8.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n12; 
          tuple2_L_L* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
              long ps_suppkey = e12->_1;  
              long v12 = e12->__av; 
            agg7 += (v12 != 0 ? 1L : 0L);      
              n12 = n12->nxt;
            }
          }
        }(/*if */(part_brand != c1 && 0L == Upreg_match(preg1,part_type) && ((part_size == 49L) || (part_size == 14L) || (part_size == 23L) || (part_size == 45L) || (part_size == 19L) || (part_size == 3L) || (part_size == 36L) || (part_size == 9L))) ? SUPPLIER_CNT.addOrDelOnZero(se14.modify(part_brand,part_type,part_size),(agg5 + (agg7 * -1L))) : (void)0);
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0* i13 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0*>(SUPPLIER_CNT_mPART4_E1_2.index[1]);
          const HASH_RES_t h9 = SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn::hash(se22.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0::IdxNode* n13 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0::IdxNode*>(i13->slice(se22, h9));
          SUPPLIER_CNT_mPART4_E1_2_entry* e13;
         
          if (n13 && (e13 = n13->obj)) {
            do {                
              long ps_suppkey = e13->PS_SUPPKEY;
              long v13 = e13->__av;
              SUPPLIER_CNT_mPART4_E1_1.addOrDelOnZero(se21.modify(part_brand,part_type,part_size,ps_suppkey),(v13 * -1L));
              n13 = n13->nxt;
            } while (n13 && (e13 = n13->obj) && h9 == n13->hash &&  SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn::equals(se22, *e13)); 
          }
        }SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1.addOrDelOnZero(se23.modify(part_partkey,part_brand,part_type,part_size),-1L);
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0* i14 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0*>(SUPPLIER_CNT_mPART4_E1_2.index[1]);
          const HASH_RES_t h10 = SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn::hash(se25.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0::IdxNode* n14 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_2_map_0::IdxNode*>(i14->slice(se25, h10));
          SUPPLIER_CNT_mPART4_E1_2_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e14->PS_SUPPKEY;
              long v14 = e14->__av;
              (/*if */(part_brand != c1 && 0L == Upreg_match(preg1,part_type) && ((part_size == 49L) || (part_size == 14L) || (part_size == 23L) || (part_size == 45L) || (part_size == 19L) || (part_size == 3L) || (part_size == 36L) || (part_size == 9L))) ? SUPPLIER_CNT_mPARTSUPP1_E1_2.addOrDelOnZero(se24.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),(v14 * -1L)) : (void)0);
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h10 == n14->hash &&  SUPPLIER_CNT_mPART4_E1_2_mapkey0_idxfn::equals(se25, *e14)); 
          }
        }(/*if */(((part_size == 49L) || (part_size == 14L) || (part_size == 23L) || (part_size == 45L) || (part_size == 19L) || (part_size == 3L) || (part_size == 36L) || (part_size == 9L)) && 0L == Upreg_match(preg1,part_type) && part_brand != c1) ? SUPPLIER_CNT_mPARTSUPP1_E1_4.addOrDelOnZero(se26.modify(part_partkey,part_brand,part_type,part_size),-1L) : (void)0);
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  //++tN;
        agg9.clear();
        
        long l5 = (SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se28.modify(supplier_suppkey)) + (/*if */(0L != Upreg_match(preg2,supplier_comment)) ? 1L : 0L));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i15 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h11 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se29.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n15 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i15->slice(se29, h11));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e15;
         
          if (n15 && (e15 = n15->obj)) {
            do {                
              STRING_TYPE p_brand = e15->P_BRAND;
              STRING_TYPE p_type = e15->P_TYPE;
              long p_size = e15->P_SIZE;
              long v15 = e15->__av;
              (/*if */(l5 == 0L) ? agg9.addOrDelOnZero(st7.modify(p_brand,p_type,p_size,v15), v15) : (void)0);
              n15 = n15->nxt;
            } while (n15 && (e15 = n15->obj) && h11 == n15->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se29, *e15)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i16 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg9.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n16; 
          tuple4_SSL_L* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
              STRING_TYPE p_brand = e16->_1;
              STRING_TYPE p_type = e16->_2;
              long p_size = e16->_3;  
              long v16 = e16->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se27.modify(p_brand,p_type,p_size),(v16 != 0 ? 1L : 0L));      
              n16 = n16->nxt;
            }
          }
        }agg10.clear();
        
        long l6 = SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se30.modify(supplier_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i17 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h12 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se31.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n17 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i17->slice(se31, h12));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e17;
         
          if (n17 && (e17 = n17->obj)) {
            do {                
              STRING_TYPE p_brand = e17->P_BRAND;
              STRING_TYPE p_type = e17->P_TYPE;
              long p_size = e17->P_SIZE;
              long v17 = e17->__av;
              (/*if */(l6 == 0L) ? agg10.addOrDelOnZero(st8.modify(p_brand,p_type,p_size,v17), v17) : (void)0);
              n17 = n17->nxt;
            } while (n17 && (e17 = n17->obj) && h12 == n17->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se31, *e17)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i18 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg10.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n18; 
          tuple4_SSL_L* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
              STRING_TYPE p_brand = e18->_1;
              STRING_TYPE p_type = e18->_2;
              long p_size = e18->_3;  
              long v18 = e18->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se27.modify(p_brand,p_type,p_size),((v18 != 0 ? 1L : 0L) * -1L));      
              n18 = n18->nxt;
            }
          }
        }(/*if */(0L != Upreg_match(preg2,supplier_comment)) ? SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.addOrDelOnZero(se32.modify(supplier_suppkey),1L) : (void)0);
      }
    }
    void on_delete_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  //++tN;
        agg11.clear();
        
        long l7 = (SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se34.modify(supplier_suppkey)) + (/*if */(0L != Upreg_match(preg2,supplier_comment)) ? -1L : 0L));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i19 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h13 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se35.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n19 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i19->slice(se35, h13));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e19;
         
          if (n19 && (e19 = n19->obj)) {
            do {                
              STRING_TYPE p_brand = e19->P_BRAND;
              STRING_TYPE p_type = e19->P_TYPE;
              long p_size = e19->P_SIZE;
              long v19 = e19->__av;
              (/*if */(l7 == 0L) ? agg11.addOrDelOnZero(st9.modify(p_brand,p_type,p_size,v19), v19) : (void)0);
              n19 = n19->nxt;
            } while (n19 && (e19 = n19->obj) && h13 == n19->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se35, *e19)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i20 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg11.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n20; 
          tuple4_SSL_L* e20;
        
          for (size_t i = 0; i < i20->size_; i++)
          {
            n20 = i20->buckets_ + i;
            while (n20 && (e20 = n20->obj))
            {
              STRING_TYPE p_brand = e20->_1;
              STRING_TYPE p_type = e20->_2;
              long p_size = e20->_3;  
              long v20 = e20->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se33.modify(p_brand,p_type,p_size),(v20 != 0 ? 1L : 0L));      
              n20 = n20->nxt;
            }
          }
        }agg12.clear();
        
        long l8 = SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se36.modify(supplier_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i21 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h14 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se37.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n21 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i21->slice(se37, h14));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e21;
         
          if (n21 && (e21 = n21->obj)) {
            do {                
              STRING_TYPE p_brand = e21->P_BRAND;
              STRING_TYPE p_type = e21->P_TYPE;
              long p_size = e21->P_SIZE;
              long v21 = e21->__av;
              (/*if */(l8 == 0L) ? agg12.addOrDelOnZero(st10.modify(p_brand,p_type,p_size,v21), v21) : (void)0);
              n21 = n21->nxt;
            } while (n21 && (e21 = n21->obj) && h14 == n21->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se37, *e21)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i22 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg12.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n22; 
          tuple4_SSL_L* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
              STRING_TYPE p_brand = e22->_1;
              STRING_TYPE p_type = e22->_2;
              long p_size = e22->_3;  
              long v22 = e22->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se33.modify(p_brand,p_type,p_size),((v22 != 0 ? 1L : 0L) * -1L));      
              n22 = n22->nxt;
            }
          }
        }(/*if */(0L != Upreg_match(preg2,supplier_comment)) ? SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.addOrDelOnZero(se38.modify(supplier_suppkey),-1L) : (void)0);
      }
    }
    void on_insert_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  //++tN;
        agg13.clear();
        
        long l9 = SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se40.modify(partsupp_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i23 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h15 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se41.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n23 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i23->slice(se41, h15));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e23;
         
          if (n23 && (e23 = n23->obj)) {
            do {                
              STRING_TYPE p_brand = e23->P_BRAND;
              STRING_TYPE p_type = e23->P_TYPE;
              long p_size = e23->P_SIZE;
              long v23 = e23->__av;
              (/*if */(l9 == 0L) ? agg13.addOrDelOnZero(st11.modify(p_brand,p_type,p_size,v23), v23) : (void)0);
              n23 = n23->nxt;
            } while (n23 && (e23 = n23->obj) && h15 == n23->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se41, *e23)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0* i24 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h16 = SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::hash(se42.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode* n24 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode*>(i24->slice(se42, h16));
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              STRING_TYPE p_brand = e24->P_BRAND;
              STRING_TYPE p_type = e24->P_TYPE;
              long p_size = e24->P_SIZE;
              long v24 = e24->__av;
              (/*if */(l9 == 0L) ? agg13.addOrDelOnZero(st12.modify(p_brand,p_type,p_size,v24), v24) : (void)0);
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h16 == n24->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::equals(se42, *e24)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i25 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg13.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n25; 
          tuple4_SSL_L* e25;
        
          for (size_t i = 0; i < i25->size_; i++)
          {
            n25 = i25->buckets_ + i;
            while (n25 && (e25 = n25->obj))
            {
              STRING_TYPE p_brand = e25->_1;
              STRING_TYPE p_type = e25->_2;
              long p_size = e25->_3;  
              long v25 = e25->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se39.modify(p_brand,p_type,p_size),(v25 != 0 ? 1L : 0L));      
              n25 = n25->nxt;
            }
          }
        }agg14.clear();
        
        long l10 = SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se43.modify(partsupp_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i26 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h17 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se44.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n26 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i26->slice(se44, h17));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e26;
         
          if (n26 && (e26 = n26->obj)) {
            do {                
              STRING_TYPE p_brand = e26->P_BRAND;
              STRING_TYPE p_type = e26->P_TYPE;
              long p_size = e26->P_SIZE;
              long v26 = e26->__av;
              (/*if */(l10 == 0L) ? agg14.addOrDelOnZero(st13.modify(p_brand,p_type,p_size,v26), v26) : (void)0);
              n26 = n26->nxt;
            } while (n26 && (e26 = n26->obj) && h17 == n26->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se44, *e26)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i27 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg14.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n27; 
          tuple4_SSL_L* e27;
        
          for (size_t i = 0; i < i27->size_; i++)
          {
            n27 = i27->buckets_ + i;
            while (n27 && (e27 = n27->obj))
            {
              STRING_TYPE p_brand = e27->_1;
              STRING_TYPE p_type = e27->_2;
              long p_size = e27->_3;  
              long v27 = e27->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se39.modify(p_brand,p_type,p_size),((v27 != 0 ? 1L : 0L) * -1L));      
              n27 = n27->nxt;
            }
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_map_0* i28 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_map_0*>(SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1.index[1]);
          const HASH_RES_t h18 = SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_mapkey0_idxfn::hash(se46.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_map_0::IdxNode* n28 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_map_0::IdxNode*>(i28->slice(se46, h18));
          SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry* e28;
         
          if (n28 && (e28 = n28->obj)) {
            do {                
              STRING_TYPE supplier_cnt_mpartpart_brand = e28->SUPPLIER_CNT_mPARTPART_BRAND;
              STRING_TYPE supplier_cnt_mpartpart_type = e28->SUPPLIER_CNT_mPARTPART_TYPE;
              long supplier_cnt_mpartpart_size = e28->SUPPLIER_CNT_mPARTPART_SIZE;
              long v28 = e28->__av;
              SUPPLIER_CNT_mPART4_E1_1.addOrDelOnZero(se45.modify(supplier_cnt_mpartpart_brand,supplier_cnt_mpartpart_type,supplier_cnt_mpartpart_size,partsupp_suppkey),v28);
              n28 = n28->nxt;
            } while (n28 && (e28 = n28->obj) && h18 == n28->hash &&  SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_mapkey0_idxfn::equals(se46, *e28)); 
          }
        }SUPPLIER_CNT_mPART4_E1_2.addOrDelOnZero(se47.modify(partsupp_partkey,partsupp_suppkey),1L);
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0* i29 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h19 = SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::hash(se49.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode* n29 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode*>(i29->slice(se49, h19));
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e29;
         
          if (n29 && (e29 = n29->obj)) {
            do {                
              STRING_TYPE p_brand = e29->P_BRAND;
              STRING_TYPE p_type = e29->P_TYPE;
              long p_size = e29->P_SIZE;
              long v29 = e29->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_2.addOrDelOnZero(se48.modify(partsupp_suppkey,p_brand,p_type,p_size),v29);
              n29 = n29->nxt;
            } while (n29 && (e29 = n29->obj) && h19 == n29->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::equals(se49, *e29)); 
          }
        }
      }
    }
    void on_delete_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  //++tN;
        agg15.clear();
        
        long l11 = SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se51.modify(partsupp_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i30 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h20 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se52.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n30 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i30->slice(se52, h20));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e30;
         
          if (n30 && (e30 = n30->obj)) {
            do {                
              STRING_TYPE p_brand = e30->P_BRAND;
              STRING_TYPE p_type = e30->P_TYPE;
              long p_size = e30->P_SIZE;
              long v30 = e30->__av;
              (/*if */(l11 == 0L) ? agg15.addOrDelOnZero(st14.modify(p_brand,p_type,p_size,v30), v30) : (void)0);
              n30 = n30->nxt;
            } while (n30 && (e30 = n30->obj) && h20 == n30->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se52, *e30)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0* i31 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h21 = SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::hash(se53.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode* n31 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode*>(i31->slice(se53, h21));
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e31;
         
          if (n31 && (e31 = n31->obj)) {
            do {                
              STRING_TYPE p_brand = e31->P_BRAND;
              STRING_TYPE p_type = e31->P_TYPE;
              long p_size = e31->P_SIZE;
              long v31 = e31->__av;
              (/*if */(l11 == 0L) ? agg15.addOrDelOnZero(st15.modify(p_brand,p_type,p_size,(v31 * -1L)), (v31 * -1L)) : (void)0);
              n31 = n31->nxt;
            } while (n31 && (e31 = n31->obj) && h21 == n31->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::equals(se53, *e31)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i32 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg15.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n32; 
          tuple4_SSL_L* e32;
        
          for (size_t i = 0; i < i32->size_; i++)
          {
            n32 = i32->buckets_ + i;
            while (n32 && (e32 = n32->obj))
            {
              STRING_TYPE p_brand = e32->_1;
              STRING_TYPE p_type = e32->_2;
              long p_size = e32->_3;  
              long v32 = e32->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se50.modify(p_brand,p_type,p_size),(v32 != 0 ? 1L : 0L));      
              n32 = n32->nxt;
            }
          }
        }agg16.clear();
        
        long l12 = SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se54.modify(partsupp_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i33 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h22 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se55.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n33 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i33->slice(se55, h22));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e33;
         
          if (n33 && (e33 = n33->obj)) {
            do {                
              STRING_TYPE p_brand = e33->P_BRAND;
              STRING_TYPE p_type = e33->P_TYPE;
              long p_size = e33->P_SIZE;
              long v33 = e33->__av;
              (/*if */(l12 == 0L) ? agg16.addOrDelOnZero(st16.modify(p_brand,p_type,p_size,v33), v33) : (void)0);
              n33 = n33->nxt;
            } while (n33 && (e33 = n33->obj) && h22 == n33->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se55, *e33)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i34 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg16.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n34; 
          tuple4_SSL_L* e34;
        
          for (size_t i = 0; i < i34->size_; i++)
          {
            n34 = i34->buckets_ + i;
            while (n34 && (e34 = n34->obj))
            {
              STRING_TYPE p_brand = e34->_1;
              STRING_TYPE p_type = e34->_2;
              long p_size = e34->_3;  
              long v34 = e34->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se50.modify(p_brand,p_type,p_size),((v34 != 0 ? 1L : 0L) * -1L));      
              n34 = n34->nxt;
            }
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_map_0* i35 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_map_0*>(SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1.index[1]);
          const HASH_RES_t h23 = SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_mapkey0_idxfn::hash(se57.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_map_0::IdxNode* n35 = static_cast<HashIndex_SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_map_0::IdxNode*>(i35->slice(se57, h23));
          SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry* e35;
         
          if (n35 && (e35 = n35->obj)) {
            do {                
              STRING_TYPE supplier_cnt_mpartpart_brand = e35->SUPPLIER_CNT_mPARTPART_BRAND;
              STRING_TYPE supplier_cnt_mpartpart_type = e35->SUPPLIER_CNT_mPARTPART_TYPE;
              long supplier_cnt_mpartpart_size = e35->SUPPLIER_CNT_mPARTPART_SIZE;
              long v35 = e35->__av;
              SUPPLIER_CNT_mPART4_E1_1.addOrDelOnZero(se56.modify(supplier_cnt_mpartpart_brand,supplier_cnt_mpartpart_type,supplier_cnt_mpartpart_size,partsupp_suppkey),(v35 * -1L));
              n35 = n35->nxt;
            } while (n35 && (e35 = n35->obj) && h23 == n35->hash &&  SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_mapkey0_idxfn::equals(se57, *e35)); 
          }
        }SUPPLIER_CNT_mPART4_E1_2.addOrDelOnZero(se58.modify(partsupp_partkey,partsupp_suppkey),-1L);
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0* i36 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h24 = SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::hash(se60.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode* n36 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode*>(i36->slice(se60, h24));
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e36;
         
          if (n36 && (e36 = n36->obj)) {
            do {                
              STRING_TYPE p_brand = e36->P_BRAND;
              STRING_TYPE p_type = e36->P_TYPE;
              long p_size = e36->P_SIZE;
              long v36 = e36->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_2.addOrDelOnZero(se59.modify(partsupp_suppkey,p_brand,p_type,p_size),(v36 * -1L));
              n36 = n36->nxt;
            } while (n36 && (e36 = n36->obj) && h24 == n36->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::equals(se60, *e36)); 
          }
        }
      }
    }
    void on_system_ready_event() {
      {  //
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    SUPPLIER_CNT_entry se1;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se2;
    tuple2_L_L st1;
    SUPPLIER_CNT_mPART4_E1_1_entry se3;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se4;
    tuple2_L_L st2;
    SUPPLIER_CNT_mPART4_E1_2_entry se5;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se6;
    tuple2_L_L st3;
    SUPPLIER_CNT_mPART4_E1_1_entry se7;
    SUPPLIER_CNT_mPART4_E1_1_entry se8;
    SUPPLIER_CNT_mPART4_E1_2_entry se9;
    SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry se10;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se11;
    SUPPLIER_CNT_mPART4_E1_2_entry se12;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se13;
    SUPPLIER_CNT_entry se14;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se15;
    tuple2_L_L st4;
    SUPPLIER_CNT_mPART4_E1_1_entry se16;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se17;
    tuple2_L_L st5;
    SUPPLIER_CNT_mPART4_E1_2_entry se18;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se19;
    tuple2_L_L st6;
    SUPPLIER_CNT_mPART4_E1_1_entry se20;
    SUPPLIER_CNT_mPART4_E1_1_entry se21;
    SUPPLIER_CNT_mPART4_E1_2_entry se22;
    SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry se23;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se24;
    SUPPLIER_CNT_mPART4_E1_2_entry se25;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se26;
    SUPPLIER_CNT_entry se27;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se28;
    tuple4_SSL_L st7;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se29;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se30;
    tuple4_SSL_L st8;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se31;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se32;
    SUPPLIER_CNT_entry se33;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se34;
    tuple4_SSL_L st9;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se35;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se36;
    tuple4_SSL_L st10;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se37;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se38;
    SUPPLIER_CNT_entry se39;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se40;
    tuple4_SSL_L st11;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se41;
    tuple4_SSL_L st12;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se42;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se43;
    tuple4_SSL_L st13;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se44;
    SUPPLIER_CNT_mPART4_E1_1_entry se45;
    SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry se46;
    SUPPLIER_CNT_mPART4_E1_2_entry se47;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se48;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se49;
    SUPPLIER_CNT_entry se50;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se51;
    tuple4_SSL_L st14;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se52;
    tuple4_SSL_L st15;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se53;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se54;
    tuple4_SSL_L st16;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se55;
    SUPPLIER_CNT_mPART4_E1_1_entry se56;
    SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_entry se57;
    SUPPLIER_CNT_mPART4_E1_2_entry se58;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se59;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se60;
    /* regex_t temporary objects */
    regex_t preg2;
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    SUPPLIER_CNT_mPART4_E1_1_map SUPPLIER_CNT_mPART4_E1_1;
    SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1_map SUPPLIER_CNT_mPART4_E1_1_mPARTSUPP1;
    SUPPLIER_CNT_mPART4_E1_2_map SUPPLIER_CNT_mPART4_E1_2;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_map SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_map SUPPLIER_CNT_mPARTSUPP1_E1_2;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_map SUPPLIER_CNT_mPARTSUPP1_E1_4;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg11;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg6;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg13;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg8;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg16;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg2;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg10;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg4;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg12;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg15;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg14;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg9;
    /*const static*/ STRING_TYPE c1;
  
  };

}
