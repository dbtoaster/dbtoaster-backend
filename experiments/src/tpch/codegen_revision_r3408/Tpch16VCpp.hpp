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
  
  struct SUPPLIER_CNTPART4_E1_1_entry {
    STRING_TYPE SUPPLIER_CNTPARTPART_BRAND; STRING_TYPE SUPPLIER_CNTPARTPART_TYPE; long SUPPLIER_CNTPARTPART_SIZE; long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTPART4_E1_1_entry() { /*SUPPLIER_CNTPARTPART_BRAND = ""; SUPPLIER_CNTPARTPART_TYPE = ""; SUPPLIER_CNTPARTPART_SIZE = 0L; PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPART4_E1_1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const long c3, const long c4) { SUPPLIER_CNTPARTPART_BRAND = c0; SUPPLIER_CNTPARTPART_TYPE = c1; SUPPLIER_CNTPARTPART_SIZE = c2; PS_SUPPKEY = c3; __av = c4; }
    SUPPLIER_CNTPART4_E1_1_entry(const SUPPLIER_CNTPART4_E1_1_entry& other) : SUPPLIER_CNTPARTPART_BRAND( other.SUPPLIER_CNTPARTPART_BRAND ), SUPPLIER_CNTPARTPART_TYPE( other.SUPPLIER_CNTPARTPART_TYPE ), SUPPLIER_CNTPARTPART_SIZE( other.SUPPLIER_CNTPARTPART_SIZE ), PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPART4_E1_1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const long c3) { SUPPLIER_CNTPARTPART_BRAND = c0; SUPPLIER_CNTPARTPART_TYPE = c1; SUPPLIER_CNTPARTPART_SIZE = c2; PS_SUPPKEY = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPART4_E1_1_entry& modify012(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { SUPPLIER_CNTPARTPART_BRAND = c0; SUPPLIER_CNTPARTPART_TYPE = c1; SUPPLIER_CNTPARTPART_SIZE = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNTPARTPART_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNTPARTPART_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNTPARTPART_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPART4_E1_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART4_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNTPARTPART_BRAND);
      hash_combine(h, e.SUPPLIER_CNTPARTPART_TYPE);
      hash_combine(h, e.SUPPLIER_CNTPARTPART_SIZE);
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART4_E1_1_entry& x, const SUPPLIER_CNTPART4_E1_1_entry& y) {
      return x.SUPPLIER_CNTPARTPART_BRAND == y.SUPPLIER_CNTPARTPART_BRAND && x.SUPPLIER_CNTPARTPART_TYPE == y.SUPPLIER_CNTPARTPART_TYPE && x.SUPPLIER_CNTPARTPART_SIZE == y.SUPPLIER_CNTPARTPART_SIZE && x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  struct SUPPLIER_CNTPART4_E1_1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART4_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNTPARTPART_BRAND);
      hash_combine(h, e.SUPPLIER_CNTPARTPART_TYPE);
      hash_combine(h, e.SUPPLIER_CNTPARTPART_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART4_E1_1_entry& x, const SUPPLIER_CNTPART4_E1_1_entry& y) {
      return x.SUPPLIER_CNTPARTPART_BRAND == y.SUPPLIER_CNTPARTPART_BRAND && x.SUPPLIER_CNTPARTPART_TYPE == y.SUPPLIER_CNTPARTPART_TYPE && x.SUPPLIER_CNTPARTPART_SIZE == y.SUPPLIER_CNTPARTPART_SIZE;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPART4_E1_1_entry,long,
    HashIndex<SUPPLIER_CNTPART4_E1_1_entry,long,SUPPLIER_CNTPART4_E1_1_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPART4_E1_1_entry,long,SUPPLIER_CNTPART4_E1_1_mapkey012_idxfn,false>
  > SUPPLIER_CNTPART4_E1_1_map;
  typedef HashIndex<SUPPLIER_CNTPART4_E1_1_entry,long,SUPPLIER_CNTPART4_E1_1_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPART4_E1_1_map_0123;
  typedef HashIndex<SUPPLIER_CNTPART4_E1_1_entry,long,SUPPLIER_CNTPART4_E1_1_mapkey012_idxfn,false> HashIndex_SUPPLIER_CNTPART4_E1_1_map_012;
  
  struct SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry {
    long SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY; STRING_TYPE SUPPLIER_CNTPARTPART_BRAND; STRING_TYPE SUPPLIER_CNTPARTPART_TYPE; long SUPPLIER_CNTPARTPART_SIZE; long __av; 
    explicit SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry() { /*SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY = 0L; SUPPLIER_CNTPARTPART_BRAND = ""; SUPPLIER_CNTPARTPART_TYPE = ""; SUPPLIER_CNTPARTPART_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY = c0; SUPPLIER_CNTPARTPART_BRAND = c1; SUPPLIER_CNTPARTPART_TYPE = c2; SUPPLIER_CNTPARTPART_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry(const SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry& other) : SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY ), SUPPLIER_CNTPARTPART_BRAND( other.SUPPLIER_CNTPARTPART_BRAND ), SUPPLIER_CNTPARTPART_TYPE( other.SUPPLIER_CNTPARTPART_TYPE ), SUPPLIER_CNTPARTPART_SIZE( other.SUPPLIER_CNTPARTPART_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY = c0; SUPPLIER_CNTPARTPART_BRAND = c1; SUPPLIER_CNTPARTPART_TYPE = c2; SUPPLIER_CNTPARTPART_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry& modify0(const long c0) { SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNTPARTPART_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNTPARTPART_TYPE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNTPARTPART_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPART4_E1_1PARTSUPP1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.SUPPLIER_CNTPARTPART_BRAND);
      hash_combine(h, e.SUPPLIER_CNTPARTPART_TYPE);
      hash_combine(h, e.SUPPLIER_CNTPARTPART_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry& x, const SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry& y) {
      return x.SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY && x.SUPPLIER_CNTPARTPART_BRAND == y.SUPPLIER_CNTPARTPART_BRAND && x.SUPPLIER_CNTPARTPART_TYPE == y.SUPPLIER_CNTPARTPART_TYPE && x.SUPPLIER_CNTPARTPART_SIZE == y.SUPPLIER_CNTPARTPART_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPART4_E1_1PARTSUPP1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry& x, const SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry& y) {
      return x.SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNTPART4_E1_1PARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry,long,
    HashIndex<SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry,long,SUPPLIER_CNTPART4_E1_1PARTSUPP1_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry,long,SUPPLIER_CNTPART4_E1_1PARTSUPP1_mapkey0_idxfn,false>
  > SUPPLIER_CNTPART4_E1_1PARTSUPP1_map;
  typedef HashIndex<SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry,long,SUPPLIER_CNTPART4_E1_1PARTSUPP1_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPART4_E1_1PARTSUPP1_map_0123;
  typedef HashIndex<SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry,long,SUPPLIER_CNTPART4_E1_1PARTSUPP1_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPART4_E1_1PARTSUPP1_map_0;
  
  struct SUPPLIER_CNTPART4_E1_2_entry {
    long SUPPLIER_CNTPARTPART_PARTKEY; long PS_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTPART4_E1_2_entry() { /*SUPPLIER_CNTPARTPART_PARTKEY = 0L; PS_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPART4_E1_2_entry(const long c0, const long c1, const long c2) { SUPPLIER_CNTPARTPART_PARTKEY = c0; PS_SUPPKEY = c1; __av = c2; }
    SUPPLIER_CNTPART4_E1_2_entry(const SUPPLIER_CNTPART4_E1_2_entry& other) : SUPPLIER_CNTPARTPART_PARTKEY( other.SUPPLIER_CNTPARTPART_PARTKEY ), PS_SUPPKEY( other.PS_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPART4_E1_2_entry& modify(const long c0, const long c1) { SUPPLIER_CNTPARTPART_PARTKEY = c0; PS_SUPPKEY = c1;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPART4_E1_2_entry& modify0(const long c0) { SUPPLIER_CNTPARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNTPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPART4_E1_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART4_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNTPARTPART_PARTKEY);
      hash_combine(h, e.PS_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART4_E1_2_entry& x, const SUPPLIER_CNTPART4_E1_2_entry& y) {
      return x.SUPPLIER_CNTPARTPART_PARTKEY == y.SUPPLIER_CNTPARTPART_PARTKEY && x.PS_SUPPKEY == y.PS_SUPPKEY;
    }
  };
  
  struct SUPPLIER_CNTPART4_E1_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPART4_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNTPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPART4_E1_2_entry& x, const SUPPLIER_CNTPART4_E1_2_entry& y) {
      return x.SUPPLIER_CNTPARTPART_PARTKEY == y.SUPPLIER_CNTPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPART4_E1_2_entry,long,
    HashIndex<SUPPLIER_CNTPART4_E1_2_entry,long,SUPPLIER_CNTPART4_E1_2_mapkey01_idxfn,true>,
    HashIndex<SUPPLIER_CNTPART4_E1_2_entry,long,SUPPLIER_CNTPART4_E1_2_mapkey0_idxfn,false>
  > SUPPLIER_CNTPART4_E1_2_map;
  typedef HashIndex<SUPPLIER_CNTPART4_E1_2_entry,long,SUPPLIER_CNTPART4_E1_2_mapkey01_idxfn,true> HashIndex_SUPPLIER_CNTPART4_E1_2_map_01;
  typedef HashIndex<SUPPLIER_CNTPART4_E1_2_entry,long,SUPPLIER_CNTPART4_E1_2_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPART4_E1_2_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry {
    long SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry() { /*SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry(const long c0, const long c1) { SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY = c0; __av = c1; }
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry(const SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry& other) : SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY( other.SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry& modify(const long c0) { SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry& y) {
      return x.SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry,long,SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_mapkey0_idxfn,true>
  > SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry,long,SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_mapkey0_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_2_entry {
    long SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_2_entry() { /*SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_2_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_2_entry(const SUPPLIER_CNTPARTSUPP1_E1_2_entry& other) : SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY( other.SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_2_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_2_entry& modify0(const long c0) { SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY);
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
  struct SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_2_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_2_entry& y) {
      return x.SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_2_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_2_entry& y) {
      return x.SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY == y.SUPPLIER_CNTPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_2_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_2_entry,long,SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_2_entry,long,SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_2_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_2_entry,long,SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_2_entry,long,SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0;
  
  struct SUPPLIER_CNTPARTSUPP1_E1_4_entry {
    long SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY; STRING_TYPE P_BRAND; STRING_TYPE P_TYPE; long P_SIZE; long __av; 
    explicit SUPPLIER_CNTPARTSUPP1_E1_4_entry() { /*SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY = 0L; P_BRAND = ""; P_TYPE = ""; P_SIZE = 0L; __av = 0L; */ }
    explicit SUPPLIER_CNTPARTSUPP1_E1_4_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const long c4) { SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3; __av = c4; }
    SUPPLIER_CNTPARTSUPP1_E1_4_entry(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& other) : SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY( other.SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY ), P_BRAND( other.P_BRAND ), P_TYPE( other.P_TYPE ), P_SIZE( other.P_SIZE ), __av( other.__av ) {}
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_4_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY = c0; P_BRAND = c1; P_TYPE = c2; P_SIZE = c3;  return *this; }
    FORCE_INLINE SUPPLIER_CNTPARTSUPP1_E1_4_entry& modify0(const long c0) { SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY);
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
  struct SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_TYPE);
      hash_combine(h, e.P_SIZE);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_4_entry& y) {
      return x.SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_TYPE == y.P_TYPE && x.P_SIZE == y.P_SIZE;
    }
  };
  
  struct SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const SUPPLIER_CNTPARTSUPP1_E1_4_entry& x, const SUPPLIER_CNTPARTSUPP1_E1_4_entry& y) {
      return x.SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY == y.SUPPLIER_CNTPARTSUPPPARTSUPP_PARTKEY;
    }
  };
  
  typedef MultiHashMap<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0123_idxfn,true>,
    HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn,false>
  > SUPPLIER_CNTPARTSUPP1_E1_4_map;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0123_idxfn,true> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0123;
  typedef HashIndex<SUPPLIER_CNTPARTSUPP1_E1_4_entry,long,SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn,false> HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0;
  
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
    data_t(): tlq_t(), agg6(16U), agg8(16U), agg2(16U), agg5(16U), agg4(16U), agg7(16U) {
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
          const HashIndex_SUPPLIER_CNTPART4_E1_1_map_012* i1 = static_cast<HashIndex_SUPPLIER_CNTPART4_E1_1_map_012*>(SUPPLIER_CNTPART4_E1_1.index[1]);
          const HASH_RES_t h1 = SUPPLIER_CNTPART4_E1_1_mapkey012_idxfn::hash(se3.modify012(part_brand, part_type, part_size));
          HashIndex_SUPPLIER_CNTPART4_E1_1_map_012::IdxNode* n1 = static_cast<HashIndex_SUPPLIER_CNTPART4_E1_1_map_012::IdxNode*>(i1->slice(se3, h1));
          SUPPLIER_CNTPART4_E1_1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long ps_suppkey = e1->PS_SUPPKEY;
              long v1 = e1->__av;
              (/*if */(l1 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se2.modify(ps_suppkey))) ? agg2.addOrDelOnZero(st1.modify(ps_suppkey,v1), v1) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  SUPPLIER_CNTPART4_E1_1_mapkey012_idxfn::equals(se3, *e1)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNTPART4_E1_2_map_0* i2 = static_cast<HashIndex_SUPPLIER_CNTPART4_E1_2_map_0*>(SUPPLIER_CNTPART4_E1_2.index[1]);
          const HASH_RES_t h2 = SUPPLIER_CNTPART4_E1_2_mapkey0_idxfn::hash(se5.modify0(part_partkey));
          HashIndex_SUPPLIER_CNTPART4_E1_2_map_0::IdxNode* n2 = static_cast<HashIndex_SUPPLIER_CNTPART4_E1_2_map_0::IdxNode*>(i2->slice(se5, h2));
          SUPPLIER_CNTPART4_E1_2_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long ps_suppkey = e2->PS_SUPPKEY;
              long v2 = e2->__av;
              (/*if */(l1 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se4.modify(ps_suppkey))) ? agg2.addOrDelOnZero(st2.modify(ps_suppkey,v2), v2) : (void)0);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  SUPPLIER_CNTPART4_E1_2_mapkey0_idxfn::equals(se5, *e2)); 
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
          const HashIndex_SUPPLIER_CNTPART4_E1_1_map_012* i4 = static_cast<HashIndex_SUPPLIER_CNTPART4_E1_1_map_012*>(SUPPLIER_CNTPART4_E1_1.index[1]);
          const HASH_RES_t h3 = SUPPLIER_CNTPART4_E1_1_mapkey012_idxfn::hash(se7.modify012(part_brand, part_type, part_size));
          HashIndex_SUPPLIER_CNTPART4_E1_1_map_012::IdxNode* n4 = static_cast<HashIndex_SUPPLIER_CNTPART4_E1_1_map_012::IdxNode*>(i4->slice(se7, h3));
          SUPPLIER_CNTPART4_E1_1_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long ps_suppkey = e4->PS_SUPPKEY;
              long v4 = e4->__av;
              (/*if */(l2 == SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se6.modify(ps_suppkey))) ? agg4.addOrDelOnZero(st3.modify(ps_suppkey,v4), v4) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h3 == n4->hash &&  SUPPLIER_CNTPART4_E1_1_mapkey012_idxfn::equals(se7, *e4)); 
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
          const HashIndex_SUPPLIER_CNTPART4_E1_2_map_0* i6 = static_cast<HashIndex_SUPPLIER_CNTPART4_E1_2_map_0*>(SUPPLIER_CNTPART4_E1_2.index[1]);
          const HASH_RES_t h4 = SUPPLIER_CNTPART4_E1_2_mapkey0_idxfn::hash(se9.modify0(part_partkey));
          HashIndex_SUPPLIER_CNTPART4_E1_2_map_0::IdxNode* n6 = static_cast<HashIndex_SUPPLIER_CNTPART4_E1_2_map_0::IdxNode*>(i6->slice(se9, h4));
          SUPPLIER_CNTPART4_E1_2_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              long ps_suppkey = e6->PS_SUPPKEY;
              long v6 = e6->__av;
              SUPPLIER_CNTPART4_E1_1.addOrDelOnZero(se8.modify(part_brand,part_type,part_size,ps_suppkey),v6);
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h4 == n6->hash &&  SUPPLIER_CNTPART4_E1_2_mapkey0_idxfn::equals(se9, *e6)); 
          }
        }SUPPLIER_CNTPART4_E1_1PARTSUPP1.addOrDelOnZero(se10.modify(part_partkey,part_brand,part_type,part_size),1L);
        { //slice 
          const HashIndex_SUPPLIER_CNTPART4_E1_2_map_0* i7 = static_cast<HashIndex_SUPPLIER_CNTPART4_E1_2_map_0*>(SUPPLIER_CNTPART4_E1_2.index[1]);
          const HASH_RES_t h5 = SUPPLIER_CNTPART4_E1_2_mapkey0_idxfn::hash(se12.modify0(part_partkey));
          HashIndex_SUPPLIER_CNTPART4_E1_2_map_0::IdxNode* n7 = static_cast<HashIndex_SUPPLIER_CNTPART4_E1_2_map_0::IdxNode*>(i7->slice(se12, h5));
          SUPPLIER_CNTPART4_E1_2_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              long supplier_cntpartsupppartsupp_suppkey = e7->PS_SUPPKEY;
              long v7 = e7->__av;
              (/*if */(((part_size == 49L) || (part_size == 14L) || (part_size == 23L) || (part_size == 45L) || (part_size == 19L) || (part_size == 3L) || (part_size == 36L) || (part_size == 9L)) && 0L == Upreg_match(preg1,part_type) && part_brand != c1) ? SUPPLIER_CNTPARTSUPP1_E1_2.addOrDelOnZero(se11.modify(supplier_cntpartsupppartsupp_suppkey,part_brand,part_type,part_size),v7) : (void)0);
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h5 == n7->hash &&  SUPPLIER_CNTPART4_E1_2_mapkey0_idxfn::equals(se12, *e7)); 
          }
        }(/*if */(((part_size == 49L) || (part_size == 14L) || (part_size == 23L) || (part_size == 45L) || (part_size == 19L) || (part_size == 3L) || (part_size == 36L) || (part_size == 9L)) && 0L == Upreg_match(preg1,part_type) && part_brand != c1) ? SUPPLIER_CNTPARTSUPP1_E1_4.addOrDelOnZero(se13.modify(part_partkey,part_brand,part_type,part_size),1L) : (void)0);
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        agg5.clear();
        
        long l3 = (SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se15.modify(supplier_suppkey)) + (/*if */(0L != Upreg_match(preg2,supplier_comment)) ? 1L : 0L));
        { //slice 
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0* i8 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h6 = SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::hash(se16.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode* n8 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode*>(i8->slice(se16, h6));
          SUPPLIER_CNTPARTSUPP1_E1_2_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              STRING_TYPE p_brand = e8->P_BRAND;
              STRING_TYPE p_type = e8->P_TYPE;
              long p_size = e8->P_SIZE;
              long v8 = e8->__av;
              (/*if */(l3 == 0L) ? agg5.addOrDelOnZero(st4.modify(p_brand,p_type,p_size,v8), v8) : (void)0);
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h6 == n8->hash &&  SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::equals(se16, *e8)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i9 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg5.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n9; 
          tuple4_SSL_L* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
              STRING_TYPE p_brand = e9->_1;
              STRING_TYPE p_type = e9->_2;
              long p_size = e9->_3;  
              long v9 = e9->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se14.modify(p_brand,p_type,p_size),(v9 != 0 ? 1L : 0L));      
              n9 = n9->nxt;
            }
          }
        }agg6.clear();
        
        long l4 = SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se17.modify(supplier_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0* i10 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h7 = SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::hash(se18.modify0(supplier_suppkey));
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode* n10 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode*>(i10->slice(se18, h7));
          SUPPLIER_CNTPARTSUPP1_E1_2_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              STRING_TYPE p_brand = e10->P_BRAND;
              STRING_TYPE p_type = e10->P_TYPE;
              long p_size = e10->P_SIZE;
              long v10 = e10->__av;
              (/*if */(l4 == 0L) ? agg6.addOrDelOnZero(st5.modify(p_brand,p_type,p_size,v10), v10) : (void)0);
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h7 == n10->hash &&  SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::equals(se18, *e10)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i11 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg6.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n11; 
          tuple4_SSL_L* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
              STRING_TYPE p_brand = e11->_1;
              STRING_TYPE p_type = e11->_2;
              long p_size = e11->_3;  
              long v11 = e11->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se14.modify(p_brand,p_type,p_size),((v11 != 0 ? 1L : 0L) * -1L));      
              n11 = n11->nxt;
            }
          }
        }(/*if */(0L != Upreg_match(preg2,supplier_comment)) ? SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.addOrDelOnZero(se19.modify(supplier_suppkey),1L) : (void)0);
      }
    }
    void on_insert_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        agg7.clear();
        
        long l5 = SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se21.modify(partsupp_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0* i12 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h8 = SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::hash(se22.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode* n12 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode*>(i12->slice(se22, h8));
          SUPPLIER_CNTPARTSUPP1_E1_2_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              STRING_TYPE p_brand = e12->P_BRAND;
              STRING_TYPE p_type = e12->P_TYPE;
              long p_size = e12->P_SIZE;
              long v12 = e12->__av;
              (/*if */(l5 == 0L) ? agg7.addOrDelOnZero(st6.modify(p_brand,p_type,p_size,v12), v12) : (void)0);
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h8 == n12->hash &&  SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::equals(se22, *e12)); 
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0* i13 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h9 = SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::hash(se23.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode* n13 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode*>(i13->slice(se23, h9));
          SUPPLIER_CNTPARTSUPP1_E1_4_entry* e13;
         
          if (n13 && (e13 = n13->obj)) {
            do {                
              STRING_TYPE p_brand = e13->P_BRAND;
              STRING_TYPE p_type = e13->P_TYPE;
              long p_size = e13->P_SIZE;
              long v13 = e13->__av;
              (/*if */(l5 == 0L) ? agg7.addOrDelOnZero(st7.modify(p_brand,p_type,p_size,v13), v13) : (void)0);
              n13 = n13->nxt;
            } while (n13 && (e13 = n13->obj) && h9 == n13->hash &&  SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::equals(se23, *e13)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i14 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg7.index[0]);
          HashIndex<tuple4_SSL_L, long>::IdxNode* n14; 
          tuple4_SSL_L* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
              STRING_TYPE p_brand = e14->_1;
              STRING_TYPE p_type = e14->_2;
              long p_size = e14->_3;  
              long v14 = e14->__av; 
            SUPPLIER_CNT.addOrDelOnZero(se20.modify(p_brand,p_type,p_size),(v14 != 0 ? 1L : 0L));      
              n14 = n14->nxt;
            }
          }
        }agg8.clear();
        
        long l6 = SUPPLIER_CNTPARTSUPP1_E1_1_L2_1.getValueOrDefault(se24.modify(partsupp_suppkey));
        { //slice 
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0* i15 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_2.index[1]);
          const HASH_RES_t h10 = SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::hash(se25.modify0(partsupp_suppkey));
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode* n15 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_2_map_0::IdxNode*>(i15->slice(se25, h10));
          SUPPLIER_CNTPARTSUPP1_E1_2_entry* e15;
         
          if (n15 && (e15 = n15->obj)) {
            do {                
              STRING_TYPE p_brand = e15->P_BRAND;
              STRING_TYPE p_type = e15->P_TYPE;
              long p_size = e15->P_SIZE;
              long v15 = e15->__av;
              (/*if */(l6 == 0L) ? agg8.addOrDelOnZero(st8.modify(p_brand,p_type,p_size,v15), v15) : (void)0);
              n15 = n15->nxt;
            } while (n15 && (e15 = n15->obj) && h10 == n15->hash &&  SUPPLIER_CNTPARTSUPP1_E1_2_mapkey0_idxfn::equals(se25, *e15)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_SSL_L, long>* i16 = static_cast<HashIndex<tuple4_SSL_L, long>*>(agg8.index[0]);
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
            SUPPLIER_CNT.addOrDelOnZero(se20.modify(p_brand,p_type,p_size),((v16 != 0 ? 1L : 0L) * -1L));      
              n16 = n16->nxt;
            }
          }
        }{ //slice 
          const HashIndex_SUPPLIER_CNTPART4_E1_1PARTSUPP1_map_0* i17 = static_cast<HashIndex_SUPPLIER_CNTPART4_E1_1PARTSUPP1_map_0*>(SUPPLIER_CNTPART4_E1_1PARTSUPP1.index[1]);
          const HASH_RES_t h11 = SUPPLIER_CNTPART4_E1_1PARTSUPP1_mapkey0_idxfn::hash(se27.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNTPART4_E1_1PARTSUPP1_map_0::IdxNode* n17 = static_cast<HashIndex_SUPPLIER_CNTPART4_E1_1PARTSUPP1_map_0::IdxNode*>(i17->slice(se27, h11));
          SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry* e17;
         
          if (n17 && (e17 = n17->obj)) {
            do {                
              STRING_TYPE supplier_cntpartpart_brand = e17->SUPPLIER_CNTPARTPART_BRAND;
              STRING_TYPE supplier_cntpartpart_type = e17->SUPPLIER_CNTPARTPART_TYPE;
              long supplier_cntpartpart_size = e17->SUPPLIER_CNTPARTPART_SIZE;
              long v17 = e17->__av;
              SUPPLIER_CNTPART4_E1_1.addOrDelOnZero(se26.modify(supplier_cntpartpart_brand,supplier_cntpartpart_type,supplier_cntpartpart_size,partsupp_suppkey),v17);
              n17 = n17->nxt;
            } while (n17 && (e17 = n17->obj) && h11 == n17->hash &&  SUPPLIER_CNTPART4_E1_1PARTSUPP1_mapkey0_idxfn::equals(se27, *e17)); 
          }
        }SUPPLIER_CNTPART4_E1_2.addOrDelOnZero(se28.modify(partsupp_partkey,partsupp_suppkey),1L);
        { //slice 
          const HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0* i18 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0*>(SUPPLIER_CNTPARTSUPP1_E1_4.index[1]);
          const HASH_RES_t h12 = SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::hash(se30.modify0(partsupp_partkey));
          HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode* n18 = static_cast<HashIndex_SUPPLIER_CNTPARTSUPP1_E1_4_map_0::IdxNode*>(i18->slice(se30, h12));
          SUPPLIER_CNTPARTSUPP1_E1_4_entry* e18;
         
          if (n18 && (e18 = n18->obj)) {
            do {                
              STRING_TYPE p_brand = e18->P_BRAND;
              STRING_TYPE p_type = e18->P_TYPE;
              long p_size = e18->P_SIZE;
              long v18 = e18->__av;
              SUPPLIER_CNTPARTSUPP1_E1_2.addOrDelOnZero(se29.modify(partsupp_suppkey,p_brand,p_type,p_size),v18);
              n18 = n18->nxt;
            } while (n18 && (e18 = n18->obj) && h12 == n18->hash &&  SUPPLIER_CNTPARTSUPP1_E1_4_mapkey0_idxfn::equals(se30, *e18)); 
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
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se2;
    tuple2_L_L st1;
    SUPPLIER_CNTPART4_E1_1_entry se3;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se4;
    tuple2_L_L st2;
    SUPPLIER_CNTPART4_E1_2_entry se5;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se6;
    tuple2_L_L st3;
    SUPPLIER_CNTPART4_E1_1_entry se7;
    SUPPLIER_CNTPART4_E1_1_entry se8;
    SUPPLIER_CNTPART4_E1_2_entry se9;
    SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry se10;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se11;
    SUPPLIER_CNTPART4_E1_2_entry se12;
    SUPPLIER_CNTPARTSUPP1_E1_4_entry se13;
    SUPPLIER_CNT_entry se14;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se15;
    tuple4_SSL_L st4;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se16;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se17;
    tuple4_SSL_L st5;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se18;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se19;
    SUPPLIER_CNT_entry se20;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se21;
    tuple4_SSL_L st6;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se22;
    tuple4_SSL_L st7;
    SUPPLIER_CNTPARTSUPP1_E1_4_entry se23;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_entry se24;
    tuple4_SSL_L st8;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se25;
    SUPPLIER_CNTPART4_E1_1_entry se26;
    SUPPLIER_CNTPART4_E1_1PARTSUPP1_entry se27;
    SUPPLIER_CNTPART4_E1_2_entry se28;
    SUPPLIER_CNTPARTSUPP1_E1_2_entry se29;
    SUPPLIER_CNTPARTSUPP1_E1_4_entry se30;
    /* regex_t temporary objects */
    regex_t preg2;
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    SUPPLIER_CNTPART4_E1_1_map SUPPLIER_CNTPART4_E1_1;
    SUPPLIER_CNTPART4_E1_1PARTSUPP1_map SUPPLIER_CNTPART4_E1_1PARTSUPP1;
    SUPPLIER_CNTPART4_E1_2_map SUPPLIER_CNTPART4_E1_2;
    SUPPLIER_CNTPARTSUPP1_E1_1_L2_1_map SUPPLIER_CNTPARTSUPP1_E1_1_L2_1;
    SUPPLIER_CNTPARTSUPP1_E1_2_map SUPPLIER_CNTPARTSUPP1_E1_2;
    SUPPLIER_CNTPARTSUPP1_E1_4_map SUPPLIER_CNTPARTSUPP1_E1_4;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg6;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg8;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg2;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg5;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg4;
    MultiHashMap<tuple4_SSL_L,long,HashIndex<tuple4_SSL_L,long> > agg7;
    /*const static*/ STRING_TYPE c1;
  
  };

}
