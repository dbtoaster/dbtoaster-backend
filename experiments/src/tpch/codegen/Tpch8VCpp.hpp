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
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_4_entry {
    long MKT_SHARE_mORDERSORDERS_CUSTKEY; long __av; 
    explicit MKT_SHARE_mORDERS1_L2_1_L1_4_entry() { /*MKT_SHARE_mORDERSORDERS_CUSTKEY = 0L; __av = 0L; */ }
    explicit MKT_SHARE_mORDERS1_L2_1_L1_4_entry(const long c0, const long c1) { MKT_SHARE_mORDERSORDERS_CUSTKEY = c0; __av = c1; }
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry(const MKT_SHARE_mORDERS1_L2_1_L1_4_entry& other) : MKT_SHARE_mORDERSORDERS_CUSTKEY( other.MKT_SHARE_mORDERSORDERS_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_4_entry& modify(const long c0) { MKT_SHARE_mORDERSORDERS_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERSORDERS_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS1_L2_1_L1_4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_4_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_4_entry& y) {
      return x.MKT_SHARE_mORDERSORDERS_CUSTKEY == y.MKT_SHARE_mORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS1_L2_1_L1_4_entry,long,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_4_entry,long,MKT_SHARE_mORDERS1_L2_1_L1_4_mapkey0_idxfn,true>
  > MKT_SHARE_mORDERS1_L2_1_L1_4_map;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_4_entry,long,MKT_SHARE_mORDERS1_L2_1_L1_4_mapkey0_idxfn,true> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_4_map_0;
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry {
    long MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMERCUSTOMER_NATIONKEY; long __av; 
    explicit MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry() { /*MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMERCUSTOMER_NATIONKEY = 0L; __av = 0L; */ }
    explicit MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry(const long c0, const long c1) { MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMERCUSTOMER_NATIONKEY = c0; __av = c1; }
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry(const MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry& other) : MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMERCUSTOMER_NATIONKEY( other.MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMERCUSTOMER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry& modify(const long c0) { MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMERCUSTOMER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMERCUSTOMER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMERCUSTOMER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry& y) {
      return x.MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMERCUSTOMER_NATIONKEY == y.MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMERCUSTOMER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry,long,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry,long,MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_mapkey0_idxfn,true>
  > MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_map;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry,long,MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_mapkey0_idxfn,true> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_map_0;
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_entry {
    long MKT_SHARE_mORDERSORDERS_ORDERKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_entry() { /*MKT_SHARE_mORDERSORDERS_ORDERKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_entry(const long c0, const DOUBLE_TYPE c1) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0; __av = c1; }
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry(const MKT_SHARE_mORDERS1_L2_1_L1_5_entry& other) : MKT_SHARE_mORDERSORDERS_ORDERKEY( other.MKT_SHARE_mORDERSORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_entry& modify(const long c0) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_entry& y) {
      return x.MKT_SHARE_mORDERSORDERS_ORDERKEY == y.MKT_SHARE_mORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS1_L2_1_L1_5_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mapkey0_idxfn,true>
  > MKT_SHARE_mORDERS1_L2_1_L1_5_map;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mapkey0_idxfn,true> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_map_0;
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry {
    long MKT_SHARE_mORDERSORDERS_ORDERKEY; long MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry() { /*MKT_SHARE_mORDERSORDERS_ORDERKEY = 0L; MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0; MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY = c1; __av = c2; }
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& other) : MKT_SHARE_mORDERSORDERS_ORDERKEY( other.MKT_SHARE_mORDERSORDERS_ORDERKEY ), MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& modify(const long c0, const long c1) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0; MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& modify0(const long c0) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& modify1(const long c1) { MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERSORDERS_ORDERKEY);
      hash_combine(h, e.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& y) {
      return x.MKT_SHARE_mORDERSORDERS_ORDERKEY == y.MKT_SHARE_mORDERSORDERS_ORDERKEY && x.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& y) {
      return x.MKT_SHARE_mORDERSORDERS_ORDERKEY == y.MKT_SHARE_mORDERSORDERS_ORDERKEY;
    }
  };
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry& y) {
      return x.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn,false>,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey1_idxfn,false>
  > MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey01_idxfn,true> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_01;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1;
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry {
    long MKT_SHARE_mORDERSORDERS_ORDERKEY; long MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY; long MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry() { /*MKT_SHARE_mORDERSORDERS_ORDERKEY = 0L; MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY = 0L; MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0; MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY = c1; MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY = c2; __av = c3; }
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& other) : MKT_SHARE_mORDERSORDERS_ORDERKEY( other.MKT_SHARE_mORDERSORDERS_ORDERKEY ), MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY( other.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY ), MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& modify(const long c0, const long c1, const long c2) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0; MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY = c1; MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY = c2;  return *this; }
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& modify0(const long c0) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& modify1(const long c1) { MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& modify2(const long c2) { MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERSORDERS_ORDERKEY);
      hash_combine(h, e.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& y) {
      return x.MKT_SHARE_mORDERSORDERS_ORDERKEY == y.MKT_SHARE_mORDERSORDERS_ORDERKEY && x.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY == y.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY && x.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& y) {
      return x.MKT_SHARE_mORDERSORDERS_ORDERKEY == y.MKT_SHARE_mORDERSORDERS_ORDERKEY;
    }
  };
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& y) {
      return x.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY == y.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry& y) {
      return x.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey1_idxfn,false>,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey2_idxfn,false>
  > MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey012_idxfn,true> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_012;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_1;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey2_idxfn,false> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2;
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry {
    long MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_NATIONKEY; long __av; 
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry() { /*MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_NATIONKEY = 0L; __av = 0L; */ }
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry(const long c0, const long c1) { MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_NATIONKEY = c0; __av = c1; }
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry& other) : MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_NATIONKEY( other.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry& modify(const long c0) { MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry& y) {
      return x.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_NATIONKEY == y.MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry,long,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry,long,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_mapkey0_idxfn,true>
  > MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_map;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry,long,MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_mapkey0_idxfn,true> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_map_0;
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry {
    long MKT_SHARE_mORDERSORDERS_ORDERKEY; long MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry() { /*MKT_SHARE_mORDERSORDERS_ORDERKEY = 0L; MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0; MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY = c1; __av = c2; }
    MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry(const MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& other) : MKT_SHARE_mORDERSORDERS_ORDERKEY( other.MKT_SHARE_mORDERSORDERS_ORDERKEY ), MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY( other.MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& modify(const long c0, const long c1) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0; MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& modify0(const long c0) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& modify1(const long c1) { MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERSORDERS_ORDERKEY);
      hash_combine(h, e.MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& y) {
      return x.MKT_SHARE_mORDERSORDERS_ORDERKEY == y.MKT_SHARE_mORDERSORDERS_ORDERKEY && x.MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY == y.MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& y) {
      return x.MKT_SHARE_mORDERSORDERS_ORDERKEY == y.MKT_SHARE_mORDERSORDERS_ORDERKEY;
    }
  };
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry& y) {
      return x.MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY == y.MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey1_idxfn,false>
  > MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey01_idxfn,true> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_01;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_1;
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry {
    long MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_PARTKEY; long __av; 
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry() { /*MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_PARTKEY = 0L; __av = 0L; */ }
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry(const long c0, const long c1) { MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_PARTKEY = c0; __av = c1; }
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry(const MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry& other) : MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_PARTKEY( other.MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry& modify(const long c0) { MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry& y) {
      return x.MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_PARTKEY == y.MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry,long,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry,long,MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_mapkey0_idxfn,true>
  > MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_map;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry,long,MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_mapkey0_idxfn,true> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_map_0;
  
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry {
    long MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_SUPPKEY; long __av; 
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry() { /*MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_SUPPKEY = 0L; __av = 0L; */ }
    explicit MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry(const long c0, const long c1) { MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_SUPPKEY = c0; __av = c1; }
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry(const MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry& other) : MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_SUPPKEY( other.MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry& modify(const long c0) { MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry& x, const MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry& y) {
      return x.MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_SUPPKEY == y.MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEMLINEITEM_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry,long,
    HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry,long,MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_mapkey0_idxfn,true>
  > MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_map;
  typedef HashIndex<MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry,long,MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_mapkey0_idxfn,true> HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_map_0;
  
  struct MKT_SHARE_mORDERS6_entry {
    long MKT_SHARE_mORDERSORDERS_ORDERKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mORDERS6_entry() { /*MKT_SHARE_mORDERSORDERS_ORDERKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mORDERS6_entry(const long c0, const DOUBLE_TYPE c1) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0; __av = c1; }
    MKT_SHARE_mORDERS6_entry(const MKT_SHARE_mORDERS6_entry& other) : MKT_SHARE_mORDERSORDERS_ORDERKEY( other.MKT_SHARE_mORDERSORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS6_entry& modify(const long c0) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS6_entry& x, const MKT_SHARE_mORDERS6_entry& y) {
      return x.MKT_SHARE_mORDERSORDERS_ORDERKEY == y.MKT_SHARE_mORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS6_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mORDERS6_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS6_mapkey0_idxfn,true>
  > MKT_SHARE_mORDERS6_map;
  typedef HashIndex<MKT_SHARE_mORDERS6_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS6_mapkey0_idxfn,true> HashIndex_MKT_SHARE_mORDERS6_map_0;
  
  struct MKT_SHARE_mORDERS6_mSUPPLIER1_entry {
    long MKT_SHARE_mORDERS6_mSUPPLIERSUPPLIER_NATIONKEY; long __av; 
    explicit MKT_SHARE_mORDERS6_mSUPPLIER1_entry() { /*MKT_SHARE_mORDERS6_mSUPPLIERSUPPLIER_NATIONKEY = 0L; __av = 0L; */ }
    explicit MKT_SHARE_mORDERS6_mSUPPLIER1_entry(const long c0, const long c1) { MKT_SHARE_mORDERS6_mSUPPLIERSUPPLIER_NATIONKEY = c0; __av = c1; }
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry(const MKT_SHARE_mORDERS6_mSUPPLIER1_entry& other) : MKT_SHARE_mORDERS6_mSUPPLIERSUPPLIER_NATIONKEY( other.MKT_SHARE_mORDERS6_mSUPPLIERSUPPLIER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS6_mSUPPLIER1_entry& modify(const long c0) { MKT_SHARE_mORDERS6_mSUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERS6_mSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS6_mSUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS6_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERS6_mSUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS6_mSUPPLIER1_entry& x, const MKT_SHARE_mORDERS6_mSUPPLIER1_entry& y) {
      return x.MKT_SHARE_mORDERS6_mSUPPLIERSUPPLIER_NATIONKEY == y.MKT_SHARE_mORDERS6_mSUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS6_mSUPPLIER1_entry,long,
    HashIndex<MKT_SHARE_mORDERS6_mSUPPLIER1_entry,long,MKT_SHARE_mORDERS6_mSUPPLIER1_mapkey0_idxfn,true>
  > MKT_SHARE_mORDERS6_mSUPPLIER1_map;
  typedef HashIndex<MKT_SHARE_mORDERS6_mSUPPLIER1_entry,long,MKT_SHARE_mORDERS6_mSUPPLIER1_mapkey0_idxfn,true> HashIndex_MKT_SHARE_mORDERS6_mSUPPLIER1_map_0;
  
  struct MKT_SHARE_mORDERS6_mPART2_entry {
    long MKT_SHARE_mORDERSORDERS_ORDERKEY; long MKT_SHARE_mORDERS6_mPARTPART_PARTKEY; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mORDERS6_mPART2_entry() { /*MKT_SHARE_mORDERSORDERS_ORDERKEY = 0L; MKT_SHARE_mORDERS6_mPARTPART_PARTKEY = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mORDERS6_mPART2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0; MKT_SHARE_mORDERS6_mPARTPART_PARTKEY = c1; __av = c2; }
    MKT_SHARE_mORDERS6_mPART2_entry(const MKT_SHARE_mORDERS6_mPART2_entry& other) : MKT_SHARE_mORDERSORDERS_ORDERKEY( other.MKT_SHARE_mORDERSORDERS_ORDERKEY ), MKT_SHARE_mORDERS6_mPARTPART_PARTKEY( other.MKT_SHARE_mORDERS6_mPARTPART_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS6_mPART2_entry& modify(const long c0, const long c1) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0; MKT_SHARE_mORDERS6_mPARTPART_PARTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mORDERS6_mPART2_entry& modify0(const long c0) { MKT_SHARE_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHARE_mORDERS6_mPART2_entry& modify1(const long c1) { MKT_SHARE_mORDERS6_mPARTPART_PARTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERS6_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS6_mPART2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS6_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERSORDERS_ORDERKEY);
      hash_combine(h, e.MKT_SHARE_mORDERS6_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS6_mPART2_entry& x, const MKT_SHARE_mORDERS6_mPART2_entry& y) {
      return x.MKT_SHARE_mORDERSORDERS_ORDERKEY == y.MKT_SHARE_mORDERSORDERS_ORDERKEY && x.MKT_SHARE_mORDERS6_mPARTPART_PARTKEY == y.MKT_SHARE_mORDERS6_mPARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHARE_mORDERS6_mPART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS6_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS6_mPART2_entry& x, const MKT_SHARE_mORDERS6_mPART2_entry& y) {
      return x.MKT_SHARE_mORDERSORDERS_ORDERKEY == y.MKT_SHARE_mORDERSORDERS_ORDERKEY;
    }
  };
  
  struct MKT_SHARE_mORDERS6_mPART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS6_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERS6_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS6_mPART2_entry& x, const MKT_SHARE_mORDERS6_mPART2_entry& y) {
      return x.MKT_SHARE_mORDERS6_mPARTPART_PARTKEY == y.MKT_SHARE_mORDERS6_mPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS6_mPART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mORDERS6_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS6_mPART2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHARE_mORDERS6_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS6_mPART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHARE_mORDERS6_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS6_mPART2_mapkey1_idxfn,false>
  > MKT_SHARE_mORDERS6_mPART2_map;
  typedef HashIndex<MKT_SHARE_mORDERS6_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS6_mPART2_mapkey01_idxfn,true> HashIndex_MKT_SHARE_mORDERS6_mPART2_map_01;
  typedef HashIndex<MKT_SHARE_mORDERS6_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS6_mPART2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0;
  typedef HashIndex<MKT_SHARE_mORDERS6_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mORDERS6_mPART2_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mORDERS6_mPART2_map_1;
  
  struct MKT_SHARE_mORDERS6_mLINEITEM1_entry {
    long MKT_SHARE_mORDERS6_mLINEITEMLINEITEM_SUPPKEY; long __av; 
    explicit MKT_SHARE_mORDERS6_mLINEITEM1_entry() { /*MKT_SHARE_mORDERS6_mLINEITEMLINEITEM_SUPPKEY = 0L; __av = 0L; */ }
    explicit MKT_SHARE_mORDERS6_mLINEITEM1_entry(const long c0, const long c1) { MKT_SHARE_mORDERS6_mLINEITEMLINEITEM_SUPPKEY = c0; __av = c1; }
    MKT_SHARE_mORDERS6_mLINEITEM1_entry(const MKT_SHARE_mORDERS6_mLINEITEM1_entry& other) : MKT_SHARE_mORDERS6_mLINEITEMLINEITEM_SUPPKEY( other.MKT_SHARE_mORDERS6_mLINEITEMLINEITEM_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mORDERS6_mLINEITEM1_entry& modify(const long c0) { MKT_SHARE_mORDERS6_mLINEITEMLINEITEM_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mORDERS6_mLINEITEMLINEITEM_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mORDERS6_mLINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mORDERS6_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mORDERS6_mLINEITEMLINEITEM_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mORDERS6_mLINEITEM1_entry& x, const MKT_SHARE_mORDERS6_mLINEITEM1_entry& y) {
      return x.MKT_SHARE_mORDERS6_mLINEITEMLINEITEM_SUPPKEY == y.MKT_SHARE_mORDERS6_mLINEITEMLINEITEM_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mORDERS6_mLINEITEM1_entry,long,
    HashIndex<MKT_SHARE_mORDERS6_mLINEITEM1_entry,long,MKT_SHARE_mORDERS6_mLINEITEM1_mapkey0_idxfn,true>
  > MKT_SHARE_mORDERS6_mLINEITEM1_map;
  typedef HashIndex<MKT_SHARE_mORDERS6_mLINEITEM1_entry,long,MKT_SHARE_mORDERS6_mLINEITEM1_mapkey0_idxfn,true> HashIndex_MKT_SHARE_mORDERS6_mLINEITEM1_map_0;
  
  struct MKT_SHARE_mPART1_entry {
    date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_entry() { /*O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_entry(const date c0, const DOUBLE_TYPE c1) { O_ORDERDATE = c0; __av = c1; }
    MKT_SHARE_mPART1_entry(const MKT_SHARE_mPART1_entry& other) : O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_entry& modify(const date c0) { O_ORDERDATE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_entry& x, const MKT_SHARE_mPART1_entry& y) {
      return x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mapkey0_idxfn,true>
  > MKT_SHARE_mPART1_map;
  typedef HashIndex<MKT_SHARE_mPART1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mapkey0_idxfn,true> HashIndex_MKT_SHARE_mPART1_map_0;
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_entry {
    long MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_mCUSTOMER1_entry() { /*MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_mCUSTOMER1_entry(const long c0, const date c1, const DOUBLE_TYPE c2) { MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c0; O_ORDERDATE = c1; __av = c2; }
    MKT_SHARE_mPART1_mCUSTOMER1_entry(const MKT_SHARE_mPART1_mCUSTOMER1_entry& other) : MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_entry& modify(const long c0, const date c1) { MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c0; O_ORDERDATE = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_entry& modify0(const long c0) { MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_mCUSTOMER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_mCUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mapkey0_idxfn,false>
  > MKT_SHARE_mPART1_mCUSTOMER1_map;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mapkey01_idxfn,true> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_map_01;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_map_0;
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry {
    long MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY; long MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY; date O_ORDERDATE; long __av; 
    explicit MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry() { /*MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = 0L; MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry(const long c0, const long c1, const date c2, const long c3) { MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = c0; MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry(const MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& other) : MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY( other.MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY ), MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& modify(const long c0, const long c1, const date c2) { MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = c0; MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c1; O_ORDERDATE = c2;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& modify0(const long c0) { MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& modify1(const long c1) { MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY == y.MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY && x.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY == y.MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry,long,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey012_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn,false>,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn,false>
  > MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey012_idxfn,true> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_012;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_1;
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry {
    long MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY; long MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry() { /*MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry(const long c0, const long c1, const date c2, const DOUBLE_TYPE c3) { MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c0; MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& other) : MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY ), MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& modify(const long c0, const long c1, const date c2) { MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c0; MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c1; O_ORDERDATE = c2;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& modify1(const long c1) { MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& modify0(const long c0) { MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY && x.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn,false>,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn,false>
  > MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey012_idxfn,true> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_012;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_1;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_0;
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry {
    long MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY; long MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY; long MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry() { /*MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY = 0L; MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry(const long c0, const long c1, const long c2, const date c3, const DOUBLE_TYPE c4) { MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY = c0; MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c1; MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c2; O_ORDERDATE = c3; __av = c4; }
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& other) : MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY( other.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY ), MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY ), MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& modify(const long c0, const long c1, const long c2, const date c3) { MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY = c0; MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c1; MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c2; O_ORDERDATE = c3;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& modify0(const long c0) { MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& modify2(const long c2) { MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c2;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& modify1(const long c1) { MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY && x.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY && x.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey0123_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey2_idxfn,false>,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey1_idxfn,false>
  > MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey0123_idxfn,true> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_0123;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_0;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey2_idxfn,false> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_2;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_1;
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry {
    long MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY; long MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry() { /*MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY = 0L; MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry(const long c0, const long c1, const date c2, const DOUBLE_TYPE c3) { MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY = c0; MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry(const MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& other) : MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY( other.MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY ), MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& modify(const long c0, const long c1, const date c2) { MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY = c0; MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c1; O_ORDERDATE = c2;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& modify0(const long c0) { MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& modify1(const long c1) { MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY && x.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& x, const MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey1_idxfn,false>
  > MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey012_idxfn,true> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_012;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_0;
  typedef HashIndex<MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_1;
  
  struct MKT_SHARE_mPART1_mLINEITEM3_entry {
    long MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY; date O_ORDERDATE; long __av; 
    explicit MKT_SHARE_mPART1_mLINEITEM3_entry() { /*MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY = 0L; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit MKT_SHARE_mPART1_mLINEITEM3_entry(const long c0, const date c1, const long c2) { MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY = c0; O_ORDERDATE = c1; __av = c2; }
    MKT_SHARE_mPART1_mLINEITEM3_entry(const MKT_SHARE_mPART1_mLINEITEM3_entry& other) : MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY( other.MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_mLINEITEM3_entry& modify(const long c0, const date c1) { MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY = c0; O_ORDERDATE = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mLINEITEM3_entry& modify0(const long c0) { MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_mLINEITEM3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mLINEITEM3_entry& x, const MKT_SHARE_mPART1_mLINEITEM3_entry& y) {
      return x.MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY == y.MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mLINEITEM3_entry& x, const MKT_SHARE_mPART1_mLINEITEM3_entry& y) {
      return x.MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY == y.MKT_SHARE_mPART1_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_mLINEITEM3_entry,long,
    HashIndex<MKT_SHARE_mPART1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_mLINEITEM3_mapkey01_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn,false>
  > MKT_SHARE_mPART1_mLINEITEM3_map;
  typedef HashIndex<MKT_SHARE_mPART1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_mLINEITEM3_mapkey01_idxfn,true> HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_01;
  typedef HashIndex<MKT_SHARE_mPART1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0;
  
  struct MKT_SHARE_mPART1_mSUPPLIER2_entry {
    long MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_mSUPPLIER2_entry() { /*MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_mSUPPLIER2_entry(const long c0, const date c1, const DOUBLE_TYPE c2) { MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY = c0; O_ORDERDATE = c1; __av = c2; }
    MKT_SHARE_mPART1_mSUPPLIER2_entry(const MKT_SHARE_mPART1_mSUPPLIER2_entry& other) : MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_mSUPPLIER2_entry& modify(const long c0, const date c1) { MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY = c0; O_ORDERDATE = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mSUPPLIER2_entry& modify0(const long c0) { MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_mSUPPLIER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mSUPPLIER2_entry& x, const MKT_SHARE_mPART1_mSUPPLIER2_entry& y) {
      return x.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHARE_mPART1_mSUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mSUPPLIER2_entry& x, const MKT_SHARE_mPART1_mSUPPLIER2_entry& y) {
      return x.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_mSUPPLIER2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_mSUPPLIER2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mSUPPLIER2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_mSUPPLIER2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mSUPPLIER2_mapkey0_idxfn,false>
  > MKT_SHARE_mPART1_mSUPPLIER2_map;
  typedef HashIndex<MKT_SHARE_mPART1_mSUPPLIER2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mSUPPLIER2_mapkey01_idxfn,true> HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_map_01;
  typedef HashIndex<MKT_SHARE_mPART1_mSUPPLIER2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mSUPPLIER2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_map_0;
  
  struct MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry {
    long MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY; long MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry() { /*MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY = 0L; MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry(const long c0, const long c1, const date c2, const DOUBLE_TYPE c3) { MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY = c0; MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY = c1; O_ORDERDATE = c2; __av = c3; }
    MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry(const MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& other) : MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY( other.MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY ), MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& modify(const long c0, const long c1, const date c2) { MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY = c0; MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY = c1; O_ORDERDATE = c2;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& modify0(const long c0) { MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& modify1(const long c1) { MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& x, const MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY && x.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& x, const MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& x, const MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey1_idxfn,false>
  > MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map;
  typedef HashIndex<MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey012_idxfn,true> HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_012;
  typedef HashIndex<MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_0;
  typedef HashIndex<MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_1;
  
  struct MKT_SHARE_mPART1_mPART2_entry {
    long MKT_SHARE_mPART1_mPARTPART_PARTKEY; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_mPART2_entry() { /*MKT_SHARE_mPART1_mPARTPART_PARTKEY = 0L; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_mPART2_entry(const long c0, const date c1, const DOUBLE_TYPE c2) { MKT_SHARE_mPART1_mPARTPART_PARTKEY = c0; O_ORDERDATE = c1; __av = c2; }
    MKT_SHARE_mPART1_mPART2_entry(const MKT_SHARE_mPART1_mPART2_entry& other) : MKT_SHARE_mPART1_mPARTPART_PARTKEY( other.MKT_SHARE_mPART1_mPARTPART_PARTKEY ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_mPART2_entry& modify(const long c0, const date c1) { MKT_SHARE_mPART1_mPARTPART_PARTKEY = c0; O_ORDERDATE = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_mPART2_entry& modify0(const long c0) { MKT_SHARE_mPART1_mPARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_mPART2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mPARTPART_PARTKEY);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mPART2_entry& x, const MKT_SHARE_mPART1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_mPARTPART_PARTKEY && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct MKT_SHARE_mPART1_mPART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_mPART2_entry& x, const MKT_SHARE_mPART1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_mPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_mPART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mPART2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mPART2_mapkey0_idxfn,false>
  > MKT_SHARE_mPART1_mPART2_map;
  typedef HashIndex<MKT_SHARE_mPART1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mPART2_mapkey01_idxfn,true> HashIndex_MKT_SHARE_mPART1_mPART2_map_01;
  typedef HashIndex<MKT_SHARE_mPART1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_mPART2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_mPART2_map_0;
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_entry {
    long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_L2_1_L1_1_entry() { /*TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_L2_1_L1_1_entry(const long c0, const DOUBLE_TYPE c1) { TOTAL_O_YEAR = c0; __av = c1; }
    MKT_SHARE_mPART1_L2_1_L1_1_entry(const MKT_SHARE_mPART1_L2_1_L1_1_entry& other) : TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_entry& modify(const long c0) { TOTAL_O_YEAR = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_L2_1_L1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_entry& y) {
      return x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_L2_1_L1_1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mapkey0_idxfn,true>
  > MKT_SHARE_mPART1_L2_1_L1_1_map;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mapkey0_idxfn,true> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_map_0;
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry {
    long MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry() { /*MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry& other) : MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry& modify(const long c0, const long c1) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry& modify0(const long c0) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mapkey0_idxfn,false>
  > MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_map;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mapkey01_idxfn,true> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_map_01;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_map_0;
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry {
    long MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY; long MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY; long TOTAL_O_YEAR; long __av; 
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry() { /*MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = 0L; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0L; */ }
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry(const long c0, const long c1, const long c2, const long c3) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = c0; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& other) : MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY ), MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& modify(const long c0, const long c1, const long c2) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = c0; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& modify0(const long c0) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& modify1(const long c1) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY && x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry,long,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey012_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn,false>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn,false>
  > MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey012_idxfn,true> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_012;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry,long,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_1;
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry {
    long MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY; long MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry() { /*MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c0; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& other) : MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY ), MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& modify(const long c0, const long c1, const long c2) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c0; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& modify1(const long c1) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& modify0(const long c0) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY && x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey012_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey1_idxfn,false>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey0_idxfn,false>
  > MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey012_idxfn,true> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_012;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_1;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_0;
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry {
    long MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY; long MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY; long MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry() { /*MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY = 0L; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY = c0; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c1; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c2; TOTAL_O_YEAR = c3; __av = c4; }
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& other) : MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY ), MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY ), MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& modify(const long c0, const long c1, const long c2, const long c3) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY = c0; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c1; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c2; TOTAL_O_YEAR = c3;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& modify0(const long c0) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& modify2(const long c2) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c2;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& modify1(const long c1) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY && x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY && x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey0123_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey2_idxfn,false>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey1_idxfn,false>
  > MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey0123_idxfn,true> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_0123;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_0;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey2_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_2;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_1;
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry {
    long MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY; long MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry() { /*MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY = 0L; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY = c0; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& other) : MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY ), MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& modify(const long c0, const long c1, const long c2) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY = c0; MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& modify0(const long c0) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& modify1(const long c1) { MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY && x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey1_idxfn,false>
  > MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey012_idxfn,true> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_012;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_0;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_1;
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry {
    long MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY; long TOTAL_O_YEAR; long __av; 
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry() { /*MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0L; */ }
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry(const long c0, const long c1, const long c2) { MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry(const MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry& other) : MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry& modify(const long c0, const long c1) { MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry& modify0(const long c0) { MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry,long,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry,long,MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry,long,MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn,false>
  > MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry,long,MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey01_idxfn,true> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_01;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry,long,MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0;
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry {
    long MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry() { /*MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry(const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry& other) : MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry& modify(const long c0, const long c1) { MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry& modify0(const long c0) { MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mapkey01_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mapkey0_idxfn,false>
  > MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_map;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mapkey01_idxfn,true> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_map_01;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_map_0;
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry {
    long MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY; long MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry() { /*MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY = 0L; MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY = c0; MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY = c1; TOTAL_O_YEAR = c2; __av = c3; }
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry(const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& other) : MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY ), MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& modify(const long c0, const long c1, const long c2) { MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY = c0; MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY = c1; TOTAL_O_YEAR = c2;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& modify0(const long c0) { MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY = c0;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& modify1(const long c1) { MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY);
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY && x.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey012_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey0_idxfn,false>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey1_idxfn,false>
  > MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey012_idxfn,true> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_012;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_0;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey1_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_1;
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry {
    long MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY; long TOTAL_O_YEAR; DOUBLE_TYPE __av; 
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry() { /*MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY = 0L; TOTAL_O_YEAR = 0L; __av = 0.0; */ }
    explicit MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY = c0; TOTAL_O_YEAR = c1; __av = c2; }
    MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry(const MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry& other) : MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY( other.MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY ), TOTAL_O_YEAR( other.TOTAL_O_YEAR ), __av( other.__av ) {}
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry& modify(const long c0, const long c1) { MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY = c0; TOTAL_O_YEAR = c1;  return *this; }
    FORCE_INLINE MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry& modify0(const long c0) { MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TOTAL_O_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MKT_SHARE_mPART1_L2_1_L1_1_mPART2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY);
      hash_combine(h, e.TOTAL_O_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY && x.TOTAL_O_YEAR == y.TOTAL_O_YEAR;
    }
  };
  
  struct MKT_SHARE_mPART1_L2_1_L1_1_mPART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry& x, const MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry& y) {
      return x.MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY == y.MKT_SHARE_mPART1_L2_1_L1_1_mPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry,DOUBLE_TYPE,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mPART2_mapkey01_idxfn,true>,
    HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mPART2_mapkey0_idxfn,false>
  > MKT_SHARE_mPART1_L2_1_L1_1_mPART2_map;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mPART2_mapkey01_idxfn,true> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mPART2_map_01;
  typedef HashIndex<MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry,DOUBLE_TYPE,MKT_SHARE_mPART1_L2_1_L1_1_mPART2_mapkey0_idxfn,false> HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mPART2_map_0;
  
  
  
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
      {  //++tN;
        MKT_SHARE_mORDERS1_L2_1_L1_5.addOrDelOnZero(se1.modify(lineitem_orderkey),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se2.modify(lineitem_partkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.getValueOrDefault(se3.modify(lineitem_suppkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
        MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.addOrDelOnZero(se4.modify(lineitem_orderkey,lineitem_suppkey),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se5.modify(lineitem_partkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
        MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.addOrDelOnZero(se6.modify(lineitem_orderkey,lineitem_partkey,lineitem_suppkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount))));
        MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.addOrDelOnZero(se7.modify(lineitem_orderkey,lineitem_partkey),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.getValueOrDefault(se8.modify(lineitem_suppkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
        MKT_SHARE_mORDERS6.addOrDelOnZero(se9.modify(lineitem_orderkey),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se10.modify(lineitem_partkey)) * (MKT_SHARE_mORDERS6_mLINEITEM1.getValueOrDefault(se11.modify(lineitem_suppkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
        MKT_SHARE_mORDERS6_mPART2.addOrDelOnZero(se12.modify(lineitem_orderkey,lineitem_partkey),(MKT_SHARE_mORDERS6_mLINEITEM1.getValueOrDefault(se13.modify(lineitem_suppkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
        { //slice 
          const HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0* i1 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mLINEITEM3.index[1]);
          const HASH_RES_t h1 = MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::hash(se17.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode* n1 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode*>(i1->slice(se17, h1));
          MKT_SHARE_mPART1_mLINEITEM3_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              date o_orderdate = e1->O_ORDERDATE;
              long v1 = e1->__av;
              MKT_SHARE_mPART1.addOrDelOnZero(se14.modify(o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se15.modify(lineitem_partkey)) * (MKT_SHARE_mORDERS6_mLINEITEM1.getValueOrDefault(se16.modify(lineitem_suppkey)) * (v1 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::equals(se17, *e1)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0* i2 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h2 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se21.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n2 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i2->slice(se21, h2));
          MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long mkt_share_mpart1_mcustomercustomer_custkey = e2->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e2->O_ORDERDATE;
              long v2 = e2->__av;
              MKT_SHARE_mPART1_mCUSTOMER1.addOrDelOnZero(se18.modify(mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se19.modify(lineitem_partkey)) * (MKT_SHARE_mORDERS6_mLINEITEM1.getValueOrDefault(se20.modify(lineitem_suppkey)) * (v2 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se21, *e2)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0* i3 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h3 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se24.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n3 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i3->slice(se24, h3));
          MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              long mkt_share_mpart1_mcustomercustomer_custkey = e3->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e3->O_ORDERDATE;
              long v3 = e3->__av;
              MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.addOrDelOnZero(se22.modify(lineitem_suppkey,mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se23.modify(lineitem_partkey)) * (v3 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se24, *e3)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0* i4 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h4 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se26.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n4 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i4->slice(se26, h4));
          MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long mkt_share_mpart1_mcustomercustomer_custkey = e4->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e4->O_ORDERDATE;
              long v4 = e4->__av;
              MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.addOrDelOnZero(se25.modify(lineitem_partkey,lineitem_suppkey,mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(v4 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se26, *e4)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0* i5 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h5 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se29.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n5 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i5->slice(se29, h5));
          MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long mkt_share_mpart1_mcustomercustomer_custkey = e5->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e5->O_ORDERDATE;
              long v5 = e5->__av;
              MKT_SHARE_mPART1_mCUSTOMER1_mPART2.addOrDelOnZero(se27.modify(lineitem_partkey,mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(MKT_SHARE_mORDERS6_mLINEITEM1.getValueOrDefault(se28.modify(lineitem_suppkey)) * (v5 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se29, *e5)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0* i6 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mLINEITEM3.index[1]);
          const HASH_RES_t h6 = MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::hash(se32.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode* n6 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode*>(i6->slice(se32, h6));
          MKT_SHARE_mPART1_mLINEITEM3_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              date o_orderdate = e6->O_ORDERDATE;
              long v6 = e6->__av;
              MKT_SHARE_mPART1_mSUPPLIER2.addOrDelOnZero(se30.modify(lineitem_suppkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se31.modify(lineitem_partkey)) * (v6 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h6 == n6->hash &&  MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::equals(se32, *e6)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0* i7 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mLINEITEM3.index[1]);
          const HASH_RES_t h7 = MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::hash(se34.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode* n7 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode*>(i7->slice(se34, h7));
          MKT_SHARE_mPART1_mLINEITEM3_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              date o_orderdate = e7->O_ORDERDATE;
              long v7 = e7->__av;
              MKT_SHARE_mPART1_mSUPPLIER2_mPART2.addOrDelOnZero(se33.modify(lineitem_partkey,lineitem_suppkey,o_orderdate),(v7 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h7 == n7->hash &&  MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::equals(se34, *e7)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0* i8 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mLINEITEM3.index[1]);
          const HASH_RES_t h8 = MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::hash(se37.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode* n8 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode*>(i8->slice(se37, h8));
          MKT_SHARE_mPART1_mLINEITEM3_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              date o_orderdate = e8->O_ORDERDATE;
              long v8 = e8->__av;
              MKT_SHARE_mPART1_mPART2.addOrDelOnZero(se35.modify(lineitem_partkey,o_orderdate),(MKT_SHARE_mORDERS6_mLINEITEM1.getValueOrDefault(se36.modify(lineitem_suppkey)) * (v8 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h8 == n8->hash &&  MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::equals(se37, *e8)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0* i9 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.index[1]);
          const HASH_RES_t h9 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::hash(se41.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode* n9 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode*>(i9->slice(se41, h9));
          MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              long total_o_year = e9->TOTAL_O_YEAR;
              long v9 = e9->__av;
              MKT_SHARE_mPART1_L2_1_L1_1.addOrDelOnZero(se38.modify(total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se39.modify(lineitem_partkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.getValueOrDefault(se40.modify(lineitem_suppkey)) * (v9 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h9 == n9->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::equals(se41, *e9)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0* i10 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h10 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se45.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n10 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i10->slice(se45, h10));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e10->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e10->TOTAL_O_YEAR;
              long v10 = e10->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.addOrDelOnZero(se42.modify(mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se43.modify(lineitem_partkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.getValueOrDefault(se44.modify(lineitem_suppkey)) * (v10 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h10 == n10->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se45, *e10)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0* i11 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h11 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se48.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n11 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i11->slice(se48, h11));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e11->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e11->TOTAL_O_YEAR;
              long v11 = e11->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.addOrDelOnZero(se46.modify(lineitem_suppkey,mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se47.modify(lineitem_partkey)) * (v11 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h11 == n11->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se48, *e11)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0* i12 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h12 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se50.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n12 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i12->slice(se50, h12));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e12->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e12->TOTAL_O_YEAR;
              long v12 = e12->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.addOrDelOnZero(se49.modify(lineitem_partkey,lineitem_suppkey,mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(v12 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h12 == n12->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se50, *e12)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0* i13 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h13 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se53.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n13 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i13->slice(se53, h13));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry* e13;
         
          if (n13 && (e13 = n13->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e13->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e13->TOTAL_O_YEAR;
              long v13 = e13->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.addOrDelOnZero(se51.modify(lineitem_partkey,mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.getValueOrDefault(se52.modify(lineitem_suppkey)) * (v13 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n13 = n13->nxt;
            } while (n13 && (e13 = n13->obj) && h13 == n13->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se53, *e13)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0* i14 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.index[1]);
          const HASH_RES_t h14 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::hash(se56.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode* n14 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode*>(i14->slice(se56, h14));
          MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              long total_o_year = e14->TOTAL_O_YEAR;
              long v14 = e14->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.addOrDelOnZero(se54.modify(lineitem_suppkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se55.modify(lineitem_partkey)) * (v14 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h14 == n14->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::equals(se56, *e14)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0* i15 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.index[1]);
          const HASH_RES_t h15 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::hash(se58.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode* n15 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode*>(i15->slice(se58, h15));
          MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry* e15;
         
          if (n15 && (e15 = n15->obj)) {
            do {                
              long total_o_year = e15->TOTAL_O_YEAR;
              long v15 = e15->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.addOrDelOnZero(se57.modify(lineitem_partkey,lineitem_suppkey,total_o_year),(v15 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
              n15 = n15->nxt;
            } while (n15 && (e15 = n15->obj) && h15 == n15->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::equals(se58, *e15)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0* i16 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.index[1]);
          const HASH_RES_t h16 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::hash(se61.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode* n16 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode*>(i16->slice(se61, h16));
          MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry* e16;
         
          if (n16 && (e16 = n16->obj)) {
            do {                
              long total_o_year = e16->TOTAL_O_YEAR;
              long v16 = e16->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mPART2.addOrDelOnZero(se59.modify(lineitem_partkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.getValueOrDefault(se60.modify(lineitem_suppkey)) * (v16 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n16 = n16->nxt;
            } while (n16 && (e16 = n16->obj) && h16 == n16->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::equals(se61, *e16)); 
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHARE_mPART1_map_0* i17 = static_cast<HashIndex_MKT_SHARE_mPART1_map_0*>(MKT_SHARE_mPART1.index[0]);
          HashIndex_MKT_SHARE_mPART1_map_0::IdxNode* n17; 
          MKT_SHARE_mPART1_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                date o_orderdate = e17->O_ORDERDATE;
                DOUBLE_TYPE v17 = e17->__av;
                long l1 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg1 = 0.0;
                DOUBLE_TYPE l3 = MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se63.modify(l1));
                agg1 += Ulistmax(1L, l3);
                DOUBLE_TYPE l2 = agg1;
                MKT_SHARE.addOrDelOnZero(se62.modify(l1),(v17 * Udiv(l2)));
              n17 = n17->nxt;
            }
          }
        }
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  //++tN;
        MKT_SHARE_mORDERS1_L2_1_L1_5.addOrDelOnZero(se64.modify(lineitem_orderkey),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se65.modify(lineitem_partkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.getValueOrDefault(se66.modify(lineitem_suppkey)) * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
        MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.addOrDelOnZero(se67.modify(lineitem_orderkey,lineitem_suppkey),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se68.modify(lineitem_partkey)) * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
        MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.addOrDelOnZero(se69.modify(lineitem_orderkey,lineitem_partkey,lineitem_suppkey),(-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
        MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.addOrDelOnZero(se70.modify(lineitem_orderkey,lineitem_partkey),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.getValueOrDefault(se71.modify(lineitem_suppkey)) * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
        MKT_SHARE_mORDERS6.addOrDelOnZero(se72.modify(lineitem_orderkey),(MKT_SHARE_mORDERS6_mLINEITEM1.getValueOrDefault(se73.modify(lineitem_suppkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se74.modify(lineitem_partkey)) * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
        MKT_SHARE_mORDERS6_mPART2.addOrDelOnZero(se75.modify(lineitem_orderkey,lineitem_partkey),(MKT_SHARE_mORDERS6_mLINEITEM1.getValueOrDefault(se76.modify(lineitem_suppkey)) * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
        { //slice 
          const HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0* i18 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mLINEITEM3.index[1]);
          const HASH_RES_t h17 = MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::hash(se80.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode* n18 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode*>(i18->slice(se80, h17));
          MKT_SHARE_mPART1_mLINEITEM3_entry* e18;
         
          if (n18 && (e18 = n18->obj)) {
            do {                
              date o_orderdate = e18->O_ORDERDATE;
              long v18 = e18->__av;
              MKT_SHARE_mPART1.addOrDelOnZero(se77.modify(o_orderdate),(MKT_SHARE_mORDERS6_mLINEITEM1.getValueOrDefault(se78.modify(lineitem_suppkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se79.modify(lineitem_partkey)) * (v18 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))))));
              n18 = n18->nxt;
            } while (n18 && (e18 = n18->obj) && h17 == n18->hash &&  MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::equals(se80, *e18)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0* i19 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h18 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se84.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n19 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i19->slice(se84, h18));
          MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry* e19;
         
          if (n19 && (e19 = n19->obj)) {
            do {                
              long mkt_share_mpart1_mcustomercustomer_custkey = e19->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e19->O_ORDERDATE;
              long v19 = e19->__av;
              MKT_SHARE_mPART1_mCUSTOMER1.addOrDelOnZero(se81.modify(mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(MKT_SHARE_mORDERS6_mLINEITEM1.getValueOrDefault(se82.modify(lineitem_suppkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se83.modify(lineitem_partkey)) * (v19 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))))));
              n19 = n19->nxt;
            } while (n19 && (e19 = n19->obj) && h18 == n19->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se84, *e19)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0* i20 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h19 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se87.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n20 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i20->slice(se87, h19));
          MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry* e20;
         
          if (n20 && (e20 = n20->obj)) {
            do {                
              long mkt_share_mpart1_mcustomercustomer_custkey = e20->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e20->O_ORDERDATE;
              long v20 = e20->__av;
              MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.addOrDelOnZero(se85.modify(lineitem_suppkey,mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se86.modify(lineitem_partkey)) * (v20 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n20 = n20->nxt;
            } while (n20 && (e20 = n20->obj) && h19 == n20->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se87, *e20)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0* i21 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h20 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se89.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n21 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i21->slice(se89, h20));
          MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry* e21;
         
          if (n21 && (e21 = n21->obj)) {
            do {                
              long mkt_share_mpart1_mcustomercustomer_custkey = e21->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e21->O_ORDERDATE;
              long v21 = e21->__av;
              MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.addOrDelOnZero(se88.modify(lineitem_partkey,lineitem_suppkey,mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(v21 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n21 = n21->nxt;
            } while (n21 && (e21 = n21->obj) && h20 == n21->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se89, *e21)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0* i22 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h21 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se92.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n22 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i22->slice(se92, h21));
          MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry* e22;
         
          if (n22 && (e22 = n22->obj)) {
            do {                
              long mkt_share_mpart1_mcustomercustomer_custkey = e22->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e22->O_ORDERDATE;
              long v22 = e22->__av;
              MKT_SHARE_mPART1_mCUSTOMER1_mPART2.addOrDelOnZero(se90.modify(lineitem_partkey,mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(MKT_SHARE_mORDERS6_mLINEITEM1.getValueOrDefault(se91.modify(lineitem_suppkey)) * (v22 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n22 = n22->nxt;
            } while (n22 && (e22 = n22->obj) && h21 == n22->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se92, *e22)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0* i23 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mLINEITEM3.index[1]);
          const HASH_RES_t h22 = MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::hash(se95.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode* n23 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode*>(i23->slice(se95, h22));
          MKT_SHARE_mPART1_mLINEITEM3_entry* e23;
         
          if (n23 && (e23 = n23->obj)) {
            do {                
              date o_orderdate = e23->O_ORDERDATE;
              long v23 = e23->__av;
              MKT_SHARE_mPART1_mSUPPLIER2.addOrDelOnZero(se93.modify(lineitem_suppkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se94.modify(lineitem_partkey)) * (v23 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n23 = n23->nxt;
            } while (n23 && (e23 = n23->obj) && h22 == n23->hash &&  MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::equals(se95, *e23)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0* i24 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mLINEITEM3.index[1]);
          const HASH_RES_t h23 = MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::hash(se97.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode* n24 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode*>(i24->slice(se97, h23));
          MKT_SHARE_mPART1_mLINEITEM3_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              date o_orderdate = e24->O_ORDERDATE;
              long v24 = e24->__av;
              MKT_SHARE_mPART1_mSUPPLIER2_mPART2.addOrDelOnZero(se96.modify(lineitem_partkey,lineitem_suppkey,o_orderdate),(v24 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h23 == n24->hash &&  MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::equals(se97, *e24)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0* i25 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_mLINEITEM3.index[1]);
          const HASH_RES_t h24 = MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::hash(se100.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode* n25 = static_cast<HashIndex_MKT_SHARE_mPART1_mLINEITEM3_map_0::IdxNode*>(i25->slice(se100, h24));
          MKT_SHARE_mPART1_mLINEITEM3_entry* e25;
         
          if (n25 && (e25 = n25->obj)) {
            do {                
              date o_orderdate = e25->O_ORDERDATE;
              long v25 = e25->__av;
              MKT_SHARE_mPART1_mPART2.addOrDelOnZero(se98.modify(lineitem_partkey,o_orderdate),(MKT_SHARE_mORDERS6_mLINEITEM1.getValueOrDefault(se99.modify(lineitem_suppkey)) * (v25 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n25 = n25->nxt;
            } while (n25 && (e25 = n25->obj) && h24 == n25->hash &&  MKT_SHARE_mPART1_mLINEITEM3_mapkey0_idxfn::equals(se100, *e25)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0* i26 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.index[1]);
          const HASH_RES_t h25 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::hash(se104.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode* n26 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode*>(i26->slice(se104, h25));
          MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry* e26;
         
          if (n26 && (e26 = n26->obj)) {
            do {                
              long total_o_year = e26->TOTAL_O_YEAR;
              long v26 = e26->__av;
              MKT_SHARE_mPART1_L2_1_L1_1.addOrDelOnZero(se101.modify(total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se102.modify(lineitem_partkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.getValueOrDefault(se103.modify(lineitem_suppkey)) * (v26 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))))));
              n26 = n26->nxt;
            } while (n26 && (e26 = n26->obj) && h25 == n26->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::equals(se104, *e26)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0* i27 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h26 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se108.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n27 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i27->slice(se108, h26));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry* e27;
         
          if (n27 && (e27 = n27->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e27->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e27->TOTAL_O_YEAR;
              long v27 = e27->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.addOrDelOnZero(se105.modify(mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se106.modify(lineitem_partkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.getValueOrDefault(se107.modify(lineitem_suppkey)) * (v27 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))))));
              n27 = n27->nxt;
            } while (n27 && (e27 = n27->obj) && h26 == n27->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se108, *e27)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0* i28 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h27 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se111.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n28 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i28->slice(se111, h27));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry* e28;
         
          if (n28 && (e28 = n28->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e28->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e28->TOTAL_O_YEAR;
              long v28 = e28->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.addOrDelOnZero(se109.modify(lineitem_suppkey,mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se110.modify(lineitem_partkey)) * (v28 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n28 = n28->nxt;
            } while (n28 && (e28 = n28->obj) && h27 == n28->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se111, *e28)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0* i29 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h28 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se113.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n29 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i29->slice(se113, h28));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry* e29;
         
          if (n29 && (e29 = n29->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e29->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e29->TOTAL_O_YEAR;
              long v29 = e29->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.addOrDelOnZero(se112.modify(lineitem_partkey,lineitem_suppkey,mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(v29 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n29 = n29->nxt;
            } while (n29 && (e29 = n29->obj) && h28 == n29->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se113, *e29)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0* i30 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index[1]);
          const HASH_RES_t h29 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::hash(se116.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode* n30 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_0::IdxNode*>(i30->slice(se116, h29));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry* e30;
         
          if (n30 && (e30 = n30->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e30->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e30->TOTAL_O_YEAR;
              long v30 = e30->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.addOrDelOnZero(se114.modify(lineitem_partkey,mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.getValueOrDefault(se115.modify(lineitem_suppkey)) * (v30 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n30 = n30->nxt;
            } while (n30 && (e30 = n30->obj) && h29 == n30->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey0_idxfn::equals(se116, *e30)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0* i31 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.index[1]);
          const HASH_RES_t h30 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::hash(se119.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode* n31 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode*>(i31->slice(se119, h30));
          MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry* e31;
         
          if (n31 && (e31 = n31->obj)) {
            do {                
              long total_o_year = e31->TOTAL_O_YEAR;
              long v31 = e31->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.addOrDelOnZero(se117.modify(lineitem_suppkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.getValueOrDefault(se118.modify(lineitem_partkey)) * (v31 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n31 = n31->nxt;
            } while (n31 && (e31 = n31->obj) && h30 == n31->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::equals(se119, *e31)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0* i32 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.index[1]);
          const HASH_RES_t h31 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::hash(se121.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode* n32 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode*>(i32->slice(se121, h31));
          MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry* e32;
         
          if (n32 && (e32 = n32->obj)) {
            do {                
              long total_o_year = e32->TOTAL_O_YEAR;
              long v32 = e32->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.addOrDelOnZero(se120.modify(lineitem_partkey,lineitem_suppkey,total_o_year),(v32 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))));
              n32 = n32->nxt;
            } while (n32 && (e32 = n32->obj) && h31 == n32->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::equals(se121, *e32)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0* i33 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.index[1]);
          const HASH_RES_t h32 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::hash(se124.modify0(lineitem_orderkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode* n33 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map_0::IdxNode*>(i33->slice(se124, h32));
          MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry* e33;
         
          if (n33 && (e33 = n33->obj)) {
            do {                
              long total_o_year = e33->TOTAL_O_YEAR;
              long v33 = e33->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mPART2.addOrDelOnZero(se122.modify(lineitem_partkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.getValueOrDefault(se123.modify(lineitem_suppkey)) * (v33 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))));
              n33 = n33->nxt;
            } while (n33 && (e33 = n33->obj) && h32 == n33->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_mapkey0_idxfn::equals(se124, *e33)); 
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHARE_mPART1_map_0* i34 = static_cast<HashIndex_MKT_SHARE_mPART1_map_0*>(MKT_SHARE_mPART1.index[0]);
          HashIndex_MKT_SHARE_mPART1_map_0::IdxNode* n34; 
          MKT_SHARE_mPART1_entry* e34;
        
          for (size_t i = 0; i < i34->size_; i++)
          {
            n34 = i34->buckets_ + i;
            while (n34 && (e34 = n34->obj))
            {
                date o_orderdate = e34->O_ORDERDATE;
                DOUBLE_TYPE v34 = e34->__av;
                long l4 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg2 = 0.0;
                DOUBLE_TYPE l6 = MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se126.modify(l4));
                agg2 += Ulistmax(1L, l6);
                DOUBLE_TYPE l5 = agg2;
                MKT_SHARE.addOrDelOnZero(se125.modify(l4),(v34 * Udiv(l5)));
              n34 = n34->nxt;
            }
          }
        }
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        long l7 = Uyear_part(orders_orderdate);
        DOUBLE_TYPE agg3 = 0.0;
        DOUBLE_TYPE agg4 = 0.0;
        DOUBLE_TYPE l9 = (MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se128.modify(l7)) + (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? (MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se129.modify(orders_custkey)) * MKT_SHARE_mORDERS1_L2_1_L1_5.getValueOrDefault(se130.modify(orders_orderkey))) : 0.0));
        agg4 += Ulistmax(1L, l9);
        DOUBLE_TYPE l8 = agg4;
        {  // foreach
          const HashIndex_MKT_SHARE_mPART1_map_0* i35 = static_cast<HashIndex_MKT_SHARE_mPART1_map_0*>(MKT_SHARE_mPART1.index[0]);
          HashIndex_MKT_SHARE_mPART1_map_0::IdxNode* n35; 
          MKT_SHARE_mPART1_entry* e35;
        
          for (size_t i = 0; i < i35->size_; i++)
          {
            n35 = i35->buckets_ + i;
            while (n35 && (e35 = n35->obj))
            {
                date o_orderdate = e35->O_ORDERDATE;
                DOUBLE_TYPE v35 = e35->__av;
                (/*if */(l7 == Uyear_part(o_orderdate)) ? agg3 += (v35 * Udiv(l8)) : 0.0);
              n35 = n35->nxt;
            }
          }
        }DOUBLE_TYPE agg5 = 0.0;
        DOUBLE_TYPE agg6 = 0.0;
        DOUBLE_TYPE l11 = MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se131.modify(l7));
        agg6 += Ulistmax(1L, l11);
        DOUBLE_TYPE l10 = agg6;
        {  // foreach
          const HashIndex_MKT_SHARE_mPART1_map_0* i36 = static_cast<HashIndex_MKT_SHARE_mPART1_map_0*>(MKT_SHARE_mPART1.index[0]);
          HashIndex_MKT_SHARE_mPART1_map_0::IdxNode* n36; 
          MKT_SHARE_mPART1_entry* e36;
        
          for (size_t i = 0; i < i36->size_; i++)
          {
            n36 = i36->buckets_ + i;
            while (n36 && (e36 = n36->obj))
            {
                date o_orderdate = e36->O_ORDERDATE;
                DOUBLE_TYPE v36 = e36->__av;
                (/*if */(l7 == Uyear_part(o_orderdate)) ? agg5 += (v36 * Udiv(l10)) : 0.0);
              n36 = n36->nxt;
            }
          }
        }DOUBLE_TYPE agg7 = 0.0;
        DOUBLE_TYPE agg8 = 0.0;
        DOUBLE_TYPE l13 = (MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se134.modify(l7)) + (MKT_SHARE_mORDERS1_L2_1_L1_5.getValueOrDefault(se135.modify(orders_orderkey)) * MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se136.modify(orders_custkey))));
        agg8 += Ulistmax(1L, l13);
        DOUBLE_TYPE l12 = agg8;
        agg7 += Udiv(l12);
        MKT_SHARE.addOrDelOnZero(se127.modify(l7),(agg3 + ((agg5 * -1L) + (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? (MKT_SHARE_mORDERS6.getValueOrDefault(se132.modify(orders_orderkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se133.modify(orders_custkey)) * agg7)) : 0.0))));
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1.addOrDelOnZero(se137.modify(orders_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se138.modify(orders_custkey)) * MKT_SHARE_mORDERS6.getValueOrDefault(se139.modify(orders_orderkey)))) : (void)0);
        (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHARE_mPART1_mCUSTOMER1.addOrDelOnZero(se140.modify(orders_custkey,orders_orderdate),MKT_SHARE_mORDERS6.getValueOrDefault(se141.modify(orders_orderkey))) : (void)0);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.addOrDelOnZero(se142.modify(orders_orderkey,orders_custkey,orders_orderdate),1L) : (void)0);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0* i37 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index[1]);
          const HASH_RES_t h33 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::hash(se144.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode* n37 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode*>(i37->slice(se144, h33));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry* e37;
         
          if (n37 && (e37 = n37->obj)) {
            do {                
              long mkt_share_mpart1_mcustomer1_msuppliersupplier_suppkey = e37->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v37 = e37->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.addOrDelOnZero(se143.modify(mkt_share_mpart1_mcustomer1_msuppliersupplier_suppkey,orders_custkey,orders_orderdate),v37) : (void)0);
              n37 = n37->nxt;
            } while (n37 && (e37 = n37->obj) && h33 == n37->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::equals(se144, *e37)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0* i38 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[1]);
          const HASH_RES_t h34 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::hash(se146.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode* n38 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode*>(i38->slice(se146, h34));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e38;
         
          if (n38 && (e38 = n38->obj)) {
            do {                
              long mkt_share_mpart1_mcustomer1_msupplier2_mpartpart_partkey = e38->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
              long mkt_share_mpart1_mcustomer1_msuppliersupplier_suppkey = e38->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v38 = e38->__av;
              (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.addOrDelOnZero(se145.modify(mkt_share_mpart1_mcustomer1_msupplier2_mpartpart_partkey,mkt_share_mpart1_mcustomer1_msuppliersupplier_suppkey,orders_custkey,orders_orderdate),v38) : (void)0);
              n38 = n38->nxt;
            } while (n38 && (e38 = n38->obj) && h34 == n38->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::equals(se146, *e38)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0* i39 = static_cast<HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0*>(MKT_SHARE_mORDERS6_mPART2.index[1]);
          const HASH_RES_t h35 = MKT_SHARE_mORDERS6_mPART2_mapkey0_idxfn::hash(se148.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0::IdxNode* n39 = static_cast<HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0::IdxNode*>(i39->slice(se148, h35));
          MKT_SHARE_mORDERS6_mPART2_entry* e39;
         
          if (n39 && (e39 = n39->obj)) {
            do {                
              long mkt_share_mpart1_mcustomer1_mpartpart_partkey = e39->MKT_SHARE_mORDERS6_mPARTPART_PARTKEY;
              DOUBLE_TYPE v39 = e39->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_mCUSTOMER1_mPART2.addOrDelOnZero(se147.modify(mkt_share_mpart1_mcustomer1_mpartpart_partkey,orders_custkey,orders_orderdate),v39) : (void)0);
              n39 = n39->nxt;
            } while (n39 && (e39 = n39->obj) && h35 == n39->hash &&  MKT_SHARE_mORDERS6_mPART2_mapkey0_idxfn::equals(se148, *e39)); 
          }
        }(/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHARE_mPART1_mLINEITEM3.addOrDelOnZero(se149.modify(orders_orderkey,orders_orderdate),MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se150.modify(orders_custkey))) : (void)0);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0* i40 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index[1]);
          const HASH_RES_t h36 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::hash(se153.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode* n40 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode*>(i40->slice(se153, h36));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry* e40;
         
          if (n40 && (e40 = n40->obj)) {
            do {                
              long mkt_share_mpart1_msuppliersupplier_suppkey = e40->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v40 = e40->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_mSUPPLIER2.addOrDelOnZero(se151.modify(mkt_share_mpart1_msuppliersupplier_suppkey,orders_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se152.modify(orders_custkey)) * v40)) : (void)0);
              n40 = n40->nxt;
            } while (n40 && (e40 = n40->obj) && h36 == n40->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::equals(se153, *e40)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0* i41 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[1]);
          const HASH_RES_t h37 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::hash(se156.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode* n41 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode*>(i41->slice(se156, h37));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e41;
         
          if (n41 && (e41 = n41->obj)) {
            do {                
              long mkt_share_mpart1_msupplier2_mpartpart_partkey = e41->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
              long mkt_share_mpart1_msuppliersupplier_suppkey = e41->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v41 = e41->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_mSUPPLIER2_mPART2.addOrDelOnZero(se154.modify(mkt_share_mpart1_msupplier2_mpartpart_partkey,mkt_share_mpart1_msuppliersupplier_suppkey,orders_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se155.modify(orders_custkey)) * v41)) : (void)0);
              n41 = n41->nxt;
            } while (n41 && (e41 = n41->obj) && h37 == n41->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::equals(se156, *e41)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0* i42 = static_cast<HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0*>(MKT_SHARE_mORDERS6_mPART2.index[1]);
          const HASH_RES_t h38 = MKT_SHARE_mORDERS6_mPART2_mapkey0_idxfn::hash(se159.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0::IdxNode* n42 = static_cast<HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0::IdxNode*>(i42->slice(se159, h38));
          MKT_SHARE_mORDERS6_mPART2_entry* e42;
         
          if (n42 && (e42 = n42->obj)) {
            do {                
              long mkt_share_mpart1_mpartpart_partkey = e42->MKT_SHARE_mORDERS6_mPARTPART_PARTKEY;
              DOUBLE_TYPE v42 = e42->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_mPART2.addOrDelOnZero(se157.modify(mkt_share_mpart1_mpartpart_partkey,orders_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se158.modify(orders_custkey)) * v42)) : (void)0);
              n42 = n42->nxt;
            } while (n42 && (e42 = n42->obj) && h38 == n42->hash &&  MKT_SHARE_mORDERS6_mPART2_mapkey0_idxfn::equals(se159, *e42)); 
          }
        }long l14 = Uyear_part(orders_orderdate);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1.addOrDelOnZero(se160.modify(l14),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se161.modify(orders_custkey)) * MKT_SHARE_mORDERS1_L2_1_L1_5.getValueOrDefault(se162.modify(orders_orderkey)))) : (void)0);
        long l15 = Uyear_part(orders_orderdate);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.addOrDelOnZero(se163.modify(orders_custkey,l15),MKT_SHARE_mORDERS1_L2_1_L1_5.getValueOrDefault(se164.modify(orders_orderkey))) : (void)0);
        long l16 = Uyear_part(orders_orderdate);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.addOrDelOnZero(se165.modify(orders_orderkey,orders_custkey,l16),1L) : (void)0);
        long l17 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0* i43 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index[1]);
          const HASH_RES_t h39 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::hash(se167.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode* n43 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode*>(i43->slice(se167, h39));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry* e43;
         
          if (n43 && (e43 = n43->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomer1_msuppliersupplier_suppkey = e43->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v43 = e43->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.addOrDelOnZero(se166.modify(mkt_share_mpart1_l2_1_l1_1_mcustomer1_msuppliersupplier_suppkey,orders_custkey,l17),v43) : (void)0);
              n43 = n43->nxt;
            } while (n43 && (e43 = n43->obj) && h39 == n43->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::equals(se167, *e43)); 
          }
        }long l18 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0* i44 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[1]);
          const HASH_RES_t h40 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::hash(se169.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode* n44 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode*>(i44->slice(se169, h40));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e44;
         
          if (n44 && (e44 = n44->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomer1_msupplier1_mpartpart_partkey = e44->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
              long mkt_share_mpart1_l2_1_l1_1_mcustomer1_msuppliersupplier_suppkey = e44->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v44 = e44->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.addOrDelOnZero(se168.modify(mkt_share_mpart1_l2_1_l1_1_mcustomer1_msupplier1_mpartpart_partkey,mkt_share_mpart1_l2_1_l1_1_mcustomer1_msuppliersupplier_suppkey,orders_custkey,l18),v44) : (void)0);
              n44 = n44->nxt;
            } while (n44 && (e44 = n44->obj) && h40 == n44->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::equals(se169, *e44)); 
          }
        }long l19 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0* i45 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.index[1]);
          const HASH_RES_t h41 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey0_idxfn::hash(se171.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0::IdxNode* n45 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0::IdxNode*>(i45->slice(se171, h41));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry* e45;
         
          if (n45 && (e45 = n45->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomer1_mpartpart_partkey = e45->MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY;
              DOUBLE_TYPE v45 = e45->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.addOrDelOnZero(se170.modify(mkt_share_mpart1_l2_1_l1_1_mcustomer1_mpartpart_partkey,orders_custkey,l19),v45) : (void)0);
              n45 = n45->nxt;
            } while (n45 && (e45 = n45->obj) && h41 == n45->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey0_idxfn::equals(se171, *e45)); 
          }
        }long l20 = Uyear_part(orders_orderdate);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.addOrDelOnZero(se172.modify(orders_orderkey,l20),MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se173.modify(orders_custkey))) : (void)0);
        long l21 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0* i46 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index[1]);
          const HASH_RES_t h42 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::hash(se176.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode* n46 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode*>(i46->slice(se176, h42));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry* e46;
         
          if (n46 && (e46 = n46->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey = e46->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v46 = e46->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.addOrDelOnZero(se174.modify(mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey,l21),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se175.modify(orders_custkey)) * v46)) : (void)0);
              n46 = n46->nxt;
            } while (n46 && (e46 = n46->obj) && h42 == n46->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::equals(se176, *e46)); 
          }
        }long l22 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0* i47 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[1]);
          const HASH_RES_t h43 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::hash(se179.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode* n47 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode*>(i47->slice(se179, h43));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e47;
         
          if (n47 && (e47 = n47->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_msupplier1_mpartpart_partkey = e47->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
              long mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey = e47->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v47 = e47->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.addOrDelOnZero(se177.modify(mkt_share_mpart1_l2_1_l1_1_msupplier1_mpartpart_partkey,mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey,l22),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se178.modify(orders_custkey)) * v47)) : (void)0);
              n47 = n47->nxt;
            } while (n47 && (e47 = n47->obj) && h43 == n47->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::equals(se179, *e47)); 
          }
        }long l23 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0* i48 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.index[1]);
          const HASH_RES_t h44 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey0_idxfn::hash(se182.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0::IdxNode* n48 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0::IdxNode*>(i48->slice(se182, h44));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry* e48;
         
          if (n48 && (e48 = n48->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mpartpart_partkey = e48->MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY;
              DOUBLE_TYPE v48 = e48->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mPART2.addOrDelOnZero(se180.modify(mkt_share_mpart1_l2_1_l1_1_mpartpart_partkey,l23),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se181.modify(orders_custkey)) * v48)) : (void)0);
              n48 = n48->nxt;
            } while (n48 && (e48 = n48->obj) && h44 == n48->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey0_idxfn::equals(se182, *e48)); 
          }
        }
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        long l24 = Uyear_part(orders_orderdate);
        DOUBLE_TYPE agg9 = 0.0;
        DOUBLE_TYPE agg10 = 0.0;
        DOUBLE_TYPE l26 = (MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se184.modify(l24)) + (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? (MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se185.modify(orders_custkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_5.getValueOrDefault(se186.modify(orders_orderkey)) * -1L)) : 0.0));
        agg10 += Ulistmax(1L, l26);
        DOUBLE_TYPE l25 = agg10;
        {  // foreach
          const HashIndex_MKT_SHARE_mPART1_map_0* i49 = static_cast<HashIndex_MKT_SHARE_mPART1_map_0*>(MKT_SHARE_mPART1.index[0]);
          HashIndex_MKT_SHARE_mPART1_map_0::IdxNode* n49; 
          MKT_SHARE_mPART1_entry* e49;
        
          for (size_t i = 0; i < i49->size_; i++)
          {
            n49 = i49->buckets_ + i;
            while (n49 && (e49 = n49->obj))
            {
                date o_orderdate = e49->O_ORDERDATE;
                DOUBLE_TYPE v49 = e49->__av;
                (/*if */(l24 == Uyear_part(o_orderdate)) ? agg9 += (v49 * Udiv(l25)) : 0.0);
              n49 = n49->nxt;
            }
          }
        }DOUBLE_TYPE agg11 = 0.0;
        DOUBLE_TYPE agg12 = 0.0;
        DOUBLE_TYPE l28 = MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se187.modify(l24));
        agg12 += Ulistmax(1L, l28);
        DOUBLE_TYPE l27 = agg12;
        {  // foreach
          const HashIndex_MKT_SHARE_mPART1_map_0* i50 = static_cast<HashIndex_MKT_SHARE_mPART1_map_0*>(MKT_SHARE_mPART1.index[0]);
          HashIndex_MKT_SHARE_mPART1_map_0::IdxNode* n50; 
          MKT_SHARE_mPART1_entry* e50;
        
          for (size_t i = 0; i < i50->size_; i++)
          {
            n50 = i50->buckets_ + i;
            while (n50 && (e50 = n50->obj))
            {
                date o_orderdate = e50->O_ORDERDATE;
                DOUBLE_TYPE v50 = e50->__av;
                (/*if */(l24 == Uyear_part(o_orderdate)) ? agg11 += (v50 * Udiv(l27)) : 0.0);
              n50 = n50->nxt;
            }
          }
        }DOUBLE_TYPE agg13 = 0.0;
        DOUBLE_TYPE agg14 = 0.0;
        DOUBLE_TYPE l30 = (MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se190.modify(l24)) + (MKT_SHARE_mORDERS1_L2_1_L1_5.getValueOrDefault(se191.modify(orders_orderkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se192.modify(orders_custkey)) * -1L)));
        agg14 += Ulistmax(1L, l30);
        DOUBLE_TYPE l29 = agg14;
        agg13 += Udiv(l29);
        MKT_SHARE.addOrDelOnZero(se183.modify(l24),(agg9 + ((agg11 * -1L) + (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? (MKT_SHARE_mORDERS6.getValueOrDefault(se188.modify(orders_orderkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se189.modify(orders_custkey)) * (agg13 * -1L))) : 0.0))));
        (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHARE_mPART1.addOrDelOnZero(se193.modify(orders_orderdate),(MKT_SHARE_mORDERS6.getValueOrDefault(se194.modify(orders_orderkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se195.modify(orders_custkey)) * -1L))) : (void)0);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_mCUSTOMER1.addOrDelOnZero(se196.modify(orders_custkey,orders_orderdate),(MKT_SHARE_mORDERS6.getValueOrDefault(se197.modify(orders_orderkey)) * -1L)) : (void)0);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.addOrDelOnZero(se198.modify(orders_orderkey,orders_custkey,orders_orderdate),-1L) : (void)0);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0* i51 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index[1]);
          const HASH_RES_t h45 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::hash(se200.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode* n51 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode*>(i51->slice(se200, h45));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry* e51;
         
          if (n51 && (e51 = n51->obj)) {
            do {                
              long mkt_share_mpart1_mcustomer1_msuppliersupplier_suppkey = e51->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v51 = e51->__av;
              (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.addOrDelOnZero(se199.modify(mkt_share_mpart1_mcustomer1_msuppliersupplier_suppkey,orders_custkey,orders_orderdate),(v51 * -1L)) : (void)0);
              n51 = n51->nxt;
            } while (n51 && (e51 = n51->obj) && h45 == n51->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::equals(se200, *e51)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0* i52 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[1]);
          const HASH_RES_t h46 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::hash(se202.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode* n52 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode*>(i52->slice(se202, h46));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e52;
         
          if (n52 && (e52 = n52->obj)) {
            do {                
              long mkt_share_mpart1_mcustomer1_msupplier2_mpartpart_partkey = e52->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
              long mkt_share_mpart1_mcustomer1_msuppliersupplier_suppkey = e52->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v52 = e52->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.addOrDelOnZero(se201.modify(mkt_share_mpart1_mcustomer1_msupplier2_mpartpart_partkey,mkt_share_mpart1_mcustomer1_msuppliersupplier_suppkey,orders_custkey,orders_orderdate),(v52 * -1L)) : (void)0);
              n52 = n52->nxt;
            } while (n52 && (e52 = n52->obj) && h46 == n52->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::equals(se202, *e52)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0* i53 = static_cast<HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0*>(MKT_SHARE_mORDERS6_mPART2.index[1]);
          const HASH_RES_t h47 = MKT_SHARE_mORDERS6_mPART2_mapkey0_idxfn::hash(se204.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0::IdxNode* n53 = static_cast<HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0::IdxNode*>(i53->slice(se204, h47));
          MKT_SHARE_mORDERS6_mPART2_entry* e53;
         
          if (n53 && (e53 = n53->obj)) {
            do {                
              long mkt_share_mpart1_mcustomer1_mpartpart_partkey = e53->MKT_SHARE_mORDERS6_mPARTPART_PARTKEY;
              DOUBLE_TYPE v53 = e53->__av;
              (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHARE_mPART1_mCUSTOMER1_mPART2.addOrDelOnZero(se203.modify(mkt_share_mpart1_mcustomer1_mpartpart_partkey,orders_custkey,orders_orderdate),(v53 * -1L)) : (void)0);
              n53 = n53->nxt;
            } while (n53 && (e53 = n53->obj) && h47 == n53->hash &&  MKT_SHARE_mORDERS6_mPART2_mapkey0_idxfn::equals(se204, *e53)); 
          }
        }(/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHARE_mPART1_mLINEITEM3.addOrDelOnZero(se205.modify(orders_orderkey,orders_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se206.modify(orders_custkey)) * -1L)) : (void)0);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0* i54 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index[1]);
          const HASH_RES_t h48 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::hash(se209.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode* n54 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode*>(i54->slice(se209, h48));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry* e54;
         
          if (n54 && (e54 = n54->obj)) {
            do {                
              long mkt_share_mpart1_msuppliersupplier_suppkey = e54->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v54 = e54->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_mSUPPLIER2.addOrDelOnZero(se207.modify(mkt_share_mpart1_msuppliersupplier_suppkey,orders_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se208.modify(orders_custkey)) * (v54 * -1L))) : (void)0);
              n54 = n54->nxt;
            } while (n54 && (e54 = n54->obj) && h48 == n54->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::equals(se209, *e54)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0* i55 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[1]);
          const HASH_RES_t h49 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::hash(se212.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode* n55 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode*>(i55->slice(se212, h49));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e55;
         
          if (n55 && (e55 = n55->obj)) {
            do {                
              long mkt_share_mpart1_msupplier2_mpartpart_partkey = e55->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
              long mkt_share_mpart1_msuppliersupplier_suppkey = e55->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v55 = e55->__av;
              (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHARE_mPART1_mSUPPLIER2_mPART2.addOrDelOnZero(se210.modify(mkt_share_mpart1_msupplier2_mpartpart_partkey,mkt_share_mpart1_msuppliersupplier_suppkey,orders_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se211.modify(orders_custkey)) * (v55 * -1L))) : (void)0);
              n55 = n55->nxt;
            } while (n55 && (e55 = n55->obj) && h49 == n55->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::equals(se212, *e55)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0* i56 = static_cast<HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0*>(MKT_SHARE_mORDERS6_mPART2.index[1]);
          const HASH_RES_t h50 = MKT_SHARE_mORDERS6_mPART2_mapkey0_idxfn::hash(se215.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0::IdxNode* n56 = static_cast<HashIndex_MKT_SHARE_mORDERS6_mPART2_map_0::IdxNode*>(i56->slice(se215, h50));
          MKT_SHARE_mORDERS6_mPART2_entry* e56;
         
          if (n56 && (e56 = n56->obj)) {
            do {                
              long mkt_share_mpart1_mpartpart_partkey = e56->MKT_SHARE_mORDERS6_mPARTPART_PARTKEY;
              DOUBLE_TYPE v56 = e56->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_mPART2.addOrDelOnZero(se213.modify(mkt_share_mpart1_mpartpart_partkey,orders_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se214.modify(orders_custkey)) * (v56 * -1L))) : (void)0);
              n56 = n56->nxt;
            } while (n56 && (e56 = n56->obj) && h50 == n56->hash &&  MKT_SHARE_mORDERS6_mPART2_mapkey0_idxfn::equals(se215, *e56)); 
          }
        }long l31 = Uyear_part(orders_orderdate);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1.addOrDelOnZero(se216.modify(l31),(MKT_SHARE_mORDERS1_L2_1_L1_5.getValueOrDefault(se217.modify(orders_orderkey)) * (MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se218.modify(orders_custkey)) * -1L))) : (void)0);
        long l32 = Uyear_part(orders_orderdate);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.addOrDelOnZero(se219.modify(orders_custkey,l32),(MKT_SHARE_mORDERS1_L2_1_L1_5.getValueOrDefault(se220.modify(orders_orderkey)) * -1L)) : (void)0);
        long l33 = Uyear_part(orders_orderdate);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.addOrDelOnZero(se221.modify(orders_orderkey,orders_custkey,l33),-1L) : (void)0);
        long l34 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0* i57 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index[1]);
          const HASH_RES_t h51 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::hash(se223.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode* n57 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode*>(i57->slice(se223, h51));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry* e57;
         
          if (n57 && (e57 = n57->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomer1_msuppliersupplier_suppkey = e57->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v57 = e57->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.addOrDelOnZero(se222.modify(mkt_share_mpart1_l2_1_l1_1_mcustomer1_msuppliersupplier_suppkey,orders_custkey,l34),(v57 * -1L)) : (void)0);
              n57 = n57->nxt;
            } while (n57 && (e57 = n57->obj) && h51 == n57->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::equals(se223, *e57)); 
          }
        }long l35 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0* i58 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[1]);
          const HASH_RES_t h52 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::hash(se225.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode* n58 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode*>(i58->slice(se225, h52));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e58;
         
          if (n58 && (e58 = n58->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomer1_msupplier1_mpartpart_partkey = e58->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
              long mkt_share_mpart1_l2_1_l1_1_mcustomer1_msuppliersupplier_suppkey = e58->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v58 = e58->__av;
              (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.addOrDelOnZero(se224.modify(mkt_share_mpart1_l2_1_l1_1_mcustomer1_msupplier1_mpartpart_partkey,mkt_share_mpart1_l2_1_l1_1_mcustomer1_msuppliersupplier_suppkey,orders_custkey,l35),(v58 * -1L)) : (void)0);
              n58 = n58->nxt;
            } while (n58 && (e58 = n58->obj) && h52 == n58->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::equals(se225, *e58)); 
          }
        }long l36 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0* i59 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.index[1]);
          const HASH_RES_t h53 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey0_idxfn::hash(se227.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0::IdxNode* n59 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0::IdxNode*>(i59->slice(se227, h53));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry* e59;
         
          if (n59 && (e59 = n59->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomer1_mpartpart_partkey = e59->MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY;
              DOUBLE_TYPE v59 = e59->__av;
              (/*if */(orders_orderdate >= c1 && c2 >= orders_orderdate) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.addOrDelOnZero(se226.modify(mkt_share_mpart1_l2_1_l1_1_mcustomer1_mpartpart_partkey,orders_custkey,l36),(v59 * -1L)) : (void)0);
              n59 = n59->nxt;
            } while (n59 && (e59 = n59->obj) && h53 == n59->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey0_idxfn::equals(se227, *e59)); 
          }
        }long l37 = Uyear_part(orders_orderdate);
        (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.addOrDelOnZero(se228.modify(orders_orderkey,l37),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se229.modify(orders_custkey)) * -1L)) : (void)0);
        long l38 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0* i60 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index[1]);
          const HASH_RES_t h54 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::hash(se232.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode* n60 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_0::IdxNode*>(i60->slice(se232, h54));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry* e60;
         
          if (n60 && (e60 = n60->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey = e60->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v60 = e60->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.addOrDelOnZero(se230.modify(mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey,l38),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se231.modify(orders_custkey)) * (v60 * -1L))) : (void)0);
              n60 = n60->nxt;
            } while (n60 && (e60 = n60->obj) && h54 == n60->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey0_idxfn::equals(se232, *e60)); 
          }
        }long l39 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0* i61 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[1]);
          const HASH_RES_t h55 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::hash(se235.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode* n61 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_0::IdxNode*>(i61->slice(se235, h55));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e61;
         
          if (n61 && (e61 = n61->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_msupplier1_mpartpart_partkey = e61->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
              long mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey = e61->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v61 = e61->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.addOrDelOnZero(se233.modify(mkt_share_mpart1_l2_1_l1_1_msupplier1_mpartpart_partkey,mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey,l39),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se234.modify(orders_custkey)) * (v61 * -1L))) : (void)0);
              n61 = n61->nxt;
            } while (n61 && (e61 = n61->obj) && h55 == n61->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey0_idxfn::equals(se235, *e61)); 
          }
        }long l40 = Uyear_part(orders_orderdate);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0* i62 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.index[1]);
          const HASH_RES_t h56 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey0_idxfn::hash(se238.modify0(orders_orderkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0::IdxNode* n62 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_0::IdxNode*>(i62->slice(se238, h56));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry* e62;
         
          if (n62 && (e62 = n62->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mpartpart_partkey = e62->MKT_SHARE_mORDERS1_L2_1_L1_5_mPARTPART_PARTKEY;
              DOUBLE_TYPE v62 = e62->__av;
              (/*if */(c2 >= orders_orderdate && orders_orderdate >= c1) ? MKT_SHARE_mPART1_L2_1_L1_1_mPART2.addOrDelOnZero(se236.modify(mkt_share_mpart1_l2_1_l1_1_mpartpart_partkey,l40),(MKT_SHARE_mORDERS1_L2_1_L1_4.getValueOrDefault(se237.modify(orders_custkey)) * (v62 * -1L))) : (void)0);
              n62 = n62->nxt;
            } while (n62 && (e62 = n62->obj) && h56 == n62->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey0_idxfn::equals(se238, *e62)); 
          }
        }
      }
    }
    void on_insert_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_1* i63 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_1*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.index[2]);
          const HASH_RES_t h57 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey1_idxfn::hash(se240.modify1(part_partkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_1::IdxNode* n63 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_1::IdxNode*>(i63->slice(se240, h57));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry* e63;
         
          if (n63 && (e63 = n63->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e63->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v63 = e63->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mORDERS1_L2_1_L1_5.addOrDelOnZero(se239.modify(mkt_share_mordersorders_orderkey),v63) : (void)0);
              n63 = n63->nxt;
            } while (n63 && (e63 = n63->obj) && h57 == n63->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey1_idxfn::equals(se240, *e63)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_1* i64 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_1*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[2]);
          const HASH_RES_t h58 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey1_idxfn::hash(se242.modify1(part_partkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_1::IdxNode* n64 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_1::IdxNode*>(i64->slice(se242, h58));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e64;
         
          if (n64 && (e64 = n64->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e64->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              long mkt_share_morders1_l2_1_l1_5_msuppliersupplier_suppkey = e64->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v64 = e64->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.addOrDelOnZero(se241.modify(mkt_share_mordersorders_orderkey,mkt_share_morders1_l2_1_l1_5_msuppliersupplier_suppkey),v64) : (void)0);
              n64 = n64->nxt;
            } while (n64 && (e64 = n64->obj) && h58 == n64->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey1_idxfn::equals(se242, *e64)); 
          }
        }(/*if */(part_type == c3) ? MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.addOrDelOnZero(se243.modify(part_partkey),1L) : (void)0);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS6_mPART2_map_1* i65 = static_cast<HashIndex_MKT_SHARE_mORDERS6_mPART2_map_1*>(MKT_SHARE_mORDERS6_mPART2.index[2]);
          const HASH_RES_t h59 = MKT_SHARE_mORDERS6_mPART2_mapkey1_idxfn::hash(se245.modify1(part_partkey));
          HashIndex_MKT_SHARE_mORDERS6_mPART2_map_1::IdxNode* n65 = static_cast<HashIndex_MKT_SHARE_mORDERS6_mPART2_map_1::IdxNode*>(i65->slice(se245, h59));
          MKT_SHARE_mORDERS6_mPART2_entry* e65;
         
          if (n65 && (e65 = n65->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e65->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v65 = e65->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mORDERS6.addOrDelOnZero(se244.modify(mkt_share_mordersorders_orderkey),v65) : (void)0);
              n65 = n65->nxt;
            } while (n65 && (e65 = n65->obj) && h59 == n65->hash &&  MKT_SHARE_mORDERS6_mPART2_mapkey1_idxfn::equals(se245, *e65)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mPART2_map_0* i66 = static_cast<HashIndex_MKT_SHARE_mPART1_mPART2_map_0*>(MKT_SHARE_mPART1_mPART2.index[1]);
          const HASH_RES_t h60 = MKT_SHARE_mPART1_mPART2_mapkey0_idxfn::hash(se247.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_mPART2_map_0::IdxNode* n66 = static_cast<HashIndex_MKT_SHARE_mPART1_mPART2_map_0::IdxNode*>(i66->slice(se247, h60));
          MKT_SHARE_mPART1_mPART2_entry* e66;
         
          if (n66 && (e66 = n66->obj)) {
            do {                
              date o_orderdate = e66->O_ORDERDATE;
              DOUBLE_TYPE v66 = e66->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1.addOrDelOnZero(se246.modify(o_orderdate),v66) : (void)0);
              n66 = n66->nxt;
            } while (n66 && (e66 = n66->obj) && h60 == n66->hash &&  MKT_SHARE_mPART1_mPART2_mapkey0_idxfn::equals(se247, *e66)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_0* i67 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mPART2.index[1]);
          const HASH_RES_t h61 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey0_idxfn::hash(se249.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_0::IdxNode* n67 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_0::IdxNode*>(i67->slice(se249, h61));
          MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry* e67;
         
          if (n67 && (e67 = n67->obj)) {
            do {                
              long mkt_share_mpart1_mcustomercustomer_custkey = e67->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e67->O_ORDERDATE;
              DOUBLE_TYPE v67 = e67->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_mCUSTOMER1.addOrDelOnZero(se248.modify(mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),v67) : (void)0);
              n67 = n67->nxt;
            } while (n67 && (e67 = n67->obj) && h61 == n67->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey0_idxfn::equals(se249, *e67)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_0* i68 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.index[1]);
          const HASH_RES_t h62 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey0_idxfn::hash(se251.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_0::IdxNode* n68 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_0::IdxNode*>(i68->slice(se251, h62));
          MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry* e68;
         
          if (n68 && (e68 = n68->obj)) {
            do {                
              long mkt_share_mpart1_mcustomer1_msuppliersupplier_suppkey = e68->MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              long mkt_share_mpart1_mcustomercustomer_custkey = e68->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e68->O_ORDERDATE;
              DOUBLE_TYPE v68 = e68->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.addOrDelOnZero(se250.modify(mkt_share_mpart1_mcustomer1_msuppliersupplier_suppkey,mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),v68) : (void)0);
              n68 = n68->nxt;
            } while (n68 && (e68 = n68->obj) && h62 == n68->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey0_idxfn::equals(se251, *e68)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_0* i69 = static_cast<HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_0*>(MKT_SHARE_mPART1_mSUPPLIER2_mPART2.index[1]);
          const HASH_RES_t h63 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey0_idxfn::hash(se253.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_0::IdxNode* n69 = static_cast<HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_0::IdxNode*>(i69->slice(se253, h63));
          MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry* e69;
         
          if (n69 && (e69 = n69->obj)) {
            do {                
              long mkt_share_mpart1_msuppliersupplier_suppkey = e69->MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY;
              date o_orderdate = e69->O_ORDERDATE;
              DOUBLE_TYPE v69 = e69->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_mSUPPLIER2.addOrDelOnZero(se252.modify(mkt_share_mpart1_msuppliersupplier_suppkey,o_orderdate),v69) : (void)0);
              n69 = n69->nxt;
            } while (n69 && (e69 = n69->obj) && h63 == n69->hash &&  MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey0_idxfn::equals(se253, *e69)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mPART2_map_0* i70 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mPART2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mPART2.index[1]);
          const HASH_RES_t h64 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2_mapkey0_idxfn::hash(se255.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mPART2_map_0::IdxNode* n70 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mPART2_map_0::IdxNode*>(i70->slice(se255, h64));
          MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry* e70;
         
          if (n70 && (e70 = n70->obj)) {
            do {                
              long total_o_year = e70->TOTAL_O_YEAR;
              DOUBLE_TYPE v70 = e70->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_L2_1_L1_1.addOrDelOnZero(se254.modify(total_o_year),v70) : (void)0);
              n70 = n70->nxt;
            } while (n70 && (e70 = n70->obj) && h64 == n70->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mPART2_mapkey0_idxfn::equals(se255, *e70)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_0* i71 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.index[1]);
          const HASH_RES_t h65 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey0_idxfn::hash(se257.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_0::IdxNode* n71 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_0::IdxNode*>(i71->slice(se257, h65));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry* e71;
         
          if (n71 && (e71 = n71->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e71->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e71->TOTAL_O_YEAR;
              DOUBLE_TYPE v71 = e71->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.addOrDelOnZero(se256.modify(mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),v71) : (void)0);
              n71 = n71->nxt;
            } while (n71 && (e71 = n71->obj) && h65 == n71->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey0_idxfn::equals(se257, *e71)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_0* i72 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.index[1]);
          const HASH_RES_t h66 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey0_idxfn::hash(se259.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_0::IdxNode* n72 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_0::IdxNode*>(i72->slice(se259, h66));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry* e72;
         
          if (n72 && (e72 = n72->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomer1_msuppliersupplier_suppkey = e72->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e72->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e72->TOTAL_O_YEAR;
              DOUBLE_TYPE v72 = e72->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.addOrDelOnZero(se258.modify(mkt_share_mpart1_l2_1_l1_1_mcustomer1_msuppliersupplier_suppkey,mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),v72) : (void)0);
              n72 = n72->nxt;
            } while (n72 && (e72 = n72->obj) && h66 == n72->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey0_idxfn::equals(se259, *e72)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_0* i73 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.index[1]);
          const HASH_RES_t h67 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey0_idxfn::hash(se261.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_0::IdxNode* n73 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_0::IdxNode*>(i73->slice(se261, h67));
          MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry* e73;
         
          if (n73 && (e73 = n73->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey = e73->MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY;
              long total_o_year = e73->TOTAL_O_YEAR;
              DOUBLE_TYPE v73 = e73->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.addOrDelOnZero(se260.modify(mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey,total_o_year),v73) : (void)0);
              n73 = n73->nxt;
            } while (n73 && (e73 = n73->obj) && h67 == n73->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey0_idxfn::equals(se261, *e73)); 
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHARE_mPART1_map_0* i74 = static_cast<HashIndex_MKT_SHARE_mPART1_map_0*>(MKT_SHARE_mPART1.index[0]);
          HashIndex_MKT_SHARE_mPART1_map_0::IdxNode* n74; 
          MKT_SHARE_mPART1_entry* e74;
        
          for (size_t i = 0; i < i74->size_; i++)
          {
            n74 = i74->buckets_ + i;
            while (n74 && (e74 = n74->obj))
            {
                date o_orderdate = e74->O_ORDERDATE;
                DOUBLE_TYPE v74 = e74->__av;
                long l41 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg15 = 0.0;
                DOUBLE_TYPE l43 = MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se263.modify(l41));
                agg15 += Ulistmax(1L, l43);
                DOUBLE_TYPE l42 = agg15;
                MKT_SHARE.addOrDelOnZero(se262.modify(l41),(v74 * Udiv(l42)));
              n74 = n74->nxt;
            }
          }
        }
      }
    }
    void on_delete_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_1* i75 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_1*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.index[2]);
          const HASH_RES_t h68 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey1_idxfn::hash(se265.modify1(part_partkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_1::IdxNode* n75 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map_1::IdxNode*>(i75->slice(se265, h68));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry* e75;
         
          if (n75 && (e75 = n75->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e75->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v75 = e75->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mORDERS1_L2_1_L1_5.addOrDelOnZero(se264.modify(mkt_share_mordersorders_orderkey),(v75 * -1L)) : (void)0);
              n75 = n75->nxt;
            } while (n75 && (e75 = n75->obj) && h68 == n75->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_mapkey1_idxfn::equals(se265, *e75)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_1* i76 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_1*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[2]);
          const HASH_RES_t h69 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey1_idxfn::hash(se267.modify1(part_partkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_1::IdxNode* n76 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_1::IdxNode*>(i76->slice(se267, h69));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e76;
         
          if (n76 && (e76 = n76->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e76->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              long mkt_share_morders1_l2_1_l1_5_msuppliersupplier_suppkey = e76->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIERSUPPLIER_SUPPKEY;
              DOUBLE_TYPE v76 = e76->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.addOrDelOnZero(se266.modify(mkt_share_mordersorders_orderkey,mkt_share_morders1_l2_1_l1_5_msuppliersupplier_suppkey),(v76 * -1L)) : (void)0);
              n76 = n76->nxt;
            } while (n76 && (e76 = n76->obj) && h69 == n76->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey1_idxfn::equals(se267, *e76)); 
          }
        }(/*if */(part_type == c3) ? MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.addOrDelOnZero(se268.modify(part_partkey),-1L) : (void)0);
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS6_mPART2_map_1* i77 = static_cast<HashIndex_MKT_SHARE_mORDERS6_mPART2_map_1*>(MKT_SHARE_mORDERS6_mPART2.index[2]);
          const HASH_RES_t h70 = MKT_SHARE_mORDERS6_mPART2_mapkey1_idxfn::hash(se270.modify1(part_partkey));
          HashIndex_MKT_SHARE_mORDERS6_mPART2_map_1::IdxNode* n77 = static_cast<HashIndex_MKT_SHARE_mORDERS6_mPART2_map_1::IdxNode*>(i77->slice(se270, h70));
          MKT_SHARE_mORDERS6_mPART2_entry* e77;
         
          if (n77 && (e77 = n77->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e77->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v77 = e77->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mORDERS6.addOrDelOnZero(se269.modify(mkt_share_mordersorders_orderkey),(v77 * -1L)) : (void)0);
              n77 = n77->nxt;
            } while (n77 && (e77 = n77->obj) && h70 == n77->hash &&  MKT_SHARE_mORDERS6_mPART2_mapkey1_idxfn::equals(se270, *e77)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mPART2_map_0* i78 = static_cast<HashIndex_MKT_SHARE_mPART1_mPART2_map_0*>(MKT_SHARE_mPART1_mPART2.index[1]);
          const HASH_RES_t h71 = MKT_SHARE_mPART1_mPART2_mapkey0_idxfn::hash(se272.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_mPART2_map_0::IdxNode* n78 = static_cast<HashIndex_MKT_SHARE_mPART1_mPART2_map_0::IdxNode*>(i78->slice(se272, h71));
          MKT_SHARE_mPART1_mPART2_entry* e78;
         
          if (n78 && (e78 = n78->obj)) {
            do {                
              date o_orderdate = e78->O_ORDERDATE;
              DOUBLE_TYPE v78 = e78->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1.addOrDelOnZero(se271.modify(o_orderdate),(v78 * -1L)) : (void)0);
              n78 = n78->nxt;
            } while (n78 && (e78 = n78->obj) && h71 == n78->hash &&  MKT_SHARE_mPART1_mPART2_mapkey0_idxfn::equals(se272, *e78)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_0* i79 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mPART2.index[1]);
          const HASH_RES_t h72 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey0_idxfn::hash(se274.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_0::IdxNode* n79 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_0::IdxNode*>(i79->slice(se274, h72));
          MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry* e79;
         
          if (n79 && (e79 = n79->obj)) {
            do {                
              long mkt_share_mpart1_mcustomercustomer_custkey = e79->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e79->O_ORDERDATE;
              DOUBLE_TYPE v79 = e79->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_mCUSTOMER1.addOrDelOnZero(se273.modify(mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(v79 * -1L)) : (void)0);
              n79 = n79->nxt;
            } while (n79 && (e79 = n79->obj) && h72 == n79->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey0_idxfn::equals(se274, *e79)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_0* i80 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.index[1]);
          const HASH_RES_t h73 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey0_idxfn::hash(se276.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_0::IdxNode* n80 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_0::IdxNode*>(i80->slice(se276, h73));
          MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry* e80;
         
          if (n80 && (e80 = n80->obj)) {
            do {                
              long mkt_share_mpart1_mcustomer1_msuppliersupplier_suppkey = e80->MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              long mkt_share_mpart1_mcustomercustomer_custkey = e80->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e80->O_ORDERDATE;
              DOUBLE_TYPE v80 = e80->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.addOrDelOnZero(se275.modify(mkt_share_mpart1_mcustomer1_msuppliersupplier_suppkey,mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(v80 * -1L)) : (void)0);
              n80 = n80->nxt;
            } while (n80 && (e80 = n80->obj) && h73 == n80->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey0_idxfn::equals(se276, *e80)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_0* i81 = static_cast<HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_0*>(MKT_SHARE_mPART1_mSUPPLIER2_mPART2.index[1]);
          const HASH_RES_t h74 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey0_idxfn::hash(se278.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_0::IdxNode* n81 = static_cast<HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_0::IdxNode*>(i81->slice(se278, h74));
          MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry* e81;
         
          if (n81 && (e81 = n81->obj)) {
            do {                
              long mkt_share_mpart1_msuppliersupplier_suppkey = e81->MKT_SHARE_mPART1_mSUPPLIERSUPPLIER_SUPPKEY;
              date o_orderdate = e81->O_ORDERDATE;
              DOUBLE_TYPE v81 = e81->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_mSUPPLIER2.addOrDelOnZero(se277.modify(mkt_share_mpart1_msuppliersupplier_suppkey,o_orderdate),(v81 * -1L)) : (void)0);
              n81 = n81->nxt;
            } while (n81 && (e81 = n81->obj) && h74 == n81->hash &&  MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey0_idxfn::equals(se278, *e81)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mPART2_map_0* i82 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mPART2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mPART2.index[1]);
          const HASH_RES_t h75 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2_mapkey0_idxfn::hash(se280.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mPART2_map_0::IdxNode* n82 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mPART2_map_0::IdxNode*>(i82->slice(se280, h75));
          MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry* e82;
         
          if (n82 && (e82 = n82->obj)) {
            do {                
              long total_o_year = e82->TOTAL_O_YEAR;
              DOUBLE_TYPE v82 = e82->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_L2_1_L1_1.addOrDelOnZero(se279.modify(total_o_year),(v82 * -1L)) : (void)0);
              n82 = n82->nxt;
            } while (n82 && (e82 = n82->obj) && h75 == n82->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mPART2_mapkey0_idxfn::equals(se280, *e82)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_0* i83 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.index[1]);
          const HASH_RES_t h76 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey0_idxfn::hash(se282.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_0::IdxNode* n83 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_0::IdxNode*>(i83->slice(se282, h76));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry* e83;
         
          if (n83 && (e83 = n83->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e83->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e83->TOTAL_O_YEAR;
              DOUBLE_TYPE v83 = e83->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.addOrDelOnZero(se281.modify(mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(v83 * -1L)) : (void)0);
              n83 = n83->nxt;
            } while (n83 && (e83 = n83->obj) && h76 == n83->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey0_idxfn::equals(se282, *e83)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_0* i84 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.index[1]);
          const HASH_RES_t h77 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey0_idxfn::hash(se284.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_0::IdxNode* n84 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_0::IdxNode*>(i84->slice(se284, h77));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry* e84;
         
          if (n84 && (e84 = n84->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomer1_msuppliersupplier_suppkey = e84->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e84->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e84->TOTAL_O_YEAR;
              DOUBLE_TYPE v84 = e84->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.addOrDelOnZero(se283.modify(mkt_share_mpart1_l2_1_l1_1_mcustomer1_msuppliersupplier_suppkey,mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(v84 * -1L)) : (void)0);
              n84 = n84->nxt;
            } while (n84 && (e84 = n84->obj) && h77 == n84->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey0_idxfn::equals(se284, *e84)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_0* i85 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.index[1]);
          const HASH_RES_t h78 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey0_idxfn::hash(se286.modify0(part_partkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_0::IdxNode* n85 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_0::IdxNode*>(i85->slice(se286, h78));
          MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry* e85;
         
          if (n85 && (e85 = n85->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey = e85->MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIERSUPPLIER_SUPPKEY;
              long total_o_year = e85->TOTAL_O_YEAR;
              DOUBLE_TYPE v85 = e85->__av;
              (/*if */(part_type == c3) ? MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.addOrDelOnZero(se285.modify(mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey,total_o_year),(v85 * -1L)) : (void)0);
              n85 = n85->nxt;
            } while (n85 && (e85 = n85->obj) && h78 == n85->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey0_idxfn::equals(se286, *e85)); 
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHARE_mPART1_map_0* i86 = static_cast<HashIndex_MKT_SHARE_mPART1_map_0*>(MKT_SHARE_mPART1.index[0]);
          HashIndex_MKT_SHARE_mPART1_map_0::IdxNode* n86; 
          MKT_SHARE_mPART1_entry* e86;
        
          for (size_t i = 0; i < i86->size_; i++)
          {
            n86 = i86->buckets_ + i;
            while (n86 && (e86 = n86->obj))
            {
                date o_orderdate = e86->O_ORDERDATE;
                DOUBLE_TYPE v86 = e86->__av;
                long l44 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg16 = 0.0;
                DOUBLE_TYPE l46 = MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se288.modify(l44));
                agg16 += Ulistmax(1L, l46);
                DOUBLE_TYPE l45 = agg16;
                MKT_SHARE.addOrDelOnZero(se287.modify(l44),(v86 * Udiv(l45)));
              n86 = n86->nxt;
            }
          }
        }
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  //++tN;
        MKT_SHARE_mORDERS1_L2_1_L1_4.addOrDelOnZero(se289.modify(customer_custkey),MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se290.modify(customer_nationkey)));
        { //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_map_0* i87 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1.index[1]);
          const HASH_RES_t h79 = MKT_SHARE_mPART1_mCUSTOMER1_mapkey0_idxfn::hash(se293.modify0(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_map_0::IdxNode* n87 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_map_0::IdxNode*>(i87->slice(se293, h79));
          MKT_SHARE_mPART1_mCUSTOMER1_entry* e87;
         
          if (n87 && (e87 = n87->obj)) {
            do {                
              date o_orderdate = e87->O_ORDERDATE;
              DOUBLE_TYPE v87 = e87->__av;
              MKT_SHARE_mPART1.addOrDelOnZero(se291.modify(o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se292.modify(customer_nationkey)) * v87));
              n87 = n87->nxt;
            } while (n87 && (e87 = n87->obj) && h79 == n87->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mapkey0_idxfn::equals(se293, *e87)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_1* i88 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_1*>(MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index[2]);
          const HASH_RES_t h80 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn::hash(se296.modify1(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_1::IdxNode* n88 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_1::IdxNode*>(i88->slice(se296, h80));
          MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry* e88;
         
          if (n88 && (e88 = n88->obj)) {
            do {                
              long mkt_share_mpart1_mlineitemlineitem_orderkey = e88->MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
              date o_orderdate = e88->O_ORDERDATE;
              long v88 = e88->__av;
              MKT_SHARE_mPART1_mLINEITEM3.addOrDelOnZero(se294.modify(mkt_share_mpart1_mlineitemlineitem_orderkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se295.modify(customer_nationkey)) * v88));
              n88 = n88->nxt;
            } while (n88 && (e88 = n88->obj) && h80 == n88->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn::equals(se296, *e88)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_1* i89 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_1*>(MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.index[1]);
          const HASH_RES_t h81 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn::hash(se299.modify1(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_1::IdxNode* n89 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_1::IdxNode*>(i89->slice(se299, h81));
          MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry* e89;
         
          if (n89 && (e89 = n89->obj)) {
            do {                
              long mkt_share_mpart1_msuppliersupplier_suppkey = e89->MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              date o_orderdate = e89->O_ORDERDATE;
              DOUBLE_TYPE v89 = e89->__av;
              MKT_SHARE_mPART1_mSUPPLIER2.addOrDelOnZero(se297.modify(mkt_share_mpart1_msuppliersupplier_suppkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se298.modify(customer_nationkey)) * v89));
              n89 = n89->nxt;
            } while (n89 && (e89 = n89->obj) && h81 == n89->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn::equals(se299, *e89)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_2* i90 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_2*>(MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.index[2]);
          const HASH_RES_t h82 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey2_idxfn::hash(se302.modify2(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_2::IdxNode* n90 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_2::IdxNode*>(i90->slice(se302, h82));
          MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry* e90;
         
          if (n90 && (e90 = n90->obj)) {
            do {                
              long mkt_share_mpart1_msupplier2_mpartpart_partkey = e90->MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY;
              long mkt_share_mpart1_msuppliersupplier_suppkey = e90->MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              date o_orderdate = e90->O_ORDERDATE;
              DOUBLE_TYPE v90 = e90->__av;
              MKT_SHARE_mPART1_mSUPPLIER2_mPART2.addOrDelOnZero(se300.modify(mkt_share_mpart1_msupplier2_mpartpart_partkey,mkt_share_mpart1_msuppliersupplier_suppkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se301.modify(customer_nationkey)) * v90));
              n90 = n90->nxt;
            } while (n90 && (e90 = n90->obj) && h82 == n90->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey2_idxfn::equals(se302, *e90)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_1* i91 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_1*>(MKT_SHARE_mPART1_mCUSTOMER1_mPART2.index[2]);
          const HASH_RES_t h83 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey1_idxfn::hash(se305.modify1(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_1::IdxNode* n91 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_1::IdxNode*>(i91->slice(se305, h83));
          MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry* e91;
         
          if (n91 && (e91 = n91->obj)) {
            do {                
              long mkt_share_mpart1_mpartpart_partkey = e91->MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY;
              date o_orderdate = e91->O_ORDERDATE;
              DOUBLE_TYPE v91 = e91->__av;
              MKT_SHARE_mPART1_mPART2.addOrDelOnZero(se303.modify(mkt_share_mpart1_mpartpart_partkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se304.modify(customer_nationkey)) * v91));
              n91 = n91->nxt;
            } while (n91 && (e91 = n91->obj) && h83 == n91->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey1_idxfn::equals(se305, *e91)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_map_0* i92 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.index[1]);
          const HASH_RES_t h84 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mapkey0_idxfn::hash(se308.modify0(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_map_0::IdxNode* n92 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_map_0::IdxNode*>(i92->slice(se308, h84));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry* e92;
         
          if (n92 && (e92 = n92->obj)) {
            do {                
              long total_o_year = e92->TOTAL_O_YEAR;
              DOUBLE_TYPE v92 = e92->__av;
              MKT_SHARE_mPART1_L2_1_L1_1.addOrDelOnZero(se306.modify(total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se307.modify(customer_nationkey)) * v92));
              n92 = n92->nxt;
            } while (n92 && (e92 = n92->obj) && h84 == n92->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mapkey0_idxfn::equals(se308, *e92)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_1* i93 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_1*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index[2]);
          const HASH_RES_t h85 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn::hash(se311.modify1(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_1::IdxNode* n93 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_1::IdxNode*>(i93->slice(se311, h85));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry* e93;
         
          if (n93 && (e93 = n93->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mlineitemlineitem_orderkey = e93->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
              long total_o_year = e93->TOTAL_O_YEAR;
              long v93 = e93->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.addOrDelOnZero(se309.modify(mkt_share_mpart1_l2_1_l1_1_mlineitemlineitem_orderkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se310.modify(customer_nationkey)) * v93));
              n93 = n93->nxt;
            } while (n93 && (e93 = n93->obj) && h85 == n93->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn::equals(se311, *e93)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_1* i94 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_1*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.index[1]);
          const HASH_RES_t h86 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey1_idxfn::hash(se314.modify1(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_1::IdxNode* n94 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_1::IdxNode*>(i94->slice(se314, h86));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry* e94;
         
          if (n94 && (e94 = n94->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey = e94->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              long total_o_year = e94->TOTAL_O_YEAR;
              DOUBLE_TYPE v94 = e94->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.addOrDelOnZero(se312.modify(mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se313.modify(customer_nationkey)) * v94));
              n94 = n94->nxt;
            } while (n94 && (e94 = n94->obj) && h86 == n94->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey1_idxfn::equals(se314, *e94)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_2* i95 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_2*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.index[2]);
          const HASH_RES_t h87 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey2_idxfn::hash(se317.modify2(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_2::IdxNode* n95 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_2::IdxNode*>(i95->slice(se317, h87));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry* e95;
         
          if (n95 && (e95 = n95->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_msupplier1_mpartpart_partkey = e95->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY;
              long mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey = e95->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              long total_o_year = e95->TOTAL_O_YEAR;
              DOUBLE_TYPE v95 = e95->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.addOrDelOnZero(se315.modify(mkt_share_mpart1_l2_1_l1_1_msupplier1_mpartpart_partkey,mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se316.modify(customer_nationkey)) * v95));
              n95 = n95->nxt;
            } while (n95 && (e95 = n95->obj) && h87 == n95->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey2_idxfn::equals(se317, *e95)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_1* i96 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_1*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.index[2]);
          const HASH_RES_t h88 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey1_idxfn::hash(se320.modify1(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_1::IdxNode* n96 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_1::IdxNode*>(i96->slice(se320, h88));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry* e96;
         
          if (n96 && (e96 = n96->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mpartpart_partkey = e96->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY;
              long total_o_year = e96->TOTAL_O_YEAR;
              DOUBLE_TYPE v96 = e96->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mPART2.addOrDelOnZero(se318.modify(mkt_share_mpart1_l2_1_l1_1_mpartpart_partkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se319.modify(customer_nationkey)) * v96));
              n96 = n96->nxt;
            } while (n96 && (e96 = n96->obj) && h88 == n96->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey1_idxfn::equals(se320, *e96)); 
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHARE_mPART1_map_0* i97 = static_cast<HashIndex_MKT_SHARE_mPART1_map_0*>(MKT_SHARE_mPART1.index[0]);
          HashIndex_MKT_SHARE_mPART1_map_0::IdxNode* n97; 
          MKT_SHARE_mPART1_entry* e97;
        
          for (size_t i = 0; i < i97->size_; i++)
          {
            n97 = i97->buckets_ + i;
            while (n97 && (e97 = n97->obj))
            {
                date o_orderdate = e97->O_ORDERDATE;
                DOUBLE_TYPE v97 = e97->__av;
                long l47 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg17 = 0.0;
                DOUBLE_TYPE l49 = MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se322.modify(l47));
                agg17 += Ulistmax(1L, l49);
                DOUBLE_TYPE l48 = agg17;
                MKT_SHARE.addOrDelOnZero(se321.modify(l47),(v97 * Udiv(l48)));
              n97 = n97->nxt;
            }
          }
        }
      }
    }
    void on_delete_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  //++tN;
        MKT_SHARE_mORDERS1_L2_1_L1_4.addOrDelOnZero(se323.modify(customer_custkey),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se324.modify(customer_nationkey)) * -1L));
        { //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_map_0* i98 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1.index[1]);
          const HASH_RES_t h89 = MKT_SHARE_mPART1_mCUSTOMER1_mapkey0_idxfn::hash(se327.modify0(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_map_0::IdxNode* n98 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_map_0::IdxNode*>(i98->slice(se327, h89));
          MKT_SHARE_mPART1_mCUSTOMER1_entry* e98;
         
          if (n98 && (e98 = n98->obj)) {
            do {                
              date o_orderdate = e98->O_ORDERDATE;
              DOUBLE_TYPE v98 = e98->__av;
              MKT_SHARE_mPART1.addOrDelOnZero(se325.modify(o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se326.modify(customer_nationkey)) * (v98 * -1L)));
              n98 = n98->nxt;
            } while (n98 && (e98 = n98->obj) && h89 == n98->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mapkey0_idxfn::equals(se327, *e98)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_1* i99 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_1*>(MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index[2]);
          const HASH_RES_t h90 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn::hash(se330.modify1(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_1::IdxNode* n99 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map_1::IdxNode*>(i99->slice(se330, h90));
          MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry* e99;
         
          if (n99 && (e99 = n99->obj)) {
            do {                
              long mkt_share_mpart1_mlineitemlineitem_orderkey = e99->MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
              date o_orderdate = e99->O_ORDERDATE;
              long v99 = e99->__av;
              MKT_SHARE_mPART1_mLINEITEM3.addOrDelOnZero(se328.modify(mkt_share_mpart1_mlineitemlineitem_orderkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se329.modify(customer_nationkey)) * (v99 * -1L)));
              n99 = n99->nxt;
            } while (n99 && (e99 = n99->obj) && h90 == n99->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn::equals(se330, *e99)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_1* i100 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_1*>(MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.index[1]);
          const HASH_RES_t h91 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn::hash(se333.modify1(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_1::IdxNode* n100 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_1::IdxNode*>(i100->slice(se333, h91));
          MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry* e100;
         
          if (n100 && (e100 = n100->obj)) {
            do {                
              long mkt_share_mpart1_msuppliersupplier_suppkey = e100->MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              date o_orderdate = e100->O_ORDERDATE;
              DOUBLE_TYPE v100 = e100->__av;
              MKT_SHARE_mPART1_mSUPPLIER2.addOrDelOnZero(se331.modify(mkt_share_mpart1_msuppliersupplier_suppkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se332.modify(customer_nationkey)) * (v100 * -1L)));
              n100 = n100->nxt;
            } while (n100 && (e100 = n100->obj) && h91 == n100->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn::equals(se333, *e100)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_2* i101 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_2*>(MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.index[2]);
          const HASH_RES_t h92 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey2_idxfn::hash(se336.modify2(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_2::IdxNode* n101 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_2::IdxNode*>(i101->slice(se336, h92));
          MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry* e101;
         
          if (n101 && (e101 = n101->obj)) {
            do {                
              long mkt_share_mpart1_msupplier2_mpartpart_partkey = e101->MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY;
              long mkt_share_mpart1_msuppliersupplier_suppkey = e101->MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              date o_orderdate = e101->O_ORDERDATE;
              DOUBLE_TYPE v101 = e101->__av;
              MKT_SHARE_mPART1_mSUPPLIER2_mPART2.addOrDelOnZero(se334.modify(mkt_share_mpart1_msupplier2_mpartpart_partkey,mkt_share_mpart1_msuppliersupplier_suppkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se335.modify(customer_nationkey)) * (v101 * -1L)));
              n101 = n101->nxt;
            } while (n101 && (e101 = n101->obj) && h92 == n101->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey2_idxfn::equals(se336, *e101)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_1* i102 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_1*>(MKT_SHARE_mPART1_mCUSTOMER1_mPART2.index[2]);
          const HASH_RES_t h93 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey1_idxfn::hash(se339.modify1(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_1::IdxNode* n102 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map_1::IdxNode*>(i102->slice(se339, h93));
          MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry* e102;
         
          if (n102 && (e102 = n102->obj)) {
            do {                
              long mkt_share_mpart1_mpartpart_partkey = e102->MKT_SHARE_mPART1_mCUSTOMER1_mPARTPART_PARTKEY;
              date o_orderdate = e102->O_ORDERDATE;
              DOUBLE_TYPE v102 = e102->__av;
              MKT_SHARE_mPART1_mPART2.addOrDelOnZero(se337.modify(mkt_share_mpart1_mpartpart_partkey,o_orderdate),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se338.modify(customer_nationkey)) * (v102 * -1L)));
              n102 = n102->nxt;
            } while (n102 && (e102 = n102->obj) && h93 == n102->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mPART2_mapkey1_idxfn::equals(se339, *e102)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_map_0* i103 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.index[1]);
          const HASH_RES_t h94 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mapkey0_idxfn::hash(se342.modify0(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_map_0::IdxNode* n103 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_map_0::IdxNode*>(i103->slice(se342, h94));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry* e103;
         
          if (n103 && (e103 = n103->obj)) {
            do {                
              long total_o_year = e103->TOTAL_O_YEAR;
              DOUBLE_TYPE v103 = e103->__av;
              MKT_SHARE_mPART1_L2_1_L1_1.addOrDelOnZero(se340.modify(total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se341.modify(customer_nationkey)) * (v103 * -1L)));
              n103 = n103->nxt;
            } while (n103 && (e103 = n103->obj) && h94 == n103->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mapkey0_idxfn::equals(se342, *e103)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_1* i104 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_1*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index[2]);
          const HASH_RES_t h95 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn::hash(se345.modify1(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_1::IdxNode* n104 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map_1::IdxNode*>(i104->slice(se345, h95));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry* e104;
         
          if (n104 && (e104 = n104->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mlineitemlineitem_orderkey = e104->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
              long total_o_year = e104->TOTAL_O_YEAR;
              long v104 = e104->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.addOrDelOnZero(se343.modify(mkt_share_mpart1_l2_1_l1_1_mlineitemlineitem_orderkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se344.modify(customer_nationkey)) * (v104 * -1L)));
              n104 = n104->nxt;
            } while (n104 && (e104 = n104->obj) && h95 == n104->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_mapkey1_idxfn::equals(se345, *e104)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_1* i105 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_1*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.index[1]);
          const HASH_RES_t h96 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey1_idxfn::hash(se348.modify1(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_1::IdxNode* n105 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_1::IdxNode*>(i105->slice(se348, h96));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry* e105;
         
          if (n105 && (e105 = n105->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey = e105->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              long total_o_year = e105->TOTAL_O_YEAR;
              DOUBLE_TYPE v105 = e105->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.addOrDelOnZero(se346.modify(mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se347.modify(customer_nationkey)) * (v105 * -1L)));
              n105 = n105->nxt;
            } while (n105 && (e105 = n105->obj) && h96 == n105->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey1_idxfn::equals(se348, *e105)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_2* i106 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_2*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.index[2]);
          const HASH_RES_t h97 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey2_idxfn::hash(se351.modify2(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_2::IdxNode* n106 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_2::IdxNode*>(i106->slice(se351, h97));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry* e106;
         
          if (n106 && (e106 = n106->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_msupplier1_mpartpart_partkey = e106->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY;
              long mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey = e106->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              long total_o_year = e106->TOTAL_O_YEAR;
              DOUBLE_TYPE v106 = e106->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.addOrDelOnZero(se349.modify(mkt_share_mpart1_l2_1_l1_1_msupplier1_mpartpart_partkey,mkt_share_mpart1_l2_1_l1_1_msuppliersupplier_suppkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se350.modify(customer_nationkey)) * (v106 * -1L)));
              n106 = n106->nxt;
            } while (n106 && (e106 = n106->obj) && h97 == n106->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey2_idxfn::equals(se351, *e106)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_1* i107 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_1*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.index[2]);
          const HASH_RES_t h98 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey1_idxfn::hash(se354.modify1(customer_custkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_1::IdxNode* n107 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map_1::IdxNode*>(i107->slice(se354, h98));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry* e107;
         
          if (n107 && (e107 = n107->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mpartpart_partkey = e107->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPARTPART_PARTKEY;
              long total_o_year = e107->TOTAL_O_YEAR;
              DOUBLE_TYPE v107 = e107->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mPART2.addOrDelOnZero(se352.modify(mkt_share_mpart1_l2_1_l1_1_mpartpart_partkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.getValueOrDefault(se353.modify(customer_nationkey)) * (v107 * -1L)));
              n107 = n107->nxt;
            } while (n107 && (e107 = n107->obj) && h98 == n107->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_mapkey1_idxfn::equals(se354, *e107)); 
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHARE_mPART1_map_0* i108 = static_cast<HashIndex_MKT_SHARE_mPART1_map_0*>(MKT_SHARE_mPART1.index[0]);
          HashIndex_MKT_SHARE_mPART1_map_0::IdxNode* n108; 
          MKT_SHARE_mPART1_entry* e108;
        
          for (size_t i = 0; i < i108->size_; i++)
          {
            n108 = i108->buckets_ + i;
            while (n108 && (e108 = n108->obj))
            {
                date o_orderdate = e108->O_ORDERDATE;
                DOUBLE_TYPE v108 = e108->__av;
                long l50 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg18 = 0.0;
                DOUBLE_TYPE l52 = MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se356.modify(l50));
                agg18 += Ulistmax(1L, l52);
                DOUBLE_TYPE l51 = agg18;
                MKT_SHARE.addOrDelOnZero(se355.modify(l50),(v108 * Udiv(l51)));
              n108 = n108->nxt;
            }
          }
        }
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1* i109 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index[2]);
          const HASH_RES_t h99 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey1_idxfn::hash(se359.modify1(supplier_suppkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1::IdxNode* n109 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1::IdxNode*>(i109->slice(se359, h99));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry* e109;
         
          if (n109 && (e109 = n109->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e109->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v109 = e109->__av;
              MKT_SHARE_mORDERS1_L2_1_L1_5.addOrDelOnZero(se357.modify(mkt_share_mordersorders_orderkey),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se358.modify(supplier_nationkey)) * v109));
              n109 = n109->nxt;
            } while (n109 && (e109 = n109->obj) && h99 == n109->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey1_idxfn::equals(se359, *e109)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2* i110 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[3]);
          const HASH_RES_t h100 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey2_idxfn::hash(se362.modify2(supplier_suppkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2::IdxNode* n110 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2::IdxNode*>(i110->slice(se362, h100));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e110;
         
          if (n110 && (e110 = n110->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e110->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              long mkt_share_morders1_l2_1_l1_5_mpartpart_partkey = e110->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
              DOUBLE_TYPE v110 = e110->__av;
              MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.addOrDelOnZero(se360.modify(mkt_share_mordersorders_orderkey,mkt_share_morders1_l2_1_l1_5_mpartpart_partkey),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se361.modify(supplier_nationkey)) * v110));
              n110 = n110->nxt;
            } while (n110 && (e110 = n110->obj) && h100 == n110->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey2_idxfn::equals(se362, *e110)); 
          }
        }MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.addOrDelOnZero(se363.modify(supplier_suppkey),MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se364.modify(supplier_nationkey)));
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1* i111 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index[2]);
          const HASH_RES_t h101 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey1_idxfn::hash(se367.modify1(supplier_suppkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1::IdxNode* n111 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1::IdxNode*>(i111->slice(se367, h101));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry* e111;
         
          if (n111 && (e111 = n111->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e111->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v111 = e111->__av;
              MKT_SHARE_mORDERS6.addOrDelOnZero(se365.modify(mkt_share_mordersorders_orderkey),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se366.modify(supplier_nationkey)) * v111));
              n111 = n111->nxt;
            } while (n111 && (e111 = n111->obj) && h101 == n111->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey1_idxfn::equals(se367, *e111)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2* i112 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[3]);
          const HASH_RES_t h102 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey2_idxfn::hash(se370.modify2(supplier_suppkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2::IdxNode* n112 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2::IdxNode*>(i112->slice(se370, h102));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e112;
         
          if (n112 && (e112 = n112->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e112->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              long mkt_share_morders6_mpartpart_partkey = e112->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
              DOUBLE_TYPE v112 = e112->__av;
              MKT_SHARE_mORDERS6_mPART2.addOrDelOnZero(se368.modify(mkt_share_mordersorders_orderkey,mkt_share_morders6_mpartpart_partkey),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se369.modify(supplier_nationkey)) * v112));
              n112 = n112->nxt;
            } while (n112 && (e112 = n112->obj) && h102 == n112->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey2_idxfn::equals(se370, *e112)); 
          }
        }MKT_SHARE_mORDERS6_mLINEITEM1.addOrDelOnZero(se371.modify(supplier_suppkey),MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se372.modify(supplier_nationkey)));
        { //slice 
          const HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_map_0* i113 = static_cast<HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_map_0*>(MKT_SHARE_mPART1_mSUPPLIER2.index[1]);
          const HASH_RES_t h103 = MKT_SHARE_mPART1_mSUPPLIER2_mapkey0_idxfn::hash(se375.modify0(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_map_0::IdxNode* n113 = static_cast<HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_map_0::IdxNode*>(i113->slice(se375, h103));
          MKT_SHARE_mPART1_mSUPPLIER2_entry* e113;
         
          if (n113 && (e113 = n113->obj)) {
            do {                
              date o_orderdate = e113->O_ORDERDATE;
              DOUBLE_TYPE v113 = e113->__av;
              MKT_SHARE_mPART1.addOrDelOnZero(se373.modify(o_orderdate),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se374.modify(supplier_nationkey)) * v113));
              n113 = n113->nxt;
            } while (n113 && (e113 = n113->obj) && h103 == n113->hash &&  MKT_SHARE_mPART1_mSUPPLIER2_mapkey0_idxfn::equals(se375, *e113)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_0* i114 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.index[2]);
          const HASH_RES_t h104 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn::hash(se378.modify0(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_0::IdxNode* n114 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_0::IdxNode*>(i114->slice(se378, h104));
          MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry* e114;
         
          if (n114 && (e114 = n114->obj)) {
            do {                
              long mkt_share_mpart1_mcustomercustomer_custkey = e114->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e114->O_ORDERDATE;
              DOUBLE_TYPE v114 = e114->__av;
              MKT_SHARE_mPART1_mCUSTOMER1.addOrDelOnZero(se376.modify(mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se377.modify(supplier_nationkey)) * v114));
              n114 = n114->nxt;
            } while (n114 && (e114 = n114->obj) && h104 == n114->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn::equals(se378, *e114)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_1* i115 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_1*>(MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.index[3]);
          const HASH_RES_t h105 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey1_idxfn::hash(se381.modify1(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_1::IdxNode* n115 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_1::IdxNode*>(i115->slice(se381, h105));
          MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry* e115;
         
          if (n115 && (e115 = n115->obj)) {
            do {                
              long mkt_share_mpart1_mcustomer1_mpartpart_partkey = e115->MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY;
              long mkt_share_mpart1_mcustomercustomer_custkey = e115->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e115->O_ORDERDATE;
              DOUBLE_TYPE v115 = e115->__av;
              MKT_SHARE_mPART1_mCUSTOMER1_mPART2.addOrDelOnZero(se379.modify(mkt_share_mpart1_mcustomer1_mpartpart_partkey,mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se380.modify(supplier_nationkey)) * v115));
              n115 = n115->nxt;
            } while (n115 && (e115 = n115->obj) && h105 == n115->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey1_idxfn::equals(se381, *e115)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_1* i116 = static_cast<HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_1*>(MKT_SHARE_mPART1_mSUPPLIER2_mPART2.index[2]);
          const HASH_RES_t h106 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey1_idxfn::hash(se384.modify1(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_1::IdxNode* n116 = static_cast<HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_1::IdxNode*>(i116->slice(se384, h106));
          MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry* e116;
         
          if (n116 && (e116 = n116->obj)) {
            do {                
              long mkt_share_mpart1_mpartpart_partkey = e116->MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY;
              date o_orderdate = e116->O_ORDERDATE;
              DOUBLE_TYPE v116 = e116->__av;
              MKT_SHARE_mPART1_mPART2.addOrDelOnZero(se382.modify(mkt_share_mpart1_mpartpart_partkey,o_orderdate),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se383.modify(supplier_nationkey)) * v116));
              n116 = n116->nxt;
            } while (n116 && (e116 = n116->obj) && h106 == n116->hash &&  MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey1_idxfn::equals(se384, *e116)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_map_0* i117 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.index[1]);
          const HASH_RES_t h107 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mapkey0_idxfn::hash(se387.modify0(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_map_0::IdxNode* n117 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_map_0::IdxNode*>(i117->slice(se387, h107));
          MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry* e117;
         
          if (n117 && (e117 = n117->obj)) {
            do {                
              long total_o_year = e117->TOTAL_O_YEAR;
              DOUBLE_TYPE v117 = e117->__av;
              MKT_SHARE_mPART1_L2_1_L1_1.addOrDelOnZero(se385.modify(total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se386.modify(supplier_nationkey)) * v117));
              n117 = n117->nxt;
            } while (n117 && (e117 = n117->obj) && h107 == n117->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mapkey0_idxfn::equals(se387, *e117)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_0* i118 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.index[2]);
          const HASH_RES_t h108 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey0_idxfn::hash(se390.modify0(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_0::IdxNode* n118 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_0::IdxNode*>(i118->slice(se390, h108));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry* e118;
         
          if (n118 && (e118 = n118->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e118->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e118->TOTAL_O_YEAR;
              DOUBLE_TYPE v118 = e118->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.addOrDelOnZero(se388.modify(mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se389.modify(supplier_nationkey)) * v118));
              n118 = n118->nxt;
            } while (n118 && (e118 = n118->obj) && h108 == n118->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey0_idxfn::equals(se390, *e118)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_1* i119 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_1*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.index[3]);
          const HASH_RES_t h109 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey1_idxfn::hash(se393.modify1(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_1::IdxNode* n119 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_1::IdxNode*>(i119->slice(se393, h109));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry* e119;
         
          if (n119 && (e119 = n119->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomer1_mpartpart_partkey = e119->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY;
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e119->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e119->TOTAL_O_YEAR;
              DOUBLE_TYPE v119 = e119->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.addOrDelOnZero(se391.modify(mkt_share_mpart1_l2_1_l1_1_mcustomer1_mpartpart_partkey,mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se392.modify(supplier_nationkey)) * v119));
              n119 = n119->nxt;
            } while (n119 && (e119 = n119->obj) && h109 == n119->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey1_idxfn::equals(se393, *e119)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_1* i120 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_1*>(MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.index[2]);
          const HASH_RES_t h110 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey1_idxfn::hash(se396.modify1(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_1::IdxNode* n120 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_1::IdxNode*>(i120->slice(se396, h110));
          MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry* e120;
         
          if (n120 && (e120 = n120->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mpartpart_partkey = e120->MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY;
              long total_o_year = e120->TOTAL_O_YEAR;
              DOUBLE_TYPE v120 = e120->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mPART2.addOrDelOnZero(se394.modify(mkt_share_mpart1_l2_1_l1_1_mpartpart_partkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se395.modify(supplier_nationkey)) * v120));
              n120 = n120->nxt;
            } while (n120 && (e120 = n120->obj) && h110 == n120->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey1_idxfn::equals(se396, *e120)); 
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHARE_mPART1_map_0* i121 = static_cast<HashIndex_MKT_SHARE_mPART1_map_0*>(MKT_SHARE_mPART1.index[0]);
          HashIndex_MKT_SHARE_mPART1_map_0::IdxNode* n121; 
          MKT_SHARE_mPART1_entry* e121;
        
          for (size_t i = 0; i < i121->size_; i++)
          {
            n121 = i121->buckets_ + i;
            while (n121 && (e121 = n121->obj))
            {
                date o_orderdate = e121->O_ORDERDATE;
                DOUBLE_TYPE v121 = e121->__av;
                long l53 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg19 = 0.0;
                DOUBLE_TYPE l55 = MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se398.modify(l53));
                agg19 += Ulistmax(1L, l55);
                DOUBLE_TYPE l54 = agg19;
                MKT_SHARE.addOrDelOnZero(se397.modify(l53),(v121 * Udiv(l54)));
              n121 = n121->nxt;
            }
          }
        }
      }
    }
    void on_delete_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1* i122 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index[2]);
          const HASH_RES_t h111 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey1_idxfn::hash(se401.modify1(supplier_suppkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1::IdxNode* n122 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1::IdxNode*>(i122->slice(se401, h111));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry* e122;
         
          if (n122 && (e122 = n122->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e122->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v122 = e122->__av;
              MKT_SHARE_mORDERS1_L2_1_L1_5.addOrDelOnZero(se399.modify(mkt_share_mordersorders_orderkey),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se400.modify(supplier_nationkey)) * (v122 * -1L)));
              n122 = n122->nxt;
            } while (n122 && (e122 = n122->obj) && h111 == n122->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey1_idxfn::equals(se401, *e122)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2* i123 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[3]);
          const HASH_RES_t h112 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey2_idxfn::hash(se404.modify2(supplier_suppkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2::IdxNode* n123 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2::IdxNode*>(i123->slice(se404, h112));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e123;
         
          if (n123 && (e123 = n123->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e123->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              long mkt_share_morders1_l2_1_l1_5_mpartpart_partkey = e123->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
              DOUBLE_TYPE v123 = e123->__av;
              MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.addOrDelOnZero(se402.modify(mkt_share_mordersorders_orderkey,mkt_share_morders1_l2_1_l1_5_mpartpart_partkey),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se403.modify(supplier_nationkey)) * (v123 * -1L)));
              n123 = n123->nxt;
            } while (n123 && (e123 = n123->obj) && h112 == n123->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey2_idxfn::equals(se404, *e123)); 
          }
        }MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.addOrDelOnZero(se405.modify(supplier_suppkey),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se406.modify(supplier_nationkey)) * -1L));
        { //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1* i124 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index[2]);
          const HASH_RES_t h113 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey1_idxfn::hash(se409.modify1(supplier_suppkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1::IdxNode* n124 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map_1::IdxNode*>(i124->slice(se409, h113));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry* e124;
         
          if (n124 && (e124 = n124->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e124->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              DOUBLE_TYPE v124 = e124->__av;
              MKT_SHARE_mORDERS6.addOrDelOnZero(se407.modify(mkt_share_mordersorders_orderkey),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se408.modify(supplier_nationkey)) * (v124 * -1L)));
              n124 = n124->nxt;
            } while (n124 && (e124 = n124->obj) && h113 == n124->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mapkey1_idxfn::equals(se409, *e124)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2* i125 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2*>(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index[3]);
          const HASH_RES_t h114 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey2_idxfn::hash(se412.modify2(supplier_suppkey));
          HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2::IdxNode* n125 = static_cast<HashIndex_MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map_2::IdxNode*>(i125->slice(se412, h114));
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry* e125;
         
          if (n125 && (e125 = n125->obj)) {
            do {                
              long mkt_share_mordersorders_orderkey = e125->MKT_SHARE_mORDERSORDERS_ORDERKEY;
              long mkt_share_morders6_mpartpart_partkey = e125->MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPARTPART_PARTKEY;
              DOUBLE_TYPE v125 = e125->__av;
              MKT_SHARE_mORDERS6_mPART2.addOrDelOnZero(se410.modify(mkt_share_mordersorders_orderkey,mkt_share_morders6_mpartpart_partkey),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se411.modify(supplier_nationkey)) * (v125 * -1L)));
              n125 = n125->nxt;
            } while (n125 && (e125 = n125->obj) && h114 == n125->hash &&  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_mapkey2_idxfn::equals(se412, *e125)); 
          }
        }MKT_SHARE_mORDERS6_mLINEITEM1.addOrDelOnZero(se413.modify(supplier_suppkey),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se414.modify(supplier_nationkey)) * -1L));
        { //slice 
          const HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_map_0* i126 = static_cast<HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_map_0*>(MKT_SHARE_mPART1_mSUPPLIER2.index[1]);
          const HASH_RES_t h115 = MKT_SHARE_mPART1_mSUPPLIER2_mapkey0_idxfn::hash(se417.modify0(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_map_0::IdxNode* n126 = static_cast<HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_map_0::IdxNode*>(i126->slice(se417, h115));
          MKT_SHARE_mPART1_mSUPPLIER2_entry* e126;
         
          if (n126 && (e126 = n126->obj)) {
            do {                
              date o_orderdate = e126->O_ORDERDATE;
              DOUBLE_TYPE v126 = e126->__av;
              MKT_SHARE_mPART1.addOrDelOnZero(se415.modify(o_orderdate),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se416.modify(supplier_nationkey)) * (v126 * -1L)));
              n126 = n126->nxt;
            } while (n126 && (e126 = n126->obj) && h115 == n126->hash &&  MKT_SHARE_mPART1_mSUPPLIER2_mapkey0_idxfn::equals(se417, *e126)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_0* i127 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_0*>(MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.index[2]);
          const HASH_RES_t h116 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn::hash(se420.modify0(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_0::IdxNode* n127 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map_0::IdxNode*>(i127->slice(se420, h116));
          MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry* e127;
         
          if (n127 && (e127 = n127->obj)) {
            do {                
              long mkt_share_mpart1_mcustomercustomer_custkey = e127->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e127->O_ORDERDATE;
              DOUBLE_TYPE v127 = e127->__av;
              MKT_SHARE_mPART1_mCUSTOMER1.addOrDelOnZero(se418.modify(mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se419.modify(supplier_nationkey)) * (v127 * -1L)));
              n127 = n127->nxt;
            } while (n127 && (e127 = n127->obj) && h116 == n127->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn::equals(se420, *e127)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_1* i128 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_1*>(MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.index[3]);
          const HASH_RES_t h117 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey1_idxfn::hash(se423.modify1(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_1::IdxNode* n128 = static_cast<HashIndex_MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map_1::IdxNode*>(i128->slice(se423, h117));
          MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry* e128;
         
          if (n128 && (e128 = n128->obj)) {
            do {                
              long mkt_share_mpart1_mcustomer1_mpartpart_partkey = e128->MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPARTPART_PARTKEY;
              long mkt_share_mpart1_mcustomercustomer_custkey = e128->MKT_SHARE_mPART1_mCUSTOMERCUSTOMER_CUSTKEY;
              date o_orderdate = e128->O_ORDERDATE;
              DOUBLE_TYPE v128 = e128->__av;
              MKT_SHARE_mPART1_mCUSTOMER1_mPART2.addOrDelOnZero(se421.modify(mkt_share_mpart1_mcustomer1_mpartpart_partkey,mkt_share_mpart1_mcustomercustomer_custkey,o_orderdate),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se422.modify(supplier_nationkey)) * (v128 * -1L)));
              n128 = n128->nxt;
            } while (n128 && (e128 = n128->obj) && h117 == n128->hash &&  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_mapkey1_idxfn::equals(se423, *e128)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_1* i129 = static_cast<HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_1*>(MKT_SHARE_mPART1_mSUPPLIER2_mPART2.index[2]);
          const HASH_RES_t h118 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey1_idxfn::hash(se426.modify1(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_1::IdxNode* n129 = static_cast<HashIndex_MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map_1::IdxNode*>(i129->slice(se426, h118));
          MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry* e129;
         
          if (n129 && (e129 = n129->obj)) {
            do {                
              long mkt_share_mpart1_mpartpart_partkey = e129->MKT_SHARE_mPART1_mSUPPLIER2_mPARTPART_PARTKEY;
              date o_orderdate = e129->O_ORDERDATE;
              DOUBLE_TYPE v129 = e129->__av;
              MKT_SHARE_mPART1_mPART2.addOrDelOnZero(se424.modify(mkt_share_mpart1_mpartpart_partkey,o_orderdate),(MKT_SHARE_mORDERS6_mSUPPLIER1.getValueOrDefault(se425.modify(supplier_nationkey)) * (v129 * -1L)));
              n129 = n129->nxt;
            } while (n129 && (e129 = n129->obj) && h118 == n129->hash &&  MKT_SHARE_mPART1_mSUPPLIER2_mPART2_mapkey1_idxfn::equals(se426, *e129)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_map_0* i130 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.index[1]);
          const HASH_RES_t h119 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mapkey0_idxfn::hash(se429.modify0(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_map_0::IdxNode* n130 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_map_0::IdxNode*>(i130->slice(se429, h119));
          MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry* e130;
         
          if (n130 && (e130 = n130->obj)) {
            do {                
              long total_o_year = e130->TOTAL_O_YEAR;
              DOUBLE_TYPE v130 = e130->__av;
              MKT_SHARE_mPART1_L2_1_L1_1.addOrDelOnZero(se427.modify(total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se428.modify(supplier_nationkey)) * (v130 * -1L)));
              n130 = n130->nxt;
            } while (n130 && (e130 = n130->obj) && h119 == n130->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mapkey0_idxfn::equals(se429, *e130)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_0* i131 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_0*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.index[2]);
          const HASH_RES_t h120 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey0_idxfn::hash(se432.modify0(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_0::IdxNode* n131 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map_0::IdxNode*>(i131->slice(se432, h120));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry* e131;
         
          if (n131 && (e131 = n131->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e131->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e131->TOTAL_O_YEAR;
              DOUBLE_TYPE v131 = e131->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.addOrDelOnZero(se430.modify(mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se431.modify(supplier_nationkey)) * (v131 * -1L)));
              n131 = n131->nxt;
            } while (n131 && (e131 = n131->obj) && h120 == n131->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mapkey0_idxfn::equals(se432, *e131)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_1* i132 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_1*>(MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.index[3]);
          const HASH_RES_t h121 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey1_idxfn::hash(se435.modify1(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_1::IdxNode* n132 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map_1::IdxNode*>(i132->slice(se435, h121));
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry* e132;
         
          if (n132 && (e132 = n132->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mcustomer1_mpartpart_partkey = e132->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPARTPART_PARTKEY;
              long mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey = e132->MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMERCUSTOMER_CUSTKEY;
              long total_o_year = e132->TOTAL_O_YEAR;
              DOUBLE_TYPE v132 = e132->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.addOrDelOnZero(se433.modify(mkt_share_mpart1_l2_1_l1_1_mcustomer1_mpartpart_partkey,mkt_share_mpart1_l2_1_l1_1_mcustomercustomer_custkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se434.modify(supplier_nationkey)) * (v132 * -1L)));
              n132 = n132->nxt;
            } while (n132 && (e132 = n132->obj) && h121 == n132->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_mapkey1_idxfn::equals(se435, *e132)); 
          }
        }{ //slice 
          const HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_1* i133 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_1*>(MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.index[2]);
          const HASH_RES_t h122 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey1_idxfn::hash(se438.modify1(supplier_suppkey));
          HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_1::IdxNode* n133 = static_cast<HashIndex_MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map_1::IdxNode*>(i133->slice(se438, h122));
          MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry* e133;
         
          if (n133 && (e133 = n133->obj)) {
            do {                
              long mkt_share_mpart1_l2_1_l1_1_mpartpart_partkey = e133->MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPARTPART_PARTKEY;
              long total_o_year = e133->TOTAL_O_YEAR;
              DOUBLE_TYPE v133 = e133->__av;
              MKT_SHARE_mPART1_L2_1_L1_1_mPART2.addOrDelOnZero(se436.modify(mkt_share_mpart1_l2_1_l1_1_mpartpart_partkey,total_o_year),(MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.getValueOrDefault(se437.modify(supplier_nationkey)) * (v133 * -1L)));
              n133 = n133->nxt;
            } while (n133 && (e133 = n133->obj) && h122 == n133->hash &&  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_mapkey1_idxfn::equals(se438, *e133)); 
          }
        }MKT_SHARE.clear();
        {  // foreach
          const HashIndex_MKT_SHARE_mPART1_map_0* i134 = static_cast<HashIndex_MKT_SHARE_mPART1_map_0*>(MKT_SHARE_mPART1.index[0]);
          HashIndex_MKT_SHARE_mPART1_map_0::IdxNode* n134; 
          MKT_SHARE_mPART1_entry* e134;
        
          for (size_t i = 0; i < i134->size_; i++)
          {
            n134 = i134->buckets_ + i;
            while (n134 && (e134 = n134->obj))
            {
                date o_orderdate = e134->O_ORDERDATE;
                DOUBLE_TYPE v134 = e134->__av;
                long l56 = Uyear_part(o_orderdate);
                DOUBLE_TYPE agg20 = 0.0;
                DOUBLE_TYPE l58 = MKT_SHARE_mPART1_L2_1_L1_1.getValueOrDefault(se440.modify(l56));
                agg20 += Ulistmax(1L, l58);
                DOUBLE_TYPE l57 = agg20;
                MKT_SHARE.addOrDelOnZero(se439.modify(l56),(v134 * Udiv(l57)));
              n134 = n134->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  //
        MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.clear();
        STRING_TYPE l59 = c4;
        {  // foreach
          const HashIndex_NATION_map_0123* i135 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n135; 
          NATION_entry* e135;
        
          for (size_t i = 0; i < i135->size_; i++)
          {
            n135 = i135->buckets_ + i;
            while (n135 && (e135 = n135->obj))
            {
                long mkt_share_morders1_l2_1_l1_4_mcustomercustomer_nationkey = e135->NATION_NATIONKEY;
                STRING_TYPE n1_name = e135->NATION_NAME;
                long n1_regionkey = e135->NATION_REGIONKEY;
                STRING_TYPE n1_comment = e135->NATION_COMMENT;
                long v135 = e135->__av;
                { //slice 
                  const HashIndex_REGION_map_01* i136 = static_cast<HashIndex_REGION_map_01*>(REGION.index[1]);
                  const HASH_RES_t h123 = REGION_mapkey01_idxfn::hash(se442.modify01(n1_regionkey, l59));
                  HashIndex_REGION_map_01::IdxNode* n136 = static_cast<HashIndex_REGION_map_01::IdxNode*>(i136->slice(se442, h123));
                  REGION_entry* e136;
                 
                  if (n136 && (e136 = n136->obj)) {
                    do {                
                      STRING_TYPE r_comment = e136->REGION_COMMENT;
                      long v136 = e136->__av;
                      MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.addOrDelOnZero(se441.modify(mkt_share_morders1_l2_1_l1_4_mcustomercustomer_nationkey),(v135 * v136));
                      n136 = n136->nxt;
                    } while (n136 && (e136 = n136->obj) && h123 == n136->hash &&  REGION_mapkey01_idxfn::equals(se442, *e136)); 
                  }
                }
              n135 = n135->nxt;
            }
          }
        }MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.clear();
        {  // foreach
          const HashIndex_NATION_map_0123* i137 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n137; 
          NATION_entry* e137;
        
          for (size_t i = 0; i < i137->size_; i++)
          {
            n137 = i137->buckets_ + i;
            while (n137 && (e137 = n137->obj))
            {
                long mkt_share_morders1_l2_1_l1_5_msuppliersupplier_nationkey = e137->NATION_NATIONKEY;
                STRING_TYPE n2_name = e137->NATION_NAME;
                long n2_regionkey = e137->NATION_REGIONKEY;
                STRING_TYPE n2_comment = e137->NATION_COMMENT;
                long v137 = e137->__av;
                MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.addOrDelOnZero(se443.modify(mkt_share_morders1_l2_1_l1_5_msuppliersupplier_nationkey),v137);
              n137 = n137->nxt;
            }
          }
        }MKT_SHARE_mORDERS6_mSUPPLIER1.clear();
        STRING_TYPE l60 = c5;
        { //slice 
          const HashIndex_NATION_map_1* i138 = static_cast<HashIndex_NATION_map_1*>(NATION.index[1]);
          const HASH_RES_t h124 = NATION_mapkey1_idxfn::hash(se445.modify1(l60));
          HashIndex_NATION_map_1::IdxNode* n138 = static_cast<HashIndex_NATION_map_1::IdxNode*>(i138->slice(se445, h124));
          NATION_entry* e138;
         
          if (n138 && (e138 = n138->obj)) {
            do {                
              long mkt_share_morders6_msuppliersupplier_nationkey = e138->NATION_NATIONKEY;
              long n2_regionkey = e138->NATION_REGIONKEY;
              STRING_TYPE n2_comment = e138->NATION_COMMENT;
              long v138 = e138->__av;
              MKT_SHARE_mORDERS6_mSUPPLIER1.addOrDelOnZero(se444.modify(mkt_share_morders6_msuppliersupplier_nationkey),v138);
              n138 = n138->nxt;
            } while (n138 && (e138 = n138->obj) && h124 == n138->hash &&  NATION_mapkey1_idxfn::equals(se445, *e138)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se1;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se2;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se3;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se4;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se5;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se6;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry se7;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se8;
    MKT_SHARE_mORDERS6_entry se9;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se10;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se11;
    MKT_SHARE_mORDERS6_mPART2_entry se12;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se13;
    MKT_SHARE_mPART1_entry se14;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se15;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se16;
    MKT_SHARE_mPART1_mLINEITEM3_entry se17;
    MKT_SHARE_mPART1_mCUSTOMER1_entry se18;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se19;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se20;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry se21;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry se22;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se23;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry se24;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry se25;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry se26;
    MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry se27;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se28;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry se29;
    MKT_SHARE_mPART1_mSUPPLIER2_entry se30;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se31;
    MKT_SHARE_mPART1_mLINEITEM3_entry se32;
    MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry se33;
    MKT_SHARE_mPART1_mLINEITEM3_entry se34;
    MKT_SHARE_mPART1_mPART2_entry se35;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se36;
    MKT_SHARE_mPART1_mLINEITEM3_entry se37;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se38;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se39;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se40;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry se41;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry se42;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se43;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se44;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry se45;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry se46;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se47;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry se48;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry se49;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry se50;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry se51;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se52;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry se53;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry se54;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se55;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry se56;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry se57;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry se58;
    MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry se59;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se60;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry se61;
    MKT_SHARE_entry se62;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se63;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se64;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se65;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se66;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se67;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se68;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se69;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry se70;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se71;
    MKT_SHARE_mORDERS6_entry se72;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se73;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se74;
    MKT_SHARE_mORDERS6_mPART2_entry se75;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se76;
    MKT_SHARE_mPART1_entry se77;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se78;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se79;
    MKT_SHARE_mPART1_mLINEITEM3_entry se80;
    MKT_SHARE_mPART1_mCUSTOMER1_entry se81;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se82;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se83;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry se84;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry se85;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se86;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry se87;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry se88;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry se89;
    MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry se90;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se91;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry se92;
    MKT_SHARE_mPART1_mSUPPLIER2_entry se93;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se94;
    MKT_SHARE_mPART1_mLINEITEM3_entry se95;
    MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry se96;
    MKT_SHARE_mPART1_mLINEITEM3_entry se97;
    MKT_SHARE_mPART1_mPART2_entry se98;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se99;
    MKT_SHARE_mPART1_mLINEITEM3_entry se100;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se101;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se102;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se103;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry se104;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry se105;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se106;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se107;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry se108;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry se109;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se110;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry se111;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry se112;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry se113;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry se114;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se115;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry se116;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry se117;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se118;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry se119;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry se120;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry se121;
    MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry se122;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se123;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry se124;
    MKT_SHARE_entry se125;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se126;
    MKT_SHARE_entry se127;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se128;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se129;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se130;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se131;
    MKT_SHARE_mORDERS6_entry se132;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se133;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se134;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se135;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se136;
    MKT_SHARE_mPART1_entry se137;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se138;
    MKT_SHARE_mORDERS6_entry se139;
    MKT_SHARE_mPART1_mCUSTOMER1_entry se140;
    MKT_SHARE_mORDERS6_entry se141;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry se142;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry se143;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se144;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry se145;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se146;
    MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry se147;
    MKT_SHARE_mORDERS6_mPART2_entry se148;
    MKT_SHARE_mPART1_mLINEITEM3_entry se149;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se150;
    MKT_SHARE_mPART1_mSUPPLIER2_entry se151;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se152;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se153;
    MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry se154;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se155;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se156;
    MKT_SHARE_mPART1_mPART2_entry se157;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se158;
    MKT_SHARE_mORDERS6_mPART2_entry se159;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se160;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se161;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se162;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry se163;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se164;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry se165;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry se166;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se167;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry se168;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se169;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry se170;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry se171;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry se172;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se173;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry se174;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se175;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se176;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry se177;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se178;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se179;
    MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry se180;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se181;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry se182;
    MKT_SHARE_entry se183;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se184;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se185;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se186;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se187;
    MKT_SHARE_mORDERS6_entry se188;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se189;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se190;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se191;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se192;
    MKT_SHARE_mPART1_entry se193;
    MKT_SHARE_mORDERS6_entry se194;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se195;
    MKT_SHARE_mPART1_mCUSTOMER1_entry se196;
    MKT_SHARE_mORDERS6_entry se197;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry se198;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry se199;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se200;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry se201;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se202;
    MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry se203;
    MKT_SHARE_mORDERS6_mPART2_entry se204;
    MKT_SHARE_mPART1_mLINEITEM3_entry se205;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se206;
    MKT_SHARE_mPART1_mSUPPLIER2_entry se207;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se208;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se209;
    MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry se210;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se211;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se212;
    MKT_SHARE_mPART1_mPART2_entry se213;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se214;
    MKT_SHARE_mORDERS6_mPART2_entry se215;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se216;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se217;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se218;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry se219;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se220;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry se221;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry se222;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se223;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry se224;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se225;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry se226;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry se227;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry se228;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se229;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry se230;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se231;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se232;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry se233;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se234;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se235;
    MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry se236;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se237;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry se238;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se239;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry se240;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se241;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se242;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se243;
    MKT_SHARE_mORDERS6_entry se244;
    MKT_SHARE_mORDERS6_mPART2_entry se245;
    MKT_SHARE_mPART1_entry se246;
    MKT_SHARE_mPART1_mPART2_entry se247;
    MKT_SHARE_mPART1_mCUSTOMER1_entry se248;
    MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry se249;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry se250;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry se251;
    MKT_SHARE_mPART1_mSUPPLIER2_entry se252;
    MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry se253;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se254;
    MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry se255;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry se256;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry se257;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry se258;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry se259;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry se260;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry se261;
    MKT_SHARE_entry se262;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se263;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se264;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry se265;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se266;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se267;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_entry se268;
    MKT_SHARE_mORDERS6_entry se269;
    MKT_SHARE_mORDERS6_mPART2_entry se270;
    MKT_SHARE_mPART1_entry se271;
    MKT_SHARE_mPART1_mPART2_entry se272;
    MKT_SHARE_mPART1_mCUSTOMER1_entry se273;
    MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry se274;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry se275;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry se276;
    MKT_SHARE_mPART1_mSUPPLIER2_entry se277;
    MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry se278;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se279;
    MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry se280;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry se281;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry se282;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry se283;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry se284;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry se285;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry se286;
    MKT_SHARE_entry se287;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se288;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se289;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se290;
    MKT_SHARE_mPART1_entry se291;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se292;
    MKT_SHARE_mPART1_mCUSTOMER1_entry se293;
    MKT_SHARE_mPART1_mLINEITEM3_entry se294;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se295;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry se296;
    MKT_SHARE_mPART1_mSUPPLIER2_entry se297;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se298;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry se299;
    MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry se300;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se301;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry se302;
    MKT_SHARE_mPART1_mPART2_entry se303;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se304;
    MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry se305;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se306;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se307;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry se308;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry se309;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se310;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry se311;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry se312;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se313;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry se314;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry se315;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se316;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry se317;
    MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry se318;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se319;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry se320;
    MKT_SHARE_entry se321;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se322;
    MKT_SHARE_mORDERS1_L2_1_L1_4_entry se323;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se324;
    MKT_SHARE_mPART1_entry se325;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se326;
    MKT_SHARE_mPART1_mCUSTOMER1_entry se327;
    MKT_SHARE_mPART1_mLINEITEM3_entry se328;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se329;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_entry se330;
    MKT_SHARE_mPART1_mSUPPLIER2_entry se331;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se332;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry se333;
    MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry se334;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se335;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry se336;
    MKT_SHARE_mPART1_mPART2_entry se337;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se338;
    MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry se339;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se340;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se341;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry se342;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_entry se343;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se344;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_entry se345;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry se346;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se347;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry se348;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry se349;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se350;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry se351;
    MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry se352;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se353;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry se354;
    MKT_SHARE_entry se355;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se356;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se357;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se358;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se359;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry se360;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se361;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se362;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se363;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se364;
    MKT_SHARE_mORDERS6_entry se365;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se366;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se367;
    MKT_SHARE_mORDERS6_mPART2_entry se368;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se369;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se370;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se371;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se372;
    MKT_SHARE_mPART1_entry se373;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se374;
    MKT_SHARE_mPART1_mSUPPLIER2_entry se375;
    MKT_SHARE_mPART1_mCUSTOMER1_entry se376;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se377;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry se378;
    MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry se379;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se380;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry se381;
    MKT_SHARE_mPART1_mPART2_entry se382;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se383;
    MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry se384;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se385;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se386;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry se387;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry se388;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se389;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry se390;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry se391;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se392;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry se393;
    MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry se394;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se395;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry se396;
    MKT_SHARE_entry se397;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se398;
    MKT_SHARE_mORDERS1_L2_1_L1_5_entry se399;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se400;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se401;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_entry se402;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se403;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se404;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_entry se405;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se406;
    MKT_SHARE_mORDERS6_entry se407;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se408;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_entry se409;
    MKT_SHARE_mORDERS6_mPART2_entry se410;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se411;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_entry se412;
    MKT_SHARE_mORDERS6_mLINEITEM1_entry se413;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se414;
    MKT_SHARE_mPART1_entry se415;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se416;
    MKT_SHARE_mPART1_mSUPPLIER2_entry se417;
    MKT_SHARE_mPART1_mCUSTOMER1_entry se418;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se419;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_entry se420;
    MKT_SHARE_mPART1_mCUSTOMER1_mPART2_entry se421;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se422;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_entry se423;
    MKT_SHARE_mPART1_mPART2_entry se424;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se425;
    MKT_SHARE_mPART1_mSUPPLIER2_mPART2_entry se426;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se427;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se428;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_entry se429;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_entry se430;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se431;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_entry se432;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_entry se433;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se434;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_entry se435;
    MKT_SHARE_mPART1_L2_1_L1_1_mPART2_entry se436;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se437;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_entry se438;
    MKT_SHARE_entry se439;
    MKT_SHARE_mPART1_L2_1_L1_1_entry se440;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_entry se441;
    REGION_entry se442;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_entry se443;
    MKT_SHARE_mORDERS6_mSUPPLIER1_entry se444;
    NATION_entry se445;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REGION_map REGION;
    MKT_SHARE_mORDERS1_L2_1_L1_4_map MKT_SHARE_mORDERS1_L2_1_L1_4;
    MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1_map MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1;
    MKT_SHARE_mORDERS1_L2_1_L1_5_map MKT_SHARE_mORDERS1_L2_1_L1_5;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_map MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2_map MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2_map MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2_map MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1_map MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1;
    MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2_map MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2;
    MKT_SHARE_mORDERS6_map MKT_SHARE_mORDERS6;
    MKT_SHARE_mORDERS6_mSUPPLIER1_map MKT_SHARE_mORDERS6_mSUPPLIER1;
    MKT_SHARE_mORDERS6_mPART2_map MKT_SHARE_mORDERS6_mPART2;
    MKT_SHARE_mORDERS6_mLINEITEM1_map MKT_SHARE_mORDERS6_mLINEITEM1;
    MKT_SHARE_mPART1_map MKT_SHARE_mPART1;
    MKT_SHARE_mPART1_mCUSTOMER1_map MKT_SHARE_mPART1_mCUSTOMER1;
    MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3_map MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_map MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2;
    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2_map MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2;
    MKT_SHARE_mPART1_mCUSTOMER1_mPART2_map MKT_SHARE_mPART1_mCUSTOMER1_mPART2;
    MKT_SHARE_mPART1_mLINEITEM3_map MKT_SHARE_mPART1_mLINEITEM3;
    MKT_SHARE_mPART1_mSUPPLIER2_map MKT_SHARE_mPART1_mSUPPLIER2;
    MKT_SHARE_mPART1_mSUPPLIER2_mPART2_map MKT_SHARE_mPART1_mSUPPLIER2_mPART2;
    MKT_SHARE_mPART1_mPART2_map MKT_SHARE_mPART1_mPART2;
    MKT_SHARE_mPART1_L2_1_L1_1_map MKT_SHARE_mPART1_L2_1_L1_1;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_map MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3_map MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_map MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2_map MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2;
    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2_map MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2;
    MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2_map MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_map MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1;
    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2_map MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2;
    MKT_SHARE_mPART1_L2_1_L1_1_mPART2_map MKT_SHARE_mPART1_L2_1_L1_1_mPART2;
    
    /*const static*/ long c2;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c5;
  
  };

}
