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
  struct QUERY18_entry {
    STRING_TYPE C_NAME; long C_CUSTKEY; long O_ORDERKEY; date O_ORDERDATE; DOUBLE_TYPE O_TOTALPRICE; DOUBLE_TYPE __av; 
    explicit QUERY18_entry() { /*C_NAME = ""; C_CUSTKEY = 0L; O_ORDERKEY = 0L; O_ORDERDATE = 00000000; O_TOTALPRICE = 0.0; __av = 0.0; */ }
    explicit QUERY18_entry(const STRING_TYPE& c0, const long c1, const long c2, const date c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5) { C_NAME = c0; C_CUSTKEY = c1; O_ORDERKEY = c2; O_ORDERDATE = c3; O_TOTALPRICE = c4; __av = c5; }
    QUERY18_entry(const QUERY18_entry& other) : C_NAME( other.C_NAME ), C_CUSTKEY( other.C_CUSTKEY ), O_ORDERKEY( other.O_ORDERKEY ), O_ORDERDATE( other.O_ORDERDATE ), O_TOTALPRICE( other.O_TOTALPRICE ), __av( other.__av ) {}
    FORCE_INLINE QUERY18_entry& modify(const STRING_TYPE& c0, const long c1, const long c2, const date c3, const DOUBLE_TYPE c4) { C_NAME = c0; C_CUSTKEY = c1; O_ORDERKEY = c2; O_ORDERDATE = c3; O_TOTALPRICE = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.O_ORDERDATE);
      hash_combine(h, e.O_TOTALPRICE);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_entry& x, const QUERY18_entry& y) {
      return x.C_NAME == y.C_NAME && x.C_CUSTKEY == y.C_CUSTKEY && x.O_ORDERKEY == y.O_ORDERKEY && x.O_ORDERDATE == y.O_ORDERDATE && x.O_TOTALPRICE == y.O_TOTALPRICE;
    }
  };
  
  typedef MultiHashMap<QUERY18_entry,DOUBLE_TYPE,
    HashIndex<QUERY18_entry,DOUBLE_TYPE,QUERY18_mapkey01234_idxfn,true>
  > QUERY18_map;
  typedef HashIndex<QUERY18_entry,DOUBLE_TYPE,QUERY18_mapkey01234_idxfn,true> HashIndex_QUERY18_map_01234;
  
  struct QUERY18_mLINEITEM2_entry {
    long C_CUSTKEY; STRING_TYPE C_NAME; long QUERY18_mLINEITEMLINEITEM_ORDERKEY; DOUBLE_TYPE O_TOTALPRICE; date O_ORDERDATE; long __av; 
    explicit QUERY18_mLINEITEM2_entry() { /*C_CUSTKEY = 0L; C_NAME = ""; QUERY18_mLINEITEMLINEITEM_ORDERKEY = 0L; O_TOTALPRICE = 0.0; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit QUERY18_mLINEITEM2_entry(const long c0, const STRING_TYPE& c1, const long c2, const DOUBLE_TYPE c3, const date c4, const long c5) { C_CUSTKEY = c0; C_NAME = c1; QUERY18_mLINEITEMLINEITEM_ORDERKEY = c2; O_TOTALPRICE = c3; O_ORDERDATE = c4; __av = c5; }
    QUERY18_mLINEITEM2_entry(const QUERY18_mLINEITEM2_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_NAME( other.C_NAME ), QUERY18_mLINEITEMLINEITEM_ORDERKEY( other.QUERY18_mLINEITEMLINEITEM_ORDERKEY ), O_TOTALPRICE( other.O_TOTALPRICE ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE QUERY18_mLINEITEM2_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const DOUBLE_TYPE c3, const date c4) { C_CUSTKEY = c0; C_NAME = c1; QUERY18_mLINEITEMLINEITEM_ORDERKEY = c2; O_TOTALPRICE = c3; O_ORDERDATE = c4;  return *this; }
    FORCE_INLINE QUERY18_mLINEITEM2_entry& modify2(const long c2) { QUERY18_mLINEITEMLINEITEM_ORDERKEY = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY18_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18_mLINEITEM2_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_mLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.QUERY18_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.O_TOTALPRICE);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_mLINEITEM2_entry& x, const QUERY18_mLINEITEM2_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_NAME == y.C_NAME && x.QUERY18_mLINEITEMLINEITEM_ORDERKEY == y.QUERY18_mLINEITEMLINEITEM_ORDERKEY && x.O_TOTALPRICE == y.O_TOTALPRICE && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct QUERY18_mLINEITEM2_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_mLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_mLINEITEM2_entry& x, const QUERY18_mLINEITEM2_entry& y) {
      return x.QUERY18_mLINEITEMLINEITEM_ORDERKEY == y.QUERY18_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18_mLINEITEM2_entry,long,
    HashIndex<QUERY18_mLINEITEM2_entry,long,QUERY18_mLINEITEM2_mapkey01234_idxfn,true>,
    HashIndex<QUERY18_mLINEITEM2_entry,long,QUERY18_mLINEITEM2_mapkey2_idxfn,false>
  > QUERY18_mLINEITEM2_map;
  typedef HashIndex<QUERY18_mLINEITEM2_entry,long,QUERY18_mLINEITEM2_mapkey01234_idxfn,true> HashIndex_QUERY18_mLINEITEM2_map_01234;
  typedef HashIndex<QUERY18_mLINEITEM2_entry,long,QUERY18_mLINEITEM2_mapkey2_idxfn,false> HashIndex_QUERY18_mLINEITEM2_map_2;
  
  struct QUERY18_mLINEITEM2_mCUSTOMER1_entry {
    long QUERY18_mLINEITEMLINEITEM_ORDERKEY; long QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY; DOUBLE_TYPE O_TOTALPRICE; date O_ORDERDATE; long __av; 
    explicit QUERY18_mLINEITEM2_mCUSTOMER1_entry() { /*QUERY18_mLINEITEMLINEITEM_ORDERKEY = 0L; QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY = 0L; O_TOTALPRICE = 0.0; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit QUERY18_mLINEITEM2_mCUSTOMER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3, const long c4) { QUERY18_mLINEITEMLINEITEM_ORDERKEY = c0; QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3; __av = c4; }
    QUERY18_mLINEITEM2_mCUSTOMER1_entry(const QUERY18_mLINEITEM2_mCUSTOMER1_entry& other) : QUERY18_mLINEITEMLINEITEM_ORDERKEY( other.QUERY18_mLINEITEMLINEITEM_ORDERKEY ), QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY( other.QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY ), O_TOTALPRICE( other.O_TOTALPRICE ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE QUERY18_mLINEITEM2_mCUSTOMER1_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3) { QUERY18_mLINEITEMLINEITEM_ORDERKEY = c0; QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3;  return *this; }
    FORCE_INLINE QUERY18_mLINEITEM2_mCUSTOMER1_entry& modify0(const long c0) { QUERY18_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE QUERY18_mLINEITEM2_mCUSTOMER1_entry& modify1(const long c1) { QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY18_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18_mLINEITEM2_mCUSTOMER1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_mLINEITEM2_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_TOTALPRICE);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_mLINEITEM2_mCUSTOMER1_entry& x, const QUERY18_mLINEITEM2_mCUSTOMER1_entry& y) {
      return x.QUERY18_mLINEITEMLINEITEM_ORDERKEY == y.QUERY18_mLINEITEMLINEITEM_ORDERKEY && x.QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY == y.QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY && x.O_TOTALPRICE == y.O_TOTALPRICE && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct QUERY18_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_mLINEITEM2_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_mLINEITEM2_mCUSTOMER1_entry& x, const QUERY18_mLINEITEM2_mCUSTOMER1_entry& y) {
      return x.QUERY18_mLINEITEMLINEITEM_ORDERKEY == y.QUERY18_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct QUERY18_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_mLINEITEM2_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_mLINEITEM2_mCUSTOMER1_entry& x, const QUERY18_mLINEITEM2_mCUSTOMER1_entry& y) {
      return x.QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY == y.QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18_mLINEITEM2_mCUSTOMER1_entry,long,
    HashIndex<QUERY18_mLINEITEM2_mCUSTOMER1_entry,long,QUERY18_mLINEITEM2_mCUSTOMER1_mapkey0123_idxfn,true>,
    HashIndex<QUERY18_mLINEITEM2_mCUSTOMER1_entry,long,QUERY18_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn,false>,
    HashIndex<QUERY18_mLINEITEM2_mCUSTOMER1_entry,long,QUERY18_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn,false>
  > QUERY18_mLINEITEM2_mCUSTOMER1_map;
  typedef HashIndex<QUERY18_mLINEITEM2_mCUSTOMER1_entry,long,QUERY18_mLINEITEM2_mCUSTOMER1_mapkey0123_idxfn,true> HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_0123;
  typedef HashIndex<QUERY18_mLINEITEM2_mCUSTOMER1_entry,long,QUERY18_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn,false> HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_0;
  typedef HashIndex<QUERY18_mLINEITEM2_mCUSTOMER1_entry,long,QUERY18_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn,false> HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_1;
  
  struct QUERY18_mORDERS2_entry {
    long QUERY18_mORDERSORDERS_CUSTKEY; STRING_TYPE C_NAME; long __av; 
    explicit QUERY18_mORDERS2_entry() { /*QUERY18_mORDERSORDERS_CUSTKEY = 0L; C_NAME = ""; __av = 0L; */ }
    explicit QUERY18_mORDERS2_entry(const long c0, const STRING_TYPE& c1, const long c2) { QUERY18_mORDERSORDERS_CUSTKEY = c0; C_NAME = c1; __av = c2; }
    QUERY18_mORDERS2_entry(const QUERY18_mORDERS2_entry& other) : QUERY18_mORDERSORDERS_CUSTKEY( other.QUERY18_mORDERSORDERS_CUSTKEY ), C_NAME( other.C_NAME ), __av( other.__av ) {}
    FORCE_INLINE QUERY18_mORDERS2_entry& modify(const long c0, const STRING_TYPE& c1) { QUERY18_mORDERSORDERS_CUSTKEY = c0; C_NAME = c1;  return *this; }
    FORCE_INLINE QUERY18_mORDERS2_entry& modify0(const long c0) { QUERY18_mORDERSORDERS_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY18_mORDERSORDERS_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18_mORDERS2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_mORDERS2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18_mORDERSORDERS_CUSTKEY);
      hash_combine(h, e.C_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_mORDERS2_entry& x, const QUERY18_mORDERS2_entry& y) {
      return x.QUERY18_mORDERSORDERS_CUSTKEY == y.QUERY18_mORDERSORDERS_CUSTKEY && x.C_NAME == y.C_NAME;
    }
  };
  
  struct QUERY18_mORDERS2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_mORDERS2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18_mORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_mORDERS2_entry& x, const QUERY18_mORDERS2_entry& y) {
      return x.QUERY18_mORDERSORDERS_CUSTKEY == y.QUERY18_mORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18_mORDERS2_entry,long,
    HashIndex<QUERY18_mORDERS2_entry,long,QUERY18_mORDERS2_mapkey01_idxfn,true>,
    HashIndex<QUERY18_mORDERS2_entry,long,QUERY18_mORDERS2_mapkey0_idxfn,false>
  > QUERY18_mORDERS2_map;
  typedef HashIndex<QUERY18_mORDERS2_entry,long,QUERY18_mORDERS2_mapkey01_idxfn,true> HashIndex_QUERY18_mORDERS2_map_01;
  typedef HashIndex<QUERY18_mORDERS2_entry,long,QUERY18_mORDERS2_mapkey0_idxfn,false> HashIndex_QUERY18_mORDERS2_map_0;
  
  struct QUERY18_mCUSTOMER1_entry {
    long O_ORDERKEY; long QUERY18_mCUSTOMERCUSTOMER_CUSTKEY; DOUBLE_TYPE O_TOTALPRICE; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit QUERY18_mCUSTOMER1_entry() { /*O_ORDERKEY = 0L; QUERY18_mCUSTOMERCUSTOMER_CUSTKEY = 0L; O_TOTALPRICE = 0.0; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit QUERY18_mCUSTOMER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3, const DOUBLE_TYPE c4) { O_ORDERKEY = c0; QUERY18_mCUSTOMERCUSTOMER_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3; __av = c4; }
    QUERY18_mCUSTOMER1_entry(const QUERY18_mCUSTOMER1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), QUERY18_mCUSTOMERCUSTOMER_CUSTKEY( other.QUERY18_mCUSTOMERCUSTOMER_CUSTKEY ), O_TOTALPRICE( other.O_TOTALPRICE ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE QUERY18_mCUSTOMER1_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3) { O_ORDERKEY = c0; QUERY18_mCUSTOMERCUSTOMER_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3;  return *this; }
    FORCE_INLINE QUERY18_mCUSTOMER1_entry& modify1(const long c1) { QUERY18_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY18_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18_mCUSTOMER1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.QUERY18_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_TOTALPRICE);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_mCUSTOMER1_entry& x, const QUERY18_mCUSTOMER1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.QUERY18_mCUSTOMERCUSTOMER_CUSTKEY == y.QUERY18_mCUSTOMERCUSTOMER_CUSTKEY && x.O_TOTALPRICE == y.O_TOTALPRICE && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct QUERY18_mCUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_mCUSTOMER1_entry& x, const QUERY18_mCUSTOMER1_entry& y) {
      return x.QUERY18_mCUSTOMERCUSTOMER_CUSTKEY == y.QUERY18_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18_mCUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<QUERY18_mCUSTOMER1_entry,DOUBLE_TYPE,QUERY18_mCUSTOMER1_mapkey0123_idxfn,true>,
    HashIndex<QUERY18_mCUSTOMER1_entry,DOUBLE_TYPE,QUERY18_mCUSTOMER1_mapkey1_idxfn,false>
  > QUERY18_mCUSTOMER1_map;
  typedef HashIndex<QUERY18_mCUSTOMER1_entry,DOUBLE_TYPE,QUERY18_mCUSTOMER1_mapkey0123_idxfn,true> HashIndex_QUERY18_mCUSTOMER1_map_0123;
  typedef HashIndex<QUERY18_mCUSTOMER1_entry,DOUBLE_TYPE,QUERY18_mCUSTOMER1_mapkey1_idxfn,false> HashIndex_QUERY18_mCUSTOMER1_map_1;
  
  struct QUERY18_mCUSTOMER1_L1_1_entry {
    long O_ORDERKEY; DOUBLE_TYPE __av; 
    explicit QUERY18_mCUSTOMER1_L1_1_entry() { /*O_ORDERKEY = 0L; __av = 0.0; */ }
    explicit QUERY18_mCUSTOMER1_L1_1_entry(const long c0, const DOUBLE_TYPE c1) { O_ORDERKEY = c0; __av = c1; }
    QUERY18_mCUSTOMER1_L1_1_entry(const QUERY18_mCUSTOMER1_L1_1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY18_mCUSTOMER1_L1_1_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18_mCUSTOMER1_L1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_mCUSTOMER1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_mCUSTOMER1_L1_1_entry& x, const QUERY18_mCUSTOMER1_L1_1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18_mCUSTOMER1_L1_1_entry,DOUBLE_TYPE,
    HashIndex<QUERY18_mCUSTOMER1_L1_1_entry,DOUBLE_TYPE,QUERY18_mCUSTOMER1_L1_1_mapkey0_idxfn,true>
  > QUERY18_mCUSTOMER1_L1_1_map;
  typedef HashIndex<QUERY18_mCUSTOMER1_L1_1_entry,DOUBLE_TYPE,QUERY18_mCUSTOMER1_L1_1_mapkey0_idxfn,true> HashIndex_QUERY18_mCUSTOMER1_L1_1_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const QUERY18_map& _QUERY18 = get_QUERY18();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(QUERY18), _QUERY18, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const QUERY18_map& get_QUERY18() const {
      return QUERY18;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    QUERY18_map QUERY18;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_QUERY18_mLINEITEM2_map_2* i1 = static_cast<HashIndex_QUERY18_mLINEITEM2_map_2*>(QUERY18_mLINEITEM2.index[1]);
          const HASH_RES_t h1 = QUERY18_mLINEITEM2_mapkey2_idxfn::hash(se6.modify2(lineitem_orderkey));
          HashIndex_QUERY18_mLINEITEM2_map_2::IdxNode* n1 = static_cast<HashIndex_QUERY18_mLINEITEM2_map_2::IdxNode*>(i1->slice(se6, h1));
          QUERY18_mLINEITEM2_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long c_custkey = e1->C_CUSTKEY;
              STRING_TYPE c_name = e1->C_NAME;
              DOUBLE_TYPE o_totalprice = e1->O_TOTALPRICE;
              date o_orderdate = e1->O_ORDERDATE;
              long v1 = e1->__av;
              long agg1 = 0L;
              DOUBLE_TYPE l1 = (QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se2.modify(lineitem_orderkey)) + lineitem_quantity);
              (/*if */(l1 > 100L) ? agg1 += 1L : 0L);
              long agg2 = 0L;
              DOUBLE_TYPE l2 = QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se4.modify(lineitem_orderkey));
              (/*if */(l2 > 100L) ? agg2 += 1L : 0L);
              QUERY18.addOrDelOnZero(se1.modify(c_name,c_custkey,lineitem_orderkey,o_orderdate,o_totalprice),(v1 * ((agg1 * (QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se3.modify(lineitem_orderkey)) + lineitem_quantity)) + (agg2 * (QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se5.modify(lineitem_orderkey)) * -1L)))));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  QUERY18_mLINEITEM2_mapkey2_idxfn::equals(se6, *e1)); 
          }
        }{ //slice 
          const HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_0* i2 = static_cast<HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_0*>(QUERY18_mLINEITEM2_mCUSTOMER1.index[1]);
          const HASH_RES_t h2 = QUERY18_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn::hash(se8.modify0(lineitem_orderkey));
          HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_0::IdxNode* n2 = static_cast<HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_0::IdxNode*>(i2->slice(se8, h2));
          QUERY18_mLINEITEM2_mCUSTOMER1_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long query18_mcustomercustomer_custkey = e2->QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY;
              DOUBLE_TYPE o_totalprice = e2->O_TOTALPRICE;
              date o_orderdate = e2->O_ORDERDATE;
              long v2 = e2->__av;
              QUERY18_mCUSTOMER1.addOrDelOnZero(se7.modify(lineitem_orderkey,query18_mcustomercustomer_custkey,o_totalprice,o_orderdate),(v2 * lineitem_quantity));
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  QUERY18_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn::equals(se8, *e2)); 
          }
        }QUERY18_mCUSTOMER1_L1_1.addOrDelOnZero(se9.modify(lineitem_orderkey),lineitem_quantity);
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_QUERY18_mLINEITEM2_map_2* i3 = static_cast<HashIndex_QUERY18_mLINEITEM2_map_2*>(QUERY18_mLINEITEM2.index[1]);
          const HASH_RES_t h3 = QUERY18_mLINEITEM2_mapkey2_idxfn::hash(se15.modify2(lineitem_orderkey));
          HashIndex_QUERY18_mLINEITEM2_map_2::IdxNode* n3 = static_cast<HashIndex_QUERY18_mLINEITEM2_map_2::IdxNode*>(i3->slice(se15, h3));
          QUERY18_mLINEITEM2_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              long c_custkey = e3->C_CUSTKEY;
              STRING_TYPE c_name = e3->C_NAME;
              DOUBLE_TYPE o_totalprice = e3->O_TOTALPRICE;
              date o_orderdate = e3->O_ORDERDATE;
              long v3 = e3->__av;
              long agg3 = 0L;
              DOUBLE_TYPE l3 = (QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se11.modify(lineitem_orderkey)) + (-1L * lineitem_quantity));
              (/*if */(l3 > 100L) ? agg3 += 1L : 0L);
              long agg4 = 0L;
              DOUBLE_TYPE l4 = QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se13.modify(lineitem_orderkey));
              (/*if */(l4 > 100L) ? agg4 += 1L : 0L);
              QUERY18.addOrDelOnZero(se10.modify(c_name,c_custkey,lineitem_orderkey,o_orderdate,o_totalprice),(v3 * ((agg3 * (QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se12.modify(lineitem_orderkey)) + (-1L * lineitem_quantity))) + (agg4 * (QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se14.modify(lineitem_orderkey)) * -1L)))));
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  QUERY18_mLINEITEM2_mapkey2_idxfn::equals(se15, *e3)); 
          }
        }{ //slice 
          const HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_0* i4 = static_cast<HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_0*>(QUERY18_mLINEITEM2_mCUSTOMER1.index[1]);
          const HASH_RES_t h4 = QUERY18_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn::hash(se17.modify0(lineitem_orderkey));
          HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_0::IdxNode* n4 = static_cast<HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_0::IdxNode*>(i4->slice(se17, h4));
          QUERY18_mLINEITEM2_mCUSTOMER1_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long query18_mcustomercustomer_custkey = e4->QUERY18_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY;
              DOUBLE_TYPE o_totalprice = e4->O_TOTALPRICE;
              date o_orderdate = e4->O_ORDERDATE;
              long v4 = e4->__av;
              QUERY18_mCUSTOMER1.addOrDelOnZero(se16.modify(lineitem_orderkey,query18_mcustomercustomer_custkey,o_totalprice,o_orderdate),(v4 * (-1L * lineitem_quantity)));
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  QUERY18_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn::equals(se17, *e4)); 
          }
        }QUERY18_mCUSTOMER1_L1_1.addOrDelOnZero(se18.modify(lineitem_orderkey),(-1L * lineitem_quantity));
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg5 = 0L;
        DOUBLE_TYPE l5 = QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se20.modify(orders_orderkey));
        (/*if */(l5 > 100L) ? agg5 += 1L : 0L);
        { //slice 
          const HashIndex_QUERY18_mORDERS2_map_0* i5 = static_cast<HashIndex_QUERY18_mORDERS2_map_0*>(QUERY18_mORDERS2.index[1]);
          const HASH_RES_t h5 = QUERY18_mORDERS2_mapkey0_idxfn::hash(se22.modify0(orders_custkey));
          HashIndex_QUERY18_mORDERS2_map_0::IdxNode* n5 = static_cast<HashIndex_QUERY18_mORDERS2_map_0::IdxNode*>(i5->slice(se22, h5));
          QUERY18_mORDERS2_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              STRING_TYPE c_name = e5->C_NAME;
              long v5 = e5->__av;
              QUERY18.addOrDelOnZero(se19.modify(c_name,orders_custkey,orders_orderkey,orders_orderdate,orders_totalprice),(agg5 * (v5 * QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se21.modify(orders_orderkey)))));
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  QUERY18_mORDERS2_mapkey0_idxfn::equals(se22, *e5)); 
          }
        }{ //slice 
          const HashIndex_QUERY18_mORDERS2_map_0* i6 = static_cast<HashIndex_QUERY18_mORDERS2_map_0*>(QUERY18_mORDERS2.index[1]);
          const HASH_RES_t h6 = QUERY18_mORDERS2_mapkey0_idxfn::hash(se24.modify0(orders_custkey));
          HashIndex_QUERY18_mORDERS2_map_0::IdxNode* n6 = static_cast<HashIndex_QUERY18_mORDERS2_map_0::IdxNode*>(i6->slice(se24, h6));
          QUERY18_mORDERS2_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              STRING_TYPE c_name = e6->C_NAME;
              long v6 = e6->__av;
              QUERY18_mLINEITEM2.addOrDelOnZero(se23.modify(orders_custkey,c_name,orders_orderkey,orders_totalprice,orders_orderdate),v6);
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h6 == n6->hash &&  QUERY18_mORDERS2_mapkey0_idxfn::equals(se24, *e6)); 
          }
        }QUERY18_mLINEITEM2_mCUSTOMER1.addOrDelOnZero(se25.modify(orders_orderkey,orders_custkey,orders_totalprice,orders_orderdate),1L);
        QUERY18_mCUSTOMER1.addOrDelOnZero(se26.modify(orders_orderkey,orders_custkey,orders_totalprice,orders_orderdate),QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se27.modify(orders_orderkey)));
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg6 = 0L;
        DOUBLE_TYPE l6 = QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se29.modify(orders_orderkey));
        (/*if */(l6 > 100L) ? agg6 += 1L : 0L);
        { //slice 
          const HashIndex_QUERY18_mORDERS2_map_0* i7 = static_cast<HashIndex_QUERY18_mORDERS2_map_0*>(QUERY18_mORDERS2.index[1]);
          const HASH_RES_t h7 = QUERY18_mORDERS2_mapkey0_idxfn::hash(se31.modify0(orders_custkey));
          HashIndex_QUERY18_mORDERS2_map_0::IdxNode* n7 = static_cast<HashIndex_QUERY18_mORDERS2_map_0::IdxNode*>(i7->slice(se31, h7));
          QUERY18_mORDERS2_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              STRING_TYPE c_name = e7->C_NAME;
              long v7 = e7->__av;
              QUERY18.addOrDelOnZero(se28.modify(c_name,orders_custkey,orders_orderkey,orders_orderdate,orders_totalprice),(agg6 * (v7 * (QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se30.modify(orders_orderkey)) * -1L))));
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h7 == n7->hash &&  QUERY18_mORDERS2_mapkey0_idxfn::equals(se31, *e7)); 
          }
        }{ //slice 
          const HashIndex_QUERY18_mORDERS2_map_0* i8 = static_cast<HashIndex_QUERY18_mORDERS2_map_0*>(QUERY18_mORDERS2.index[1]);
          const HASH_RES_t h8 = QUERY18_mORDERS2_mapkey0_idxfn::hash(se33.modify0(orders_custkey));
          HashIndex_QUERY18_mORDERS2_map_0::IdxNode* n8 = static_cast<HashIndex_QUERY18_mORDERS2_map_0::IdxNode*>(i8->slice(se33, h8));
          QUERY18_mORDERS2_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              STRING_TYPE c_name = e8->C_NAME;
              long v8 = e8->__av;
              QUERY18_mLINEITEM2.addOrDelOnZero(se32.modify(orders_custkey,c_name,orders_orderkey,orders_totalprice,orders_orderdate),(v8 * -1L));
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h8 == n8->hash &&  QUERY18_mORDERS2_mapkey0_idxfn::equals(se33, *e8)); 
          }
        }QUERY18_mLINEITEM2_mCUSTOMER1.addOrDelOnZero(se34.modify(orders_orderkey,orders_custkey,orders_totalprice,orders_orderdate),-1L);
        QUERY18_mCUSTOMER1.addOrDelOnZero(se35.modify(orders_orderkey,orders_custkey,orders_totalprice,orders_orderdate),(QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se36.modify(orders_orderkey)) * -1L));
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_QUERY18_mCUSTOMER1_map_1* i9 = static_cast<HashIndex_QUERY18_mCUSTOMER1_map_1*>(QUERY18_mCUSTOMER1.index[1]);
          const HASH_RES_t h9 = QUERY18_mCUSTOMER1_mapkey1_idxfn::hash(se39.modify1(customer_custkey));
          HashIndex_QUERY18_mCUSTOMER1_map_1::IdxNode* n9 = static_cast<HashIndex_QUERY18_mCUSTOMER1_map_1::IdxNode*>(i9->slice(se39, h9));
          QUERY18_mCUSTOMER1_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              long o_orderkey = e9->O_ORDERKEY;
              DOUBLE_TYPE o_totalprice = e9->O_TOTALPRICE;
              date o_orderdate = e9->O_ORDERDATE;
              DOUBLE_TYPE v9 = e9->__av;
              long agg7 = 0L;
              DOUBLE_TYPE l7 = QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se38.modify(o_orderkey));
              (/*if */(l7 > 100L) ? agg7 += 1L : 0L);
              QUERY18.addOrDelOnZero(se37.modify(customer_name,customer_custkey,o_orderkey,o_orderdate,o_totalprice),(v9 * agg7));
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h9 == n9->hash &&  QUERY18_mCUSTOMER1_mapkey1_idxfn::equals(se39, *e9)); 
          }
        }{ //slice 
          const HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_1* i10 = static_cast<HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_1*>(QUERY18_mLINEITEM2_mCUSTOMER1.index[2]);
          const HASH_RES_t h10 = QUERY18_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn::hash(se41.modify1(customer_custkey));
          HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_1::IdxNode* n10 = static_cast<HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_1::IdxNode*>(i10->slice(se41, h10));
          QUERY18_mLINEITEM2_mCUSTOMER1_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              long query18_mlineitemlineitem_orderkey = e10->QUERY18_mLINEITEMLINEITEM_ORDERKEY;
              DOUBLE_TYPE o_totalprice = e10->O_TOTALPRICE;
              date o_orderdate = e10->O_ORDERDATE;
              long v10 = e10->__av;
              QUERY18_mLINEITEM2.addOrDelOnZero(se40.modify(customer_custkey,customer_name,query18_mlineitemlineitem_orderkey,o_totalprice,o_orderdate),v10);
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h10 == n10->hash &&  QUERY18_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn::equals(se41, *e10)); 
          }
        }QUERY18_mORDERS2.addOrDelOnZero(se42.modify(customer_custkey,customer_name),1L);
      }
    }
    void on_delete_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_QUERY18_mCUSTOMER1_map_1* i11 = static_cast<HashIndex_QUERY18_mCUSTOMER1_map_1*>(QUERY18_mCUSTOMER1.index[1]);
          const HASH_RES_t h11 = QUERY18_mCUSTOMER1_mapkey1_idxfn::hash(se45.modify1(customer_custkey));
          HashIndex_QUERY18_mCUSTOMER1_map_1::IdxNode* n11 = static_cast<HashIndex_QUERY18_mCUSTOMER1_map_1::IdxNode*>(i11->slice(se45, h11));
          QUERY18_mCUSTOMER1_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              long o_orderkey = e11->O_ORDERKEY;
              DOUBLE_TYPE o_totalprice = e11->O_TOTALPRICE;
              date o_orderdate = e11->O_ORDERDATE;
              DOUBLE_TYPE v11 = e11->__av;
              long agg8 = 0L;
              DOUBLE_TYPE l8 = QUERY18_mCUSTOMER1_L1_1.getValueOrDefault(se44.modify(o_orderkey));
              (/*if */(l8 > 100L) ? agg8 += 1L : 0L);
              QUERY18.addOrDelOnZero(se43.modify(customer_name,customer_custkey,o_orderkey,o_orderdate,o_totalprice),(v11 * (agg8 * -1L)));
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h11 == n11->hash &&  QUERY18_mCUSTOMER1_mapkey1_idxfn::equals(se45, *e11)); 
          }
        }{ //slice 
          const HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_1* i12 = static_cast<HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_1*>(QUERY18_mLINEITEM2_mCUSTOMER1.index[2]);
          const HASH_RES_t h12 = QUERY18_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn::hash(se47.modify1(customer_custkey));
          HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_1::IdxNode* n12 = static_cast<HashIndex_QUERY18_mLINEITEM2_mCUSTOMER1_map_1::IdxNode*>(i12->slice(se47, h12));
          QUERY18_mLINEITEM2_mCUSTOMER1_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              long query18_mlineitemlineitem_orderkey = e12->QUERY18_mLINEITEMLINEITEM_ORDERKEY;
              DOUBLE_TYPE o_totalprice = e12->O_TOTALPRICE;
              date o_orderdate = e12->O_ORDERDATE;
              long v12 = e12->__av;
              QUERY18_mLINEITEM2.addOrDelOnZero(se46.modify(customer_custkey,customer_name,query18_mlineitemlineitem_orderkey,o_totalprice,o_orderdate),(v12 * -1L));
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h12 == n12->hash &&  QUERY18_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn::equals(se47, *e12)); 
          }
        }QUERY18_mORDERS2.addOrDelOnZero(se48.modify(customer_custkey,customer_name),-1L);
      }
    }
    void on_system_ready_event() {
      {  
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    QUERY18_entry se1;
    QUERY18_mCUSTOMER1_L1_1_entry se2;
    QUERY18_mCUSTOMER1_L1_1_entry se3;
    QUERY18_mCUSTOMER1_L1_1_entry se4;
    QUERY18_mCUSTOMER1_L1_1_entry se5;
    QUERY18_mLINEITEM2_entry se6;
    QUERY18_mCUSTOMER1_entry se7;
    QUERY18_mLINEITEM2_mCUSTOMER1_entry se8;
    QUERY18_mCUSTOMER1_L1_1_entry se9;
    QUERY18_entry se10;
    QUERY18_mCUSTOMER1_L1_1_entry se11;
    QUERY18_mCUSTOMER1_L1_1_entry se12;
    QUERY18_mCUSTOMER1_L1_1_entry se13;
    QUERY18_mCUSTOMER1_L1_1_entry se14;
    QUERY18_mLINEITEM2_entry se15;
    QUERY18_mCUSTOMER1_entry se16;
    QUERY18_mLINEITEM2_mCUSTOMER1_entry se17;
    QUERY18_mCUSTOMER1_L1_1_entry se18;
    QUERY18_entry se19;
    QUERY18_mCUSTOMER1_L1_1_entry se20;
    QUERY18_mCUSTOMER1_L1_1_entry se21;
    QUERY18_mORDERS2_entry se22;
    QUERY18_mLINEITEM2_entry se23;
    QUERY18_mORDERS2_entry se24;
    QUERY18_mLINEITEM2_mCUSTOMER1_entry se25;
    QUERY18_mCUSTOMER1_entry se26;
    QUERY18_mCUSTOMER1_L1_1_entry se27;
    QUERY18_entry se28;
    QUERY18_mCUSTOMER1_L1_1_entry se29;
    QUERY18_mCUSTOMER1_L1_1_entry se30;
    QUERY18_mORDERS2_entry se31;
    QUERY18_mLINEITEM2_entry se32;
    QUERY18_mORDERS2_entry se33;
    QUERY18_mLINEITEM2_mCUSTOMER1_entry se34;
    QUERY18_mCUSTOMER1_entry se35;
    QUERY18_mCUSTOMER1_L1_1_entry se36;
    QUERY18_entry se37;
    QUERY18_mCUSTOMER1_L1_1_entry se38;
    QUERY18_mCUSTOMER1_entry se39;
    QUERY18_mLINEITEM2_entry se40;
    QUERY18_mLINEITEM2_mCUSTOMER1_entry se41;
    QUERY18_mORDERS2_entry se42;
    QUERY18_entry se43;
    QUERY18_mCUSTOMER1_L1_1_entry se44;
    QUERY18_mCUSTOMER1_entry se45;
    QUERY18_mLINEITEM2_entry se46;
    QUERY18_mLINEITEM2_mCUSTOMER1_entry se47;
    QUERY18_mORDERS2_entry se48;
  
    /* Data structures used for storing materialized views */
    QUERY18_mLINEITEM2_map QUERY18_mLINEITEM2;
    QUERY18_mLINEITEM2_mCUSTOMER1_map QUERY18_mLINEITEM2_mCUSTOMER1;
    QUERY18_mORDERS2_map QUERY18_mORDERS2;
    QUERY18_mCUSTOMER1_map QUERY18_mCUSTOMER1;
    QUERY18_mCUSTOMER1_L1_1_map QUERY18_mCUSTOMER1_L1_1;
    
    
  
  };

}
