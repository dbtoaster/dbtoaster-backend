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
  
  struct NUMCUST_mCUSTOMER1_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUST_mCUSTOMER1_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUST_mCUSTOMER1_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUST_mCUSTOMER1_entry(const NUMCUST_mCUSTOMER1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUST_mCUSTOMER1_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUST_mCUSTOMER1_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct NUMCUST_mCUSTOMER1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER1_entry& x, const NUMCUST_mCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUST_mCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER1_entry& x, const NUMCUST_mCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUST_mCUSTOMER1_entry,long,
    HashIndex<NUMCUST_mCUSTOMER1_entry,long,NUMCUST_mCUSTOMER1_mapkey012_idxfn,true>,
    HashIndex<NUMCUST_mCUSTOMER1_entry,long,NUMCUST_mCUSTOMER1_mapkey0_idxfn,false>
  > NUMCUST_mCUSTOMER1_map;
  typedef HashIndex<NUMCUST_mCUSTOMER1_entry,long,NUMCUST_mCUSTOMER1_mapkey012_idxfn,true> HashIndex_NUMCUST_mCUSTOMER1_map_012;
  typedef HashIndex<NUMCUST_mCUSTOMER1_entry,long,NUMCUST_mCUSTOMER1_mapkey0_idxfn,false> HashIndex_NUMCUST_mCUSTOMER1_map_0;
  
  struct NUMCUST_mCUSTOMER1_L3_1_entry {
    long C_CUSTKEY; long __av; 
    explicit NUMCUST_mCUSTOMER1_L3_1_entry() { /*C_CUSTKEY = 0L; __av = 0L; */ }
    explicit NUMCUST_mCUSTOMER1_L3_1_entry(const long c0, const long c1) { C_CUSTKEY = c0; __av = c1; }
    NUMCUST_mCUSTOMER1_L3_1_entry(const NUMCUST_mCUSTOMER1_L3_1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMCUST_mCUSTOMER1_L3_1_entry& modify(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUST_mCUSTOMER1_L3_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER1_L3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER1_L3_1_entry& x, const NUMCUST_mCUSTOMER1_L3_1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUST_mCUSTOMER1_L3_1_entry,long,
    HashIndex<NUMCUST_mCUSTOMER1_L3_1_entry,long,NUMCUST_mCUSTOMER1_L3_1_mapkey0_idxfn,true>
  > NUMCUST_mCUSTOMER1_L3_1_map;
  typedef HashIndex<NUMCUST_mCUSTOMER1_L3_1_entry,long,NUMCUST_mCUSTOMER1_L3_1_mapkey0_idxfn,true> HashIndex_NUMCUST_mCUSTOMER1_L3_1_map_0;
  
  struct NUMCUST_mCUSTOMER2_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUST_mCUSTOMER2_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUST_mCUSTOMER2_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUST_mCUSTOMER2_entry(const NUMCUST_mCUSTOMER2_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUST_mCUSTOMER2_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUST_mCUSTOMER2_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct NUMCUST_mCUSTOMER2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER2_entry& x, const NUMCUST_mCUSTOMER2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUST_mCUSTOMER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER2_entry& x, const NUMCUST_mCUSTOMER2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUST_mCUSTOMER2_entry,long,
    HashIndex<NUMCUST_mCUSTOMER2_entry,long,NUMCUST_mCUSTOMER2_mapkey012_idxfn,true>,
    HashIndex<NUMCUST_mCUSTOMER2_entry,long,NUMCUST_mCUSTOMER2_mapkey0_idxfn,false>
  > NUMCUST_mCUSTOMER2_map;
  typedef HashIndex<NUMCUST_mCUSTOMER2_entry,long,NUMCUST_mCUSTOMER2_mapkey012_idxfn,true> HashIndex_NUMCUST_mCUSTOMER2_map_012;
  typedef HashIndex<NUMCUST_mCUSTOMER2_entry,long,NUMCUST_mCUSTOMER2_mapkey0_idxfn,false> HashIndex_NUMCUST_mCUSTOMER2_map_0;
  
  struct NUMCUST_mCUSTOMER3_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUST_mCUSTOMER3_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUST_mCUSTOMER3_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUST_mCUSTOMER3_entry(const NUMCUST_mCUSTOMER3_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUST_mCUSTOMER3_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUST_mCUSTOMER3_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct NUMCUST_mCUSTOMER3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER3_entry& x, const NUMCUST_mCUSTOMER3_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUST_mCUSTOMER3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER3_entry& x, const NUMCUST_mCUSTOMER3_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUST_mCUSTOMER3_entry,long,
    HashIndex<NUMCUST_mCUSTOMER3_entry,long,NUMCUST_mCUSTOMER3_mapkey012_idxfn,true>,
    HashIndex<NUMCUST_mCUSTOMER3_entry,long,NUMCUST_mCUSTOMER3_mapkey0_idxfn,false>
  > NUMCUST_mCUSTOMER3_map;
  typedef HashIndex<NUMCUST_mCUSTOMER3_entry,long,NUMCUST_mCUSTOMER3_mapkey012_idxfn,true> HashIndex_NUMCUST_mCUSTOMER3_map_012;
  typedef HashIndex<NUMCUST_mCUSTOMER3_entry,long,NUMCUST_mCUSTOMER3_mapkey0_idxfn,false> HashIndex_NUMCUST_mCUSTOMER3_map_0;
  
  struct NUMCUST_mCUSTOMER4_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUST_mCUSTOMER4_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUST_mCUSTOMER4_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUST_mCUSTOMER4_entry(const NUMCUST_mCUSTOMER4_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUST_mCUSTOMER4_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUST_mCUSTOMER4_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct NUMCUST_mCUSTOMER4_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER4_entry& x, const NUMCUST_mCUSTOMER4_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUST_mCUSTOMER4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER4_entry& x, const NUMCUST_mCUSTOMER4_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUST_mCUSTOMER4_entry,long,
    HashIndex<NUMCUST_mCUSTOMER4_entry,long,NUMCUST_mCUSTOMER4_mapkey012_idxfn,true>,
    HashIndex<NUMCUST_mCUSTOMER4_entry,long,NUMCUST_mCUSTOMER4_mapkey0_idxfn,false>
  > NUMCUST_mCUSTOMER4_map;
  typedef HashIndex<NUMCUST_mCUSTOMER4_entry,long,NUMCUST_mCUSTOMER4_mapkey012_idxfn,true> HashIndex_NUMCUST_mCUSTOMER4_map_012;
  typedef HashIndex<NUMCUST_mCUSTOMER4_entry,long,NUMCUST_mCUSTOMER4_mapkey0_idxfn,false> HashIndex_NUMCUST_mCUSTOMER4_map_0;
  
  struct NUMCUST_mCUSTOMER5_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUST_mCUSTOMER5_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUST_mCUSTOMER5_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUST_mCUSTOMER5_entry(const NUMCUST_mCUSTOMER5_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUST_mCUSTOMER5_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUST_mCUSTOMER5_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct NUMCUST_mCUSTOMER5_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER5_entry& x, const NUMCUST_mCUSTOMER5_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUST_mCUSTOMER5_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER5_entry& x, const NUMCUST_mCUSTOMER5_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUST_mCUSTOMER5_entry,long,
    HashIndex<NUMCUST_mCUSTOMER5_entry,long,NUMCUST_mCUSTOMER5_mapkey012_idxfn,true>,
    HashIndex<NUMCUST_mCUSTOMER5_entry,long,NUMCUST_mCUSTOMER5_mapkey0_idxfn,false>
  > NUMCUST_mCUSTOMER5_map;
  typedef HashIndex<NUMCUST_mCUSTOMER5_entry,long,NUMCUST_mCUSTOMER5_mapkey012_idxfn,true> HashIndex_NUMCUST_mCUSTOMER5_map_012;
  typedef HashIndex<NUMCUST_mCUSTOMER5_entry,long,NUMCUST_mCUSTOMER5_mapkey0_idxfn,false> HashIndex_NUMCUST_mCUSTOMER5_map_0;
  
  struct NUMCUST_mCUSTOMER6_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUST_mCUSTOMER6_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUST_mCUSTOMER6_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUST_mCUSTOMER6_entry(const NUMCUST_mCUSTOMER6_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUST_mCUSTOMER6_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUST_mCUSTOMER6_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct NUMCUST_mCUSTOMER6_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER6_entry& x, const NUMCUST_mCUSTOMER6_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUST_mCUSTOMER6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER6_entry& x, const NUMCUST_mCUSTOMER6_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUST_mCUSTOMER6_entry,long,
    HashIndex<NUMCUST_mCUSTOMER6_entry,long,NUMCUST_mCUSTOMER6_mapkey012_idxfn,true>,
    HashIndex<NUMCUST_mCUSTOMER6_entry,long,NUMCUST_mCUSTOMER6_mapkey0_idxfn,false>
  > NUMCUST_mCUSTOMER6_map;
  typedef HashIndex<NUMCUST_mCUSTOMER6_entry,long,NUMCUST_mCUSTOMER6_mapkey012_idxfn,true> HashIndex_NUMCUST_mCUSTOMER6_map_012;
  typedef HashIndex<NUMCUST_mCUSTOMER6_entry,long,NUMCUST_mCUSTOMER6_mapkey0_idxfn,false> HashIndex_NUMCUST_mCUSTOMER6_map_0;
  
  struct NUMCUST_mCUSTOMER7_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUST_mCUSTOMER7_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUST_mCUSTOMER7_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUST_mCUSTOMER7_entry(const NUMCUST_mCUSTOMER7_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUST_mCUSTOMER7_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUST_mCUSTOMER7_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct NUMCUST_mCUSTOMER7_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER7_entry& x, const NUMCUST_mCUSTOMER7_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUST_mCUSTOMER7_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER7_entry& x, const NUMCUST_mCUSTOMER7_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUST_mCUSTOMER7_entry,long,
    HashIndex<NUMCUST_mCUSTOMER7_entry,long,NUMCUST_mCUSTOMER7_mapkey012_idxfn,true>,
    HashIndex<NUMCUST_mCUSTOMER7_entry,long,NUMCUST_mCUSTOMER7_mapkey0_idxfn,false>
  > NUMCUST_mCUSTOMER7_map;
  typedef HashIndex<NUMCUST_mCUSTOMER7_entry,long,NUMCUST_mCUSTOMER7_mapkey012_idxfn,true> HashIndex_NUMCUST_mCUSTOMER7_map_012;
  typedef HashIndex<NUMCUST_mCUSTOMER7_entry,long,NUMCUST_mCUSTOMER7_mapkey0_idxfn,false> HashIndex_NUMCUST_mCUSTOMER7_map_0;
  
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
  
  struct TOTALACCTBAL_mCUSTOMER1_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBAL_mCUSTOMER1_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBAL_mCUSTOMER1_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBAL_mCUSTOMER1_entry(const TOTALACCTBAL_mCUSTOMER1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER1_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER1_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct TOTALACCTBAL_mCUSTOMER1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER1_entry& x, const TOTALACCTBAL_mCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER1_entry& x, const TOTALACCTBAL_mCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBAL_mCUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBAL_mCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER1_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBAL_mCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn,false>
  > TOTALACCTBAL_mCUSTOMER1_map;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER1_mapkey012_idxfn,true> HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn,false> HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0;
  
  struct TOTALACCTBAL_mCUSTOMER2_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBAL_mCUSTOMER2_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBAL_mCUSTOMER2_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBAL_mCUSTOMER2_entry(const TOTALACCTBAL_mCUSTOMER2_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER2_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER2_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct TOTALACCTBAL_mCUSTOMER2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER2_entry& x, const TOTALACCTBAL_mCUSTOMER2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBAL_mCUSTOMER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER2_entry& x, const TOTALACCTBAL_mCUSTOMER2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBAL_mCUSTOMER2_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBAL_mCUSTOMER2_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER2_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBAL_mCUSTOMER2_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER2_mapkey0_idxfn,false>
  > TOTALACCTBAL_mCUSTOMER2_map;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER2_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER2_mapkey012_idxfn,true> HashIndex_TOTALACCTBAL_mCUSTOMER2_map_012;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER2_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER2_mapkey0_idxfn,false> HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0;
  
  struct TOTALACCTBAL_mCUSTOMER3_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBAL_mCUSTOMER3_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBAL_mCUSTOMER3_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBAL_mCUSTOMER3_entry(const TOTALACCTBAL_mCUSTOMER3_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER3_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER3_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct TOTALACCTBAL_mCUSTOMER3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER3_entry& x, const TOTALACCTBAL_mCUSTOMER3_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBAL_mCUSTOMER3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER3_entry& x, const TOTALACCTBAL_mCUSTOMER3_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBAL_mCUSTOMER3_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBAL_mCUSTOMER3_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER3_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBAL_mCUSTOMER3_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER3_mapkey0_idxfn,false>
  > TOTALACCTBAL_mCUSTOMER3_map;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER3_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER3_mapkey012_idxfn,true> HashIndex_TOTALACCTBAL_mCUSTOMER3_map_012;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER3_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER3_mapkey0_idxfn,false> HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0;
  
  struct TOTALACCTBAL_mCUSTOMER4_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBAL_mCUSTOMER4_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBAL_mCUSTOMER4_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBAL_mCUSTOMER4_entry(const TOTALACCTBAL_mCUSTOMER4_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER4_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER4_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct TOTALACCTBAL_mCUSTOMER4_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER4_entry& x, const TOTALACCTBAL_mCUSTOMER4_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBAL_mCUSTOMER4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER4_entry& x, const TOTALACCTBAL_mCUSTOMER4_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBAL_mCUSTOMER4_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBAL_mCUSTOMER4_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER4_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBAL_mCUSTOMER4_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER4_mapkey0_idxfn,false>
  > TOTALACCTBAL_mCUSTOMER4_map;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER4_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER4_mapkey012_idxfn,true> HashIndex_TOTALACCTBAL_mCUSTOMER4_map_012;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER4_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER4_mapkey0_idxfn,false> HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0;
  
  struct TOTALACCTBAL_mCUSTOMER5_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBAL_mCUSTOMER5_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBAL_mCUSTOMER5_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBAL_mCUSTOMER5_entry(const TOTALACCTBAL_mCUSTOMER5_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER5_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER5_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct TOTALACCTBAL_mCUSTOMER5_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER5_entry& x, const TOTALACCTBAL_mCUSTOMER5_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBAL_mCUSTOMER5_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER5_entry& x, const TOTALACCTBAL_mCUSTOMER5_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBAL_mCUSTOMER5_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBAL_mCUSTOMER5_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER5_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBAL_mCUSTOMER5_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER5_mapkey0_idxfn,false>
  > TOTALACCTBAL_mCUSTOMER5_map;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER5_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER5_mapkey012_idxfn,true> HashIndex_TOTALACCTBAL_mCUSTOMER5_map_012;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER5_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER5_mapkey0_idxfn,false> HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0;
  
  struct TOTALACCTBAL_mCUSTOMER6_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBAL_mCUSTOMER6_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBAL_mCUSTOMER6_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBAL_mCUSTOMER6_entry(const TOTALACCTBAL_mCUSTOMER6_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER6_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER6_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct TOTALACCTBAL_mCUSTOMER6_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER6_entry& x, const TOTALACCTBAL_mCUSTOMER6_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBAL_mCUSTOMER6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER6_entry& x, const TOTALACCTBAL_mCUSTOMER6_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBAL_mCUSTOMER6_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBAL_mCUSTOMER6_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER6_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBAL_mCUSTOMER6_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER6_mapkey0_idxfn,false>
  > TOTALACCTBAL_mCUSTOMER6_map;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER6_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER6_mapkey012_idxfn,true> HashIndex_TOTALACCTBAL_mCUSTOMER6_map_012;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER6_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER6_mapkey0_idxfn,false> HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0;
  
  struct TOTALACCTBAL_mCUSTOMER7_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBAL_mCUSTOMER7_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBAL_mCUSTOMER7_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBAL_mCUSTOMER7_entry(const TOTALACCTBAL_mCUSTOMER7_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER7_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER7_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct TOTALACCTBAL_mCUSTOMER7_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER7_entry& x, const TOTALACCTBAL_mCUSTOMER7_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBAL_mCUSTOMER7_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER7_entry& x, const TOTALACCTBAL_mCUSTOMER7_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBAL_mCUSTOMER7_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBAL_mCUSTOMER7_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER7_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBAL_mCUSTOMER7_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER7_mapkey0_idxfn,false>
  > TOTALACCTBAL_mCUSTOMER7_map;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER7_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER7_mapkey012_idxfn,true> HashIndex_TOTALACCTBAL_mCUSTOMER7_map_012;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER7_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER7_mapkey0_idxfn,false> HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
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
    data_t(): tlq_t(), NUMCUST_mCUSTOMER1_L2_1_L1_1(0L), NUMCUST_mCUSTOMER1_L2_1_L1_2(0L), NUMCUST_mCUSTOMER1_L2_1_L1_3(0L), NUMCUST_mCUSTOMER1_L2_1_L1_4(0L), NUMCUST_mCUSTOMER1_L2_1_L1_5(0L), NUMCUST_mCUSTOMER1_L2_1_L1_6(0L), NUMCUST_mCUSTOMER1_L2_1_L1_7(0L), NUMCUST_mCUSTOMER1_L2_2(0.0), NUMCUST_mCUSTOMER1_L2_4(0.0), NUMCUST_mCUSTOMER1_L2_6(0.0), NUMCUST_mCUSTOMER1_L2_8(0.0), NUMCUST_mCUSTOMER1_L2_10(0.0), NUMCUST_mCUSTOMER1_L2_12(0.0), NUMCUST_mCUSTOMER1_L2_14(0.0) {
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
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg1 = 0L;
        long l1 = (NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se2.modify(orders_custkey)) + 1L);
        (/*if */(l1 == 0L) ? agg1 += 1L : 0L);
        DOUBLE_TYPE agg2 = 0.0;
        long l3 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l3) ? agg2 += Udiv(Ulistmax(1L, l3)) : 0.0);
        DOUBLE_TYPE l2 = (agg2 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER1_map_0* i1 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_0*>(NUMCUST_mCUSTOMER1.index[1]);
          const HASH_RES_t h1 = NUMCUST_mCUSTOMER1_mapkey0_idxfn::hash(se3.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER1_map_0::IdxNode* n1 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_0::IdxNode*>(i1->slice(se3, h1));
          NUMCUST_mCUSTOMER1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e1->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e1->CUSTSALE_CNTRYCODE;
              long v1 = e1->__av;
              (/*if */(c_acctbal > l2) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg1 * v1)) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  NUMCUST_mCUSTOMER1_mapkey0_idxfn::equals(se3, *e1)); 
          }
        }DOUBLE_TYPE agg3 = 0.0;
        long l5 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l5) ? agg3 += Udiv(Ulistmax(1L, l5)) : 0.0);
        DOUBLE_TYPE l4 = (agg3 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER2_map_0* i2 = static_cast<HashIndex_NUMCUST_mCUSTOMER2_map_0*>(NUMCUST_mCUSTOMER2.index[1]);
          const HASH_RES_t h2 = NUMCUST_mCUSTOMER2_mapkey0_idxfn::hash(se4.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER2_map_0::IdxNode* n2 = static_cast<HashIndex_NUMCUST_mCUSTOMER2_map_0::IdxNode*>(i2->slice(se4, h2));
          NUMCUST_mCUSTOMER2_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e2->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e2->CUSTSALE_CNTRYCODE;
              long v2 = e2->__av;
              (/*if */(c_acctbal > l4) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg1 * v2)) : (void)0);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  NUMCUST_mCUSTOMER2_mapkey0_idxfn::equals(se4, *e2)); 
          }
        }DOUBLE_TYPE agg4 = 0.0;
        long l7 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l7) ? agg4 += Udiv(Ulistmax(1L, l7)) : 0.0);
        DOUBLE_TYPE l6 = (agg4 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER3_map_0* i3 = static_cast<HashIndex_NUMCUST_mCUSTOMER3_map_0*>(NUMCUST_mCUSTOMER3.index[1]);
          const HASH_RES_t h3 = NUMCUST_mCUSTOMER3_mapkey0_idxfn::hash(se5.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER3_map_0::IdxNode* n3 = static_cast<HashIndex_NUMCUST_mCUSTOMER3_map_0::IdxNode*>(i3->slice(se5, h3));
          NUMCUST_mCUSTOMER3_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e3->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e3->CUSTSALE_CNTRYCODE;
              long v3 = e3->__av;
              (/*if */(c_acctbal > l6) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg1 * v3)) : (void)0);
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  NUMCUST_mCUSTOMER3_mapkey0_idxfn::equals(se5, *e3)); 
          }
        }DOUBLE_TYPE agg5 = 0.0;
        long l9 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l9) ? agg5 += Udiv(Ulistmax(1L, l9)) : 0.0);
        DOUBLE_TYPE l8 = (agg5 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER4_map_0* i4 = static_cast<HashIndex_NUMCUST_mCUSTOMER4_map_0*>(NUMCUST_mCUSTOMER4.index[1]);
          const HASH_RES_t h4 = NUMCUST_mCUSTOMER4_mapkey0_idxfn::hash(se6.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER4_map_0::IdxNode* n4 = static_cast<HashIndex_NUMCUST_mCUSTOMER4_map_0::IdxNode*>(i4->slice(se6, h4));
          NUMCUST_mCUSTOMER4_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e4->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e4->CUSTSALE_CNTRYCODE;
              long v4 = e4->__av;
              (/*if */(c_acctbal > l8) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg1 * v4)) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  NUMCUST_mCUSTOMER4_mapkey0_idxfn::equals(se6, *e4)); 
          }
        }DOUBLE_TYPE agg6 = 0.0;
        long l11 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l11) ? agg6 += Udiv(Ulistmax(1L, l11)) : 0.0);
        DOUBLE_TYPE l10 = (agg6 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER5_map_0* i5 = static_cast<HashIndex_NUMCUST_mCUSTOMER5_map_0*>(NUMCUST_mCUSTOMER5.index[1]);
          const HASH_RES_t h5 = NUMCUST_mCUSTOMER5_mapkey0_idxfn::hash(se7.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER5_map_0::IdxNode* n5 = static_cast<HashIndex_NUMCUST_mCUSTOMER5_map_0::IdxNode*>(i5->slice(se7, h5));
          NUMCUST_mCUSTOMER5_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e5->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e5->CUSTSALE_CNTRYCODE;
              long v5 = e5->__av;
              (/*if */(c_acctbal > l10) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg1 * v5)) : (void)0);
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  NUMCUST_mCUSTOMER5_mapkey0_idxfn::equals(se7, *e5)); 
          }
        }DOUBLE_TYPE agg7 = 0.0;
        long l13 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l13) ? agg7 += Udiv(Ulistmax(1L, l13)) : 0.0);
        DOUBLE_TYPE l12 = (agg7 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER6_map_0* i6 = static_cast<HashIndex_NUMCUST_mCUSTOMER6_map_0*>(NUMCUST_mCUSTOMER6.index[1]);
          const HASH_RES_t h6 = NUMCUST_mCUSTOMER6_mapkey0_idxfn::hash(se8.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER6_map_0::IdxNode* n6 = static_cast<HashIndex_NUMCUST_mCUSTOMER6_map_0::IdxNode*>(i6->slice(se8, h6));
          NUMCUST_mCUSTOMER6_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e6->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e6->CUSTSALE_CNTRYCODE;
              long v6 = e6->__av;
              (/*if */(c_acctbal > l12) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg1 * v6)) : (void)0);
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h6 == n6->hash &&  NUMCUST_mCUSTOMER6_mapkey0_idxfn::equals(se8, *e6)); 
          }
        }DOUBLE_TYPE agg8 = 0.0;
        long l15 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l15) ? agg8 += Udiv(Ulistmax(1L, l15)) : 0.0);
        DOUBLE_TYPE l14 = (agg8 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER7_map_0* i7 = static_cast<HashIndex_NUMCUST_mCUSTOMER7_map_0*>(NUMCUST_mCUSTOMER7.index[1]);
          const HASH_RES_t h7 = NUMCUST_mCUSTOMER7_mapkey0_idxfn::hash(se9.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER7_map_0::IdxNode* n7 = static_cast<HashIndex_NUMCUST_mCUSTOMER7_map_0::IdxNode*>(i7->slice(se9, h7));
          NUMCUST_mCUSTOMER7_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e7->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e7->CUSTSALE_CNTRYCODE;
              long v7 = e7->__av;
              (/*if */(c_acctbal > l14) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg1 * v7)) : (void)0);
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h7 == n7->hash &&  NUMCUST_mCUSTOMER7_mapkey0_idxfn::equals(se9, *e7)); 
          }
        }long agg9 = 0L;
        long l16 = NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se10.modify(orders_custkey));
        (/*if */(l16 == 0L) ? agg9 += 1L : 0L);
        DOUBLE_TYPE agg10 = 0.0;
        long l18 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l18) ? agg10 += Udiv(Ulistmax(1L, l18)) : 0.0);
        DOUBLE_TYPE l17 = (agg10 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER1_map_0* i8 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_0*>(NUMCUST_mCUSTOMER1.index[1]);
          const HASH_RES_t h8 = NUMCUST_mCUSTOMER1_mapkey0_idxfn::hash(se11.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER1_map_0::IdxNode* n8 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_0::IdxNode*>(i8->slice(se11, h8));
          NUMCUST_mCUSTOMER1_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e8->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e8->CUSTSALE_CNTRYCODE;
              long v8 = e8->__av;
              (/*if */(c_acctbal > l17) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg9 * (v8 * -1L))) : (void)0);
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h8 == n8->hash &&  NUMCUST_mCUSTOMER1_mapkey0_idxfn::equals(se11, *e8)); 
          }
        }DOUBLE_TYPE agg11 = 0.0;
        long l20 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l20) ? agg11 += Udiv(Ulistmax(1L, l20)) : 0.0);
        DOUBLE_TYPE l19 = (agg11 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER2_map_0* i9 = static_cast<HashIndex_NUMCUST_mCUSTOMER2_map_0*>(NUMCUST_mCUSTOMER2.index[1]);
          const HASH_RES_t h9 = NUMCUST_mCUSTOMER2_mapkey0_idxfn::hash(se12.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER2_map_0::IdxNode* n9 = static_cast<HashIndex_NUMCUST_mCUSTOMER2_map_0::IdxNode*>(i9->slice(se12, h9));
          NUMCUST_mCUSTOMER2_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e9->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e9->CUSTSALE_CNTRYCODE;
              long v9 = e9->__av;
              (/*if */(c_acctbal > l19) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg9 * (v9 * -1L))) : (void)0);
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h9 == n9->hash &&  NUMCUST_mCUSTOMER2_mapkey0_idxfn::equals(se12, *e9)); 
          }
        }DOUBLE_TYPE agg12 = 0.0;
        long l22 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l22) ? agg12 += Udiv(Ulistmax(1L, l22)) : 0.0);
        DOUBLE_TYPE l21 = (agg12 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER3_map_0* i10 = static_cast<HashIndex_NUMCUST_mCUSTOMER3_map_0*>(NUMCUST_mCUSTOMER3.index[1]);
          const HASH_RES_t h10 = NUMCUST_mCUSTOMER3_mapkey0_idxfn::hash(se13.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER3_map_0::IdxNode* n10 = static_cast<HashIndex_NUMCUST_mCUSTOMER3_map_0::IdxNode*>(i10->slice(se13, h10));
          NUMCUST_mCUSTOMER3_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e10->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e10->CUSTSALE_CNTRYCODE;
              long v10 = e10->__av;
              (/*if */(c_acctbal > l21) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg9 * (v10 * -1L))) : (void)0);
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h10 == n10->hash &&  NUMCUST_mCUSTOMER3_mapkey0_idxfn::equals(se13, *e10)); 
          }
        }DOUBLE_TYPE agg13 = 0.0;
        long l24 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l24) ? agg13 += Udiv(Ulistmax(1L, l24)) : 0.0);
        DOUBLE_TYPE l23 = (agg13 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER4_map_0* i11 = static_cast<HashIndex_NUMCUST_mCUSTOMER4_map_0*>(NUMCUST_mCUSTOMER4.index[1]);
          const HASH_RES_t h11 = NUMCUST_mCUSTOMER4_mapkey0_idxfn::hash(se14.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER4_map_0::IdxNode* n11 = static_cast<HashIndex_NUMCUST_mCUSTOMER4_map_0::IdxNode*>(i11->slice(se14, h11));
          NUMCUST_mCUSTOMER4_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e11->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e11->CUSTSALE_CNTRYCODE;
              long v11 = e11->__av;
              (/*if */(c_acctbal > l23) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg9 * (v11 * -1L))) : (void)0);
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h11 == n11->hash &&  NUMCUST_mCUSTOMER4_mapkey0_idxfn::equals(se14, *e11)); 
          }
        }DOUBLE_TYPE agg14 = 0.0;
        long l26 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l26) ? agg14 += Udiv(Ulistmax(1L, l26)) : 0.0);
        DOUBLE_TYPE l25 = (agg14 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER5_map_0* i12 = static_cast<HashIndex_NUMCUST_mCUSTOMER5_map_0*>(NUMCUST_mCUSTOMER5.index[1]);
          const HASH_RES_t h12 = NUMCUST_mCUSTOMER5_mapkey0_idxfn::hash(se15.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER5_map_0::IdxNode* n12 = static_cast<HashIndex_NUMCUST_mCUSTOMER5_map_0::IdxNode*>(i12->slice(se15, h12));
          NUMCUST_mCUSTOMER5_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e12->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e12->CUSTSALE_CNTRYCODE;
              long v12 = e12->__av;
              (/*if */(c_acctbal > l25) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg9 * (v12 * -1L))) : (void)0);
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h12 == n12->hash &&  NUMCUST_mCUSTOMER5_mapkey0_idxfn::equals(se15, *e12)); 
          }
        }DOUBLE_TYPE agg15 = 0.0;
        long l28 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l28) ? agg15 += Udiv(Ulistmax(1L, l28)) : 0.0);
        DOUBLE_TYPE l27 = (agg15 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER6_map_0* i13 = static_cast<HashIndex_NUMCUST_mCUSTOMER6_map_0*>(NUMCUST_mCUSTOMER6.index[1]);
          const HASH_RES_t h13 = NUMCUST_mCUSTOMER6_mapkey0_idxfn::hash(se16.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER6_map_0::IdxNode* n13 = static_cast<HashIndex_NUMCUST_mCUSTOMER6_map_0::IdxNode*>(i13->slice(se16, h13));
          NUMCUST_mCUSTOMER6_entry* e13;
         
          if (n13 && (e13 = n13->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e13->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e13->CUSTSALE_CNTRYCODE;
              long v13 = e13->__av;
              (/*if */(c_acctbal > l27) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg9 * (v13 * -1L))) : (void)0);
              n13 = n13->nxt;
            } while (n13 && (e13 = n13->obj) && h13 == n13->hash &&  NUMCUST_mCUSTOMER6_mapkey0_idxfn::equals(se16, *e13)); 
          }
        }DOUBLE_TYPE agg16 = 0.0;
        long l30 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l30) ? agg16 += Udiv(Ulistmax(1L, l30)) : 0.0);
        DOUBLE_TYPE l29 = (agg16 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER7_map_0* i14 = static_cast<HashIndex_NUMCUST_mCUSTOMER7_map_0*>(NUMCUST_mCUSTOMER7.index[1]);
          const HASH_RES_t h14 = NUMCUST_mCUSTOMER7_mapkey0_idxfn::hash(se17.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER7_map_0::IdxNode* n14 = static_cast<HashIndex_NUMCUST_mCUSTOMER7_map_0::IdxNode*>(i14->slice(se17, h14));
          NUMCUST_mCUSTOMER7_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e14->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e14->CUSTSALE_CNTRYCODE;
              long v14 = e14->__av;
              (/*if */(c_acctbal > l29) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),(agg9 * (v14 * -1L))) : (void)0);
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h14 == n14->hash &&  NUMCUST_mCUSTOMER7_mapkey0_idxfn::equals(se17, *e14)); 
          }
        }long agg17 = 0L;
        long l31 = (NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se19.modify(orders_custkey)) + 1L);
        (/*if */(l31 == 0L) ? agg17 += 1L : 0L);
        DOUBLE_TYPE agg18 = 0.0;
        long l33 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l33) ? agg18 += Udiv(Ulistmax(1L, l33)) : 0.0);
        DOUBLE_TYPE l32 = (agg18 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0* i15 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0*>(TOTALACCTBAL_mCUSTOMER1.index[1]);
          const HASH_RES_t h15 = TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn::hash(se20.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0::IdxNode* n15 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0::IdxNode*>(i15->slice(se20, h15));
          TOTALACCTBAL_mCUSTOMER1_entry* e15;
         
          if (n15 && (e15 = n15->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e15->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e15->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v15 = e15->__av;
              (/*if */(c_acctbal > l32) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg17 * v15)) : (void)0);
              n15 = n15->nxt;
            } while (n15 && (e15 = n15->obj) && h15 == n15->hash &&  TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn::equals(se20, *e15)); 
          }
        }DOUBLE_TYPE agg19 = 0.0;
        long l35 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l35) ? agg19 += Udiv(Ulistmax(1L, l35)) : 0.0);
        DOUBLE_TYPE l34 = (agg19 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0* i16 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0*>(TOTALACCTBAL_mCUSTOMER2.index[1]);
          const HASH_RES_t h16 = TOTALACCTBAL_mCUSTOMER2_mapkey0_idxfn::hash(se21.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0::IdxNode* n16 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0::IdxNode*>(i16->slice(se21, h16));
          TOTALACCTBAL_mCUSTOMER2_entry* e16;
         
          if (n16 && (e16 = n16->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e16->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e16->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v16 = e16->__av;
              (/*if */(c_acctbal > l34) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg17 * v16)) : (void)0);
              n16 = n16->nxt;
            } while (n16 && (e16 = n16->obj) && h16 == n16->hash &&  TOTALACCTBAL_mCUSTOMER2_mapkey0_idxfn::equals(se21, *e16)); 
          }
        }DOUBLE_TYPE agg20 = 0.0;
        long l37 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l37) ? agg20 += Udiv(Ulistmax(1L, l37)) : 0.0);
        DOUBLE_TYPE l36 = (agg20 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0* i17 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0*>(TOTALACCTBAL_mCUSTOMER3.index[1]);
          const HASH_RES_t h17 = TOTALACCTBAL_mCUSTOMER3_mapkey0_idxfn::hash(se22.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0::IdxNode* n17 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0::IdxNode*>(i17->slice(se22, h17));
          TOTALACCTBAL_mCUSTOMER3_entry* e17;
         
          if (n17 && (e17 = n17->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e17->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e17->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v17 = e17->__av;
              (/*if */(c_acctbal > l36) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg17 * v17)) : (void)0);
              n17 = n17->nxt;
            } while (n17 && (e17 = n17->obj) && h17 == n17->hash &&  TOTALACCTBAL_mCUSTOMER3_mapkey0_idxfn::equals(se22, *e17)); 
          }
        }DOUBLE_TYPE agg21 = 0.0;
        long l39 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l39) ? agg21 += Udiv(Ulistmax(1L, l39)) : 0.0);
        DOUBLE_TYPE l38 = (agg21 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0* i18 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0*>(TOTALACCTBAL_mCUSTOMER4.index[1]);
          const HASH_RES_t h18 = TOTALACCTBAL_mCUSTOMER4_mapkey0_idxfn::hash(se23.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0::IdxNode* n18 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0::IdxNode*>(i18->slice(se23, h18));
          TOTALACCTBAL_mCUSTOMER4_entry* e18;
         
          if (n18 && (e18 = n18->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e18->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e18->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v18 = e18->__av;
              (/*if */(c_acctbal > l38) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg17 * v18)) : (void)0);
              n18 = n18->nxt;
            } while (n18 && (e18 = n18->obj) && h18 == n18->hash &&  TOTALACCTBAL_mCUSTOMER4_mapkey0_idxfn::equals(se23, *e18)); 
          }
        }DOUBLE_TYPE agg22 = 0.0;
        long l41 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l41) ? agg22 += Udiv(Ulistmax(1L, l41)) : 0.0);
        DOUBLE_TYPE l40 = (agg22 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0* i19 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0*>(TOTALACCTBAL_mCUSTOMER5.index[1]);
          const HASH_RES_t h19 = TOTALACCTBAL_mCUSTOMER5_mapkey0_idxfn::hash(se24.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0::IdxNode* n19 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0::IdxNode*>(i19->slice(se24, h19));
          TOTALACCTBAL_mCUSTOMER5_entry* e19;
         
          if (n19 && (e19 = n19->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e19->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e19->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v19 = e19->__av;
              (/*if */(c_acctbal > l40) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg17 * v19)) : (void)0);
              n19 = n19->nxt;
            } while (n19 && (e19 = n19->obj) && h19 == n19->hash &&  TOTALACCTBAL_mCUSTOMER5_mapkey0_idxfn::equals(se24, *e19)); 
          }
        }DOUBLE_TYPE agg23 = 0.0;
        long l43 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l43) ? agg23 += Udiv(Ulistmax(1L, l43)) : 0.0);
        DOUBLE_TYPE l42 = (agg23 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0* i20 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0*>(TOTALACCTBAL_mCUSTOMER6.index[1]);
          const HASH_RES_t h20 = TOTALACCTBAL_mCUSTOMER6_mapkey0_idxfn::hash(se25.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0::IdxNode* n20 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0::IdxNode*>(i20->slice(se25, h20));
          TOTALACCTBAL_mCUSTOMER6_entry* e20;
         
          if (n20 && (e20 = n20->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e20->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e20->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v20 = e20->__av;
              (/*if */(c_acctbal > l42) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg17 * v20)) : (void)0);
              n20 = n20->nxt;
            } while (n20 && (e20 = n20->obj) && h20 == n20->hash &&  TOTALACCTBAL_mCUSTOMER6_mapkey0_idxfn::equals(se25, *e20)); 
          }
        }DOUBLE_TYPE agg24 = 0.0;
        long l45 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l45) ? agg24 += Udiv(Ulistmax(1L, l45)) : 0.0);
        DOUBLE_TYPE l44 = (agg24 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0* i21 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0*>(TOTALACCTBAL_mCUSTOMER7.index[1]);
          const HASH_RES_t h21 = TOTALACCTBAL_mCUSTOMER7_mapkey0_idxfn::hash(se26.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0::IdxNode* n21 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0::IdxNode*>(i21->slice(se26, h21));
          TOTALACCTBAL_mCUSTOMER7_entry* e21;
         
          if (n21 && (e21 = n21->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e21->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e21->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v21 = e21->__av;
              (/*if */(c_acctbal > l44) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg17 * v21)) : (void)0);
              n21 = n21->nxt;
            } while (n21 && (e21 = n21->obj) && h21 == n21->hash &&  TOTALACCTBAL_mCUSTOMER7_mapkey0_idxfn::equals(se26, *e21)); 
          }
        }long agg25 = 0L;
        long l46 = NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se27.modify(orders_custkey));
        (/*if */(l46 == 0L) ? agg25 += 1L : 0L);
        DOUBLE_TYPE agg26 = 0.0;
        long l48 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l48) ? agg26 += Udiv(Ulistmax(1L, l48)) : 0.0);
        DOUBLE_TYPE l47 = (agg26 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0* i22 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0*>(TOTALACCTBAL_mCUSTOMER1.index[1]);
          const HASH_RES_t h22 = TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn::hash(se28.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0::IdxNode* n22 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0::IdxNode*>(i22->slice(se28, h22));
          TOTALACCTBAL_mCUSTOMER1_entry* e22;
         
          if (n22 && (e22 = n22->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e22->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e22->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v22 = e22->__av;
              (/*if */(c_acctbal > l47) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg25 * (v22 * -1L))) : (void)0);
              n22 = n22->nxt;
            } while (n22 && (e22 = n22->obj) && h22 == n22->hash &&  TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn::equals(se28, *e22)); 
          }
        }DOUBLE_TYPE agg27 = 0.0;
        long l50 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l50) ? agg27 += Udiv(Ulistmax(1L, l50)) : 0.0);
        DOUBLE_TYPE l49 = (agg27 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0* i23 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0*>(TOTALACCTBAL_mCUSTOMER2.index[1]);
          const HASH_RES_t h23 = TOTALACCTBAL_mCUSTOMER2_mapkey0_idxfn::hash(se29.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0::IdxNode* n23 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0::IdxNode*>(i23->slice(se29, h23));
          TOTALACCTBAL_mCUSTOMER2_entry* e23;
         
          if (n23 && (e23 = n23->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e23->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e23->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v23 = e23->__av;
              (/*if */(c_acctbal > l49) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg25 * (v23 * -1L))) : (void)0);
              n23 = n23->nxt;
            } while (n23 && (e23 = n23->obj) && h23 == n23->hash &&  TOTALACCTBAL_mCUSTOMER2_mapkey0_idxfn::equals(se29, *e23)); 
          }
        }DOUBLE_TYPE agg28 = 0.0;
        long l52 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l52) ? agg28 += Udiv(Ulistmax(1L, l52)) : 0.0);
        DOUBLE_TYPE l51 = (agg28 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0* i24 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0*>(TOTALACCTBAL_mCUSTOMER3.index[1]);
          const HASH_RES_t h24 = TOTALACCTBAL_mCUSTOMER3_mapkey0_idxfn::hash(se30.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0::IdxNode* n24 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0::IdxNode*>(i24->slice(se30, h24));
          TOTALACCTBAL_mCUSTOMER3_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e24->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e24->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v24 = e24->__av;
              (/*if */(c_acctbal > l51) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg25 * (v24 * -1L))) : (void)0);
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h24 == n24->hash &&  TOTALACCTBAL_mCUSTOMER3_mapkey0_idxfn::equals(se30, *e24)); 
          }
        }DOUBLE_TYPE agg29 = 0.0;
        long l54 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l54) ? agg29 += Udiv(Ulistmax(1L, l54)) : 0.0);
        DOUBLE_TYPE l53 = (agg29 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0* i25 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0*>(TOTALACCTBAL_mCUSTOMER4.index[1]);
          const HASH_RES_t h25 = TOTALACCTBAL_mCUSTOMER4_mapkey0_idxfn::hash(se31.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0::IdxNode* n25 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0::IdxNode*>(i25->slice(se31, h25));
          TOTALACCTBAL_mCUSTOMER4_entry* e25;
         
          if (n25 && (e25 = n25->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e25->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e25->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v25 = e25->__av;
              (/*if */(c_acctbal > l53) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg25 * (v25 * -1L))) : (void)0);
              n25 = n25->nxt;
            } while (n25 && (e25 = n25->obj) && h25 == n25->hash &&  TOTALACCTBAL_mCUSTOMER4_mapkey0_idxfn::equals(se31, *e25)); 
          }
        }DOUBLE_TYPE agg30 = 0.0;
        long l56 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l56) ? agg30 += Udiv(Ulistmax(1L, l56)) : 0.0);
        DOUBLE_TYPE l55 = (agg30 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0* i26 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0*>(TOTALACCTBAL_mCUSTOMER5.index[1]);
          const HASH_RES_t h26 = TOTALACCTBAL_mCUSTOMER5_mapkey0_idxfn::hash(se32.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0::IdxNode* n26 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0::IdxNode*>(i26->slice(se32, h26));
          TOTALACCTBAL_mCUSTOMER5_entry* e26;
         
          if (n26 && (e26 = n26->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e26->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e26->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v26 = e26->__av;
              (/*if */(c_acctbal > l55) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg25 * (v26 * -1L))) : (void)0);
              n26 = n26->nxt;
            } while (n26 && (e26 = n26->obj) && h26 == n26->hash &&  TOTALACCTBAL_mCUSTOMER5_mapkey0_idxfn::equals(se32, *e26)); 
          }
        }DOUBLE_TYPE agg31 = 0.0;
        long l58 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l58) ? agg31 += Udiv(Ulistmax(1L, l58)) : 0.0);
        DOUBLE_TYPE l57 = (agg31 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0* i27 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0*>(TOTALACCTBAL_mCUSTOMER6.index[1]);
          const HASH_RES_t h27 = TOTALACCTBAL_mCUSTOMER6_mapkey0_idxfn::hash(se33.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0::IdxNode* n27 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0::IdxNode*>(i27->slice(se33, h27));
          TOTALACCTBAL_mCUSTOMER6_entry* e27;
         
          if (n27 && (e27 = n27->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e27->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e27->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v27 = e27->__av;
              (/*if */(c_acctbal > l57) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg25 * (v27 * -1L))) : (void)0);
              n27 = n27->nxt;
            } while (n27 && (e27 = n27->obj) && h27 == n27->hash &&  TOTALACCTBAL_mCUSTOMER6_mapkey0_idxfn::equals(se33, *e27)); 
          }
        }DOUBLE_TYPE agg32 = 0.0;
        long l60 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l60) ? agg32 += Udiv(Ulistmax(1L, l60)) : 0.0);
        DOUBLE_TYPE l59 = (agg32 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0* i28 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0*>(TOTALACCTBAL_mCUSTOMER7.index[1]);
          const HASH_RES_t h28 = TOTALACCTBAL_mCUSTOMER7_mapkey0_idxfn::hash(se34.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0::IdxNode* n28 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0::IdxNode*>(i28->slice(se34, h28));
          TOTALACCTBAL_mCUSTOMER7_entry* e28;
         
          if (n28 && (e28 = n28->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e28->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e28->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v28 = e28->__av;
              (/*if */(c_acctbal > l59) ? TOTALACCTBAL.addOrDelOnZero(se18.modify(custsale_cntrycode),(agg25 * (v28 * -1L))) : (void)0);
              n28 = n28->nxt;
            } while (n28 && (e28 = n28->obj) && h28 == n28->hash &&  TOTALACCTBAL_mCUSTOMER7_mapkey0_idxfn::equals(se34, *e28)); 
          }
        }NUMCUST_mCUSTOMER1_L3_1.addOrDelOnZero(se35.modify(orders_custkey),1L);
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg33 = 0L;
        long l61 = (NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se37.modify(orders_custkey)) + -1L);
        (/*if */(l61 == 0L) ? agg33 += 1L : 0L);
        DOUBLE_TYPE agg34 = 0.0;
        long l63 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l63) ? agg34 += Udiv(Ulistmax(1L, l63)) : 0.0);
        DOUBLE_TYPE l62 = (agg34 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER1_map_0* i29 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_0*>(NUMCUST_mCUSTOMER1.index[1]);
          const HASH_RES_t h29 = NUMCUST_mCUSTOMER1_mapkey0_idxfn::hash(se38.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER1_map_0::IdxNode* n29 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_0::IdxNode*>(i29->slice(se38, h29));
          NUMCUST_mCUSTOMER1_entry* e29;
         
          if (n29 && (e29 = n29->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e29->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e29->CUSTSALE_CNTRYCODE;
              long v29 = e29->__av;
              (/*if */(c_acctbal > l62) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg33 * v29)) : (void)0);
              n29 = n29->nxt;
            } while (n29 && (e29 = n29->obj) && h29 == n29->hash &&  NUMCUST_mCUSTOMER1_mapkey0_idxfn::equals(se38, *e29)); 
          }
        }DOUBLE_TYPE agg35 = 0.0;
        long l65 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l65) ? agg35 += Udiv(Ulistmax(1L, l65)) : 0.0);
        DOUBLE_TYPE l64 = (agg35 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER2_map_0* i30 = static_cast<HashIndex_NUMCUST_mCUSTOMER2_map_0*>(NUMCUST_mCUSTOMER2.index[1]);
          const HASH_RES_t h30 = NUMCUST_mCUSTOMER2_mapkey0_idxfn::hash(se39.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER2_map_0::IdxNode* n30 = static_cast<HashIndex_NUMCUST_mCUSTOMER2_map_0::IdxNode*>(i30->slice(se39, h30));
          NUMCUST_mCUSTOMER2_entry* e30;
         
          if (n30 && (e30 = n30->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e30->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e30->CUSTSALE_CNTRYCODE;
              long v30 = e30->__av;
              (/*if */(c_acctbal > l64) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg33 * v30)) : (void)0);
              n30 = n30->nxt;
            } while (n30 && (e30 = n30->obj) && h30 == n30->hash &&  NUMCUST_mCUSTOMER2_mapkey0_idxfn::equals(se39, *e30)); 
          }
        }DOUBLE_TYPE agg36 = 0.0;
        long l67 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l67) ? agg36 += Udiv(Ulistmax(1L, l67)) : 0.0);
        DOUBLE_TYPE l66 = (agg36 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER3_map_0* i31 = static_cast<HashIndex_NUMCUST_mCUSTOMER3_map_0*>(NUMCUST_mCUSTOMER3.index[1]);
          const HASH_RES_t h31 = NUMCUST_mCUSTOMER3_mapkey0_idxfn::hash(se40.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER3_map_0::IdxNode* n31 = static_cast<HashIndex_NUMCUST_mCUSTOMER3_map_0::IdxNode*>(i31->slice(se40, h31));
          NUMCUST_mCUSTOMER3_entry* e31;
         
          if (n31 && (e31 = n31->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e31->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e31->CUSTSALE_CNTRYCODE;
              long v31 = e31->__av;
              (/*if */(c_acctbal > l66) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg33 * v31)) : (void)0);
              n31 = n31->nxt;
            } while (n31 && (e31 = n31->obj) && h31 == n31->hash &&  NUMCUST_mCUSTOMER3_mapkey0_idxfn::equals(se40, *e31)); 
          }
        }DOUBLE_TYPE agg37 = 0.0;
        long l69 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l69) ? agg37 += Udiv(Ulistmax(1L, l69)) : 0.0);
        DOUBLE_TYPE l68 = (agg37 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER4_map_0* i32 = static_cast<HashIndex_NUMCUST_mCUSTOMER4_map_0*>(NUMCUST_mCUSTOMER4.index[1]);
          const HASH_RES_t h32 = NUMCUST_mCUSTOMER4_mapkey0_idxfn::hash(se41.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER4_map_0::IdxNode* n32 = static_cast<HashIndex_NUMCUST_mCUSTOMER4_map_0::IdxNode*>(i32->slice(se41, h32));
          NUMCUST_mCUSTOMER4_entry* e32;
         
          if (n32 && (e32 = n32->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e32->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e32->CUSTSALE_CNTRYCODE;
              long v32 = e32->__av;
              (/*if */(c_acctbal > l68) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg33 * v32)) : (void)0);
              n32 = n32->nxt;
            } while (n32 && (e32 = n32->obj) && h32 == n32->hash &&  NUMCUST_mCUSTOMER4_mapkey0_idxfn::equals(se41, *e32)); 
          }
        }DOUBLE_TYPE agg38 = 0.0;
        long l71 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l71) ? agg38 += Udiv(Ulistmax(1L, l71)) : 0.0);
        DOUBLE_TYPE l70 = (agg38 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER5_map_0* i33 = static_cast<HashIndex_NUMCUST_mCUSTOMER5_map_0*>(NUMCUST_mCUSTOMER5.index[1]);
          const HASH_RES_t h33 = NUMCUST_mCUSTOMER5_mapkey0_idxfn::hash(se42.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER5_map_0::IdxNode* n33 = static_cast<HashIndex_NUMCUST_mCUSTOMER5_map_0::IdxNode*>(i33->slice(se42, h33));
          NUMCUST_mCUSTOMER5_entry* e33;
         
          if (n33 && (e33 = n33->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e33->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e33->CUSTSALE_CNTRYCODE;
              long v33 = e33->__av;
              (/*if */(c_acctbal > l70) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg33 * v33)) : (void)0);
              n33 = n33->nxt;
            } while (n33 && (e33 = n33->obj) && h33 == n33->hash &&  NUMCUST_mCUSTOMER5_mapkey0_idxfn::equals(se42, *e33)); 
          }
        }DOUBLE_TYPE agg39 = 0.0;
        long l73 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l73) ? agg39 += Udiv(Ulistmax(1L, l73)) : 0.0);
        DOUBLE_TYPE l72 = (agg39 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER6_map_0* i34 = static_cast<HashIndex_NUMCUST_mCUSTOMER6_map_0*>(NUMCUST_mCUSTOMER6.index[1]);
          const HASH_RES_t h34 = NUMCUST_mCUSTOMER6_mapkey0_idxfn::hash(se43.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER6_map_0::IdxNode* n34 = static_cast<HashIndex_NUMCUST_mCUSTOMER6_map_0::IdxNode*>(i34->slice(se43, h34));
          NUMCUST_mCUSTOMER6_entry* e34;
         
          if (n34 && (e34 = n34->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e34->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e34->CUSTSALE_CNTRYCODE;
              long v34 = e34->__av;
              (/*if */(c_acctbal > l72) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg33 * v34)) : (void)0);
              n34 = n34->nxt;
            } while (n34 && (e34 = n34->obj) && h34 == n34->hash &&  NUMCUST_mCUSTOMER6_mapkey0_idxfn::equals(se43, *e34)); 
          }
        }DOUBLE_TYPE agg40 = 0.0;
        long l75 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l75) ? agg40 += Udiv(Ulistmax(1L, l75)) : 0.0);
        DOUBLE_TYPE l74 = (agg40 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER7_map_0* i35 = static_cast<HashIndex_NUMCUST_mCUSTOMER7_map_0*>(NUMCUST_mCUSTOMER7.index[1]);
          const HASH_RES_t h35 = NUMCUST_mCUSTOMER7_mapkey0_idxfn::hash(se44.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER7_map_0::IdxNode* n35 = static_cast<HashIndex_NUMCUST_mCUSTOMER7_map_0::IdxNode*>(i35->slice(se44, h35));
          NUMCUST_mCUSTOMER7_entry* e35;
         
          if (n35 && (e35 = n35->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e35->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e35->CUSTSALE_CNTRYCODE;
              long v35 = e35->__av;
              (/*if */(c_acctbal > l74) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg33 * v35)) : (void)0);
              n35 = n35->nxt;
            } while (n35 && (e35 = n35->obj) && h35 == n35->hash &&  NUMCUST_mCUSTOMER7_mapkey0_idxfn::equals(se44, *e35)); 
          }
        }long agg41 = 0L;
        long l76 = NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se45.modify(orders_custkey));
        (/*if */(l76 == 0L) ? agg41 += 1L : 0L);
        DOUBLE_TYPE agg42 = 0.0;
        long l78 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l78) ? agg42 += Udiv(Ulistmax(1L, l78)) : 0.0);
        DOUBLE_TYPE l77 = (agg42 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER1_map_0* i36 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_0*>(NUMCUST_mCUSTOMER1.index[1]);
          const HASH_RES_t h36 = NUMCUST_mCUSTOMER1_mapkey0_idxfn::hash(se46.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER1_map_0::IdxNode* n36 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_0::IdxNode*>(i36->slice(se46, h36));
          NUMCUST_mCUSTOMER1_entry* e36;
         
          if (n36 && (e36 = n36->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e36->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e36->CUSTSALE_CNTRYCODE;
              long v36 = e36->__av;
              (/*if */(c_acctbal > l77) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg41 * (v36 * -1L))) : (void)0);
              n36 = n36->nxt;
            } while (n36 && (e36 = n36->obj) && h36 == n36->hash &&  NUMCUST_mCUSTOMER1_mapkey0_idxfn::equals(se46, *e36)); 
          }
        }DOUBLE_TYPE agg43 = 0.0;
        long l80 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l80) ? agg43 += Udiv(Ulistmax(1L, l80)) : 0.0);
        DOUBLE_TYPE l79 = (agg43 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER2_map_0* i37 = static_cast<HashIndex_NUMCUST_mCUSTOMER2_map_0*>(NUMCUST_mCUSTOMER2.index[1]);
          const HASH_RES_t h37 = NUMCUST_mCUSTOMER2_mapkey0_idxfn::hash(se47.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER2_map_0::IdxNode* n37 = static_cast<HashIndex_NUMCUST_mCUSTOMER2_map_0::IdxNode*>(i37->slice(se47, h37));
          NUMCUST_mCUSTOMER2_entry* e37;
         
          if (n37 && (e37 = n37->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e37->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e37->CUSTSALE_CNTRYCODE;
              long v37 = e37->__av;
              (/*if */(c_acctbal > l79) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg41 * (v37 * -1L))) : (void)0);
              n37 = n37->nxt;
            } while (n37 && (e37 = n37->obj) && h37 == n37->hash &&  NUMCUST_mCUSTOMER2_mapkey0_idxfn::equals(se47, *e37)); 
          }
        }DOUBLE_TYPE agg44 = 0.0;
        long l82 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l82) ? agg44 += Udiv(Ulistmax(1L, l82)) : 0.0);
        DOUBLE_TYPE l81 = (agg44 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER3_map_0* i38 = static_cast<HashIndex_NUMCUST_mCUSTOMER3_map_0*>(NUMCUST_mCUSTOMER3.index[1]);
          const HASH_RES_t h38 = NUMCUST_mCUSTOMER3_mapkey0_idxfn::hash(se48.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER3_map_0::IdxNode* n38 = static_cast<HashIndex_NUMCUST_mCUSTOMER3_map_0::IdxNode*>(i38->slice(se48, h38));
          NUMCUST_mCUSTOMER3_entry* e38;
         
          if (n38 && (e38 = n38->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e38->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e38->CUSTSALE_CNTRYCODE;
              long v38 = e38->__av;
              (/*if */(c_acctbal > l81) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg41 * (v38 * -1L))) : (void)0);
              n38 = n38->nxt;
            } while (n38 && (e38 = n38->obj) && h38 == n38->hash &&  NUMCUST_mCUSTOMER3_mapkey0_idxfn::equals(se48, *e38)); 
          }
        }DOUBLE_TYPE agg45 = 0.0;
        long l84 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l84) ? agg45 += Udiv(Ulistmax(1L, l84)) : 0.0);
        DOUBLE_TYPE l83 = (agg45 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER4_map_0* i39 = static_cast<HashIndex_NUMCUST_mCUSTOMER4_map_0*>(NUMCUST_mCUSTOMER4.index[1]);
          const HASH_RES_t h39 = NUMCUST_mCUSTOMER4_mapkey0_idxfn::hash(se49.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER4_map_0::IdxNode* n39 = static_cast<HashIndex_NUMCUST_mCUSTOMER4_map_0::IdxNode*>(i39->slice(se49, h39));
          NUMCUST_mCUSTOMER4_entry* e39;
         
          if (n39 && (e39 = n39->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e39->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e39->CUSTSALE_CNTRYCODE;
              long v39 = e39->__av;
              (/*if */(c_acctbal > l83) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg41 * (v39 * -1L))) : (void)0);
              n39 = n39->nxt;
            } while (n39 && (e39 = n39->obj) && h39 == n39->hash &&  NUMCUST_mCUSTOMER4_mapkey0_idxfn::equals(se49, *e39)); 
          }
        }DOUBLE_TYPE agg46 = 0.0;
        long l86 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l86) ? agg46 += Udiv(Ulistmax(1L, l86)) : 0.0);
        DOUBLE_TYPE l85 = (agg46 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER5_map_0* i40 = static_cast<HashIndex_NUMCUST_mCUSTOMER5_map_0*>(NUMCUST_mCUSTOMER5.index[1]);
          const HASH_RES_t h40 = NUMCUST_mCUSTOMER5_mapkey0_idxfn::hash(se50.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER5_map_0::IdxNode* n40 = static_cast<HashIndex_NUMCUST_mCUSTOMER5_map_0::IdxNode*>(i40->slice(se50, h40));
          NUMCUST_mCUSTOMER5_entry* e40;
         
          if (n40 && (e40 = n40->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e40->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e40->CUSTSALE_CNTRYCODE;
              long v40 = e40->__av;
              (/*if */(c_acctbal > l85) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg41 * (v40 * -1L))) : (void)0);
              n40 = n40->nxt;
            } while (n40 && (e40 = n40->obj) && h40 == n40->hash &&  NUMCUST_mCUSTOMER5_mapkey0_idxfn::equals(se50, *e40)); 
          }
        }DOUBLE_TYPE agg47 = 0.0;
        long l88 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l88) ? agg47 += Udiv(Ulistmax(1L, l88)) : 0.0);
        DOUBLE_TYPE l87 = (agg47 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER6_map_0* i41 = static_cast<HashIndex_NUMCUST_mCUSTOMER6_map_0*>(NUMCUST_mCUSTOMER6.index[1]);
          const HASH_RES_t h41 = NUMCUST_mCUSTOMER6_mapkey0_idxfn::hash(se51.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER6_map_0::IdxNode* n41 = static_cast<HashIndex_NUMCUST_mCUSTOMER6_map_0::IdxNode*>(i41->slice(se51, h41));
          NUMCUST_mCUSTOMER6_entry* e41;
         
          if (n41 && (e41 = n41->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e41->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e41->CUSTSALE_CNTRYCODE;
              long v41 = e41->__av;
              (/*if */(c_acctbal > l87) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg41 * (v41 * -1L))) : (void)0);
              n41 = n41->nxt;
            } while (n41 && (e41 = n41->obj) && h41 == n41->hash &&  NUMCUST_mCUSTOMER6_mapkey0_idxfn::equals(se51, *e41)); 
          }
        }DOUBLE_TYPE agg48 = 0.0;
        long l90 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l90) ? agg48 += Udiv(Ulistmax(1L, l90)) : 0.0);
        DOUBLE_TYPE l89 = (agg48 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER7_map_0* i42 = static_cast<HashIndex_NUMCUST_mCUSTOMER7_map_0*>(NUMCUST_mCUSTOMER7.index[1]);
          const HASH_RES_t h42 = NUMCUST_mCUSTOMER7_mapkey0_idxfn::hash(se52.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER7_map_0::IdxNode* n42 = static_cast<HashIndex_NUMCUST_mCUSTOMER7_map_0::IdxNode*>(i42->slice(se52, h42));
          NUMCUST_mCUSTOMER7_entry* e42;
         
          if (n42 && (e42 = n42->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e42->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e42->CUSTSALE_CNTRYCODE;
              long v42 = e42->__av;
              (/*if */(c_acctbal > l89) ? NUMCUST.addOrDelOnZero(se36.modify(custsale_cntrycode),(agg41 * (v42 * -1L))) : (void)0);
              n42 = n42->nxt;
            } while (n42 && (e42 = n42->obj) && h42 == n42->hash &&  NUMCUST_mCUSTOMER7_mapkey0_idxfn::equals(se52, *e42)); 
          }
        }long agg49 = 0L;
        long l91 = (NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se54.modify(orders_custkey)) + -1L);
        (/*if */(l91 == 0L) ? agg49 += 1L : 0L);
        DOUBLE_TYPE agg50 = 0.0;
        long l93 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l93) ? agg50 += Udiv(Ulistmax(1L, l93)) : 0.0);
        DOUBLE_TYPE l92 = (agg50 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0* i43 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0*>(TOTALACCTBAL_mCUSTOMER1.index[1]);
          const HASH_RES_t h43 = TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn::hash(se55.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0::IdxNode* n43 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0::IdxNode*>(i43->slice(se55, h43));
          TOTALACCTBAL_mCUSTOMER1_entry* e43;
         
          if (n43 && (e43 = n43->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e43->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e43->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v43 = e43->__av;
              (/*if */(c_acctbal > l92) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg49 * v43)) : (void)0);
              n43 = n43->nxt;
            } while (n43 && (e43 = n43->obj) && h43 == n43->hash &&  TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn::equals(se55, *e43)); 
          }
        }DOUBLE_TYPE agg51 = 0.0;
        long l95 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l95) ? agg51 += Udiv(Ulistmax(1L, l95)) : 0.0);
        DOUBLE_TYPE l94 = (agg51 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0* i44 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0*>(TOTALACCTBAL_mCUSTOMER2.index[1]);
          const HASH_RES_t h44 = TOTALACCTBAL_mCUSTOMER2_mapkey0_idxfn::hash(se56.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0::IdxNode* n44 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0::IdxNode*>(i44->slice(se56, h44));
          TOTALACCTBAL_mCUSTOMER2_entry* e44;
         
          if (n44 && (e44 = n44->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e44->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e44->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v44 = e44->__av;
              (/*if */(c_acctbal > l94) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg49 * v44)) : (void)0);
              n44 = n44->nxt;
            } while (n44 && (e44 = n44->obj) && h44 == n44->hash &&  TOTALACCTBAL_mCUSTOMER2_mapkey0_idxfn::equals(se56, *e44)); 
          }
        }DOUBLE_TYPE agg52 = 0.0;
        long l97 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l97) ? agg52 += Udiv(Ulistmax(1L, l97)) : 0.0);
        DOUBLE_TYPE l96 = (agg52 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0* i45 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0*>(TOTALACCTBAL_mCUSTOMER3.index[1]);
          const HASH_RES_t h45 = TOTALACCTBAL_mCUSTOMER3_mapkey0_idxfn::hash(se57.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0::IdxNode* n45 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0::IdxNode*>(i45->slice(se57, h45));
          TOTALACCTBAL_mCUSTOMER3_entry* e45;
         
          if (n45 && (e45 = n45->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e45->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e45->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v45 = e45->__av;
              (/*if */(c_acctbal > l96) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg49 * v45)) : (void)0);
              n45 = n45->nxt;
            } while (n45 && (e45 = n45->obj) && h45 == n45->hash &&  TOTALACCTBAL_mCUSTOMER3_mapkey0_idxfn::equals(se57, *e45)); 
          }
        }DOUBLE_TYPE agg53 = 0.0;
        long l99 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l99) ? agg53 += Udiv(Ulistmax(1L, l99)) : 0.0);
        DOUBLE_TYPE l98 = (agg53 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0* i46 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0*>(TOTALACCTBAL_mCUSTOMER4.index[1]);
          const HASH_RES_t h46 = TOTALACCTBAL_mCUSTOMER4_mapkey0_idxfn::hash(se58.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0::IdxNode* n46 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0::IdxNode*>(i46->slice(se58, h46));
          TOTALACCTBAL_mCUSTOMER4_entry* e46;
         
          if (n46 && (e46 = n46->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e46->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e46->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v46 = e46->__av;
              (/*if */(c_acctbal > l98) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg49 * v46)) : (void)0);
              n46 = n46->nxt;
            } while (n46 && (e46 = n46->obj) && h46 == n46->hash &&  TOTALACCTBAL_mCUSTOMER4_mapkey0_idxfn::equals(se58, *e46)); 
          }
        }DOUBLE_TYPE agg54 = 0.0;
        long l101 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l101) ? agg54 += Udiv(Ulistmax(1L, l101)) : 0.0);
        DOUBLE_TYPE l100 = (agg54 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0* i47 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0*>(TOTALACCTBAL_mCUSTOMER5.index[1]);
          const HASH_RES_t h47 = TOTALACCTBAL_mCUSTOMER5_mapkey0_idxfn::hash(se59.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0::IdxNode* n47 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0::IdxNode*>(i47->slice(se59, h47));
          TOTALACCTBAL_mCUSTOMER5_entry* e47;
         
          if (n47 && (e47 = n47->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e47->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e47->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v47 = e47->__av;
              (/*if */(c_acctbal > l100) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg49 * v47)) : (void)0);
              n47 = n47->nxt;
            } while (n47 && (e47 = n47->obj) && h47 == n47->hash &&  TOTALACCTBAL_mCUSTOMER5_mapkey0_idxfn::equals(se59, *e47)); 
          }
        }DOUBLE_TYPE agg55 = 0.0;
        long l103 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l103) ? agg55 += Udiv(Ulistmax(1L, l103)) : 0.0);
        DOUBLE_TYPE l102 = (agg55 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0* i48 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0*>(TOTALACCTBAL_mCUSTOMER6.index[1]);
          const HASH_RES_t h48 = TOTALACCTBAL_mCUSTOMER6_mapkey0_idxfn::hash(se60.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0::IdxNode* n48 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0::IdxNode*>(i48->slice(se60, h48));
          TOTALACCTBAL_mCUSTOMER6_entry* e48;
         
          if (n48 && (e48 = n48->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e48->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e48->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v48 = e48->__av;
              (/*if */(c_acctbal > l102) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg49 * v48)) : (void)0);
              n48 = n48->nxt;
            } while (n48 && (e48 = n48->obj) && h48 == n48->hash &&  TOTALACCTBAL_mCUSTOMER6_mapkey0_idxfn::equals(se60, *e48)); 
          }
        }DOUBLE_TYPE agg56 = 0.0;
        long l105 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l105) ? agg56 += Udiv(Ulistmax(1L, l105)) : 0.0);
        DOUBLE_TYPE l104 = (agg56 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0* i49 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0*>(TOTALACCTBAL_mCUSTOMER7.index[1]);
          const HASH_RES_t h49 = TOTALACCTBAL_mCUSTOMER7_mapkey0_idxfn::hash(se61.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0::IdxNode* n49 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0::IdxNode*>(i49->slice(se61, h49));
          TOTALACCTBAL_mCUSTOMER7_entry* e49;
         
          if (n49 && (e49 = n49->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e49->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e49->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v49 = e49->__av;
              (/*if */(c_acctbal > l104) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg49 * v49)) : (void)0);
              n49 = n49->nxt;
            } while (n49 && (e49 = n49->obj) && h49 == n49->hash &&  TOTALACCTBAL_mCUSTOMER7_mapkey0_idxfn::equals(se61, *e49)); 
          }
        }long agg57 = 0L;
        long l106 = NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se62.modify(orders_custkey));
        (/*if */(l106 == 0L) ? agg57 += 1L : 0L);
        DOUBLE_TYPE agg58 = 0.0;
        long l108 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l108) ? agg58 += Udiv(Ulistmax(1L, l108)) : 0.0);
        DOUBLE_TYPE l107 = (agg58 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0* i50 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0*>(TOTALACCTBAL_mCUSTOMER1.index[1]);
          const HASH_RES_t h50 = TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn::hash(se63.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0::IdxNode* n50 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0::IdxNode*>(i50->slice(se63, h50));
          TOTALACCTBAL_mCUSTOMER1_entry* e50;
         
          if (n50 && (e50 = n50->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e50->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e50->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v50 = e50->__av;
              (/*if */(c_acctbal > l107) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg57 * (v50 * -1L))) : (void)0);
              n50 = n50->nxt;
            } while (n50 && (e50 = n50->obj) && h50 == n50->hash &&  TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn::equals(se63, *e50)); 
          }
        }DOUBLE_TYPE agg59 = 0.0;
        long l110 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l110) ? agg59 += Udiv(Ulistmax(1L, l110)) : 0.0);
        DOUBLE_TYPE l109 = (agg59 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0* i51 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0*>(TOTALACCTBAL_mCUSTOMER2.index[1]);
          const HASH_RES_t h51 = TOTALACCTBAL_mCUSTOMER2_mapkey0_idxfn::hash(se64.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0::IdxNode* n51 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER2_map_0::IdxNode*>(i51->slice(se64, h51));
          TOTALACCTBAL_mCUSTOMER2_entry* e51;
         
          if (n51 && (e51 = n51->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e51->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e51->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v51 = e51->__av;
              (/*if */(c_acctbal > l109) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg57 * (v51 * -1L))) : (void)0);
              n51 = n51->nxt;
            } while (n51 && (e51 = n51->obj) && h51 == n51->hash &&  TOTALACCTBAL_mCUSTOMER2_mapkey0_idxfn::equals(se64, *e51)); 
          }
        }DOUBLE_TYPE agg60 = 0.0;
        long l112 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l112) ? agg60 += Udiv(Ulistmax(1L, l112)) : 0.0);
        DOUBLE_TYPE l111 = (agg60 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0* i52 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0*>(TOTALACCTBAL_mCUSTOMER3.index[1]);
          const HASH_RES_t h52 = TOTALACCTBAL_mCUSTOMER3_mapkey0_idxfn::hash(se65.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0::IdxNode* n52 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER3_map_0::IdxNode*>(i52->slice(se65, h52));
          TOTALACCTBAL_mCUSTOMER3_entry* e52;
         
          if (n52 && (e52 = n52->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e52->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e52->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v52 = e52->__av;
              (/*if */(c_acctbal > l111) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg57 * (v52 * -1L))) : (void)0);
              n52 = n52->nxt;
            } while (n52 && (e52 = n52->obj) && h52 == n52->hash &&  TOTALACCTBAL_mCUSTOMER3_mapkey0_idxfn::equals(se65, *e52)); 
          }
        }DOUBLE_TYPE agg61 = 0.0;
        long l114 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l114) ? agg61 += Udiv(Ulistmax(1L, l114)) : 0.0);
        DOUBLE_TYPE l113 = (agg61 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0* i53 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0*>(TOTALACCTBAL_mCUSTOMER4.index[1]);
          const HASH_RES_t h53 = TOTALACCTBAL_mCUSTOMER4_mapkey0_idxfn::hash(se66.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0::IdxNode* n53 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER4_map_0::IdxNode*>(i53->slice(se66, h53));
          TOTALACCTBAL_mCUSTOMER4_entry* e53;
         
          if (n53 && (e53 = n53->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e53->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e53->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v53 = e53->__av;
              (/*if */(c_acctbal > l113) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg57 * (v53 * -1L))) : (void)0);
              n53 = n53->nxt;
            } while (n53 && (e53 = n53->obj) && h53 == n53->hash &&  TOTALACCTBAL_mCUSTOMER4_mapkey0_idxfn::equals(se66, *e53)); 
          }
        }DOUBLE_TYPE agg62 = 0.0;
        long l116 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l116) ? agg62 += Udiv(Ulistmax(1L, l116)) : 0.0);
        DOUBLE_TYPE l115 = (agg62 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0* i54 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0*>(TOTALACCTBAL_mCUSTOMER5.index[1]);
          const HASH_RES_t h54 = TOTALACCTBAL_mCUSTOMER5_mapkey0_idxfn::hash(se67.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0::IdxNode* n54 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER5_map_0::IdxNode*>(i54->slice(se67, h54));
          TOTALACCTBAL_mCUSTOMER5_entry* e54;
         
          if (n54 && (e54 = n54->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e54->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e54->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v54 = e54->__av;
              (/*if */(c_acctbal > l115) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg57 * (v54 * -1L))) : (void)0);
              n54 = n54->nxt;
            } while (n54 && (e54 = n54->obj) && h54 == n54->hash &&  TOTALACCTBAL_mCUSTOMER5_mapkey0_idxfn::equals(se67, *e54)); 
          }
        }DOUBLE_TYPE agg63 = 0.0;
        long l118 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l118) ? agg63 += Udiv(Ulistmax(1L, l118)) : 0.0);
        DOUBLE_TYPE l117 = (agg63 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0* i55 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0*>(TOTALACCTBAL_mCUSTOMER6.index[1]);
          const HASH_RES_t h55 = TOTALACCTBAL_mCUSTOMER6_mapkey0_idxfn::hash(se68.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0::IdxNode* n55 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER6_map_0::IdxNode*>(i55->slice(se68, h55));
          TOTALACCTBAL_mCUSTOMER6_entry* e55;
         
          if (n55 && (e55 = n55->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e55->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e55->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v55 = e55->__av;
              (/*if */(c_acctbal > l117) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg57 * (v55 * -1L))) : (void)0);
              n55 = n55->nxt;
            } while (n55 && (e55 = n55->obj) && h55 == n55->hash &&  TOTALACCTBAL_mCUSTOMER6_mapkey0_idxfn::equals(se68, *e55)); 
          }
        }DOUBLE_TYPE agg64 = 0.0;
        long l120 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l120) ? agg64 += Udiv(Ulistmax(1L, l120)) : 0.0);
        DOUBLE_TYPE l119 = (agg64 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0* i56 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0*>(TOTALACCTBAL_mCUSTOMER7.index[1]);
          const HASH_RES_t h56 = TOTALACCTBAL_mCUSTOMER7_mapkey0_idxfn::hash(se69.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0::IdxNode* n56 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER7_map_0::IdxNode*>(i56->slice(se69, h56));
          TOTALACCTBAL_mCUSTOMER7_entry* e56;
         
          if (n56 && (e56 = n56->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e56->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e56->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v56 = e56->__av;
              (/*if */(c_acctbal > l119) ? TOTALACCTBAL.addOrDelOnZero(se53.modify(custsale_cntrycode),(agg57 * (v56 * -1L))) : (void)0);
              n56 = n56->nxt;
            } while (n56 && (e56 = n56->obj) && h56 == n56->hash &&  TOTALACCTBAL_mCUSTOMER7_mapkey0_idxfn::equals(se69, *e56)); 
          }
        }NUMCUST_mCUSTOMER1_L3_1.addOrDelOnZero(se70.modify(orders_custkey),-1L);
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        STRING_TYPE l121 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c1 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1.addOrDelOnZero(se71.modify(customer_custkey,customer_acctbal,l121),1L) : (void)0);
        (/*if */(customer_acctbal > 0.0 && c1 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_1 += 1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c2 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_2 += 1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c3 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_3 += 1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c4 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_4 += 1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c5 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_5 += 1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c6 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_6 += 1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c7 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_7 += 1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c1 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_2 += customer_acctbal : 0L);
        (/*if */(customer_acctbal > 0.0 && c2 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_4 += customer_acctbal : 0L);
        (/*if */(customer_acctbal > 0.0 && c3 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_6 += customer_acctbal : 0L);
        (/*if */(customer_acctbal > 0.0 && c4 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_8 += customer_acctbal : 0L);
        (/*if */(customer_acctbal > 0.0 && c5 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_10 += customer_acctbal : 0L);
        (/*if */(customer_acctbal > 0.0 && c6 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_12 += customer_acctbal : 0L);
        (/*if */(customer_acctbal > 0.0 && c7 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_14 += customer_acctbal : 0L);
        STRING_TYPE l122 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c2 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER2.addOrDelOnZero(se86.modify(customer_custkey,customer_acctbal,l122),1L) : (void)0);
        STRING_TYPE l123 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c3 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER3.addOrDelOnZero(se87.modify(customer_custkey,customer_acctbal,l123),1L) : (void)0);
        STRING_TYPE l124 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c4 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER4.addOrDelOnZero(se88.modify(customer_custkey,customer_acctbal,l124),1L) : (void)0);
        STRING_TYPE l125 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c5 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER5.addOrDelOnZero(se89.modify(customer_custkey,customer_acctbal,l125),1L) : (void)0);
        STRING_TYPE l126 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c6 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER6.addOrDelOnZero(se90.modify(customer_custkey,customer_acctbal,l126),1L) : (void)0);
        STRING_TYPE l127 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c7 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER7.addOrDelOnZero(se91.modify(customer_custkey,customer_acctbal,l127),1L) : (void)0);
        STRING_TYPE l128 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c1 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER1.addOrDelOnZero(se92.modify(customer_custkey,customer_acctbal,l128),customer_acctbal) : (void)0);
        STRING_TYPE l129 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c2 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER2.addOrDelOnZero(se93.modify(customer_custkey,customer_acctbal,l129),customer_acctbal) : (void)0);
        STRING_TYPE l130 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c3 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER3.addOrDelOnZero(se94.modify(customer_custkey,customer_acctbal,l130),customer_acctbal) : (void)0);
        STRING_TYPE l131 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c4 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER4.addOrDelOnZero(se95.modify(customer_custkey,customer_acctbal,l131),customer_acctbal) : (void)0);
        STRING_TYPE l132 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c5 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER5.addOrDelOnZero(se96.modify(customer_custkey,customer_acctbal,l132),customer_acctbal) : (void)0);
        STRING_TYPE l133 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c6 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER6.addOrDelOnZero(se97.modify(customer_custkey,customer_acctbal,l133),customer_acctbal) : (void)0);
        STRING_TYPE l134 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c7 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER7.addOrDelOnZero(se98.modify(customer_custkey,customer_acctbal,l134),customer_acctbal) : (void)0);
        NUMCUST.clear();
        DOUBLE_TYPE agg65 = 0.0;
        long l136 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l136) ? agg65 += Udiv(Ulistmax(1L, l136)) : 0.0);
        DOUBLE_TYPE l135 = (agg65 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l137 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER1_map_012* i57 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_012*>(NUMCUST_mCUSTOMER1.index[0]);
          HashIndex_NUMCUST_mCUSTOMER1_map_012::IdxNode* n57; 
          NUMCUST_mCUSTOMER1_entry* e57;
        
          for (size_t i = 0; i < i57->size_; i++)
          {
            n57 = i57->buckets_ + i;
            while (n57 && (e57 = n57->obj))
            {
                long c_custkey = e57->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e57->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e57->CUSTSALE_CNTRYCODE;
                long v57 = e57->__av;
                (/*if */(l137 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se100.modify(c_custkey)) && c_acctbal > l135) ? NUMCUST.addOrDelOnZero(se99.modify(custsale_cntrycode),v57) : (void)0);
              n57 = n57->nxt;
            }
          }
        }DOUBLE_TYPE agg66 = 0.0;
        long l139 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l139) ? agg66 += Udiv(Ulistmax(1L, l139)) : 0.0);
        DOUBLE_TYPE l138 = (agg66 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l140 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER2_map_012* i58 = static_cast<HashIndex_NUMCUST_mCUSTOMER2_map_012*>(NUMCUST_mCUSTOMER2.index[0]);
          HashIndex_NUMCUST_mCUSTOMER2_map_012::IdxNode* n58; 
          NUMCUST_mCUSTOMER2_entry* e58;
        
          for (size_t i = 0; i < i58->size_; i++)
          {
            n58 = i58->buckets_ + i;
            while (n58 && (e58 = n58->obj))
            {
                long c_custkey = e58->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e58->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e58->CUSTSALE_CNTRYCODE;
                long v58 = e58->__av;
                (/*if */(l140 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se101.modify(c_custkey)) && c_acctbal > l138) ? NUMCUST.addOrDelOnZero(se99.modify(custsale_cntrycode),v58) : (void)0);
              n58 = n58->nxt;
            }
          }
        }DOUBLE_TYPE agg67 = 0.0;
        long l142 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l142) ? agg67 += Udiv(Ulistmax(1L, l142)) : 0.0);
        DOUBLE_TYPE l141 = (agg67 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l143 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER3_map_012* i59 = static_cast<HashIndex_NUMCUST_mCUSTOMER3_map_012*>(NUMCUST_mCUSTOMER3.index[0]);
          HashIndex_NUMCUST_mCUSTOMER3_map_012::IdxNode* n59; 
          NUMCUST_mCUSTOMER3_entry* e59;
        
          for (size_t i = 0; i < i59->size_; i++)
          {
            n59 = i59->buckets_ + i;
            while (n59 && (e59 = n59->obj))
            {
                long c_custkey = e59->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e59->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e59->CUSTSALE_CNTRYCODE;
                long v59 = e59->__av;
                (/*if */(l143 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se102.modify(c_custkey)) && c_acctbal > l141) ? NUMCUST.addOrDelOnZero(se99.modify(custsale_cntrycode),v59) : (void)0);
              n59 = n59->nxt;
            }
          }
        }DOUBLE_TYPE agg68 = 0.0;
        long l145 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l145) ? agg68 += Udiv(Ulistmax(1L, l145)) : 0.0);
        DOUBLE_TYPE l144 = (agg68 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l146 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER4_map_012* i60 = static_cast<HashIndex_NUMCUST_mCUSTOMER4_map_012*>(NUMCUST_mCUSTOMER4.index[0]);
          HashIndex_NUMCUST_mCUSTOMER4_map_012::IdxNode* n60; 
          NUMCUST_mCUSTOMER4_entry* e60;
        
          for (size_t i = 0; i < i60->size_; i++)
          {
            n60 = i60->buckets_ + i;
            while (n60 && (e60 = n60->obj))
            {
                long c_custkey = e60->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e60->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e60->CUSTSALE_CNTRYCODE;
                long v60 = e60->__av;
                (/*if */(l146 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se103.modify(c_custkey)) && c_acctbal > l144) ? NUMCUST.addOrDelOnZero(se99.modify(custsale_cntrycode),v60) : (void)0);
              n60 = n60->nxt;
            }
          }
        }DOUBLE_TYPE agg69 = 0.0;
        long l148 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l148) ? agg69 += Udiv(Ulistmax(1L, l148)) : 0.0);
        DOUBLE_TYPE l147 = (agg69 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l149 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER5_map_012* i61 = static_cast<HashIndex_NUMCUST_mCUSTOMER5_map_012*>(NUMCUST_mCUSTOMER5.index[0]);
          HashIndex_NUMCUST_mCUSTOMER5_map_012::IdxNode* n61; 
          NUMCUST_mCUSTOMER5_entry* e61;
        
          for (size_t i = 0; i < i61->size_; i++)
          {
            n61 = i61->buckets_ + i;
            while (n61 && (e61 = n61->obj))
            {
                long c_custkey = e61->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e61->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e61->CUSTSALE_CNTRYCODE;
                long v61 = e61->__av;
                (/*if */(l149 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se104.modify(c_custkey)) && c_acctbal > l147) ? NUMCUST.addOrDelOnZero(se99.modify(custsale_cntrycode),v61) : (void)0);
              n61 = n61->nxt;
            }
          }
        }DOUBLE_TYPE agg70 = 0.0;
        long l151 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l151) ? agg70 += Udiv(Ulistmax(1L, l151)) : 0.0);
        DOUBLE_TYPE l150 = (agg70 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l152 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER6_map_012* i62 = static_cast<HashIndex_NUMCUST_mCUSTOMER6_map_012*>(NUMCUST_mCUSTOMER6.index[0]);
          HashIndex_NUMCUST_mCUSTOMER6_map_012::IdxNode* n62; 
          NUMCUST_mCUSTOMER6_entry* e62;
        
          for (size_t i = 0; i < i62->size_; i++)
          {
            n62 = i62->buckets_ + i;
            while (n62 && (e62 = n62->obj))
            {
                long c_custkey = e62->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e62->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e62->CUSTSALE_CNTRYCODE;
                long v62 = e62->__av;
                (/*if */(l152 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se105.modify(c_custkey)) && c_acctbal > l150) ? NUMCUST.addOrDelOnZero(se99.modify(custsale_cntrycode),v62) : (void)0);
              n62 = n62->nxt;
            }
          }
        }DOUBLE_TYPE agg71 = 0.0;
        long l154 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l154) ? agg71 += Udiv(Ulistmax(1L, l154)) : 0.0);
        DOUBLE_TYPE l153 = (agg71 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l155 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER7_map_012* i63 = static_cast<HashIndex_NUMCUST_mCUSTOMER7_map_012*>(NUMCUST_mCUSTOMER7.index[0]);
          HashIndex_NUMCUST_mCUSTOMER7_map_012::IdxNode* n63; 
          NUMCUST_mCUSTOMER7_entry* e63;
        
          for (size_t i = 0; i < i63->size_; i++)
          {
            n63 = i63->buckets_ + i;
            while (n63 && (e63 = n63->obj))
            {
                long c_custkey = e63->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e63->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e63->CUSTSALE_CNTRYCODE;
                long v63 = e63->__av;
                (/*if */(l155 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se106.modify(c_custkey)) && c_acctbal > l153) ? NUMCUST.addOrDelOnZero(se99.modify(custsale_cntrycode),v63) : (void)0);
              n63 = n63->nxt;
            }
          }
        }TOTALACCTBAL.clear();
        DOUBLE_TYPE agg72 = 0.0;
        long l157 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l157) ? agg72 += Udiv(Ulistmax(1L, l157)) : 0.0);
        DOUBLE_TYPE l156 = (agg72 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l158 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012* i64 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012*>(TOTALACCTBAL_mCUSTOMER1.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012::IdxNode* n64; 
          TOTALACCTBAL_mCUSTOMER1_entry* e64;
        
          for (size_t i = 0; i < i64->size_; i++)
          {
            n64 = i64->buckets_ + i;
            while (n64 && (e64 = n64->obj))
            {
                long c_custkey = e64->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e64->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e64->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v64 = e64->__av;
                (/*if */(l158 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se108.modify(c_custkey)) && c_acctbal > l156) ? TOTALACCTBAL.addOrDelOnZero(se107.modify(custsale_cntrycode),v64) : (void)0);
              n64 = n64->nxt;
            }
          }
        }DOUBLE_TYPE agg73 = 0.0;
        long l160 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l160) ? agg73 += Udiv(Ulistmax(1L, l160)) : 0.0);
        DOUBLE_TYPE l159 = (agg73 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l161 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER2_map_012* i65 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER2_map_012*>(TOTALACCTBAL_mCUSTOMER2.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER2_map_012::IdxNode* n65; 
          TOTALACCTBAL_mCUSTOMER2_entry* e65;
        
          for (size_t i = 0; i < i65->size_; i++)
          {
            n65 = i65->buckets_ + i;
            while (n65 && (e65 = n65->obj))
            {
                long c_custkey = e65->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e65->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e65->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v65 = e65->__av;
                (/*if */(l161 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se109.modify(c_custkey)) && c_acctbal > l159) ? TOTALACCTBAL.addOrDelOnZero(se107.modify(custsale_cntrycode),v65) : (void)0);
              n65 = n65->nxt;
            }
          }
        }DOUBLE_TYPE agg74 = 0.0;
        long l163 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l163) ? agg74 += Udiv(Ulistmax(1L, l163)) : 0.0);
        DOUBLE_TYPE l162 = (agg74 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l164 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER3_map_012* i66 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER3_map_012*>(TOTALACCTBAL_mCUSTOMER3.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER3_map_012::IdxNode* n66; 
          TOTALACCTBAL_mCUSTOMER3_entry* e66;
        
          for (size_t i = 0; i < i66->size_; i++)
          {
            n66 = i66->buckets_ + i;
            while (n66 && (e66 = n66->obj))
            {
                long c_custkey = e66->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e66->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e66->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v66 = e66->__av;
                (/*if */(l164 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se110.modify(c_custkey)) && c_acctbal > l162) ? TOTALACCTBAL.addOrDelOnZero(se107.modify(custsale_cntrycode),v66) : (void)0);
              n66 = n66->nxt;
            }
          }
        }DOUBLE_TYPE agg75 = 0.0;
        long l166 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l166) ? agg75 += Udiv(Ulistmax(1L, l166)) : 0.0);
        DOUBLE_TYPE l165 = (agg75 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l167 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER4_map_012* i67 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER4_map_012*>(TOTALACCTBAL_mCUSTOMER4.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER4_map_012::IdxNode* n67; 
          TOTALACCTBAL_mCUSTOMER4_entry* e67;
        
          for (size_t i = 0; i < i67->size_; i++)
          {
            n67 = i67->buckets_ + i;
            while (n67 && (e67 = n67->obj))
            {
                long c_custkey = e67->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e67->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e67->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v67 = e67->__av;
                (/*if */(l167 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se111.modify(c_custkey)) && c_acctbal > l165) ? TOTALACCTBAL.addOrDelOnZero(se107.modify(custsale_cntrycode),v67) : (void)0);
              n67 = n67->nxt;
            }
          }
        }DOUBLE_TYPE agg76 = 0.0;
        long l169 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l169) ? agg76 += Udiv(Ulistmax(1L, l169)) : 0.0);
        DOUBLE_TYPE l168 = (agg76 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l170 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER5_map_012* i68 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER5_map_012*>(TOTALACCTBAL_mCUSTOMER5.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER5_map_012::IdxNode* n68; 
          TOTALACCTBAL_mCUSTOMER5_entry* e68;
        
          for (size_t i = 0; i < i68->size_; i++)
          {
            n68 = i68->buckets_ + i;
            while (n68 && (e68 = n68->obj))
            {
                long c_custkey = e68->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e68->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e68->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v68 = e68->__av;
                (/*if */(l170 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se112.modify(c_custkey)) && c_acctbal > l168) ? TOTALACCTBAL.addOrDelOnZero(se107.modify(custsale_cntrycode),v68) : (void)0);
              n68 = n68->nxt;
            }
          }
        }DOUBLE_TYPE agg77 = 0.0;
        long l172 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l172) ? agg77 += Udiv(Ulistmax(1L, l172)) : 0.0);
        DOUBLE_TYPE l171 = (agg77 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l173 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER6_map_012* i69 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER6_map_012*>(TOTALACCTBAL_mCUSTOMER6.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER6_map_012::IdxNode* n69; 
          TOTALACCTBAL_mCUSTOMER6_entry* e69;
        
          for (size_t i = 0; i < i69->size_; i++)
          {
            n69 = i69->buckets_ + i;
            while (n69 && (e69 = n69->obj))
            {
                long c_custkey = e69->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e69->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e69->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v69 = e69->__av;
                (/*if */(l173 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se113.modify(c_custkey)) && c_acctbal > l171) ? TOTALACCTBAL.addOrDelOnZero(se107.modify(custsale_cntrycode),v69) : (void)0);
              n69 = n69->nxt;
            }
          }
        }DOUBLE_TYPE agg78 = 0.0;
        long l175 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l175) ? agg78 += Udiv(Ulistmax(1L, l175)) : 0.0);
        DOUBLE_TYPE l174 = (agg78 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l176 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER7_map_012* i70 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER7_map_012*>(TOTALACCTBAL_mCUSTOMER7.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER7_map_012::IdxNode* n70; 
          TOTALACCTBAL_mCUSTOMER7_entry* e70;
        
          for (size_t i = 0; i < i70->size_; i++)
          {
            n70 = i70->buckets_ + i;
            while (n70 && (e70 = n70->obj))
            {
                long c_custkey = e70->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e70->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e70->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v70 = e70->__av;
                (/*if */(l176 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se114.modify(c_custkey)) && c_acctbal > l174) ? TOTALACCTBAL.addOrDelOnZero(se107.modify(custsale_cntrycode),v70) : (void)0);
              n70 = n70->nxt;
            }
          }
        }
      }
    }
    void on_delete_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        STRING_TYPE l177 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c1 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1.addOrDelOnZero(se115.modify(customer_custkey,customer_acctbal,l177),-1L) : (void)0);
        (/*if */(customer_acctbal > 0.0 && c1 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_1 += -1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c2 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_2 += -1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c3 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_3 += -1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c4 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_4 += -1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c5 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_5 += -1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c6 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_6 += -1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c7 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_1_L1_7 += -1L : 0L);
        (/*if */(customer_acctbal > 0.0 && c1 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_2 += (-1L * customer_acctbal) : 0L);
        (/*if */(customer_acctbal > 0.0 && c2 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_4 += (-1L * customer_acctbal) : 0L);
        (/*if */(customer_acctbal > 0.0 && c3 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_6 += (-1L * customer_acctbal) : 0L);
        (/*if */(customer_acctbal > 0.0 && c4 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_8 += (-1L * customer_acctbal) : 0L);
        (/*if */(customer_acctbal > 0.0 && c5 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_10 += (-1L * customer_acctbal) : 0L);
        (/*if */(customer_acctbal > 0.0 && c6 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_12 += (-1L * customer_acctbal) : 0L);
        (/*if */(customer_acctbal > 0.0 && c7 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER1_L2_14 += (-1L * customer_acctbal) : 0L);
        STRING_TYPE l178 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c2 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER2.addOrDelOnZero(se130.modify(customer_custkey,customer_acctbal,l178),-1L) : (void)0);
        STRING_TYPE l179 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c3 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER3.addOrDelOnZero(se131.modify(customer_custkey,customer_acctbal,l179),-1L) : (void)0);
        STRING_TYPE l180 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c4 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER4.addOrDelOnZero(se132.modify(customer_custkey,customer_acctbal,l180),-1L) : (void)0);
        STRING_TYPE l181 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c5 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER5.addOrDelOnZero(se133.modify(customer_custkey,customer_acctbal,l181),-1L) : (void)0);
        STRING_TYPE l182 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c6 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER6.addOrDelOnZero(se134.modify(customer_custkey,customer_acctbal,l182),-1L) : (void)0);
        STRING_TYPE l183 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c7 == Usubstring(customer_phone, 0L, 2L)) ? NUMCUST_mCUSTOMER7.addOrDelOnZero(se135.modify(customer_custkey,customer_acctbal,l183),-1L) : (void)0);
        STRING_TYPE l184 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c1 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER1.addOrDelOnZero(se136.modify(customer_custkey,customer_acctbal,l184),(-1L * customer_acctbal)) : (void)0);
        STRING_TYPE l185 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c2 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER2.addOrDelOnZero(se137.modify(customer_custkey,customer_acctbal,l185),(-1L * customer_acctbal)) : (void)0);
        STRING_TYPE l186 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c3 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER3.addOrDelOnZero(se138.modify(customer_custkey,customer_acctbal,l186),(-1L * customer_acctbal)) : (void)0);
        STRING_TYPE l187 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c4 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER4.addOrDelOnZero(se139.modify(customer_custkey,customer_acctbal,l187),(-1L * customer_acctbal)) : (void)0);
        STRING_TYPE l188 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c5 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER5.addOrDelOnZero(se140.modify(customer_custkey,customer_acctbal,l188),(-1L * customer_acctbal)) : (void)0);
        STRING_TYPE l189 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c6 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER6.addOrDelOnZero(se141.modify(customer_custkey,customer_acctbal,l189),(-1L * customer_acctbal)) : (void)0);
        STRING_TYPE l190 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(c7 == Usubstring(customer_phone, 0L, 2L)) ? TOTALACCTBAL_mCUSTOMER7.addOrDelOnZero(se142.modify(customer_custkey,customer_acctbal,l190),(-1L * customer_acctbal)) : (void)0);
        NUMCUST.clear();
        DOUBLE_TYPE agg79 = 0.0;
        long l192 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l192) ? agg79 += Udiv(Ulistmax(1L, l192)) : 0.0);
        DOUBLE_TYPE l191 = (agg79 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l193 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER1_map_012* i71 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_012*>(NUMCUST_mCUSTOMER1.index[0]);
          HashIndex_NUMCUST_mCUSTOMER1_map_012::IdxNode* n71; 
          NUMCUST_mCUSTOMER1_entry* e71;
        
          for (size_t i = 0; i < i71->size_; i++)
          {
            n71 = i71->buckets_ + i;
            while (n71 && (e71 = n71->obj))
            {
                long c_custkey = e71->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e71->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e71->CUSTSALE_CNTRYCODE;
                long v71 = e71->__av;
                (/*if */(l193 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se144.modify(c_custkey)) && c_acctbal > l191) ? NUMCUST.addOrDelOnZero(se143.modify(custsale_cntrycode),v71) : (void)0);
              n71 = n71->nxt;
            }
          }
        }DOUBLE_TYPE agg80 = 0.0;
        long l195 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l195) ? agg80 += Udiv(Ulistmax(1L, l195)) : 0.0);
        DOUBLE_TYPE l194 = (agg80 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l196 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER2_map_012* i72 = static_cast<HashIndex_NUMCUST_mCUSTOMER2_map_012*>(NUMCUST_mCUSTOMER2.index[0]);
          HashIndex_NUMCUST_mCUSTOMER2_map_012::IdxNode* n72; 
          NUMCUST_mCUSTOMER2_entry* e72;
        
          for (size_t i = 0; i < i72->size_; i++)
          {
            n72 = i72->buckets_ + i;
            while (n72 && (e72 = n72->obj))
            {
                long c_custkey = e72->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e72->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e72->CUSTSALE_CNTRYCODE;
                long v72 = e72->__av;
                (/*if */(l196 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se145.modify(c_custkey)) && c_acctbal > l194) ? NUMCUST.addOrDelOnZero(se143.modify(custsale_cntrycode),v72) : (void)0);
              n72 = n72->nxt;
            }
          }
        }DOUBLE_TYPE agg81 = 0.0;
        long l198 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l198) ? agg81 += Udiv(Ulistmax(1L, l198)) : 0.0);
        DOUBLE_TYPE l197 = (agg81 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l199 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER3_map_012* i73 = static_cast<HashIndex_NUMCUST_mCUSTOMER3_map_012*>(NUMCUST_mCUSTOMER3.index[0]);
          HashIndex_NUMCUST_mCUSTOMER3_map_012::IdxNode* n73; 
          NUMCUST_mCUSTOMER3_entry* e73;
        
          for (size_t i = 0; i < i73->size_; i++)
          {
            n73 = i73->buckets_ + i;
            while (n73 && (e73 = n73->obj))
            {
                long c_custkey = e73->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e73->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e73->CUSTSALE_CNTRYCODE;
                long v73 = e73->__av;
                (/*if */(l199 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se146.modify(c_custkey)) && c_acctbal > l197) ? NUMCUST.addOrDelOnZero(se143.modify(custsale_cntrycode),v73) : (void)0);
              n73 = n73->nxt;
            }
          }
        }DOUBLE_TYPE agg82 = 0.0;
        long l201 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l201) ? agg82 += Udiv(Ulistmax(1L, l201)) : 0.0);
        DOUBLE_TYPE l200 = (agg82 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l202 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER4_map_012* i74 = static_cast<HashIndex_NUMCUST_mCUSTOMER4_map_012*>(NUMCUST_mCUSTOMER4.index[0]);
          HashIndex_NUMCUST_mCUSTOMER4_map_012::IdxNode* n74; 
          NUMCUST_mCUSTOMER4_entry* e74;
        
          for (size_t i = 0; i < i74->size_; i++)
          {
            n74 = i74->buckets_ + i;
            while (n74 && (e74 = n74->obj))
            {
                long c_custkey = e74->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e74->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e74->CUSTSALE_CNTRYCODE;
                long v74 = e74->__av;
                (/*if */(l202 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se147.modify(c_custkey)) && c_acctbal > l200) ? NUMCUST.addOrDelOnZero(se143.modify(custsale_cntrycode),v74) : (void)0);
              n74 = n74->nxt;
            }
          }
        }DOUBLE_TYPE agg83 = 0.0;
        long l204 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l204) ? agg83 += Udiv(Ulistmax(1L, l204)) : 0.0);
        DOUBLE_TYPE l203 = (agg83 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l205 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER5_map_012* i75 = static_cast<HashIndex_NUMCUST_mCUSTOMER5_map_012*>(NUMCUST_mCUSTOMER5.index[0]);
          HashIndex_NUMCUST_mCUSTOMER5_map_012::IdxNode* n75; 
          NUMCUST_mCUSTOMER5_entry* e75;
        
          for (size_t i = 0; i < i75->size_; i++)
          {
            n75 = i75->buckets_ + i;
            while (n75 && (e75 = n75->obj))
            {
                long c_custkey = e75->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e75->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e75->CUSTSALE_CNTRYCODE;
                long v75 = e75->__av;
                (/*if */(l205 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se148.modify(c_custkey)) && c_acctbal > l203) ? NUMCUST.addOrDelOnZero(se143.modify(custsale_cntrycode),v75) : (void)0);
              n75 = n75->nxt;
            }
          }
        }DOUBLE_TYPE agg84 = 0.0;
        long l207 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l207) ? agg84 += Udiv(Ulistmax(1L, l207)) : 0.0);
        DOUBLE_TYPE l206 = (agg84 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l208 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER6_map_012* i76 = static_cast<HashIndex_NUMCUST_mCUSTOMER6_map_012*>(NUMCUST_mCUSTOMER6.index[0]);
          HashIndex_NUMCUST_mCUSTOMER6_map_012::IdxNode* n76; 
          NUMCUST_mCUSTOMER6_entry* e76;
        
          for (size_t i = 0; i < i76->size_; i++)
          {
            n76 = i76->buckets_ + i;
            while (n76 && (e76 = n76->obj))
            {
                long c_custkey = e76->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e76->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e76->CUSTSALE_CNTRYCODE;
                long v76 = e76->__av;
                (/*if */(l208 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se149.modify(c_custkey)) && c_acctbal > l206) ? NUMCUST.addOrDelOnZero(se143.modify(custsale_cntrycode),v76) : (void)0);
              n76 = n76->nxt;
            }
          }
        }DOUBLE_TYPE agg85 = 0.0;
        long l210 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l210) ? agg85 += Udiv(Ulistmax(1L, l210)) : 0.0);
        DOUBLE_TYPE l209 = (agg85 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l211 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER7_map_012* i77 = static_cast<HashIndex_NUMCUST_mCUSTOMER7_map_012*>(NUMCUST_mCUSTOMER7.index[0]);
          HashIndex_NUMCUST_mCUSTOMER7_map_012::IdxNode* n77; 
          NUMCUST_mCUSTOMER7_entry* e77;
        
          for (size_t i = 0; i < i77->size_; i++)
          {
            n77 = i77->buckets_ + i;
            while (n77 && (e77 = n77->obj))
            {
                long c_custkey = e77->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e77->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e77->CUSTSALE_CNTRYCODE;
                long v77 = e77->__av;
                (/*if */(l211 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se150.modify(c_custkey)) && c_acctbal > l209) ? NUMCUST.addOrDelOnZero(se143.modify(custsale_cntrycode),v77) : (void)0);
              n77 = n77->nxt;
            }
          }
        }TOTALACCTBAL.clear();
        DOUBLE_TYPE agg86 = 0.0;
        long l213 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l213) ? agg86 += Udiv(Ulistmax(1L, l213)) : 0.0);
        DOUBLE_TYPE l212 = (agg86 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l214 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012* i78 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012*>(TOTALACCTBAL_mCUSTOMER1.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012::IdxNode* n78; 
          TOTALACCTBAL_mCUSTOMER1_entry* e78;
        
          for (size_t i = 0; i < i78->size_; i++)
          {
            n78 = i78->buckets_ + i;
            while (n78 && (e78 = n78->obj))
            {
                long c_custkey = e78->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e78->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e78->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v78 = e78->__av;
                (/*if */(l214 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se152.modify(c_custkey)) && c_acctbal > l212) ? TOTALACCTBAL.addOrDelOnZero(se151.modify(custsale_cntrycode),v78) : (void)0);
              n78 = n78->nxt;
            }
          }
        }DOUBLE_TYPE agg87 = 0.0;
        long l216 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l216) ? agg87 += Udiv(Ulistmax(1L, l216)) : 0.0);
        DOUBLE_TYPE l215 = (agg87 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l217 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER2_map_012* i79 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER2_map_012*>(TOTALACCTBAL_mCUSTOMER2.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER2_map_012::IdxNode* n79; 
          TOTALACCTBAL_mCUSTOMER2_entry* e79;
        
          for (size_t i = 0; i < i79->size_; i++)
          {
            n79 = i79->buckets_ + i;
            while (n79 && (e79 = n79->obj))
            {
                long c_custkey = e79->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e79->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e79->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v79 = e79->__av;
                (/*if */(l217 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se153.modify(c_custkey)) && c_acctbal > l215) ? TOTALACCTBAL.addOrDelOnZero(se151.modify(custsale_cntrycode),v79) : (void)0);
              n79 = n79->nxt;
            }
          }
        }DOUBLE_TYPE agg88 = 0.0;
        long l219 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l219) ? agg88 += Udiv(Ulistmax(1L, l219)) : 0.0);
        DOUBLE_TYPE l218 = (agg88 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l220 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER3_map_012* i80 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER3_map_012*>(TOTALACCTBAL_mCUSTOMER3.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER3_map_012::IdxNode* n80; 
          TOTALACCTBAL_mCUSTOMER3_entry* e80;
        
          for (size_t i = 0; i < i80->size_; i++)
          {
            n80 = i80->buckets_ + i;
            while (n80 && (e80 = n80->obj))
            {
                long c_custkey = e80->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e80->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e80->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v80 = e80->__av;
                (/*if */(l220 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se154.modify(c_custkey)) && c_acctbal > l218) ? TOTALACCTBAL.addOrDelOnZero(se151.modify(custsale_cntrycode),v80) : (void)0);
              n80 = n80->nxt;
            }
          }
        }DOUBLE_TYPE agg89 = 0.0;
        long l222 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l222) ? agg89 += Udiv(Ulistmax(1L, l222)) : 0.0);
        DOUBLE_TYPE l221 = (agg89 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l223 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER4_map_012* i81 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER4_map_012*>(TOTALACCTBAL_mCUSTOMER4.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER4_map_012::IdxNode* n81; 
          TOTALACCTBAL_mCUSTOMER4_entry* e81;
        
          for (size_t i = 0; i < i81->size_; i++)
          {
            n81 = i81->buckets_ + i;
            while (n81 && (e81 = n81->obj))
            {
                long c_custkey = e81->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e81->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e81->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v81 = e81->__av;
                (/*if */(l223 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se155.modify(c_custkey)) && c_acctbal > l221) ? TOTALACCTBAL.addOrDelOnZero(se151.modify(custsale_cntrycode),v81) : (void)0);
              n81 = n81->nxt;
            }
          }
        }DOUBLE_TYPE agg90 = 0.0;
        long l225 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l225) ? agg90 += Udiv(Ulistmax(1L, l225)) : 0.0);
        DOUBLE_TYPE l224 = (agg90 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l226 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER5_map_012* i82 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER5_map_012*>(TOTALACCTBAL_mCUSTOMER5.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER5_map_012::IdxNode* n82; 
          TOTALACCTBAL_mCUSTOMER5_entry* e82;
        
          for (size_t i = 0; i < i82->size_; i++)
          {
            n82 = i82->buckets_ + i;
            while (n82 && (e82 = n82->obj))
            {
                long c_custkey = e82->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e82->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e82->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v82 = e82->__av;
                (/*if */(l226 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se156.modify(c_custkey)) && c_acctbal > l224) ? TOTALACCTBAL.addOrDelOnZero(se151.modify(custsale_cntrycode),v82) : (void)0);
              n82 = n82->nxt;
            }
          }
        }DOUBLE_TYPE agg91 = 0.0;
        long l228 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l228) ? agg91 += Udiv(Ulistmax(1L, l228)) : 0.0);
        DOUBLE_TYPE l227 = (agg91 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l229 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER6_map_012* i83 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER6_map_012*>(TOTALACCTBAL_mCUSTOMER6.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER6_map_012::IdxNode* n83; 
          TOTALACCTBAL_mCUSTOMER6_entry* e83;
        
          for (size_t i = 0; i < i83->size_; i++)
          {
            n83 = i83->buckets_ + i;
            while (n83 && (e83 = n83->obj))
            {
                long c_custkey = e83->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e83->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e83->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v83 = e83->__av;
                (/*if */(l229 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se157.modify(c_custkey)) && c_acctbal > l227) ? TOTALACCTBAL.addOrDelOnZero(se151.modify(custsale_cntrycode),v83) : (void)0);
              n83 = n83->nxt;
            }
          }
        }DOUBLE_TYPE agg92 = 0.0;
        long l231 = (NUMCUST_mCUSTOMER1_L2_1_L1_1 + (NUMCUST_mCUSTOMER1_L2_1_L1_2 + (NUMCUST_mCUSTOMER1_L2_1_L1_3 + (NUMCUST_mCUSTOMER1_L2_1_L1_4 + (NUMCUST_mCUSTOMER1_L2_1_L1_5 + (NUMCUST_mCUSTOMER1_L2_1_L1_6 + NUMCUST_mCUSTOMER1_L2_1_L1_7))))));
        (/*if */(0L != l231) ? agg92 += Udiv(Ulistmax(1L, l231)) : 0.0);
        DOUBLE_TYPE l230 = (agg92 * (NUMCUST_mCUSTOMER1_L2_2 + (NUMCUST_mCUSTOMER1_L2_4 + (NUMCUST_mCUSTOMER1_L2_6 + (NUMCUST_mCUSTOMER1_L2_8 + (NUMCUST_mCUSTOMER1_L2_10 + (NUMCUST_mCUSTOMER1_L2_12 + NUMCUST_mCUSTOMER1_L2_14)))))));
        long l232 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER7_map_012* i84 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER7_map_012*>(TOTALACCTBAL_mCUSTOMER7.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER7_map_012::IdxNode* n84; 
          TOTALACCTBAL_mCUSTOMER7_entry* e84;
        
          for (size_t i = 0; i < i84->size_; i++)
          {
            n84 = i84->buckets_ + i;
            while (n84 && (e84 = n84->obj))
            {
                long c_custkey = e84->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e84->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e84->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v84 = e84->__av;
                (/*if */(l232 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se158.modify(c_custkey)) && c_acctbal > l230) ? TOTALACCTBAL.addOrDelOnZero(se151.modify(custsale_cntrycode),v84) : (void)0);
              n84 = n84->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        NUMCUST_mCUSTOMER1_L2_2 = 0.0;
        NUMCUST_mCUSTOMER1_L2_4 = 0.0;
        NUMCUST_mCUSTOMER1_L2_6 = 0.0;
        NUMCUST_mCUSTOMER1_L2_8 = 0.0;
        NUMCUST_mCUSTOMER1_L2_10 = 0.0;
        NUMCUST_mCUSTOMER1_L2_12 = 0.0;
        NUMCUST_mCUSTOMER1_L2_14 = 0.0;
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    NUMCUST_entry se1;
    NUMCUST_mCUSTOMER1_L3_1_entry se2;
    NUMCUST_mCUSTOMER1_entry se3;
    NUMCUST_mCUSTOMER2_entry se4;
    NUMCUST_mCUSTOMER3_entry se5;
    NUMCUST_mCUSTOMER4_entry se6;
    NUMCUST_mCUSTOMER5_entry se7;
    NUMCUST_mCUSTOMER6_entry se8;
    NUMCUST_mCUSTOMER7_entry se9;
    NUMCUST_mCUSTOMER1_L3_1_entry se10;
    NUMCUST_mCUSTOMER1_entry se11;
    NUMCUST_mCUSTOMER2_entry se12;
    NUMCUST_mCUSTOMER3_entry se13;
    NUMCUST_mCUSTOMER4_entry se14;
    NUMCUST_mCUSTOMER5_entry se15;
    NUMCUST_mCUSTOMER6_entry se16;
    NUMCUST_mCUSTOMER7_entry se17;
    TOTALACCTBAL_entry se18;
    NUMCUST_mCUSTOMER1_L3_1_entry se19;
    TOTALACCTBAL_mCUSTOMER1_entry se20;
    TOTALACCTBAL_mCUSTOMER2_entry se21;
    TOTALACCTBAL_mCUSTOMER3_entry se22;
    TOTALACCTBAL_mCUSTOMER4_entry se23;
    TOTALACCTBAL_mCUSTOMER5_entry se24;
    TOTALACCTBAL_mCUSTOMER6_entry se25;
    TOTALACCTBAL_mCUSTOMER7_entry se26;
    NUMCUST_mCUSTOMER1_L3_1_entry se27;
    TOTALACCTBAL_mCUSTOMER1_entry se28;
    TOTALACCTBAL_mCUSTOMER2_entry se29;
    TOTALACCTBAL_mCUSTOMER3_entry se30;
    TOTALACCTBAL_mCUSTOMER4_entry se31;
    TOTALACCTBAL_mCUSTOMER5_entry se32;
    TOTALACCTBAL_mCUSTOMER6_entry se33;
    TOTALACCTBAL_mCUSTOMER7_entry se34;
    NUMCUST_mCUSTOMER1_L3_1_entry se35;
    NUMCUST_entry se36;
    NUMCUST_mCUSTOMER1_L3_1_entry se37;
    NUMCUST_mCUSTOMER1_entry se38;
    NUMCUST_mCUSTOMER2_entry se39;
    NUMCUST_mCUSTOMER3_entry se40;
    NUMCUST_mCUSTOMER4_entry se41;
    NUMCUST_mCUSTOMER5_entry se42;
    NUMCUST_mCUSTOMER6_entry se43;
    NUMCUST_mCUSTOMER7_entry se44;
    NUMCUST_mCUSTOMER1_L3_1_entry se45;
    NUMCUST_mCUSTOMER1_entry se46;
    NUMCUST_mCUSTOMER2_entry se47;
    NUMCUST_mCUSTOMER3_entry se48;
    NUMCUST_mCUSTOMER4_entry se49;
    NUMCUST_mCUSTOMER5_entry se50;
    NUMCUST_mCUSTOMER6_entry se51;
    NUMCUST_mCUSTOMER7_entry se52;
    TOTALACCTBAL_entry se53;
    NUMCUST_mCUSTOMER1_L3_1_entry se54;
    TOTALACCTBAL_mCUSTOMER1_entry se55;
    TOTALACCTBAL_mCUSTOMER2_entry se56;
    TOTALACCTBAL_mCUSTOMER3_entry se57;
    TOTALACCTBAL_mCUSTOMER4_entry se58;
    TOTALACCTBAL_mCUSTOMER5_entry se59;
    TOTALACCTBAL_mCUSTOMER6_entry se60;
    TOTALACCTBAL_mCUSTOMER7_entry se61;
    NUMCUST_mCUSTOMER1_L3_1_entry se62;
    TOTALACCTBAL_mCUSTOMER1_entry se63;
    TOTALACCTBAL_mCUSTOMER2_entry se64;
    TOTALACCTBAL_mCUSTOMER3_entry se65;
    TOTALACCTBAL_mCUSTOMER4_entry se66;
    TOTALACCTBAL_mCUSTOMER5_entry se67;
    TOTALACCTBAL_mCUSTOMER6_entry se68;
    TOTALACCTBAL_mCUSTOMER7_entry se69;
    NUMCUST_mCUSTOMER1_L3_1_entry se70;
    NUMCUST_mCUSTOMER1_entry se71;
    NUMCUST_mCUSTOMER2_entry se86;
    NUMCUST_mCUSTOMER3_entry se87;
    NUMCUST_mCUSTOMER4_entry se88;
    NUMCUST_mCUSTOMER5_entry se89;
    NUMCUST_mCUSTOMER6_entry se90;
    NUMCUST_mCUSTOMER7_entry se91;
    TOTALACCTBAL_mCUSTOMER1_entry se92;
    TOTALACCTBAL_mCUSTOMER2_entry se93;
    TOTALACCTBAL_mCUSTOMER3_entry se94;
    TOTALACCTBAL_mCUSTOMER4_entry se95;
    TOTALACCTBAL_mCUSTOMER5_entry se96;
    TOTALACCTBAL_mCUSTOMER6_entry se97;
    TOTALACCTBAL_mCUSTOMER7_entry se98;
    NUMCUST_entry se99;
    NUMCUST_mCUSTOMER1_L3_1_entry se100;
    NUMCUST_mCUSTOMER1_L3_1_entry se101;
    NUMCUST_mCUSTOMER1_L3_1_entry se102;
    NUMCUST_mCUSTOMER1_L3_1_entry se103;
    NUMCUST_mCUSTOMER1_L3_1_entry se104;
    NUMCUST_mCUSTOMER1_L3_1_entry se105;
    NUMCUST_mCUSTOMER1_L3_1_entry se106;
    TOTALACCTBAL_entry se107;
    NUMCUST_mCUSTOMER1_L3_1_entry se108;
    NUMCUST_mCUSTOMER1_L3_1_entry se109;
    NUMCUST_mCUSTOMER1_L3_1_entry se110;
    NUMCUST_mCUSTOMER1_L3_1_entry se111;
    NUMCUST_mCUSTOMER1_L3_1_entry se112;
    NUMCUST_mCUSTOMER1_L3_1_entry se113;
    NUMCUST_mCUSTOMER1_L3_1_entry se114;
    NUMCUST_mCUSTOMER1_entry se115;
    NUMCUST_mCUSTOMER2_entry se130;
    NUMCUST_mCUSTOMER3_entry se131;
    NUMCUST_mCUSTOMER4_entry se132;
    NUMCUST_mCUSTOMER5_entry se133;
    NUMCUST_mCUSTOMER6_entry se134;
    NUMCUST_mCUSTOMER7_entry se135;
    TOTALACCTBAL_mCUSTOMER1_entry se136;
    TOTALACCTBAL_mCUSTOMER2_entry se137;
    TOTALACCTBAL_mCUSTOMER3_entry se138;
    TOTALACCTBAL_mCUSTOMER4_entry se139;
    TOTALACCTBAL_mCUSTOMER5_entry se140;
    TOTALACCTBAL_mCUSTOMER6_entry se141;
    TOTALACCTBAL_mCUSTOMER7_entry se142;
    NUMCUST_entry se143;
    NUMCUST_mCUSTOMER1_L3_1_entry se144;
    NUMCUST_mCUSTOMER1_L3_1_entry se145;
    NUMCUST_mCUSTOMER1_L3_1_entry se146;
    NUMCUST_mCUSTOMER1_L3_1_entry se147;
    NUMCUST_mCUSTOMER1_L3_1_entry se148;
    NUMCUST_mCUSTOMER1_L3_1_entry se149;
    NUMCUST_mCUSTOMER1_L3_1_entry se150;
    TOTALACCTBAL_entry se151;
    NUMCUST_mCUSTOMER1_L3_1_entry se152;
    NUMCUST_mCUSTOMER1_L3_1_entry se153;
    NUMCUST_mCUSTOMER1_L3_1_entry se154;
    NUMCUST_mCUSTOMER1_L3_1_entry se155;
    NUMCUST_mCUSTOMER1_L3_1_entry se156;
    NUMCUST_mCUSTOMER1_L3_1_entry se157;
    NUMCUST_mCUSTOMER1_L3_1_entry se158;
  
    /* Data structures used for storing materialized views */
    NUMCUST_mCUSTOMER1_map NUMCUST_mCUSTOMER1;
    long NUMCUST_mCUSTOMER1_L2_1_L1_1;
    long NUMCUST_mCUSTOMER1_L2_1_L1_2;
    long NUMCUST_mCUSTOMER1_L2_1_L1_3;
    long NUMCUST_mCUSTOMER1_L2_1_L1_4;
    long NUMCUST_mCUSTOMER1_L2_1_L1_5;
    long NUMCUST_mCUSTOMER1_L2_1_L1_6;
    long NUMCUST_mCUSTOMER1_L2_1_L1_7;
    DOUBLE_TYPE NUMCUST_mCUSTOMER1_L2_2;
    DOUBLE_TYPE NUMCUST_mCUSTOMER1_L2_4;
    DOUBLE_TYPE NUMCUST_mCUSTOMER1_L2_6;
    DOUBLE_TYPE NUMCUST_mCUSTOMER1_L2_8;
    DOUBLE_TYPE NUMCUST_mCUSTOMER1_L2_10;
    DOUBLE_TYPE NUMCUST_mCUSTOMER1_L2_12;
    DOUBLE_TYPE NUMCUST_mCUSTOMER1_L2_14;
    NUMCUST_mCUSTOMER1_L3_1_map NUMCUST_mCUSTOMER1_L3_1;
    NUMCUST_mCUSTOMER2_map NUMCUST_mCUSTOMER2;
    NUMCUST_mCUSTOMER3_map NUMCUST_mCUSTOMER3;
    NUMCUST_mCUSTOMER4_map NUMCUST_mCUSTOMER4;
    NUMCUST_mCUSTOMER5_map NUMCUST_mCUSTOMER5;
    NUMCUST_mCUSTOMER6_map NUMCUST_mCUSTOMER6;
    NUMCUST_mCUSTOMER7_map NUMCUST_mCUSTOMER7;
    TOTALACCTBAL_mCUSTOMER1_map TOTALACCTBAL_mCUSTOMER1;
    TOTALACCTBAL_mCUSTOMER2_map TOTALACCTBAL_mCUSTOMER2;
    TOTALACCTBAL_mCUSTOMER3_map TOTALACCTBAL_mCUSTOMER3;
    TOTALACCTBAL_mCUSTOMER4_map TOTALACCTBAL_mCUSTOMER4;
    TOTALACCTBAL_mCUSTOMER5_map TOTALACCTBAL_mCUSTOMER5;
    TOTALACCTBAL_mCUSTOMER6_map TOTALACCTBAL_mCUSTOMER6;
    TOTALACCTBAL_mCUSTOMER7_map TOTALACCTBAL_mCUSTOMER7;
    
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c5;
  
  };

}
