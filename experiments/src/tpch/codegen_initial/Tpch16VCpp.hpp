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
  
  struct SUPPLIER_CNT_mPART3_E1_1_entry {
    long PS_SUPPKEY; STRING_TYPE SUPPLIER_CNT_mPARTPART_BRAND; STRING_TYPE SUPPLIER_CNT_mPARTPART_TYPE; long SUPPLIER_CNT_mPARTPART_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPART3_E1_1_entry() { /*PS_SUPPKEY = 0L; SUPPLIER_CNT_mPARTPART_BRAND = ""; SUPPLIER_CNT_mPARTPART_TYPE = ""; SUPPLIER_CNT_mPARTPART_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPART3_E1_1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { PS_SUPPKEY = c0; SUPPLIER_CNT_mPARTPART_BRAND = c1; SUPPLIER_CNT_mPARTPART_TYPE = c2; SUPPLIER_CNT_mPARTPART_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPART3_E1_1_entry(const SUPPLIER_CNT_mPART3_E1_1_entry& other) : PS_SUPPKEY( other.PS_SUPPKEY ), SUPPLIER_CNT_mPARTPART_BRAND( other.SUPPLIER_CNT_mPARTPART_BRAND ), SUPPLIER_CNT_mPARTPART_TYPE( other.SUPPLIER_CNT_mPARTPART_TYPE ), SUPPLIER_CNT_mPARTPART_SIZE( other.SUPPLIER_CNT_mPARTPART_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPART3_E1_1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { PS_SUPPKEY = c0; SUPPLIER_CNT_mPARTPART_BRAND = c1; SUPPLIER_CNT_mPARTPART_TYPE = c2; SUPPLIER_CNT_mPARTPART_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPART3_E1_1_entry& modify123(const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTPART_BRAND = c1; SUPPLIER_CNT_mPARTPART_TYPE = c2; SUPPLIER_CNT_mPARTPART_SIZE = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
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
  struct SUPPLIER_CNT_mPART3_E1_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPART3_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_SUPPKEY);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_BRAND);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_TYPE);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPART3_E1_1_entry& x, const SUPPLIER_CNT_mPART3_E1_1_entry& y) {
      return x.PS_SUPPKEY == y.PS_SUPPKEY && x.SUPPLIER_CNT_mPARTPART_BRAND == y.SUPPLIER_CNT_mPARTPART_BRAND && x.SUPPLIER_CNT_mPARTPART_TYPE == y.SUPPLIER_CNT_mPARTPART_TYPE && x.SUPPLIER_CNT_mPARTPART_SIZE == y.SUPPLIER_CNT_mPARTPART_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPART3_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_BRAND);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_TYPE);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPART3_E1_1_entry& x, const SUPPLIER_CNT_mPART3_E1_1_entry& y) {
      return x.SUPPLIER_CNT_mPARTPART_BRAND == y.SUPPLIER_CNT_mPARTPART_BRAND && x.SUPPLIER_CNT_mPARTPART_TYPE == y.SUPPLIER_CNT_mPARTPART_TYPE && x.SUPPLIER_CNT_mPARTPART_SIZE == y.SUPPLIER_CNT_mPARTPART_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPART3_E1_1_entry,long,
    HashIndex<SUPPLIER_CNT_mPART3_E1_1_entry,long,SUPPLIER_CNT_mPART3_E1_1_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPART3_E1_1_entry,long,SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn,false>
  > SUPPLIER_CNT_mPART3_E1_1_map;
  typedef HashIndex<SUPPLIER_CNT_mPART3_E1_1_entry,long,SUPPLIER_CNT_mPART3_E1_1_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPART3_E1_1_entry,long,SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn,false> HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123;
  
  struct SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry {
    long SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE SUPPLIER_CNT_mPARTPART_BRAND; STRING_TYPE SUPPLIER_CNT_mPARTPART_TYPE; long SUPPLIER_CNT_mPARTPART_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry() { /*SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY = 0L; SUPPLIER_CNT_mPARTPART_BRAND = ""; SUPPLIER_CNT_mPARTPART_TYPE = ""; SUPPLIER_CNT_mPARTPART_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY = c0; SUPPLIER_CNT_mPARTPART_BRAND = c1; SUPPLIER_CNT_mPARTPART_TYPE = c2; SUPPLIER_CNT_mPARTPART_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry(const SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry& other) : SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY ), SUPPLIER_CNT_mPARTPART_BRAND( other.SUPPLIER_CNT_mPARTPART_BRAND ), SUPPLIER_CNT_mPARTPART_TYPE( other.SUPPLIER_CNT_mPARTPART_TYPE ), SUPPLIER_CNT_mPARTPART_SIZE( other.SUPPLIER_CNT_mPARTPART_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY = c0; SUPPLIER_CNT_mPARTPART_BRAND = c1; SUPPLIER_CNT_mPARTPART_TYPE = c2; SUPPLIER_CNT_mPARTPART_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry& modify0(const long c0) { SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY);
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
  struct SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_BRAND);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_TYPE);
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry& x, const SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry& y) {
      return x.SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY && x.SUPPLIER_CNT_mPARTPART_BRAND == y.SUPPLIER_CNT_mPARTPART_BRAND && x.SUPPLIER_CNT_mPARTPART_TYPE == y.SUPPLIER_CNT_mPARTPART_TYPE && x.SUPPLIER_CNT_mPARTPART_SIZE == y.SUPPLIER_CNT_mPARTPART_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry& x, const SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry& y) {
      return x.SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPART3_E1_1_mPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry,long,
    HashIndex<SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry,long,SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry,long,SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_map;
  typedef HashIndex<SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry,long,SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry,long,SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_map_0;
  
  struct SUPPLIER_CNT_mPART3_E1_17_entry {
    long SUPPLIER_CNT_mPARTPART_PARTKEY; long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNT_mPART3_E1_17_entry() { /*SUPPLIER_CNT_mPARTPART_PARTKEY = 0L; PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPART3_E1_17_entry(const long c0, const long c1, const long c2) { SUPPLIER_CNT_mPARTPART_PARTKEY = c0; PS_SUPPKEY = c1; __av = c2; }
    SUPPLIER_CNT_mPART3_E1_17_entry(const SUPPLIER_CNT_mPART3_E1_17_entry& other) : SUPPLIER_CNT_mPARTPART_PARTKEY( other.SUPPLIER_CNT_mPARTPART_PARTKEY ), PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPART3_E1_17_entry& modify(const long c0, const long c1) { SUPPLIER_CNT_mPARTPART_PARTKEY = c0; PS_SUPPKEY = c1;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPART3_E1_17_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTPART_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPART3_E1_17_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPART3_E1_17_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_PARTKEY);
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPART3_E1_17_entry& x, const SUPPLIER_CNT_mPART3_E1_17_entry& y) {
      return x.SUPPLIER_CNT_mPARTPART_PARTKEY == y.SUPPLIER_CNT_mPARTPART_PARTKEY && x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  struct SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPART3_E1_17_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPART3_E1_17_entry& x, const SUPPLIER_CNT_mPART3_E1_17_entry& y) {
      return x.SUPPLIER_CNT_mPARTPART_PARTKEY == y.SUPPLIER_CNT_mPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPART3_E1_17_entry,long,
    HashIndex<SUPPLIER_CNT_mPART3_E1_17_entry,long,SUPPLIER_CNT_mPART3_E1_17_mapkey01_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPART3_E1_17_entry,long,SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPART3_E1_17_map;
  typedef HashIndex<SUPPLIER_CNT_mPART3_E1_17_entry,long,SUPPLIER_CNT_mPART3_E1_17_mapkey01_idxfn,true> HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_01;
  typedef HashIndex<SUPPLIER_CNT_mPART3_E1_17_entry,long,SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0;
  
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
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_4_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_4_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_4_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_4_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_4_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_4_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_4_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_4_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_4_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_6_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_6_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_6_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_6_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_6_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_6_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_6_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_6_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_6_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_6_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_6_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_6_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_6_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_6_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_6_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_6_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_8_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_8_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_8_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_8_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_8_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_8_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_8_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_8_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_8_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_8_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_8_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_8_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_8_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_8_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_8_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_8_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_8_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_8_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_10_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_10_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_10_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_10_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_10_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_10_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_10_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_10_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_10_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_10_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_10_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_10_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_10_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_10_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_10_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_10_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_10_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_10_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_12_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_12_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_12_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_12_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_12_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_12_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_12_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_12_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_12_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_12_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_12_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_12_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_12_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_12_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_12_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_12_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_12_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_12_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_14_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_14_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_14_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_14_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_14_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_14_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_14_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_14_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_14_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_14_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_14_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_14_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_14_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_14_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_14_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_14_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_14_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_14_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_16_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_16_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_16_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_16_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_16_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_16_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_16_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_16_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_16_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_16_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_16_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_16_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_16_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_16_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_16_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_16_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_16_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_16_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_17_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_17_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_17_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_17_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_17_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_17_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_17_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_17_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_17_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_17_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_17_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_17_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_17_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_17_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_17_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_17_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_17_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_17_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_17_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_20_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_20_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_20_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_20_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_20_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_20_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_20_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_20_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_20_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_20_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_20_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_20_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_20_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_20_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_20_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_20_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_20_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_20_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_20_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_23_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_23_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_23_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_23_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_23_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_23_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_23_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_23_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_23_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_23_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_23_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_23_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_23_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_23_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_23_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_23_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_23_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_23_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_23_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_26_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_26_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_26_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_26_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_26_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_26_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_26_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_26_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_26_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_26_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_26_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_26_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_26_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_26_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_26_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_26_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_26_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_26_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_26_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_29_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_29_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_29_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_29_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_29_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_29_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_29_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_29_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_29_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_29_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_29_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_29_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_29_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_29_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_29_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_29_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_29_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_29_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_29_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_32_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_32_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_32_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_32_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_32_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_32_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_32_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_32_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_32_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_32_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_32_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_32_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_32_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_32_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_32_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_32_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_32_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_32_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_32_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_35_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_35_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_35_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_35_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_35_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_35_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_35_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_35_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_35_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_35_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_35_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_35_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_35_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_35_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_35_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_35_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_35_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_35_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_35_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0;
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_38_entry {
    long SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_38_entry() { /*SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNT_mPARTSUPP1_E1_38_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNT_mPARTSUPP1_E1_38_entry(const SUPPLIER_CNT_mPARTSUPP1_E1_38_entry& other) : SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_38_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNT_mPARTSUPP1_E1_38_entry& modify0(const long c0) { SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
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
  struct SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_38_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_38_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_38_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNT_mPARTSUPP1_E1_38_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNT_mPARTSUPP1_E1_38_entry& x, const SUPPLIER_CNT_mPARTSUPP1_E1_38_entry& y) {
      return x.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNT_mPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNT_mPARTSUPP1_E1_38_entry,long,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_38_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_38_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0_idxfn,false>
  > SUPPLIER_CNT_mPARTSUPP1_E1_38_map;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_38_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0123;
  typedef HashIndex<SUPPLIER_CNT_mPARTSUPP1_E1_38_entry,long,SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0;
  
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
  struct tuple5_LSSL_L {
    long _1; STRING_TYPE _2; STRING_TYPE _3; long _4; long __av;
    explicit tuple5_LSSL_L() { }
    explicit tuple5_LSSL_L(const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; __av = c__av;}
    int operator==(const tuple5_LSSL_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4)); }
    FORCE_INLINE tuple5_LSSL_L& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; __av = c__av; return *this; }
    static bool equals(const tuple5_LSSL_L &x, const tuple5_LSSL_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4)); }
    static long hash(const tuple5_LSSL_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
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
    data_t(): tlq_t(), agg26(16U), agg6(16U), agg19(16U), agg25(16U), agg13(16U), agg28(16U), agg8(16U), agg16(16U), agg22(16U), agg2(16U), agg10(16U), agg21(16U), agg24(16U), agg4(16U), agg18(16U), agg27(16U), agg12(16U), agg15(16U), agg20(16U), agg14(16U), agg17(16U), agg23(16U) {
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
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg1 = 0L;
        agg2.clear();
        
        long l1 = 0L;
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123* i1 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123*>(SUPPLIER_CNT_mPART3_E1_1.index[1]);
          const HASH_RES_t h1 = SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn::hash(se3.modify123(part_brand, part_type, part_size));
          HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123::IdxNode* n1 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123::IdxNode*>(i1->slice(se3, h1));
          SUPPLIER_CNT_mPART3_E1_1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long ps_suppkey = e1->PS_SUPPKEY;
              long v1 = e1->__av;
              (/*if */(l1 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se2.modify(ps_suppkey)) && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? agg2.addOrDelOnZero(st1.modify(ps_suppkey,(v1 * ((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))))), (v1 * ((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))))) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn::equals(se3, *e1)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i2 = static_cast<HashIndex<tuple2_L_L, long>*>(agg2.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n2; 
          tuple2_L_L* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
              long ps_suppkey = e2->_1;  
              long v2 = e2->__av; 
            agg1 += (v2 != 0 ? 1L : 0L);      
              n2 = n2->nxt;
            }
          }
        }if (SUPPLIER_CNT.getValueOrDefault(se1.modify(part_brand,part_type,part_size))==0) SUPPLIER_CNT.setOrDelOnZero(se1, agg1);
        long agg3 = 0L;
        agg4.clear();
        
        long l2 = 0L;
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123* i3 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123*>(SUPPLIER_CNT_mPART3_E1_1.index[1]);
          const HASH_RES_t h2 = SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn::hash(se5.modify123(part_brand, part_type, part_size));
          HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123::IdxNode* n3 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123::IdxNode*>(i3->slice(se5, h2));
          SUPPLIER_CNT_mPART3_E1_1_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              long ps_suppkey = e3->PS_SUPPKEY;
              long v3 = e3->__av;
              (/*if */(l2 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se4.modify(ps_suppkey))) ? agg4.addOrDelOnZero(st2.modify(ps_suppkey,(((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))) * v3)), (((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))) * v3)) : (void)0);
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h2 == n3->hash &&  SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn::equals(se5, *e3)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i4 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h3 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se7.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n4 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i4->slice(se7, h3));
          SUPPLIER_CNT_mPART3_E1_17_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long ps_suppkey = e4->PS_SUPPKEY;
              long v4 = e4->__av;
              (/*if */(l2 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se6.modify(ps_suppkey))) ? agg4.addOrDelOnZero(st3.modify(ps_suppkey,(((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))) * v4)), (((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))) * v4)) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h3 == n4->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se7, *e4)); 
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
        }long agg5 = 0L;
        agg6.clear();
        
        long l3 = 0L;
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123* i6 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123*>(SUPPLIER_CNT_mPART3_E1_1.index[1]);
          const HASH_RES_t h4 = SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn::hash(se9.modify123(part_brand, part_type, part_size));
          HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123::IdxNode* n6 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123::IdxNode*>(i6->slice(se9, h4));
          SUPPLIER_CNT_mPART3_E1_1_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              long ps_suppkey = e6->PS_SUPPKEY;
              long v6 = e6->__av;
              (/*if */(l3 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se8.modify(ps_suppkey))) ? agg6.addOrDelOnZero(st4.modify(ps_suppkey,(v6 * ((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))))), (v6 * ((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))))) : (void)0);
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h4 == n6->hash &&  SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn::equals(se9, *e6)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i7 = static_cast<HashIndex<tuple2_L_L, long>*>(agg6.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n7; 
          tuple2_L_L* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
              long ps_suppkey = e7->_1;  
              long v7 = e7->__av; 
            agg5 += (v7 != 0 ? 1L : 0L);      
              n7 = n7->nxt;
            }
          }
        }(/*if */(part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT.addOrDelOnZero(se1.modify(part_brand,part_type,part_size),(agg3 + (agg5 * -1L))) : (void)0);
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i8 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h5 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se11.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n8 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i8->slice(se11, h5));
          SUPPLIER_CNT_mPART3_E1_17_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              long ps_suppkey = e8->PS_SUPPKEY;
              long v8 = e8->__av;
              SUPPLIER_CNT_mPART3_E1_1.addOrDelOnZero(se10.modify(ps_suppkey,part_brand,part_type,part_size),v8);
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h5 == n8->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se11, *e8)); 
          }
        }SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1.addOrDelOnZero(se12.modify(part_partkey,part_brand,part_type,part_size),1L);
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i9 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h6 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se14.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n9 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i9->slice(se14, h6));
          SUPPLIER_CNT_mPART3_E1_17_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e9->PS_SUPPKEY;
              long v9 = e9->__av;
              (/*if */(part_size == 49L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_2.addOrDelOnZero(se13.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),v9) : (void)0);
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h6 == n9->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se14, *e9)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i10 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h7 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se16.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n10 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i10->slice(se16, h7));
          SUPPLIER_CNT_mPART3_E1_17_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e10->PS_SUPPKEY;
              long v10 = e10->__av;
              (/*if */(part_size == 14L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_4.addOrDelOnZero(se15.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),v10) : (void)0);
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h7 == n10->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se16, *e10)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i11 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h8 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se18.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n11 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i11->slice(se18, h8));
          SUPPLIER_CNT_mPART3_E1_17_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e11->PS_SUPPKEY;
              long v11 = e11->__av;
              (/*if */(part_size == 23L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_6.addOrDelOnZero(se17.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),v11) : (void)0);
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h8 == n11->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se18, *e11)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i12 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h9 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se20.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n12 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i12->slice(se20, h9));
          SUPPLIER_CNT_mPART3_E1_17_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e12->PS_SUPPKEY;
              long v12 = e12->__av;
              (/*if */(part_size == 45L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_8.addOrDelOnZero(se19.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),v12) : (void)0);
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h9 == n12->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se20, *e12)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i13 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h10 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se22.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n13 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i13->slice(se22, h10));
          SUPPLIER_CNT_mPART3_E1_17_entry* e13;
         
          if (n13 && (e13 = n13->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e13->PS_SUPPKEY;
              long v13 = e13->__av;
              (/*if */(part_size == 19L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_10.addOrDelOnZero(se21.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),v13) : (void)0);
              n13 = n13->nxt;
            } while (n13 && (e13 = n13->obj) && h10 == n13->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se22, *e13)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i14 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h11 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se24.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n14 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i14->slice(se24, h11));
          SUPPLIER_CNT_mPART3_E1_17_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e14->PS_SUPPKEY;
              long v14 = e14->__av;
              (/*if */(part_size == 3L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_12.addOrDelOnZero(se23.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),v14) : (void)0);
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h11 == n14->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se24, *e14)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i15 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h12 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se26.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n15 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i15->slice(se26, h12));
          SUPPLIER_CNT_mPART3_E1_17_entry* e15;
         
          if (n15 && (e15 = n15->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e15->PS_SUPPKEY;
              long v15 = e15->__av;
              (/*if */(part_size == 36L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_14.addOrDelOnZero(se25.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),v15) : (void)0);
              n15 = n15->nxt;
            } while (n15 && (e15 = n15->obj) && h12 == n15->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se26, *e15)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i16 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h13 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se28.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n16 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i16->slice(se28, h13));
          SUPPLIER_CNT_mPART3_E1_17_entry* e16;
         
          if (n16 && (e16 = n16->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e16->PS_SUPPKEY;
              long v16 = e16->__av;
              (/*if */(part_size == 9L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_16.addOrDelOnZero(se27.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),v16) : (void)0);
              n16 = n16->nxt;
            } while (n16 && (e16 = n16->obj) && h13 == n16->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se28, *e16)); 
          }
        }(/*if */(part_size == 49L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_17.addOrDelOnZero(se29.modify(part_partkey,part_brand,part_type,part_size),1L) : (void)0);
        (/*if */(part_size == 14L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_20.addOrDelOnZero(se30.modify(part_partkey,part_brand,part_type,part_size),1L) : (void)0);
        (/*if */(part_size == 23L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_23.addOrDelOnZero(se31.modify(part_partkey,part_brand,part_type,part_size),1L) : (void)0);
        (/*if */(part_size == 45L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_26.addOrDelOnZero(se32.modify(part_partkey,part_brand,part_type,part_size),1L) : (void)0);
        (/*if */(part_size == 19L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_29.addOrDelOnZero(se33.modify(part_partkey,part_brand,part_type,part_size),1L) : (void)0);
        (/*if */(part_size == 3L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_32.addOrDelOnZero(se34.modify(part_partkey,part_brand,part_type,part_size),1L) : (void)0);
        (/*if */(part_size == 36L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_35.addOrDelOnZero(se35.modify(part_partkey,part_brand,part_type,part_size),1L) : (void)0);
        (/*if */(part_size == 9L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_38.addOrDelOnZero(se36.modify(part_partkey,part_brand,part_type,part_size),1L) : (void)0);
      }
    }
    void on_delete_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg7 = 0L;
        agg8.clear();
        
        long l4 = 0L;
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123* i17 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123*>(SUPPLIER_CNT_mPART3_E1_1.index[1]);
          const HASH_RES_t h14 = SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn::hash(se39.modify123(part_brand, part_type, part_size));
          HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123::IdxNode* n17 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123::IdxNode*>(i17->slice(se39, h14));
          SUPPLIER_CNT_mPART3_E1_1_entry* e17;
         
          if (n17 && (e17 = n17->obj)) {
            do {                
              long ps_suppkey = e17->PS_SUPPKEY;
              long v17 = e17->__av;
              (/*if */(l4 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se38.modify(ps_suppkey)) && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? agg8.addOrDelOnZero(st5.modify(ps_suppkey,(v17 * ((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))))), (v17 * ((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))))) : (void)0);
              n17 = n17->nxt;
            } while (n17 && (e17 = n17->obj) && h14 == n17->hash &&  SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn::equals(se39, *e17)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i18 = static_cast<HashIndex<tuple2_L_L, long>*>(agg8.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n18; 
          tuple2_L_L* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
              long ps_suppkey = e18->_1;  
              long v18 = e18->__av; 
            agg7 += (v18 != 0 ? 1L : 0L);      
              n18 = n18->nxt;
            }
          }
        }if (SUPPLIER_CNT.getValueOrDefault(se37.modify(part_brand,part_type,part_size))==0) SUPPLIER_CNT.setOrDelOnZero(se37, agg7);
        long agg9 = 0L;
        agg10.clear();
        
        long l5 = 0L;
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123* i19 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123*>(SUPPLIER_CNT_mPART3_E1_1.index[1]);
          const HASH_RES_t h15 = SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn::hash(se41.modify123(part_brand, part_type, part_size));
          HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123::IdxNode* n19 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123::IdxNode*>(i19->slice(se41, h15));
          SUPPLIER_CNT_mPART3_E1_1_entry* e19;
         
          if (n19 && (e19 = n19->obj)) {
            do {                
              long ps_suppkey = e19->PS_SUPPKEY;
              long v19 = e19->__av;
              (/*if */(l5 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se40.modify(ps_suppkey))) ? agg10.addOrDelOnZero(st6.modify(ps_suppkey,(v19 * ((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))))), (v19 * ((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))))) : (void)0);
              n19 = n19->nxt;
            } while (n19 && (e19 = n19->obj) && h15 == n19->hash &&  SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn::equals(se41, *e19)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i20 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h16 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se43.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n20 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i20->slice(se43, h16));
          SUPPLIER_CNT_mPART3_E1_17_entry* e20;
         
          if (n20 && (e20 = n20->obj)) {
            do {                
              long ps_suppkey = e20->PS_SUPPKEY;
              long v20 = e20->__av;
              (/*if */(l5 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se42.modify(ps_suppkey))) ? agg10.addOrDelOnZero(st7.modify(ps_suppkey,(v20 * ((/*if */(part_size == 49L) ? -1L : 0L) + ((/*if */(part_size == 14L) ? -1L : 0L) + ((/*if */(part_size == 23L) ? -1L : 0L) + ((/*if */(part_size == 45L) ? -1L : 0L) + ((/*if */(part_size == 19L) ? -1L : 0L) + ((/*if */(part_size == 3L) ? -1L : 0L) + ((/*if */(part_size == 36L) ? -1L : 0L) + (/*if */(part_size == 9L) ? -1L : 0L)))))))))), (v20 * ((/*if */(part_size == 49L) ? -1L : 0L) + ((/*if */(part_size == 14L) ? -1L : 0L) + ((/*if */(part_size == 23L) ? -1L : 0L) + ((/*if */(part_size == 45L) ? -1L : 0L) + ((/*if */(part_size == 19L) ? -1L : 0L) + ((/*if */(part_size == 3L) ? -1L : 0L) + ((/*if */(part_size == 36L) ? -1L : 0L) + (/*if */(part_size == 9L) ? -1L : 0L)))))))))) : (void)0);
              n20 = n20->nxt;
            } while (n20 && (e20 = n20->obj) && h16 == n20->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se43, *e20)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i21 = static_cast<HashIndex<tuple2_L_L, long>*>(agg10.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n21; 
          tuple2_L_L* e21;
        
          for (size_t i = 0; i < i21->size_; i++)
          {
            n21 = i21->buckets_ + i;
            while (n21 && (e21 = n21->obj))
            {
              long ps_suppkey = e21->_1;  
              long v21 = e21->__av; 
            agg9 += (v21 != 0 ? 1L : 0L);      
              n21 = n21->nxt;
            }
          }
        }long agg11 = 0L;
        agg12.clear();
        
        long l6 = 0L;
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123* i22 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123*>(SUPPLIER_CNT_mPART3_E1_1.index[1]);
          const HASH_RES_t h17 = SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn::hash(se45.modify123(part_brand, part_type, part_size));
          HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123::IdxNode* n22 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_map_123::IdxNode*>(i22->slice(se45, h17));
          SUPPLIER_CNT_mPART3_E1_1_entry* e22;
         
          if (n22 && (e22 = n22->obj)) {
            do {                
              long ps_suppkey = e22->PS_SUPPKEY;
              long v22 = e22->__av;
              (/*if */(l6 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se44.modify(ps_suppkey))) ? agg12.addOrDelOnZero(st8.modify(ps_suppkey,(v22 * ((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))))), (v22 * ((/*if */(part_size == 49L) ? 1L : 0L) + ((/*if */(part_size == 14L) ? 1L : 0L) + ((/*if */(part_size == 23L) ? 1L : 0L) + ((/*if */(part_size == 45L) ? 1L : 0L) + ((/*if */(part_size == 19L) ? 1L : 0L) + ((/*if */(part_size == 3L) ? 1L : 0L) + ((/*if */(part_size == 36L) ? 1L : 0L) + (/*if */(part_size == 9L) ? 1L : 0L)))))))))) : (void)0);
              n22 = n22->nxt;
            } while (n22 && (e22 = n22->obj) && h17 == n22->hash &&  SUPPLIER_CNT_mPART3_E1_1_mapkey123_idxfn::equals(se45, *e22)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i23 = static_cast<HashIndex<tuple2_L_L, long>*>(agg12.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n23; 
          tuple2_L_L* e23;
        
          for (size_t i = 0; i < i23->size_; i++)
          {
            n23 = i23->buckets_ + i;
            while (n23 && (e23 = n23->obj))
            {
              long ps_suppkey = e23->_1;  
              long v23 = e23->__av; 
            agg11 += (v23 != 0 ? 1L : 0L);      
              n23 = n23->nxt;
            }
          }
        }(/*if */(0L == Upreg_match(preg1,part_type) && part_brand != c1) ? SUPPLIER_CNT.addOrDelOnZero(se37.modify(part_brand,part_type,part_size),(agg9 + (agg11 * -1L))) : (void)0);
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i24 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h18 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se47.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n24 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i24->slice(se47, h18));
          SUPPLIER_CNT_mPART3_E1_17_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              long ps_suppkey = e24->PS_SUPPKEY;
              long v24 = e24->__av;
              SUPPLIER_CNT_mPART3_E1_1.addOrDelOnZero(se46.modify(ps_suppkey,part_brand,part_type,part_size),(v24 * -1L));
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h18 == n24->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se47, *e24)); 
          }
        }SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1.addOrDelOnZero(se48.modify(part_partkey,part_brand,part_type,part_size),-1L);
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i25 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h19 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se50.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n25 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i25->slice(se50, h19));
          SUPPLIER_CNT_mPART3_E1_17_entry* e25;
         
          if (n25 && (e25 = n25->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e25->PS_SUPPKEY;
              long v25 = e25->__av;
              (/*if */(part_size == 49L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_2.addOrDelOnZero(se49.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),(v25 * -1L)) : (void)0);
              n25 = n25->nxt;
            } while (n25 && (e25 = n25->obj) && h19 == n25->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se50, *e25)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i26 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h20 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se52.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n26 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i26->slice(se52, h20));
          SUPPLIER_CNT_mPART3_E1_17_entry* e26;
         
          if (n26 && (e26 = n26->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e26->PS_SUPPKEY;
              long v26 = e26->__av;
              (/*if */(part_size == 14L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_4.addOrDelOnZero(se51.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),(v26 * -1L)) : (void)0);
              n26 = n26->nxt;
            } while (n26 && (e26 = n26->obj) && h20 == n26->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se52, *e26)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i27 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h21 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se54.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n27 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i27->slice(se54, h21));
          SUPPLIER_CNT_mPART3_E1_17_entry* e27;
         
          if (n27 && (e27 = n27->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e27->PS_SUPPKEY;
              long v27 = e27->__av;
              (/*if */(part_size == 23L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_6.addOrDelOnZero(se53.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),(v27 * -1L)) : (void)0);
              n27 = n27->nxt;
            } while (n27 && (e27 = n27->obj) && h21 == n27->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se54, *e27)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i28 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h22 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se56.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n28 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i28->slice(se56, h22));
          SUPPLIER_CNT_mPART3_E1_17_entry* e28;
         
          if (n28 && (e28 = n28->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e28->PS_SUPPKEY;
              long v28 = e28->__av;
              (/*if */(part_size == 45L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_8.addOrDelOnZero(se55.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),(v28 * -1L)) : (void)0);
              n28 = n28->nxt;
            } while (n28 && (e28 = n28->obj) && h22 == n28->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se56, *e28)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i29 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h23 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se58.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n29 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i29->slice(se58, h23));
          SUPPLIER_CNT_mPART3_E1_17_entry* e29;
         
          if (n29 && (e29 = n29->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e29->PS_SUPPKEY;
              long v29 = e29->__av;
              (/*if */(part_size == 19L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_10.addOrDelOnZero(se57.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),(v29 * -1L)) : (void)0);
              n29 = n29->nxt;
            } while (n29 && (e29 = n29->obj) && h23 == n29->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se58, *e29)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i30 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h24 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se60.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n30 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i30->slice(se60, h24));
          SUPPLIER_CNT_mPART3_E1_17_entry* e30;
         
          if (n30 && (e30 = n30->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e30->PS_SUPPKEY;
              long v30 = e30->__av;
              (/*if */(part_size == 3L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_12.addOrDelOnZero(se59.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),(v30 * -1L)) : (void)0);
              n30 = n30->nxt;
            } while (n30 && (e30 = n30->obj) && h24 == n30->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se60, *e30)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i31 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h25 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se62.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n31 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i31->slice(se62, h25));
          SUPPLIER_CNT_mPART3_E1_17_entry* e31;
         
          if (n31 && (e31 = n31->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e31->PS_SUPPKEY;
              long v31 = e31->__av;
              (/*if */(part_size == 36L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_14.addOrDelOnZero(se61.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),(v31 * -1L)) : (void)0);
              n31 = n31->nxt;
            } while (n31 && (e31 = n31->obj) && h25 == n31->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se62, *e31)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0* i32 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0*>(SUPPLIER_CNT_mPART3_E1_17.index[1]);
          const HASH_RES_t h26 = SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::hash(se64.modify0(part_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode* n32 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_17_map_0::IdxNode*>(i32->slice(se64, h26));
          SUPPLIER_CNT_mPART3_E1_17_entry* e32;
         
          if (n32 && (e32 = n32->obj)) {
            do {                
              long supplier_cnt_mpartsupppartsupp_suppkey = e32->PS_SUPPKEY;
              long v32 = e32->__av;
              (/*if */(part_size == 9L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_16.addOrDelOnZero(se63.modify(supplier_cnt_mpartsupppartsupp_suppkey,part_brand,part_type,part_size),(v32 * -1L)) : (void)0);
              n32 = n32->nxt;
            } while (n32 && (e32 = n32->obj) && h26 == n32->hash &&  SUPPLIER_CNT_mPART3_E1_17_mapkey0_idxfn::equals(se64, *e32)); 
          }
        }(/*if */(part_size == 49L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_17.addOrDelOnZero(se65.modify(part_partkey,part_brand,part_type,part_size),-1L) : (void)0);
        (/*if */(part_size == 14L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_20.addOrDelOnZero(se66.modify(part_partkey,part_brand,part_type,part_size),-1L) : (void)0);
        (/*if */(part_size == 23L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_23.addOrDelOnZero(se67.modify(part_partkey,part_brand,part_type,part_size),-1L) : (void)0);
        (/*if */(part_size == 45L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_26.addOrDelOnZero(se68.modify(part_partkey,part_brand,part_type,part_size),-1L) : (void)0);
        (/*if */(part_size == 19L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_29.addOrDelOnZero(se69.modify(part_partkey,part_brand,part_type,part_size),-1L) : (void)0);
        (/*if */(part_size == 3L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_32.addOrDelOnZero(se70.modify(part_partkey,part_brand,part_type,part_size),-1L) : (void)0);
        (/*if */(part_size == 36L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_35.addOrDelOnZero(se71.modify(part_partkey,part_brand,part_type,part_size),-1L) : (void)0);
        (/*if */(part_size == 9L && part_brand != c1 && 0L == Upreg_match(preg1,part_type)) ? SUPPLIER_CNT_mPARTSUPP1_E1_38.addOrDelOnZero(se72.modify(part_partkey,part_brand,part_type,part_size),-1L) : (void)0);
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        agg13.clear();
        
        agg14.clear();
        
        long l7 = 0L;
        {  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123* i33 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123::IdxNode* n33; 
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e33;
        
          for (size_t i = 0; i < i33->size_; i++)
          {
            n33 = i33->buckets_ + i;
            while (n33 && (e33 = n33->obj))
            {
                long ps_suppkey = e33->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e33->P_BRAND;
                STRING_TYPE p_type = e33->P_TYPE;
                long p_size = e33->P_SIZE;
                long v33 = e33->__av;
                (/*if */(l7 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se74.modify(ps_suppkey))) ? agg14.addOrDelOnZero(st9.modify(ps_suppkey,p_brand,p_type,p_size,v33), v33) : (void)0);
              n33 = n33->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123* i34 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123::IdxNode* n34; 
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e34;
        
          for (size_t i = 0; i < i34->size_; i++)
          {
            n34 = i34->buckets_ + i;
            while (n34 && (e34 = n34->obj))
            {
                long ps_suppkey = e34->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e34->P_BRAND;
                STRING_TYPE p_type = e34->P_TYPE;
                long p_size = e34->P_SIZE;
                long v34 = e34->__av;
                (/*if */(l7 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se75.modify(ps_suppkey))) ? agg14.addOrDelOnZero(st10.modify(ps_suppkey,p_brand,p_type,p_size,v34), v34) : (void)0);
              n34 = n34->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123* i35 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_6.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123::IdxNode* n35; 
          SUPPLIER_CNT_mPARTSUPP1_E1_6_entry* e35;
        
          for (size_t i = 0; i < i35->size_; i++)
          {
            n35 = i35->buckets_ + i;
            while (n35 && (e35 = n35->obj))
            {
                long ps_suppkey = e35->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e35->P_BRAND;
                STRING_TYPE p_type = e35->P_TYPE;
                long p_size = e35->P_SIZE;
                long v35 = e35->__av;
                (/*if */(l7 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se76.modify(ps_suppkey))) ? agg14.addOrDelOnZero(st11.modify(ps_suppkey,p_brand,p_type,p_size,v35), v35) : (void)0);
              n35 = n35->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123* i36 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_8.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123::IdxNode* n36; 
          SUPPLIER_CNT_mPARTSUPP1_E1_8_entry* e36;
        
          for (size_t i = 0; i < i36->size_; i++)
          {
            n36 = i36->buckets_ + i;
            while (n36 && (e36 = n36->obj))
            {
                long ps_suppkey = e36->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e36->P_BRAND;
                STRING_TYPE p_type = e36->P_TYPE;
                long p_size = e36->P_SIZE;
                long v36 = e36->__av;
                (/*if */(l7 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se77.modify(ps_suppkey))) ? agg14.addOrDelOnZero(st12.modify(ps_suppkey,p_brand,p_type,p_size,v36), v36) : (void)0);
              n36 = n36->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123* i37 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_10.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123::IdxNode* n37; 
          SUPPLIER_CNT_mPARTSUPP1_E1_10_entry* e37;
        
          for (size_t i = 0; i < i37->size_; i++)
          {
            n37 = i37->buckets_ + i;
            while (n37 && (e37 = n37->obj))
            {
                long ps_suppkey = e37->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e37->P_BRAND;
                STRING_TYPE p_type = e37->P_TYPE;
                long p_size = e37->P_SIZE;
                long v37 = e37->__av;
                (/*if */(l7 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se78.modify(ps_suppkey))) ? agg14.addOrDelOnZero(st13.modify(ps_suppkey,p_brand,p_type,p_size,v37), v37) : (void)0);
              n37 = n37->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123* i38 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_12.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123::IdxNode* n38; 
          SUPPLIER_CNT_mPARTSUPP1_E1_12_entry* e38;
        
          for (size_t i = 0; i < i38->size_; i++)
          {
            n38 = i38->buckets_ + i;
            while (n38 && (e38 = n38->obj))
            {
                long ps_suppkey = e38->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e38->P_BRAND;
                STRING_TYPE p_type = e38->P_TYPE;
                long p_size = e38->P_SIZE;
                long v38 = e38->__av;
                (/*if */(l7 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se79.modify(ps_suppkey))) ? agg14.addOrDelOnZero(st14.modify(ps_suppkey,p_brand,p_type,p_size,v38), v38) : (void)0);
              n38 = n38->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123* i39 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_14.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123::IdxNode* n39; 
          SUPPLIER_CNT_mPARTSUPP1_E1_14_entry* e39;
        
          for (size_t i = 0; i < i39->size_; i++)
          {
            n39 = i39->buckets_ + i;
            while (n39 && (e39 = n39->obj))
            {
                long ps_suppkey = e39->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e39->P_BRAND;
                STRING_TYPE p_type = e39->P_TYPE;
                long p_size = e39->P_SIZE;
                long v39 = e39->__av;
                (/*if */(l7 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se80.modify(ps_suppkey))) ? agg14.addOrDelOnZero(st15.modify(ps_suppkey,p_brand,p_type,p_size,v39), v39) : (void)0);
              n39 = n39->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123* i40 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_16.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123::IdxNode* n40; 
          SUPPLIER_CNT_mPARTSUPP1_E1_16_entry* e40;
        
          for (size_t i = 0; i < i40->size_; i++)
          {
            n40 = i40->buckets_ + i;
            while (n40 && (e40 = n40->obj))
            {
                long ps_suppkey = e40->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e40->P_BRAND;
                STRING_TYPE p_type = e40->P_TYPE;
                long p_size = e40->P_SIZE;
                long v40 = e40->__av;
                (/*if */(l7 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se81.modify(ps_suppkey))) ? agg14.addOrDelOnZero(st16.modify(ps_suppkey,p_brand,p_type,p_size,v40), v40) : (void)0);
              n40 = n40->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple5_LSSL_L, long>* i41 = static_cast<HashIndex<tuple5_LSSL_L, long>*>(agg14.index[0]);
          HashIndex<tuple5_LSSL_L, long>::IdxNode* n41; 
          tuple5_LSSL_L* e41;
        
          for (size_t i = 0; i < i41->size_; i++)
          {
            n41 = i41->buckets_ + i;
            while (n41 && (e41 = n41->obj))
            {
              long ps_suppkey = e41->_1;
              STRING_TYPE p_brand = e41->_2;
              STRING_TYPE p_type = e41->_3;
              long p_size = e41->_4;  
              long v41 = e41->__av; 
            agg13.addOrDelOnZero(st17.modify(p_brand,p_type,p_size,(v41 != 0 ? 1L : 0L)), (v41 != 0 ? 1L : 0L));      
              n41 = n41->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i42 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg13.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n42; 
          tuple4_SSL_L* e42;
        
          for (size_t i = 0; i < i42->size_; i++)
          {
            n42 = i42->buckets_ + i;
            while (n42 && (e42 = n42->obj))
            {
              STRING_TYPE p_brand = e42->_1;
              STRING_TYPE p_type = e42->_2;
              long p_size = e42->_3;  
              long v42 = e42->__av; 
            if (SUPPLIER_CNT.getValueOrDefault(se73.modify(p_brand,p_type,p_size))==0) SUPPLIER_CNT.setOrDelOnZero(se73, v42);      
              n42 = n42->nxt;
            }
          }
        }agg15.clear();
        
        long l8 = (SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se82.modify(supplier_suppkey)) + (/*if */(0L != Upreg_match(preg2,supplier_comment)) ? 1L : 0L));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i43 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h27 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se83.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n43 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i43->slice(se83, h27));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e43;
         
          if (n43 && (e43 = n43->obj)) {
            do {                
              STRING_TYPE p_brand = e43->P_BRAND;
              STRING_TYPE p_type = e43->P_TYPE;
              long p_size = e43->P_SIZE;
              long v43 = e43->__av;
              (/*if */(l8 == 0L) ? agg15.addOrDelOnZero(st18.modify(p_brand,p_type,p_size,v43), v43) : (void)0);
              n43 = n43->nxt;
            } while (n43 && (e43 = n43->obj) && h27 == n43->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se83, *e43)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0* i44 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h28 = SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::hash(se84.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode* n44 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode*>(i44->slice(se84, h28));
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e44;
         
          if (n44 && (e44 = n44->obj)) {
            do {                
              STRING_TYPE p_brand = e44->P_BRAND;
              STRING_TYPE p_type = e44->P_TYPE;
              long p_size = e44->P_SIZE;
              long v44 = e44->__av;
              (/*if */(l8 == 0L) ? agg15.addOrDelOnZero(st19.modify(p_brand,p_type,p_size,v44), v44) : (void)0);
              n44 = n44->nxt;
            } while (n44 && (e44 = n44->obj) && h28 == n44->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::equals(se84, *e44)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0* i45 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_6.index[1]);
          const HASH_RES_t h29 = SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::hash(se85.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode* n45 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode*>(i45->slice(se85, h29));
          SUPPLIER_CNT_mPARTSUPP1_E1_6_entry* e45;
         
          if (n45 && (e45 = n45->obj)) {
            do {                
              STRING_TYPE p_brand = e45->P_BRAND;
              STRING_TYPE p_type = e45->P_TYPE;
              long p_size = e45->P_SIZE;
              long v45 = e45->__av;
              (/*if */(l8 == 0L) ? agg15.addOrDelOnZero(st20.modify(p_brand,p_type,p_size,v45), v45) : (void)0);
              n45 = n45->nxt;
            } while (n45 && (e45 = n45->obj) && h29 == n45->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::equals(se85, *e45)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0* i46 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_8.index[1]);
          const HASH_RES_t h30 = SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::hash(se86.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode* n46 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode*>(i46->slice(se86, h30));
          SUPPLIER_CNT_mPARTSUPP1_E1_8_entry* e46;
         
          if (n46 && (e46 = n46->obj)) {
            do {                
              STRING_TYPE p_brand = e46->P_BRAND;
              STRING_TYPE p_type = e46->P_TYPE;
              long p_size = e46->P_SIZE;
              long v46 = e46->__av;
              (/*if */(l8 == 0L) ? agg15.addOrDelOnZero(st21.modify(p_brand,p_type,p_size,v46), v46) : (void)0);
              n46 = n46->nxt;
            } while (n46 && (e46 = n46->obj) && h30 == n46->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::equals(se86, *e46)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0* i47 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_10.index[1]);
          const HASH_RES_t h31 = SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::hash(se87.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode* n47 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode*>(i47->slice(se87, h31));
          SUPPLIER_CNT_mPARTSUPP1_E1_10_entry* e47;
         
          if (n47 && (e47 = n47->obj)) {
            do {                
              STRING_TYPE p_brand = e47->P_BRAND;
              STRING_TYPE p_type = e47->P_TYPE;
              long p_size = e47->P_SIZE;
              long v47 = e47->__av;
              (/*if */(l8 == 0L) ? agg15.addOrDelOnZero(st22.modify(p_brand,p_type,p_size,v47), v47) : (void)0);
              n47 = n47->nxt;
            } while (n47 && (e47 = n47->obj) && h31 == n47->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::equals(se87, *e47)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0* i48 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_12.index[1]);
          const HASH_RES_t h32 = SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::hash(se88.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode* n48 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode*>(i48->slice(se88, h32));
          SUPPLIER_CNT_mPARTSUPP1_E1_12_entry* e48;
         
          if (n48 && (e48 = n48->obj)) {
            do {                
              STRING_TYPE p_brand = e48->P_BRAND;
              STRING_TYPE p_type = e48->P_TYPE;
              long p_size = e48->P_SIZE;
              long v48 = e48->__av;
              (/*if */(l8 == 0L) ? agg15.addOrDelOnZero(st23.modify(p_brand,p_type,p_size,v48), v48) : (void)0);
              n48 = n48->nxt;
            } while (n48 && (e48 = n48->obj) && h32 == n48->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::equals(se88, *e48)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0* i49 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_14.index[1]);
          const HASH_RES_t h33 = SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::hash(se89.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode* n49 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode*>(i49->slice(se89, h33));
          SUPPLIER_CNT_mPARTSUPP1_E1_14_entry* e49;
         
          if (n49 && (e49 = n49->obj)) {
            do {                
              STRING_TYPE p_brand = e49->P_BRAND;
              STRING_TYPE p_type = e49->P_TYPE;
              long p_size = e49->P_SIZE;
              long v49 = e49->__av;
              (/*if */(l8 == 0L) ? agg15.addOrDelOnZero(st24.modify(p_brand,p_type,p_size,v49), v49) : (void)0);
              n49 = n49->nxt;
            } while (n49 && (e49 = n49->obj) && h33 == n49->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::equals(se89, *e49)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0* i50 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_16.index[1]);
          const HASH_RES_t h34 = SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::hash(se90.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode* n50 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode*>(i50->slice(se90, h34));
          SUPPLIER_CNT_mPARTSUPP1_E1_16_entry* e50;
         
          if (n50 && (e50 = n50->obj)) {
            do {                
              STRING_TYPE p_brand = e50->P_BRAND;
              STRING_TYPE p_type = e50->P_TYPE;
              long p_size = e50->P_SIZE;
              long v50 = e50->__av;
              (/*if */(l8 == 0L) ? agg15.addOrDelOnZero(st25.modify(p_brand,p_type,p_size,v50), v50) : (void)0);
              n50 = n50->nxt;
            } while (n50 && (e50 = n50->obj) && h34 == n50->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::equals(se90, *e50)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i51 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg15.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n51; 
          tuple4_SSL_L* e51;
        
          for (size_t i = 0; i < i51->size_; i++)
          {
            n51 = i51->buckets_ + i;
            while (n51 && (e51 = n51->obj))
            {
              STRING_TYPE p_brand = e51->_1;
              STRING_TYPE p_type = e51->_2;
              long p_size = e51->_3;  
              long v51 = e51->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se73.modify(p_brand,p_type,p_size),(v51 != 0 ? 1L : 0L));      
              n51 = n51->nxt;
            }
          }
        }agg16.clear();
        
        long l9 = SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se91.modify(supplier_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i52 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h35 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se92.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n52 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i52->slice(se92, h35));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e52;
         
          if (n52 && (e52 = n52->obj)) {
            do {                
              STRING_TYPE p_brand = e52->P_BRAND;
              STRING_TYPE p_type = e52->P_TYPE;
              long p_size = e52->P_SIZE;
              long v52 = e52->__av;
              (/*if */(l9 == 0L) ? agg16.addOrDelOnZero(st26.modify(p_brand,p_type,p_size,v52), v52) : (void)0);
              n52 = n52->nxt;
            } while (n52 && (e52 = n52->obj) && h35 == n52->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se92, *e52)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0* i53 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h36 = SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::hash(se93.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode* n53 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode*>(i53->slice(se93, h36));
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e53;
         
          if (n53 && (e53 = n53->obj)) {
            do {                
              STRING_TYPE p_brand = e53->P_BRAND;
              STRING_TYPE p_type = e53->P_TYPE;
              long p_size = e53->P_SIZE;
              long v53 = e53->__av;
              (/*if */(l9 == 0L) ? agg16.addOrDelOnZero(st27.modify(p_brand,p_type,p_size,v53), v53) : (void)0);
              n53 = n53->nxt;
            } while (n53 && (e53 = n53->obj) && h36 == n53->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::equals(se93, *e53)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0* i54 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_6.index[1]);
          const HASH_RES_t h37 = SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::hash(se94.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode* n54 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode*>(i54->slice(se94, h37));
          SUPPLIER_CNT_mPARTSUPP1_E1_6_entry* e54;
         
          if (n54 && (e54 = n54->obj)) {
            do {                
              STRING_TYPE p_brand = e54->P_BRAND;
              STRING_TYPE p_type = e54->P_TYPE;
              long p_size = e54->P_SIZE;
              long v54 = e54->__av;
              (/*if */(l9 == 0L) ? agg16.addOrDelOnZero(st28.modify(p_brand,p_type,p_size,v54), v54) : (void)0);
              n54 = n54->nxt;
            } while (n54 && (e54 = n54->obj) && h37 == n54->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::equals(se94, *e54)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0* i55 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_8.index[1]);
          const HASH_RES_t h38 = SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::hash(se95.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode* n55 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode*>(i55->slice(se95, h38));
          SUPPLIER_CNT_mPARTSUPP1_E1_8_entry* e55;
         
          if (n55 && (e55 = n55->obj)) {
            do {                
              STRING_TYPE p_brand = e55->P_BRAND;
              STRING_TYPE p_type = e55->P_TYPE;
              long p_size = e55->P_SIZE;
              long v55 = e55->__av;
              (/*if */(l9 == 0L) ? agg16.addOrDelOnZero(st29.modify(p_brand,p_type,p_size,v55), v55) : (void)0);
              n55 = n55->nxt;
            } while (n55 && (e55 = n55->obj) && h38 == n55->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::equals(se95, *e55)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0* i56 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_10.index[1]);
          const HASH_RES_t h39 = SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::hash(se96.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode* n56 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode*>(i56->slice(se96, h39));
          SUPPLIER_CNT_mPARTSUPP1_E1_10_entry* e56;
         
          if (n56 && (e56 = n56->obj)) {
            do {                
              STRING_TYPE p_brand = e56->P_BRAND;
              STRING_TYPE p_type = e56->P_TYPE;
              long p_size = e56->P_SIZE;
              long v56 = e56->__av;
              (/*if */(l9 == 0L) ? agg16.addOrDelOnZero(st30.modify(p_brand,p_type,p_size,v56), v56) : (void)0);
              n56 = n56->nxt;
            } while (n56 && (e56 = n56->obj) && h39 == n56->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::equals(se96, *e56)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0* i57 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_12.index[1]);
          const HASH_RES_t h40 = SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::hash(se97.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode* n57 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode*>(i57->slice(se97, h40));
          SUPPLIER_CNT_mPARTSUPP1_E1_12_entry* e57;
         
          if (n57 && (e57 = n57->obj)) {
            do {                
              STRING_TYPE p_brand = e57->P_BRAND;
              STRING_TYPE p_type = e57->P_TYPE;
              long p_size = e57->P_SIZE;
              long v57 = e57->__av;
              (/*if */(l9 == 0L) ? agg16.addOrDelOnZero(st31.modify(p_brand,p_type,p_size,v57), v57) : (void)0);
              n57 = n57->nxt;
            } while (n57 && (e57 = n57->obj) && h40 == n57->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::equals(se97, *e57)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0* i58 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_14.index[1]);
          const HASH_RES_t h41 = SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::hash(se98.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode* n58 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode*>(i58->slice(se98, h41));
          SUPPLIER_CNT_mPARTSUPP1_E1_14_entry* e58;
         
          if (n58 && (e58 = n58->obj)) {
            do {                
              STRING_TYPE p_brand = e58->P_BRAND;
              STRING_TYPE p_type = e58->P_TYPE;
              long p_size = e58->P_SIZE;
              long v58 = e58->__av;
              (/*if */(l9 == 0L) ? agg16.addOrDelOnZero(st32.modify(p_brand,p_type,p_size,v58), v58) : (void)0);
              n58 = n58->nxt;
            } while (n58 && (e58 = n58->obj) && h41 == n58->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::equals(se98, *e58)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0* i59 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_16.index[1]);
          const HASH_RES_t h42 = SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::hash(se99.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode* n59 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode*>(i59->slice(se99, h42));
          SUPPLIER_CNT_mPARTSUPP1_E1_16_entry* e59;
         
          if (n59 && (e59 = n59->obj)) {
            do {                
              STRING_TYPE p_brand = e59->P_BRAND;
              STRING_TYPE p_type = e59->P_TYPE;
              long p_size = e59->P_SIZE;
              long v59 = e59->__av;
              (/*if */(l9 == 0L) ? agg16.addOrDelOnZero(st33.modify(p_brand,p_type,p_size,v59), v59) : (void)0);
              n59 = n59->nxt;
            } while (n59 && (e59 = n59->obj) && h42 == n59->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::equals(se99, *e59)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i60 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg16.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n60; 
          tuple4_SSL_L* e60;
        
          for (size_t i = 0; i < i60->size_; i++)
          {
            n60 = i60->buckets_ + i;
            while (n60 && (e60 = n60->obj))
            {
              STRING_TYPE p_brand = e60->_1;
              STRING_TYPE p_type = e60->_2;
              long p_size = e60->_3;  
              long v60 = e60->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se73.modify(p_brand,p_type,p_size),((v60 != 0 ? 1L : 0L) * -1L));      
              n60 = n60->nxt;
            }
          }
        }(/*if */(0L != Upreg_match(preg2,supplier_comment)) ? SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.addOrDelOnZero(se100.modify(supplier_suppkey),1L) : (void)0);
      }
    }
    void on_delete_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        agg17.clear();
        
        agg18.clear();
        
        long l10 = 0L;
        {  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123* i61 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123::IdxNode* n61; 
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e61;
        
          for (size_t i = 0; i < i61->size_; i++)
          {
            n61 = i61->buckets_ + i;
            while (n61 && (e61 = n61->obj))
            {
                long ps_suppkey = e61->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e61->P_BRAND;
                STRING_TYPE p_type = e61->P_TYPE;
                long p_size = e61->P_SIZE;
                long v61 = e61->__av;
                (/*if */(l10 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se102.modify(ps_suppkey))) ? agg18.addOrDelOnZero(st34.modify(ps_suppkey,p_brand,p_type,p_size,v61), v61) : (void)0);
              n61 = n61->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123* i62 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123::IdxNode* n62; 
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e62;
        
          for (size_t i = 0; i < i62->size_; i++)
          {
            n62 = i62->buckets_ + i;
            while (n62 && (e62 = n62->obj))
            {
                long ps_suppkey = e62->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e62->P_BRAND;
                STRING_TYPE p_type = e62->P_TYPE;
                long p_size = e62->P_SIZE;
                long v62 = e62->__av;
                (/*if */(l10 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se103.modify(ps_suppkey))) ? agg18.addOrDelOnZero(st35.modify(ps_suppkey,p_brand,p_type,p_size,v62), v62) : (void)0);
              n62 = n62->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123* i63 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_6.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123::IdxNode* n63; 
          SUPPLIER_CNT_mPARTSUPP1_E1_6_entry* e63;
        
          for (size_t i = 0; i < i63->size_; i++)
          {
            n63 = i63->buckets_ + i;
            while (n63 && (e63 = n63->obj))
            {
                long ps_suppkey = e63->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e63->P_BRAND;
                STRING_TYPE p_type = e63->P_TYPE;
                long p_size = e63->P_SIZE;
                long v63 = e63->__av;
                (/*if */(l10 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se104.modify(ps_suppkey))) ? agg18.addOrDelOnZero(st36.modify(ps_suppkey,p_brand,p_type,p_size,v63), v63) : (void)0);
              n63 = n63->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123* i64 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_8.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123::IdxNode* n64; 
          SUPPLIER_CNT_mPARTSUPP1_E1_8_entry* e64;
        
          for (size_t i = 0; i < i64->size_; i++)
          {
            n64 = i64->buckets_ + i;
            while (n64 && (e64 = n64->obj))
            {
                long ps_suppkey = e64->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e64->P_BRAND;
                STRING_TYPE p_type = e64->P_TYPE;
                long p_size = e64->P_SIZE;
                long v64 = e64->__av;
                (/*if */(l10 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se105.modify(ps_suppkey))) ? agg18.addOrDelOnZero(st37.modify(ps_suppkey,p_brand,p_type,p_size,v64), v64) : (void)0);
              n64 = n64->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123* i65 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_10.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123::IdxNode* n65; 
          SUPPLIER_CNT_mPARTSUPP1_E1_10_entry* e65;
        
          for (size_t i = 0; i < i65->size_; i++)
          {
            n65 = i65->buckets_ + i;
            while (n65 && (e65 = n65->obj))
            {
                long ps_suppkey = e65->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e65->P_BRAND;
                STRING_TYPE p_type = e65->P_TYPE;
                long p_size = e65->P_SIZE;
                long v65 = e65->__av;
                (/*if */(l10 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se106.modify(ps_suppkey))) ? agg18.addOrDelOnZero(st38.modify(ps_suppkey,p_brand,p_type,p_size,v65), v65) : (void)0);
              n65 = n65->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123* i66 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_12.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123::IdxNode* n66; 
          SUPPLIER_CNT_mPARTSUPP1_E1_12_entry* e66;
        
          for (size_t i = 0; i < i66->size_; i++)
          {
            n66 = i66->buckets_ + i;
            while (n66 && (e66 = n66->obj))
            {
                long ps_suppkey = e66->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e66->P_BRAND;
                STRING_TYPE p_type = e66->P_TYPE;
                long p_size = e66->P_SIZE;
                long v66 = e66->__av;
                (/*if */(l10 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se107.modify(ps_suppkey))) ? agg18.addOrDelOnZero(st39.modify(ps_suppkey,p_brand,p_type,p_size,v66), v66) : (void)0);
              n66 = n66->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123* i67 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_14.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123::IdxNode* n67; 
          SUPPLIER_CNT_mPARTSUPP1_E1_14_entry* e67;
        
          for (size_t i = 0; i < i67->size_; i++)
          {
            n67 = i67->buckets_ + i;
            while (n67 && (e67 = n67->obj))
            {
                long ps_suppkey = e67->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e67->P_BRAND;
                STRING_TYPE p_type = e67->P_TYPE;
                long p_size = e67->P_SIZE;
                long v67 = e67->__av;
                (/*if */(l10 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se108.modify(ps_suppkey))) ? agg18.addOrDelOnZero(st40.modify(ps_suppkey,p_brand,p_type,p_size,v67), v67) : (void)0);
              n67 = n67->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123* i68 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_16.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123::IdxNode* n68; 
          SUPPLIER_CNT_mPARTSUPP1_E1_16_entry* e68;
        
          for (size_t i = 0; i < i68->size_; i++)
          {
            n68 = i68->buckets_ + i;
            while (n68 && (e68 = n68->obj))
            {
                long ps_suppkey = e68->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e68->P_BRAND;
                STRING_TYPE p_type = e68->P_TYPE;
                long p_size = e68->P_SIZE;
                long v68 = e68->__av;
                (/*if */(l10 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se109.modify(ps_suppkey))) ? agg18.addOrDelOnZero(st41.modify(ps_suppkey,p_brand,p_type,p_size,v68), v68) : (void)0);
              n68 = n68->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple5_LSSL_L, long>* i69 = static_cast<HashIndex<tuple5_LSSL_L, long>*>(agg18.index[0]);
          HashIndex<tuple5_LSSL_L, long>::IdxNode* n69; 
          tuple5_LSSL_L* e69;
        
          for (size_t i = 0; i < i69->size_; i++)
          {
            n69 = i69->buckets_ + i;
            while (n69 && (e69 = n69->obj))
            {
              long ps_suppkey = e69->_1;
              STRING_TYPE p_brand = e69->_2;
              STRING_TYPE p_type = e69->_3;
              long p_size = e69->_4;  
              long v69 = e69->__av; 
            agg17.addOrDelOnZero(st42.modify(p_brand,p_type,p_size,(v69 != 0 ? 1L : 0L)), (v69 != 0 ? 1L : 0L));      
              n69 = n69->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i70 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg17.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n70; 
          tuple4_SSL_L* e70;
        
          for (size_t i = 0; i < i70->size_; i++)
          {
            n70 = i70->buckets_ + i;
            while (n70 && (e70 = n70->obj))
            {
              STRING_TYPE p_brand = e70->_1;
              STRING_TYPE p_type = e70->_2;
              long p_size = e70->_3;  
              long v70 = e70->__av; 
            if (SUPPLIER_CNT.getValueOrDefault(se101.modify(p_brand,p_type,p_size))==0) SUPPLIER_CNT.setOrDelOnZero(se101, v70);      
              n70 = n70->nxt;
            }
          }
        }agg19.clear();
        
        long l11 = (SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se110.modify(supplier_suppkey)) + (/*if */(0L != Upreg_match(preg2,supplier_comment)) ? -1L : 0L));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i71 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h43 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se111.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n71 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i71->slice(se111, h43));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e71;
         
          if (n71 && (e71 = n71->obj)) {
            do {                
              STRING_TYPE p_brand = e71->P_BRAND;
              STRING_TYPE p_type = e71->P_TYPE;
              long p_size = e71->P_SIZE;
              long v71 = e71->__av;
              (/*if */(l11 == 0L) ? agg19.addOrDelOnZero(st43.modify(p_brand,p_type,p_size,v71), v71) : (void)0);
              n71 = n71->nxt;
            } while (n71 && (e71 = n71->obj) && h43 == n71->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se111, *e71)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0* i72 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h44 = SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::hash(se112.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode* n72 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode*>(i72->slice(se112, h44));
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e72;
         
          if (n72 && (e72 = n72->obj)) {
            do {                
              STRING_TYPE p_brand = e72->P_BRAND;
              STRING_TYPE p_type = e72->P_TYPE;
              long p_size = e72->P_SIZE;
              long v72 = e72->__av;
              (/*if */(l11 == 0L) ? agg19.addOrDelOnZero(st44.modify(p_brand,p_type,p_size,v72), v72) : (void)0);
              n72 = n72->nxt;
            } while (n72 && (e72 = n72->obj) && h44 == n72->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::equals(se112, *e72)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0* i73 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_6.index[1]);
          const HASH_RES_t h45 = SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::hash(se113.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode* n73 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode*>(i73->slice(se113, h45));
          SUPPLIER_CNT_mPARTSUPP1_E1_6_entry* e73;
         
          if (n73 && (e73 = n73->obj)) {
            do {                
              STRING_TYPE p_brand = e73->P_BRAND;
              STRING_TYPE p_type = e73->P_TYPE;
              long p_size = e73->P_SIZE;
              long v73 = e73->__av;
              (/*if */(l11 == 0L) ? agg19.addOrDelOnZero(st45.modify(p_brand,p_type,p_size,v73), v73) : (void)0);
              n73 = n73->nxt;
            } while (n73 && (e73 = n73->obj) && h45 == n73->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::equals(se113, *e73)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0* i74 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_8.index[1]);
          const HASH_RES_t h46 = SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::hash(se114.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode* n74 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode*>(i74->slice(se114, h46));
          SUPPLIER_CNT_mPARTSUPP1_E1_8_entry* e74;
         
          if (n74 && (e74 = n74->obj)) {
            do {                
              STRING_TYPE p_brand = e74->P_BRAND;
              STRING_TYPE p_type = e74->P_TYPE;
              long p_size = e74->P_SIZE;
              long v74 = e74->__av;
              (/*if */(l11 == 0L) ? agg19.addOrDelOnZero(st46.modify(p_brand,p_type,p_size,v74), v74) : (void)0);
              n74 = n74->nxt;
            } while (n74 && (e74 = n74->obj) && h46 == n74->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::equals(se114, *e74)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0* i75 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_10.index[1]);
          const HASH_RES_t h47 = SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::hash(se115.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode* n75 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode*>(i75->slice(se115, h47));
          SUPPLIER_CNT_mPARTSUPP1_E1_10_entry* e75;
         
          if (n75 && (e75 = n75->obj)) {
            do {                
              STRING_TYPE p_brand = e75->P_BRAND;
              STRING_TYPE p_type = e75->P_TYPE;
              long p_size = e75->P_SIZE;
              long v75 = e75->__av;
              (/*if */(l11 == 0L) ? agg19.addOrDelOnZero(st47.modify(p_brand,p_type,p_size,v75), v75) : (void)0);
              n75 = n75->nxt;
            } while (n75 && (e75 = n75->obj) && h47 == n75->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::equals(se115, *e75)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0* i76 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_12.index[1]);
          const HASH_RES_t h48 = SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::hash(se116.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode* n76 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode*>(i76->slice(se116, h48));
          SUPPLIER_CNT_mPARTSUPP1_E1_12_entry* e76;
         
          if (n76 && (e76 = n76->obj)) {
            do {                
              STRING_TYPE p_brand = e76->P_BRAND;
              STRING_TYPE p_type = e76->P_TYPE;
              long p_size = e76->P_SIZE;
              long v76 = e76->__av;
              (/*if */(l11 == 0L) ? agg19.addOrDelOnZero(st48.modify(p_brand,p_type,p_size,v76), v76) : (void)0);
              n76 = n76->nxt;
            } while (n76 && (e76 = n76->obj) && h48 == n76->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::equals(se116, *e76)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0* i77 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_14.index[1]);
          const HASH_RES_t h49 = SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::hash(se117.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode* n77 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode*>(i77->slice(se117, h49));
          SUPPLIER_CNT_mPARTSUPP1_E1_14_entry* e77;
         
          if (n77 && (e77 = n77->obj)) {
            do {                
              STRING_TYPE p_brand = e77->P_BRAND;
              STRING_TYPE p_type = e77->P_TYPE;
              long p_size = e77->P_SIZE;
              long v77 = e77->__av;
              (/*if */(l11 == 0L) ? agg19.addOrDelOnZero(st49.modify(p_brand,p_type,p_size,v77), v77) : (void)0);
              n77 = n77->nxt;
            } while (n77 && (e77 = n77->obj) && h49 == n77->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::equals(se117, *e77)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0* i78 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_16.index[1]);
          const HASH_RES_t h50 = SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::hash(se118.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode* n78 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode*>(i78->slice(se118, h50));
          SUPPLIER_CNT_mPARTSUPP1_E1_16_entry* e78;
         
          if (n78 && (e78 = n78->obj)) {
            do {                
              STRING_TYPE p_brand = e78->P_BRAND;
              STRING_TYPE p_type = e78->P_TYPE;
              long p_size = e78->P_SIZE;
              long v78 = e78->__av;
              (/*if */(l11 == 0L) ? agg19.addOrDelOnZero(st50.modify(p_brand,p_type,p_size,v78), v78) : (void)0);
              n78 = n78->nxt;
            } while (n78 && (e78 = n78->obj) && h50 == n78->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::equals(se118, *e78)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i79 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg19.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n79; 
          tuple4_SSL_L* e79;
        
          for (size_t i = 0; i < i79->size_; i++)
          {
            n79 = i79->buckets_ + i;
            while (n79 && (e79 = n79->obj))
            {
              STRING_TYPE p_brand = e79->_1;
              STRING_TYPE p_type = e79->_2;
              long p_size = e79->_3;  
              long v79 = e79->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se101.modify(p_brand,p_type,p_size),(v79 != 0 ? 1L : 0L));      
              n79 = n79->nxt;
            }
          }
        }agg20.clear();
        
        long l12 = SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se119.modify(supplier_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i80 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h51 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se120.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n80 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i80->slice(se120, h51));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e80;
         
          if (n80 && (e80 = n80->obj)) {
            do {                
              STRING_TYPE p_brand = e80->P_BRAND;
              STRING_TYPE p_type = e80->P_TYPE;
              long p_size = e80->P_SIZE;
              long v80 = e80->__av;
              (/*if */(l12 == 0L) ? agg20.addOrDelOnZero(st51.modify(p_brand,p_type,p_size,v80), v80) : (void)0);
              n80 = n80->nxt;
            } while (n80 && (e80 = n80->obj) && h51 == n80->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se120, *e80)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0* i81 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h52 = SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::hash(se121.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode* n81 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode*>(i81->slice(se121, h52));
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e81;
         
          if (n81 && (e81 = n81->obj)) {
            do {                
              STRING_TYPE p_brand = e81->P_BRAND;
              STRING_TYPE p_type = e81->P_TYPE;
              long p_size = e81->P_SIZE;
              long v81 = e81->__av;
              (/*if */(l12 == 0L) ? agg20.addOrDelOnZero(st52.modify(p_brand,p_type,p_size,v81), v81) : (void)0);
              n81 = n81->nxt;
            } while (n81 && (e81 = n81->obj) && h52 == n81->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::equals(se121, *e81)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0* i82 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_6.index[1]);
          const HASH_RES_t h53 = SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::hash(se122.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode* n82 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode*>(i82->slice(se122, h53));
          SUPPLIER_CNT_mPARTSUPP1_E1_6_entry* e82;
         
          if (n82 && (e82 = n82->obj)) {
            do {                
              STRING_TYPE p_brand = e82->P_BRAND;
              STRING_TYPE p_type = e82->P_TYPE;
              long p_size = e82->P_SIZE;
              long v82 = e82->__av;
              (/*if */(l12 == 0L) ? agg20.addOrDelOnZero(st53.modify(p_brand,p_type,p_size,v82), v82) : (void)0);
              n82 = n82->nxt;
            } while (n82 && (e82 = n82->obj) && h53 == n82->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::equals(se122, *e82)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0* i83 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_8.index[1]);
          const HASH_RES_t h54 = SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::hash(se123.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode* n83 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode*>(i83->slice(se123, h54));
          SUPPLIER_CNT_mPARTSUPP1_E1_8_entry* e83;
         
          if (n83 && (e83 = n83->obj)) {
            do {                
              STRING_TYPE p_brand = e83->P_BRAND;
              STRING_TYPE p_type = e83->P_TYPE;
              long p_size = e83->P_SIZE;
              long v83 = e83->__av;
              (/*if */(l12 == 0L) ? agg20.addOrDelOnZero(st54.modify(p_brand,p_type,p_size,v83), v83) : (void)0);
              n83 = n83->nxt;
            } while (n83 && (e83 = n83->obj) && h54 == n83->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::equals(se123, *e83)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0* i84 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_10.index[1]);
          const HASH_RES_t h55 = SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::hash(se124.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode* n84 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode*>(i84->slice(se124, h55));
          SUPPLIER_CNT_mPARTSUPP1_E1_10_entry* e84;
         
          if (n84 && (e84 = n84->obj)) {
            do {                
              STRING_TYPE p_brand = e84->P_BRAND;
              STRING_TYPE p_type = e84->P_TYPE;
              long p_size = e84->P_SIZE;
              long v84 = e84->__av;
              (/*if */(l12 == 0L) ? agg20.addOrDelOnZero(st55.modify(p_brand,p_type,p_size,v84), v84) : (void)0);
              n84 = n84->nxt;
            } while (n84 && (e84 = n84->obj) && h55 == n84->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::equals(se124, *e84)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0* i85 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_12.index[1]);
          const HASH_RES_t h56 = SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::hash(se125.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode* n85 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode*>(i85->slice(se125, h56));
          SUPPLIER_CNT_mPARTSUPP1_E1_12_entry* e85;
         
          if (n85 && (e85 = n85->obj)) {
            do {                
              STRING_TYPE p_brand = e85->P_BRAND;
              STRING_TYPE p_type = e85->P_TYPE;
              long p_size = e85->P_SIZE;
              long v85 = e85->__av;
              (/*if */(l12 == 0L) ? agg20.addOrDelOnZero(st56.modify(p_brand,p_type,p_size,v85), v85) : (void)0);
              n85 = n85->nxt;
            } while (n85 && (e85 = n85->obj) && h56 == n85->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::equals(se125, *e85)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0* i86 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_14.index[1]);
          const HASH_RES_t h57 = SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::hash(se126.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode* n86 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode*>(i86->slice(se126, h57));
          SUPPLIER_CNT_mPARTSUPP1_E1_14_entry* e86;
         
          if (n86 && (e86 = n86->obj)) {
            do {                
              STRING_TYPE p_brand = e86->P_BRAND;
              STRING_TYPE p_type = e86->P_TYPE;
              long p_size = e86->P_SIZE;
              long v86 = e86->__av;
              (/*if */(l12 == 0L) ? agg20.addOrDelOnZero(st57.modify(p_brand,p_type,p_size,v86), v86) : (void)0);
              n86 = n86->nxt;
            } while (n86 && (e86 = n86->obj) && h57 == n86->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::equals(se126, *e86)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0* i87 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_16.index[1]);
          const HASH_RES_t h58 = SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::hash(se127.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode* n87 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode*>(i87->slice(se127, h58));
          SUPPLIER_CNT_mPARTSUPP1_E1_16_entry* e87;
         
          if (n87 && (e87 = n87->obj)) {
            do {                
              STRING_TYPE p_brand = e87->P_BRAND;
              STRING_TYPE p_type = e87->P_TYPE;
              long p_size = e87->P_SIZE;
              long v87 = e87->__av;
              (/*if */(l12 == 0L) ? agg20.addOrDelOnZero(st58.modify(p_brand,p_type,p_size,v87), v87) : (void)0);
              n87 = n87->nxt;
            } while (n87 && (e87 = n87->obj) && h58 == n87->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::equals(se127, *e87)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i88 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg20.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n88; 
          tuple4_SSL_L* e88;
        
          for (size_t i = 0; i < i88->size_; i++)
          {
            n88 = i88->buckets_ + i;
            while (n88 && (e88 = n88->obj))
            {
              STRING_TYPE p_brand = e88->_1;
              STRING_TYPE p_type = e88->_2;
              long p_size = e88->_3;  
              long v88 = e88->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se101.modify(p_brand,p_type,p_size),((v88 != 0 ? 1L : 0L) * -1L));      
              n88 = n88->nxt;
            }
          }
        }(/*if */(0L != Upreg_match(preg2,supplier_comment)) ? SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.addOrDelOnZero(se128.modify(supplier_suppkey),-1L) : (void)0);
      }
    }
    void on_insert_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        agg21.clear();
        
        agg22.clear();
        
        long l13 = 0L;
        {  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123* i89 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123::IdxNode* n89; 
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e89;
        
          for (size_t i = 0; i < i89->size_; i++)
          {
            n89 = i89->buckets_ + i;
            while (n89 && (e89 = n89->obj))
            {
                long ps_suppkey = e89->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e89->P_BRAND;
                STRING_TYPE p_type = e89->P_TYPE;
                long p_size = e89->P_SIZE;
                long v89 = e89->__av;
                (/*if */(l13 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se130.modify(ps_suppkey))) ? agg22.addOrDelOnZero(st59.modify(ps_suppkey,p_brand,p_type,p_size,v89), v89) : (void)0);
              n89 = n89->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123* i90 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123::IdxNode* n90; 
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e90;
        
          for (size_t i = 0; i < i90->size_; i++)
          {
            n90 = i90->buckets_ + i;
            while (n90 && (e90 = n90->obj))
            {
                long ps_suppkey = e90->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e90->P_BRAND;
                STRING_TYPE p_type = e90->P_TYPE;
                long p_size = e90->P_SIZE;
                long v90 = e90->__av;
                (/*if */(l13 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se131.modify(ps_suppkey))) ? agg22.addOrDelOnZero(st60.modify(ps_suppkey,p_brand,p_type,p_size,v90), v90) : (void)0);
              n90 = n90->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123* i91 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_6.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123::IdxNode* n91; 
          SUPPLIER_CNT_mPARTSUPP1_E1_6_entry* e91;
        
          for (size_t i = 0; i < i91->size_; i++)
          {
            n91 = i91->buckets_ + i;
            while (n91 && (e91 = n91->obj))
            {
                long ps_suppkey = e91->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e91->P_BRAND;
                STRING_TYPE p_type = e91->P_TYPE;
                long p_size = e91->P_SIZE;
                long v91 = e91->__av;
                (/*if */(l13 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se132.modify(ps_suppkey))) ? agg22.addOrDelOnZero(st61.modify(ps_suppkey,p_brand,p_type,p_size,v91), v91) : (void)0);
              n91 = n91->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123* i92 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_8.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123::IdxNode* n92; 
          SUPPLIER_CNT_mPARTSUPP1_E1_8_entry* e92;
        
          for (size_t i = 0; i < i92->size_; i++)
          {
            n92 = i92->buckets_ + i;
            while (n92 && (e92 = n92->obj))
            {
                long ps_suppkey = e92->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e92->P_BRAND;
                STRING_TYPE p_type = e92->P_TYPE;
                long p_size = e92->P_SIZE;
                long v92 = e92->__av;
                (/*if */(l13 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se133.modify(ps_suppkey))) ? agg22.addOrDelOnZero(st62.modify(ps_suppkey,p_brand,p_type,p_size,v92), v92) : (void)0);
              n92 = n92->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123* i93 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_10.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123::IdxNode* n93; 
          SUPPLIER_CNT_mPARTSUPP1_E1_10_entry* e93;
        
          for (size_t i = 0; i < i93->size_; i++)
          {
            n93 = i93->buckets_ + i;
            while (n93 && (e93 = n93->obj))
            {
                long ps_suppkey = e93->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e93->P_BRAND;
                STRING_TYPE p_type = e93->P_TYPE;
                long p_size = e93->P_SIZE;
                long v93 = e93->__av;
                (/*if */(l13 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se134.modify(ps_suppkey))) ? agg22.addOrDelOnZero(st63.modify(ps_suppkey,p_brand,p_type,p_size,v93), v93) : (void)0);
              n93 = n93->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123* i94 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_12.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123::IdxNode* n94; 
          SUPPLIER_CNT_mPARTSUPP1_E1_12_entry* e94;
        
          for (size_t i = 0; i < i94->size_; i++)
          {
            n94 = i94->buckets_ + i;
            while (n94 && (e94 = n94->obj))
            {
                long ps_suppkey = e94->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e94->P_BRAND;
                STRING_TYPE p_type = e94->P_TYPE;
                long p_size = e94->P_SIZE;
                long v94 = e94->__av;
                (/*if */(l13 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se135.modify(ps_suppkey))) ? agg22.addOrDelOnZero(st64.modify(ps_suppkey,p_brand,p_type,p_size,v94), v94) : (void)0);
              n94 = n94->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123* i95 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_14.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123::IdxNode* n95; 
          SUPPLIER_CNT_mPARTSUPP1_E1_14_entry* e95;
        
          for (size_t i = 0; i < i95->size_; i++)
          {
            n95 = i95->buckets_ + i;
            while (n95 && (e95 = n95->obj))
            {
                long ps_suppkey = e95->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e95->P_BRAND;
                STRING_TYPE p_type = e95->P_TYPE;
                long p_size = e95->P_SIZE;
                long v95 = e95->__av;
                (/*if */(l13 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se136.modify(ps_suppkey))) ? agg22.addOrDelOnZero(st65.modify(ps_suppkey,p_brand,p_type,p_size,v95), v95) : (void)0);
              n95 = n95->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123* i96 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_16.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123::IdxNode* n96; 
          SUPPLIER_CNT_mPARTSUPP1_E1_16_entry* e96;
        
          for (size_t i = 0; i < i96->size_; i++)
          {
            n96 = i96->buckets_ + i;
            while (n96 && (e96 = n96->obj))
            {
                long ps_suppkey = e96->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e96->P_BRAND;
                STRING_TYPE p_type = e96->P_TYPE;
                long p_size = e96->P_SIZE;
                long v96 = e96->__av;
                (/*if */(l13 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se137.modify(ps_suppkey))) ? agg22.addOrDelOnZero(st66.modify(ps_suppkey,p_brand,p_type,p_size,v96), v96) : (void)0);
              n96 = n96->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple5_LSSL_L, long>* i97 = static_cast<HashIndex<tuple5_LSSL_L, long>*>(agg22.index[0]);
          HashIndex<tuple5_LSSL_L, long>::IdxNode* n97; 
          tuple5_LSSL_L* e97;
        
          for (size_t i = 0; i < i97->size_; i++)
          {
            n97 = i97->buckets_ + i;
            while (n97 && (e97 = n97->obj))
            {
              long ps_suppkey = e97->_1;
              STRING_TYPE p_brand = e97->_2;
              STRING_TYPE p_type = e97->_3;
              long p_size = e97->_4;  
              long v97 = e97->__av; 
            agg21.addOrDelOnZero(st67.modify(p_brand,p_type,p_size,(v97 != 0 ? 1L : 0L)), (v97 != 0 ? 1L : 0L));      
              n97 = n97->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i98 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg21.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n98; 
          tuple4_SSL_L* e98;
        
          for (size_t i = 0; i < i98->size_; i++)
          {
            n98 = i98->buckets_ + i;
            while (n98 && (e98 = n98->obj))
            {
              STRING_TYPE p_brand = e98->_1;
              STRING_TYPE p_type = e98->_2;
              long p_size = e98->_3;  
              long v98 = e98->__av; 
            if (SUPPLIER_CNT.getValueOrDefault(se129.modify(p_brand,p_type,p_size))==0) SUPPLIER_CNT.setOrDelOnZero(se129, v98);      
              n98 = n98->nxt;
            }
          }
        }agg23.clear();
        
        long l14 = SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se138.modify(partsupp_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i99 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h59 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se139.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n99 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i99->slice(se139, h59));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e99;
         
          if (n99 && (e99 = n99->obj)) {
            do {                
              STRING_TYPE p_brand = e99->P_BRAND;
              STRING_TYPE p_type = e99->P_TYPE;
              long p_size = e99->P_SIZE;
              long v99 = e99->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st68.modify(p_brand,p_type,p_size,v99), v99) : (void)0);
              n99 = n99->nxt;
            } while (n99 && (e99 = n99->obj) && h59 == n99->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se139, *e99)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0* i100 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h60 = SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::hash(se140.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode* n100 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode*>(i100->slice(se140, h60));
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e100;
         
          if (n100 && (e100 = n100->obj)) {
            do {                
              STRING_TYPE p_brand = e100->P_BRAND;
              STRING_TYPE p_type = e100->P_TYPE;
              long p_size = e100->P_SIZE;
              long v100 = e100->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st69.modify(p_brand,p_type,p_size,v100), v100) : (void)0);
              n100 = n100->nxt;
            } while (n100 && (e100 = n100->obj) && h60 == n100->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::equals(se140, *e100)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0* i101 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_6.index[1]);
          const HASH_RES_t h61 = SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::hash(se141.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode* n101 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode*>(i101->slice(se141, h61));
          SUPPLIER_CNT_mPARTSUPP1_E1_6_entry* e101;
         
          if (n101 && (e101 = n101->obj)) {
            do {                
              STRING_TYPE p_brand = e101->P_BRAND;
              STRING_TYPE p_type = e101->P_TYPE;
              long p_size = e101->P_SIZE;
              long v101 = e101->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st70.modify(p_brand,p_type,p_size,v101), v101) : (void)0);
              n101 = n101->nxt;
            } while (n101 && (e101 = n101->obj) && h61 == n101->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::equals(se141, *e101)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0* i102 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_8.index[1]);
          const HASH_RES_t h62 = SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::hash(se142.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode* n102 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode*>(i102->slice(se142, h62));
          SUPPLIER_CNT_mPARTSUPP1_E1_8_entry* e102;
         
          if (n102 && (e102 = n102->obj)) {
            do {                
              STRING_TYPE p_brand = e102->P_BRAND;
              STRING_TYPE p_type = e102->P_TYPE;
              long p_size = e102->P_SIZE;
              long v102 = e102->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st71.modify(p_brand,p_type,p_size,v102), v102) : (void)0);
              n102 = n102->nxt;
            } while (n102 && (e102 = n102->obj) && h62 == n102->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::equals(se142, *e102)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0* i103 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_10.index[1]);
          const HASH_RES_t h63 = SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::hash(se143.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode* n103 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode*>(i103->slice(se143, h63));
          SUPPLIER_CNT_mPARTSUPP1_E1_10_entry* e103;
         
          if (n103 && (e103 = n103->obj)) {
            do {                
              STRING_TYPE p_brand = e103->P_BRAND;
              STRING_TYPE p_type = e103->P_TYPE;
              long p_size = e103->P_SIZE;
              long v103 = e103->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st72.modify(p_brand,p_type,p_size,v103), v103) : (void)0);
              n103 = n103->nxt;
            } while (n103 && (e103 = n103->obj) && h63 == n103->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::equals(se143, *e103)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0* i104 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_12.index[1]);
          const HASH_RES_t h64 = SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::hash(se144.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode* n104 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode*>(i104->slice(se144, h64));
          SUPPLIER_CNT_mPARTSUPP1_E1_12_entry* e104;
         
          if (n104 && (e104 = n104->obj)) {
            do {                
              STRING_TYPE p_brand = e104->P_BRAND;
              STRING_TYPE p_type = e104->P_TYPE;
              long p_size = e104->P_SIZE;
              long v104 = e104->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st73.modify(p_brand,p_type,p_size,v104), v104) : (void)0);
              n104 = n104->nxt;
            } while (n104 && (e104 = n104->obj) && h64 == n104->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::equals(se144, *e104)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0* i105 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_14.index[1]);
          const HASH_RES_t h65 = SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::hash(se145.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode* n105 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode*>(i105->slice(se145, h65));
          SUPPLIER_CNT_mPARTSUPP1_E1_14_entry* e105;
         
          if (n105 && (e105 = n105->obj)) {
            do {                
              STRING_TYPE p_brand = e105->P_BRAND;
              STRING_TYPE p_type = e105->P_TYPE;
              long p_size = e105->P_SIZE;
              long v105 = e105->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st74.modify(p_brand,p_type,p_size,v105), v105) : (void)0);
              n105 = n105->nxt;
            } while (n105 && (e105 = n105->obj) && h65 == n105->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::equals(se145, *e105)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0* i106 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_16.index[1]);
          const HASH_RES_t h66 = SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::hash(se146.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode* n106 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode*>(i106->slice(se146, h66));
          SUPPLIER_CNT_mPARTSUPP1_E1_16_entry* e106;
         
          if (n106 && (e106 = n106->obj)) {
            do {                
              STRING_TYPE p_brand = e106->P_BRAND;
              STRING_TYPE p_type = e106->P_TYPE;
              long p_size = e106->P_SIZE;
              long v106 = e106->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st75.modify(p_brand,p_type,p_size,v106), v106) : (void)0);
              n106 = n106->nxt;
            } while (n106 && (e106 = n106->obj) && h66 == n106->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::equals(se146, *e106)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0* i107 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_17.index[1]);
          const HASH_RES_t h67 = SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0_idxfn::hash(se147.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0::IdxNode* n107 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0::IdxNode*>(i107->slice(se147, h67));
          SUPPLIER_CNT_mPARTSUPP1_E1_17_entry* e107;
         
          if (n107 && (e107 = n107->obj)) {
            do {                
              STRING_TYPE p_brand = e107->P_BRAND;
              STRING_TYPE p_type = e107->P_TYPE;
              long p_size = e107->P_SIZE;
              long v107 = e107->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st76.modify(p_brand,p_type,p_size,v107), v107) : (void)0);
              n107 = n107->nxt;
            } while (n107 && (e107 = n107->obj) && h67 == n107->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0_idxfn::equals(se147, *e107)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0* i108 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_20.index[1]);
          const HASH_RES_t h68 = SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0_idxfn::hash(se148.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0::IdxNode* n108 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0::IdxNode*>(i108->slice(se148, h68));
          SUPPLIER_CNT_mPARTSUPP1_E1_20_entry* e108;
         
          if (n108 && (e108 = n108->obj)) {
            do {                
              STRING_TYPE p_brand = e108->P_BRAND;
              STRING_TYPE p_type = e108->P_TYPE;
              long p_size = e108->P_SIZE;
              long v108 = e108->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st77.modify(p_brand,p_type,p_size,v108), v108) : (void)0);
              n108 = n108->nxt;
            } while (n108 && (e108 = n108->obj) && h68 == n108->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0_idxfn::equals(se148, *e108)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0* i109 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_23.index[1]);
          const HASH_RES_t h69 = SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0_idxfn::hash(se149.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0::IdxNode* n109 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0::IdxNode*>(i109->slice(se149, h69));
          SUPPLIER_CNT_mPARTSUPP1_E1_23_entry* e109;
         
          if (n109 && (e109 = n109->obj)) {
            do {                
              STRING_TYPE p_brand = e109->P_BRAND;
              STRING_TYPE p_type = e109->P_TYPE;
              long p_size = e109->P_SIZE;
              long v109 = e109->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st78.modify(p_brand,p_type,p_size,v109), v109) : (void)0);
              n109 = n109->nxt;
            } while (n109 && (e109 = n109->obj) && h69 == n109->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0_idxfn::equals(se149, *e109)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0* i110 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_26.index[1]);
          const HASH_RES_t h70 = SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0_idxfn::hash(se150.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0::IdxNode* n110 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0::IdxNode*>(i110->slice(se150, h70));
          SUPPLIER_CNT_mPARTSUPP1_E1_26_entry* e110;
         
          if (n110 && (e110 = n110->obj)) {
            do {                
              STRING_TYPE p_brand = e110->P_BRAND;
              STRING_TYPE p_type = e110->P_TYPE;
              long p_size = e110->P_SIZE;
              long v110 = e110->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st79.modify(p_brand,p_type,p_size,v110), v110) : (void)0);
              n110 = n110->nxt;
            } while (n110 && (e110 = n110->obj) && h70 == n110->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0_idxfn::equals(se150, *e110)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0* i111 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_29.index[1]);
          const HASH_RES_t h71 = SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0_idxfn::hash(se151.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0::IdxNode* n111 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0::IdxNode*>(i111->slice(se151, h71));
          SUPPLIER_CNT_mPARTSUPP1_E1_29_entry* e111;
         
          if (n111 && (e111 = n111->obj)) {
            do {                
              STRING_TYPE p_brand = e111->P_BRAND;
              STRING_TYPE p_type = e111->P_TYPE;
              long p_size = e111->P_SIZE;
              long v111 = e111->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st80.modify(p_brand,p_type,p_size,v111), v111) : (void)0);
              n111 = n111->nxt;
            } while (n111 && (e111 = n111->obj) && h71 == n111->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0_idxfn::equals(se151, *e111)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0* i112 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_32.index[1]);
          const HASH_RES_t h72 = SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0_idxfn::hash(se152.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0::IdxNode* n112 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0::IdxNode*>(i112->slice(se152, h72));
          SUPPLIER_CNT_mPARTSUPP1_E1_32_entry* e112;
         
          if (n112 && (e112 = n112->obj)) {
            do {                
              STRING_TYPE p_brand = e112->P_BRAND;
              STRING_TYPE p_type = e112->P_TYPE;
              long p_size = e112->P_SIZE;
              long v112 = e112->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st81.modify(p_brand,p_type,p_size,v112), v112) : (void)0);
              n112 = n112->nxt;
            } while (n112 && (e112 = n112->obj) && h72 == n112->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0_idxfn::equals(se152, *e112)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0* i113 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_35.index[1]);
          const HASH_RES_t h73 = SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0_idxfn::hash(se153.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0::IdxNode* n113 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0::IdxNode*>(i113->slice(se153, h73));
          SUPPLIER_CNT_mPARTSUPP1_E1_35_entry* e113;
         
          if (n113 && (e113 = n113->obj)) {
            do {                
              STRING_TYPE p_brand = e113->P_BRAND;
              STRING_TYPE p_type = e113->P_TYPE;
              long p_size = e113->P_SIZE;
              long v113 = e113->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st82.modify(p_brand,p_type,p_size,v113), v113) : (void)0);
              n113 = n113->nxt;
            } while (n113 && (e113 = n113->obj) && h73 == n113->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0_idxfn::equals(se153, *e113)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0* i114 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_38.index[1]);
          const HASH_RES_t h74 = SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0_idxfn::hash(se154.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0::IdxNode* n114 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0::IdxNode*>(i114->slice(se154, h74));
          SUPPLIER_CNT_mPARTSUPP1_E1_38_entry* e114;
         
          if (n114 && (e114 = n114->obj)) {
            do {                
              STRING_TYPE p_brand = e114->P_BRAND;
              STRING_TYPE p_type = e114->P_TYPE;
              long p_size = e114->P_SIZE;
              long v114 = e114->__av;
              (/*if */(l14 == 0L) ? agg23.addOrDelOnZero(st83.modify(p_brand,p_type,p_size,v114), v114) : (void)0);
              n114 = n114->nxt;
            } while (n114 && (e114 = n114->obj) && h74 == n114->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0_idxfn::equals(se154, *e114)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i115 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg23.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n115; 
          tuple4_SSL_L* e115;
        
          for (size_t i = 0; i < i115->size_; i++)
          {
            n115 = i115->buckets_ + i;
            while (n115 && (e115 = n115->obj))
            {
              STRING_TYPE p_brand = e115->_1;
              STRING_TYPE p_type = e115->_2;
              long p_size = e115->_3;  
              long v115 = e115->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se129.modify(p_brand,p_type,p_size),(v115 != 0 ? 1L : 0L));      
              n115 = n115->nxt;
            }
          }
        }agg24.clear();
        
        long l15 = SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se155.modify(partsupp_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i116 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h75 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se156.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n116 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i116->slice(se156, h75));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e116;
         
          if (n116 && (e116 = n116->obj)) {
            do {                
              STRING_TYPE p_brand = e116->P_BRAND;
              STRING_TYPE p_type = e116->P_TYPE;
              long p_size = e116->P_SIZE;
              long v116 = e116->__av;
              (/*if */(l15 == 0L) ? agg24.addOrDelOnZero(st84.modify(p_brand,p_type,p_size,v116), v116) : (void)0);
              n116 = n116->nxt;
            } while (n116 && (e116 = n116->obj) && h75 == n116->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se156, *e116)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0* i117 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h76 = SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::hash(se157.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode* n117 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode*>(i117->slice(se157, h76));
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e117;
         
          if (n117 && (e117 = n117->obj)) {
            do {                
              STRING_TYPE p_brand = e117->P_BRAND;
              STRING_TYPE p_type = e117->P_TYPE;
              long p_size = e117->P_SIZE;
              long v117 = e117->__av;
              (/*if */(l15 == 0L) ? agg24.addOrDelOnZero(st85.modify(p_brand,p_type,p_size,v117), v117) : (void)0);
              n117 = n117->nxt;
            } while (n117 && (e117 = n117->obj) && h76 == n117->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::equals(se157, *e117)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0* i118 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_6.index[1]);
          const HASH_RES_t h77 = SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::hash(se158.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode* n118 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode*>(i118->slice(se158, h77));
          SUPPLIER_CNT_mPARTSUPP1_E1_6_entry* e118;
         
          if (n118 && (e118 = n118->obj)) {
            do {                
              STRING_TYPE p_brand = e118->P_BRAND;
              STRING_TYPE p_type = e118->P_TYPE;
              long p_size = e118->P_SIZE;
              long v118 = e118->__av;
              (/*if */(l15 == 0L) ? agg24.addOrDelOnZero(st86.modify(p_brand,p_type,p_size,v118), v118) : (void)0);
              n118 = n118->nxt;
            } while (n118 && (e118 = n118->obj) && h77 == n118->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::equals(se158, *e118)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0* i119 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_8.index[1]);
          const HASH_RES_t h78 = SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::hash(se159.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode* n119 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode*>(i119->slice(se159, h78));
          SUPPLIER_CNT_mPARTSUPP1_E1_8_entry* e119;
         
          if (n119 && (e119 = n119->obj)) {
            do {                
              STRING_TYPE p_brand = e119->P_BRAND;
              STRING_TYPE p_type = e119->P_TYPE;
              long p_size = e119->P_SIZE;
              long v119 = e119->__av;
              (/*if */(l15 == 0L) ? agg24.addOrDelOnZero(st87.modify(p_brand,p_type,p_size,v119), v119) : (void)0);
              n119 = n119->nxt;
            } while (n119 && (e119 = n119->obj) && h78 == n119->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::equals(se159, *e119)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0* i120 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_10.index[1]);
          const HASH_RES_t h79 = SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::hash(se160.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode* n120 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode*>(i120->slice(se160, h79));
          SUPPLIER_CNT_mPARTSUPP1_E1_10_entry* e120;
         
          if (n120 && (e120 = n120->obj)) {
            do {                
              STRING_TYPE p_brand = e120->P_BRAND;
              STRING_TYPE p_type = e120->P_TYPE;
              long p_size = e120->P_SIZE;
              long v120 = e120->__av;
              (/*if */(l15 == 0L) ? agg24.addOrDelOnZero(st88.modify(p_brand,p_type,p_size,v120), v120) : (void)0);
              n120 = n120->nxt;
            } while (n120 && (e120 = n120->obj) && h79 == n120->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::equals(se160, *e120)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0* i121 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_12.index[1]);
          const HASH_RES_t h80 = SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::hash(se161.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode* n121 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode*>(i121->slice(se161, h80));
          SUPPLIER_CNT_mPARTSUPP1_E1_12_entry* e121;
         
          if (n121 && (e121 = n121->obj)) {
            do {                
              STRING_TYPE p_brand = e121->P_BRAND;
              STRING_TYPE p_type = e121->P_TYPE;
              long p_size = e121->P_SIZE;
              long v121 = e121->__av;
              (/*if */(l15 == 0L) ? agg24.addOrDelOnZero(st89.modify(p_brand,p_type,p_size,v121), v121) : (void)0);
              n121 = n121->nxt;
            } while (n121 && (e121 = n121->obj) && h80 == n121->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::equals(se161, *e121)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0* i122 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_14.index[1]);
          const HASH_RES_t h81 = SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::hash(se162.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode* n122 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode*>(i122->slice(se162, h81));
          SUPPLIER_CNT_mPARTSUPP1_E1_14_entry* e122;
         
          if (n122 && (e122 = n122->obj)) {
            do {                
              STRING_TYPE p_brand = e122->P_BRAND;
              STRING_TYPE p_type = e122->P_TYPE;
              long p_size = e122->P_SIZE;
              long v122 = e122->__av;
              (/*if */(l15 == 0L) ? agg24.addOrDelOnZero(st90.modify(p_brand,p_type,p_size,v122), v122) : (void)0);
              n122 = n122->nxt;
            } while (n122 && (e122 = n122->obj) && h81 == n122->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::equals(se162, *e122)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0* i123 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_16.index[1]);
          const HASH_RES_t h82 = SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::hash(se163.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode* n123 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode*>(i123->slice(se163, h82));
          SUPPLIER_CNT_mPARTSUPP1_E1_16_entry* e123;
         
          if (n123 && (e123 = n123->obj)) {
            do {                
              STRING_TYPE p_brand = e123->P_BRAND;
              STRING_TYPE p_type = e123->P_TYPE;
              long p_size = e123->P_SIZE;
              long v123 = e123->__av;
              (/*if */(l15 == 0L) ? agg24.addOrDelOnZero(st91.modify(p_brand,p_type,p_size,v123), v123) : (void)0);
              n123 = n123->nxt;
            } while (n123 && (e123 = n123->obj) && h82 == n123->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::equals(se163, *e123)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i124 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg24.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n124; 
          tuple4_SSL_L* e124;
        
          for (size_t i = 0; i < i124->size_; i++)
          {
            n124 = i124->buckets_ + i;
            while (n124 && (e124 = n124->obj))
            {
              STRING_TYPE p_brand = e124->_1;
              STRING_TYPE p_type = e124->_2;
              long p_size = e124->_3;  
              long v124 = e124->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se129.modify(p_brand,p_type,p_size),((v124 != 0 ? 1L : 0L) * -1L));      
              n124 = n124->nxt;
            }
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_map_0* i125 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_map_0*>(SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1.index[1]);
          const HASH_RES_t h83 = SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_mapkey0_idxfn::hash(se165.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_map_0::IdxNode* n125 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_map_0::IdxNode*>(i125->slice(se165, h83));
          SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry* e125;
         
          if (n125 && (e125 = n125->obj)) {
            do {                
              STRING_TYPE supplier_cnt_mpartpart_brand = e125->SUPPLIER_CNT_mPARTPART_BRAND;
              STRING_TYPE supplier_cnt_mpartpart_type = e125->SUPPLIER_CNT_mPARTPART_TYPE;
              long supplier_cnt_mpartpart_size = e125->SUPPLIER_CNT_mPARTPART_SIZE;
              long v125 = e125->__av;
              SUPPLIER_CNT_mPART3_E1_1.addOrDelOnZero(se164.modify(partsupp_suppkey,supplier_cnt_mpartpart_brand,supplier_cnt_mpartpart_type,supplier_cnt_mpartpart_size),v125);
              n125 = n125->nxt;
            } while (n125 && (e125 = n125->obj) && h83 == n125->hash &&  SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_mapkey0_idxfn::equals(se165, *e125)); 
          }
        }SUPPLIER_CNT_mPART3_E1_17.addOrDelOnZero(se166.modify(partsupp_partkey,partsupp_suppkey),1L);
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0* i126 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_17.index[1]);
          const HASH_RES_t h84 = SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0_idxfn::hash(se168.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0::IdxNode* n126 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0::IdxNode*>(i126->slice(se168, h84));
          SUPPLIER_CNT_mPARTSUPP1_E1_17_entry* e126;
         
          if (n126 && (e126 = n126->obj)) {
            do {                
              STRING_TYPE p_brand = e126->P_BRAND;
              STRING_TYPE p_type = e126->P_TYPE;
              long p_size = e126->P_SIZE;
              long v126 = e126->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_2.addOrDelOnZero(se167.modify(partsupp_suppkey,p_brand,p_type,p_size),v126);
              n126 = n126->nxt;
            } while (n126 && (e126 = n126->obj) && h84 == n126->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0_idxfn::equals(se168, *e126)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0* i127 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_20.index[1]);
          const HASH_RES_t h85 = SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0_idxfn::hash(se170.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0::IdxNode* n127 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0::IdxNode*>(i127->slice(se170, h85));
          SUPPLIER_CNT_mPARTSUPP1_E1_20_entry* e127;
         
          if (n127 && (e127 = n127->obj)) {
            do {                
              STRING_TYPE p_brand = e127->P_BRAND;
              STRING_TYPE p_type = e127->P_TYPE;
              long p_size = e127->P_SIZE;
              long v127 = e127->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_4.addOrDelOnZero(se169.modify(partsupp_suppkey,p_brand,p_type,p_size),v127);
              n127 = n127->nxt;
            } while (n127 && (e127 = n127->obj) && h85 == n127->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0_idxfn::equals(se170, *e127)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0* i128 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_23.index[1]);
          const HASH_RES_t h86 = SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0_idxfn::hash(se172.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0::IdxNode* n128 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0::IdxNode*>(i128->slice(se172, h86));
          SUPPLIER_CNT_mPARTSUPP1_E1_23_entry* e128;
         
          if (n128 && (e128 = n128->obj)) {
            do {                
              STRING_TYPE p_brand = e128->P_BRAND;
              STRING_TYPE p_type = e128->P_TYPE;
              long p_size = e128->P_SIZE;
              long v128 = e128->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_6.addOrDelOnZero(se171.modify(partsupp_suppkey,p_brand,p_type,p_size),v128);
              n128 = n128->nxt;
            } while (n128 && (e128 = n128->obj) && h86 == n128->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0_idxfn::equals(se172, *e128)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0* i129 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_26.index[1]);
          const HASH_RES_t h87 = SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0_idxfn::hash(se174.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0::IdxNode* n129 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0::IdxNode*>(i129->slice(se174, h87));
          SUPPLIER_CNT_mPARTSUPP1_E1_26_entry* e129;
         
          if (n129 && (e129 = n129->obj)) {
            do {                
              STRING_TYPE p_brand = e129->P_BRAND;
              STRING_TYPE p_type = e129->P_TYPE;
              long p_size = e129->P_SIZE;
              long v129 = e129->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_8.addOrDelOnZero(se173.modify(partsupp_suppkey,p_brand,p_type,p_size),v129);
              n129 = n129->nxt;
            } while (n129 && (e129 = n129->obj) && h87 == n129->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0_idxfn::equals(se174, *e129)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0* i130 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_29.index[1]);
          const HASH_RES_t h88 = SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0_idxfn::hash(se176.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0::IdxNode* n130 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0::IdxNode*>(i130->slice(se176, h88));
          SUPPLIER_CNT_mPARTSUPP1_E1_29_entry* e130;
         
          if (n130 && (e130 = n130->obj)) {
            do {                
              STRING_TYPE p_brand = e130->P_BRAND;
              STRING_TYPE p_type = e130->P_TYPE;
              long p_size = e130->P_SIZE;
              long v130 = e130->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_10.addOrDelOnZero(se175.modify(partsupp_suppkey,p_brand,p_type,p_size),v130);
              n130 = n130->nxt;
            } while (n130 && (e130 = n130->obj) && h88 == n130->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0_idxfn::equals(se176, *e130)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0* i131 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_32.index[1]);
          const HASH_RES_t h89 = SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0_idxfn::hash(se178.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0::IdxNode* n131 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0::IdxNode*>(i131->slice(se178, h89));
          SUPPLIER_CNT_mPARTSUPP1_E1_32_entry* e131;
         
          if (n131 && (e131 = n131->obj)) {
            do {                
              STRING_TYPE p_brand = e131->P_BRAND;
              STRING_TYPE p_type = e131->P_TYPE;
              long p_size = e131->P_SIZE;
              long v131 = e131->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_12.addOrDelOnZero(se177.modify(partsupp_suppkey,p_brand,p_type,p_size),v131);
              n131 = n131->nxt;
            } while (n131 && (e131 = n131->obj) && h89 == n131->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0_idxfn::equals(se178, *e131)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0* i132 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_35.index[1]);
          const HASH_RES_t h90 = SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0_idxfn::hash(se180.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0::IdxNode* n132 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0::IdxNode*>(i132->slice(se180, h90));
          SUPPLIER_CNT_mPARTSUPP1_E1_35_entry* e132;
         
          if (n132 && (e132 = n132->obj)) {
            do {                
              STRING_TYPE p_brand = e132->P_BRAND;
              STRING_TYPE p_type = e132->P_TYPE;
              long p_size = e132->P_SIZE;
              long v132 = e132->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_14.addOrDelOnZero(se179.modify(partsupp_suppkey,p_brand,p_type,p_size),v132);
              n132 = n132->nxt;
            } while (n132 && (e132 = n132->obj) && h90 == n132->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0_idxfn::equals(se180, *e132)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0* i133 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_38.index[1]);
          const HASH_RES_t h91 = SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0_idxfn::hash(se182.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0::IdxNode* n133 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0::IdxNode*>(i133->slice(se182, h91));
          SUPPLIER_CNT_mPARTSUPP1_E1_38_entry* e133;
         
          if (n133 && (e133 = n133->obj)) {
            do {                
              STRING_TYPE p_brand = e133->P_BRAND;
              STRING_TYPE p_type = e133->P_TYPE;
              long p_size = e133->P_SIZE;
              long v133 = e133->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_16.addOrDelOnZero(se181.modify(partsupp_suppkey,p_brand,p_type,p_size),v133);
              n133 = n133->nxt;
            } while (n133 && (e133 = n133->obj) && h91 == n133->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0_idxfn::equals(se182, *e133)); 
          }
        }
      }
    }
    void on_delete_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        agg25.clear();
        
        agg26.clear();
        
        long l16 = 0L;
        {  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123* i134 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0123::IdxNode* n134; 
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e134;
        
          for (size_t i = 0; i < i134->size_; i++)
          {
            n134 = i134->buckets_ + i;
            while (n134 && (e134 = n134->obj))
            {
                long ps_suppkey = e134->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e134->P_BRAND;
                STRING_TYPE p_type = e134->P_TYPE;
                long p_size = e134->P_SIZE;
                long v134 = e134->__av;
                (/*if */(l16 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se184.modify(ps_suppkey))) ? agg26.addOrDelOnZero(st92.modify(ps_suppkey,p_brand,p_type,p_size,v134), v134) : (void)0);
              n134 = n134->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123* i135 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0123::IdxNode* n135; 
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e135;
        
          for (size_t i = 0; i < i135->size_; i++)
          {
            n135 = i135->buckets_ + i;
            while (n135 && (e135 = n135->obj))
            {
                long ps_suppkey = e135->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e135->P_BRAND;
                STRING_TYPE p_type = e135->P_TYPE;
                long p_size = e135->P_SIZE;
                long v135 = e135->__av;
                (/*if */(l16 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se185.modify(ps_suppkey))) ? agg26.addOrDelOnZero(st93.modify(ps_suppkey,p_brand,p_type,p_size,v135), v135) : (void)0);
              n135 = n135->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123* i136 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_6.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0123::IdxNode* n136; 
          SUPPLIER_CNT_mPARTSUPP1_E1_6_entry* e136;
        
          for (size_t i = 0; i < i136->size_; i++)
          {
            n136 = i136->buckets_ + i;
            while (n136 && (e136 = n136->obj))
            {
                long ps_suppkey = e136->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e136->P_BRAND;
                STRING_TYPE p_type = e136->P_TYPE;
                long p_size = e136->P_SIZE;
                long v136 = e136->__av;
                (/*if */(l16 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se186.modify(ps_suppkey))) ? agg26.addOrDelOnZero(st94.modify(ps_suppkey,p_brand,p_type,p_size,v136), v136) : (void)0);
              n136 = n136->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123* i137 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_8.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0123::IdxNode* n137; 
          SUPPLIER_CNT_mPARTSUPP1_E1_8_entry* e137;
        
          for (size_t i = 0; i < i137->size_; i++)
          {
            n137 = i137->buckets_ + i;
            while (n137 && (e137 = n137->obj))
            {
                long ps_suppkey = e137->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e137->P_BRAND;
                STRING_TYPE p_type = e137->P_TYPE;
                long p_size = e137->P_SIZE;
                long v137 = e137->__av;
                (/*if */(l16 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se187.modify(ps_suppkey))) ? agg26.addOrDelOnZero(st95.modify(ps_suppkey,p_brand,p_type,p_size,v137), v137) : (void)0);
              n137 = n137->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123* i138 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_10.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0123::IdxNode* n138; 
          SUPPLIER_CNT_mPARTSUPP1_E1_10_entry* e138;
        
          for (size_t i = 0; i < i138->size_; i++)
          {
            n138 = i138->buckets_ + i;
            while (n138 && (e138 = n138->obj))
            {
                long ps_suppkey = e138->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e138->P_BRAND;
                STRING_TYPE p_type = e138->P_TYPE;
                long p_size = e138->P_SIZE;
                long v138 = e138->__av;
                (/*if */(l16 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se188.modify(ps_suppkey))) ? agg26.addOrDelOnZero(st96.modify(ps_suppkey,p_brand,p_type,p_size,v138), v138) : (void)0);
              n138 = n138->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123* i139 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_12.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0123::IdxNode* n139; 
          SUPPLIER_CNT_mPARTSUPP1_E1_12_entry* e139;
        
          for (size_t i = 0; i < i139->size_; i++)
          {
            n139 = i139->buckets_ + i;
            while (n139 && (e139 = n139->obj))
            {
                long ps_suppkey = e139->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e139->P_BRAND;
                STRING_TYPE p_type = e139->P_TYPE;
                long p_size = e139->P_SIZE;
                long v139 = e139->__av;
                (/*if */(l16 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se189.modify(ps_suppkey))) ? agg26.addOrDelOnZero(st97.modify(ps_suppkey,p_brand,p_type,p_size,v139), v139) : (void)0);
              n139 = n139->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123* i140 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_14.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0123::IdxNode* n140; 
          SUPPLIER_CNT_mPARTSUPP1_E1_14_entry* e140;
        
          for (size_t i = 0; i < i140->size_; i++)
          {
            n140 = i140->buckets_ + i;
            while (n140 && (e140 = n140->obj))
            {
                long ps_suppkey = e140->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e140->P_BRAND;
                STRING_TYPE p_type = e140->P_TYPE;
                long p_size = e140->P_SIZE;
                long v140 = e140->__av;
                (/*if */(l16 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se190.modify(ps_suppkey))) ? agg26.addOrDelOnZero(st98.modify(ps_suppkey,p_brand,p_type,p_size,v140), v140) : (void)0);
              n140 = n140->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123* i141 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123*>(SUPPLIER_CNT_mPARTSUPP1_E1_16.index[0]);
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0123::IdxNode* n141; 
          SUPPLIER_CNT_mPARTSUPP1_E1_16_entry* e141;
        
          for (size_t i = 0; i < i141->size_; i++)
          {
            n141 = i141->buckets_ + i;
            while (n141 && (e141 = n141->obj))
            {
                long ps_suppkey = e141->SUPPLIER_CNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE p_brand = e141->P_BRAND;
                STRING_TYPE p_type = e141->P_TYPE;
                long p_size = e141->P_SIZE;
                long v141 = e141->__av;
                (/*if */(l16 == SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se191.modify(ps_suppkey))) ? agg26.addOrDelOnZero(st99.modify(ps_suppkey,p_brand,p_type,p_size,v141), v141) : (void)0);
              n141 = n141->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple5_LSSL_L, long>* i142 = static_cast<HashIndex<tuple5_LSSL_L, long>*>(agg26.index[0]);
          HashIndex<tuple5_LSSL_L, long>::IdxNode* n142; 
          tuple5_LSSL_L* e142;
        
          for (size_t i = 0; i < i142->size_; i++)
          {
            n142 = i142->buckets_ + i;
            while (n142 && (e142 = n142->obj))
            {
              long ps_suppkey = e142->_1;
              STRING_TYPE p_brand = e142->_2;
              STRING_TYPE p_type = e142->_3;
              long p_size = e142->_4;  
              long v142 = e142->__av; 
            agg25.addOrDelOnZero(st100.modify(p_brand,p_type,p_size,(v142 != 0 ? 1L : 0L)), (v142 != 0 ? 1L : 0L));      
              n142 = n142->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i143 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg25.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n143; 
          tuple4_SSL_L* e143;
        
          for (size_t i = 0; i < i143->size_; i++)
          {
            n143 = i143->buckets_ + i;
            while (n143 && (e143 = n143->obj))
            {
              STRING_TYPE p_brand = e143->_1;
              STRING_TYPE p_type = e143->_2;
              long p_size = e143->_3;  
              long v143 = e143->__av; 
            if (SUPPLIER_CNT.getValueOrDefault(se183.modify(p_brand,p_type,p_size))==0) SUPPLIER_CNT.setOrDelOnZero(se183, v143);      
              n143 = n143->nxt;
            }
          }
        }agg27.clear();
        
        long l17 = SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se192.modify(partsupp_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i144 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h92 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se193.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n144 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i144->slice(se193, h92));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e144;
         
          if (n144 && (e144 = n144->obj)) {
            do {                
              STRING_TYPE p_brand = e144->P_BRAND;
              STRING_TYPE p_type = e144->P_TYPE;
              long p_size = e144->P_SIZE;
              long v144 = e144->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st101.modify(p_brand,p_type,p_size,v144), v144) : (void)0);
              n144 = n144->nxt;
            } while (n144 && (e144 = n144->obj) && h92 == n144->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se193, *e144)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0* i145 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h93 = SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::hash(se194.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode* n145 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode*>(i145->slice(se194, h93));
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e145;
         
          if (n145 && (e145 = n145->obj)) {
            do {                
              STRING_TYPE p_brand = e145->P_BRAND;
              STRING_TYPE p_type = e145->P_TYPE;
              long p_size = e145->P_SIZE;
              long v145 = e145->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st102.modify(p_brand,p_type,p_size,v145), v145) : (void)0);
              n145 = n145->nxt;
            } while (n145 && (e145 = n145->obj) && h93 == n145->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::equals(se194, *e145)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0* i146 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_6.index[1]);
          const HASH_RES_t h94 = SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::hash(se195.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode* n146 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode*>(i146->slice(se195, h94));
          SUPPLIER_CNT_mPARTSUPP1_E1_6_entry* e146;
         
          if (n146 && (e146 = n146->obj)) {
            do {                
              STRING_TYPE p_brand = e146->P_BRAND;
              STRING_TYPE p_type = e146->P_TYPE;
              long p_size = e146->P_SIZE;
              long v146 = e146->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st103.modify(p_brand,p_type,p_size,v146), v146) : (void)0);
              n146 = n146->nxt;
            } while (n146 && (e146 = n146->obj) && h94 == n146->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::equals(se195, *e146)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0* i147 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_8.index[1]);
          const HASH_RES_t h95 = SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::hash(se196.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode* n147 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode*>(i147->slice(se196, h95));
          SUPPLIER_CNT_mPARTSUPP1_E1_8_entry* e147;
         
          if (n147 && (e147 = n147->obj)) {
            do {                
              STRING_TYPE p_brand = e147->P_BRAND;
              STRING_TYPE p_type = e147->P_TYPE;
              long p_size = e147->P_SIZE;
              long v147 = e147->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st104.modify(p_brand,p_type,p_size,v147), v147) : (void)0);
              n147 = n147->nxt;
            } while (n147 && (e147 = n147->obj) && h95 == n147->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::equals(se196, *e147)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0* i148 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_10.index[1]);
          const HASH_RES_t h96 = SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::hash(se197.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode* n148 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode*>(i148->slice(se197, h96));
          SUPPLIER_CNT_mPARTSUPP1_E1_10_entry* e148;
         
          if (n148 && (e148 = n148->obj)) {
            do {                
              STRING_TYPE p_brand = e148->P_BRAND;
              STRING_TYPE p_type = e148->P_TYPE;
              long p_size = e148->P_SIZE;
              long v148 = e148->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st105.modify(p_brand,p_type,p_size,v148), v148) : (void)0);
              n148 = n148->nxt;
            } while (n148 && (e148 = n148->obj) && h96 == n148->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::equals(se197, *e148)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0* i149 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_12.index[1]);
          const HASH_RES_t h97 = SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::hash(se198.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode* n149 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode*>(i149->slice(se198, h97));
          SUPPLIER_CNT_mPARTSUPP1_E1_12_entry* e149;
         
          if (n149 && (e149 = n149->obj)) {
            do {                
              STRING_TYPE p_brand = e149->P_BRAND;
              STRING_TYPE p_type = e149->P_TYPE;
              long p_size = e149->P_SIZE;
              long v149 = e149->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st106.modify(p_brand,p_type,p_size,v149), v149) : (void)0);
              n149 = n149->nxt;
            } while (n149 && (e149 = n149->obj) && h97 == n149->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::equals(se198, *e149)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0* i150 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_14.index[1]);
          const HASH_RES_t h98 = SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::hash(se199.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode* n150 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode*>(i150->slice(se199, h98));
          SUPPLIER_CNT_mPARTSUPP1_E1_14_entry* e150;
         
          if (n150 && (e150 = n150->obj)) {
            do {                
              STRING_TYPE p_brand = e150->P_BRAND;
              STRING_TYPE p_type = e150->P_TYPE;
              long p_size = e150->P_SIZE;
              long v150 = e150->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st107.modify(p_brand,p_type,p_size,v150), v150) : (void)0);
              n150 = n150->nxt;
            } while (n150 && (e150 = n150->obj) && h98 == n150->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::equals(se199, *e150)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0* i151 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_16.index[1]);
          const HASH_RES_t h99 = SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::hash(se200.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode* n151 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode*>(i151->slice(se200, h99));
          SUPPLIER_CNT_mPARTSUPP1_E1_16_entry* e151;
         
          if (n151 && (e151 = n151->obj)) {
            do {                
              STRING_TYPE p_brand = e151->P_BRAND;
              STRING_TYPE p_type = e151->P_TYPE;
              long p_size = e151->P_SIZE;
              long v151 = e151->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st108.modify(p_brand,p_type,p_size,v151), v151) : (void)0);
              n151 = n151->nxt;
            } while (n151 && (e151 = n151->obj) && h99 == n151->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::equals(se200, *e151)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0* i152 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_17.index[1]);
          const HASH_RES_t h100 = SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0_idxfn::hash(se201.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0::IdxNode* n152 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0::IdxNode*>(i152->slice(se201, h100));
          SUPPLIER_CNT_mPARTSUPP1_E1_17_entry* e152;
         
          if (n152 && (e152 = n152->obj)) {
            do {                
              STRING_TYPE p_brand = e152->P_BRAND;
              STRING_TYPE p_type = e152->P_TYPE;
              long p_size = e152->P_SIZE;
              long v152 = e152->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st109.modify(p_brand,p_type,p_size,(v152 * -1L)), (v152 * -1L)) : (void)0);
              n152 = n152->nxt;
            } while (n152 && (e152 = n152->obj) && h100 == n152->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0_idxfn::equals(se201, *e152)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0* i153 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_20.index[1]);
          const HASH_RES_t h101 = SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0_idxfn::hash(se202.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0::IdxNode* n153 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0::IdxNode*>(i153->slice(se202, h101));
          SUPPLIER_CNT_mPARTSUPP1_E1_20_entry* e153;
         
          if (n153 && (e153 = n153->obj)) {
            do {                
              STRING_TYPE p_brand = e153->P_BRAND;
              STRING_TYPE p_type = e153->P_TYPE;
              long p_size = e153->P_SIZE;
              long v153 = e153->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st110.modify(p_brand,p_type,p_size,(v153 * -1L)), (v153 * -1L)) : (void)0);
              n153 = n153->nxt;
            } while (n153 && (e153 = n153->obj) && h101 == n153->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0_idxfn::equals(se202, *e153)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0* i154 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_23.index[1]);
          const HASH_RES_t h102 = SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0_idxfn::hash(se203.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0::IdxNode* n154 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0::IdxNode*>(i154->slice(se203, h102));
          SUPPLIER_CNT_mPARTSUPP1_E1_23_entry* e154;
         
          if (n154 && (e154 = n154->obj)) {
            do {                
              STRING_TYPE p_brand = e154->P_BRAND;
              STRING_TYPE p_type = e154->P_TYPE;
              long p_size = e154->P_SIZE;
              long v154 = e154->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st111.modify(p_brand,p_type,p_size,(v154 * -1L)), (v154 * -1L)) : (void)0);
              n154 = n154->nxt;
            } while (n154 && (e154 = n154->obj) && h102 == n154->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0_idxfn::equals(se203, *e154)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0* i155 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_26.index[1]);
          const HASH_RES_t h103 = SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0_idxfn::hash(se204.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0::IdxNode* n155 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0::IdxNode*>(i155->slice(se204, h103));
          SUPPLIER_CNT_mPARTSUPP1_E1_26_entry* e155;
         
          if (n155 && (e155 = n155->obj)) {
            do {                
              STRING_TYPE p_brand = e155->P_BRAND;
              STRING_TYPE p_type = e155->P_TYPE;
              long p_size = e155->P_SIZE;
              long v155 = e155->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st112.modify(p_brand,p_type,p_size,(v155 * -1L)), (v155 * -1L)) : (void)0);
              n155 = n155->nxt;
            } while (n155 && (e155 = n155->obj) && h103 == n155->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0_idxfn::equals(se204, *e155)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0* i156 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_29.index[1]);
          const HASH_RES_t h104 = SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0_idxfn::hash(se205.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0::IdxNode* n156 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0::IdxNode*>(i156->slice(se205, h104));
          SUPPLIER_CNT_mPARTSUPP1_E1_29_entry* e156;
         
          if (n156 && (e156 = n156->obj)) {
            do {                
              STRING_TYPE p_brand = e156->P_BRAND;
              STRING_TYPE p_type = e156->P_TYPE;
              long p_size = e156->P_SIZE;
              long v156 = e156->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st113.modify(p_brand,p_type,p_size,(v156 * -1L)), (v156 * -1L)) : (void)0);
              n156 = n156->nxt;
            } while (n156 && (e156 = n156->obj) && h104 == n156->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0_idxfn::equals(se205, *e156)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0* i157 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_32.index[1]);
          const HASH_RES_t h105 = SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0_idxfn::hash(se206.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0::IdxNode* n157 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0::IdxNode*>(i157->slice(se206, h105));
          SUPPLIER_CNT_mPARTSUPP1_E1_32_entry* e157;
         
          if (n157 && (e157 = n157->obj)) {
            do {                
              STRING_TYPE p_brand = e157->P_BRAND;
              STRING_TYPE p_type = e157->P_TYPE;
              long p_size = e157->P_SIZE;
              long v157 = e157->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st114.modify(p_brand,p_type,p_size,(v157 * -1L)), (v157 * -1L)) : (void)0);
              n157 = n157->nxt;
            } while (n157 && (e157 = n157->obj) && h105 == n157->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0_idxfn::equals(se206, *e157)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0* i158 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_35.index[1]);
          const HASH_RES_t h106 = SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0_idxfn::hash(se207.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0::IdxNode* n158 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0::IdxNode*>(i158->slice(se207, h106));
          SUPPLIER_CNT_mPARTSUPP1_E1_35_entry* e158;
         
          if (n158 && (e158 = n158->obj)) {
            do {                
              STRING_TYPE p_brand = e158->P_BRAND;
              STRING_TYPE p_type = e158->P_TYPE;
              long p_size = e158->P_SIZE;
              long v158 = e158->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st115.modify(p_brand,p_type,p_size,(v158 * -1L)), (v158 * -1L)) : (void)0);
              n158 = n158->nxt;
            } while (n158 && (e158 = n158->obj) && h106 == n158->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0_idxfn::equals(se207, *e158)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0* i159 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_38.index[1]);
          const HASH_RES_t h107 = SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0_idxfn::hash(se208.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0::IdxNode* n159 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0::IdxNode*>(i159->slice(se208, h107));
          SUPPLIER_CNT_mPARTSUPP1_E1_38_entry* e159;
         
          if (n159 && (e159 = n159->obj)) {
            do {                
              STRING_TYPE p_brand = e159->P_BRAND;
              STRING_TYPE p_type = e159->P_TYPE;
              long p_size = e159->P_SIZE;
              long v159 = e159->__av;
              (/*if */(l17 == 0L) ? agg27.addOrDelOnZero(st116.modify(p_brand,p_type,p_size,(v159 * -1L)), (v159 * -1L)) : (void)0);
              n159 = n159->nxt;
            } while (n159 && (e159 = n159->obj) && h107 == n159->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0_idxfn::equals(se208, *e159)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i160 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg27.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n160; 
          tuple4_SSL_L* e160;
        
          for (size_t i = 0; i < i160->size_; i++)
          {
            n160 = i160->buckets_ + i;
            while (n160 && (e160 = n160->obj))
            {
              STRING_TYPE p_brand = e160->_1;
              STRING_TYPE p_type = e160->_2;
              long p_size = e160->_3;  
              long v160 = e160->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se183.modify(p_brand,p_type,p_size),(v160 != 0 ? 1L : 0L));      
              n160 = n160->nxt;
            }
          }
        }agg28.clear();
        
        long l18 = SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1.getValueOrDefault(se209.modify(partsupp_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0* i161 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h108 = SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::hash(se210.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode* n161 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_2_map_0::IdxNode*>(i161->slice(se210, h108));
          SUPPLIER_CNT_mPARTSUPP1_E1_2_entry* e161;
         
          if (n161 && (e161 = n161->obj)) {
            do {                
              STRING_TYPE p_brand = e161->P_BRAND;
              STRING_TYPE p_type = e161->P_TYPE;
              long p_size = e161->P_SIZE;
              long v161 = e161->__av;
              (/*if */(l18 == 0L) ? agg28.addOrDelOnZero(st117.modify(p_brand,p_type,p_size,v161), v161) : (void)0);
              n161 = n161->nxt;
            } while (n161 && (e161 = n161->obj) && h108 == n161->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_2_mapkey0_idxfn::equals(se210, *e161)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0* i162 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h109 = SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::hash(se211.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode* n162 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_4_map_0::IdxNode*>(i162->slice(se211, h109));
          SUPPLIER_CNT_mPARTSUPP1_E1_4_entry* e162;
         
          if (n162 && (e162 = n162->obj)) {
            do {                
              STRING_TYPE p_brand = e162->P_BRAND;
              STRING_TYPE p_type = e162->P_TYPE;
              long p_size = e162->P_SIZE;
              long v162 = e162->__av;
              (/*if */(l18 == 0L) ? agg28.addOrDelOnZero(st118.modify(p_brand,p_type,p_size,v162), v162) : (void)0);
              n162 = n162->nxt;
            } while (n162 && (e162 = n162->obj) && h109 == n162->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_4_mapkey0_idxfn::equals(se211, *e162)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0* i163 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_6.index[1]);
          const HASH_RES_t h110 = SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::hash(se212.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode* n163 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_6_map_0::IdxNode*>(i163->slice(se212, h110));
          SUPPLIER_CNT_mPARTSUPP1_E1_6_entry* e163;
         
          if (n163 && (e163 = n163->obj)) {
            do {                
              STRING_TYPE p_brand = e163->P_BRAND;
              STRING_TYPE p_type = e163->P_TYPE;
              long p_size = e163->P_SIZE;
              long v163 = e163->__av;
              (/*if */(l18 == 0L) ? agg28.addOrDelOnZero(st119.modify(p_brand,p_type,p_size,v163), v163) : (void)0);
              n163 = n163->nxt;
            } while (n163 && (e163 = n163->obj) && h110 == n163->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_6_mapkey0_idxfn::equals(se212, *e163)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0* i164 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_8.index[1]);
          const HASH_RES_t h111 = SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::hash(se213.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode* n164 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_8_map_0::IdxNode*>(i164->slice(se213, h111));
          SUPPLIER_CNT_mPARTSUPP1_E1_8_entry* e164;
         
          if (n164 && (e164 = n164->obj)) {
            do {                
              STRING_TYPE p_brand = e164->P_BRAND;
              STRING_TYPE p_type = e164->P_TYPE;
              long p_size = e164->P_SIZE;
              long v164 = e164->__av;
              (/*if */(l18 == 0L) ? agg28.addOrDelOnZero(st120.modify(p_brand,p_type,p_size,v164), v164) : (void)0);
              n164 = n164->nxt;
            } while (n164 && (e164 = n164->obj) && h111 == n164->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_8_mapkey0_idxfn::equals(se213, *e164)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0* i165 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_10.index[1]);
          const HASH_RES_t h112 = SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::hash(se214.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode* n165 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_10_map_0::IdxNode*>(i165->slice(se214, h112));
          SUPPLIER_CNT_mPARTSUPP1_E1_10_entry* e165;
         
          if (n165 && (e165 = n165->obj)) {
            do {                
              STRING_TYPE p_brand = e165->P_BRAND;
              STRING_TYPE p_type = e165->P_TYPE;
              long p_size = e165->P_SIZE;
              long v165 = e165->__av;
              (/*if */(l18 == 0L) ? agg28.addOrDelOnZero(st121.modify(p_brand,p_type,p_size,v165), v165) : (void)0);
              n165 = n165->nxt;
            } while (n165 && (e165 = n165->obj) && h112 == n165->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_10_mapkey0_idxfn::equals(se214, *e165)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0* i166 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_12.index[1]);
          const HASH_RES_t h113 = SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::hash(se215.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode* n166 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_12_map_0::IdxNode*>(i166->slice(se215, h113));
          SUPPLIER_CNT_mPARTSUPP1_E1_12_entry* e166;
         
          if (n166 && (e166 = n166->obj)) {
            do {                
              STRING_TYPE p_brand = e166->P_BRAND;
              STRING_TYPE p_type = e166->P_TYPE;
              long p_size = e166->P_SIZE;
              long v166 = e166->__av;
              (/*if */(l18 == 0L) ? agg28.addOrDelOnZero(st122.modify(p_brand,p_type,p_size,v166), v166) : (void)0);
              n166 = n166->nxt;
            } while (n166 && (e166 = n166->obj) && h113 == n166->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_12_mapkey0_idxfn::equals(se215, *e166)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0* i167 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_14.index[1]);
          const HASH_RES_t h114 = SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::hash(se216.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode* n167 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_14_map_0::IdxNode*>(i167->slice(se216, h114));
          SUPPLIER_CNT_mPARTSUPP1_E1_14_entry* e167;
         
          if (n167 && (e167 = n167->obj)) {
            do {                
              STRING_TYPE p_brand = e167->P_BRAND;
              STRING_TYPE p_type = e167->P_TYPE;
              long p_size = e167->P_SIZE;
              long v167 = e167->__av;
              (/*if */(l18 == 0L) ? agg28.addOrDelOnZero(st123.modify(p_brand,p_type,p_size,v167), v167) : (void)0);
              n167 = n167->nxt;
            } while (n167 && (e167 = n167->obj) && h114 == n167->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_14_mapkey0_idxfn::equals(se216, *e167)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0* i168 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_16.index[1]);
          const HASH_RES_t h115 = SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::hash(se217.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode* n168 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_16_map_0::IdxNode*>(i168->slice(se217, h115));
          SUPPLIER_CNT_mPARTSUPP1_E1_16_entry* e168;
         
          if (n168 && (e168 = n168->obj)) {
            do {                
              STRING_TYPE p_brand = e168->P_BRAND;
              STRING_TYPE p_type = e168->P_TYPE;
              long p_size = e168->P_SIZE;
              long v168 = e168->__av;
              (/*if */(l18 == 0L) ? agg28.addOrDelOnZero(st124.modify(p_brand,p_type,p_size,v168), v168) : (void)0);
              n168 = n168->nxt;
            } while (n168 && (e168 = n168->obj) && h115 == n168->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_16_mapkey0_idxfn::equals(se217, *e168)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i169 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg28.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n169; 
          tuple4_SSL_L* e169;
        
          for (size_t i = 0; i < i169->size_; i++)
          {
            n169 = i169->buckets_ + i;
            while (n169 && (e169 = n169->obj))
            {
              STRING_TYPE p_brand = e169->_1;
              STRING_TYPE p_type = e169->_2;
              long p_size = e169->_3;  
              long v169 = e169->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se183.modify(p_brand,p_type,p_size),((v169 != 0 ? 1L : 0L) * -1L));      
              n169 = n169->nxt;
            }
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_map_0* i170 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_map_0*>(SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1.index[1]);
          const HASH_RES_t h116 = SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_mapkey0_idxfn::hash(se219.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_map_0::IdxNode* n170 = static_cast<HashIndex_SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_map_0::IdxNode*>(i170->slice(se219, h116));
          SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry* e170;
         
          if (n170 && (e170 = n170->obj)) {
            do {                
              STRING_TYPE supplier_cnt_mpartpart_brand = e170->SUPPLIER_CNT_mPARTPART_BRAND;
              STRING_TYPE supplier_cnt_mpartpart_type = e170->SUPPLIER_CNT_mPARTPART_TYPE;
              long supplier_cnt_mpartpart_size = e170->SUPPLIER_CNT_mPARTPART_SIZE;
              long v170 = e170->__av;
              SUPPLIER_CNT_mPART3_E1_1.addOrDelOnZero(se218.modify(partsupp_suppkey,supplier_cnt_mpartpart_brand,supplier_cnt_mpartpart_type,supplier_cnt_mpartpart_size),(v170 * -1L));
              n170 = n170->nxt;
            } while (n170 && (e170 = n170->obj) && h116 == n170->hash &&  SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_mapkey0_idxfn::equals(se219, *e170)); 
          }
        }SUPPLIER_CNT_mPART3_E1_17.addOrDelOnZero(se220.modify(partsupp_partkey,partsupp_suppkey),-1L);
        { //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0* i171 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_17.index[1]);
          const HASH_RES_t h117 = SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0_idxfn::hash(se222.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0::IdxNode* n171 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_17_map_0::IdxNode*>(i171->slice(se222, h117));
          SUPPLIER_CNT_mPARTSUPP1_E1_17_entry* e171;
         
          if (n171 && (e171 = n171->obj)) {
            do {                
              STRING_TYPE p_brand = e171->P_BRAND;
              STRING_TYPE p_type = e171->P_TYPE;
              long p_size = e171->P_SIZE;
              long v171 = e171->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_2.addOrDelOnZero(se221.modify(partsupp_suppkey,p_brand,p_type,p_size),(v171 * -1L));
              n171 = n171->nxt;
            } while (n171 && (e171 = n171->obj) && h117 == n171->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_17_mapkey0_idxfn::equals(se222, *e171)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0* i172 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_20.index[1]);
          const HASH_RES_t h118 = SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0_idxfn::hash(se224.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0::IdxNode* n172 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_20_map_0::IdxNode*>(i172->slice(se224, h118));
          SUPPLIER_CNT_mPARTSUPP1_E1_20_entry* e172;
         
          if (n172 && (e172 = n172->obj)) {
            do {                
              STRING_TYPE p_brand = e172->P_BRAND;
              STRING_TYPE p_type = e172->P_TYPE;
              long p_size = e172->P_SIZE;
              long v172 = e172->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_4.addOrDelOnZero(se223.modify(partsupp_suppkey,p_brand,p_type,p_size),(v172 * -1L));
              n172 = n172->nxt;
            } while (n172 && (e172 = n172->obj) && h118 == n172->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_20_mapkey0_idxfn::equals(se224, *e172)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0* i173 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_23.index[1]);
          const HASH_RES_t h119 = SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0_idxfn::hash(se226.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0::IdxNode* n173 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_23_map_0::IdxNode*>(i173->slice(se226, h119));
          SUPPLIER_CNT_mPARTSUPP1_E1_23_entry* e173;
         
          if (n173 && (e173 = n173->obj)) {
            do {                
              STRING_TYPE p_brand = e173->P_BRAND;
              STRING_TYPE p_type = e173->P_TYPE;
              long p_size = e173->P_SIZE;
              long v173 = e173->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_6.addOrDelOnZero(se225.modify(partsupp_suppkey,p_brand,p_type,p_size),(v173 * -1L));
              n173 = n173->nxt;
            } while (n173 && (e173 = n173->obj) && h119 == n173->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_23_mapkey0_idxfn::equals(se226, *e173)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0* i174 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_26.index[1]);
          const HASH_RES_t h120 = SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0_idxfn::hash(se228.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0::IdxNode* n174 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_26_map_0::IdxNode*>(i174->slice(se228, h120));
          SUPPLIER_CNT_mPARTSUPP1_E1_26_entry* e174;
         
          if (n174 && (e174 = n174->obj)) {
            do {                
              STRING_TYPE p_brand = e174->P_BRAND;
              STRING_TYPE p_type = e174->P_TYPE;
              long p_size = e174->P_SIZE;
              long v174 = e174->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_8.addOrDelOnZero(se227.modify(partsupp_suppkey,p_brand,p_type,p_size),(v174 * -1L));
              n174 = n174->nxt;
            } while (n174 && (e174 = n174->obj) && h120 == n174->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_26_mapkey0_idxfn::equals(se228, *e174)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0* i175 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_29.index[1]);
          const HASH_RES_t h121 = SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0_idxfn::hash(se230.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0::IdxNode* n175 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_29_map_0::IdxNode*>(i175->slice(se230, h121));
          SUPPLIER_CNT_mPARTSUPP1_E1_29_entry* e175;
         
          if (n175 && (e175 = n175->obj)) {
            do {                
              STRING_TYPE p_brand = e175->P_BRAND;
              STRING_TYPE p_type = e175->P_TYPE;
              long p_size = e175->P_SIZE;
              long v175 = e175->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_10.addOrDelOnZero(se229.modify(partsupp_suppkey,p_brand,p_type,p_size),(v175 * -1L));
              n175 = n175->nxt;
            } while (n175 && (e175 = n175->obj) && h121 == n175->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_29_mapkey0_idxfn::equals(se230, *e175)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0* i176 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_32.index[1]);
          const HASH_RES_t h122 = SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0_idxfn::hash(se232.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0::IdxNode* n176 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_32_map_0::IdxNode*>(i176->slice(se232, h122));
          SUPPLIER_CNT_mPARTSUPP1_E1_32_entry* e176;
         
          if (n176 && (e176 = n176->obj)) {
            do {                
              STRING_TYPE p_brand = e176->P_BRAND;
              STRING_TYPE p_type = e176->P_TYPE;
              long p_size = e176->P_SIZE;
              long v176 = e176->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_12.addOrDelOnZero(se231.modify(partsupp_suppkey,p_brand,p_type,p_size),(v176 * -1L));
              n176 = n176->nxt;
            } while (n176 && (e176 = n176->obj) && h122 == n176->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_32_mapkey0_idxfn::equals(se232, *e176)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0* i177 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_35.index[1]);
          const HASH_RES_t h123 = SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0_idxfn::hash(se234.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0::IdxNode* n177 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_35_map_0::IdxNode*>(i177->slice(se234, h123));
          SUPPLIER_CNT_mPARTSUPP1_E1_35_entry* e177;
         
          if (n177 && (e177 = n177->obj)) {
            do {                
              STRING_TYPE p_brand = e177->P_BRAND;
              STRING_TYPE p_type = e177->P_TYPE;
              long p_size = e177->P_SIZE;
              long v177 = e177->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_14.addOrDelOnZero(se233.modify(partsupp_suppkey,p_brand,p_type,p_size),(v177 * -1L));
              n177 = n177->nxt;
            } while (n177 && (e177 = n177->obj) && h123 == n177->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_35_mapkey0_idxfn::equals(se234, *e177)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0* i178 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0*>(SUPPLIER_CNT_mPARTSUPP1_E1_38.index[1]);
          const HASH_RES_t h124 = SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0_idxfn::hash(se236.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0::IdxNode* n178 = static_cast<HashIndex_SUPPLIER_CNT_mPARTSUPP1_E1_38_map_0::IdxNode*>(i178->slice(se236, h124));
          SUPPLIER_CNT_mPARTSUPP1_E1_38_entry* e178;
         
          if (n178 && (e178 = n178->obj)) {
            do {                
              STRING_TYPE p_brand = e178->P_BRAND;
              STRING_TYPE p_type = e178->P_TYPE;
              long p_size = e178->P_SIZE;
              long v178 = e178->__av;
              SUPPLIER_CNT_mPARTSUPP1_E1_16.addOrDelOnZero(se235.modify(partsupp_suppkey,p_brand,p_type,p_size),(v178 * -1L));
              n178 = n178->nxt;
            } while (n178 && (e178 = n178->obj) && h124 == n178->hash &&  SUPPLIER_CNT_mPARTSUPP1_E1_38_mapkey0_idxfn::equals(se236, *e178)); 
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
    SUPPLIER_CNT_entry se1;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se2;
    tuple2_L_L st1;
    SUPPLIER_CNT_mPART3_E1_1_entry se3;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se4;
    tuple2_L_L st2;
    SUPPLIER_CNT_mPART3_E1_1_entry se5;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se6;
    tuple2_L_L st3;
    SUPPLIER_CNT_mPART3_E1_17_entry se7;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se8;
    tuple2_L_L st4;
    SUPPLIER_CNT_mPART3_E1_1_entry se9;
    SUPPLIER_CNT_mPART3_E1_1_entry se10;
    SUPPLIER_CNT_mPART3_E1_17_entry se11;
    SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry se12;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se13;
    SUPPLIER_CNT_mPART3_E1_17_entry se14;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se15;
    SUPPLIER_CNT_mPART3_E1_17_entry se16;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry se17;
    SUPPLIER_CNT_mPART3_E1_17_entry se18;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry se19;
    SUPPLIER_CNT_mPART3_E1_17_entry se20;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry se21;
    SUPPLIER_CNT_mPART3_E1_17_entry se22;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry se23;
    SUPPLIER_CNT_mPART3_E1_17_entry se24;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry se25;
    SUPPLIER_CNT_mPART3_E1_17_entry se26;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry se27;
    SUPPLIER_CNT_mPART3_E1_17_entry se28;
    SUPPLIER_CNT_mPARTSUPP1_E1_17_entry se29;
    SUPPLIER_CNT_mPARTSUPP1_E1_20_entry se30;
    SUPPLIER_CNT_mPARTSUPP1_E1_23_entry se31;
    SUPPLIER_CNT_mPARTSUPP1_E1_26_entry se32;
    SUPPLIER_CNT_mPARTSUPP1_E1_29_entry se33;
    SUPPLIER_CNT_mPARTSUPP1_E1_32_entry se34;
    SUPPLIER_CNT_mPARTSUPP1_E1_35_entry se35;
    SUPPLIER_CNT_mPARTSUPP1_E1_38_entry se36;
    SUPPLIER_CNT_entry se37;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se38;
    tuple2_L_L st5;
    SUPPLIER_CNT_mPART3_E1_1_entry se39;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se40;
    tuple2_L_L st6;
    SUPPLIER_CNT_mPART3_E1_1_entry se41;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se42;
    tuple2_L_L st7;
    SUPPLIER_CNT_mPART3_E1_17_entry se43;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se44;
    tuple2_L_L st8;
    SUPPLIER_CNT_mPART3_E1_1_entry se45;
    SUPPLIER_CNT_mPART3_E1_1_entry se46;
    SUPPLIER_CNT_mPART3_E1_17_entry se47;
    SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry se48;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se49;
    SUPPLIER_CNT_mPART3_E1_17_entry se50;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se51;
    SUPPLIER_CNT_mPART3_E1_17_entry se52;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry se53;
    SUPPLIER_CNT_mPART3_E1_17_entry se54;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry se55;
    SUPPLIER_CNT_mPART3_E1_17_entry se56;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry se57;
    SUPPLIER_CNT_mPART3_E1_17_entry se58;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry se59;
    SUPPLIER_CNT_mPART3_E1_17_entry se60;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry se61;
    SUPPLIER_CNT_mPART3_E1_17_entry se62;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry se63;
    SUPPLIER_CNT_mPART3_E1_17_entry se64;
    SUPPLIER_CNT_mPARTSUPP1_E1_17_entry se65;
    SUPPLIER_CNT_mPARTSUPP1_E1_20_entry se66;
    SUPPLIER_CNT_mPARTSUPP1_E1_23_entry se67;
    SUPPLIER_CNT_mPARTSUPP1_E1_26_entry se68;
    SUPPLIER_CNT_mPARTSUPP1_E1_29_entry se69;
    SUPPLIER_CNT_mPARTSUPP1_E1_32_entry se70;
    SUPPLIER_CNT_mPARTSUPP1_E1_35_entry se71;
    SUPPLIER_CNT_mPARTSUPP1_E1_38_entry se72;
    SUPPLIER_CNT_entry se73;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se74;
    tuple5_LSSL_L st9;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se75;
    tuple5_LSSL_L st10;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se76;
    tuple5_LSSL_L st11;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se77;
    tuple5_LSSL_L st12;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se78;
    tuple5_LSSL_L st13;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se79;
    tuple5_LSSL_L st14;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se80;
    tuple5_LSSL_L st15;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se81;
    tuple5_LSSL_L st16;
    tuple4_SSL_L st17;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se82;
    tuple4_SSL_L st18;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se83;
    tuple4_SSL_L st19;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se84;
    tuple4_SSL_L st20;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry se85;
    tuple4_SSL_L st21;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry se86;
    tuple4_SSL_L st22;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry se87;
    tuple4_SSL_L st23;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry se88;
    tuple4_SSL_L st24;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry se89;
    tuple4_SSL_L st25;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry se90;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se91;
    tuple4_SSL_L st26;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se92;
    tuple4_SSL_L st27;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se93;
    tuple4_SSL_L st28;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry se94;
    tuple4_SSL_L st29;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry se95;
    tuple4_SSL_L st30;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry se96;
    tuple4_SSL_L st31;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry se97;
    tuple4_SSL_L st32;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry se98;
    tuple4_SSL_L st33;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry se99;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se100;
    SUPPLIER_CNT_entry se101;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se102;
    tuple5_LSSL_L st34;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se103;
    tuple5_LSSL_L st35;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se104;
    tuple5_LSSL_L st36;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se105;
    tuple5_LSSL_L st37;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se106;
    tuple5_LSSL_L st38;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se107;
    tuple5_LSSL_L st39;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se108;
    tuple5_LSSL_L st40;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se109;
    tuple5_LSSL_L st41;
    tuple4_SSL_L st42;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se110;
    tuple4_SSL_L st43;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se111;
    tuple4_SSL_L st44;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se112;
    tuple4_SSL_L st45;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry se113;
    tuple4_SSL_L st46;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry se114;
    tuple4_SSL_L st47;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry se115;
    tuple4_SSL_L st48;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry se116;
    tuple4_SSL_L st49;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry se117;
    tuple4_SSL_L st50;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry se118;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se119;
    tuple4_SSL_L st51;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se120;
    tuple4_SSL_L st52;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se121;
    tuple4_SSL_L st53;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry se122;
    tuple4_SSL_L st54;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry se123;
    tuple4_SSL_L st55;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry se124;
    tuple4_SSL_L st56;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry se125;
    tuple4_SSL_L st57;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry se126;
    tuple4_SSL_L st58;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry se127;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se128;
    SUPPLIER_CNT_entry se129;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se130;
    tuple5_LSSL_L st59;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se131;
    tuple5_LSSL_L st60;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se132;
    tuple5_LSSL_L st61;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se133;
    tuple5_LSSL_L st62;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se134;
    tuple5_LSSL_L st63;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se135;
    tuple5_LSSL_L st64;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se136;
    tuple5_LSSL_L st65;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se137;
    tuple5_LSSL_L st66;
    tuple4_SSL_L st67;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se138;
    tuple4_SSL_L st68;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se139;
    tuple4_SSL_L st69;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se140;
    tuple4_SSL_L st70;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry se141;
    tuple4_SSL_L st71;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry se142;
    tuple4_SSL_L st72;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry se143;
    tuple4_SSL_L st73;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry se144;
    tuple4_SSL_L st74;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry se145;
    tuple4_SSL_L st75;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry se146;
    tuple4_SSL_L st76;
    SUPPLIER_CNT_mPARTSUPP1_E1_17_entry se147;
    tuple4_SSL_L st77;
    SUPPLIER_CNT_mPARTSUPP1_E1_20_entry se148;
    tuple4_SSL_L st78;
    SUPPLIER_CNT_mPARTSUPP1_E1_23_entry se149;
    tuple4_SSL_L st79;
    SUPPLIER_CNT_mPARTSUPP1_E1_26_entry se150;
    tuple4_SSL_L st80;
    SUPPLIER_CNT_mPARTSUPP1_E1_29_entry se151;
    tuple4_SSL_L st81;
    SUPPLIER_CNT_mPARTSUPP1_E1_32_entry se152;
    tuple4_SSL_L st82;
    SUPPLIER_CNT_mPARTSUPP1_E1_35_entry se153;
    tuple4_SSL_L st83;
    SUPPLIER_CNT_mPARTSUPP1_E1_38_entry se154;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se155;
    tuple4_SSL_L st84;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se156;
    tuple4_SSL_L st85;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se157;
    tuple4_SSL_L st86;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry se158;
    tuple4_SSL_L st87;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry se159;
    tuple4_SSL_L st88;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry se160;
    tuple4_SSL_L st89;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry se161;
    tuple4_SSL_L st90;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry se162;
    tuple4_SSL_L st91;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry se163;
    SUPPLIER_CNT_mPART3_E1_1_entry se164;
    SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry se165;
    SUPPLIER_CNT_mPART3_E1_17_entry se166;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se167;
    SUPPLIER_CNT_mPARTSUPP1_E1_17_entry se168;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se169;
    SUPPLIER_CNT_mPARTSUPP1_E1_20_entry se170;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry se171;
    SUPPLIER_CNT_mPARTSUPP1_E1_23_entry se172;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry se173;
    SUPPLIER_CNT_mPARTSUPP1_E1_26_entry se174;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry se175;
    SUPPLIER_CNT_mPARTSUPP1_E1_29_entry se176;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry se177;
    SUPPLIER_CNT_mPARTSUPP1_E1_32_entry se178;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry se179;
    SUPPLIER_CNT_mPARTSUPP1_E1_35_entry se180;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry se181;
    SUPPLIER_CNT_mPARTSUPP1_E1_38_entry se182;
    SUPPLIER_CNT_entry se183;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se184;
    tuple5_LSSL_L st92;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se185;
    tuple5_LSSL_L st93;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se186;
    tuple5_LSSL_L st94;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se187;
    tuple5_LSSL_L st95;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se188;
    tuple5_LSSL_L st96;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se189;
    tuple5_LSSL_L st97;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se190;
    tuple5_LSSL_L st98;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se191;
    tuple5_LSSL_L st99;
    tuple4_SSL_L st100;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se192;
    tuple4_SSL_L st101;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se193;
    tuple4_SSL_L st102;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se194;
    tuple4_SSL_L st103;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry se195;
    tuple4_SSL_L st104;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry se196;
    tuple4_SSL_L st105;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry se197;
    tuple4_SSL_L st106;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry se198;
    tuple4_SSL_L st107;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry se199;
    tuple4_SSL_L st108;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry se200;
    tuple4_SSL_L st109;
    SUPPLIER_CNT_mPARTSUPP1_E1_17_entry se201;
    tuple4_SSL_L st110;
    SUPPLIER_CNT_mPARTSUPP1_E1_20_entry se202;
    tuple4_SSL_L st111;
    SUPPLIER_CNT_mPARTSUPP1_E1_23_entry se203;
    tuple4_SSL_L st112;
    SUPPLIER_CNT_mPARTSUPP1_E1_26_entry se204;
    tuple4_SSL_L st113;
    SUPPLIER_CNT_mPARTSUPP1_E1_29_entry se205;
    tuple4_SSL_L st114;
    SUPPLIER_CNT_mPARTSUPP1_E1_32_entry se206;
    tuple4_SSL_L st115;
    SUPPLIER_CNT_mPARTSUPP1_E1_35_entry se207;
    tuple4_SSL_L st116;
    SUPPLIER_CNT_mPARTSUPP1_E1_38_entry se208;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_entry se209;
    tuple4_SSL_L st117;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se210;
    tuple4_SSL_L st118;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se211;
    tuple4_SSL_L st119;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry se212;
    tuple4_SSL_L st120;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry se213;
    tuple4_SSL_L st121;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry se214;
    tuple4_SSL_L st122;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry se215;
    tuple4_SSL_L st123;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry se216;
    tuple4_SSL_L st124;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry se217;
    SUPPLIER_CNT_mPART3_E1_1_entry se218;
    SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_entry se219;
    SUPPLIER_CNT_mPART3_E1_17_entry se220;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_entry se221;
    SUPPLIER_CNT_mPARTSUPP1_E1_17_entry se222;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_entry se223;
    SUPPLIER_CNT_mPARTSUPP1_E1_20_entry se224;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_entry se225;
    SUPPLIER_CNT_mPARTSUPP1_E1_23_entry se226;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_entry se227;
    SUPPLIER_CNT_mPARTSUPP1_E1_26_entry se228;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_entry se229;
    SUPPLIER_CNT_mPARTSUPP1_E1_29_entry se230;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_entry se231;
    SUPPLIER_CNT_mPARTSUPP1_E1_32_entry se232;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_entry se233;
    SUPPLIER_CNT_mPARTSUPP1_E1_35_entry se234;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_entry se235;
    SUPPLIER_CNT_mPARTSUPP1_E1_38_entry se236;
    /* regex_t temporary objects */
    regex_t preg2;
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    SUPPLIER_CNT_mPART3_E1_1_map SUPPLIER_CNT_mPART3_E1_1;
    SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1_map SUPPLIER_CNT_mPART3_E1_1_mPARTSUPP1;
    SUPPLIER_CNT_mPART3_E1_17_map SUPPLIER_CNT_mPART3_E1_17;
    SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1_map SUPPLIER_CNT_mPARTSUPP1_E1_1_L2_1;
    SUPPLIER_CNT_mPARTSUPP1_E1_2_map SUPPLIER_CNT_mPARTSUPP1_E1_2;
    SUPPLIER_CNT_mPARTSUPP1_E1_4_map SUPPLIER_CNT_mPARTSUPP1_E1_4;
    SUPPLIER_CNT_mPARTSUPP1_E1_6_map SUPPLIER_CNT_mPARTSUPP1_E1_6;
    SUPPLIER_CNT_mPARTSUPP1_E1_8_map SUPPLIER_CNT_mPARTSUPP1_E1_8;
    SUPPLIER_CNT_mPARTSUPP1_E1_10_map SUPPLIER_CNT_mPARTSUPP1_E1_10;
    SUPPLIER_CNT_mPARTSUPP1_E1_12_map SUPPLIER_CNT_mPARTSUPP1_E1_12;
    SUPPLIER_CNT_mPARTSUPP1_E1_14_map SUPPLIER_CNT_mPARTSUPP1_E1_14;
    SUPPLIER_CNT_mPARTSUPP1_E1_16_map SUPPLIER_CNT_mPARTSUPP1_E1_16;
    SUPPLIER_CNT_mPARTSUPP1_E1_17_map SUPPLIER_CNT_mPARTSUPP1_E1_17;
    SUPPLIER_CNT_mPARTSUPP1_E1_20_map SUPPLIER_CNT_mPARTSUPP1_E1_20;
    SUPPLIER_CNT_mPARTSUPP1_E1_23_map SUPPLIER_CNT_mPARTSUPP1_E1_23;
    SUPPLIER_CNT_mPARTSUPP1_E1_26_map SUPPLIER_CNT_mPARTSUPP1_E1_26;
    SUPPLIER_CNT_mPARTSUPP1_E1_29_map SUPPLIER_CNT_mPARTSUPP1_E1_29;
    SUPPLIER_CNT_mPARTSUPP1_E1_32_map SUPPLIER_CNT_mPARTSUPP1_E1_32;
    SUPPLIER_CNT_mPARTSUPP1_E1_35_map SUPPLIER_CNT_mPARTSUPP1_E1_35;
    SUPPLIER_CNT_mPARTSUPP1_E1_38_map SUPPLIER_CNT_mPARTSUPP1_E1_38;
    MultiHashMap<tuple5_LSSL_L,long,HashIndex<tuple5_LSSL_L,long> > agg26;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg6;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg19;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg25;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg13;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg28;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg8;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg16;
    MultiHashMap<tuple5_LSSL_L,long,HashIndex<tuple5_LSSL_L,long> > agg22;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg2;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg10;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg21;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg24;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg4;
    MultiHashMap<tuple5_LSSL_L,long,HashIndex<tuple5_LSSL_L,long> > agg18;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg27;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg12;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg15;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg20;
    MultiHashMap<tuple5_LSSL_L,long,HashIndex<tuple5_LSSL_L,long> > agg14;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg17;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg23;
    /*const static*/ STRING_TYPE c1;
  
  };

}
