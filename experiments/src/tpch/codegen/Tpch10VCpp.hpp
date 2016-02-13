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
  
  struct REVENUE_entry {
    long C_CUSTKEY; STRING_TYPE C_NAME; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE N_NAME; STRING_TYPE C_ADDRESS; STRING_TYPE C_PHONE; STRING_TYPE C_COMMENT; DOUBLE_TYPE __av; 
    explicit REVENUE_entry() { /*C_CUSTKEY = 0L; C_NAME = ""; C_ACCTBAL = 0.0; N_NAME = ""; C_ADDRESS = ""; C_PHONE = ""; C_COMMENT = ""; __av = 0.0; */ }
    explicit REVENUE_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7) { C_CUSTKEY = c0; C_NAME = c1; C_ACCTBAL = c2; N_NAME = c3; C_ADDRESS = c4; C_PHONE = c5; C_COMMENT = c6; __av = c7; }
    REVENUE_entry(const REVENUE_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_NAME( other.C_NAME ), C_ACCTBAL( other.C_ACCTBAL ), N_NAME( other.N_NAME ), C_ADDRESS( other.C_ADDRESS ), C_PHONE( other.C_PHONE ), C_COMMENT( other.C_COMMENT ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_entry& modify(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6) { C_CUSTKEY = c0; C_NAME = c1; C_ACCTBAL = c2; N_NAME = c3; C_ADDRESS = c4; C_PHONE = c5; C_COMMENT = c6;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.N_NAME);
      hash_combine(h, e.C_ADDRESS);
      hash_combine(h, e.C_PHONE);
      hash_combine(h, e.C_COMMENT);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_entry& x, const REVENUE_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_NAME == y.C_NAME && x.C_ACCTBAL == y.C_ACCTBAL && x.N_NAME == y.N_NAME && x.C_ADDRESS == y.C_ADDRESS && x.C_PHONE == y.C_PHONE && x.C_COMMENT == y.C_COMMENT;
    }
  };
  
  typedef MultiHashMap<REVENUE_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_entry,DOUBLE_TYPE,REVENUE_mapkey0123456_idxfn,true>
  > REVENUE_map;
  typedef HashIndex<REVENUE_entry,DOUBLE_TYPE,REVENUE_mapkey0123456_idxfn,true> HashIndex_REVENUE_map_0123456;
  
  struct REVENUE_mLINEITEM2_entry {
    long REVENUE_mLINEITEMLINEITEM_ORDERKEY; long C_CUSTKEY; STRING_TYPE C_NAME; STRING_TYPE C_ADDRESS; STRING_TYPE C_PHONE; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE C_COMMENT; STRING_TYPE N_NAME; long __av; 
    explicit REVENUE_mLINEITEM2_entry() { /*REVENUE_mLINEITEMLINEITEM_ORDERKEY = 0L; C_CUSTKEY = 0L; C_NAME = ""; C_ADDRESS = ""; C_PHONE = ""; C_ACCTBAL = 0.0; C_COMMENT = ""; N_NAME = ""; __av = 0L; */ }
    explicit REVENUE_mLINEITEM2_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const STRING_TYPE& c7, const long c8) { REVENUE_mLINEITEMLINEITEM_ORDERKEY = c0; C_CUSTKEY = c1; C_NAME = c2; C_ADDRESS = c3; C_PHONE = c4; C_ACCTBAL = c5; C_COMMENT = c6; N_NAME = c7; __av = c8; }
    REVENUE_mLINEITEM2_entry(const REVENUE_mLINEITEM2_entry& other) : REVENUE_mLINEITEMLINEITEM_ORDERKEY( other.REVENUE_mLINEITEMLINEITEM_ORDERKEY ), C_CUSTKEY( other.C_CUSTKEY ), C_NAME( other.C_NAME ), C_ADDRESS( other.C_ADDRESS ), C_PHONE( other.C_PHONE ), C_ACCTBAL( other.C_ACCTBAL ), C_COMMENT( other.C_COMMENT ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mLINEITEM2_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const STRING_TYPE& c7) { REVENUE_mLINEITEMLINEITEM_ORDERKEY = c0; C_CUSTKEY = c1; C_NAME = c2; C_ADDRESS = c3; C_PHONE = c4; C_ACCTBAL = c5; C_COMMENT = c6; N_NAME = c7;  return *this; }
    FORCE_INLINE REVENUE_mLINEITEM2_entry& modify0(const long c0) { REVENUE_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mLINEITEM2_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.C_ADDRESS);
      hash_combine(h, e.C_PHONE);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.C_COMMENT);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM2_entry& x, const REVENUE_mLINEITEM2_entry& y) {
      return x.REVENUE_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mLINEITEMLINEITEM_ORDERKEY && x.C_CUSTKEY == y.C_CUSTKEY && x.C_NAME == y.C_NAME && x.C_ADDRESS == y.C_ADDRESS && x.C_PHONE == y.C_PHONE && x.C_ACCTBAL == y.C_ACCTBAL && x.C_COMMENT == y.C_COMMENT && x.N_NAME == y.N_NAME;
    }
  };
  
  struct REVENUE_mLINEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM2_entry& x, const REVENUE_mLINEITEM2_entry& y) {
      return x.REVENUE_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mLINEITEM2_entry,long,
    HashIndex<REVENUE_mLINEITEM2_entry,long,REVENUE_mLINEITEM2_mapkey01234567_idxfn,true>,
    HashIndex<REVENUE_mLINEITEM2_entry,long,REVENUE_mLINEITEM2_mapkey0_idxfn,false>
  > REVENUE_mLINEITEM2_map;
  typedef HashIndex<REVENUE_mLINEITEM2_entry,long,REVENUE_mLINEITEM2_mapkey01234567_idxfn,true> HashIndex_REVENUE_mLINEITEM2_map_01234567;
  typedef HashIndex<REVENUE_mLINEITEM2_entry,long,REVENUE_mLINEITEM2_mapkey0_idxfn,false> HashIndex_REVENUE_mLINEITEM2_map_0;
  
  struct REVENUE_mLINEITEM2_mCUSTOMER1_entry {
    long REVENUE_mLINEITEMLINEITEM_ORDERKEY; long REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY; long __av; 
    explicit REVENUE_mLINEITEM2_mCUSTOMER1_entry() { /*REVENUE_mLINEITEMLINEITEM_ORDERKEY = 0L; REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY = 0L; __av = 0L; */ }
    explicit REVENUE_mLINEITEM2_mCUSTOMER1_entry(const long c0, const long c1, const long c2) { REVENUE_mLINEITEMLINEITEM_ORDERKEY = c0; REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY = c1; __av = c2; }
    REVENUE_mLINEITEM2_mCUSTOMER1_entry(const REVENUE_mLINEITEM2_mCUSTOMER1_entry& other) : REVENUE_mLINEITEMLINEITEM_ORDERKEY( other.REVENUE_mLINEITEMLINEITEM_ORDERKEY ), REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY( other.REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mLINEITEM2_mCUSTOMER1_entry& modify(const long c0, const long c1) { REVENUE_mLINEITEMLINEITEM_ORDERKEY = c0; REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mLINEITEM2_mCUSTOMER1_entry& modify0(const long c0) { REVENUE_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUE_mLINEITEM2_mCUSTOMER1_entry& modify1(const long c1) { REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mLINEITEM2_mCUSTOMER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM2_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM2_mCUSTOMER1_entry& x, const REVENUE_mLINEITEM2_mCUSTOMER1_entry& y) {
      return x.REVENUE_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mLINEITEMLINEITEM_ORDERKEY && x.REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct REVENUE_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM2_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM2_mCUSTOMER1_entry& x, const REVENUE_mLINEITEM2_mCUSTOMER1_entry& y) {
      return x.REVENUE_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct REVENUE_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM2_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM2_mCUSTOMER1_entry& x, const REVENUE_mLINEITEM2_mCUSTOMER1_entry& y) {
      return x.REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mLINEITEM2_mCUSTOMER1_entry,long,
    HashIndex<REVENUE_mLINEITEM2_mCUSTOMER1_entry,long,REVENUE_mLINEITEM2_mCUSTOMER1_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mLINEITEM2_mCUSTOMER1_entry,long,REVENUE_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn,false>,
    HashIndex<REVENUE_mLINEITEM2_mCUSTOMER1_entry,long,REVENUE_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn,false>
  > REVENUE_mLINEITEM2_mCUSTOMER1_map;
  typedef HashIndex<REVENUE_mLINEITEM2_mCUSTOMER1_entry,long,REVENUE_mLINEITEM2_mCUSTOMER1_mapkey01_idxfn,true> HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_01;
  typedef HashIndex<REVENUE_mLINEITEM2_mCUSTOMER1_entry,long,REVENUE_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn,false> HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_0;
  typedef HashIndex<REVENUE_mLINEITEM2_mCUSTOMER1_entry,long,REVENUE_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn,false> HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_1;
  
  struct REVENUE_mORDERS3_entry {
    long REVENUE_mORDERSORDERS_ORDERKEY; DOUBLE_TYPE __av; 
    explicit REVENUE_mORDERS3_entry() { /*REVENUE_mORDERSORDERS_ORDERKEY = 0L; __av = 0.0; */ }
    explicit REVENUE_mORDERS3_entry(const long c0, const DOUBLE_TYPE c1) { REVENUE_mORDERSORDERS_ORDERKEY = c0; __av = c1; }
    REVENUE_mORDERS3_entry(const REVENUE_mORDERS3_entry& other) : REVENUE_mORDERSORDERS_ORDERKEY( other.REVENUE_mORDERSORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mORDERS3_entry& modify(const long c0) { REVENUE_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mORDERS3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mORDERS3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mORDERS3_entry& x, const REVENUE_mORDERS3_entry& y) {
      return x.REVENUE_mORDERSORDERS_ORDERKEY == y.REVENUE_mORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mORDERS3_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mORDERS3_entry,DOUBLE_TYPE,REVENUE_mORDERS3_mapkey0_idxfn,true>
  > REVENUE_mORDERS3_map;
  typedef HashIndex<REVENUE_mORDERS3_entry,DOUBLE_TYPE,REVENUE_mORDERS3_mapkey0_idxfn,true> HashIndex_REVENUE_mORDERS3_map_0;
  
  struct REVENUE_mORDERS4_entry {
    long REVENUE_mORDERSORDERS_CUSTKEY; STRING_TYPE C_NAME; STRING_TYPE C_ADDRESS; STRING_TYPE C_PHONE; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE C_COMMENT; STRING_TYPE N_NAME; long __av; 
    explicit REVENUE_mORDERS4_entry() { /*REVENUE_mORDERSORDERS_CUSTKEY = 0L; C_NAME = ""; C_ADDRESS = ""; C_PHONE = ""; C_ACCTBAL = 0.0; C_COMMENT = ""; N_NAME = ""; __av = 0L; */ }
    explicit REVENUE_mORDERS4_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const long c7) { REVENUE_mORDERSORDERS_CUSTKEY = c0; C_NAME = c1; C_ADDRESS = c2; C_PHONE = c3; C_ACCTBAL = c4; C_COMMENT = c5; N_NAME = c6; __av = c7; }
    REVENUE_mORDERS4_entry(const REVENUE_mORDERS4_entry& other) : REVENUE_mORDERSORDERS_CUSTKEY( other.REVENUE_mORDERSORDERS_CUSTKEY ), C_NAME( other.C_NAME ), C_ADDRESS( other.C_ADDRESS ), C_PHONE( other.C_PHONE ), C_ACCTBAL( other.C_ACCTBAL ), C_COMMENT( other.C_COMMENT ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mORDERS4_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6) { REVENUE_mORDERSORDERS_CUSTKEY = c0; C_NAME = c1; C_ADDRESS = c2; C_PHONE = c3; C_ACCTBAL = c4; C_COMMENT = c5; N_NAME = c6;  return *this; }
    FORCE_INLINE REVENUE_mORDERS4_entry& modify0(const long c0) { REVENUE_mORDERSORDERS_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mORDERSORDERS_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mORDERS4_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mORDERS4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mORDERSORDERS_CUSTKEY);
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.C_ADDRESS);
      hash_combine(h, e.C_PHONE);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.C_COMMENT);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mORDERS4_entry& x, const REVENUE_mORDERS4_entry& y) {
      return x.REVENUE_mORDERSORDERS_CUSTKEY == y.REVENUE_mORDERSORDERS_CUSTKEY && x.C_NAME == y.C_NAME && x.C_ADDRESS == y.C_ADDRESS && x.C_PHONE == y.C_PHONE && x.C_ACCTBAL == y.C_ACCTBAL && x.C_COMMENT == y.C_COMMENT && x.N_NAME == y.N_NAME;
    }
  };
  
  struct REVENUE_mORDERS4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mORDERS4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mORDERS4_entry& x, const REVENUE_mORDERS4_entry& y) {
      return x.REVENUE_mORDERSORDERS_CUSTKEY == y.REVENUE_mORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mORDERS4_entry,long,
    HashIndex<REVENUE_mORDERS4_entry,long,REVENUE_mORDERS4_mapkey0123456_idxfn,true>,
    HashIndex<REVENUE_mORDERS4_entry,long,REVENUE_mORDERS4_mapkey0_idxfn,false>
  > REVENUE_mORDERS4_map;
  typedef HashIndex<REVENUE_mORDERS4_entry,long,REVENUE_mORDERS4_mapkey0123456_idxfn,true> HashIndex_REVENUE_mORDERS4_map_0123456;
  typedef HashIndex<REVENUE_mORDERS4_entry,long,REVENUE_mORDERS4_mapkey0_idxfn,false> HashIndex_REVENUE_mORDERS4_map_0;
  
  struct REVENUE_mCUSTOMER1_entry {
    long REVENUE_mCUSTOMERCUSTOMER_CUSTKEY; DOUBLE_TYPE __av; 
    explicit REVENUE_mCUSTOMER1_entry() { /*REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = 0L; __av = 0.0; */ }
    explicit REVENUE_mCUSTOMER1_entry(const long c0, const DOUBLE_TYPE c1) { REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c0; __av = c1; }
    REVENUE_mCUSTOMER1_entry(const REVENUE_mCUSTOMER1_entry& other) : REVENUE_mCUSTOMERCUSTOMER_CUSTKEY( other.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mCUSTOMER1_entry& modify(const long c0) { REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_entry& x, const REVENUE_mCUSTOMER1_entry& y) {
      return x.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mCUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mCUSTOMER1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mapkey0_idxfn,true>
  > REVENUE_mCUSTOMER1_map;
  typedef HashIndex<REVENUE_mCUSTOMER1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mapkey0_idxfn,true> HashIndex_REVENUE_mCUSTOMER1_map_0;
  
  struct REVENUE_mCUSTOMER2_entry {
    long REVENUE_mCUSTOMERCUSTOMER_NATIONKEY; STRING_TYPE N_NAME; long __av; 
    explicit REVENUE_mCUSTOMER2_entry() { /*REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = 0L; N_NAME = ""; __av = 0L; */ }
    explicit REVENUE_mCUSTOMER2_entry(const long c0, const STRING_TYPE& c1, const long c2) { REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c0; N_NAME = c1; __av = c2; }
    REVENUE_mCUSTOMER2_entry(const REVENUE_mCUSTOMER2_entry& other) : REVENUE_mCUSTOMERCUSTOMER_NATIONKEY( other.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY ), N_NAME( other.N_NAME ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mCUSTOMER2_entry& modify(const long c0, const STRING_TYPE& c1) { REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c0; N_NAME = c1;  return *this; }
    FORCE_INLINE REVENUE_mCUSTOMER2_entry& modify0(const long c0) { REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, N_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mCUSTOMER2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      hash_combine(h, e.N_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER2_entry& x, const REVENUE_mCUSTOMER2_entry& y) {
      return x.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY == y.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY && x.N_NAME == y.N_NAME;
    }
  };
  
  struct REVENUE_mCUSTOMER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER2_entry& x, const REVENUE_mCUSTOMER2_entry& y) {
      return x.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY == y.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mCUSTOMER2_entry,long,
    HashIndex<REVENUE_mCUSTOMER2_entry,long,REVENUE_mCUSTOMER2_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mCUSTOMER2_entry,long,REVENUE_mCUSTOMER2_mapkey0_idxfn,false>
  > REVENUE_mCUSTOMER2_map;
  typedef HashIndex<REVENUE_mCUSTOMER2_entry,long,REVENUE_mCUSTOMER2_mapkey01_idxfn,true> HashIndex_REVENUE_mCUSTOMER2_map_01;
  typedef HashIndex<REVENUE_mCUSTOMER2_entry,long,REVENUE_mCUSTOMER2_mapkey0_idxfn,false> HashIndex_REVENUE_mCUSTOMER2_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const REVENUE_map& _REVENUE = get_REVENUE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(REVENUE), _REVENUE, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const REVENUE_map& get_REVENUE() const {
      return REVENUE;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    REVENUE_map REVENUE;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c1 = STRING_TYPE("R");
      c3 = Udate(STRING_TYPE("1993-10-1"));
      c2 = Udate(STRING_TYPE("1994-1-1"));
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_NATION(const long nation_nationkey, const STRING_TYPE nation_name, const long nation_regionkey, const STRING_TYPE nation_comment) {
      NATION_entry e(nation_nationkey, nation_name, nation_regionkey, nation_comment, 1L);
      NATION.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_REVENUE_mLINEITEM2_map_0* i1 = static_cast<HashIndex_REVENUE_mLINEITEM2_map_0*>(REVENUE_mLINEITEM2.index[1]);
          const HASH_RES_t h1 = REVENUE_mLINEITEM2_mapkey0_idxfn::hash(se2.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mLINEITEM2_map_0::IdxNode* n1 = static_cast<HashIndex_REVENUE_mLINEITEM2_map_0::IdxNode*>(i1->slice(se2, h1));
          REVENUE_mLINEITEM2_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long c_custkey = e1->C_CUSTKEY;
              STRING_TYPE c_name = e1->C_NAME;
              STRING_TYPE c_address = e1->C_ADDRESS;
              STRING_TYPE c_phone = e1->C_PHONE;
              DOUBLE_TYPE c_acctbal = e1->C_ACCTBAL;
              STRING_TYPE c_comment = e1->C_COMMENT;
              STRING_TYPE n_name = e1->N_NAME;
              long v1 = e1->__av;
              (/*if */(lineitem_returnflag == c1) ? REVENUE.addOrDelOnZero(se1.modify(c_custkey,c_name,c_acctbal,n_name,c_address,c_phone,c_comment),(v1 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  REVENUE_mLINEITEM2_mapkey0_idxfn::equals(se2, *e1)); 
          }
        }(/*if */(lineitem_returnflag == c1) ? REVENUE_mORDERS3.addOrDelOnZero(se3.modify(lineitem_orderkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        { //slice 
          const HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_0* i2 = static_cast<HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_0*>(REVENUE_mLINEITEM2_mCUSTOMER1.index[1]);
          const HASH_RES_t h2 = REVENUE_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn::hash(se5.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_0::IdxNode* n2 = static_cast<HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_0::IdxNode*>(i2->slice(se5, h2));
          REVENUE_mLINEITEM2_mCUSTOMER1_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long revenue_mcustomercustomer_custkey = e2->REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY;
              long v2 = e2->__av;
              (/*if */(lineitem_returnflag == c1) ? REVENUE_mCUSTOMER1.addOrDelOnZero(se4.modify(revenue_mcustomercustomer_custkey),(v2 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  REVENUE_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn::equals(se5, *e2)); 
          }
        }
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_REVENUE_mLINEITEM2_map_0* i3 = static_cast<HashIndex_REVENUE_mLINEITEM2_map_0*>(REVENUE_mLINEITEM2.index[1]);
          const HASH_RES_t h3 = REVENUE_mLINEITEM2_mapkey0_idxfn::hash(se7.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mLINEITEM2_map_0::IdxNode* n3 = static_cast<HashIndex_REVENUE_mLINEITEM2_map_0::IdxNode*>(i3->slice(se7, h3));
          REVENUE_mLINEITEM2_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              long c_custkey = e3->C_CUSTKEY;
              STRING_TYPE c_name = e3->C_NAME;
              STRING_TYPE c_address = e3->C_ADDRESS;
              STRING_TYPE c_phone = e3->C_PHONE;
              DOUBLE_TYPE c_acctbal = e3->C_ACCTBAL;
              STRING_TYPE c_comment = e3->C_COMMENT;
              STRING_TYPE n_name = e3->N_NAME;
              long v3 = e3->__av;
              (/*if */(lineitem_returnflag == c1) ? REVENUE.addOrDelOnZero(se6.modify(c_custkey,c_name,c_acctbal,n_name,c_address,c_phone,c_comment),(v3 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))) : (void)0);
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  REVENUE_mLINEITEM2_mapkey0_idxfn::equals(se7, *e3)); 
          }
        }(/*if */(lineitem_returnflag == c1) ? REVENUE_mORDERS3.addOrDelOnZero(se8.modify(lineitem_orderkey),(-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
        { //slice 
          const HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_0* i4 = static_cast<HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_0*>(REVENUE_mLINEITEM2_mCUSTOMER1.index[1]);
          const HASH_RES_t h4 = REVENUE_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn::hash(se10.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_0::IdxNode* n4 = static_cast<HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_0::IdxNode*>(i4->slice(se10, h4));
          REVENUE_mLINEITEM2_mCUSTOMER1_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long revenue_mcustomercustomer_custkey = e4->REVENUE_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY;
              long v4 = e4->__av;
              (/*if */(lineitem_returnflag == c1) ? REVENUE_mCUSTOMER1.addOrDelOnZero(se9.modify(revenue_mcustomercustomer_custkey),(v4 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  REVENUE_mLINEITEM2_mCUSTOMER1_mapkey0_idxfn::equals(se10, *e4)); 
          }
        }
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_REVENUE_mORDERS4_map_0* i5 = static_cast<HashIndex_REVENUE_mORDERS4_map_0*>(REVENUE_mORDERS4.index[1]);
          const HASH_RES_t h5 = REVENUE_mORDERS4_mapkey0_idxfn::hash(se13.modify0(orders_custkey));
          HashIndex_REVENUE_mORDERS4_map_0::IdxNode* n5 = static_cast<HashIndex_REVENUE_mORDERS4_map_0::IdxNode*>(i5->slice(se13, h5));
          REVENUE_mORDERS4_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              STRING_TYPE c_name = e5->C_NAME;
              STRING_TYPE c_address = e5->C_ADDRESS;
              STRING_TYPE c_phone = e5->C_PHONE;
              DOUBLE_TYPE c_acctbal = e5->C_ACCTBAL;
              STRING_TYPE c_comment = e5->C_COMMENT;
              STRING_TYPE n_name = e5->N_NAME;
              long v5 = e5->__av;
              (/*if */(c2 > orders_orderdate && orders_orderdate >= c3) ? REVENUE.addOrDelOnZero(se11.modify(orders_custkey,c_name,c_acctbal,n_name,c_address,c_phone,c_comment),(REVENUE_mORDERS3.getValueOrDefault(se12.modify(orders_orderkey)) * v5)) : (void)0);
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  REVENUE_mORDERS4_mapkey0_idxfn::equals(se13, *e5)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mORDERS4_map_0* i6 = static_cast<HashIndex_REVENUE_mORDERS4_map_0*>(REVENUE_mORDERS4.index[1]);
          const HASH_RES_t h6 = REVENUE_mORDERS4_mapkey0_idxfn::hash(se15.modify0(orders_custkey));
          HashIndex_REVENUE_mORDERS4_map_0::IdxNode* n6 = static_cast<HashIndex_REVENUE_mORDERS4_map_0::IdxNode*>(i6->slice(se15, h6));
          REVENUE_mORDERS4_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              STRING_TYPE c_name = e6->C_NAME;
              STRING_TYPE c_address = e6->C_ADDRESS;
              STRING_TYPE c_phone = e6->C_PHONE;
              DOUBLE_TYPE c_acctbal = e6->C_ACCTBAL;
              STRING_TYPE c_comment = e6->C_COMMENT;
              STRING_TYPE n_name = e6->N_NAME;
              long v6 = e6->__av;
              (/*if */(c2 > orders_orderdate && orders_orderdate >= c3) ? REVENUE_mLINEITEM2.addOrDelOnZero(se14.modify(orders_orderkey,orders_custkey,c_name,c_address,c_phone,c_acctbal,c_comment,n_name),v6) : (void)0);
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h6 == n6->hash &&  REVENUE_mORDERS4_mapkey0_idxfn::equals(se15, *e6)); 
          }
        }(/*if */(orders_orderdate >= c3 && c2 > orders_orderdate) ? REVENUE_mLINEITEM2_mCUSTOMER1.addOrDelOnZero(se16.modify(orders_orderkey,orders_custkey),1L) : (void)0);
        (/*if */(c2 > orders_orderdate && orders_orderdate >= c3) ? REVENUE_mCUSTOMER1.addOrDelOnZero(se17.modify(orders_custkey),REVENUE_mORDERS3.getValueOrDefault(se18.modify(orders_orderkey))) : (void)0);
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_REVENUE_mORDERS4_map_0* i7 = static_cast<HashIndex_REVENUE_mORDERS4_map_0*>(REVENUE_mORDERS4.index[1]);
          const HASH_RES_t h7 = REVENUE_mORDERS4_mapkey0_idxfn::hash(se21.modify0(orders_custkey));
          HashIndex_REVENUE_mORDERS4_map_0::IdxNode* n7 = static_cast<HashIndex_REVENUE_mORDERS4_map_0::IdxNode*>(i7->slice(se21, h7));
          REVENUE_mORDERS4_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              STRING_TYPE c_name = e7->C_NAME;
              STRING_TYPE c_address = e7->C_ADDRESS;
              STRING_TYPE c_phone = e7->C_PHONE;
              DOUBLE_TYPE c_acctbal = e7->C_ACCTBAL;
              STRING_TYPE c_comment = e7->C_COMMENT;
              STRING_TYPE n_name = e7->N_NAME;
              long v7 = e7->__av;
              (/*if */(orders_orderdate >= c3 && c2 > orders_orderdate) ? REVENUE.addOrDelOnZero(se19.modify(orders_custkey,c_name,c_acctbal,n_name,c_address,c_phone,c_comment),(REVENUE_mORDERS3.getValueOrDefault(se20.modify(orders_orderkey)) * (v7 * -1L))) : (void)0);
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h7 == n7->hash &&  REVENUE_mORDERS4_mapkey0_idxfn::equals(se21, *e7)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mORDERS4_map_0* i8 = static_cast<HashIndex_REVENUE_mORDERS4_map_0*>(REVENUE_mORDERS4.index[1]);
          const HASH_RES_t h8 = REVENUE_mORDERS4_mapkey0_idxfn::hash(se23.modify0(orders_custkey));
          HashIndex_REVENUE_mORDERS4_map_0::IdxNode* n8 = static_cast<HashIndex_REVENUE_mORDERS4_map_0::IdxNode*>(i8->slice(se23, h8));
          REVENUE_mORDERS4_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              STRING_TYPE c_name = e8->C_NAME;
              STRING_TYPE c_address = e8->C_ADDRESS;
              STRING_TYPE c_phone = e8->C_PHONE;
              DOUBLE_TYPE c_acctbal = e8->C_ACCTBAL;
              STRING_TYPE c_comment = e8->C_COMMENT;
              STRING_TYPE n_name = e8->N_NAME;
              long v8 = e8->__av;
              (/*if */(c2 > orders_orderdate && orders_orderdate >= c3) ? REVENUE_mLINEITEM2.addOrDelOnZero(se22.modify(orders_orderkey,orders_custkey,c_name,c_address,c_phone,c_acctbal,c_comment,n_name),(v8 * -1L)) : (void)0);
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h8 == n8->hash &&  REVENUE_mORDERS4_mapkey0_idxfn::equals(se23, *e8)); 
          }
        }(/*if */(orders_orderdate >= c3 && c2 > orders_orderdate) ? REVENUE_mLINEITEM2_mCUSTOMER1.addOrDelOnZero(se24.modify(orders_orderkey,orders_custkey),-1L) : (void)0);
        (/*if */(orders_orderdate >= c3 && c2 > orders_orderdate) ? REVENUE_mCUSTOMER1.addOrDelOnZero(se25.modify(orders_custkey),(REVENUE_mORDERS3.getValueOrDefault(se26.modify(orders_orderkey)) * -1L)) : (void)0);
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER2_map_0* i9 = static_cast<HashIndex_REVENUE_mCUSTOMER2_map_0*>(REVENUE_mCUSTOMER2.index[1]);
          const HASH_RES_t h9 = REVENUE_mCUSTOMER2_mapkey0_idxfn::hash(se29.modify0(customer_nationkey));
          HashIndex_REVENUE_mCUSTOMER2_map_0::IdxNode* n9 = static_cast<HashIndex_REVENUE_mCUSTOMER2_map_0::IdxNode*>(i9->slice(se29, h9));
          REVENUE_mCUSTOMER2_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              STRING_TYPE n_name = e9->N_NAME;
              long v9 = e9->__av;
              REVENUE.addOrDelOnZero(se27.modify(customer_custkey,customer_name,customer_acctbal,n_name,customer_address,customer_phone,customer_comment),(REVENUE_mCUSTOMER1.getValueOrDefault(se28.modify(customer_custkey)) * v9));
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h9 == n9->hash &&  REVENUE_mCUSTOMER2_mapkey0_idxfn::equals(se29, *e9)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_1* i10 = static_cast<HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_1*>(REVENUE_mLINEITEM2_mCUSTOMER1.index[2]);
          const HASH_RES_t h11 = REVENUE_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn::hash(se32.modify1(customer_custkey));
          HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_1::IdxNode* n10 = static_cast<HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_1::IdxNode*>(i10->slice(se32, h11));
          REVENUE_mLINEITEM2_mCUSTOMER1_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              long revenue_mlineitemlineitem_orderkey = e10->REVENUE_mLINEITEMLINEITEM_ORDERKEY;
              long v10 = e10->__av;
              { //slice 
                const HashIndex_REVENUE_mCUSTOMER2_map_0* i11 = static_cast<HashIndex_REVENUE_mCUSTOMER2_map_0*>(REVENUE_mCUSTOMER2.index[1]);
                const HASH_RES_t h10 = REVENUE_mCUSTOMER2_mapkey0_idxfn::hash(se31.modify0(customer_nationkey));
                HashIndex_REVENUE_mCUSTOMER2_map_0::IdxNode* n11 = static_cast<HashIndex_REVENUE_mCUSTOMER2_map_0::IdxNode*>(i11->slice(se31, h10));
                REVENUE_mCUSTOMER2_entry* e11;
               
                if (n11 && (e11 = n11->obj)) {
                  do {                
                    STRING_TYPE n_name = e11->N_NAME;
                    long v11 = e11->__av;
                    REVENUE_mLINEITEM2.addOrDelOnZero(se30.modify(revenue_mlineitemlineitem_orderkey,customer_custkey,customer_name,customer_address,customer_phone,customer_acctbal,customer_comment,n_name),(v10 * v11));
                    n11 = n11->nxt;
                  } while (n11 && (e11 = n11->obj) && h10 == n11->hash &&  REVENUE_mCUSTOMER2_mapkey0_idxfn::equals(se31, *e11)); 
                }
              }
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h11 == n10->hash &&  REVENUE_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn::equals(se32, *e10)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mCUSTOMER2_map_0* i12 = static_cast<HashIndex_REVENUE_mCUSTOMER2_map_0*>(REVENUE_mCUSTOMER2.index[1]);
          const HASH_RES_t h12 = REVENUE_mCUSTOMER2_mapkey0_idxfn::hash(se34.modify0(customer_nationkey));
          HashIndex_REVENUE_mCUSTOMER2_map_0::IdxNode* n12 = static_cast<HashIndex_REVENUE_mCUSTOMER2_map_0::IdxNode*>(i12->slice(se34, h12));
          REVENUE_mCUSTOMER2_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              STRING_TYPE n_name = e12->N_NAME;
              long v12 = e12->__av;
              REVENUE_mORDERS4.addOrDelOnZero(se33.modify(customer_custkey,customer_name,customer_address,customer_phone,customer_acctbal,customer_comment,n_name),v12);
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h12 == n12->hash &&  REVENUE_mCUSTOMER2_mapkey0_idxfn::equals(se34, *e12)); 
          }
        }
      }
    }
    void on_delete_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER2_map_0* i13 = static_cast<HashIndex_REVENUE_mCUSTOMER2_map_0*>(REVENUE_mCUSTOMER2.index[1]);
          const HASH_RES_t h13 = REVENUE_mCUSTOMER2_mapkey0_idxfn::hash(se37.modify0(customer_nationkey));
          HashIndex_REVENUE_mCUSTOMER2_map_0::IdxNode* n13 = static_cast<HashIndex_REVENUE_mCUSTOMER2_map_0::IdxNode*>(i13->slice(se37, h13));
          REVENUE_mCUSTOMER2_entry* e13;
         
          if (n13 && (e13 = n13->obj)) {
            do {                
              STRING_TYPE n_name = e13->N_NAME;
              long v13 = e13->__av;
              REVENUE.addOrDelOnZero(se35.modify(customer_custkey,customer_name,customer_acctbal,n_name,customer_address,customer_phone,customer_comment),(REVENUE_mCUSTOMER1.getValueOrDefault(se36.modify(customer_custkey)) * (v13 * -1L)));
              n13 = n13->nxt;
            } while (n13 && (e13 = n13->obj) && h13 == n13->hash &&  REVENUE_mCUSTOMER2_mapkey0_idxfn::equals(se37, *e13)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_1* i14 = static_cast<HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_1*>(REVENUE_mLINEITEM2_mCUSTOMER1.index[2]);
          const HASH_RES_t h15 = REVENUE_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn::hash(se40.modify1(customer_custkey));
          HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_1::IdxNode* n14 = static_cast<HashIndex_REVENUE_mLINEITEM2_mCUSTOMER1_map_1::IdxNode*>(i14->slice(se40, h15));
          REVENUE_mLINEITEM2_mCUSTOMER1_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              long revenue_mlineitemlineitem_orderkey = e14->REVENUE_mLINEITEMLINEITEM_ORDERKEY;
              long v14 = e14->__av;
              { //slice 
                const HashIndex_REVENUE_mCUSTOMER2_map_0* i15 = static_cast<HashIndex_REVENUE_mCUSTOMER2_map_0*>(REVENUE_mCUSTOMER2.index[1]);
                const HASH_RES_t h14 = REVENUE_mCUSTOMER2_mapkey0_idxfn::hash(se39.modify0(customer_nationkey));
                HashIndex_REVENUE_mCUSTOMER2_map_0::IdxNode* n15 = static_cast<HashIndex_REVENUE_mCUSTOMER2_map_0::IdxNode*>(i15->slice(se39, h14));
                REVENUE_mCUSTOMER2_entry* e15;
               
                if (n15 && (e15 = n15->obj)) {
                  do {                
                    STRING_TYPE n_name = e15->N_NAME;
                    long v15 = e15->__av;
                    REVENUE_mLINEITEM2.addOrDelOnZero(se38.modify(revenue_mlineitemlineitem_orderkey,customer_custkey,customer_name,customer_address,customer_phone,customer_acctbal,customer_comment,n_name),(v14 * (v15 * -1L)));
                    n15 = n15->nxt;
                  } while (n15 && (e15 = n15->obj) && h14 == n15->hash &&  REVENUE_mCUSTOMER2_mapkey0_idxfn::equals(se39, *e15)); 
                }
              }
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h15 == n14->hash &&  REVENUE_mLINEITEM2_mCUSTOMER1_mapkey1_idxfn::equals(se40, *e14)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mCUSTOMER2_map_0* i16 = static_cast<HashIndex_REVENUE_mCUSTOMER2_map_0*>(REVENUE_mCUSTOMER2.index[1]);
          const HASH_RES_t h16 = REVENUE_mCUSTOMER2_mapkey0_idxfn::hash(se42.modify0(customer_nationkey));
          HashIndex_REVENUE_mCUSTOMER2_map_0::IdxNode* n16 = static_cast<HashIndex_REVENUE_mCUSTOMER2_map_0::IdxNode*>(i16->slice(se42, h16));
          REVENUE_mCUSTOMER2_entry* e16;
         
          if (n16 && (e16 = n16->obj)) {
            do {                
              STRING_TYPE n_name = e16->N_NAME;
              long v16 = e16->__av;
              REVENUE_mORDERS4.addOrDelOnZero(se41.modify(customer_custkey,customer_name,customer_address,customer_phone,customer_acctbal,customer_comment,n_name),(v16 * -1L));
              n16 = n16->nxt;
            } while (n16 && (e16 = n16->obj) && h16 == n16->hash &&  REVENUE_mCUSTOMER2_mapkey0_idxfn::equals(se42, *e16)); 
          }
        }
      }
    }
    void on_system_ready_event() {
      {  //
        REVENUE_mCUSTOMER2.clear();
        {  // foreach
          const HashIndex_NATION_map_0123* i17 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n17; 
          NATION_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long revenue_mcustomercustomer_nationkey = e17->NATION_NATIONKEY;
                STRING_TYPE n_name = e17->NATION_NAME;
                long n_regionkey = e17->NATION_REGIONKEY;
                STRING_TYPE n_comment = e17->NATION_COMMENT;
                long v17 = e17->__av;
                REVENUE_mCUSTOMER2.addOrDelOnZero(se43.modify(revenue_mcustomercustomer_nationkey,n_name),v17);
              n17 = n17->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    REVENUE_entry se1;
    REVENUE_mLINEITEM2_entry se2;
    REVENUE_mORDERS3_entry se3;
    REVENUE_mCUSTOMER1_entry se4;
    REVENUE_mLINEITEM2_mCUSTOMER1_entry se5;
    REVENUE_entry se6;
    REVENUE_mLINEITEM2_entry se7;
    REVENUE_mORDERS3_entry se8;
    REVENUE_mCUSTOMER1_entry se9;
    REVENUE_mLINEITEM2_mCUSTOMER1_entry se10;
    REVENUE_entry se11;
    REVENUE_mORDERS3_entry se12;
    REVENUE_mORDERS4_entry se13;
    REVENUE_mLINEITEM2_entry se14;
    REVENUE_mORDERS4_entry se15;
    REVENUE_mLINEITEM2_mCUSTOMER1_entry se16;
    REVENUE_mCUSTOMER1_entry se17;
    REVENUE_mORDERS3_entry se18;
    REVENUE_entry se19;
    REVENUE_mORDERS3_entry se20;
    REVENUE_mORDERS4_entry se21;
    REVENUE_mLINEITEM2_entry se22;
    REVENUE_mORDERS4_entry se23;
    REVENUE_mLINEITEM2_mCUSTOMER1_entry se24;
    REVENUE_mCUSTOMER1_entry se25;
    REVENUE_mORDERS3_entry se26;
    REVENUE_entry se27;
    REVENUE_mCUSTOMER1_entry se28;
    REVENUE_mCUSTOMER2_entry se29;
    REVENUE_mLINEITEM2_entry se30;
    REVENUE_mCUSTOMER2_entry se31;
    REVENUE_mLINEITEM2_mCUSTOMER1_entry se32;
    REVENUE_mORDERS4_entry se33;
    REVENUE_mCUSTOMER2_entry se34;
    REVENUE_entry se35;
    REVENUE_mCUSTOMER1_entry se36;
    REVENUE_mCUSTOMER2_entry se37;
    REVENUE_mLINEITEM2_entry se38;
    REVENUE_mCUSTOMER2_entry se39;
    REVENUE_mLINEITEM2_mCUSTOMER1_entry se40;
    REVENUE_mORDERS4_entry se41;
    REVENUE_mCUSTOMER2_entry se42;
    REVENUE_mCUSTOMER2_entry se43;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REVENUE_mLINEITEM2_map REVENUE_mLINEITEM2;
    REVENUE_mLINEITEM2_mCUSTOMER1_map REVENUE_mLINEITEM2_mCUSTOMER1;
    REVENUE_mORDERS3_map REVENUE_mORDERS3;
    REVENUE_mORDERS4_map REVENUE_mORDERS4;
    REVENUE_mCUSTOMER1_map REVENUE_mCUSTOMER1;
    REVENUE_mCUSTOMER2_map REVENUE_mCUSTOMER2;
    
    /*const static*/ STRING_TYPE c1;
    /*const static*/ long c3;
    /*const static*/ long c2;
    /*const static*/ STRING_TYPE c4;
  
  };

}
